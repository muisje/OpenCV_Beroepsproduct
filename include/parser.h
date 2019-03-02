/**
 * @file parser.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief parsing for batch files of specifications
 * @version 0.1
 * @date 2019-03-02
 * 
 */
#ifndef PARSER_H
#define PARSER_H

#include "language.h"
#include "specification.h"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/optional.hpp>

class Parser
{
private:
    std::ifstream * file;
    Language language;

public:
    Parser(std::string filename, Language language = Language::ENGLISH);
    ~Parser();

    /**
     * @brief reads the next line of batch file and returns it as a specification
     * 
     * @return Specification of the new line
     */
    Specification nextSpecification();
};

#endif