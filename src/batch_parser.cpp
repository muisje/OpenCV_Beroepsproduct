#include "../include/batch_parser.h"

#define DELIMITER "#"

BatchParser::BatchParser(std::string filename, Language language)
{
    this->language = language;
    file = new std::ifstream(filename);
}

BatchParser::~BatchParser()
{
    file->close();
    delete file;
}

Specification BatchParser::nextSpecification()
{
    if (file->is_open()) {
        std::string line;
        getline(*file, line);
        std::istringstream iss(line);
        std::string shape, colour;

        if (!(iss >> shape >> colour)) { 
            Specification specification{
                .shape = Shape::NO_SHAPE,
                .colour = Colour::NO_COLOUR
            };
            return specification;
        } 
        colour = colour.substr(0, colour.find(DELIMITER));    
        shape = toEnglish(toUpper(shape), language);
        colour = toEnglish(toUpper(colour), language);
        return parseSpecification(shape, colour);
    }

    Specification specification{
        .shape = Shape::NO_SHAPE,
        .colour = Colour::NO_COLOUR
    };
    return specification;
}   