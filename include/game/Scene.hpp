#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Item.hpp"

#define KEYS 0
#define JACKET 1
#define SHOES 2
#define SHIRT 3
#define PANTS 4
#define GLOVES 5
#define JELLY 6
#define PB 7
#define BREAD 8
#define SOUND 9

enum class Result {success, fail};

class Scene{

	protected:
		Item items[10];
		std::string name = "Unknown scene";
		bool alreadyVisited;

	public:
	       	virtual std::string getIntro()=0;
		virtual std::string lookAtSomething (std::vector<std::string>&)=0;
		Status grabItem(std::string);
		std::string getName ();
		Scene();
		
};

#endif
