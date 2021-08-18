#include "DXUT.h"
#include "Game.h"

Scene* nowScene = NULL;

Game::~Game()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pLine);
}

void Game::Init()
{
	ChangeScene(new GameScene());

	DXUTGetD3D9Device()->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, 0);
	D3DXCreateLine(DXUTGetD3D9Device(), &pLine);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


	srand(time(NULL));

	Input::GetInstance().Start();
	Camera::GetInstance().Init();
}

void Game::Update(float deltaTime)
{
	Input::GetInstance().Update();

	if (nextScene)
	{
		nowScene = nextScene;
		nowScene->Init();
		nextScene = NULL;
	}

	Camera::GetInstance().Update(deltaTime);

	if (nowScene)
		nowScene->Update(deltaTime * timeScale);

	unscaleTime = deltaTime;
}

void Game::Render()
{
	if (nowScene)
		nowScene->Render();
}

void Game::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color, float width)
{
	pLine->SetWidth(width);
	pLine->Begin();
	D3DXVECTOR3 v[] = { D3DXVECTOR3(p1.x, 20.0f, p1.y), D3DXVECTOR3(p2.x, 20.0f, p2.y) };
	D3DXMATRIX retMat = matrix * Camera::GetInstance().matWorld * Camera::GetInstance().matView * Camera::GetInstance().matProj;
	pLine->DrawTransform(v, 2, &retMat, color);
	pLine->End();
}

void Game::Check()
{
#ifdef _DEBUG
	screenHeight = 1040;
#endif
}

void Game::ChangeScene(Scene* nextScene)
{
	this->nextScene = nextScene;
}

D3DXVECTOR2 Game::ScreenSize()
{
	return D3DXVECTOR2(screenWidth / 2, screenHeight / 2);
}
