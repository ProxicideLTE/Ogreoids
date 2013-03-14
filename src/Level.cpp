#include "stdafx.h"

#include "Level.h"
#include "gamestates.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"
#include "obstacles.h"

namespace ogreoids {

	/**
	 * Level constructor.
	 */
	Level::Level() 
		: mSceneMgr(GameplayState::getInstance()->getSceneManager())
	{
		initLevel();
	}

	/**
	 * Level destructor.
	 */
	Level::~Level() {
		delete player;

		for (unsigned i = 0; i < obstacles.size(); i++)
			delete obstacles[i];

		for (unsigned i = 0; i < projectiles.size(); i++)
			delete projectiles[i];

		for (unsigned i = 0; i < powerups.size(); i++)
			delete powerups[i];

	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================
	
	/**
	 * This function sets up the level.
	 */
	void Level::initLevel() {

		// Set skybox for the level.
		mSceneMgr->setSkyBox(true, "SpaceBox", 10, true);

		// Create the player.
		player = new Player(this);

		Ogre::Real zPos = 2500;

		// Create some initial obstacles for the player to dodge and/or shoot at.
		for (int i = 0; i < 10; i++) {
			Ogre::Real x = Ogre::Math::RangeRandom(-90,90);
			Ogre::Real y = Ogre::Math::RangeRandom(-90,90);
			obstacles.push_back(new Ogreoid(this, Ogre::Vector3(x,y,zPos)));
			zPos += 1500;
		}

	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the scene.
	 *
	 * @param deltaT					time since last frame
	 *
	 */
	void Level::update(Ogre::Real deltaT) {
		player->update(deltaT);
		updateObstacles(deltaT);
		updateProjectiles(deltaT);
	}

	void Level::updateObstacles(Ogre::Real deltaT) {

		if (obstacles.empty()) return;

		// Check collisions with the player.
		for (unsigned i = 0; i < obstacles.size(); ) {
			
			// If the obstacle should be destroyed.
			if (obstacles[i]->isDisposable()) {
				delete obstacles[i];
				obstacles[i] = obstacles.back();
				obstacles.pop_back();
			}

			else {

				// Get the distance to the obstacle.
				Ogre::Vector3 playerPos = player->getPosition();
				Ogre::Real dist = (playerPos - obstacles[i]->getObstaclePosition()).length();

				if (dist <= 100) {
					std::cout << "Collision" << std::endl;
					player->applyDamage(obstacles[i]->getCollideDamage());
					obstacles[i]->setDisposable();
				}

				else if (player->getPosition().z >= obstacles[i]->getObstaclePosition().z) {
					std::cout << "Deleting obstacle" << std::endl;
					obstacles[i]->setDisposable();
				}

			}

			i++;

		}

	}

	void Level::updateProjectiles(Ogre::Real deltaT) {

		if (projectiles.size() == 0) return;

		// Loop all projectiles in the level.
		for (unsigned i = 0; i < projectiles.size(); /* */) {

			// Update the projectile.
			Projectile* projectile = projectiles[i];
			projectile->update(deltaT);

			// If the projectile should be destroyed.
			if (projectile->isDisposable()) {
                delete projectile;
                projectiles[i] = projectiles.back();
                projectiles.pop_back();
			}

			else  {

				// For each projectile determine if it has collided with an obstacle.
				for (unsigned j = 0; j < obstacles.size(); /* */) {

					// If the obstacle should be destroyed.
					if (obstacles[j]->isDisposable()) {
						delete obstacles[j];
						obstacles[j] = obstacles.back();
						obstacles.pop_back();
					}

					else {

						// Get the distance from the projectile to the obstacle.
						Ogre::Vector3 projectilePos = projectiles[i]->getProjectilePosition();
						Ogre::Vector3 obstaclePos = obstacles[j]->getObstaclePosition();
						Ogre::Real dist = (obstaclePos - projectilePos).length();
							
						// Projectile collided with obstacle.
						if (dist <= obstacles[j]->getRadius()) {
							projectiles[i]->setDisposable();
							obstacles[j]->applyDamage(projectiles[i]->getDamage());
						}

						j++;

					}

				} // end of for loop for obstacles
				
				i++;

			}

		} // end of for loop for projectiles.

	}

}
