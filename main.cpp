#include "include/printer.h"
#include "include/batch_parser.h"
#include <thread>
#include <iterator>
#include <chrono>
#include "include/language.h"
#include "include/specification.h"
#include <atomic>

#include "include/detection.h"

using namespace std::literals::chrono_literals;
Language language = Language::DUTCH;
SpecificationMode specMode = SpecificationMode::INTERACTIVE;
bool live = true;
std::atomic<bool> exitProgram(false);
std::atomic<bool> needToPrint(false);
std::atomic<Specification> spec;
int main(/*int argc, char **argv*/) // Warning unused parameter
{
    Specification initSpec;
    switch (specMode)
    {
    case SpecificationMode::PRE_DEFINED:
        initSpec.colour = Colour::YELLOW;
        initSpec.shape = Shape::CIRCLE;
        break;

    default:
        initSpec.colour = Colour::UNKNOWN_COLOUR;
        initSpec.shape = Shape::UNKNOWN_SHAPE;
        break;
    }
    spec.store(initSpec);
    std::thread stream(Detection::detectAndDraw, live, &exitProgram, &spec, &needToPrint, language);

    if (specMode == SpecificationMode::INTERACTIVE)
    {
        switch (language)
        {
        case Language::ENGLISH:
            Printer::print("Enter: [shape][whitespace][colour]");
            break;

        case Language::DUTCH:
            Printer::print("Voer in: [vorm][whitespace][kleur]");
            break;

        default:
            Printer::print("Warning: unsupported language");
            break;
        }
        while (!exitProgram.load())
        {
            std::string input;

            std::getline(std::cin, input);
            if (input == "exit")
            {
                exitProgram.store(true);
            }
            std::istringstream iss(input);
            std::string shape;
            std::string colour;
            std::vector<std::string> pieces;

            std::copy(std::istream_iterator<std::string>(iss),
                      std::istream_iterator<std::string>(), back_inserter(pieces));
            if (pieces.size() >= 2)
            {
                Specification tempSpec;

                std::string colour = toEnglish(toUpper(pieces[0]), language);
                std::string shape = toEnglish(toUpper(pieces[1]), language);
                tempSpec = parseSpecification(colour, shape);
                spec.store(tempSpec);
                if (tempSpec.colour == UNKNOWN_COLOUR || tempSpec.shape == UNKNOWN_SHAPE)
                {
                    Printer::print("Unknown colour or shape!");
                }
            }
            else
            {
                Printer::print("Unknown colour or shape!");
            }
        }
    }
    else if (specMode == SpecificationMode::BATCH)
    {
        if (live)
        {
            std::this_thread::sleep_for(2s); // Wait for camara to turn on
        }
        std::string batchFile;
        if (language == Language::DUTCH)
        {
            batchFile = "../batch.txt";
        }
        else
        {
            batchFile = "../batch_english.txt";
        }

        BatchParser batch(batchFile, language);
        int batchNumber = 0;
        while (!exitProgram.load())
        {
            Specification currentSpec = batch.nextSpecification();
            ++batchNumber;

            if (currentSpec.shape == Shape::NO_SHAPE || currentSpec.colour == Colour::NO_COLOUR)
            {
                exitProgram.store(true);
            }
            else if (
                currentSpec.shape == Shape::UNKNOWN_SHAPE || currentSpec.colour == Colour::UNKNOWN_COLOUR)
            {
                Printer::printUnknown(batchNumber);
            }
            else
            {
                spec.store(currentSpec);
                needToPrint.store(true);
                std::this_thread::sleep_for(1000ms);
            }
        }
    }
    stream.join();
    return 0;
}