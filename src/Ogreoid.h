#ifndef OGREOID_H_
#define OGREOID_H_

namespace ogreoids {
	
	class Level;

	class Ogreoid : public Obstacle {

	protected:

		// Instance variables.
		Level*						lvl;

		Ogre::Real					lifeSpan;

	public:

		Ogreoid(Level*l, Ogre::Vector3 pos);
		~Ogreoid();

		void update(Ogre::Real deltaT);

		// Setters.
		void applyDamage(Ogre::Real dmg);

	private:

		void init();

	};

}

#endif
