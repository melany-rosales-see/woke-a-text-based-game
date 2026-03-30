#include "Haunting.hpp"

using namespace std;

Haunting::Haunting(){

}

void Haunting::startHaunting(mutex& coutMutex){
	//spawn a thread that would take care of messaging the user periodically
	thread tHaunt (doTheTalking,std::ref(coutMutex));
	tHaunt.detach();
}

void Haunting::doTheTalking(mutex& mtx){

	//sleep for 30 sec before displaying the first message	
	std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(30)));
	cout<<"The TV suddenly turns on and booming sound comes on: YOU HAVE TO PREPARE!\n";
	cout<<"The TV shows an all white image.\n";

	for (int i=0;i<3;i++){
		std::srand(std::time(NULL));

		//sleep from 30-45 secs before displaying a randomly selected message
		double sleepTime = 30 + ((static_cast<double>(std::rand()) / RAND_MAX) * 15);
		std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(sleepTime)));
		
		double chosenMsg = (static_cast<double>(std::rand()) / RAND_MAX) * (spookyStatements.size()-1);
		unique_lock {mtx};
		cout<<spookyStatements[static_cast<int>(chosenMsg)]<< "\n";
	}
}
