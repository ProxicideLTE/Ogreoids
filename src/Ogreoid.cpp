#include "stdafx.h"

#include "obstacles.h"
#include "Level.h"

namespace ogreoids {

	/**
	 * Ogreoid constructor.
	 *
	 * @param l				pointer the level
	 * @param pos			spawn position
	 *
	 */
	Ogreoid::Ogreoid(Level* l, Ogre::Vector3 pos) 
		: lvl(l)
		, Obstacle(pos)
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
		Obstacle::collideDmg = 100;
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

	/**
	 * This function applies damage the ogreoid.
	 */
	void Ogreoid::applyDamage(Ogre::Real dmg) {
		hp -= dmg;	
		
		if (hp <= 0) {
			setDisposable();

			// Random chance of dropping a powerup.
			Ogre::Real randomVal = Ogre::Math::RangeRandom(0,10);

			// 1/5 times for a powerup to drop.
			if (randomVal > 7)
				lvl->addObstacle(new Powerup(lvl->getPlayer(), mSceneNode->getPosition()));

		}

	}

}
