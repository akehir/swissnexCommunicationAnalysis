// Mail-Anonymizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

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
		std::ifstream myfile(path.c_str());

		std::ofstream outfile (".\\output.mbx");
		//std::cout << outfile.good() << std::endl;
		//std::cout << outfile.getloc() << std::endl;

		if (myfile.is_open()) {
			while (! myfile.eof() ) {
				getline (myfile,line);
				//std::cout << line << std::endl;

				if(line.substr(0, 9).compare("Subject: ") == 0){



					bool run = 1;
					// divide line in two variables
					std::string line_left, line_right;
					line_left	= line.substr(0, 9);
					line_right	= line.substr(9);

					while(run){
						if(line_right.substr(0, 5).compare("Fwd: ") == 0){
							line_left	+= line_right.substr(0, 5);
							line_right	=	line_right.substr(5);
						}
						else if(
							line_right.substr(0, 4).compare("RE: ") == 0 
							|| line_right.substr(0, 4).compare("Re: ") == 0 
							|| line_right.substr(0, 4).compare("Fw: ") == 0
							|| line_right.substr(0, 4).compare("FW: ") == 0
							|| line_right.substr(0, 4).compare("Aw: ") == 0
							|| line_right.substr(0, 4).compare("AW: ") == 0
						){
							line_left	+= line_right.substr(0, 4);
							line_right	=	line_right.substr(4);
						}
						else{
							run = 0;
						}
					}

					// put two lines together again
					int a= hash(line_right.c_str());
					line = line_left + std::to_string(a);
				}
				outfile << line << std::endl;
			}

		myfile.close();
		outfile.close();
		} 
		else{
			std::cout << "Bad path: " << path << std::endl;
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
