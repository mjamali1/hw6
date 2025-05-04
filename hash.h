#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        // take last 6 chars of the string, if 6 not available take less
        unsigned long long hashArray[5] = {0, 0, 0, 0, 0};
        int sixGroupCnt = 0;
        int idx = 4; // start from end of array
        unsigned long long placement = 1; // tells us what to raise 36 to 
        unsigned long long current = 0;

        // break into groups of six and solve recursively
        for (int i = k.length() - 1; i >= 0; i--) {
          sixGroupCnt++;
          current += placement*letterDigitToNumber(k[i]);
          placement = placement*36;
          if (sixGroupCnt == 6) {
            hashArray[idx] = current;
            placement = 1;
            current = 0;
            sixGroupCnt = 0;
            idx -= 1;
          }
        }

        if (idx >= 0 && sixGroupCnt < 6) {
          hashArray[idx] = current;
        }

        // final equation
        HASH_INDEX_T equation = 0;
        for (int i = 0; i < 5; i++){
          equation += rValues[i] * hashArray[i];
        }
        
        return equation;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        
        // if letter - translate to numers 0 - 25
        // if lowercase letter
        HASH_INDEX_T num;
        if ( letter >= 97 && letter <= 122 ) {
          num = letter - 97;
          return num;
        }
        // if uppercase letter
        if ( letter >= 65 && letter <= 90 ) {
          num = letter - 65;
          return num;
        }
        // if number - translate to numbers 26 - 35
        if ( letter >= 48 && letter <= 57 ) {
          num = letter - 22;
          return num;
        }
        else {
          num = -1;
          return 0;
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
