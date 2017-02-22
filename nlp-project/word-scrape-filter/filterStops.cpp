#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>

std::vector<std::string> split(std::string const &input){
	std::istringstream buffer(input);
	std::vector<std::string> ret;
	
	std::copy(std::istream_iterator<std::string>(buffer),
			std::istream_iterator<std::string>(),
			std::back_inserter(ret));
	return ret;
}

int main(){

	std::ifstream inputList;
	std::ifstream inputStop;
	std::vector<std::string> words;
	std::vector<std::string> swords;
	std::regex e("([a-zA-Z]+'?)");

	try{
		std::string s;
		inputList.open("edited5000wordlist.txt");
		inputStop.open("/Users/stc1563/programming/SummerResearch/Corpus/Stopwords/stopwords_combined.txt");
		
		while(inputList.good()){
			getline(inputList, s);
			words.push_back(s);
			//std::cout << words.back() << std::endl;
		}
		s = "";
		//int stopCount = 0;
		while(inputStop.good()){
			getline(inputStop, s, ' ');
			std::vector<std::string> v = split(s);
			swords.insert(swords.end(), v.begin(), v.end());
			//stopCount += 1;
			//swords.push_back(s);
			//std::cout << swords.back() << std::endl;
		}
		inputList.close();
		inputStop.close();
		std::cout << stopCount << std::endl;

	}
	catch(int e){
		std::cout << "File read error" << std::endl;
	}

	std::ofstream filterList;
	int deleteCount = 0;
	try{
		filterList.open("StopFilteredList.txt");
		for(int i = 0; i < words.size(); i++){
			//std::cout << words.at(i) << std::endl;
			//std::cout << swords.at(i) << std::endl;
			for(int j = 0; j < swords.size(); j++){
				if(words.at(i) == swords.at(j)){
					words.at(i).erase();
					deleteCount += 1;
					//std::cout << swords.at(j) << std::endl;
				}
			}
			filterList << words.at(i) << std::endl;
		}
		filterList.close();
		std::cout << deleteCount << std::endl;

	}
	catch(int e){
		std::cout << "File write error" << std::endl;
	}

	return 0;
}
