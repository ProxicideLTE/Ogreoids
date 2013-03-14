#include "stdafx.h"

#include "Obstacle.h"
#include "Powerup.h"
#include "Player.h"

namespace ogreoids {

	/**
	 * Powerup constructor.
	 *
	 * @param p				pointer to the player to apply powerup effects.
	 * @param pos			spawn position
	 *
	 */
	Powerup::Powerup(Player* p, Ogre::Vector3 pos) 
		: p(p)
		, Obstacle(pos)
	{
		init();
	}

	/**
	 * Powerup destructor.
	 */
	Powerup::~Powerup() {
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
	void Powerup::init() {

		// Create the scenenode and attach the ogre head for this ogreoid.
		mesh = mSceneMgr->createEntity("Barrel.mesh");
		mSceneNode->attachObject(mesh);
		mSceneNode->scale(2,2,2);
		
		// Initialize stats.
		Obstacle::collideDmg = 0;
		speed = 350;
		hp = 0;
		radius = (mesh->getBoundingBox().getMaximum() - mesh->getBoundingBox().getCenter()).length();

	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the powerup.
	 */
	void Powerup::update(Ogre::Real deltaT) {

	}


// =====================================================================================
//
// #Event Callbacks
//
// =====================================================================================

	/**
	 * Set the flag so that this powerup can be destroyed next frame.
	 */
	void Powerup::setDisposable() { 
		// Set flag.
		disposable = true; 
		applyPowerupEffect();
	}

	/**
	 * Apply the effects of the powerup to the player.
	 */
	void Powerup::applyPowerupEffect() {
		p->upgradeWeaponSystem();
	}

}
