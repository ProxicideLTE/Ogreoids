#ifndef GAME_H_
#define GAME_H_

namespace ogreoids {

	// Forward declarations.
	class GameState;

	/**
	 * This class creates the game that will be used to during run time.
	 */
    class Game
        : public Ogre::FrameListener         // handle rendering loop events
        , public Ogre::WindowEventListener   // handle window events
        , public OIS::KeyListener            // handle keyboard events
        , public OIS::MouseListener          // handle mouse events
    {

        // Flag to set if game should exit.
        bool							mShouldQuit;

        // Gamestates.
        GameState*						mCurrentState;
		std::vector<GameState*>			gamestates;

        // Configuration and log file names.
        Ogre::String					mOgreCfgName;
        Ogre::String					mPluginCfgName;
        Ogre::String					mResourceCfgName;
        Ogre::String					mLogName; 

        // Core libraries and input managers.
        Ogre::Root*						mRoot;
        Ogre::RenderWindow*				mWindow;
        Ogre::Viewport*					mViewport;
		CEGUI::OgreRenderer*			mGuiRenderer;
        OIS::InputManager*				mInputMgr;
        OIS::Keyboard*					mKeyboard;
        OIS::Mouse*						mMouse;

    public:

        // Constructor and destructor.
        Game();
        ~Game();

        // The method that actually initializes everything, runs the game loop, then shuts everything down.
        void go();

		// Gamestates handling.
		void switchState(GameState* state);
		void quit()							{ mShouldQuit = true; }

        // Getters.
		static Game* getInstance();
        OIS::Keyboard* getKeyboard()		{ return mKeyboard; }
        OIS::Mouse* getMouse()				{ return mMouse; }
        Ogre::RenderWindow* getWindow()		{ return mWindow; }
        Ogre::Viewport* getViewport()		{ return mViewport; }
        Ogre::Real getTime() const			{ return 0.001f * mRoot->getTimer()->getMilliseconds(); }
		Ogre::Real getViewportWidth()		{ return mViewport->getActualWidth(); }
		Ogre::Real getViewportHeight()		{ return mViewport->getActualHeight(); }
		GameState* getCurrentState()		{ return mCurrentState;	 }
		

    private:

        // Noncopyable constructor and assignment operator.
        Game(const Game&);
        Game& operator= (const Game&);

        // Private initialization methods.
        bool initializeRenderer();
        void initializeInput();
        void initializeResources();
		void initializeCEGUI();
		void initializeGamestates();

        // Private cleanup methods.
        void shutdownRenderer();
        void shutdownInput();

        // Event Callbacks.
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);
        void windowResized(Ogre::RenderWindow* window);
        void windowClosed(Ogre::RenderWindow* window);
        bool keyPressed(const OIS::KeyEvent& arg);
        bool keyReleased(const OIS::KeyEvent& arg);
        bool mouseMoved(const OIS::MouseEvent& arg);
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

    };
}

#endif
