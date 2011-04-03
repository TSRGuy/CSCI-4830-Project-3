#include "Painter.h"


Painter::Painter(void)
{
	btCollisionConfiguration* m_collisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
	btDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	btScalar maxProxies = 32766;
	btVector3 worldAabbMin(-1000,-1000,-1000);
	btVector3 worldAabbMax(1000,1000,1000);
	btBroadphaseInterface* m_broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	btConstraintSolver* m_solver = solver;

	dynamicsWorld = new btSoftRigidDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	worldInfo.m_broadphase = m_broadphase;
	worldInfo.m_dispatcher = m_dispatcher;

	loadObj("Meshes/Sphere.obj", btVector3(0,0,-20), 1.2f);
}


Painter::~Painter(void)
{
}

btSoftRigidDynamicsWorld* Painter::getDynamicsWorld()
{
	return dynamicsWorld;
}

void Painter::update(double elapsed)
{
	//brush->addForce(btVector3(0, .001, 0), 0);
	dynamicsWorld->stepSimulation(elapsed);
}

void Painter::loadObj(const char* fileName, btVector3 &position, btScalar scaling)
{
	ConvexDecomposition::WavefrontObj wo;
	int loadedWO = wo.loadObj(fileName);

	if(loadedWO)
	{
		btVector3* d = new btVector3[wo.mTriCount * 3];

		btVector3 localScaling(scaling, scaling, scaling);
		
		int i;
		for ( i = 0; i < wo.mTriCount;i++)
		{
			int index0 = wo.mIndices[i*3];
			int index1 = wo.mIndices[i*3+1];
			int index2 = wo.mIndices[i*3+2];

			btVector3 vertex0(wo.mVertices[index0*3], wo.mVertices[index0*3+1],wo.mVertices[index0*3+2]);
			btVector3 vertex1(wo.mVertices[index1*3], wo.mVertices[index1*3+1],wo.mVertices[index1*3+2]);
			btVector3 vertex2(wo.mVertices[index2*3], wo.mVertices[index2*3+1],wo.mVertices[index2*3+2]);
			
			vertex0 *= localScaling;
			vertex1 *= localScaling;
			vertex2 *= localScaling;

			d[i * 3] = vertex0;
			d[i * 3 + 1] = vertex1;
			d[i * 3 + 2] = vertex2;

		}

		brush = btSoftBodyHelpers::CreateFromConvexHull(worldInfo, d, wo.mTriCount * 3);
		brush->generateBendingConstraints(2);
		//brush->randomizeConstraints();
		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(position);
		brush->transform(trans);
		//brush->generateClusters(64);

		dynamicsWorld->addSoftBody(brush);

	}
}
