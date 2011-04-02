#pragma once

#include <Ogre.h>
#include <string>
using namespace Ogre;
using namespace std;

class GraphicsManager
{
private:
	Ogre::Root *root;
	std::map<std::string,Ogre::RenderWindow*> render_windows;
	Ogre::SceneNode *root_sn;
	Ogre::Camera *c;
	Ogre::SceneNode *c_sn;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *manager;
	Ogre::Viewport *vp;

	void SetUpCamera();
	Ogre::RenderWindow* GetWindow(string name);

public:
	GraphicsManager(void);
	~GraphicsManager(void);

	void RenderFrame(Ogre::Real timeSinceLastFrame);
	void init();
	Ogre::SceneNode *GetRootSceneNode();
	Ogre::SceneManager *GetManager();
};

