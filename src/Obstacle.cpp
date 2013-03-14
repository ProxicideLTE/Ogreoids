#include "stdafx.h"

#include "Obstacle.h"
#include "gamestates.h"

namespace ogreoids {

	/**
	 * Obstacle constructor.
	 *
	 * @param pos			spawn position
	 *
	 */
	Obstacle::Obstacle(Ogre::Vector3 pos) 
		: mSceneMgr(GameplayState::getInstance()->getSceneManager())
		, spawnPos(pos)
		, disposable(false)
	{
		init();
	}

	/**
	 * Obstacle destructor.
	 */
	Obstacle::~Obstacle() {
		
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * Setup the obstacle's scenenode.
	 */
	void Obstacle::init() {
		mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mSceneNode->yaw(Ogre::Degree(180));
		mSceneNode->setPosition(spawnPos);
	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the obstacle.
	 */
	void Obstacle::update(Ogre::Real deltaT) {

	}


}
