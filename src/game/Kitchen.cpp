#include "Kitchen.hpp"

using namespace std;

Kitchen::Kitchen(){
	for (int i=0;i<10;i++){
		items[i].status = Status::inaccessible;
	}

	items[PB].id="200000";
	items[PB].name="pb";
	items[JELLY].id="200001";
	items[JELLY].name="jelly";
	items[BREAD].id="200002";
	items[BREAD].name="bread";
	items[BREAD].status = Status::available;
}

string Kitchen::getIntro(){
	return " The kitchen might be tiny but you have a fridge, stove with oven and a microwave. A loaf of bread in plastic was on the counter. Everything was wiped clean. No crumbs or smudges anywhere.";
}

std::string Kitchen::lookAtSomething (std::vector<std::string>& command){
	if (command.size()==1){
		return getIntro();
	}else if (command[1]=="fridge"){
		items[PB].status = Status::available;
		items[JELLY].status = Status::available;
		return "The fridge is clean though it was empty except for a bottle of peanut butter and a bottle of jelly"; 		
	}else if ((command[1]=="jelly"||(command[1]=="grape"&&command[2]=="jelly")) && items[JELLY].status == Status::available){
		return "It's grape jelly and it's organic.";
	}else if (((command[1]=="peanut" && command[2]=="butter")||command[1]=="pb") && items[PB].status == Status::available){
		return "It's organic peanut butter. Then, you asked yourself: is it pronounced gif or gif?";	
	}else if (command[1]=="loaf"||command[1]=="bread"){
		return "The loaf is already halfway consumed. No molds.";
	}else if (command[1]=="stove"||command[1]=="oven"||command[1]=="microwave"||command[1]=="cabinet"||command[1]=="cupboard"){
		return "They are clean. They seem to say please don't touch.";
	}
	return "Where are you looking at?";
}
