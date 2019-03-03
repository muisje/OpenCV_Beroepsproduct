#include "include/application.h"

int main(/*int argc, char **argv*/) // Warning unused parameter
{
    Application app;
    // app.initLiveCamera(0);
    app.initStaticImage("../testImages/testImage3.jpg");
    // app.runInteractiveMode();
    app.runBatchMode("../batch.txt");
    // app.setSpecification({Shape::RECTANGLE, Colour::BLUE});
    return 0;
}