#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

#include "GameState.h"

namespace ogreoids {

	class GameOverState : public GameState {

        // Scene properties.
        Ogre::Camera*					mCamera;

        // GUI variables.
        OgreBites::Button*				mMainMenuButton;
        OgreBites::Button*				mQuitButton;

		Ogre::Degree					mSpeed;

		// Private constructor and destructor (Singleton design pattern).
		GameOverState();
		~GameOverState();

        // Noncopyable constructor and assignment operator.
        GameOverState(const GameOverState&);
        GameOverState& operator= (const GameOverState&);

	public:

		static GameOverState* getInstance();

        void initialize();
        void finalize();

        void enter();
        void leave();

        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	private:

		// Event callbacks.
        bool mouseMoved(const OIS::MouseEvent& arg);
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        void buttonHit(OgreBites::Button* button);
		
	};

}

#endif