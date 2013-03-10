#include "stdafx.h"

#include "gamestates.h"
#include "Game.h"
#include "MusicManager.h"
#include "SelectionScene.h"

namespace ogreoids {

	/**
	 * SelectionMenuState constructor.
	 */
    SelectionMenuState::SelectionMenuState()
        : GameState()
        , mTrayMgr(NULL)
    {
		
    }

	/**
	 * SelectionMenuState destructor.
	 */
	SelectionMenuState::~SelectionMenuState() {

	}

	/**
	 * This function will create an instance of this state using the singleton design pattern.
	 *
	 * @return a pointer to this SelectionMenuState class.
	 *
	 */
	SelectionMenuState* SelectionMenuState::getInstance() {
		static SelectionMenuState menu;
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
    void SelectionMenuState::initialize() {

		GameState::initialize();
        mTrayMgr = new OgreBites::SdkTrayManager("SelectionMenu",Game::getInstance()->getWindow(),Game::getInstance()->getMouse(),this);
		mTrayMgr->hideAll();
		stateWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "SelectionMenu_MasterRoot");

		// Initialize the camera.
        mCamera = mSceneMgr->createCamera("SelectionMenuCamera");
		mCamera->setNearClipDistance(1);
        mCamera->setFarClipDistance(5000);
        mCamera->setAutoAspectRatio(true);
        mCamera->setPosition(-20, 0, 100);
		
		// Instantiate SDKTrays elements.
		mNextButton = mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "NextButton", "Next", 100);
        mPreviousButton = mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT, "PreviousButton", "Back", 100);
		mTextbox = mTrayMgr->createTextBox(OgreBites::TL_LEFT, "DetailsTextBox", "Details", 0.30f * Game::getInstance()->getViewportWidth(), 0.4f * Game::getInstance()->getViewportHeight());
		mSelectButton = mTrayMgr->createButton(OgreBites::TL_BOTTOM, "SelectButton", "Selection", 100);
		
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
    void SelectionMenuState::finalize() {
		GameState::finalize();
		if (scene != NULL) { delete scene; scene = NULL; }
    }


// =====================================================================================
//
// #Switching
//
// =====================================================================================

	/**
	 * This function will enter the main menu state.
	 */
    void SelectionMenuState::enter() {
        Game::getInstance()->getViewport()->setCamera(mCamera);
        mTrayMgr->showTrays();
        mTrayMgr->showAll();

		// New Scene manager.
		if (scene == NULL)
			scene = new SelectionScene();

    }

	/**
	 * This function will leave the main menu state.
	 */
    void SelectionMenuState::leave() {
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
    bool SelectionMenuState::frameRenderingQueued(const Ogre::FrameEvent& evt) {

		mTrayMgr->frameRenderingQueued(evt);
		GameState::frameRenderingQueued(evt);

		// Set captions for the buttons.
        mNextButton->setCaption("Next");
        mPreviousButton->setCaption("Back");
		mSelectButton->setCaption("Select");

		// Aircraft labels.
		mTextbox->setCaption(scene->getCurrentAircraft()->getAircraftName());
		mTextbox->setText(scene->getCurrentAircraft()->getDescription());

		scene->update(evt.timeSinceLastFrame);

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
    bool SelectionMenuState::keyPressed(const OIS::KeyEvent& arg) {

		if (OIS::KC_D == arg.key || OIS::KC_RIGHT == arg.key) {
			scene->loadNext();
		}

		else if (OIS::KC_A == arg.key || OIS::KC_LEFT == arg.key) {
			scene->loadPrevious();
		}

		else if (OIS::KC_RETURN == arg.key) {
			GameplayState::getInstance()->setSelectedAircraft(scene->getCurrentAircraft());
			Game::getInstance()->switchState(GameplayState::getInstance());
		}

        return true;
    }

	/**
	 * This function will handle the event when a keyboard key is released.
	 */
    bool SelectionMenuState::keyReleased(const OIS::KeyEvent& arg) {
        return true;
    }

	/**
	 * This function will handle the event when the mouse has been moved.
	 */
    bool SelectionMenuState::mouseMoved(const OIS::MouseEvent& arg) {
		mTrayMgr->injectMouseMove(arg);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been clicked.
	 */
    bool SelectionMenuState::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		mTrayMgr->injectMouseDown(arg, id);
        return true;
    }

	/**
	 * This function will handle the event when the mouse button has been released.
	 */
    bool SelectionMenuState::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		mTrayMgr->injectMouseUp(arg, id);
        return true;
    }

	/**
	 * This function will handle when a button is clicked.
	 * 
	 * @param button			pointer to the button that was clicked
	 *
	 */
	void SelectionMenuState::buttonHit(OgreBites::Button* button) {

		// Determine which button was clicked.
        if (button == mNextButton) {
			scene->loadNext();
        } 
		
		else if (button == mPreviousButton) {
			scene->loadPrevious();
        }

		else if (button == mSelectButton) {
			GameplayState::getInstance()->setSelectedAircraft(scene->getCurrentAircraft());
			Game::getInstance()->switchState(GameplayState::getInstance());
		}

	}

}
