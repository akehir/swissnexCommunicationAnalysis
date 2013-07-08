// Mail-Anonymizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include <windows.h> 

//using namespace std;
#define BUFSIZE MAX_PATH;

int hash(const char *str);

int main() {


    //std::cout << hash("Blablabla");
	std::string path;
	std::cout << "Please drag & drop your exported mailbox (*.mbx) here:" << std::endl;
	std::cin >> path;
	

	
	try{
		std::string line;
		//std::ifstream myfile ("A:/DEV/swissnexCommunicationAnalysis/Mail-Anonymizer/Mail-Anonymizer/input.mbx");
		//std::ofstream outfile ("A:/DEV/swissnexCommunicationAnalysis/Mail-Anonymizer/Mail-Anonymizer/output.mbx");
		std::ifstream myfile (path);

		std::ofstream outfile (".\\output.mbx");
		//std::cout << outfile.good() << std::endl;
		//std::cout << outfile.getloc() << std::endl;

		if (myfile.is_open()) {
			while (! myfile.eof() ) {
				getline (myfile,line);
				//std::cout << line << std::endl;

				if(line.substr(0, 9).compare("Subject: ") == 0){
					outfile << line.substr(0, 9) << hash(line.substr(9).c_str()) << std::endl;
				}
				else {
					outfile << line << std::endl;
				}
			}

		myfile.close();
		outfile.close();
		} 
		else{
			std::cout << "Bad path" << std::endl;
		}
	}
	catch (std::exception& err) {
			std::cout << err.what() << std::endl;
	}

	std::string alpha;
	std::cout << "Type 'q' to quit." << std::endl;
	std::cin >> alpha;
    return 0;
}


int hash(const char *str)
{
    int h = 0;
    while (*str)
       h = h << 1 ^ *str++;
    return h;
}