#ifndef PARSER_H
#define PARSER_H

#include "specification.h"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/optional.hpp>

class Parser
{
private:
    std::ifstream * file;

public:
    Parser(std::string filename);
    ~Parser();

    Specification nextSpecification();
};

#endif