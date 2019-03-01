#include "../include/parser.h"
#include <iostream>

#define DELIMITER "#"

Parser::Parser(std::string filename)
{
    // std::ifstream temp(filename);
    file = new std::ifstream(filename);

    // file = std::ifstream(file);
}

Parser::~Parser()
{
    file->close();
    delete file;
}

Specification Parser::nextSpecification()
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
        std::cout << shape << " " << colour << std::endl;
        return parseSpecification(shape, colour);
    }

    Specification specification{
        .shape = Shape::NO_SHAPE,
        .colour = Colour::NO_COLOUR
    };
    return specification;
}   