#include <Ogre.h>
#include "GraphicsManager.h"
#include "GameTimer.h"

GraphicsManager graphicsManager;

void main(int argc, char *argv[])
{
	graphicsManager.init();

	Ogre::Entity* ObjectEntity = graphicsManager.GetManager()->createEntity("ObjectEntity", "cube.mesh");
	ObjectEntity->setMaterialName("Box");
	Ogre::SceneNode* ObjectScene = graphicsManager.GetRootSceneNode()->createChildSceneNode("ObjectScene");
	ObjectScene->attachObject(ObjectEntity);
	ObjectScene->setPosition(0, 0, -20);
	ObjectScene->setScale(.05, .05, .05);

#pragma region Main Loop
	//Main Loop
	GameTimer timer;
	while(1)
	{
		double elapsed = timer.getElapsedTimeSec();
		graphicsManager.RenderFrame(elapsed);
		Ogre::WindowEventUtilities::messagePump();
	}
#pragma endregion

}