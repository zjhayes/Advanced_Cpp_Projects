// This program makes taking the Color Personality test easy while creating less paper waste.
// Personality traits and their associated color are imported from a CSV file.
// Users are prompted whether a word describes them, and their final results are displayed at the end.

// Zachary Hayes - zjhayes@dmacc.edu - October 15th, 2019

// FEATURES THAT I HAVE NOT USED
// --Did not include std namespace. I read you shouldn't include std and should just use, for example, std::cout.
// --Used .h file. I've been avoiding this because it's a lot of back-and-forth to edit.
// --Used switch statement. I don't like switch statements typically, but made good use of them here.
// --try/catch block. I did some exception handling so the program would fail gracefully.
// --Overloaded function. There are two versions of addTrait() so you can give it a Trait or
//    it will create the trait based on the values you give.

// NOTE: Because the list of traits is so long, I created a second shorter list for testing.
// Swap out the TRAIT_PATH with either the PROD_PATH or TEST_PATH to switch between these lists.

#include <iostream>
#include <fstream>
#include "PersonalityTest.h"

std::string const PROD_PATH = "traits.txt"; // Full list.
std::string const TEST_PATH = "test-traits.txt"; // Partial list.
std::string const TRAIT_PATH = TEST_PATH;

void populateTraits();
void parseLine(std::string);

PersonalityTest test;

int main()
{
    std::cout << "What Color is Your Personality?" << std::endl;
    
    test = PersonalityTest();
    populateTraits();
    test.run();
    
    return 0;
}

// Read file into new traits.
void populateTraits()
{
    std::ifstream reader(TRAIT_PATH);
    try
    {
        while(reader.good())
        {
            std::string line;
            getline(reader, line);
            parseLine(line);
        }
    }
    catch (std::out_of_range)
    {
        return;
    }
}

// Parse line from file into trait name and color properties.
void parseLine(std::string _line)
{
    std::string const DELIMITER = ",";
    std::string traitName = _line.substr(0, _line.find(DELIMITER));
    std::string traitColor = _line.substr(_line.find(DELIMITER) + 1);
    
    test.addTrait(traitName,traitColor);
}
