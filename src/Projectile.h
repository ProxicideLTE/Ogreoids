#ifndef PROJECTILE_H_
#define PROJECTILE_H_

namespace ogreoids {

	class Projectile {

		// Instance variables.
		bool						disposable;

		Ogre::Entity*				mesh;
		Ogre::Quaternion			orientation;
		Ogre::Real					damage;
		Ogre::Real					duration;
		Ogre::Real					speed;
		Ogre::String				meshName;
		Ogre::SceneManager*			mSceneMgr;
		Ogre::SceneNode*			mSceneNode;
		Ogre::Vector3				spawnPosition;

	public:

		Projectile(Ogre::Vector3 pos, Ogre::String meshName, Ogre::Quaternion or, Ogre::Real dmg);
		virtual ~Projectile();

		void update(Ogre::Real deltaT);

		// Getters.
		bool isDisposable()								{ return disposable; }
		Ogre::Real getDamage()							{ return damage; }
		Ogre::Vector3 getProjectilePosition()			{ return mSceneNode->getPosition(); }

		// Setters.
		void setDisposable()							{ disposable = true; }
		void setDuration(Ogre::Real lifeSpan)			{ duration = lifeSpan; }

	private:

		void init();

	};

}

#endif
