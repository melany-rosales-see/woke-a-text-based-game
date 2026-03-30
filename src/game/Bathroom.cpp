#include "Bathroom.hpp"

using namespace std;

Bathroom::Bathroom(){
	for (int i=0;i<10;i++){
		items[i].status = Status::inaccessible;
	}

	//Gloves on top of the radiator
	items[GLOVES].id="000000";
	items[GLOVES].name="gloves";
}

string Bathroom::getIntro(){
	if (alreadyVisited){
		return "In the center stood the sink and a mirror. On the right of them is full bathtub with shower. Then, to the left is the toilet with the lid closed. You wonder if it's hiding any surprises. In front of the toilet is a radiator. Something dark colored seems to be on it.";
	}else{
		alreadyVisited = true;
		return "You entered the bathroom. In front of you is the sink and a mirror. You see your sleepy head. A full bathtub with shower is on the right. Then, to your left is the toilet with the lid closed. You wonder if it's hiding any surprises. In front of the toilet is a radiator. Something dark colored seems to be on it.";
	}

}

std::string Bathroom::lookAtSomething (std::vector<std::string>& command){
	if (command.size()==1){
		return getIntro();
	}else if (command[1]=="radiator"){
		items[GLOVES].status = Status::available;
		return "Laying on top of the radiator is a pair of black gloves.";
	}else if (command[1]=="gloves" && items[GLOVES].status == Status::available){
		return "The radiator dried it well. The gloves is black. It's designed to work on celphone screens.";
	}else if (command[1]=="toilet"){
		return "You open the toilet lid. You see foamy water. Good. You closed it again.";
	}else if (command[1]=="bathtub"||command[1]=="tub"||command[1]=="shower"){
		return "The tiles are dry. There is no soap. You can't take a shower now.";
	}else if (command[1]=="mirror"){
		return "You see your face in the mirror. Good morning, little sunshine.";
	}else if (command[1]=="sink"){
		return "The sink is bare. No tootbrush or toothpaste. Do you even live in this house?";
	}

	return "Where are you looking at?";
}
