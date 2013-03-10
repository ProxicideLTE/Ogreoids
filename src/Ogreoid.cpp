#include "stdafx.h"

#include "Obstacle.h"
#include "Ogreoid.h"

namespace ogreoids {

	/**
	 * Ogreoid constructor.
	 */
	Ogreoid::Ogreoid(Ogre::Vector3 pos) 
		: Obstacle(pos)
	{
		init();
	}

	/**
	 * Ogreoid destructor.
	 */
	Ogreoid::~Ogreoid() {
		mSceneMgr->destroySceneNode(mSceneNode);
		mSceneMgr->destroyEntity(mesh);
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * Setup the obstacle scene node and entity.
	 */
	void Ogreoid::init() {

		// Create the scenenode and attach the ogre head for this ogreoid.
		mesh = mSceneMgr->createEntity("ogrehead.mesh");
		mSceneNode->attachObject(mesh);
		
		// Initialize stats.
		speed = 350;
		hp = 100;
		radius = (mesh->getBoundingBox().getMaximum() - mesh->getBoundingBox().getCenter()).length();

	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the ogreoid.
	 */
	void Ogreoid::update(Ogre::Real deltaT) {

	}

}
