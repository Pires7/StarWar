#ifndef _STARWAR_ZERGTELEPORT_H_
#define _STARWAR_ZERGTELEPORT_H_

#include "GameNode.h"

class CZergTeleport : public CGameNode
{
protected:
	float m_width;
	float m_height;
	float m_depth;	
	float m_rotationSpeed;
	LPD3DXMESH m_pMesh; 
	D3DMATERIAL9 m_pMeshMaterials; 
	unsigned long m_materialsNum; //Number of material
	int m_generationCounter;
	static const int GENERATION_FRAME_PERIOD = 100;

public:
	CZergTeleport(float width, float height, float depth, float rotationSpeed);
	
	void Update();
	bool InitVertices();
	bool InitColliders();
	void Render(LPDIRECT3DDEVICE9 pd3dDevice);
	void CollidingCallback(CGameNode *collided);
	void CollidedCallback(CGameNode *colliding);
};

#endif
