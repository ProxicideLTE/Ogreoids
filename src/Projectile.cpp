#include "stdafx.h"

#include "Projectile.h"
#include "gamestates.h"

namespace ogreoids {

	/**
	 * Projectile constructor.
	 */
	Projectile::Projectile(Ogre::Vector3 pos, Ogre::String meshName, Ogre::Quaternion or, Ogre::Real dmg) 
		: mSceneMgr(GameplayState::getInstance()->getSceneManager())
		, disposable(false)
		, meshName(meshName)
		, spawnPosition(pos)
		, orientation(or)
		, speed(2000)
		, duration(NULL)
		, damage(dmg)
	{
		init();
	}

	/**
	 * Projectile destructor.
	 */
	Projectile::~Projectile() {
		Ogre::SceneManager* sceneMgr = mSceneNode->getCreator();
		sceneMgr->destroySceneNode(mSceneNode);
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================
	
	/**
	 * Setup for the projectile.
	 */
	void Projectile::init() {

		// Create entity.
		mesh = mSceneMgr->createEntity(meshName);

		// Create a scene node.
		mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mSceneNode->setOrientation(orientation);
		mSceneNode->setPosition(spawnPosition);
		mSceneNode->attachObject(mesh);
		
	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the projectile.
	 *
	 * @param deltaT					time since last frame
	 *
	 */
	void Projectile::update(Ogre::Real deltaT) {
		
		// Translate projectile.
		Ogre::Vector3 disp = mSceneNode->getOrientation() * (mSceneNode->getPosition().UNIT_Z * speed * deltaT);
		mSceneNode->translate(disp);

		// Decrement life time.
		duration -= deltaT;
		if (duration <= 0) disposable = true;

	}

}
