#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
#include <string>

class Blur
{
    dlib::array2d<dlib::rgb_pixel> image;

public:
    Blur()
    {
        
    }

    bool load(const std::string &filename);

    bool apply(float &sigma);
};