#ifndef PLAYER_H_
#define PLAYER_H_

namespace ogreoids {

	class Level;
	class WeaponSystem;

	class Player : public OIS::KeyListener
				 , public OIS::MouseListener {

		// Instance variables.
		static Ogre::Real 					maxHeight, maxWidth, camDist;
		static Ogre::Degree 				rollSpeed, maxYaw, maxPitch;
		static const char*					filename;

		Level*								level;
		WeaponSystem*						currentWeaponSystem;

		bool								isAlive;

		Ogre::Real							hp;
		Ogre::Real							speed;
		Ogre::Degree						yawSpeed, pitchSpeed;
		Ogre::Entity*						mesh;
		Ogre::Entity*						target;
		Ogre::SceneManager*					mSceneMgr;
		Ogre::SceneNode*					mSceneNode;
		Ogre::SceneNode*					mCameraNode;
		Ogre::SceneNode*					mTarget;

		std::vector<Ogre::Entity*>			meshes;
		std::vector<Ogre::SceneNode*>		sceneNodes;
		std::vector<WeaponSystem*>			weaponSystems;

	public:

		Player(Level* lvl);
		virtual ~Player();

		void update(Ogre::Real deltaT);
		void updateVehicle(Ogre::Real deltaT);
		void updateCamera(Ogre::Real deltaT);

		// Getters.
		bool isPlayerAlive()				{ return isAlive; }
		Ogre::Vector3 getPosition()			{ return mSceneNode->getPosition(); }

		// Setters.
		void applyDamage(Ogre::Real dmg);

	private:

		void setupModel();
		void setupStats();
		void setupSystems();

		// Event callbacks.
        virtual bool keyPressed(const OIS::KeyEvent& arg);
        virtual bool keyReleased(const OIS::KeyEvent& arg);
        virtual bool mouseMoved(const OIS::MouseEvent& arg);
        virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

	};

}

#endif