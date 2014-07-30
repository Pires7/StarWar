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

extern D3DXVECTOR3 g_vEye;    // Eye Position

CCamera::CCamera(CGameNode *target, const D3DXVECTOR3 &position)
{	
	this->m_target = target;
	m_offsetPosition = D3DXVECTOR3(position);    
}

void CCamera::LateUpdate()
{
	g_vEye = m_target->GetPosition() + m_offsetPosition;
}