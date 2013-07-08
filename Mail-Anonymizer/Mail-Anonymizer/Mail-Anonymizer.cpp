// Mail-Anonymizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

//using namespace std;


int hash(const char *str);

int main() {


    std::cout << hash("Blablabla");

    return 0;
}


int hash(const char *str)
{
    int h = 0;
    while (*str)
       h = h << 1 ^ *str++;
    return h;
}