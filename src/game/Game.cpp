#include "Game.hpp"

using namespace std;

Game::Game(){
}	

Game::Game(mutex& coutMutex){
	voice.startHaunting(coutMutex);
}

string Game::init(){
	prepInventory();
	for (int i=0;i<7;i++){
		questStatus [i] = false;
	}
	return changeScene("StudioApt");

}

void Game::prepInventory(){
	for (int i=0;i<10;i++){
		inventory[i].status = Status::inaccessible;
	}
	inventory[GLOVES].id="000000";
	inventory[GLOVES].name="gloves";
	inventory[JACKET].id="000001";
	inventory[JACKET].name="jacket";
	inventory[PANTS].id="000002";
	inventory[PANTS].name="pants";
	inventory[SHIRT].id="000003";
	inventory[SHIRT].name="shirt";
	inventory[SHOES].id="000004";
	inventory[SHOES].name="shoes";
	inventory[PB].id="000006";
	inventory[PB].name="pb";
	inventory[JELLY].id="000007";
	inventory[JELLY].name="jelly";
	inventory[BREAD].id="000008";
	inventory[BREAD].name="bread";
	inventory[KEYS].id="000010";
	inventory[KEYS].name="keys";
}

string Game::checkInventory(){
	string retVal ="";
	bool isFirst = true;
	
	for (int i=0; i<10; i++){
		if (inventory[i].status==Status::available){
			if (isFirst){
				isFirst = false;
			}else{
				retVal+=", ";
			}
			retVal+=inventory[i].name;
		}
	}

	if (isFirst){
		retVal = "Your inventory is empty.";
	}else{
		retVal = "Your inventory consists of "+retVal+".";

		auto pos = retVal.find_last_of(',');
		if (pos!=string::npos){
			retVal.insert(pos+1, " and");

		}
	}

	return retVal;
	
}

std::string Game::addToInventory(string addMe){
	Json * retVal = Json::toJSONObj("{\"id\":\"-1\",\"scene\":\""+currScene->getName()+"\",\"textResponse\":\"You have no room for this in your inventory.\",\"updatedInventory\":false}");
	for (int i=0; i<10; i++){
		if (addMe == inventory[i].name){
			inventory[i].status = Status::available;
			retVal->addStringValue("textResponse", "The "+addMe+" was added to your inventory.");
		}
	}
	
	return retVal->toString();
}

bool Game::isInInventory(vector<string>& words){
	if (words[1]=="peanut"&& words[2]=="butter" && inventory[PB].status ==Status::available){
		return true;
	}else if (words[1]=="grape"&& words[2]=="jelly" && inventory[JELLY].status ==Status::available){
		return true;
	}else if (words[1]=="jeans" && inventory[PANTS].status==Status::available){
		return true;
	}else if (words[1]=="loaf" && inventory[BREAD].status==Status::available){
		return true;
	}

	for (int i=0;i<10;i++){
		if (words[1]==inventory[i].name && inventory[i].status==Status::available){
			return true;
		}
	}

	return false;
}

string Game::describeInventoryItem(vector<string>& words){
	if (words[1]=="pb"||(words[1]=="peanut"&& words[2]=="butter")){
		return "It's organic peanut butter. Then, you asked yourself: is it pronounced gif or gif?";	
	}else if (words[1]=="jelly"||(words[1]=="grape"&& words[2]=="jelly")){
		return "It's grape jelly and it's organic.";
	}else if (words[1]=="loaf"||words[1]=="bread"){
		return "The loaf is already halfway consumed. No molds.";
	}else if (words[1]=="pants"||words[1]=="jeans"){
		return "The radiator dried it well. The pants is size 6, your size.";
	}else if (words[1]=="shirt"){
		return "The radiator dried it well. The shirt is white. Nothing written on it.";
	}else if (words[1]=="keys"){
		return "On the same key ring are the car key and a bunch of other keys which you assume are the apartment's keys.";
	}else if (words[1]=="gloves"){
		return "The radiator dried it well. The gloves is black. It's designed to work on celphone screens.";
	}

	return "";
	
}
string Game::wearClothes(vector<string>& words){
	if (words[1]=="shirt"){
		if (inventory[SHIRT].status!=Status::available){
			return "You can't wear something you don't have";
		}
		inventory[SHIRT].status=Status::alreadyTaken;
		questStatus[WEARSHIRT] = true;
		return "You put on the shirt. You made sure it wasn't backwards.";
	}else if (words[1]=="pants" || words[1]=="jeans"){
		if (inventory[PANTS].status!=Status::available){
			return "You can't wear something you don't have";
		}
		inventory[PANTS].status=Status::alreadyTaken;
		questStatus[WEARPANTS] = true;
		return "The pants fit you nicely. You didn't even need to struggle even if the pants are skinny jeans.";
	}else if (words[1]=="gloves"){
		if (inventory[GLOVES].status!=Status::available){
			return "You can't wear something you don't have";
		}
		inventory[GLOVES].status=Status::alreadyTaken;
		questStatus[WEARGLOVES] = true;
		return "The gloves slid in smoothly in your hands. You are guilty. Where's your Bronco?";
	}else if (words[1]=="jacket" || words[1]=="coat" || (words[1]=="winter"&& (words[2]=="jacket" || words[2]=="coat"))){
		if (inventory[JACKET].status!=Status::available){
			return "You can't wear something you don't have";
		}
		inventory[JACKET].status=Status::alreadyTaken;
		questStatus[WEARJACKET] = true;
		return "The jacket is heavy, definitely ready for winter.";
	}else if (words[1]=="shoes" || words[1]=="boots" || (words[1]=="winter"&& (words[2]=="shoes" || words[2]=="boots"))){
		if (inventory[SHOES].status!=Status::available){
			return "You can't wear something you don't have";
		}
		inventory[SHOES].status=Status::alreadyTaken;
		questStatus[WEARSHOES] = true;
		return "The boots was comfy inside despite its rugged appearance.";
	}else if (words[1]=="jelly"||words[1]=="pb"||words[1]=="keys"||words[1]=="bread"){
		return "You can't wear that. You have a different fashion sense.";
	}

	return "You can't wear something you don't have";

}

string Game::eatItem(vector<string>& words){
	if (words[1]=="pb"||(words[1]=="peanut"&& words[2]=="butter")){
	       if(inventory[PB].status !=Status::available){
			return "You can't eat something you don't have";
	       }
	       inventory[PB].status=Status::alreadyTaken;
	       questStatus[EATFOOD]= true;
	       return "You used your finger to eat the peanut butter. Yum!";

	}else if (words[1]=="jelly" || (words[1]=="grape"&& words[2]=="jelly")){
	       if(inventory[JELLY].status !=Status::available){
			return "You can't eat something you don't have";
	       }
	       questStatus[EATFOOD]= true;
	       inventory[JELLY].status=Status::alreadyTaken;
	       return "The jelly flowed from the jar into your mouth. Yum!";
	}else if (words[1]=="bread" || words[1]=="loaf"){
	       if(inventory[BREAD].status !=Status::available){
			return "You can't eat something you don't have";
	       }
	       questStatus[EATFOOD]= true;
	       inventory[BREAD].status=Status::alreadyTaken;
	       return "You took a slice of bread and chomped it. Yum!";
	}else if (words[1]=="shirt"||words[1]=="jeans"||words[1]=="keys"||words[1]=="gloves"){
		return "Would you dare eat that?";
	}
	return "You can't eat something you don't have";

}

string Game::changeScene(string newScene){
	Json * retVal = Json::toJSONObj("{\"id\":\"-1\",\"scene\":\"\",\"textResponse\":\"You are not sure what that means.\",\"updatedInventory\":false}");
	if (newScene == "StudioApt"){
		currScene = &studioApt;
	}else if (newScene == "Bathroom"){
		currScene = &bathroom;
	}else if (newScene == "Kitchen"){
		currScene = &kitchen;
	}else{
		return retVal->toString();
	}

	currSceneStr = newScene;

	retVal->addStringValue("textResponse" , currScene->getIntro());
	retVal->addStringValue("scene", currScene->getName());
	return retVal->toString();
}

string Game::processCommand(string phrase){
	Json * retVal = Json::toJSONObj("{\"id\":\"-1\",\"scene\":\""+currScene->getName()+"\",\"textResponse\":\"\",\"updatedInventory\":false}");
	//cout<<"INPUT: "<<phrase<<endl;

	if (phrase=="exit"||phrase=="quit"){
		retVal->addStringValue("textResponse","The game is exiting.");
		return retVal->toString();
	}

	Vocab translator;
	vector<string> words = translator.inOtherWords(phrase);
	if (words[0]=="check" && words[1]=="inventory"){
		retVal->addStringValue("textResponse",checkInventory());
		return retVal->toString();
	}else if (words[0]=="look" && isInInventory(words)){
		retVal->addStringValue("textResponse",describeInventoryItem(words));
		return retVal->toString();
	}else if (words[0]=="wear"){
		retVal->addStringValue("textResponse",wearClothes(words));
		return retVal->toString();
	}else if (words[0]=="eat"){
		retVal->addStringValue("textResponse",eatItem(words));
		return retVal->toString();
	}else if(currSceneStr=="StudioApt"){
		return processCommandInStudioApt(words);
	}else if(currSceneStr=="Bathroom"){
		return processCommandInBathroom(words);
	}else if(currSceneStr=="Kitchen"){
		return processCommandInKitchen(words);
	}

	retVal->addStringValue("textResponse","You are not sure what that means.");
	return retVal->toString();
}

string Game::processCommandInStudioApt(vector<string>& words){
	Json * retVal = Json::toJSONObj("{\"id\":\"-1\",\"scene\":\""+currScene->getName()+"\",\"textResponse\":\"\",\"updatedInventory\":false}");
	
	//cout<<"OUTPUT: "<<endl;
	if (words.size()==0){
		//cout<<"You are not sure what that means."<<endl;
		retVal->addStringValue("textResponse","You are not sure what that means.");
		return retVal->toString();
	}else{
		/*for (auto i=0; i<words.size(); i++){
			cout<<words[i]<<endl;
		}*/

		if (words[0]=="walk"){
			if (words.size()==2){
				if (words[1]=="bathroom"){
					return changeScene("Bathroom");
				}else if (words[1]=="kitchen"){
					return changeScene("Kitchen");
				}else if (words[1]=="out"){
					retVal->addStringValue("textResponse","You are not ready.");
					return retVal->toString();
				}else if (((words[1] =="office" && words[2]=="desk")|| words[1]=="desk")|| (words[1]=="sound"|| (words[1]=="next" && words[2]=="desk"))){
					retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
					return retVal->toString();
				}
					
			}
		}else if (words[0]=="look"){
			if (words[1]=="inventory"){
				retVal->addStringValue("textResponse",checkInventory());
				return retVal->toString();
			}else{
				retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
				return retVal->toString();
			}
		}else if (words[0]=="grab"){
			if (words[1]=="jeans"||words[1]=="pants"){
				if(currScene->grabItem("pants")==Status::available){
					return addToInventory("pants");
				}
			}else if (words[1]=="shirt"){
				if(currScene->grabItem("shirt")==Status::available){
					return addToInventory("shirt");
				}
			}else if (words[1]=="keys"){
				if(currScene->grabItem("keys")==Status::available){
					questStatus[GETKEYS] = true;
					return addToInventory("keys");
				}
			}else if (words[1]=="jacket" || words[1]=="coat" || (words[1]=="winter"&& (words[2]=="jacket" || words[2]=="coat"))){
				if(currScene->grabItem("jacket")==Status::available){
					return addToInventory("jacket");
				}
			}else if (words[1]=="shoes" || words[1]=="boots" || (words[1]=="winter"&& (words[2]=="shoes" || words[2]=="boots"))){
				if(currScene->grabItem("shoes")==Status::available){
					return addToInventory("shoes");
				}
			}else if (words[1]=="laptop"||words[1]=="pen"||words[1]=="multipen"||words[1]=="mug"||words[1]=="notebook"){
				retVal->addStringValue("textResponse","You liked your desk setup. You don't want to disturb it.");
				return retVal->toString();				

			}
			retVal->addStringValue("textResponse","I didn't notice any "+words[1]+".");
			return retVal->toString();

		}else if (words[0]=="open" && (words[1]=="closet"||words[1]=="cabinet")){
			retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
			return retVal->toString();
		}else if (words[0]=="break"){
			retVal->addStringValue("textResponse","You wouldn't dare.");
			return retVal->toString();
		}
	}

	retVal->addStringValue("textResponse","You are not sure what that means.");
	return retVal->toString();
}

string Game::processCommandInBathroom(vector<string>& words){
	Json * retVal = Json::toJSONObj("{\"id\":\"-1\",\"scene\":\""+currScene->getName()+"\",\"textResponse\":\"\",\"updatedInventory\":false}");

	//cout<<"OUTPUT: "<<endl;
	if (words.size()==0){
		retVal->addStringValue("textResponse","You are not sure what that means.");
		return retVal->toString();
	}else{
		/*for (auto i=0; i<words.size(); i++){
			cout<<words[i]<<endl;
		}*/

		if (words[0]=="walk"){
			if (words.size()==2){
				if (words[1]=="bedroom"||words[1]=="main"||words[1]=="out"){
					return changeScene("StudioApt");
				}else if (words[1]=="kitchen"){
					return changeScene("Kitchen");
				}else if (words[1] =="radiator"){
					retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
					return retVal->toString();
				}
			}
		}else if (words[0]=="look"){
			if (words[1]=="inventory"){
				retVal->addStringValue("textResponse",checkInventory());
				return retVal->toString();
			}else{
				retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
				return retVal->toString();
			}
		}else if (words[0]=="grab"){
			if (words[1]=="gloves"){
				if(currScene->grabItem("gloves")==Status::available){
					return addToInventory("gloves");
				}
			}
			retVal->addStringValue("textResponse","I didn't notice any "+words[1]+".");
			return retVal->toString();
		}else if (words[0]=="open" && words[1]=="toilet"){			
			retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
			return retVal->toString();
		}else if (words[0]=="break"){
			retVal->addStringValue("textResponse","You wouldn't dare.");
			return retVal->toString();
		}
	}
	retVal->addStringValue("textResponse","You are not sure what that means.");
	return retVal->toString();
}

string Game::processCommandInKitchen(vector<string>& words){
	Json * retVal = Json::toJSONObj("{\"id\":\"-1\",\"scene\":\""+currScene->getName()+"\",\"textResponse\":\"\",\"updatedInventory\":false}");

	//cout<<"OUTPUT: "<<endl;
	if (words.size()==0){
		retVal->addStringValue("textResponse","You are not sure what that means.");
		return retVal->toString();
	}else{
		/*for (auto i=0; i<words.size(); i++){
			cout<<words[i]<<endl;
		}*/

		if (words[0]=="walk"){
			if (words.size()==2){
				if (words[1]=="bathroom"){
					return changeScene("Bathroom");
				}else if (words[1]=="bedroom"||words[1]=="main"||words[1]=="out"){
					return changeScene("StudioApt");
				}else if ((words[1] =="office" && words[2]=="desk")|| words[1]=="desk")	{
					retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
					return retVal->toString();
				}
			}
		}else if (words[0]=="look"){
			if (words[1]=="inventory"){
				retVal->addStringValue("textResponse",checkInventory());
				return retVal->toString();
			}else{
				retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
				return retVal->toString();
			}
		}else if (words[0]=="grab"){
			if (words[1]=="loaf"||words[1]=="bread"){
				if(currScene->grabItem("bread")==Status::available){
					return addToInventory("bread");
				}
			}else if (words[1]=="jelly"||(words[1]=="grape"&& words[2]=="jelly")){
				if(currScene->grabItem("jelly")==Status::available){
					return addToInventory("jelly");
				}
			}else if (words[1]=="pb"||(words[1]=="peanut"&& words[2]=="butter")){
				if(currScene->grabItem("pb")==Status::available){
					return addToInventory("pb");
				}
			}
			retVal->addStringValue("textResponse","I didn't notice any "+words[1]+".");
			return retVal->toString();
		}else if (words[0]=="open" && words[1]=="fridge"){
			retVal->addStringValue("textResponse",currScene->lookAtSomething(words));
			return retVal->toString();
		}else if (words[0]=="break"){
			retVal->addStringValue("textResponse","You wouldn't dare.");
			return retVal->toString();
		}
	}
	retVal->addStringValue("textResponse","You are not sure what that means.");
	return retVal->toString();

}

bool Game::isGameObjectivesReached(){
	for (int i=0;i<7;i++){
		if (!questStatus[i]){
			return false;
		}
	}
	
	return true;
}

std::string Game::endGame(){
	string endWords = "You opened the door. A blizzard is definitely afoot. Strong winds with heavy snow going down. Regardless you are now awake. The weather condition doesn't deter you. You start walking to your truck. The snow is up to your knees. You slowly make your way. In your mind, you have to reach the Maker and you will drive there even if it's the last thing you do alive. You are now awake. You continue trudging in the snow. Suddenly, you don't feel the force of the snow on your knees. You are flying! You looked down and see your tiny house getting smaller and smaller. You have reached your Maker.";

	return "{\"id\":\"-1\",\"scene\":\""+currScene->getName()+"\",\"textResponse\":\""+endWords+"\",\"updatedInventory\":false}";

}
