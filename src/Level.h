#ifndef LEVEL_H_
#define LEVEL_H_

#include "Player.h"

namespace ogreoids {

	class Player;
	class Projectile;
	class Obstacle;

	class Level {

		// Instance variables.
		Player*							player;

		Ogre::SceneManager*				mSceneMgr;

		std::vector<Projectile*>		projectiles;
		std::vector<Obstacle*>			obstacles;

	public:

		Level();
		virtual ~Level();

		void update(Ogre::Real deltaT);

		// Getters.
		bool isLevelOver()								{ return !player->isPlayerAlive(); }
		OIS::KeyListener* getKeyListener()				{ return player; }
		OIS::MouseListener* getMouseListener()			{ return player; }

		// Setters.
		void addProjectile(Projectile* p)				{ projectiles.push_back(p); }

	private:

		void initLevel();
		void updateProjectiles(Ogre::Real deltaT);
		void updateObstacles(Ogre::Real deltaT);

	};

}

#endif
