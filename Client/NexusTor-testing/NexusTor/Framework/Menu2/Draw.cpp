#include "Draw.h"
#include "Colours.h"
#include "VarSystem.h"

CDraw cDraw;

#define COL_FRIEND		D3DCOLOR_XRGB( (int)SColors::fChamsFriendR, (int)SColors::fChamsFriendG,(int)SColors::fChamsFriendB )
#define COL_FRIEND_VIS	D3DCOLOR_XRGB( (int)SColors::fChamsFriendVisR, (int)SColors::fChamsFriendVisG,(int)SColors::fChamsFriendVisB )
#define COL_ENEMY		D3DCOLOR_XRGB( (int)SColors::fChamsEnemyR, (int)SColors::fChamsEnemyG,(int)SColors::fChamsEnemyB )
#define COL_ENEMY_VIS	D3DCOLOR_XRGB( (int)SColors::fChamsEnemyVisR, (int)SColors::fChamsEnemyVisG,(int)SColors::fChamsEnemyVisB )

// void CDraw::InitChamsCol(  )
// {
// 	GenerateShader( &Shaders.sEnemy			, SColors::fChamsEnemyR		, SColors::fChamsEnemyG		, SColors::fChamsEnemyB		);
// 	GenerateShader( &Shaders.sEnemyVis		, SColors::fChamsEnemyVisR	, SColors::fChamsEnemyVisG	, SColors::fChamsEnemyVisB	);
// 	GenerateShader( &Shaders.sFriend		, SColors::fChamsFriendR	, SColors::fChamsFriendG	, SColors::fChamsFriendB	);
// 	GenerateShader( &Shaders.sFriendVis		, SColors::fChamsFriendVisR	, SColors::fChamsFriendVisG	, SColors::fChamsFriendVisB	);
// 
// 	GenerateTexture( &Textures.tEnemy		, D3DCOLOR_XRGB( (int)SColors::fChamsEnemyR, (int)SColors::fChamsEnemyG,(int)SColors::fChamsEnemyB				) );
// 	GenerateTexture( &Textures.tEnemyVis	, D3DCOLOR_XRGB( (int)SColors::fChamsEnemyVisR, (int)SColors::fChamsEnemyVisG,(int)SColors::fChamsEnemyVisB		) );
// 	GenerateTexture( &Textures.tFriend		, D3DCOLOR_XRGB( (int)SColors::fChamsFriendR, (int)SColors::fChamsFriendG,(int)SColors::fChamsFriendB			) );
// 	GenerateTexture( &Textures.tFriendVis	, D3DCOLOR_XRGB( (int)SColors::fChamsFriendVisR, (int)SColors::fChamsFriendVisG,(int)SColors::fChamsFriendVisB	) );
// }

bool CDraw::InitializeD3D ( LPDIRECT3DDEVICE9 pD3Ddevice )
{
	if( !pD3Ddevice )return false; //Check if pD3Ddevice is valid

	pDevice = pD3Ddevice; //Set the "real" device

	D3DXCreateSprite( pDevice, &m_pSprite );
	if( !m_pSprite )return false; 
	pDevice->GetViewport( &ViewPort );

	Fonts[0] = new CD3DFont	( "Agency FB Fett"	, 12 );
	Fonts[1] = new CD3DFont	( "Browallia"		, 8  );
	Fonts[2] = new CD3DFont	( "Calibri Bold"	, 12 );
	Fonts[3] = new CD3DFont	( "Consolas Bold"	, 12 );
	Fonts[4] = new CD3DFont	( "Comic Sans MS"	, 24  );
	Fonts[5] = new CD3DFont	( "DokChampa"		, 12 );
	Fonts[6] = new CD3DFont	( "Arial"			, 25 );

	GenerateShader( &Shaders.sEnemy			, 255, 255	, 0		);
	GenerateShader( &Shaders.sEnemyVis		, 255, 0	, 0		);

	GenerateShader( &Shaders.sFriend		, 0	 , 255	, 0		);
	GenerateShader( &Shaders.sFriendVis		, 36 , 239	, 255	);

	GenerateTexture( &Textures.tEnemy		, D3DCOLOR_XRGB( 255, 255,0		) );
	GenerateTexture( &Textures.tEnemyVis	, D3DCOLOR_XRGB( 255, 0,0		) );

	GenerateTexture( &Textures.tFriend		, D3DCOLOR_XRGB( 0, 255,0		) );
	GenerateTexture( &Textures.tFriendVis	, D3DCOLOR_XRGB( 36, 239,255	) );

	for ( int i = 0; i < 7; i++ )
	{
		if( Fonts[ i ] )
		{
			Fonts[ i ]->InitDeviceObjects( pDevice );
			Fonts[ i ]->RestoreDeviceObjects(  );
		}
	}
	return true;
}
void CDraw::DrawShape( long x, long y, float fDegrees, DWORD dwSides, DWORD dwSize, D3DCOLOR Color )
{
	POINT* pt = new POINT[ dwSides + 1 ];

	fDegrees = ( fDegrees * PI ) / 180.0f;

	float k = 0.000000f;

	for( int i = 0; i < dwSides; i++, k += ( TWO_PI/dwSides ) )
	{
		float fDeg = k + fDegrees; 

		while( fDeg > TWO_PI )
			fDeg -= TWO_PI; 

		pt[ i ].x = ( cos( fDeg ) * dwSize ) + x; 
		pt[ i ].y = ( sin( fDeg ) * dwSize ) + y;
	}

	pt[ dwSides ].x = pt[ 0 ].x; 
	pt[ dwSides ].y = pt[ 0 ].y;

	for( int i = 0; i < dwSides; i++ )
		DrawLine( pt[ i ].x, pt[ i ].y, pt[ i + 1 ].x, pt[ i + 1 ].y, Color );

	delete[] pt;
}
void CDraw::AddRadioButton( float X, float Y, char* Name )
{
	for ( int i = 0; i < 6; i++ )
	{
		cDraw.DrawShape( X, Y, 1, 60,i, cCol.colBlack );
		cDraw.DrawShape( X, Y, 1, 60,7, cCol.colGray );
	}
	for( int i = 0; i < 4; i++ )
	{
		int r = i*63.75;
		cDraw.DrawShape( X, Y, 1, 60, i, D3DCOLOR_ARGB( 240, r,r,r ) );
	}
	cDraw.DrawString( cDraw.Fonts[1], X + 10, Y - 7, cCol.colWhite, D3DFONT_ZENABLE, "%s",Name );
}
void CDraw::AddRadioButtonActivated( float X, float Y, char* Name )
{
	for ( int i = 0; i < 6; i++ )
	{
		cDraw.DrawShape( X, Y, 1, 60,i, cCol.colBlack );
		cDraw.DrawShape( X, Y, 1, 60,7, cCol.colGray );
	}
	for( int i = 0; i < 4; i++ )
	{
		int r = i*63.75;
		cDraw.DrawShape( X, Y, 1, 60, i, D3DCOLOR_ARGB( 240, 10,r,10 ) );
	}
	cDraw.DrawString( cDraw.Fonts[1], X + 10, Y - 7, cCol.colWhite, D3DFONT_ZENABLE, "%s",Name );
}
void CDraw::AddRadioButtonDeactivated( float X, float Y, char* Name )
{
	for ( int i = 0; i < 6; i++ )
	{
		cDraw.DrawShape( X, Y, 1, 60,i, cCol.colBlack );
		cDraw.DrawShape( X, Y, 1, 60,7, cCol.colGray );
	}
	for( int i = 0; i < 4; i++ )
	{
		int r = i*63.75;
		cDraw.DrawShape( X, Y, 1, 60, i, D3DCOLOR_ARGB( 240, r,10,10 ) );
	}
	cDraw.DrawString( cDraw.Fonts[1], X + 10, Y - 7, cCol.colWhite, D3DFONT_ZENABLE, "%s",Name );
}
void CDraw::AddCheckBoxNormal( float X, float Y, char* Name )
{
	cDraw.DrawFillRectOut( X,Y,12,12,cCol.colGray, cCol.colBlack );
	for ( int i = 0; i < 10; i++ )
	{
		int r = i*25.5;
		cDraw.DrawFillRect( X + 2, Y + 1 + i, 9, 1, D3DCOLOR_ARGB( 240, r,r,r ) );
	}
	cDraw.DrawString( cDraw.Fonts[1], X + 15, Y + 2 , cCol.colWhite,D3DFONT_ZENABLE,"%s", Name );
}
void CDraw::AddCheckBoxActivated( float X, float Y, char* Name )
{
	cDraw.DrawFillRectOut( X,Y,12,12,cCol.colGray, cCol.colBlack );
	for ( int i = 0; i < 10; i++ )
	{
		int r = i*25.5;
		cDraw.DrawFillRect( X + 2, Y + 1 + i, 9, 1, D3DCOLOR_ARGB( 240, 10,r,10 ) );
	}
	cDraw.DrawString( cDraw.Fonts[1], X + 15, Y + 2 , cCol.colWhite,D3DFONT_ZENABLE,"%s", Name );
}
void CDraw::AddCheckBoxDeactivated( float X, float Y, char* Name )
{
	cDraw.DrawFillRectOut( X,Y,12,12,cCol.colGray, cCol.colBlack );
	for ( int i = 0; i < 10; i++ )
	{
		int r = i*25.5;
		cDraw.DrawFillRect( X + 2, Y + 1 + i, 9, 1, D3DCOLOR_ARGB( 240, r,10,10 ) );
	}
	cDraw.DrawString( cDraw.Fonts[1], X + 15, Y + 2 , cCol.colWhite,D3DFONT_ZENABLE,"%s", Name );
}
void CDraw::DrawBox ( int x, int y, int w, int h, int choose )
{
	if( choose == 1 )
	{
		cDraw.DrawFillRect( x		, y		, w		, 1		, cCol.colBlack );
		cDraw.DrawFillRect( x		, y		, 1		, h		, cCol.colBlack );
		cDraw.DrawFillRect( x + w	, y		, 1		, h		, cCol.colWhite );
		cDraw.DrawFillRect( x		, y + h	, w + 1	, 1		, cCol.colWhite );
	}
	else
	{
		cDraw.DrawFillRect( x		, y		, w		, 1		, cCol.colWhite );
		cDraw.DrawFillRect( x		, y		, 1		, h		, cCol.colWhite );
		cDraw.DrawFillRect( x + w	, y		, 1		, h		, cCol.colBlack );
		cDraw.DrawFillRect( x		, y + h	, w + 1	, 1		, cCol.colBlack );
	}
}
HRESULT CDraw::DrawOutline( float x, float y, float width, float height, DWORD dwColour )
{
	const int VertexNum = 5;
	DWORD dwOrigfvf;
	CVERTEX Verts[ VertexNum ];

	Verts[ 0 ].x = x;
	Verts[ 0 ].y = y;
	Verts[ 0 ].z = 0.0f;
	Verts[ 0 ].rhw = 0.0f;
	Verts[ 0 ].dwColour = dwColour;

	Verts[ 1 ].x = x + width;
	Verts[ 1 ].y = y;
	Verts[ 1 ].z = 0.0f;
	Verts[ 1 ].rhw = 0.0f;
	Verts[ 1 ].dwColour = dwColour;

	Verts[ 2 ].x = x + width;
	Verts[ 2 ].y = y + height;
	Verts[ 2 ].z = 0.0f;
	Verts[ 2 ].rhw = 0.0f;
	Verts[ 2 ].dwColour = dwColour;

	Verts[ 3 ].x = x;
	Verts[ 3 ].y = y + height;
	Verts[ 3 ].z = 0.0f;
	Verts[ 3 ].rhw = 0.0f;
	Verts[ 3 ].dwColour = dwColour;

	Verts[ 4 ].x = x;
	Verts[ 4 ].y = y;
	Verts[ 4 ].z = 0.0f;
	Verts[ 4 ].rhw = 0.0f;
	Verts[ 4 ].dwColour = dwColour;

	HRESULT iRet = D3D_OK;

	pDevice->GetTexture( 0, &pTex );
	pDevice->GetFVF( &dwOrigfvf );
	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	iRet = pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, 4, &Verts, sizeof( CVERTEX ) );

	if( pTex )pDevice->SetTexture( 0, pTex );
	if( dwOrigfvf )pDevice->SetFVF( dwOrigfvf );
	return iRet;
}
HRESULT CDraw::DrawLine( float startX, float startY, float endX, float endY, DWORD dwColour )
{
	const int VertexNum = 3;
	DWORD dwOriginalFVF, dwAlias;
	CVERTEX Verts[ VertexNum ];

	Verts[ 0 ].x = startX;
	Verts[ 0 ].y = startY;
	Verts[ 0 ].z = 0.0f;
	Verts[ 0 ].rhw = 0.0f;
	Verts[ 0 ].dwColour = dwColour;

	Verts[ 1 ].x = endX;
	Verts[ 1 ].y = endY;
	Verts[ 1 ].z = 0.0f;
	Verts[ 1 ].rhw = 0.0f;
	Verts[ 1 ].dwColour = dwColour;

	HRESULT iRet = D3D_OK;

	pDevice->GetTexture( 0, &pTex );
	pDevice->GetFVF( &dwOriginalFVF );
	pDevice->GetRenderState( D3DRS_ANTIALIASEDLINEENABLE, &dwAlias );
	pDevice->SetTexture( 0, NULL );
	pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, true );
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

	iRet = pDevice->DrawPrimitiveUP( D3DPT_LINELIST, VertexNum, &Verts, sizeof( CVERTEX ) );

	if( pTex )pDevice->SetTexture( 0, pTex );
	if( dwAlias )pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, dwAlias );
	if( dwOriginalFVF )pDevice->SetFVF( dwOriginalFVF );
	return iRet;
}
HRESULT CDraw::DrawFillRect( float x, float y, float width, float height, DWORD dwColour )
{
	const int VertexNum = 4;
	DWORD dwOrigfvf;
	CVERTEX Verts[ VertexNum ];

	Verts[ 0 ].dwColour	= Verts[ 1 ].dwColour	= Verts[ 2 ].dwColour	= Verts[ 3 ].dwColour	= dwColour;
	Verts[ 0 ].z		= Verts[ 1 ].z			= Verts[ 2 ].z			= Verts[ 3 ].z			= 0.0f;
	Verts[ 0 ].rhw		= Verts[ 1 ].rhw		= Verts[ 2 ].rhw		= Verts[ 3 ].rhw		= 0.0f;

	Verts[ 0 ].x = x;
	Verts[ 0 ].y = y + height;
	Verts[ 1 ].x = x;
	Verts[ 1 ].y = y;
	Verts[ 2 ].x = x + width;
	Verts[ 2 ].y = y + height;
	Verts[ 3 ].x = x + width;
	Verts[ 3 ].y = y;

	HRESULT iRet = D3D_OK;

	pDevice->GetTexture( 0, &pTex );
	pDevice->GetFVF( &dwOrigfvf );
	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	iRet = pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, Verts, sizeof( CVERTEX ) );

	if( pTex )pDevice->SetTexture( 0, pTex );
	if( dwOrigfvf )pDevice->SetFVF( dwOrigfvf );
	return iRet;
}
void CDraw::DrawFillRectOut( float x, float y, float width, float height, DWORD dwOutCol, DWORD dwFillCol )
{
	DrawFillRect( x, y, width, height, dwFillCol);
	DrawOutline	( x, y, width, height, dwOutCol	);
}
void CDraw::DrawHealthbar( int choose, int x, int y, float health, int w, int h, D3DCOLOR ColOut, D3DCOLOR ColHealth )
{
	if ( choose == 1 )
	{
		DrawFillRect( x, y, w, h, ColOut );
		UINT ConvertedHealth = ( UINT )( ( ( w - 1 ) *health )/100 );
		if( ConvertedHealth < 1 ) ConvertedHealth = 1;
		if( ConvertedHealth > 100 ) ConvertedHealth = w - 1;
		DrawFillRect( x + 1, y + 1, ConvertedHealth - 1, h - 2, ColHealth );
	}
	else if ( choose == 2 )
	{
		DrawFillRect( x, y, w, h, ColOut );
		UINT ConvertedHealth2 = ( UINT )( ( ( h - 1 ) *health )/100 );
		if( ConvertedHealth2 < 1 ) ConvertedHealth2 = 1;
		if( ConvertedHealth2 > y + h - 1)ConvertedHealth2 = h - 1;
		DrawFillRect( x + 1, y + 1, w - 1, ConvertedHealth2, ColHealth );
	}
}
void CDraw::AddButton( float X, float Y, float W, char* Name )
{
	cDraw.DrawFillRectOut( X, Y, W, 20,cCol.colGray, cCol.colBlack );
	for ( int i = 0; i < 17; i++ )
	{
		int r =  i*15;
		cDraw.DrawFillRect( X + 2, Y + 2 + i, W - 3, 1, D3DCOLOR_ARGB( 240, r,r,r ) );
	}
	cDraw.DrawBorderString( cDraw.Fonts[1], X + W/2, Y + 3, cCol.colGray,cCol.colBlack,D3DFONT_CENTERED, "%s",Name  );
}
void CDraw::AddButtonActivated( float X, float Y, float W, char* Name )
{
	cDraw.DrawFillRectOut( X, Y, W, 20,cCol.colGray, cCol.colBlack );
	for ( int i = 0; i < 17; i++ )
	{
		int r =  i*15;
		cDraw.DrawFillRect( X + 2, Y + 2 + i, W - 3, 1, D3DCOLOR_ARGB( 240, 10,r,10 ) );
	}
	cDraw.DrawBorderString( cDraw.Fonts[1], X + W/2, Y + 3, cCol.colGray,cCol.colBlack,D3DFONT_CENTERED, "%s",Name  );
}
void CDraw::AddButtonDeactivated( float X, float Y, float W, char* Name )
{
	cDraw.DrawFillRectOut( X, Y, W, 20,cCol.colGray, cCol.colBlack );
	for ( int i = 0; i < 17; i++ )
	{
		int r =  i*15;
		cDraw.DrawFillRect( X + 2, Y + 2 + i, W - 3, 1, D3DCOLOR_ARGB( 240, r,10,10 ) );
	}
	cDraw.DrawBorderString( cDraw.Fonts[1], X + W/2, Y + 3, cCol.colGray,cCol.colBlack,D3DFONT_CENTERED, "%s",Name  );
}
void CDraw::DrawCrosshair( int x, int y, int Size, int linethick, bool Bordered, DWORD Color )
{
	if( !Bordered )
	{
		cDraw.DrawLine( x - Size/2, y, x + Size/2, y, Color);
		cDraw.DrawLine( x, y - Size/2, x, y + Size/2, Color);
	}
	else
	{
		cDraw.DrawFillRect( x - Size/2 - 2, y - linethick/2 - 2, Size + 4, linethick + 4, cCol.colBlack );// - Border
		cDraw.DrawFillRect( x - linethick/2 - 2, y - Size/2 - 2, linethick + 4, Size + 4, cCol.colBlack );// | Border
		cDraw.DrawFillRect( x - Size/2, y - linethick/2, Size, linethick, Color );// -
		cDraw.DrawFillRect( x - linethick/2, y - Size/2, linethick, Size, Color );// |
	}
}
void CDraw::DrawCross ( float PositionX, float PositionY, float Size, D3DCOLOR col )
{
	cDraw.DrawLine( PositionX - Size/2, PositionY, PositionX + Size/2, PositionY, col);
	cDraw.DrawLine( PositionX, PositionY - Size/2, PositionX, PositionY + Size/2, col);
}
void CDraw::Box ( float PosX, float PosY, float h, float w, float Space,float CornerLineLength, DWORD CornerLineW, DWORD LineW, DWORD ColCorners, DWORD ColLines )
{
	DrawFillRect(PosX,PosY,CornerLineLength,CornerLineW,ColCorners);
	DrawFillRect(PosX,PosY,CornerLineW,CornerLineLength,ColCorners);
	DrawFillRect(PosX + w - CornerLineLength,PosY,CornerLineLength,CornerLineW,ColCorners);
	DrawFillRect(PosX + w -1,PosY,CornerLineW,CornerLineLength,ColCorners);
	DrawFillRect(PosX,PosY + h - CornerLineLength,CornerLineW,CornerLineLength,ColCorners);
	DrawFillRect(PosX,PosY + h,  CornerLineLength,CornerLineW,ColCorners);
	DrawFillRect(PosX + w - CornerLineLength,PosY + h,CornerLineLength,CornerLineW,ColCorners);
	DrawFillRect(PosX + w - 2, PosY +h - CornerLineLength,CornerLineW,CornerLineLength,ColCorners);
	DrawLine( PosX + CornerLineLength + Space, PosY, PosX + w - ( CornerLineLength + Space ), PosY, ColLines); 
	DrawLine( PosX + CornerLineLength + Space, PosY + h, PosX + w - CornerLineLength - Space , PosY + h, ColLines ); 
	DrawLine( PosX, PosY + CornerLineLength + Space, PosX, PosY + h - CornerLineLength - Space , ColLines ); 
	DrawLine( PosX + w, PosY + CornerLineLength + Space, PosX + w, PosY + h - ( CornerLineLength + Space ), ColLines ); 
}
void CDraw::DrawString(CD3DFont* pFont,int x, int y, DWORD dwColor,DWORD dwAlign,const char* szText, ...) 
{ 
	va_list va_alist;
	char logbuf[256] = {0};
	va_start (va_alist, szText);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), szText, va_alist);
	va_end (va_alist);

	pFont->DrawTextA(x,y,dwColor,logbuf,dwAlign); 
} 
void CDraw::DrawBorderString(CD3DFont* pFont,int x, int y, DWORD dwColor,DWORD dwBorderColor, DWORD dwAlign,const char* szText, ...) 
{ 
	va_list va_alist;
	char logbuf[256] = {0};
	va_start (va_alist, szText);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), szText, va_alist);
	va_end (va_alist);

	pFont->DrawTextA(x + 1,y,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x - 1,y,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x,y + 1,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x,y - 1,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x + 1,y + 1,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x - 1,y - 1,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x + 1,y - 1,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x - 1,y + 1,dwBorderColor,logbuf,dwAlign);
	pFont->DrawTextA(x,y,dwColor,logbuf,dwAlign); 
}
void CDraw::DrawSprite( LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 vPosition )
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(pTexture,0,0,&D3DXVECTOR3(vPosition.x,vPosition.y,0),0xFFFFFFFF);
	m_pSprite->End();
}
HRESULT CDraw::GenerateShader( IDirect3DPixelShader9 **pShader, float r, float g, float b )
{
	r = r / 255;
	g = g / 255;
	b = b / 255;

	char szShader[ 256 ];
	ID3DXBuffer *pShaderBuf = NULL;
	sprintf( szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", r, g, b, 1.0f );
	D3DXAssembleShader( szShader, sizeof( szShader ), NULL, NULL, 0, &pShaderBuf, NULL );
	if( FAILED( pDevice->CreatePixelShader( ( const DWORD* )pShaderBuf->GetBufferPointer(  ), pShader ) ) )return E_FAIL;
	return S_OK;
}

HRESULT CDraw::GenerateTexture( IDirect3DTexture9 **ppD3Dtex, DWORD colour32 )
{
	if( FAILED( pDevice->CreateTexture( 8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL ) ) )return E_FAIL;
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
