#include "stdafx.h"

#include "Player.h"
#include "gamestates.h"
#include "tinyxmls.h"
#include "SelectionScene.h"
#include "GlobalVariables.h"
#include "Game.h"
#include "Level.h"
#include "Projectile.h"
#include "WeaponSystem.h"

namespace ogreoids {

	// Initialize static variables.
	const char*	Player::filename = "data/vechicles/stats.ogreoid";
	Ogre::Real Player::maxHeight = 60; 
	Ogre::Real Player::maxWidth = 60; 
	Ogre::Real Player::camDist = 225;
	Ogre::Degree Player::rollSpeed = Ogre::Degree(45);
	Ogre::Degree Player::maxYaw = Ogre::Degree(45);
	Ogre::Degree Player::maxPitch = Ogre::Degree(45);

	/**
	 * Player constructor.
	 */
	Player::Player(Level* l) 
		: mSceneMgr(GameplayState::getInstance()->getSceneManager())
		, level(l)
	{
		setupModel();
		setupStats();
		setupSystems();
	}

	/**
	 * Player destructor.
	 */
	Player::~Player() {

		for (unsigned i = 0; i < sceneNodes.size(); i++) {
			sceneNodes[i]->detachAllObjects();
			mSceneMgr->destroySceneNode(sceneNodes[i]);
		}
		
		for (unsigned i = 0; i < meshes.size(); i++)
			mSceneMgr->destroyEntity(meshes[i]);

		for (unsigned i = 0; i < weaponSystems.size(); i++)
			delete weaponSystems[i];

	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * This function will setup the model for the player depending on which aircraft was chosen.
	 */
	void Player::setupModel() {

		Aircraft* a = GameplayState::getInstance()->getSelectedAircraft();

		// Create scene node and attach an entity to it.
		mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mesh = mSceneMgr->createEntity(a->getMeshName());
		mSceneNode->attachObject(mesh);
		mSceneNode->setPosition(0,-10,0);
		mSceneNode->setFixedYawAxis(true);
		sceneNodes.push_back(mSceneNode);
		meshes.push_back(mesh);

		// Create a scene node for the camera.
		mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mCameraNode->attachObject(GameplayState::getInstance()->getGameplayCam());
		mCameraNode->setPosition(0,0,-camDist);
		sceneNodes.push_back(mCameraNode);

		// Node for the target.
		mTarget = mSceneNode->createChildSceneNode();
		mTarget->setPosition(0,0,250);
		target = mSceneMgr->createEntity("target.mesh");
		mTarget->attachObject(target);
		sceneNodes.push_back(mTarget);
		meshes.push_back(target);

		Ogre::SceneNode* farTargetNode = mSceneNode->createChildSceneNode();
		farTargetNode->setPosition(0,0,500);
		Ogre::Entity* fTarget = mSceneMgr->createEntity("target.mesh");
		farTargetNode->attachObject(fTarget);
		sceneNodes.push_back(farTargetNode);
		meshes.push_back(fTarget);

	}

	/**
	 * This function will initialize the player stats.
	 */
	void Player::setupStats() {

		Aircraft* a = GameplayState::getInstance()->getSelectedAircraft();

		// Parse XML file to get the details on the available aircrafts.
		TiXmlDocument doc;

		// Determine if the XML file exists.
		if (!doc.LoadFile(filename)) {
			std::exception("XML Error: Aircraft XML file is missing.");
		}

		// Determine if the document has a root element.
		TiXmlElement* root = doc.FirstChildElement();

		if (root == NULL) {
			std::exception("XML Error: No root element in Aircraft XML file is missing.");
			doc.Clear();
		}

		// Begin loop.
		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

			// Grab the element name.
			std::string elemName = elem->Value();
			
			// Load the ship's stats.
			if (elemName == a->getElemName()) {

				// Grab element's information.
				hp = charToFloat(elem->Attribute("hp"));
				speed = charToFloat(elem->Attribute("speed"));
				yawSpeed = Ogre::Degree(charToFloat(elem->Attribute("turnSpeed")));
				pitchSpeed = Ogre::Degree(charToFloat(elem->Attribute("turnSpeed")));

			}

		}

	}

	/**
	 * This function will initialize the weapon systems.
	 */
	void Player::setupSystems() {
		
		// Side wings.
		Ogre::SceneNode* leftWing = mSceneNode->createChildSceneNode();
		leftWing->setPosition(-20,0,0);
		sceneNodes.push_back(leftWing);
		Ogre::SceneNode* rightWing = mSceneNode->createChildSceneNode();
		rightWing->setPosition(20,0,0);
		sceneNodes.push_back(rightWing);

		//============================================================================================

		// 1 cannon - default weapon system.
		WeaponSystem* ws1 = new WeaponSystem();
		ws1->setProjectileMesh("g_laser.mesh");
		ws1->addOutput(mSceneNode);
		ws1->setSystemDamage(20);
		ws1->setLifeSpan(1.0f);
		weaponSystems.push_back(ws1);

		// 2 cannons on the wings.
		WeaponSystem* ws2 = new WeaponSystem();
		ws2->setProjectileMesh("g_laser.mesh");
		ws2->addOutput(leftWing);
		ws2->addOutput(rightWing);
		ws2->setSystemDamage(20);
		ws2->setLifeSpan(0.75f);
		weaponSystems.push_back(ws2);

		// 2 cannons on the wings.
		WeaponSystem* ws3 = new WeaponSystem();
		ws3->setProjectileMesh("b_laser.mesh");
		ws3->addOutput(leftWing);
		ws3->addOutput(rightWing);
		ws3->setSystemDamage(40);
		ws3->setLifeSpan(0.75f);
		weaponSystems.push_back(ws3);

		// 3 cannons, 1 center 2 on the wings.
		WeaponSystem* ws4 = new WeaponSystem();
		ws4->setProjectileMesh("b_laser.mesh");
		ws4->addOutput(mSceneNode);
		ws4->addOutput(leftWing);
		ws4->addOutput(rightWing);
		ws4->setSystemDamage(40);
		ws4->setLifeSpan(0.5f);
		weaponSystems.push_back(ws4);

		// Set default weapon system.
		currentWeaponSystem = ws4;

	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the player.
	 *
	 * @param deltaT					time since last frame
	 *
	 */
	void Player::update(Ogre::Real deltaT) {
		updateVehicle(deltaT);
		updateCamera(deltaT);
	}

	/**
	 * Update the player.
	 */
	void Player::updateVehicle(Ogre::Real deltaT) {

		// Variables to imply 2d movement.
		OIS::Keyboard* kb = Game::getInstance()->getKeyboard();
		Ogre::Real hDirection, vDirection = 0;
		bool shouldMoveSideways = false;
		bool shouldMoveVertically = false;
		bool lock = false;

		// Side movement.
		if (kb->isKeyDown(OIS::KC_A)) {
			shouldMoveSideways = true;
			hDirection = 1;
		}

		if (kb->isKeyDown(OIS::KC_D)) {
			shouldMoveSideways = true;
			hDirection = -1;
		}

		if (shouldMoveSideways == true) {
			mSceneNode->yaw(yawSpeed * deltaT * hDirection);
			mSceneNode->roll(rollSpeed * deltaT * -hDirection);
		}

		// Vertical movement.
		if (kb->isKeyDown(OIS::KC_W)) {
			shouldMoveVertically = true;
			vDirection = 1;
		}

		if (kb->isKeyDown(OIS::KC_S)) {
			shouldMoveVertically = true;
			vDirection = -1;
		}

		if (shouldMoveVertically == true) {
			mSceneNode->pitch(pitchSpeed * deltaT * vDirection);
		}

		// Move the ship.
		Ogre::Vector3 disp = mSceneNode->getOrientation() * (mSceneNode->getPosition().UNIT_Z * speed * deltaT);
		mSceneNode->translate(disp);

		// Dont move the ship if the ship is going off camera.
		if (mSceneNode->getPosition().x > maxWidth && mSceneNode->getPosition().y > maxHeight)				mSceneNode->setPosition(maxWidth, maxHeight, mSceneNode->getPosition().z);
		else if (mSceneNode->getPosition().x > maxWidth && mSceneNode->getPosition().y < -maxHeight)		mSceneNode->setPosition(maxWidth, -maxHeight, mSceneNode->getPosition().z);
		else if (mSceneNode->getPosition().x < -maxWidth && mSceneNode->getPosition().y > maxHeight)		mSceneNode->setPosition(-maxWidth, maxHeight, mSceneNode->getPosition().z);
		else if (mSceneNode->getPosition().x < -maxWidth && mSceneNode->getPosition().y < -maxHeight)		mSceneNode->setPosition(-maxWidth, -maxHeight, mSceneNode->getPosition().z);
		
		else if (mSceneNode->getPosition().x > maxWidth)													mSceneNode->setPosition(maxWidth, mSceneNode->getPosition().y, mSceneNode->getPosition().z);
		else if (mSceneNode->getPosition().x < -maxWidth)													mSceneNode->setPosition(-maxWidth, mSceneNode->getPosition().y, mSceneNode->getPosition().z);
		else if (mSceneNode->getPosition().y > maxHeight)													mSceneNode->setPosition(mSceneNode->getPosition().x, maxHeight, mSceneNode->getPosition().z);
		else if (mSceneNode->getPosition().y < -maxHeight) 													mSceneNode->setPosition(mSceneNode->getPosition().x, -maxHeight, mSceneNode->getPosition().z);

		// Restore balance to the ship.
		Ogre::Real rollBalance = mSceneNode->getOrientation().getRoll().valueDegrees();
		Ogre::Real yawBalance = mSceneNode->getOrientation().getRoll().valueDegrees();
		Ogre::Real pitchBalance = mSceneNode->getOrientation().getRoll().valueDegrees();
		mSceneNode->roll(Ogre::Degree(-rollBalance) * deltaT * 2.15f);
		mSceneNode->yaw(Ogre::Degree(-yawBalance) * deltaT * 2.15f);
		mSceneNode->pitch(Ogre::Degree(-pitchBalance) * deltaT * 2.15f);

	}

	/**
	 * Update the camera.
	 */
	void Player::updateCamera(Ogre::Real deltaT) {

		Ogre::Real diff = (mSceneNode->getPosition() - mCameraNode->getPosition()).length();

		// If the ship is to close to the camera pan back.
		if (diff > camDist) {
			Ogre::Vector3 disp = Ogre::Vector3::UNIT_Z * speed * deltaT;
			mCameraNode->translate(disp);
		}

	}


// =====================================================================================
//
// #Event Callbacks
//
// =====================================================================================

	/**
	 * This function will handle all keyboard events, when the user strikes any key.
	 */
	bool Player::keyPressed(const OIS::KeyEvent& arg) {

		if (OIS::KC_1 == arg.key)				currentWeaponSystem = weaponSystems[0];
		else if (OIS::KC_2 == arg.key)			currentWeaponSystem = weaponSystems[1];
		else if (OIS::KC_3 == arg.key)			currentWeaponSystem = weaponSystems[2];
		else if (OIS::KC_4 == arg.key)			currentWeaponSystem = weaponSystems[3];

		return true;
	}

	/**
	 * This function will handle all keyboard events, when the user releases from any key.
	 */
	bool Player::keyReleased(const OIS::KeyEvent& arg) {
		return true;
	}

	/**
	 * This function will handle for when the mouse moves.
	 */
	bool Player::mouseMoved(const OIS::MouseEvent& arg) {
		return true;
	}

	/**
	 * This function will handle the event for when the mouse is clicked.
	 */
	bool Player::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {

		// Spawn new projectile.
		if (id == OIS::MB_Left) {

			// Shoot depending on the current weapon system.
			for (unsigned i = 0; i < currentWeaponSystem->getOutput().size(); i++) {
				Ogre::Vector3 pos = currentWeaponSystem->getOutput()[i]->_getDerivedPosition();
				Projectile* p = new Projectile(pos, currentWeaponSystem->getMesh(), currentWeaponSystem->getOutput()[i]->_getDerivedOrientation(),currentWeaponSystem->getDamage());
				p->setDuration(currentWeaponSystem->getLifeSpan());
				level->addProjectile(p);
			}

		}

		return true;
	}

	/**
	 * This function will handle the event for when the mouse is clicked is over.
	 */
	bool Player::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) {
		return true;
	}

}
