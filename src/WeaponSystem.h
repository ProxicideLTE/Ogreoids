#ifndef WEAPONSYSTEM_H_
#define WEAPONSYSTEM_H_

namespace ogreoids {

	/**
	 * Class for the weapon system that the ship will use.
	 */
	class WeaponSystem {

		// Instance variables.
		unsigned										soundFile;

		Ogre::Real										dmg;
		Ogre::Real										lifeSpan;
		Ogre::String									meshProjectile;

		std::vector<Ogre::SceneNode*>					output;

	public:

		WeaponSystem();
		virtual ~WeaponSystem();

		// Getters.
		unsigned getSoundFile()							{ return soundFile; }
		Ogre::Real getLifeSpan()						{ return lifeSpan; }
		Ogre::Real getDamage()							{ return dmg; }
		Ogre::String getMesh()							{ return meshProjectile; }
		std::vector<Ogre::SceneNode*> getOutput()		{ return output; }

		// Setters.
		void setSoundFile(unsigned i)					{ soundFile = i; }
		void setLifeSpan(Ogre::Real lifeSpan)			{ this->lifeSpan = lifeSpan; }
		void setSystemDamage(Ogre::Real dmgAmt)			{ dmg = dmgAmt; }
		void setProjectileMesh(Ogre::String mesh)		{ meshProjectile = mesh; }
		void addOutput(Ogre::SceneNode* p)				{ output.push_back(p); }

	};

}

#endif