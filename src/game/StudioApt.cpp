#include "StudioApt.hpp"

using namespace std;
	
string StudioApt::getIntro(){
	if (alreadyVisited){
		return "The room is not exactly messy but it won't be on the front page of a lifestyle magazine. A twin size bed in the corner of a house that's the size of a studio apartment. To the right of it is an office desk next to a window. At the foot of your bed is a sofa facing a TV mounted on the wall. Below the TV is a small dining set: a table and four chairs. You can get a glimpse of a tiny kitchen through a big doorway without a door. The open concept vibe can be felt in this apartment. Also, there are only two doors to be seen. One is the bathroom because there's a sign that says so on the door. Through process of elimination, the other one goes out. A small closet door stands next to the front door.";
	}else{
		alreadyVisited = true;
		return "The room is not exactly messy but it won't be on the front page of a lifestyle magazine. You are on a twin size bed in the corner of a studio apartment. On your right is an office desk next to a window. At the foot of your bed is a sofa facing a TV mounted on the wall. Below the TV is a small dining set: a table and four chairs. You can get a glimpse of a tiny kitchen through a big doorway without a door. The open concept vibe can be felt in this apartment. Also, there are only two doors to be seen. One is the bathroom because there's a sign that says so on the door. Through process of elimination, the other one goes out. A small closet door stands next to the front door.";
	}
}

StudioApt::StudioApt(){
	for (int i=0;i<10;i++){
		items[i].status = Status::inaccessible;
	}
	items[JACKET].id="100001";
	items[JACKET].name="jacket";
	items[PANTS].id="100002";
	items[PANTS].name="pants";
	items[SHIRT].id="100003";
	items[SHIRT].name="shirt";
	items[SHOES].id="100004";
	items[SHOES].name="shoes";
	items[KEYS].id="100005";
	items[KEYS].name="keys";
	items[SOUND].id="100006";
	items[SOUND].name="sound";
}


std::string StudioApt::lookAtSomething (std::vector<std::string>& command){
	if (command.size()==1){
		return getIntro();
	}else if ((command[1] =="office" && command[2]=="desk")|| command[1]=="desk"){
		items[KEYS].status= Status::available;
		items[SOUND].status= Status::available;
		return "A laptop stood closed at the right. A pink mat covered most of the desk. Circular stains stamped the left. The culprint, a coffee mug, sat boldly but empty. Next to the laptop was an open notebook with a black multipen on its center. Car keys was also plopped at the center. Something is making sounds next to the desk.";
	}else if ((command[1]=="sound"|| (command[1]=="next" && command[2]=="desk")) && items[SOUND].status== Status::available){
		items[PANTS].status= Status::available;
		items[SHIRT].status= Status::available;
		return "The radiator was hissing and clanking. On top of it was a shirt and a pair of jeans left to dry overnight by the heat from the radiator.";
	}else if ((command[1]=="pants"||command[1]=="jeans")&&items[PANTS].status== Status::available){
		return "The radiator dried it well. The pants is size 6, your size.";
	}else if (command[1]=="shirt"&& items[SHIRT].status== Status::available){
		return "The radiator dried it well. The shirt is white. Nothing written on it.";
	}else if (command[1]=="closet"||command[1]=="cabinet"){
		items[JACKET].status = Status::available;
		return "The cabinet stores all of your clothes but you were in a cleaning frenzy yesterday and you left all your clothes at the laundrymat. You need to pick them up eventually. So, right now only a winter coat hangs in the closet.";
	}else if (command[1]=="front"&& command[2]=="door"){
		items[SHOES].status = Status::available;
		return "The front door is white. A vase stood next to it with an umbrella sticking out. A mat with a cat image was in front of the door and a pair of winter boots is sitting on the mat.";
	}else if (command[1]=="tv"||command[1]=="television"||command[1]=="telly"){
		return "The tv is a medium for sending messages through air waves.";
	}else if (command[1]=="table"){
		return "The table sits four. Small candles are on it.";
	}else if (command[1]=="chair"){
		return "One chair out of four. Wooden. No cushion of any kind.";
	}else if (command[1]=="bed"){
		return "The bed is twin sized. May fit one and a half human.";
	}

	return "Where are you looking at?";
}
