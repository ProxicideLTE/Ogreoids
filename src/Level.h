#ifndef LEVEL_H_
#define LEVEL_H_

#include "Player.h"

namespace ogreoids {

	class Player;
	class Projectile;
	class Obstacle;
	class Powerup;

	class Level {

		// Instance variables.
		Player*							player;

		Ogre::SceneManager*				mSceneMgr;

		std::vector<Projectile*>		projectiles;
		std::vector<Obstacle*>			obstacles;
		std::vector<Powerup*>			powerups;

	public:

		Level();
		virtual ~Level();

		void update(Ogre::Real deltaT);

		// Getters.
		bool isLevelOver()								{ return !player->isPlayerAlive(); }
		Player* getPlayer()								{ return player; }
		OIS::KeyListener* getKeyListener()				{ return player; }
		OIS::MouseListener* getMouseListener()			{ return player; }

		// Setters.
		void addProjectile(Projectile* p)				{ projectiles.push_back(p); }
		void addObstacle(Obstacle* o)					{ obstacles.push_back(o); }
		void spawnPowerup(Powerup* p)					{ powerups.push_back(p); }

	private:

		void initLevel();
		void updateProjectiles(Ogre::Real deltaT);
		void updateObstacles(Ogre::Real deltaT);

	};

}

#endif
