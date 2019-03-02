#include "../include/language.h"
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <map>

const std::map<std::string, std::string> dutchToEnglish = boost::assign::list_of<std::pair<std::string, std::string> >
    ("RECHTHOEK", "RECTANGLE") ("VIERKANT", "SQUARE") ("DRIEHOEK", "TRIANGLE") ("CIRKEL", "CIRCLE")
    ("HALVE_CIRKEL", "HALF_CIRCLE") 
    ("ROOD", "RED") ("GROEN", "GREEN") ("BLAUW", "BLUE") ("GEEL", "YELLOW") ("ZWART", "BLACK") ("ZWART", "BLACK");

std::string toUpper(const std::string & string)
{
    std::string upperString = string;
    for (auto & c: upperString) c = toupper(c);
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