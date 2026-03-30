#ifndef STUDIOAPT_HPP
#define STUDIOAPT_HPP

#include "Scene.hpp"
#include <vector>

class StudioApt: public Scene{

	public:
		virtual std::string getIntro() override;
		virtual std::string lookAtSomething (std::vector<std::string>&) override;
		StudioApt();

};

#endif
