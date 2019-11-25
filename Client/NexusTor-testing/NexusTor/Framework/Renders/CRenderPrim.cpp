////////////////////////////////////////////////////////////////////////
// This font class was created by Azorbix (Matthew L) for Game-Deception
// http://www.game-deception.com   http://forum.game-deception.com
// irc://irc.rizon.net/game-deception
//
// A lot all of the CD3DFont::Initialize() code was created by Microsoft
// (taken from the D3D9 SDK)
// 
// Please note that this is NOT 100% complete yet, colour tags and 
// shadows are not implemented yet
//
// USAGE:
//   CD3DFont:
//     1) Instanciate the class with the parameterized constructor
//        eg CD3DFont *g_pD3Dfont = new CD3DFont("Arial", 16, FCT_BOLD);
//
//     2) Call Initialize() after other rendering is ready
//        eg g_pD3DFont->Initialize(pD3Ddevice);
//
//     3) To begin rendering use Print function
//        eg g_pD3DFont->Print(10.0f, 50.0f, 0xFF00FF00, "Hello World", FT_BORDER);
//
//     4) call Invalidate() upon Reset of the D3D surface and re-initialize
//
//   CD3DRender:
//     1) Instanciate the class with the parameterized constructor
//        eg CD3DRender *g_pRender = new CD3DRender(128);
//
//     2) Call Initialize() after other rendering is ready
//        eg g_pRender->Initialize(pD3Ddevice);
//
//     3) To begin rendering, start rendering much like OpenGL
//        eg if( SUCCEEDED(g_pRender->Begin(D3DPT_TRIANGLELIST)) )
//           {
//               D3DAddQuad(g_pRender, 10.0f, 10.0f, 50.0f, 50.0f, 0xFFFF0000); //helper function
//               g_pRender->D3DColour(0xFF0000FF); //blue
//               g_pRender->D3DVertex2f(60.0f, 60.0f);
//               g_pRender->D3DVertex2f(60.0f, 110.0f);
//               g_pRender->D3DVertex2f(110.0f, 110.0f);
//               g_pRender->End();
//           }
//
//     4) call Invalidate() upon Reset of the D3D surface and re-initialize
//
// FASTER RENDERING (Advanced but NOT REQUIRED):
//   To enable faster rendering, it's ideal to call static function CD3DBaseRendering::BeginRender(); before
//   other font / primitive rendering code, and call CD3DBaseRendering::EndRender(); afterwards
//   *** IT IS CRUCIAL THAT YOU CALL EndRender FOR EVERY BeginRender() CALL ***
//   *** IMAGE RENDERING MAY BECOME CORRUPT IF YOU DO NOT ***
//   eg
//     if( SUCCEEDED(CD3DBaseRender::BeginRender()) )
//     {
//         //primitive and font rendering goes here
//         CD3DBaseRender::EndRender();
//     }
//

#include "CRenderPrim.h"

//#define _DEBUG(s) add_log(s)
#define _DEBUG(s) /*s*/

IDirect3DDevice9		*CD3DBaseRender::m_pD3Ddev = NULL;
IDirect3DStateBlock9	*CD3DBaseRender::m_pD3DstateDraw = NULL;
IDirect3DStateBlock9	*CD3DBaseRender::m_pD3DstateNorm = NULL;
int						CD3DBaseRender::m_renderCount = 0;
int						CD3DBaseRender::m_numShared = 0;
bool					CD3DBaseRender::m_statesOK = false;

inline d3dfont_s InitFont2DVertex(float x, float y, DWORD colour, float tu, float tv)
{
	d3dfont_s v = { x, y, 1.0f, 1.0f, colour, tu, tv };
	return v;
}

inline d3dprimitives_s InitPrim2DVertex(float x, float y, DWORD colour)
{
	d3dprimitives_s v = { x, y, 1.0f, 1.0f, colour };
	return v;
}


CD3DBaseRender::CD3DBaseRender()
{
	m_numShared++;
}

CD3DBaseRender::~CD3DBaseRender()
{
	if( (--m_numShared) == 0)
		DeleteStates();
}

HRESULT CD3DBaseRender::Initialize(IDirect3DDevice9 *pD3Ddev)
{
	if( m_pD3Ddev == NULL && (m_pD3Ddev = pD3Ddev) == NULL )
	{
		_DEBUG("m_pD3Ddev is NULL");
		return E_FAIL;
	}
	
	if( !m_statesOK && FAILED(CreateStates()) )
	{
		_DEBUG("CreateStates() failed");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CD3DBaseRender::Invalidate()
{
	DeleteStates();
	return S_OK;		
}

HRESULT CD3DBaseRender::BeginRender()
{
	if( !m_statesOK )
	{
		_DEBUG("::BeginRender() m_statesOK = false");
		return E_FAIL;
	}

	m_renderCount++;
	if( m_renderCount == 1 )
	{
		m_pD3DstateNorm->Capture();
		m_pD3DstateDraw->Apply();
	}

	return S_OK;
}

HRESULT CD3DBaseRender::EndRender()
{
	if( !m_statesOK )
	{
		_DEBUG("::EndRender() m_statesOK = false");
		return E_FAIL;
	}

	m_renderCount--;

	if( m_renderCount == 0)
		m_pD3DstateNorm->Apply();
	else if(m_renderCount < 0)
		m_renderCount = 0;

	return S_OK;
}

HRESULT CD3DBaseRender::CreateStates()
{
    for(int iStateBlock = 0; iStateBlock < 2; iStateBlock++)
	{
		m_pD3Ddev->BeginStateBlock();
		m_pD3Ddev->SetPixelShader(NULL);
		m_pD3Ddev->SetVertexShader(NULL);

        m_pD3Ddev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        m_pD3Ddev->SetRenderState( D3DRS_SRCBLEND,   D3DBLEND_SRCALPHA );
        m_pD3Ddev->SetRenderState( D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA );
        m_pD3Ddev->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
        m_pD3Ddev->SetRenderState( D3DRS_ALPHAREF,         0x08 );
        m_pD3Ddev->SetRenderState( D3DRS_ALPHAFUNC,  D3DCMP_GREATEREQUAL );
        m_pD3Ddev->SetRenderState( D3DRS_FILLMODE,   D3DFILL_SOLID );
        m_pD3Ddev->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CCW );
        m_pD3Ddev->SetRenderState( D3DRS_STENCILENABLE,    FALSE );
        m_pD3Ddev->SetRenderState( D3DRS_CLIPPING,         TRUE );
        m_pD3Ddev->SetRenderState( D3DRS_CLIPPLANEENABLE,  FALSE );
        m_pD3Ddev->SetRenderState( D3DRS_VERTEXBLEND,      D3DVBF_DISABLE );
        m_pD3Ddev->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE );
        m_pD3Ddev->SetRenderState( D3DRS_FOGENABLE,        FALSE );
        m_pD3Ddev->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_ALPHA);
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
        m_pD3Ddev->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
        m_pD3Ddev->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
        m_pD3Ddev->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
        m_pD3Ddev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
        m_pD3Ddev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
        m_pD3Ddev->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

		if(iStateBlock)	m_pD3Ddev->EndStateBlock(&m_pD3DstateDraw);
		else			m_pD3Ddev->EndStateBlock(&m_pD3DstateNorm);
	}

	m_statesOK = true;

	return S_OK;
}

HRESULT CD3DBaseRender::DeleteStates()
{
	SAFE_RELEASE(m_pD3DstateDraw);
	SAFE_RELEASE(m_pD3DstateNorm);
	m_statesOK = false;

	return S_OK;
}

/*
ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRS
TUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKL
MNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE
*/

CD3DRender::CD3DRender(int numVertices)
{
	m_canRender = false;

	m_pD3Dbuf = NULL;
	m_pVertex = NULL;

	m_maxVertex = numVertices;
	m_curVertex = 0;
}


CD3DRender::~CD3DRender()
{
	Invalidate();
}


HRESULT CD3DRender::Initialize(IDirect3DDevice9 *pD3Ddev)
{
	if( !m_canRender )
	{
		if( FAILED(CD3DBaseRender::Initialize(pD3Ddev)) )
			return E_FAIL;
		
		if( FAILED(m_pD3Ddev->CreateVertexBuffer(m_maxVertex * sizeof(d3dprimitives_s), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pD3Dbuf, NULL)) )
			return E_FAIL;
	
		m_canRender = true;
	}

	return S_OK;
}


HRESULT CD3DRender::Invalidate()
{
	CD3DBaseRender::Invalidate();
	SAFE_RELEASE(m_pD3Dbuf);
    m_canRender = false;
	m_pVertex = NULL;

	return S_OK;
}


HRESULT CD3DRender::Begin(D3DPRIMITIVETYPE primType)
{
	if( !m_canRender )
		return E_FAIL;

	if( m_pVertex != NULL )
		return E_FAIL;

	if( FAILED(m_pD3Dbuf->Lock(0, 0, (void**)&m_pVertex, D3DLOCK_DISCARD)) )
		return E_FAIL;
	
	m_primType = primType;

	return S_OK;
}


HRESULT CD3DRender::End()
{
	m_pVertex = NULL;

	if( !m_canRender )
	{
		m_curVertex = 0;
		return E_FAIL;
	}

	if( FAILED(CD3DBaseRender::BeginRender()) )
		return E_FAIL;

	int numPrims;

	switch(m_primType)
	{
		case D3DPT_POINTLIST:
			numPrims = m_curVertex;
			break;
		case D3DPT_LINELIST:
			numPrims = (int)floor(m_curVertex / 2.0f);
			break;
		case D3DPT_LINESTRIP:
			numPrims = m_curVertex - 1;
			break;
		case D3DPT_TRIANGLELIST:
			numPrims = (int)floor(m_curVertex / 3.0f);
			break;
		case D3DPT_TRIANGLESTRIP:
		case D3DPT_TRIANGLEFAN:
			numPrims = m_curVertex - 2;
			break;
		default:
			numPrims = 0;
			break;
	}

	m_curVertex = 0;

	if( numPrims > 0 )
	{
		m_pD3Dbuf->Unlock();

		DWORD fvf;
		m_pD3Ddev->GetFVF(&fvf);
		m_pD3Ddev->SetFVF(D3DFVF_PRIMITIVES);

		m_pD3Ddev->SetTexture(0, NULL);
		m_pD3Ddev->SetStreamSource(0, m_pD3Dbuf, 0, sizeof(d3dprimitives_s));

		m_pD3Ddev->DrawPrimitive(m_primType, 0, numPrims);

		m_pD3Ddev->SetFVF(fvf);
	}

	CD3DBaseRender::EndRender();

	return S_OK;
}


inline HRESULT CD3DRender::D3DColour(DWORD colour)
{
	m_colour = colour;
	return ( m_canRender ? S_OK : E_FAIL );
}


inline HRESULT CD3DRender::D3DVertex2f(float x, float y)
{
	if( m_canRender && m_pVertex && ++m_curVertex < m_maxVertex )
		*m_pVertex++ = InitPrim2DVertex(x, y, m_colour);
	else
		return E_FAIL;

	return S_OK;
}


//helper functions
HRESULT D3DAddQuad(CD3DRender *pRender, float x, float y, float w, float h, DWORD colour)
{
	if( pRender && SUCCEEDED(pRender->D3DColour(colour))
	&& SUCCEEDED(pRender->D3DVertex2f(x, y))		//triangle 1
	&& SUCCEEDED(pRender->D3DVertex2f(x+w, y))
	&& SUCCEEDED(pRender->D3DVertex2f(x, y+h))
	&& SUCCEEDED(pRender->D3DVertex2f(x, y+h))		//triangle 2
	&& SUCCEEDED(pRender->D3DVertex2f(x+w, y))
	&& SUCCEEDED(pRender->D3DVertex2f(x+w, y+h)) )
		return S_OK;

	return E_FAIL;
}