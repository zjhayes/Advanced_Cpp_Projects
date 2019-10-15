// Zachary Hayes - zjhayes@dmacc.edu - October 15th, 2019

#include "PersonalityTest.h"

// Run personality test.
void PersonalityTest::run()
{
    for(auto& trait : traits)
    {
        promptUser(trait);
        totalResponses++;
    }
    outputResults();
}

// Ask user whether a trait describes them, and update points.
void PersonalityTest::promptUser(Trait _trait)
{
    std::string answer;
    std::cout << "Would you describe yourself as \"" << _trait.getName() << "\"? (y/n) ";
    std::getline(std::cin, answer);
    
    char answerLowerChar = tolower(answer.front());
    
    if(answerLowerChar == 'y')
    {
        addPoint(_trait.getColor());
    }
    else if(answerLowerChar == 'n')
    {
        // Do nothing.
    }
    else
    {
        std::cout << "Invalid entry. Try again." << std::endl;
        promptUser(_trait); // Ask again.
    }
}

// Add a trait object to traits vector.
void PersonalityTest::addTrait(Trait _trait)
{
    traits.push_back(_trait);
}

// Create trait object first, and then add to traits vector.
void PersonalityTest::addTrait(std::string _name, std::string _colorString)
{
    Color _color = getColorByString(_colorString);
    Trait _trait = Trait(_name, _color);
    addTrait(_trait);
}

// Translate color input to enum, only concerend about first letter.
Color PersonalityTest::getColorByString(std::string _colorString)
{
    char _firstLetter = _colorString.front(); // Only checks the first letter.
    
    switch(tolower(_firstLetter))
    {
        case 'r':
            return RED;
        case 'y':
            return YELLOW;
        case 'g':
            return GREEN;
        case 'b':
            return BLUE;
        default:
            return null;
    }
}

// Add points to a specific color.
void PersonalityTest::addPoint(Color _color)
{
    switch(_color)
    {
        case RED:
            redPoints++;
            return;
        case YELLOW:
            yellowPoints++;
            return;
        case GREEN:
            greenPoints++;
            return;
        case BLUE:
            bluePoints++;
        case null:
            return;
    }
}

// Calculate and display results of test.
void PersonalityTest::outputResults()
{
    std::cout << std::endl << "Final Results:" << std::endl << std::endl;
    
    int totalPoints = redPoints + yellowPoints + greenPoints + bluePoints;
    
    std::cout << "You described yourself as " << totalPoints << " of " << totalResponses << " traits." << std::endl << std::endl;
    
    std::cout << "Red: " << redPoints << " (" << (redPoints * 100 / totalPoints) << "%)" << std::endl;
    std::cout << "Yellow: " << yellowPoints << " (" << (yellowPoints * 100 / totalPoints) << "%)" << std::endl;
    std::cout << "Green: " << greenPoints << " (" << (greenPoints * 100 / totalPoints) << "%)" << std::endl;
    std::cout << "Blue: " << bluePoints << " (" << (bluePoints * 100 / totalPoints) << "%)" << std::endl;
    
    Color finalColor = determineFinalResult();
    std::cout << std::endl << getFinalResult(finalColor) << std::endl << std::endl;
}

// Get the color description of final test result.
std::string PersonalityTest::getFinalResult(Color _color)
{
    switch(_color)
    {
        case RED:
            return redString;
        case YELLOW:
            return yellowString;
        case GREEN:
            return greenString;
        case BLUE:
            return blueString;
        case null:
            break;
    }
    
    return "Encountered error while calculating results.";
}

Color PersonalityTest::determineFinalResult()
{
    if(redPoints > yellowPoints && redPoints > greenPoints && redPoints > bluePoints)
    {
        return RED;
    }
    else if(yellowPoints > greenPoints && yellowPoints > bluePoints)
    {
        return YELLOW;
    }
    else if(greenPoints > bluePoints)
    {
        return GREEN;
    }
    else
    {
        return BLUE;
    }
}
