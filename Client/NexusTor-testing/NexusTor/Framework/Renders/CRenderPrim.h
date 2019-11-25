#ifndef _D3DRENDER_H
#define _D3DRENDER_H
#include <d3dx9.h>

class CD3DRender;

//FVF Macros
#define D3DFVF_PRIMITIVES	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//Vertex Types
struct d3dfont_s { float x,y,z,rhw; DWORD colour; float tu,tv; };
typedef struct { float x,y,z,rhw; DWORD colour; } d3dprimitives_s;

//Initialization Macros
#undef SAFE_RELEASE
#define SAFE_RELEASE(d) if(d) { d->Release(); d=NULL; }

//Helper Functions
HRESULT D3DAddQuad(CD3DRender *pRender, float x, float y, float w, float h, DWORD colour);

class CD3DBaseRender
{
public:
	CD3DBaseRender();
	~CD3DBaseRender();

	static HRESULT BeginRender();
	static HRESULT EndRender();

protected:
	static HRESULT Initialize(IDirect3DDevice9 *pD3Ddev);
	static HRESULT Invalidate();

	static HRESULT CreateStates();
	static HRESULT DeleteStates();

	static IDirect3DDevice9		*m_pD3Ddev;
	static IDirect3DStateBlock9	*m_pD3DstateDraw;
	static IDirect3DStateBlock9	*m_pD3DstateNorm;

	static int	m_renderCount;
	static int	m_numShared;
	static bool m_statesOK;
};

class CD3DRender : public CD3DBaseRender
{
public:
	CD3DRender(int numVertices);
	~CD3DRender();

	HRESULT Initialize(IDirect3DDevice9 *pD3Ddev);
	HRESULT Invalidate();

	HRESULT Begin(D3DPRIMITIVETYPE primType);
	HRESULT End();

	inline HRESULT D3DColour(DWORD colour);
	inline HRESULT D3DVertex2f(float x, float y);
	
private:
	D3DPRIMITIVETYPE		m_primType;
	IDirect3DVertexBuffer9	*m_pD3Dbuf;
	d3dprimitives_s			*m_pVertex;

	DWORD					m_colour;
	int						m_maxVertex;
	int						m_curVertex;

	bool					m_canRender;
};

#endif