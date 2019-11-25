#include "CRender.h"


CRender cRender;

CRender::~CRender()
{

	for(int i = 0; i < TOTAL_FONTS; i++)
		delete m_pFonts[i];

	
	delete m_pRenderPrim;
}

bool CRender::InitD3D(LPDIRECT3DDEVICE9 p_Device)
{

	if(!p_Device)
		return false;

	//set our d3d device
	m_pDevice = p_Device;

	

	/*GenerateShader( &m_Shaders.sBlue, 0.0f, 0.0f, 1.0f );
	GenerateShader( &m_Shaders.sGreen, 0.0f, 1.0f, 0.0f );
	GenerateShader( &m_Shaders.sOrange, 1.0f, 0.5f, 0.0f );
	GenerateShader( &m_Shaders.sPurple, 1.0f, 0.0f, 1.0f );
	GenerateShader( &m_Shaders.sRed, 1.0f, 0.0f, 0.0f );
	GenerateShader( &m_Shaders.sWhite, 1.0f, 1.0f, 1.0f );
	GenerateShader( &m_Shaders.sYellow, 1.0f, 1.0f, 0.0f );*/
	
	m_pDevice->GetViewport(&m_ViewPort);

	

	m_pFonts[MenuFont]    = new CD3DFont("Arial",8);
	m_pFonts[EspFont]     = new CD3DFont("Courier New",10);
	m_pFonts[FooterFont]  = new CD3DFont("Courier New",10);
	m_pFonts[HeaderFont]  = new CD3DFont("Courier New",40);
	m_pFonts[XHairFont]   = new CD3DFont("Courier New",22);

	m_pRenderPrim         = new CD3DRender(128);

	for(int i = 0; i < TOTAL_FONTS; i++)
	{
		if(m_pFonts[i])
		{
			m_pFonts[i]->InitDeviceObjects(m_pDevice);
			m_pFonts[i]->RestoreDeviceObjects();
		}
	}

	

	if(m_pRenderPrim)
	{
		m_pRenderPrim->Initialize(m_pDevice);
	}

	
	D3DXCreateSprite(m_pDevice,&m_pSprite);
	return true;

}
//=============================================
void CRender::onLostDevice()
{
	if(m_pRenderPrim)
		m_pRenderPrim->Invalidate();

	for(int i = 0; i < TOTAL_FONTS;i++)
	{
		if(m_pFonts[i])
		{
			m_pFonts[i]->InvalidateDeviceObjects();
			m_pFonts[i]->DeleteDeviceObjects();
		}
	}

	
	m_pSprite->OnLostDevice();
	
	/*m_Shaders.sBlue->Release();
	m_Shaders.sGreen->Release();
	m_Shaders.sOrange->Release();
	m_Shaders.sPurple->Release();
	m_Shaders.sRed->Release();
	m_Shaders.sWhite->Release();
	m_Shaders.sYellow->Release();*/

}
//============================================
void CRender::onResetDevice()
{

	if(m_pRenderPrim)
		m_pRenderPrim->Initialize(m_pDevice);


	for(int i = 0; i < TOTAL_FONTS; i++)
	{
		if(m_pFonts[i])
		{
			m_pFonts[i]->InitDeviceObjects(m_pDevice);
			m_pFonts[i]->RestoreDeviceObjects();
		}
	}

	
	m_pSprite->OnResetDevice();
	/*GenerateShader( &m_Shaders.sBlue, 0.0f, 0.0f, 1.0f );
	GenerateShader( &m_Shaders.sGreen, 0.0f, 1.0f, 0.0f );
	GenerateShader( &m_Shaders.sOrange, 1.0f, 0.5f, 0.0f );
	GenerateShader( &m_Shaders.sPurple, 1.0f, 0.0f, 1.0f );
	GenerateShader( &m_Shaders.sRed, 1.0f, 0.0f, 0.0f );
	GenerateShader( &m_Shaders.sWhite, 1.0f, 1.0f, 1.0f );
	GenerateShader( &m_Shaders.sYellow, 1.0f, 1.0f, 0.0f );*/

	m_pDevice->GetViewport(&m_ViewPort);

}
//=============================================
HRESULT CRender::DrawOutline(float x,float y,float width,float height,DWORD dwColour)
{
	const int VertexNum = 5;

	CVERTEX Verts[VertexNum];
	//===Original States===
	//=====================
	Verts[0].x = x;
	Verts[0].y = y;
	Verts[0].z = 1.0f;
	Verts[0].rhw = 1.0f;
	Verts[0].dwColour = dwColour;

	Verts[1].x = x+width;
	Verts[1].y = y;
	Verts[1].z = 1.0f;
	Verts[1].rhw = 1.0f;
	Verts[1].dwColour = dwColour;

	Verts[2].x = x+width;
	Verts[2].y = y+height;
	Verts[2].z = 1.0f;
	Verts[2].rhw = 1.0f;
	Verts[2].dwColour = dwColour;

	Verts[3].x = x;
	Verts[3].y = y+height;
	Verts[3].z = 1.0f;
	Verts[3].rhw = 1.0f;
	Verts[3].dwColour = dwColour;

	Verts[4].x = x;
	Verts[4].y = y;
	Verts[4].z = 1.0f;
	Verts[4].rhw = 1.0f;
	Verts[4].dwColour = dwColour;


	
	HRESULT hRet = m_pRenderPrim->Begin(D3DPT_LINESTRIP);

	if(SUCCEEDED(hRet))
	{
		m_pRenderPrim->D3DColour(dwColour);
		for(int i = 0; i < 5; i++)
			m_pRenderPrim->D3DVertex2f(Verts[i].x,Verts[i].y);

		m_pRenderPrim->End();
	}

	return hRet;
}

HRESULT CRender::DrawLine(float startX,float startY,float endX,float endY, DWORD dwColour )
{
	const int VertexNum = 2;

	CVERTEX Verts[VertexNum];
	//===Original States===
	//=====================
	Verts[0].x = startX;
	Verts[0].y = startY;
	Verts[0].z = 1.f;
	Verts[0].rhw = 1.f;
	Verts[0].dwColour = dwColour;

	Verts[1].x = endX;
	Verts[1].y = endY;
	Verts[1].z = 1.f;
	Verts[1].rhw = 1.f;
	Verts[1].dwColour = dwColour;

	

	HRESULT iRet = m_pRenderPrim->Begin(D3DPT_LINELIST);
	if(SUCCEEDED(iRet))
	{
		m_pRenderPrim->D3DColour(dwColour);
		m_pRenderPrim->D3DVertex2f(startX,startY);
		m_pRenderPrim->D3DVertex2f(endX,endY);
		m_pRenderPrim->End();
	}
	
	return iRet;
}

HRESULT CRender::DrawFillRect(float x, float y, float width, float height, DWORD dwColour)
{
	const int VertexNum = 4;

	CVERTEX Verts[VertexNum];
	//===Original States===
	//=====================

	Verts[0].dwColour = Verts[1].dwColour = Verts[2].dwColour = Verts[3].dwColour = dwColour;
	Verts[0].z   = Verts[1].z   = Verts[2].z   = Verts[3].z   = 1.f;
	Verts[0].rhw = Verts[1].rhw = Verts[2].rhw = Verts[3].rhw = 1.f;

	Verts[0].x = x;
	Verts[0].y = (y + height);
	Verts[1].x = x;
	Verts[1].y = y;
	Verts[2].x = (x + width);
	Verts[2].y = (y + height);
	Verts[3].x = (x + width);
	Verts[3].y = y;

	

	HRESULT hRes = m_pRenderPrim->Begin(D3DPT_TRIANGLESTRIP);

	if(SUCCEEDED(hRes))
	{
		m_pRenderPrim->D3DColour(dwColour);
		for(int i = 0; i < 4;i++)
			m_pRenderPrim->D3DVertex2f(Verts[i].x,Verts[i].y);

		m_pRenderPrim->End();
	}
	return D3D_OK;
}
CVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{ 
	CVERTEX v = {
		X,Y,Z,RHW,color,U,V
	}; 
	return v;
}

HRESULT CRender::DrawCircle(int x, int y, float radius, DWORD dwColour)
{
	const DWORD D3D_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	const int NUMPOINTS = 24;
	const float PI = ( float )3.141592654f;
	CVERTEX Circle[NUMPOINTS + 1];
	float X, Y, Theta, WedgeAngle;
	WedgeAngle = (float)((2*PI) / NUMPOINTS);

	for(int i=0; i<=NUMPOINTS; i++)
	{
		Theta = i * WedgeAngle;
		X = (float)(x + radius * cos(Theta));
		Y = (float)(y - radius * sin(Theta));
		Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, dwColour, 0.0f, 0.0f);
	}

	m_pDevice->SetPixelShader(NULL);
	m_pDevice->SetVertexShader(NULL);  

	m_pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	m_pDevice->SetRenderState( D3DRS_FOGENABLE, false );
	m_pDevice->SetRenderState( D3DRS_LIGHTING, false );

	m_pDevice->SetFVF(D3D_FVF);
	m_pDevice->SetTexture(0, NULL);
	m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));

	return D3D_OK;
}  

void CRender::DrawBox(int x, int y, int w, int h, DWORD dwColour)
{
	//int offset = w / 2; // this will shift on x axis to center the box drawing 
	DrawLine(x, y, x+w, y, dwColour); // top 
	DrawLine(x, y+h, x+w+1, y+h, dwColour); // bottom 
	DrawLine(x, y, x, y+h, dwColour); // left 
	DrawLine(x+w, y, x+w, y+h, dwColour); // right
}

void CRender::DrawGradientBox( float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation )
{
	static struct D3DVERTEX
	{
		float x, y, z, rhw; DWORD color;
	}
	vertices[4] = {{0,0,0,1.0f,0},{0,0,0,1.0f,0},{0,0,0,1.0f,0},{0,0,0,1.0f,0}};
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].color = startCol;

	vertices[1].x = x+width;
	vertices[1].y = y;
	vertices[1].color = orientation == horizontal ? endCol : startCol;

	vertices[2].x = x;
	vertices[2].y = y+height;
	vertices[2].color = orientation == horizontal ? startCol : endCol;

	vertices[3].x = x+width;
	vertices[3].y = y+height;
	vertices[3].color = endCol;


	static LPDIRECT3DVERTEXBUFFER9 pVertexObject = NULL;
	static void *pVertexBuffer = NULL;

	DWORD dwTmpFVF;
	m_pDevice->GetFVF			( &dwTmpFVF );
	m_pDevice->SetTexture		( 0, NULL );
	m_pDevice->SetPixelShader	( 0 );

	if( !pVertexObject ) {
		if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(vertices), 0, 
			D3DFVF_XYZRHW|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVertexObject, NULL)))
			return;
	}
	if(FAILED(pVertexObject->Lock(0, sizeof(vertices), &pVertexBuffer, 0)))
		return;

	memcpy( pVertexBuffer, vertices, sizeof(vertices) );
	pVertexObject->Unlock();

	m_pDevice->SetStreamSource( 0, pVertexObject, 0, sizeof(D3DVERTEX) );
	m_pDevice->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

	if( dwTmpFVF )
		m_pDevice->SetFVF		( dwTmpFVF );
}


void CRender::DrawFillRectOut(float x, float y, float width, float height, DWORD dwOutCol,DWORD dwFillCol)
{
	DrawFillRect(x,y,width,height,dwFillCol);
	DrawOutline(x,y,width,height,dwOutCol);
	
}

void CRender::DrawHealthBar(int x, int y, float health, int w, int h, D3DCOLOR color1, D3DCOLOR color2)
{
	DrawFillRect(x,y,w+1,h,color2);
	UINT hw = (UINT)(((h-2)*health)/100);
	DrawFillRect(x+1,y+1,w-1,hw,color1);
	
}

void CRender::DrawString(int x, int y, DWORD dwColor,DWORD dwAlign, eFontSet Font, const char* szText, ...) 
{ 
	va_list va_alist;
	char logbuf[256] = {0};
	va_start (va_alist, szText);
	_vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf), szText, va_alist);
	va_end (va_alist);

	m_pFonts[Font]->DrawText(x,y,dwColor,logbuf,dwAlign); 
} 


void CRender::DrawBlackBorderString(int x, int y, DWORD dwColor,DWORD dwAlign, eFontSet Font, const char* szText, ...) 
{ 
	va_list va_alist;
	char logbuf[256] = {0};
	va_start (va_alist, szText);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf), szText, va_alist);
	va_end (va_alist);

	m_pFonts[Font]->DrawTextA(x + 1,y,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x - 1,y,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x,y + 1,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x,y - 1,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x + 1,y + 1,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x - 1,y - 1,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x + 1,y - 1,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x - 1,y + 1,COL_BLACK,logbuf,dwAlign);
	m_pFonts[Font]->DrawTextA(x,y,dwColor,logbuf,dwAlign); 
	
} 

void CRender::DrawSprite( float x, float y, LPDIRECT3DTEXTURE9 Texture, float Alpha /*= 255*/ )
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(Texture,0,0,&D3DXVECTOR3(x,y,0),D3DCOLOR_ARGB((int)Alpha,255,255,255));
	m_pSprite->End();
}
//===========Generate Functions==============================
HRESULT CRender::GenerateShader(IDirect3DPixelShader9 **pShader, float r, float g, float b )
{
	char szShader[ 256 ];
	ID3DXBuffer *pShaderBuf = NULL;
	sprintf( szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", r, g, b, 1.0f );
	D3DXAssembleShader( szShader, sizeof( szShader ), NULL, NULL, 0, &pShaderBuf, NULL );

	if( FAILED( m_pDevice->CreatePixelShader((const DWORD*)pShaderBuf->GetBufferPointer(), pShader)) )return E_FAIL;
	return S_OK;
}

HRESULT CRender::GenerateTexture(IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if( FAILED(m_pDevice->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)) )return E_FAIL;
	WORD colour16 =	((WORD)((colour32>>28)&0xF)<<12)
		|(WORD)(((colour32>>20)&0xF)<<8)
		|(WORD)(((colour32>>12)&0xF)<<4)
		|(WORD)(((colour32>>4)&0xF)<<0);
	D3DLOCKED_RECT d3dlr;    
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;
	for(int xy=0; xy < 8*8; xy++)*pDst16++ = colour16;
	(*ppD3Dtex)->UnlockRect(0);
	
	return S_OK;
}

int CRender::getLength( const char *szText, CD3DFont* Font )
{
	float len = 0.0f;

	for( const char *p=szText; *p; p++ )
	{
		char c = ( *p )-32;
		if( c >= 0 && c < 96 )
			len += ( ( Font->m_fTexCoords[c][2]-Font->m_fTexCoords[c][0] ) * 256 ) - Font->m_dwSpacing * 2;
	}

	return len;
}
//=============================================