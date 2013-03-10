#ifndef GAMESTATE_H_
#define GAMESTATE_H_

namespace ogreoids {

	class Level;

	/**
	 * This class is the parent class of all game states.
	 */
	class GameState : public OgreBites::SdkTrayListener {

	protected:

		// Instance variables.
		Level*							level;
		CEGUI::Window*					stateWindow;
		Ogre::SceneManager*				mSceneMgr;
		OgreBites::SdkTrayManager*		mTrayMgr;

		// Constructor and destructor.
        GameState();
        virtual ~GameState();

	public:

        virtual void initialize();
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
		Ogre::SceneManager* getSceneManager()			{ return mSceneMgr; }

	private:

        // Noncopyable.
        GameState(const GameState&);
        GameState& operator= (const GameState&);

	};

}

#endif