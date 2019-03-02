/**
 * @file language.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief language utility
 * @version 0.1
 * @date 2019-03-02
 * 
 */
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>

/**
 * @brief Languages that are supported
 * 
 */
enum Language {ENGLISH, DUTCH};

/**
 * @brief convert a known word to english. If the word is not known an empty string ("") is returned;
 * 
 * @param word that will be translated to an English one.
 * @param from the language which it is translated from.
 * @return std::string the translated word.
 */
std::string toEnglish(const std::string & word, enum::Language from = Language::DUTCH);

/**
 * @brief convert a known word to a Dutch one.
 * 
 * @param word the to be translated word.
 * @param from the language which it is translated from.
 * @return std::string the translated word.
 */
std::string toDutch(const std::string & word, enum::Language from = Language::ENGLISH);

/**
 * @brief converts a string to upper case
 * 
 * @param string to converted
 * @return std::string uppercase of given string
 */
std::string toUpper(const std::string & string);

#endif // LANGUAGE_H