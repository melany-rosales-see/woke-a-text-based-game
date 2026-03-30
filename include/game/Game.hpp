#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>

#include "Scene.hpp"
#include "Game.hpp"
#include "Vocab.hpp"
#include "Bathroom.hpp"
#include "StudioApt.hpp"
#include "Kitchen.hpp"
#include "Item.hpp"
#include "Haunting.hpp"

#include "../json/Json.hpp"

//Game objectives
#define EATFOOD 0
#define WEARSHIRT 1
#define WEARPANTS 2
#define WEARJACKET 3
#define WEARGLOVES 4
#define WEARSHOES 5
#define GETKEYS 6


class Game{
	private:

		//rooms in this game
		Bathroom bathroom;
		Kitchen kitchen;
		StudioApt studioApt;

	       	Scene * currScene = NULL;
		std::string currSceneStr = "";
		std::string changeScene(std::string);
				
		std::string processCommandInStudioApt(std::vector<std::string>&);
		std::string processCommandInBathroom(std::vector<std::string>&);
		std::string processCommandInKitchen(std::vector<std::string>&);

		//manages items stored in inventory
		Item inventory[11];
		void prepInventory();
		std::string addToInventory(std::string);
		bool isInInventory(std::vector<std::string>&);
		std::string describeInventoryItem(std::vector<std::string>&);
		std::string checkInventory();
		
		//actions
		std::string wearClothes(std::vector<std::string>&);
		std::string eatItem(std::vector<std::string>&);
		
		//determines if the game objectives have been met
		bool questStatus[7];

		//a message will pop out once in a while to haunt you
		Haunting voice;
	public:
		Game();
		Game(std::mutex&);
		std::string init();

		std::string processCommand(std::string);

		bool isGameObjectivesReached();
		std::string endGame();

};

#endif
