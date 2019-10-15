// Zachary Hayes - zjhayes@dmacc.edu - October 15th, 2019

#ifndef PersonalityTest_hpp
#define PersonalityTest_hpp

#include "Trait.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

class PersonalityTest
{
protected:
    
    int totalResponses = 0;
    int redPoints = 0;
    int yellowPoints = 0;
    int greenPoints = 0;
    int bluePoints = 0;
    
    std::string redString = "Your color is RED. \n\nYou are task and result oriented, likes recognition, likes to be on the move, doesn’t like to be late, enjoys individual sports (golf, tennis, track, piano, individual dance, etc.) likes expensive showy things, generally honest, but their moral compass might deviate during a competitive showdown. \n\nRed personality types tend to make good leaders. They love leadership roles and enjoy “managing” people (sometime perceived as bossy or having big egos). In the classroom setting, their hands will fly up when they know the answer. Generally, 1 out of 5 students will be red (I found a higher ratio, however, in my GT classes). They like to leader of the pack. \n\nCar of choice: something flashy and expensive (e.g. sports car). \nIf you had to put a swing set together:  would pay somebody to do it for them.";
    std::string yellowString = "Your color is YELLOW. \n\nYou are people oriented, expressive, friendly, loves to talk, extravagant, optimistic, enjoys team sports (volley ball, baseball, football, basketball, drill team, cheer team, etc.). \n\nYellow personality types are the glue that holds groups together. They are generally outgoing and fun loving. They are your classroom talkers. Yellows are usually the principal color in most groups. They like to run in packs. \n\nCar of choice: one that’s big enough to hold their friends. \nIf you had to put a swing set together: would invite your friends over to build and barbeque.";
    std::string greenString = "Your color is GREEN. \n\nYou are detail oriented, precise, controlled, likes to do things right the first time, likes to complete jobs, tends to be thrifty. \n\nGreen personality types like order. They generally have neat lockers and organized notebooks. They are often perceived as “neatfreaks”. They make wonderful treasurers, secretaries, or committee chairs in clubs.  They will keep your group organized. Generally speaking, 1 out of every 7 students will be green (once again—more in GT population). Likes to keep the pack on the trail. \n\nCar of choice: hybrid vehicle (energy efficient). \nIf you had to put a swing set together: would pull out the directions, carefully count and arrange the parts, then systematically build the swing set.";
    std::string blueString = "Your color is BLUE. \n\nYou are creative, freethinking, sincere, loyal, caring, perceptive, understanding, open‐minded, oftentimes enjoys nature, may like the arts. \n\nBlue personality types are often perceived as quiet, sometimes shy individuals. Oftentimes they may be loners or have one or two other “blue” friends. They are very innovative, idea people. They tend to be quiet in a group and should be called upon to share their ideas. Generally, 1 out of every 8 or 9 students will be blue. Blues don’t usually run with the pack.\n\nCar of choice: jeep, recreational vehicle, unusual car (off-road adventures). \nIf you had to put a swing set together: would design you own swing set.";
    
    std::vector<Trait> traits;
    Color getColorByString(std::string);
    void addPoint(Color);
    void promptUser(Trait);
    void outputResults();
    std::string getFinalResult(Color);
    Color determineFinalResult();
    
public:
    
    void run();
    void addTrait(Trait);
    void addTrait(std::string,std::string);
    
};



#endif /* PersonalityTest_hpp */
