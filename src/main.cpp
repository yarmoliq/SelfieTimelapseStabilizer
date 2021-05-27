#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <math.h>
#include <filesystem>

#include "visualize/visualize.h"
#include "imgManipulation/manipulation.h"
#include "creatingVideo/creatingVideo.h"

using namespace cv;
using namespace face;
namespace fs = std::filesystem;

const unsigned int OUTPUT_WIDTH  = 3840;
const unsigned int OUTPUT_HEIGHT = 2160;

class IInputStrategy
{
public:
    virtual ~IInputStrategy() {}
    virtual std::vector<std::string> loadParams() const = 0;
};

class InputParams
{
protected:
    InputParams(){};
    static InputParams* instance;
    std::vector<std::string> params;

    IInputStrategy* inputStrategy;

    InputParams(InputParams& other);
    void operator=(const InputParams&) = delete;
public:

    static InputParams& getInstance();

    void setInputStrategy(IInputStrategy* strat) { inputStrategy = strat; }

    void loadParams()
    {
        params = inputStrategy->loadParams();
    }

    const std::string operator[](size_t i) const
    {
        return params[i];
    }

    // ~InputParams()
    // {
    //     delete inputStrategy;
    //     delete instance;
    // }
};

InputParams* InputParams::instance = nullptr;
InputParams& InputParams::getInstance()
{ 
        if(instance == nullptr)
            instance = new InputParams();

        return *instance;
}

class ArgvInputStrategy : public IInputStrategy
{
    std::vector<std::string> _argv;
public:
    void setArgv(char** argv)
    {
        _argv = std::vector<std::string> { argv[1], argv[2], argv[3] };
    }

    std::vector<std::string> loadParams() const override { return _argv; }
};

class ConsoleInputStrategy : public IInputStrategy
{
    std::vector<std::string> loadParams() const override
    {
        std::vector<std::string> params(3);
        std::cout << "Path to reference photo: ";
        std::getline(std::cin, params[0], '\n');
        std::cout << "Path to input folder: ";
        std::getline(std::cin, params[1], '\n');
        std::cout << "Path to output folder: ";
        std::getline(std::cin, params[2], '\n');
        return params;
    }
};

int main(int argc, char **argv)
{
    if(argc == 4)
    {
        auto strat = new ArgvInputStrategy();
        strat->setArgv(argv);
        InputParams::getInstance().setInputStrategy(strat);
    }
    else
    {
        InputParams::getInstance().setInputStrategy(new ConsoleInputStrategy);
    }

    InputParams::getInstance().loadParams();
        
    Mat reference = imread(InputParams::getInstance()[0], IMREAD_COLOR);

    loadModels();

    setReferencePoints(reference);

    Mat output(OUTPUT_HEIGHT, OUTPUT_WIDTH, CV_8UC3);

    std::string outDir = InputParams::getInstance()[2];
    fs::create_directory(outDir);
    fs::create_directory(outDir + "photos/");

    VideoWriter video;
    createVideoWritter(video, outDir + "result0.avi", Size(OUTPUT_WIDTH, OUTPUT_HEIGHT), 10);

    size_t counter = 0;
    for (const auto & entry : fs::directory_iterator(InputParams::getInstance()[1]))
    {
        Mat img = imread(entry.path(), IMREAD_COLOR);
        warpStabilize(img, output, reference);
        addImageToVideo(video, output);
        imwrite(outDir + "photos/" + std::to_string(counter++) + ".jpg", output);
    }

    renderVideo(video);
    return 0;
}
