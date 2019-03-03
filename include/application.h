/**
 * @file application.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief Provides a class with functions to run the application in different modes. Before you call a function that starts with run call a function that starts with init. 
 * If you desire to specify the specification without the batch or interactive mode use setSpecification.
 * @version 0.1
 * @date 2019-03-03
 * 
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "language.h"
#include "specification.h"
#include <thread>
#include <atomic>

/**
 * @brief Application class that provides the an easy interface of the core program.
 * 
 */
class Application
{
private:

    std::thread * stream;
    Language language;
    std::atomic<bool> exitProgram;
    std::atomic<bool> needToPrint;
    std::atomic<Specification> specification;
    
    void initInteractiveMode();

public:
    Application(Language language = Language::DUTCH);
    ~Application();

    /**
     * @brief initializes a live image from a webcam.
     * 
     * @param camera the camera (default is = 0)
     */
    void initLiveCamera(short camera = 0);

    /**
     * @brief initializes a static image from a given file name.
     * 
     * @param fileName the name of the image desired to use.
     */
    void initStaticImage(const std::string & fileName);

    /**
     * @brief runz the interactive mode. In the shell the user can specify the specifications.
     * 
     */
    void runInteractiveMode();

    /**
     * @brief runs the batch mode. In the file the user can specify the specifications line by line. Every starting with "#" is ignored till the new line.
     * 
     * @param fileName the name of the batch desired to use.
     */
    void runBatchMode(const std::string & fileName);

    /**
     * @brief Set the Specification object
     * 
     * @param aSpecification
     */
    void setSpecification(Specification aSpecification);
};


#endif // APPLICATION_H