#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "GameState.h"

namespace ogreoids {

	class MainMenuState : public GameState {

        // Scene properties.
        Ogre::Camera*					mCamera;

        // GUI variables.
        OgreBites::Button*				mStartButton;
        OgreBites::Button*				mQuitButton;

		Ogre::Degree					mSpeed;

		// Private constructor and destructor (Singleton design pattern).
		MainMenuState();
		~MainMenuState();

        // Noncopyable constructor and assignment operator.
        MainMenuState(const MainMenuState&);
        MainMenuState& operator= (const MainMenuState&);

	public:

		static MainMenuState* getInstance();

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