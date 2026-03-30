#ifndef VOCAB_HPP
#define VOCAB_HPP

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>

class Vocab{
	private:
		std::map<std::string, std::set<std::string>> webster;
		void initWebster();

	public:
		Vocab();
		std::vector<std::string> inOtherWords (std::string);
		static std::vector<std::string> split (std::string, std::string);
		static void toLower (std::string&);
		static void removePrepositions (std::vector<std::string>&);
};

#endif
