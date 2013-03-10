#ifndef GLOBALS_VARS_H_
#define GLOBALS_VARS_H_

namespace ogreoids {

	// Gravity acceleration vector.
    const Ogre::Vector3 gGravity(0, -9.8f, 0);        

	extern Ogre::Real gFreelookMouseSpeed;
    extern Ogre::Real gMouseSensitivity;

	// default orientation vectors
    const Ogre::Vector3 gForward(Ogre::Vector3(1, 0, 0));

	// default orientation vectors
    const Ogre::Vector3 gForwardZ(Ogre::Vector3(0, 0, 1));

	int charToInt(const char* c);
	float charToFloat(const char* c);
	std::string intToString(int num);
	std::string doubleToString(double num);

	CEGUI::MouseButton ConvertButton(OIS::MouseButtonID buttonId);

}

#endif
