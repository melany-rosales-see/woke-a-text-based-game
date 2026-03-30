#ifndef HAUNTING_HPP
#define HAUNTING_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

class Haunting{
	public:
	Haunting();
	void startHaunting(std::mutex&);
	
	private:
	static void doTheTalking(std::mutex&);
	inline const static std::vector<std::string> spookyStatements = 
		{"You are waking up!", "The end is near!", "Come join us!", "We will purge evil!"
		, "Tomorrow is promised!", "We are waiting!", "There are no aliens!"
		, "Everything is black and white.", "Come to the light!","We fight darkness."
		, "The closer we are to the edge, the closer we are to the promised land."
		};

};

#endif
