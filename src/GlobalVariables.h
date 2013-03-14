#ifndef GLOBALS_VARS_H_
#define GLOBALS_VARS_H_

namespace ogreoids {

	// Global enum for sounds.
	enum sounds {
		// Weapon Systems.
		ws1_shot = 0,				ws2_shot = 1,
		ws3_shot = 2,				ws4_shot = 2,
		// Menu.
		start_game = 3,				pause_game = 4,
		selection = 5,
		// Collisions.
		crash = 6,					laser_powerup = 7,
		// Warning.
		warning_modernate = 8
	};

	// Global enum for background music.
	enum bgm {
		main_menu = 0
	};

	// Mouse sensitivity.
	extern Ogre::Real gFreelookMouseSpeed;
    extern Ogre::Real gMouseSensitivity;

	// Gravity acceleration vector.
    const Ogre::Vector3 gGravity(0, -9.8f, 0);        

	// Default orientation vectors.
    const Ogre::Vector3 gForward(Ogre::Vector3(1, 0, 0));
    const Ogre::Vector3 gForwardZ(Ogre::Vector3(0, 0, 1));

	// Conversions.
	int charToInt(const char* c);
	float charToFloat(const char* c);
	std::string intToString(int num);
	std::string doubleToString(double num);

	CEGUI::MouseButton ConvertButton(OIS::MouseButtonID buttonId);

}

#endif
