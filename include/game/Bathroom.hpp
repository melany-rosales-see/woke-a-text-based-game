#ifndef BATHROOM_HPP
#define BATHROOM_HPP

#include "Scene.hpp"
#include <vector>

class Bathroom: public Scene{

	public:
		Bathroom();
		virtual std::string getIntro () override;
		virtual std::string lookAtSomething (std::vector<std::string>&) override;

};

#endif
