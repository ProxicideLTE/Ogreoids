#ifndef GAMEPLAYSTATE_H_
#define GAMEPLAYSTATE_H_

#include "GameState.h"

namespace ogreoids {
	
	class Aircraft;
	class Level;

	/**
	 * This class is the sub parent class for the menus.
	 */
	class GameplayState : public GameState {

		// Scene properties.
		Aircraft*						vehicle;
		Level*							level;

		bool							pause;

        Ogre::Camera*					mCamera;
		
		// UI variables.
        OgreBites::Button*				btn_resume;
        OgreBites::Button*				btn_main;
		OgreBites::Button*				btn_exit;

	protected:

		// Constructor and destructor.
        GameplayState();
        virtual ~GameplayState();

	public:

		static GameplayState* getInstance();

        virtual void initialize();
		virtual void createLevel();
		virtual void destroyLevel();
        virtual void finalize();

        virtual void enter();
        virtual void leave();

        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        virtual bool keyPressed(const OIS::KeyEvent& arg);
        virtual bool keyReleased(const OIS::KeyEvent& arg);

        virtual bool mouseMoved(const OIS::MouseEvent& arg);
        virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

		// Getters.
		Aircraft* getSelectedAircraft()				{ return vehicle; }
		Ogre::Camera* getGameplayCam()				{ return mCamera; }

		// Setters.
		void setSelectedAircraft(Aircraft* a);

	private:

        // Noncopyable constructor and assignment operator.
        GameplayState(const GameplayState&);
        GameplayState& operator= (const GameplayState&);

		// Event callbacks.
		void buttonHit(OgreBites::Button* button);

	};

}

#endif