#include "Json.hpp"

using namespace std;

void Json::assignVal(std::string key, auto val){
	Entry addMe{val};
	keyVals[key] = addMe;
}
void Json::addStringValue(string key, string val){
	assignVal (key, val);
}

void Json::addIntValue(string key, int val){
	assignVal (key, val);
}

void Json::addBooleanValue(string key, bool val){
	assignVal (key, val);
}

void Json::addDoubleValue(string key, double val){
	assignVal (key, val);
}

std::string Json::toString(){
	ostringstream oss;

	oss<<*this;

	return oss.str();
}

std::ostream& operator<< (std::ostream& os, Json& obj){
	bool isFirst = true;
	os<<"{";
	for (auto const& [key, val]: obj.keyVals){
		if (isFirst){
			isFirst = false;
		}else{
			os<<",";
		}
		os<<"\""<<key<<"\":"<<obj.keyVals[key];
	}
	os<<"}";

	return os;
}


bool Json::isStringGoodForJson(std::string input, map<int, int> & locations){
	int pos = 0;
	int max = input.size();

	stack<pair<char, int> > matchMe;

	//remove white space	
	while(pos<max && input[pos]==' '){
		pos++;	
	}
	
	//find first {
	if (pos>=max || input[pos]!='{'){
		return false;
	}else{
		matchMe.push(make_pair(input[pos], pos));
		pos++;
	}
//------------

	while (pos<max){
		//remove white space
		while(pos<max && input[pos]==' '){
			pos++;	
		}

		if (pos>=max){
			return matchMe.size()==0;
		}

		if (input[pos]=='{' || input[pos]=='['){
			matchMe.push(make_pair(input[pos], pos));
			pos++;
		}else if (input[pos]=='}'){
			if (matchMe.size()<=0){
				return false;
			}
			pair<char, int>tmp = matchMe.top();
			if ('{' == tmp.first){
				matchMe.pop();
				locations[tmp.second] = pos;
				pos++;
			}else{
				return false;
			}
		}else if (input[pos]==']'){
			if (matchMe.size()<=0){
				return false;
			}
			pair<char, int>tmp = matchMe.top();
			if ('[' == tmp.first){
				matchMe.pop();
				locations[tmp.second] = pos;
				pos++;
			}else{
				return false;
			}
		}else if (input[pos]=='"'){
			if (matchMe.size()>0){
				pair<char, int>tmp = matchMe.top();
				if ('"' == tmp.first){
					matchMe.pop();
					locations[tmp.second] = pos;
					pos++;
				}else{
					matchMe.push(make_pair(input[pos], pos));
					pos++;
				}
			}else{
				matchMe.push(make_pair(input[pos], pos));
				pos++;
			}
		}else{
			if (input[pos]>='!' && input[pos]<='~'){
				pos++;
			}else{
				return false;
			}
		}
	}

	return matchMe.size()==0;

}

Json * Json::toJSONObj(string input){

	map<int, int>  locations;

	bool isValid = isStringGoodForJson(input, locations);
	if (isValid){
	/*	cout<<"Valid json string\n";
		for (auto [k,v]: locations){
			cout<<k<<"-"<<v<<"\n";
		}*/
		int pos = locations.begin()->first;
		int max = input.size();

		return toJSONObj_helperJSON(input, locations, pos, max);
	}

	throw invalid_argument("Not a valid string");
}

Json * Json::toJSONObj_helperJSON(string input, map<int, int> locations, int pos, int max){
	Json * retVal = new Json();

	pos++;
	
	while (pos<max)
	{
	//remove white space	
	while(pos<max && input[pos]==' '){
		pos++;	
	}
	
	//find key's open "
	if (pos>=max || input[pos]!='"'){
		throw invalid_argument("Not a valid string. Invalid key.");
	}else{
		pos++;
	}

	////FIND KEY
	//find key and key's close "
	string key="";
	while (pos<max && input[pos]>='!' && input[pos]<='~'){
		if (input[pos]=='"'){
			pos++;
			break;
		}else{
			key+=input[pos];
			pos++;
		}
	}

	if (pos>=max){
		throw invalid_argument("Not a valid string. Value not provided.");
	}
	//find pair's :
	//remove white space	
	while(pos<max && input[pos]==' '){
		pos++;	
	}
	if (pos>=max || input[pos]!=':'){
		throw invalid_argument("Not a valid string. Missing :.");
	}else{
		pos++;
	}

	/////FIND VALUE
	//remove white space	
	while(pos<max && input[pos]==' '){
		pos++;	
	}

	if (pos>=max){
		throw invalid_argument("Not a valid string. Missing value.");
	}

	//value is integer or double
	if (input[pos]>='0'&&input[pos]<='9'){
		string numberAsStr="";
		int dotCount = 0;
		while(pos<max && input[pos]=='.'||(input[pos]>='0'&&input[pos]<='9')){
			if (input[pos]=='.'){
				if (dotCount>0){
					throw invalid_argument("Not a valid double. More than 1 decimal point");
				}
				dotCount++;
			}

			numberAsStr+=input[pos];
			pos++;
		}

		if (dotCount>0){
			retVal->addDoubleValue(key, atof(numberAsStr.c_str()));
		}else{
			retVal->addIntValue(key, atoi(numberAsStr.c_str()));

		}
	}else if (input[pos]=='t'){
		if (pos+3 < max){
			if (input[pos+1]=='r' && input[pos+2]=='u' && input[pos+3]=='e'){
				pos+=4;
				retVal->addBooleanValue(key, true);
			}else{
				throw invalid_argument("Found a t but not true.");
			}
		}else{
			throw invalid_argument("Found a t but not true.");
		}
	}else if (input[pos]=='f'){
		if (pos+4 < max){
			if (input[pos+1]=='a' && input[pos+2]=='l' && input[pos+3]=='s' && input[pos+4]){
				pos+=5;
				retVal->addBooleanValue(key, false);
			}else{
				throw invalid_argument("Found a f but not false.");
			}
		}else{
			throw invalid_argument("Found a f but not false.");
		}
	}else if (input[pos]=='"'){
	
		pos++;
		string valueStr="";
		while(pos<max && input[pos]!='"'){
			valueStr+=input[pos];
			pos++;
		}
		if (input[pos]=='"'){
		
			retVal->addStringValue(key, valueStr);	
			pos++;
		}else{
			throw invalid_argument("Not a valid string. Missing \".");
		}
	
	}else if (input[pos]=='{'){
		Json * innerJson = toJSONObj_helperJSON(input,locations,pos, locations[pos]+1);
		retVal->addJson(key, *innerJson);
		pos = locations[pos];
		pos++;
	}else if (input[pos]=='['){
		vector<Entry> * innerArray = toJSONObj_helperArray(input,locations,pos, locations[pos]+1);
		retVal->addVector(key, *innerArray);
		pos = locations[pos];
		pos++;
	}
	
	//find comma if there is one
	while(pos<max && input[pos]==' '){
		pos++;	
	}
	if (pos>=max || (input[pos]!=',' && input[pos]!='}')){
		throw invalid_argument("Not a valid string. Char at end doesn't make sense: "+input[pos]);
	}

	if (input[pos]=='}'){
		return retVal;
	}else if (input[pos]==','){
		pos++;
	}
}

	return retVal;

}
vector<Entry> * Json::toJSONObj_helperArray(string input, map<int, int> locations, int pos, int max){
	vector<Entry> * retVal = new vector<Entry>();

	pos++;
	
	while (pos<max)
	{
	/////FIND VALUE
	//remove white space	
	while(pos<max && input[pos]==' '){
		pos++;	
	}
	
	if (pos>=max){
		throw invalid_argument("Not a valid string. Missing value.");
	}

	//value is integer or double
	if (input[pos]>='0'&&input[pos]<='9'){
		string numberAsStr="";
		int dotCount = 0;
		while(pos<max && input[pos]=='.'||(input[pos]>='0'&&input[pos]<='9')){
			if (input[pos]=='.'){
				if (dotCount>0){
					throw invalid_argument("Not a valid string. More than 1 decimal point");
				}
				dotCount++;
			}

			numberAsStr+=input[pos];
			pos++;
		}

		//cout<<"num as str"<<numberAsStr<<"\n";
		if (dotCount>0){
			retVal->push_back(Entry{atof(numberAsStr.c_str())});
		}else{
			retVal->push_back(Entry{atoi(numberAsStr.c_str())});

		}
	}else if (input[pos]=='t'){
		if (pos+3 < max){
			if (input[pos+1]=='r' && input[pos+2]=='u' && input[pos+3]=='e'){
				pos+=4;
				retVal->push_back(Entry{true});
			}else{
				throw invalid_argument("Found a t but not true.");
			}
		}else{
			throw invalid_argument("Found a t but not true.");
		}
	}else if (input[pos]=='f'){
		if (pos+4 < max){
			if (input[pos+1]=='a' && input[pos+2]=='l' && input[pos+3]=='s' && input[pos+4]){
				pos+=5;
				retVal->push_back(Entry{false});
			}else{
				throw invalid_argument("Found a f but not false.");
			}
		}else{
			throw invalid_argument("Found a f but not false.");
		}
	}else if (input[pos]=='"'){
	
		pos++;
		string valueStr="";
		while(pos<max && input[pos]!='"'){
			valueStr+=input[pos];
			pos++;
		}
		if (input[pos]=='"'){
			retVal->push_back(Entry{valueStr});
			pos++;
		}else{
			throw invalid_argument("Not a valid string. Missing \".");
		}
	}else if (input[pos]=='{'){
		Json * innerJson = toJSONObj_helperJSON(input,locations,pos, locations[pos]+1);
		//cout<<"innerJson"<<*innerJson<<"\n";
		retVal->push_back(Entry{innerJson});
		//cout<<"after"<<"\n";
		pos = locations[pos];
		pos++;
	}else if (input[pos]=='['){
		vector<Entry> * innerArray = toJSONObj_helperArray(input,locations,pos, locations[pos]+1);
		retVal->push_back(Entry{innerArray});
		pos = locations[pos];
		pos++;
	}
	
	//find comma if there is one
	while(pos<max && input[pos]==' '){
		pos++;	
	}
	if (pos>=max || (input[pos]!=',' && input[pos]!=']')){
		throw invalid_argument("Not a valid string. Char at end doesn't make sense: "+input[pos]);
	}

	if (input[pos]==']'){
		return retVal;
	}else if (input[pos]==','){
		pos++;
	}
}

	cout<<retVal<<"\n";
	return retVal;

}

string Json::getStringValue(string key){
	if (holds_alternative<string>(keyVals[key].v)){
		return get<string>(keyVals[key].v);
	}
	throw runtime_error ("This doesn't contain string. This is a "+keyVals[key].getType());	
}
int Json::getIntegerValue(string key){
	if (holds_alternative<int>(keyVals[key].v)){
		return get<int>(keyVals[key].v);
	}
	throw runtime_error ("This doesn't contain integer. This is a "+keyVals[key].getType());	

}
bool Json::getBooleanValue(string key){
	if (holds_alternative<bool>(keyVals[key].v)){
		return get<bool>(keyVals[key].v);
	}
	throw runtime_error ("This doesn't contain boolean. This is a "+keyVals[key].getType());	

}
double Json::getDoubleValue(string key){
	if (holds_alternative<double>(keyVals[key].v)){
		return get<double>(keyVals[key].v);
	}
	throw runtime_error ("This doesn't contain double. This is a "+keyVals[key].getType());	

}
vector<Entry>& Json::getVector(string key){
	if (holds_alternative<vector<Entry> *>(keyVals[key].v)){
		return *(get<vector<Entry>* >(keyVals[key].v));
	}
	throw runtime_error ("This doesn't contain a vector. This is a "+keyVals[key].getType());	

}
Json& Json::getJson(string key){
	if (holds_alternative<Json *>(keyVals[key].v)){
		return *(get<Json * >(keyVals[key].v));
	}
	throw runtime_error ("This doesn't contain Json. This is a "+keyVals[key].getType());	

}

Json::~Json(){
	deleteJson_helper(this);
}

void Json::deleteJson_helper(Json * deleteMe){
	/*cout<<"DELETE ME!\n";
	cout<<*deleteMe<<"\n";*/
	for (auto [key, val] : deleteMe->keyVals){
		if (holds_alternative<Json *>(val.v)){
			Json * item = get<Json * >(val.v);
			deleteJson_helper(item);			
			if (item!=nullptr){
				delete(item);
			}
		}else if (holds_alternative<vector<Entry> *>(val.v)){
			deleteArray_helper(get<vector<Entry>* >(val.v));
			vector<Entry>* ptr = get<vector<Entry> * >(val.v);
			if (ptr!=nullptr){
				delete(ptr);
			}
		}
	}
}

void Json::deleteArray_helper(std::vector<Entry> * deleteMe){
	/*cout<<"DELETE ME!\n";
	for (auto m :*deleteMe){
		cout<<m<<" ";
	}*/
	for (int i=0; i<deleteMe->size(); i++){
		Entry item = (*deleteMe)[i];

		if (holds_alternative<Json *>(item.v)){
			deleteJson_helper(get<Json * >(item.v));			
			Json * ptr = get<Json * >(item.v);
			if (ptr!=nullptr){
				delete(ptr);
			}
		}else if (holds_alternative<vector<Entry> *>(item.v)){
			deleteArray_helper(get<vector<Entry>* >(item.v));
			vector<Entry>* ptr = get<vector<Entry> * >(item.v);
			if (ptr!=nullptr){
				delete(ptr);
			}
		}
		
	}
}

const std::map<std::string, Entry> & Json::getKeyVals(){
	return keyVals; 
}

Json * Json::grabJsonCopy (Json& copyMe){
	Json * newCopy = new Json();
	
	const std::map<std::string, Entry> keyVals =  copyMe.getKeyVals();

	for (auto [key, val]: keyVals){
		if (holds_alternative<string>(val.v)){
			newCopy->addStringValue(key, get<string>(val.v));
		}else if (holds_alternative<double>(val.v)){
			newCopy->addDoubleValue(key, get<double>(val.v));
		}else if (holds_alternative<int>(val.v)){
			newCopy->addIntValue(key, get<int>(val.v));
		}else if (holds_alternative<bool>(val.v)){
			newCopy->addBooleanValue(key, get<bool>(val.v));
		}else if (holds_alternative<Json *>(val.v)){
			newCopy->addJson(key, *(get<Json *>(val.v)));
		}else if (holds_alternative<vector<Entry> *>(val.v)){
			newCopy->addVector(key, *(get<vector<Entry> *>(val.v)));
		}
	}
	return newCopy;
}

void Json::addJson(std::string newKey, Json& copyMe){
	Json * newCopy = grabJsonCopy (copyMe);
	this->keyVals[newKey] = newCopy;

}

std::vector<Entry>* Json::grabVectorCopy (std::vector<Entry>& copyMe){
	vector<Entry> * newCopy = new vector<Entry>();

	for (auto item: copyMe){
		if (holds_alternative<Json*>(item.v)){
			Json * innerNewCopy = grabJsonCopy (*(get<Json *>(item.v)));
			newCopy->push_back(innerNewCopy);
		}else if (holds_alternative<vector<Entry>*>(item.v)){
			vector<Entry> * innerNewCopy = grabVectorCopy (*(get<vector<Entry> *>(item.v)));
			newCopy->push_back(innerNewCopy);

		}else{
			newCopy->push_back(item);
		}

	}
	return newCopy;
}
void Json::addVector(std::string newKey, std::vector<Entry> & copyMe){
	vector<Entry> * newCopy = grabVectorCopy (copyMe);
	this->keyVals[newKey] = newCopy;

}
