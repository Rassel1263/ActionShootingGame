#include "DXUT.h"
#include "Game.h"

Game::~Game()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pSprite);
	SAFE_RELEASE(pLine);
}

void Game::Init()
{
	DXUTGetD3D9Device()->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, 0);
	D3DXCreateLine(DXUTGetD3D9Device(), &pLine);
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHAREF, (unsigned int)0x00000001);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_CLAMP);

	srand(time(NULL));
}

void Game::Update(float deltaTime)
{
}

void Game::Render()
{
}

void Game::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color, float width)
{
}

void Game::Check()
{
#ifdef _DEBUG
	screenHeight = 1040;
#endif
}

D3DXVECTOR2 Game::ScreenSize()
{
	return D3DXVECTOR2(screenWidth / 2, screenHeight / 2);
}
