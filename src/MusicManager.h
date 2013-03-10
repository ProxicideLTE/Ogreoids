#ifndef MUSICMANAGER_H_
#define MUSICMANAGER_H_

namespace ogreoids {

	class MusicManager {

		// FMOD variables.
		FMOD_RESULT					result;
		FMOD::System*				system;

		// Music and sound collection.
		std::vector<FMOD::Sound*>		music;
		std::vector<FMOD::Sound*>		sounds;
		std::vector<FMOD::Channel*>		channels;

		// Private constructor and destructor (Singleton design pattern).
		MusicManager();
		~MusicManager();

		// Noncopyable constructor and assignment operator.
        MusicManager(const MusicManager&);
        MusicManager& operator= (const MusicManager&);

		void initialize();
		void errorCheck(const std::string& errMsg);
		void createMusic();
		void createSounds();

		inline FMOD_VECTOR OgreToFmod(const Ogre::Vector3& in) {
			// FMOD uses +x = right, +Y = up, +z = forward
			FMOD_VECTOR out = { -in.x, in.y, in.z };
			return out;
		}

		public:

			// Getters
			static MusicManager* getInstance();
			void update(Ogre::Real deltaT);
			FMOD::Channel* setAttributes(Ogre::Vector3 pos, Ogre::Vector3 vel, FMOD::Channel* channel);
			void setListenerAttributes(Ogre::Vector3 pos, Ogre::Vector3 vel, Ogre::Vector3 dir, Ogre::Vector3 up);

			void playSound(unsigned index);

	};

}

#endif