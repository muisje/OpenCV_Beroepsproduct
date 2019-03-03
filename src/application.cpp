#include "../include/application.h"
#include "../include/printer.h"
#include "../include/batch_parser.h"
#include "../include/detection.h"
#include <atomic>
#include <iterator>

using namespace std::literals::chrono_literals;

Application::Application(Language language)
    : language(language)
{
    Specification initSpecification;
    initSpecification.colour = Colour::UNKNOWN_COLOUR;
    initSpecification.shape = Shape::UNKNOWN_SHAPE;
    specification.store(initSpecification);
    exitProgram.store(false);
    needToPrint.store(false);
}

Application::~Application()
{
    stream->join();
    delete stream;
}

void Application::initLiveCamera(short camera)
{
    //TODO add language
    stream = new std::thread(Detection::detectAndDrawLive, &exitProgram, &specification, &needToPrint, language, camera);
    std::this_thread::sleep_for(1s); // Wait for camara to turn on
}

void Application::initStaticImage(const std::string & fileName)
{
    stream = new std::thread(Detection::detectAndDrawStatic, &exitProgram, &specification, &needToPrint, fileName, language);
}

void Application::initInteractiveMode()
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
}

void Application::runInteractiveMode()
{
    this->initInteractiveMode();
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
            specification.store(tempSpec);
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


void Application::runBatchMode(const std::string & fileName)
{
    BatchParser batch(fileName, language);
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
            specification.store(currentSpec);
            needToPrint.store(true);
            std::this_thread::sleep_for(1000ms);
        }
    }
}

void Application::setSpecification(Specification aSpecification)
{
    specification.store(aSpecification);
}