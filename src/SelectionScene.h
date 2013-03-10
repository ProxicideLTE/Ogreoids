#ifndef SELECTIONSCENE_H_
#define SELECTIONSCENE_H_

namespace ogreoids {

	/**
	 * Class object that will contain the details of each aircraft stats.
	 */
	class Aircraft {
		
		std::string					filename;
		Ogre::String				meshName;
		Ogre::DisplayString			aircraftName;
		Ogre::DisplayString			description;

	public:

		Aircraft(Ogre::String aircraftName, Ogre::DisplayString meshName, Ogre::DisplayString desc);

		// Setters.
		void setFileName(std::string f)						{ filename = f; }

		// Getters.
		std::string getElemName()							{ return filename; }
		Ogre::String getMeshName()							{ return meshName; }
		Ogre::DisplayString getAircraftName()				{ return aircraftName; }
		Ogre::DisplayString getDescription()				{ return description; }

	};

	/**
	 * This class provides the functionally for swapping vehciles
	 */
	class SelectionScene {

		// Instance variables.
		static const char*			filename;
		static Ogre::Degree			rotSpeed;
		
		unsigned					index;
		
		Ogre::SceneManager*			mSceneMgr;
		Ogre::SceneNode*			mSceneNode;

		std::vector<Aircraft*>		aircrafts;

	public:

		SelectionScene();
		~SelectionScene();

		void update(Ogre::Real deltaT);

		void loadNext();
		void loadPrevious();

		Aircraft* getCurrentAircraft()			{ return aircrafts[index]; }

	private:

		void initialize();

	};

}

#endif
