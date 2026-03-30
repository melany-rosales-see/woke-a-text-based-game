#ifndef ENTRY_HPP
#define ENTRY_HPP

#include<string>
#include<variant>
#include<sstream>
#include<iostream>
#include <vector>
#include<memory>

#include "Json.hpp"

struct Json;

struct Entry{
	
	std::variant <double, int, bool, std::string, std::vector<Entry> *, Json * > v;

	Entry();
	Entry(int val);
	Entry(double val);
	Entry(bool val);
	Entry(std::string val);
	Entry(const char* val);
	Entry(std::vector <Entry>* val);
	Entry(Json * val);

	std::string getType();

	Entry& operator[](unsigned int );
	friend std::ostream &operator<< (std::ostream& os, Entry& obj);

	std::string getStringValue();
	int getIntegerValue();
	double getDoubleValue();
	bool getBooleanValue();
	Json& getJson();
	std::vector<Entry>& getVector();
};

#endif
