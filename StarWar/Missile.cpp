#include "Missile.h"

CMissile::CMissile(float radius1, float radius2, float length, float moveSpeed, CGameNode *target) : 
		m_radius1(radius1), m_radius2(radius2), m_length(length), CTargetedBullet(target)
{
	m_type = MISSILE; 	
	m_moveSpeed = moveSpeed;
	m_enableControl = false;
	m_enablePhysics = true;
	m_enableRender = true;
	m_isControlable = true; 
	m_isFlyable = true;
	m_destroyCounter = 0; 
}

CMissile::~CMissile()
{
	delete m_pMesh;
}

void CMissile::SetAlive()
{
	m_isAlive = true; 
	m_destroyCounter = 0; 
	m_enableControl = false;
	m_enablePhysics = true;
	m_enableRender = true;
	m_isControlable = true; 
	m_isFlyable = true;
}

void CMissile::Render(LPDIRECT3DDEVICE9 pd3dDevice)
{	
	if(m_enableRender)
	{
		pd3dDevice->SetTransform(D3DTS_WORLD, &m_transform.GetWorldMatrix());	
		pd3dDevice->SetMaterial(&m_meshMaterials);
		m_pMesh->DrawSubset(0);
	}
}

void CMissile::Update()
{
	if(!m_enableControl && m_isAlive)
	{
		if(m_destroyCounter < DESTROY_FRAME_PERIOD)
		{
			++m_destroyCounter;
		}
		else
		{
			Recycle();
			m_destroyCounter = 0;
		}
		MoveToTarget();
	}
}
	
bool CMissile::InitVertices()
{
	LPDIRECT3DDEVICE9 pd3dDevice = CDXEngine::Instance()->GetDxDevice();

	D3DXCreateCylinder(pd3dDevice, m_radius1, m_radius2, m_length, 10, 10, &m_pMesh, NULL);
	ZeroMemory(&m_meshMaterials, sizeof(D3DMATERIAL9));
	m_meshMaterials.Diffuse.r = 0;
	m_meshMaterials.Diffuse.g = 0;
	m_meshMaterials.Diffuse.b = 0;
	m_meshMaterials.Diffuse.a = 0.8;
	m_meshMaterials.Ambient.r = 0;
	m_meshMaterials.Ambient.g = 0;
	m_meshMaterials.Ambient.b = 0;
	m_meshMaterials.Ambient.a = 0.8;
	return true;
}

bool CMissile::InitColliders()
{
	D3DXVECTOR3 pCenter;
	float pRadius;
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	m_pMesh->GetDeclaration(decl);
	LPVOID pVB;
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, &pVB);
	UINT uStride = D3DXGetDeclVertexSize(decl, 0);	
	D3DXComputeBoundingSphere((const D3DXVECTOR3* )pVB, m_pMesh->GetNumVertices(), uStride, &pCenter, &pRadius);
	Collider collider(pCenter, pRadius);
	m_colliders.push_back(collider);
	return true;
}

void CMissile::CollidingCallback(CGameNode *collided)
{
	switch(collided->GetType())
	{
	case ZERG:	
	case ZERG_TELEPORT:
		Recycle();
		m_scene->EventCallBack(STARWAR_DESTROY, this);
		break;
	default:
		return;
	}
}

void CMissile::CollidedCallback(CGameNode *colliding)
{
	//当前未定义行为
}