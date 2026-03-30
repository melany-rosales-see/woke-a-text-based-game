#include "Vocab.hpp"

using namespace std;

//splits a sentence into phrases based on the delimiter
vector<string> Vocab::split (string phrase, string delimiter){
	vector<string> retVal;

	int startPos=0;
	size_t foundHere;
	foundHere=phrase.find(delimiter, startPos);
	while(foundHere!=string::npos){
		retVal.push_back(phrase.substr(startPos, foundHere - startPos));
		startPos = foundHere + 1;
		foundHere=phrase.find(delimiter, startPos);
	}
	if (phrase.size()-startPos>0){
		retVal.push_back(phrase.substr(startPos, phrase.size() - startPos));
	}


	return retVal;

}

//make uppercase letters to lower case letters
void Vocab::toLower (string& input){

	for (auto i=0;i<input.size();i++){
		if (input[i]>='A' && input[i]<='Z'){
			input[i]+=32;
		}
	}
}

//remove prepositions
void Vocab::removePrepositions (vector<string>& input){

	for (int i= input.size()-1; i>=0; i--){
		//remove "the"
		if (input[i].compare("the")==0){
			input.erase(input.begin() + i);
		//remove prepositions
		}else if (input[i].compare("on")==0||input[i].compare("to")==0||input[i].compare("from")==0||input[i].compare("of")==0||input[i].compare("up")==0||input[i].compare("at")==0||input[i].compare("around")==0){
			input.erase(input.begin()+ i);
		}
	}

}

Vocab::Vocab(){
	initWebster();
}

//list the synonyms of each word in the vocabulary
void Vocab::initWebster(){

	set<string> walkSynonyms;
	walkSynonyms.insert("go");
	walkSynonyms.insert("run");
	walkSynonyms.insert("move");
	walkSynonyms.insert("walk");

	webster["walk"] = walkSynonyms;

	set<string> grabSynonyms;
	grabSynonyms.insert("pick");
	grabSynonyms.insert("seize");
	grabSynonyms.insert("clutch");
	grabSynonyms.insert("clasp");
	grabSynonyms.insert("snatch");
	grabSynonyms.insert("hold");
	grabSynonyms.insert("grab");
	webster["grab"] = grabSynonyms;

	set<string> lookSynonyms;
	lookSynonyms.insert("look");
	lookSynonyms.insert("glance");
	lookSynonyms.insert("investigate");
	lookSynonyms.insert("observe");
	lookSynonyms.insert("follow");
	lookSynonyms.insert("describe");
	lookSynonyms.insert("see");
	webster["look"] = lookSynonyms;
	
	set<string> openSynonyms;
	openSynonyms.insert("open");
	openSynonyms.insert("yank");
	webster["open"] = openSynonyms;

	set<string> wearSynonyms;
	wearSynonyms.insert("wear");
	wearSynonyms.insert("put");
	webster["wear"] = wearSynonyms;
	
	set<string> eatSynonyms;
	eatSynonyms.insert("eat");
	eatSynonyms.insert("gobble");
	eatSynonyms.insert("gulp");
	eatSynonyms.insert("swallow");
	webster["eat"] = eatSynonyms;
	
	set<string> breakSynonyms;
	breakSynonyms.insert("break");
	breakSynonyms.insert("smash");
	breakSynonyms.insert("destroy");
	webster["break"] = breakSynonyms;
}

//expresses the phrase in words from the vocabulary
vector<string> Vocab::inOtherWords (string input){
	toLower(input);
	vector<string> words = split (input, " ");
	removePrepositions(words);

	/*cout<<"Vocab\n";
	for (auto i=0; i<words.size(); i++){
		cout<<words[i]<<endl;
	}*/

	if (words.size()==1 && webster["look"].contains(words[0])){
		words[0] = "look";
	}else if (words.size()<2){
		for (int i=words.size()-1; i>=0; i--){
			words.erase(words.begin()+i);
		}
	}else{
		//remove dot at the end if it exists
		string lastWord = words[words.size()-1];
		if(lastWord[lastWord.length()-1]=='.'){
			words[words.size()-1] = lastWord.substr(0, lastWord.length()-1);
		}

		//first word should be a verb
		if(webster["walk"].contains(words[0])){
			words[0] =  "walk";
		}else if(webster["grab"].contains(words[0])){
			words[0] =  "grab";
		}else if(webster["look"].contains(words[0])){
			words[0] =  "look";
		}else if(webster["open"].contains(words[0])){
			words[0] =  "open";
		}else if(webster["eat"].contains(words[0])){
			words[0] =  "eat";
		}else if(webster["break"].contains(words[0])){
			words[0] =  "break";
		}else{
			for (int i=words.size()-1; i>=0; i--){
				words.erase(words.begin()+i);
			}
		}
	}

	return words;
}
