#include "stdafx.h"

#include "MusicManager.h"

namespace ogreoids {

	MusicManager::MusicManager(){
		initialize();
		createMusic();
		createSounds();
	}

	MusicManager::~MusicManager(){
		
	}

	MusicManager* MusicManager::getInstance(){
		static MusicManager musicManager;
		return &musicManager;
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	void MusicManager::initialize() {

		// Create the main system object.
		result = FMOD::System_Create(&system);	
		errorCheck("Failed to create the sound system");

		// Initialize FMOD.
		result = system->init(100, FMOD_INIT_NORMAL, 0);	
		errorCheck("Failed to initialize FMOD");
		result = system->set3DSettings(0.05f, 1, 1);
		errorCheck("Failed to set 3D sound settings");

	}

	void MusicManager::setListenerAttributes(Ogre::Vector3 pos, Ogre::Vector3 vel, Ogre::Vector3 dir, Ogre::Vector3 up){

		result = system->set3DListenerAttributes(0,
											&OgreToFmod(pos), &OgreToFmod(vel),
											&OgreToFmod(dir), &OgreToFmod(up));
		errorCheck("Failed to set 3D listener attributes");

	}

	FMOD::Channel* MusicManager::setAttributes(Ogre::Vector3 pos, Ogre::Vector3 vel, FMOD::Channel* channel) {
		result = channel->set3DAttributes(&OgreToFmod(pos), &OgreToFmod(vel));
		errorCheck("Failed to set sound 3D attributes for jetstream");
		return channel;
	}

	void MusicManager::createMusic() {
		
	}

	void MusicManager::createSounds() {
		

	}


// =====================================================================================
//
// #Update
//
// =====================================================================================

	void MusicManager::update(Ogre::Real deltaT) {
		result = system->update();
		errorCheck("Failed to update sound system");
	}
	

// =====================================================================================
//
// #Exceptation Handling
//
// =====================================================================================

	void MusicManager::errorCheck(const std::string& errMsg){

		if(result != FMOD_OK){

			std::stringstream ss;

			ss << errMsg << "FMOD error! " << result << ": " << FMOD_ErrorString(result);

			throw std::exception(ss.str().c_str());
		}

	}

}
