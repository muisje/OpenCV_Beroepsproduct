/**
 * @file batch_parser.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief parsing for batch files of specifications
 * @version 0.1
 * @date 2019-03-02
 * 
 */
#ifndef BATCH_PARSER_H
#define BATCH_PARSER_H

#include "language.h"
#include "specification.h"
#include <fstream>
/**
 * @brief Class made to easily parse batch files containing specifications
 * 
 */
class BatchParser
{
private:
    std::ifstream * file;
    Language language;

public:
    BatchParser(std::string filename, Language language = Language::ENGLISH);
    ~BatchParser();

    /**
     * @brief reads the next line of batch file and returns it as a specification
     * 
     * @return Specification of the new line
     */
    Specification nextSpecification();
};

#endif