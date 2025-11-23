#include <string>
#include <dlib/image_io.h>

class Edge_Enhancement
{
    dlib::array2d<dlib::rgb_alpha_pixel> image;

public:
    Edge_Enhancement()
    {

    }

    bool load(const std::string &filename);
    bool apply(int &idx);

};