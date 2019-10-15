// Zachary Hayes - zjhayes@dmacc.edu - October 15th, 2019

#include "Trait.h"
#include <string>

Trait::Trait(std::string _name, Color _color)
{
   name = _name;
   color = _color;
}

std::string const Trait::getName()
{
    return name;
}

Color const Trait::getColor()
{
    return color;
}
