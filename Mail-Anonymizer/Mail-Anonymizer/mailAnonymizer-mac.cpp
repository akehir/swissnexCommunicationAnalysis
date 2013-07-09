// Mail-Anonymizer.cpp : Reads a raw file containng emails and transforms into an appropriate input for the software condor
//

#include <string.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <algorithm>


// functions definitioan
std::string numberToString (int number);
int hash(const char *str);

int main() {
	
	// array that list beginning of lines we are interested in
	std::vector<std::string> headers;
	
	headers.push_back("From: ");
	headers.push_back("To: ");
	headers.push_back("Cc: ");
	headers.push_back("Subject: ");
	headers.push_back("Date: ");
	
	
	
	



	std::string path;
	std::cout << "Please drag & drop your exported mailbox (*.mbx) here:" << std::endl;
	std::cin >> path;
	
	std::string line;
	std::ifstream myfile(path.c_str());
	std::ofstream outfile ("/Users/output.mbx");
		
	if (myfile.is_open()) {
		while (! myfile.eof() ) {
			getline (myfile,line);
			
			
			bool toBeProcessed = 0;
			for(std::vector<std::string>::iterator it = headers.begin(); it != headers.end(); ++it) {
			    //std::cout << *it << std::endl;

				//std::string bla = "Sudbject: fjhfwfhw";

				if(line.substr(0, (*it).length()).compare(*it)==0){
					toBeProcessed = 1;
				}
			}
			
			if(toBeProcessed){

				if(line.substr(0, 9).compare("Subject: ") == 0){

					
					// divide line in two variables
					std::string line_left, line_right;
					line_left	= line.substr(0, 9);
					line_right	= line.substr(9);
				
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
					else{}
					
					line = line_left + numberToString(hash(line_right.c_str()));
				}
				
				if(line.substr(0, 6).compare("From: ") == 0){
					std::cout << std::endl << "From ???@?? 08.07.2013 10:00:00" << std::endl;
					outfile << std::endl;
				}
				
				std::cout << line << std::endl;
				outfile << line << std::endl;
			}

		}
		
		myfile.close();
		outfile.close();
	}
	else{
		std::cout << "Bad path: " << path << std::endl;
	}
	
	std::string alpha;
	std::cout << "Type 'q' to quit." << std::endl;
	std::cin >> alpha;
    return 0;
}


int hash(const char *str){
    int h = 0;
    while (*str)
       h = h << 1 ^ *str++;
    return h;
}

std::string numberToString (int number){
	std::ostringstream ss;
	ss << number;
	return ss.str();
}
