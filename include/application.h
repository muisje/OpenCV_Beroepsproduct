#ifndef APPLICATION_H
#define APPLICATION_H

#include "language.h"
#include "specification.h"
#include <thread>
#include <atomic>

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

    void initLiveCamera(short camera);
    void initStaticImage(const std::string & fileName);
    void runInteractiveMode();
    void runBatchMode(const std::string & fileName);

    void setSpecification(Specification aSpecification);
};


#endif // APPLICATION_H