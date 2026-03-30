#include "Scene.hpp"
	
Status Scene::grabItem(std::string lookForMe){
	for (int i=0; i<10; i++){
		if(items[i].name == lookForMe && items[i].status == Status::available){
			items[i].status = Status::alreadyTaken;
			return Status::available;
		}
	}

	return Status::inaccessible;
}

std::string Scene::getName (){
	return this->name;
}

Scene::Scene(){
	Scene::alreadyVisited = false;
}
