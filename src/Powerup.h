#ifndef POWERUP_H_
#define POWERUP_H_

#include "gamestates.h"

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
		void applyDamage(Ogre::Real dmg)			{ }
		virtual void playCollideSound()				{ MusicManager::getInstance()->playSound(laser_powerup); }

	private:

		void init();

	protected:

		void applyPowerupEffect();

	};

}

#endif
