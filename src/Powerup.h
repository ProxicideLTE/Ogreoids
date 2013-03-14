#ifndef POWERUP_H_
#define POWERUP_H_

namespace ogreoids {

	class Player;

	/**
	 * Class blueprint for all powerups that the player can pickup.
	 */
	class Powerup : public Obstacle {

		// Instance variables.
		Player*					p;

	public:

		Powerup(Player* p, Ogre::Vector3 pos);
		virtual ~Powerup();

		void update(Ogre::Real deltaT);

		// Setters.
		void setDisposable();
		void applyDamage(Ogre::Real dmg)	{ }

	private:

		void init();

	protected:

		void applyPowerupEffect();

	};

}

#endif
