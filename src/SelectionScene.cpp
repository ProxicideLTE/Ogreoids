#include "stdafx.h"

#include "SelectionScene.h"
#include "gamestates.h"
#include "tinyxmls.h"

namespace ogreoids {

	// Initialize static variables.
	const char*	SelectionScene::filename = "data/aircrafts.ogreoid";
	Ogre::Degree SelectionScene::rotSpeed = Ogre::Degree(10);
	
	/**
	 * SelectionScene constructor.
	 */
	SelectionScene::SelectionScene() 
		: mSceneMgr(SelectionMenuState::getInstance()->getSceneManager())
		, mSceneNode(NULL)
	{
		initialize();
	}

	/**
	 * SelectionScene destructor.
	 */
	SelectionScene::~SelectionScene() {
		for (unsigned i = 0; i < aircrafts.size(); i++)
			delete aircrafts[i];
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * Setup the scene.
	 */	
	void SelectionScene::initialize() {
		
		// Setup the scene node.
		mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		index = 0;

		// Parse XML file to get the details on the available aircrafts.
		TiXmlDocument doc;

		// Determine if the XML file exists.
		if (!doc.LoadFile(filename)) {
			std::exception("XML Error: aircrafts.xml is missing.");
		}

		// Determine if the document has a root element.
		TiXmlElement* root = doc.FirstChildElement();

		if (root == NULL) {
			std::exception("XML Error: No root element in aircrafts.xml");
			doc.Clear();
		}

		// Begin loop.
		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

			// Grab the element name.
			std::string elemName = elem->Value();
			
			// Load each aircraft.
			if (elemName == "aircraft") {

				// Grab element's information.
				std::string name = elem->Attribute("name");
				std::string mesh = elem->Attribute("mesh");
				std::string file = elem->Attribute("tag");
				std::string desc = elem->GetText();

				Aircraft* ship = new Aircraft(name, mesh, desc);
				ship->setFileName(file);
				aircrafts.push_back(ship);

			}

		}

		// Create the mesh and attach it to the scene node.
		Ogre::Entity* shipMesh = mSceneMgr->createEntity(aircrafts[0]->getMeshName());
		mSceneNode->attachObject(shipMesh);

	}


// =====================================================================================
//
// #Update/Render
//
// =====================================================================================

	/**
	 * This function updates the scene.
	 *
	 * @param deltaT					time since last frame
	 *
	 */
	void SelectionScene::update(Ogre::Real deltaT) {
		mSceneNode->yaw(rotSpeed * deltaT);
	}


// =====================================================================================
//
// #Switching
//
// =====================================================================================

	/**
	 * This function will load the next aircraft in the list.
	 */
	void SelectionScene::loadNext() {
		
		// Play sound.
		MusicManager::getInstance()->playSound(selection);

		// Reset and remove the entity.
		mSceneNode->detachAllObjects();

		// Load the next ship.
		unsigned next = (index + 1) % aircrafts.size();
		index = next;

		// Create the mesh and attach it to the scene node.
		Ogre::Entity* shipMesh = mSceneMgr->createEntity(aircrafts[next]->getMeshName());
		mSceneNode->attachObject(shipMesh);

	}

	/**
	 * This function will load the previous aircraft in the list.
	 */
	void SelectionScene::loadPrevious() {

		// Play sound.
		MusicManager::getInstance()->playSound(selection);

		// Reset and remove the entity.
		unsigned back;
		mSceneNode->detachAllObjects();

		// Load the next ship.
		if (index == 0) 
			back = aircrafts.size() - 1;
		
		else 
			back = (index - 1) % aircrafts.size();

		index = back;
		std::cout << index << std::endl;

		// Create the mesh and attach it to the scene node.
		Ogre::Entity* shipMesh = mSceneMgr->createEntity(aircrafts[back]->getMeshName());
		mSceneNode->attachObject(shipMesh);
	}


// =====================================================================================
//
// #Aircraft Class
//
// =====================================================================================

	/**
	 * Aircraft constructor.
	 *
	 * @param aircraftName				name of the aircraft
	 * @param meshName					mesh file name to use
	 * @param description				description of the aircraft
	 *
	 */
	Aircraft::Aircraft(Ogre::String aircraftName, Ogre::DisplayString meshName, Ogre::DisplayString description) 
		: aircraftName(aircraftName)
		, meshName(meshName)
		, description(description)
	{

	}

}
