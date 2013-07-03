// Mail-Anonymizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;

int main() {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    const char* string = "hello world"; 

    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, string, strlen(string));
    SHA256_Final(digest, &ctx);

    char mdString[SHA256_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    printf("SHA256 digest: %s\n", mdString);


    return 0;
}
