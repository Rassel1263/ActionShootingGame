#include "Header.h"

void Camera::Init()
{
	D3DXVECTOR3 vEyePt = { 0.0f, 0.0f, -10.0f };
	D3DXVECTOR3 vLookatPt = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 vUpVec = { 0.0f, 1.0f, 0.0f };
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixOrthoLH(&matProj, Game::GetInstance().screenWidth / 4, Game::GetInstance().screenHeight / 4, 0.01f, 10000.0f);
	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::Update(float deltaTime)
{
	D3DXVec2Lerp(&cameraPos, &cameraPos, &destCameraPos, 0.1f);
	D3DXVec2Lerp(&cameraScale, &cameraScale, &destCameraScale, 0.1f);
	D3DXVec2Lerp(&cameraQuaken, &cameraQuaken, &destCameraQuaken, 0.1f);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, cameraScale.x, cameraScale.y, 1.0f);
	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, ((rand() % 2 ? 1 : -1) * cameraQuaken.x) - cameraPos.x, ((rand() % 2 ? 1 : -1) * cameraQuaken.y) - cameraPos.y, 0.0f);

	matWorld = matScale * matPos;
	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}
