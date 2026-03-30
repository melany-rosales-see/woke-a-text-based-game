#include "Entry.hpp"

using namespace std;


std::string Entry::getType(){
	if (holds_alternative<string>(this->v)){
		return "string";
	}else if (holds_alternative<int>(this->v)){
		return "integer";
	}else if (holds_alternative<double>(this->v)){
		return "double";
	}else if (holds_alternative<bool>(this->v)){
		return "boolean";
	}else if (holds_alternative<vector<Entry> * >(this->v)){
		return "Entry_pointer";
	}else if (holds_alternative<Json*>(this->v)){
		return "Json_pointer";
	}else{
		return "unknown";
	}
}
std::ostream& operator<< (std::ostream& os, Entry& obj){
	if (holds_alternative<string>(obj.v)){
		os << "\""<< get<string>(obj.v)<<"\"";
	}else if (holds_alternative<int>(obj.v)){
		os << get<int>(obj.v);
	}else if (holds_alternative<double>(obj.v)){
		os << get<double>(obj.v);
	}else if (holds_alternative<bool>(obj.v)){
		if(get<bool>(obj.v)){
			os<<"true";
		}else{
			os<<"false";
		}
	}else if (holds_alternative<vector<Entry> * >(obj.v)){
		os << "[";
		bool isFirst = true;
		for (auto inner_obj : *(get<vector<Entry>*>(obj.v))){
			if (isFirst){
				isFirst = false;
			}else{
				os<<",";
			}
			os << inner_obj;
		}
		os << "]";
	}else if (holds_alternative<Json*>(obj.v)){
		os << *(get<Json*>(obj.v));
	}
	return os;
}

Entry& Entry::operator[](unsigned int i){
	if(holds_alternative<vector<Entry> * >(this->v)){
		vector<Entry> vec = (*(get<vector<Entry>*>(this->v)));
		if (i<0||i>=vec.size()){
			throw out_of_range("Index out of bounds.");	
		}
		return (*(get<vector<Entry>*>(this->v)))[i];
	}

	throw invalid_argument("Object is not a vector.");
}


Entry::Entry(){
}

Entry::Entry(int val): v{val}{
}

Entry::Entry(double val): v{val}{
}

Entry::Entry(bool val): v{val}{
}

Entry::Entry(string val): v{val}{
}

Entry::Entry(const char * val){
	v = string(val);
}

Entry::Entry(vector<Entry>* val): v{val}{
}

Entry::Entry(Json * val): v{val}{
}

string Entry::getStringValue(){
	if (holds_alternative<string>(this->v)){
		return get<string>(this->v);
	}
	throw runtime_error ("This doesn't contain string. This is a "+getType());	
}
int Entry::getIntegerValue(){
	if (holds_alternative<int>(this->v)){
		return get<int>(this->v);
	}
	throw runtime_error ("This doesn't contain int. This is a "+getType());	
}
double Entry::getDoubleValue(){
	if (holds_alternative<double>(this->v)){
		return get<double>(this->v);
	}
	throw runtime_error ("This doesn't contain double. This is a "+getType());	
}
bool Entry::getBooleanValue(){
	if (holds_alternative<bool>(this->v)){
		return get<bool>(this->v);
	}
	throw runtime_error ("This doesn't contain boolean. This is a "+getType());	
}
Json& Entry::getJson(){
	if (holds_alternative<Json *>(this->v)){
		return *(get<Json * >(this->v));
	}
	throw runtime_error ("This doesn't contain JSON. This is a "+getType());
}

vector<Entry>& Entry::getVector(){
	if (holds_alternative<vector<Entry> * >(this->v)){
		return *(get<vector<Entry> * >(this->v));
	}
	throw runtime_error ("This doesn't contain a vector. This is a "+getType());

}
