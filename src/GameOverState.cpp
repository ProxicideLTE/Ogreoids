#include "stdafx.h"

#include "gamestates.h"
#include "Game.h"

namespace ogreoids {

	/**
	 * GameOverState constructor.
	 */
    GameOverState::GameOverState()
        : GameState()
    {
		
    }

	/**
	 * GameOverState destructor.
	 */
	GameOverState::~GameOverState() {

	}

	/**
	 * This function will create an instance of this state using the singleton design pattern.
	 *
	 * @return a pointer to this GameOverState class.
	 *
	 */
	GameOverState* GameOverState::getInstance() {
		static GameOverState menu;
		return &menu;
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * This function will initialize this state.
	 */
    void GameOverState::initialize() {
		
		GameState::initialize();
        mTrayMgr = new OgreBites::SdkTrayManager("GameOverState",Game::getInstance()->getWindow(),Game::getInstance()->getMouse(),this);
		mTrayMgr->hideAll();
		stateWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "GameOver_MasterRoot");

		mSpeed = -1;

		// Initialize the camera.
        mCamera = mSceneMgr->createCamera("GameOverStateCamera");
		mCamera->setNearClipDistance(1);
        mCamera->setFarClipDistance(5000);
        mCamera->setAutoAspectRatio(true);
        mCamera->setPosition(0, 0, -5);
		
		// Instantiate buttons.
        mMainMenuButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "GameOver_MainMenuButton", "Main Menu", 200);
        mQuitButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "GameOver_QuitButton", "Quit", 200);
		
		// Set skybox for the menu.
		mSceneMgr->setSkyBox(true, "SpaceBox", 10, true);
	
	}


// =====================================================================================
//
// #Finalization
//
// =====================================================================================

	/**
	 * This function will destroy this state.
	 */
    void GameOverState::finalize() {
		GameState::finalize();
    }


// =====================================================================================
//
// #Switching
//
// =====================================================================================

	/**
	 * This function will enter this state.
	 */
    void GameOverState::enter() {
        Game::getInstance()->getViewport()->setCamera(mCamera);
        mTrayMgr->showTrays();
        mTrayMgr->showAll();
    }

	/**
	 * This function will leave this state.
	 */
    void GameOverState::leave() {
        Game::getInstance()->getViewport()->setCamera(NULL);
        mTrayMgr->hideAll();
    }


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function will render every frame for this state.
	 * 
	 * @param evt			frame event that signals when a new frame is rendered
	 *
	 */
    bool GameOverState::frameRenderingQueued(const Ogre::FrameEvent& evt) {

		mTrayMgr->frameRenderingQueued(evt);
		GameState::frameRenderingQueued(evt);

		// Set captions for the buttons.
        mMainMenuButton->setCaption("Main Menu");
        mQuitButton->setCaption("Quit");

		// Rotate camera.
		mCamera->yaw(-mSpeed * evt.timeSinceLastFrame);

        return true;
    }


// =====================================================================================
//
// #Event Listeners
//
// =====================================================================================

	/**
	 * This function will handle the event when the mouse has been moved.
	 */
    bool GameOverState::mouseMoved(const OIS::MouseEvent& arg) {
		mTrayMgr->injectMouseMove(arg);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been clicked.
	 */
    bool GameOverState::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		mTrayMgr->injectMouseDown(arg, id);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been released.
	 */
    bool GameOverState::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		mTrayMgr->injectMouseUp(arg, id);
        return true;
    }

	/**
	 * This function will handle when a button is clicked.
	 * 
	 * @param button			pointer to the button that was clicked
	 *
	 */
	void GameOverState::buttonHit(OgreBites::Button* button) {

		// Determine which button was clicked.
        if (button == mMainMenuButton) {
			Game::getInstance()->switchState(MainMenuState::getInstance());
        } 
		
		else if (button == mQuitButton) {
			Game::getInstance()->quit();
        }

	}

}
