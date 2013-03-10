#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "gamestates.h"

namespace ogreoids {

	class Obstacle {

	protected:

		// Instance variables.
		bool								disposable;

		Ogre::Real							speed;
		Ogre::Real							hp;
		Ogre::Real							radius;
		Ogre::Entity*						mesh;
		Ogre::SceneManager*					mSceneMgr;
		Ogre::SceneNode*					mSceneNode;
		Ogre::Vector3						spawnPos;

	public:

		Obstacle(Ogre::Vector3 pos);
		virtual ~Obstacle();

		virtual void update(Ogre::Real deltaT);

		// Getters.
		bool isDisposable()					{ return disposable; }
		Ogre::Real getRadius()				{ return radius; }
		Ogre::Vector3 getObstaclePosition()	{ return mSceneNode->getPosition(); }

		// Setters.
		void setDisposable()				{ disposable = true; }
		void applyDamage(Ogre::Real dmg)	{ hp -= dmg;	if (hp <= 0) setDisposable(); }


	private:

		void init();

	};

}

#endif
