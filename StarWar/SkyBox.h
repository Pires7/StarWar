#ifndef _STARWAR_SKYBOX_H_
#define _STARWAR_SKYBOX_H_

#include "GameNode.h"
#include "Camera.h"

//Define SkyBoxVertex
typedef PositionNormalDiffUseColorTexVertex SkyBoxVertex;

class CSkyBox : public CGameNode
{
public:
	//Total sides of skybox
	static const int TOTAL_SIDES = 6;
	//Number of vertices per side
	static const int VERTICES_PER_SIDE = 4;
	//Total vertices of skybox, 6 * 4
	static const int TOTAL_VERTICES = 24;
	//Enum variable of each side. Introduced for readability
	enum TSides {FRONT, BACK, LEFT, RIGHT, CEILING, FLOOR};

protected:
	//Texture point array of each side
	LPDIRECT3DTEXTURE9 m_pTextureArray[TOTAL_SIDES];
	//Vertices array of skybox
	SkyBoxVertex *m_pVertexArray;
	//Vertices buffer
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	//Point to mesh material
	D3DMATERIAL9 m_pMeshMaterials; 

	CCamera *m_pCamera;

public:
	//Constructor.
	CSkyBox();
	//Deconstructor.
	~CSkyBox();
	//Draw the skybox.
	void Update();
	void Render(LPDIRECT3DDEVICE9 pd3dDevice);
	//Create vertex buffer.
	bool InitVertices();
	bool InitColliders(){return true;};
	void CollidingCallback(CGameNode *collided){};
	void CollidedCallback(CGameNode *colliding){};
	void SetCamera(CCamera *pCamera){m_pCamera = pCamera;};
};

#endif