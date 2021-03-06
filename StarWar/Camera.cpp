//------------------------------------------------------------------------------
//           Name: Camera.cpp
//         Author: Dai Zhuofang
//    Description: Camera controller
//                 
//   Control Keys: W          - View moves forward
//                 S          - View moves backward
//                 A          - View strafes left
//                 D          - View strafes Right
//                 Left Mouse - Perform looking
//                 Mouse      - Look about the scene
//------------------------------------------------------------------------------

#include "Camera.h"

CCamera::CCamera(CGameNode *target, D3DXVECTOR3 &position)
{	
	this->m_target = target;
	m_offsetPosition = position;    
}

void CCamera::SwitchTarget(CGameNode *target)
{	
	this->m_target = target;    
}

void CCamera::UpdateViewMatrix()
{
	D3DXMATRIX view;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 up(0,0,1);

	D3DXMATRIX matrixRotationX, matrixRotationY, matrixRotationZ, matrixRotation;

	D3DXVECTOR3 m_look = D3DXVECTOR3(0, 0, 1); 
	D3DXVECTOR3 m_right = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 m_up = D3DXVECTOR3(0, 1, 0);

	//D3DXVECTOR3 rotation = m_target->GetTransform()->GetWorldRotation();	
	//D3DXMatrixRotationYawPitchRoll(&matrixRotation, rotation.y , rotation.x, rotation.z);

	D3DXQUATERNION quaternion = m_target->GetTransform()->GetWorldRotation();
	D3DXMatrixRotationQuaternion(&matrixRotation, &quaternion);

	D3DXVECTOR3 m_offsetPosition1 = m_offsetPosition;   
	D3DXVec3Normalize( &m_offsetPosition1, &m_offsetPosition1 );	
	
	//D3DXVec3TransformCoord(&m_look, &m_look, &matrixRotation);
	//D3DXVec3TransformCoord(&m_right, &m_right, &matrixRotation);
	D3DXVec3TransformCoord(&m_offsetPosition1, &m_offsetPosition1, &matrixRotation);
	D3DXVec3TransformCoord(&m_up, &m_up, &matrixRotation);

	D3DXVec3Normalize( &m_offsetPosition1, &m_offsetPosition1 );

	eye = m_target->GetTransform()->GetWorldPosition() + m_offsetPosition1 * 50;
	Util::Clip(0, 2048, eye.y);
	m_position = eye;
	D3DXMatrixLookAtLH(&view, &eye, &m_target->GetTransform()->GetWorldPosition(), &m_up);

	LPDIRECT3DDEVICE9 pd3dDevice = CDXEngine::Instance()->GetDxDevice();
	pd3dDevice->SetTransform( D3DTS_VIEW, &view ); 
}

void CCamera::LateUpdate()
{
	UpdateViewMatrix();
}