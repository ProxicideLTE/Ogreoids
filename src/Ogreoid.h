#ifndef OGREOID_H_
#define OGREOID_H_

namespace ogreoids {
	
	class Ogreoid : public Obstacle {

	protected:

		Ogre::Real					lifeSpan;

	public:

		Ogreoid(Ogre::Vector3 pos);
		~Ogreoid();

		void update(Ogre::Real deltaT);

	private:

		void init();

	};

}

#endif
