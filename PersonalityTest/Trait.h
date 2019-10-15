// This is an individual personality trait, which is assigned a color.

// Zachary Hayes - zjhayes@dmacc.edu - October 15th, 2019

#ifndef Trait_hpp
#define Trait_hpp

#include <stdio.h>
#include <string>

enum Color
{
    null,
    RED,
    YELLOW,
    GREEN,
    BLUE
};

class Trait
{
protected:
    
    std::string name;
    Color color;
    
public:
    
    Trait(std::string, Color);
    std::string const getName();
    Color const getColor();
};

#endif /* Trait_hpp */
