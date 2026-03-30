#ifndef JSON_HPP
#define JSON_HPP

#include "Entry.hpp"
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <utility>
#include <type_traits>
#include <memory>

struct Entry;

class Json{
	private:
	std::map<std::string, Entry> keyVals;
	void assignVal(std::string key, auto val);

	static bool isStringGoodForJson(std::string, std::map<int, int> &);
	static Json * toJSONObj_helperJSON(std::string, std::map<int, int>, int, int );
	static std::vector<Entry> * toJSONObj_helperArray(std::string, std::map<int, int>, int, int );

	static void deleteJson_helper(Json *);
	static void deleteArray_helper(std::vector<Entry> * );

	static Json* grabJsonCopy (Json&);
	static std::vector<Entry>* grabVectorCopy (std::vector<Entry>&);

	public:
	void addStringValue(std:: string, std::string);
	void addIntValue(std:: string, int);
	void addBooleanValue(std:: string, bool);
	void addDoubleValue(std:: string, double);

	void addVector(std::string, std::vector<Entry> &);

	void addJson(std::string, Json&);

	std::string getStringValue(std:: string);
	int getIntegerValue(std:: string);
	bool getBooleanValue(std:: string);
	double getDoubleValue(std:: string);
	std::vector<Entry>& getVector(std::string);
	Json& getJson(std::string);

	std::string toString();
	static Json * toJSONObj(std::string);

	const std::map<std::string, Entry>& getKeyVals();
	
	friend std::ostream &operator<< (std::ostream& os, Json& obj);


	~Json();
};

#endif
