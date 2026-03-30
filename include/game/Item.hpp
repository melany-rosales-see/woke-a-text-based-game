#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

enum class Status {available, alreadyTaken, inaccessible};

class Item{
	public:
		std::string id;
		std::string name;
		Status status;

};

#endif
