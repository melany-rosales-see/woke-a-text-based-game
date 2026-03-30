#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "Scene.hpp"
#include <vector>

class Kitchen: public Scene{

	public:
		Kitchen();
		virtual std::string getIntro () override;
		virtual std::string lookAtSomething (std::vector<std::string>&) override;

};

#endif
