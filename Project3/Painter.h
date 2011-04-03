#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletSoftBody\btSoftRigidDynamicsWorld.h>
#include <BulletCollision\CollisionDispatch\btSphereSphereCollisionAlgorithm.h>
#include <BulletCollision\NarrowPhaseCollision\btGjkEpa2.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftBodyHelpers.h>
#include "ConvexDecomposition\ConvexDecomposition.h"
#include "ConvexDecomposition\cd_wavefront.h"

class Painter
{
private:
	btSoftRigidDynamicsWorld* dynamicsWorld;
	btSoftBodyWorldInfo worldInfo;
	btSoftBody* brush;
	void loadObj(const char* fileName, btVector3 &position, btScalar scaling = 1.f);

public:
	Painter(void);
	~Painter(void);

	void update(double elapsed);

	btSoftRigidDynamicsWorld* getDynamicsWorld();
};

