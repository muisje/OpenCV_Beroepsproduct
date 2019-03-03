#include "../include/language.h"
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <map>

const std::map<std::string, std::string> dutchToEnglish = boost::assign::list_of<std::pair<std::string, std::string> >
    ("RECHTHOEK", "RECTANGLE") ("VIERKANT", "SQUARE") ("DRIEHOEK", "TRIANGLE") ("CIRKEL", "CIRCLE")
    ("HALVE_CIRKEL", "HALF_CIRCLE") 
    ("ROOD", "RED") ("GROEN", "GREEN") ("BLAUW", "BLUE") ("GEEL", "YELLOW") ("ZWART", "BLACK") ("ZWART", "BLACK")
    ("HOUT","WOOD")
    ("ONBEKENDE_VORM", "UNKNOWN_SHAPE") ("ONBEKENDE_KLEUR", "UNKNOWN_COLOUR");

std::map<std::string, std::string> englishToDutch;

std::string toUpper(const std::string & string)
{
    std::string upperString = string;
    for (char & c: upperString) c = static_cast<char>(toupper(c));
    return upperString;
}

std::string toEnglish(const std::string & word, enum::Language from)
{
    if(from == Language::ENGLISH)
    {
        return word;
    }
    auto iterator = dutchToEnglish.find(word);
    if (iterator == dutchToEnglish.end())
    {
        return "";
    }
    return iterator->second;
}

std::string toDutch(const std::string & word, enum::Language from)
{
    if(from == Language::DUTCH)
    {
        return word;
    }
    if (englishToDutch.size() != dutchToEnglish.size())
    {
        for(auto it = dutchToEnglish.begin(); it != dutchToEnglish.end(); it++)
        {
        englishToDutch[it->second] = it->first;
        }
    }
    auto iterator = englishToDutch.find(word);
    if (iterator == englishToDutch.end())
    {
        return "";
    }
    return iterator->second;
}

