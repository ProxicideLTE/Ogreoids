#include "stdafx.h"

#include "gamestates.h"
#include "Game.h"
#include "Level.h"
#include "SelectionScene.h"
#include "Player.h"

namespace ogreoids {

	/**
	 * GameplayState constructor.
	 */
    GameplayState::GameplayState() 
		: GameState()
	{

    }

	/**
	 * GameplayState destructor.
	 */
    GameplayState::~GameplayState()  {
    
	}

	/**
	 * This function will create an instance of this state using the singleton design pattern.
	 *
	 * @return a pointer to this GameplayState class.
	 *
	 */
	GameplayState* GameplayState::getInstance() {

		static GameplayState state;
		return &state;

	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * This function will initialize the GameplayState.
	 */
    void GameplayState::initialize() {
		
		GameState::initialize();
        mTrayMgr = new OgreBites::SdkTrayManager("GameplayState",Game::getInstance()->getWindow(),Game::getInstance()->getMouse(),this);
		mTrayMgr->hideAll();
		stateWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "Gameplay_MasterRoot");

		// Initialize the camera.
        mCamera = mSceneMgr->createCamera("GameplayCamera");
		mCamera->setNearClipDistance(1);
        mCamera->setFarClipDistance(5000);
        mCamera->setAutoAspectRatio(true);
		mCamera->yaw(Ogre::Degree(180));

		// Create buttons.
        btn_resume = mTrayMgr->createButton(OgreBites::TL_CENTER, "btn_resume", "Resume", 200);
        btn_main = mTrayMgr->createButton(OgreBites::TL_CENTER, "btn_main", "Main Menu", 200);
		btn_exit = mTrayMgr->createButton(OgreBites::TL_CENTER, "btn_exit", "Exit Game", 200);

	}

	/**
	 * This function will set the aircraft that the player has chosen.
	 */
	void GameplayState::setSelectedAircraft(Aircraft* a) { 
		vehicle = a;
	}


// =====================================================================================
//
// #Finalization
//
// =====================================================================================

	/**
	 * This function will destroy the GameplayState.
	 */
    void GameplayState::finalize() {
		GameState::finalize();
    }

	
// =====================================================================================
//
// #Switching
//
// =====================================================================================

	/**
	 * This function will enter the gameplay state.
	 */
    void GameplayState::enter() {
		Game::getInstance()->getViewport()->setCamera(mCamera);
		createLevel();
		pause = false;
    }

	/**
	 * This function creates the level.
	 */
	void GameplayState::createLevel() {
		level = new Level();
	}

	/**
	 * This function will leave the gameplay state.
	 */
    void GameplayState::leave() {
		Game::getInstance()->getViewport()->setCamera(NULL);
		destroyLevel();
		if (pause) {
			mTrayMgr->hideTrays();
			mTrayMgr->hideAll();
		}
    }

	/**
	 * This function destroys the level.
	 */
	void GameplayState::destroyLevel() {
		if (level != NULL) {
			delete level;
			level = NULL;
		}
	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function will render every frame for the gameplay state.
	 * 
	 * @param evt			Frame Event that signals when a new frame is rendered
	 *
	 */
    bool GameplayState::frameRenderingQueued(const Ogre::FrameEvent& evt) {
		if (!pause) { level->update(evt.timeSinceLastFrame); }
		btn_resume->setCaption("Resume");
        btn_main->setCaption("Main Menu");
		btn_exit->setCaption("Exit Game");
        return true;
    }


// =====================================================================================
//
// #Event Listeners
//
// =====================================================================================

	/**
	 * This function will handle the event when a keyboard key is struck.
	 */
    bool GameplayState::keyPressed(const OIS::KeyEvent& arg) {

		if (OIS::KC_ESCAPE == arg.key) {
			pause = true;
			mTrayMgr->showTrays();
			mTrayMgr->showAll();
		}

		level->getKeyListener()->keyPressed(arg);

        return true;
    }

	/**
	 * This function will handle the event when a keyboard key is released.
	 */
    bool GameplayState::keyReleased(const OIS::KeyEvent& arg) {
		level->getKeyListener()->keyReleased(arg);
        return true;
    }

	/**
	 * This function will handle the event when the mouse has been moved.
	 */
    bool GameplayState::mouseMoved(const OIS::MouseEvent& arg) {
		if (!pause)
			level->getMouseListener()->mouseMoved(arg);
		else
			mTrayMgr->injectMouseMove(arg);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been clicked.
	 */
    bool GameplayState::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		if (!pause)
			level->getMouseListener()->mousePressed(arg,id);
		else
			mTrayMgr->injectMouseDown(arg, id);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been released.
	 */
    bool GameplayState::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		if (!pause)
			level->getMouseListener()->mouseReleased(arg,id);
		else
			mTrayMgr->injectMouseUp(arg, id);
        return true;
    }

	/**
	 * This function will handle when a button is clicked.
	 * 
	 * @param button			pointer to the button that was clicked
	 *
	 */
	void GameplayState::buttonHit(OgreBites::Button* button) {

		// Determine which button was clicked.
        if (button == btn_resume) {
			pause = false;
			mTrayMgr->hideTrays();
			mTrayMgr->hideAll();
        } 
		
		else if (button == btn_main) {
			Game::getInstance()->switchState(MainMenuState::getInstance()->getInstance());
        }

		else if (button == btn_exit) {
			Game::getInstance()->quit();
        }

	}

}
