#include "stdafx.h"

#include "gamestates.h"
#include "Game.h"
#include "MusicManager.h"

namespace ogreoids {

	/**
	 * MainMenuState constructor.
	 */
    MainMenuState::MainMenuState()
        : GameState()
        , mStartButton(NULL)
        , mQuitButton(NULL)
    {
		
    }

	/**
	 * MainMenuState destructor.
	 */
	MainMenuState::~MainMenuState() {

	}

	/**
	 * This function will create an instance of this state using the singleton design pattern.
	 *
	 * @return a pointer to this MainMenuState class.
	 *
	 */
	MainMenuState* MainMenuState::getInstance() {
		static MainMenuState menu;
		return &menu;
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * This function will initialize the main menu state.
	 */
    void MainMenuState::initialize() {
		
		GameState::initialize();
        mTrayMgr = new OgreBites::SdkTrayManager("MainMenu",Game::getInstance()->getWindow(),Game::getInstance()->getMouse(),this);
		mTrayMgr->hideAll();
		stateWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "MainMenu_MasterRoot");

		mSpeed = -1;

		// Initialize the camera.
        mCamera = mSceneMgr->createCamera("MainMenuCamera");
		mCamera->setNearClipDistance(1);
        mCamera->setFarClipDistance(5000);
        mCamera->setAutoAspectRatio(true);
        mCamera->setPosition(0, 0, -5);

		//mTrayMgr->showLogo(OgreBites::TL_TOP);
		
		// Instantiate buttons.
        mStartButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "StartButton", "Start Game", 200);
        mQuitButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "QuitButton", "Quit", 200);
		
		// Set skybox for the menu.
		mSceneMgr->setSkyBox(true, "SpaceBox", 10, true);
	
	}


// =====================================================================================
//
// #Finalization
//
// =====================================================================================

	/**
	 * This function will destroy the main menu state.
	 */
    void MainMenuState::finalize() {
		GameState::finalize();
    }


// =====================================================================================
//
// #Switching
//
// =====================================================================================

	/**
	 * This function will enter the main menu state.
	 */
    void MainMenuState::enter() {
        Game::getInstance()->getViewport()->setCamera(mCamera);
        mTrayMgr->showTrays();
        mTrayMgr->showAll();
    }

	/**
	 * This function will leave the main menu state.
	 */
    void MainMenuState::leave() {
        Game::getInstance()->getViewport()->setCamera(NULL);
        mTrayMgr->hideAll();
    }


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function will render every frame for the main menu state.
	 * 
	 * @param evt			frame event that signals when a new frame is rendered
	 *
	 */
    bool MainMenuState::frameRenderingQueued(const Ogre::FrameEvent& evt) {

		mTrayMgr->frameRenderingQueued(evt);
		MusicManager::getInstance()->update(evt.timeSinceLastFrame);

		// Set captions for the buttons.
        mStartButton->setCaption("Start Game");
        mQuitButton->setCaption("Quit");

		// Rotate camera.
		mCamera->yaw(mSpeed * evt.timeSinceLastFrame);

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
    bool MainMenuState::mouseMoved(const OIS::MouseEvent& arg) {
		mTrayMgr->injectMouseMove(arg);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been clicked.
	 */
    bool MainMenuState::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		mTrayMgr->injectMouseDown(arg, id);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been released.
	 */
    bool MainMenuState::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		mTrayMgr->injectMouseUp(arg, id);
        return true;
    }

	/**
	 * This function will handle when a button is clicked.
	 * 
	 * @param button			pointer to the button that was clicked
	 *
	 */
	void MainMenuState::buttonHit(OgreBites::Button* button) {

		// Determine which button was clicked.
        if (button == mStartButton) {
			Game::getInstance()->switchState(SelectionMenuState::getInstance());
        } 
		
		else if (button == mQuitButton) {
			Game::getInstance()->quit();
        }

	}

}
