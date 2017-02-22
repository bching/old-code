#include <iostream>
#include <fstream>
#include <sstream>

#include <list>
#include <string>
#include <regex>

//#define int WORDCOUNT = 5000;

struct word{
	std::string word;
	int rank;
};

int main() {
	
	std::ifstream inputFile;
	std::list<word> words;
	// delimiter manually inserted into text file
	//std::string delimit = ">>>>";

	try {
		inputFile.open("5000wordlist_1.txt");
		//std::stringstream ss;
		std::string line;
		std::regex e("([a-zA-Z]*'?[a-zA-Z]+)(?=[ /t]+[a-z]*)");

		while(inputFile.good()){
			word newWord;
			getline(inputFile, line);
			std::cout << line << std::endl;

//			std::cin >> newWord.rank;
//			std::cin >> newWord.word;
//			inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if(std::regex_match(line, e)){

				words.push_back(newWord);
				std::cout << words.end()->word;

			}
		}
		inputFile.close();
	}
	catch(int e) {
		std::cout << "File read error." << std::endl;
	}

	std::ofstream outputFile;

	try {
		outputFile.open("5000wordoutput.txt");
		for(std::list<word>::iterator it = words.begin(); it != words.end(); it++){
			outputFile << it->word << std::endl;
		}
		outputFile.close();
	}
	catch(int e){
		std::cout << "File output error." << std::endl;
	}

	return 0;
}
			
