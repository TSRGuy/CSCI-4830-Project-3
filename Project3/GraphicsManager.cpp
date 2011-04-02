#include "GraphicsManager.h"


GraphicsManager::GraphicsManager(void)
{
}


GraphicsManager::~GraphicsManager(void)
{
}

void GraphicsManager::init()
{
#ifdef _DEBUG
	string pluginsFile = "plugins.cfg";
#else
	string pluginsFile = "plugins_release.cfg";
#endif
	string configFile = "ogre.cfg";
	string logFile = "./ogre.log";
	string resourcesFile = "resources.cfg";

	root = new Ogre::Root(pluginsFile, configFile, logFile);
	root->setRenderSystem(root->getRenderSystemByName("OpenGL Rendering Subsystem"));
	root->initialise(false);

	ConfigFile cf;
	cf.load(resourcesFile);

	ConfigFile::SectionIterator seci = cf.getSectionIterator();
	string secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap * settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for(i = settings->begin(); i!=settings->end(); i++)
		{
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	GetWindow("Project 3");
	SetUpCamera();

	//return root;
}

Ogre::RenderWindow* GraphicsManager::GetWindow(string name)
{
	Ogre::NameValuePairList nvpl;
	nvpl["parentWindowHandle"] = Ogre::StringConverter::toString((size_t)NULL);
	nvpl["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)NULL);

	window = root->createRenderWindow(name, 0, 0, false, &nvpl);
	window->setVisible(true);
	if(render_windows.size() == 0)
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		
	render_windows[name] = window;
	window->setDeactivateOnFocusChange(false);

	window->resize(800,600);

	return window;
}

void GraphicsManager::SetUpCamera()
{
	manager = root->createSceneManager(Ogre::ST_GENERIC, "main");
	root_sn = manager->getRootSceneNode();
	manager->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
	manager->setAmbientLight(Ogre::ColourValue(.5, .5, .5)); //Abient light set here

	//set up camera
	Ogre::SceneNode *player = manager->createSceneNode("Player");
	c = manager->createCamera("main_camera");
	c->setFOVy(Ogre::Degree(45));
	c->setNearClipDistance(.01);
	c->setFarClipDistance(100);
	c->setAutoAspectRatio(true);

	//TODO: Remove temporary settings
	c->setPosition(Ogre::Vector3(0, 0, 0));
	//c->lookAt(8,3,0);
	/*Ogre::Light *l = manager->createLight("light1");
	root_sn->attachObject(l);
	l->setPosition(0, 6, 0);*/

	//attach the camera
	vp = window->addViewport(c);
	c_sn = manager->createSceneNode("main_camera");
	c_sn->setPosition(0, 3, 0);
	//c_sn->attachObject(c);

	root_sn->addChild(player);
	player->addChild(c_sn);
	Ogre::SceneNode *cPitch_sn = c_sn->createChildSceneNode("cameraPitch");
	cPitch_sn->attachObject(c);
}

void GraphicsManager::RenderFrame(Ogre::Real timeSinceLastFrame)
{
	root->renderOneFrame(timeSinceLastFrame);
}

Ogre::SceneNode* GraphicsManager::GetRootSceneNode()
{
	return root_sn;
}

Ogre::SceneManager* GraphicsManager::GetManager()
{
	return manager;
}