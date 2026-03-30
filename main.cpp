#include<iostream>
#include "include/game/Game.hpp"
#include "include/json/Json.hpp"
#include <string>
#include <exception>

using namespace std;

void processResponse(string response);

mutex coutMutex;

int main(){

	Game  * obj = new Game(coutMutex);

	processResponse(obj->init());
	
	string command="";
	string previousCommand="";
	while (command!="exit" && command!="quit"){
		cout<<endl<<endl<<"What is your next move?"<<endl;
		char charCmd = getchar ();
		
		if (charCmd=='m'){
			cout<<"test\n";
		}

		previousCommand = command;
		getline(cin,command);
		command = charCmd + command;
		processResponse(obj->processCommand(command));
		if (obj->isGameObjectivesReached()){
			processResponse(obj->endGame());
			
			cout<<"\nTHE END\n";

			break;
		}
	}

	return 0;
}

void processResponse (string response){
	unique_lock {coutMutex};
	if (response.compare("error")==0){
		cout<<"You are not sure what that means."<<endl;
	}else{
		try{
			Json * resJson = Json::toJSONObj(response);
			cout<<resJson->getStringValue("textResponse")<<endl;
		}catch (exception err){
			cout<<err.what()<<"\n";
			cout<<"Encountered a problem. Terminating program."<<"\n";
			exit(-1);
		}
	}
}
