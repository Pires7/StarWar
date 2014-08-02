#ifndef _STARWAR_PLAYER_H_
#define _STARWAR_PLAYER_H_

#include "GameNode.h"

class CPlayer : public CGameNode
{
protected:
	LPD3DXMESH m_pMesh; 
	D3DMATERIAL9 m_pMeshMaterials; 
	unsigned long m_materialsNum; //Number of material

public:
	CPlayer();
	void Update();
	void Render(LPDIRECT3DDEVICE9 pd3dDevice);
	bool InitVertices();
	bool InitColliders();
	void CollidingCallback(CGameNode *collided);
	void CollidedCallback(CGameNode *colliding);
};

#endif

