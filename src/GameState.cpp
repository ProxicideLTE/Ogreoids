#include "stdafx.h"

#include "GameState.h"
#include "MusicManager.h"
#include "Game.h"

namespace ogreoids {

	/**
	 * GameState constructor.
	 */
    GameState::GameState() {

    }

	/**
	 * GameState destructor.
	 */
    GameState::~GameState()  {
    
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * This function will initialize the GameState.
	 */
    void GameState::initialize() {
        mSceneMgr = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
	}

	/**
	 * This function will destroy the GameState.
	 */
    void GameState::finalize() {
		Ogre::Root::getSingleton().destroySceneManager(mSceneMgr);
        delete mTrayMgr;
        mTrayMgr = NULL;
		if (stateWindow != NULL) {
			CEGUI::WindowManager::getSingleton().destroyWindow(stateWindow);
			stateWindow = NULL;
		}
    }


// =====================================================================================
//
// #Switching
//
// =====================================================================================

	/**
	 * This function will enter the game state.
	 */
    void GameState::enter() {

    }

	/**
	 * This function will leave the game state.
	 */
    void GameState::leave() {

    }


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function will render every frame for the game state.
	 * 
	 * @param evt			frame Event that signals when a new frame is rendered
	 *
	 */
    bool GameState::frameRenderingQueued(const Ogre::FrameEvent& evt) {
		MusicManager::getInstance()->update(evt.timeSinceLastFrame);
        return true;
    }


// =====================================================================================
//
// #Events Listeners
//
// =====================================================================================

	/**
	 * This function will handle the event when a keyboard key is struck.
	 */
    bool GameState::keyPressed(const OIS::KeyEvent& arg) {
        return true;
    }

	/**
	 * This function will handle the event when a keyboard key is released.
	 */
    bool GameState::keyReleased(const OIS::KeyEvent& arg) {
        return true;
    }

	/**
	 * This function will handle the event when the mouse has been moved.
	 */
    bool GameState::mouseMoved(const OIS::MouseEvent& arg) {
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been clicked.
	 */
    bool GameState::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been released.
	 */
    bool GameState::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
        return true;
    }

}
