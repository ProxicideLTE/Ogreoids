#ifndef SELECTIONMENUSTATE_H_
#define SELECTIONMENUSTATE_H_

#include "GameState.h"

namespace ogreoids {

	class SelectionScene;

	class SelectionMenuState : public GameState {

		// Scene properties.
        Ogre::Camera*					mCamera;
		SelectionScene*					scene;

        // GUI variables.
        OgreBites::SdkTrayManager*		mTrayMgr;
        OgreBites::Button*				mNextButton;
        OgreBites::Button*				mPreviousButton;
		OgreBites::Button*				mSelectButton;
		OgreBites::TextBox*				mTextbox;

		// Private constructor and destructor (Singleton design pattern).
		SelectionMenuState();
		~SelectionMenuState();

        // Noncopyable constructor and assignment operator.
        SelectionMenuState(const SelectionMenuState&);
        SelectionMenuState& operator= (const SelectionMenuState&);

	public:

		static SelectionMenuState* getInstance();

        void initialize();
        void finalize();

        void enter();
        void leave();

        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	private:

		// Event callbacks.
        bool keyPressed(const OIS::KeyEvent& arg);
        bool keyReleased(const OIS::KeyEvent& arg);
        bool mouseMoved(const OIS::MouseEvent& arg);
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        void buttonHit(OgreBites::Button* button);

	};

}

#endif
