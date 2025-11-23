#include "Modules/Effects/Filters/Blur.h"

bool Blur::load(const std::string &filename)
{
    try
    {
        dlib::load_image(image, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool Blur::apply(float &sigma)
{
    static int counter = 0;
    try
    {
        dlib::gaussian_blur(
            image,
            image,
            sigma,
            1001);
        
        std::string final_string = "exported_blur";
        final_string.append(std::to_string(counter++));
        final_string.append(".png");

        const std::string file_output = final_string;
        dlib::save_png(image, file_output);

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}