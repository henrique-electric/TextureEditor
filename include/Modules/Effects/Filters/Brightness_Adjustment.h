#include <dlib/image_io.h>

#include "Modules/Textures/Exporter.h"
#include "Modules/Textures/Loader.h"
#include "Modules/States/EditorState.h"

class Brightness_Adjustment
{
    float alpha;
    int beta;
    dlib::array2d<dlib::rgb_alpha_pixel> in_image;
    dlib::array2d<dlib::rgb_alpha_pixel> out_image;
public:
    Brightness_Adjustment()
    {
    }

    bool load(const std::string &filename);
    bool apply(const float &alpha, const int &beta, Loader &loader, sdl_state *sdl_pstate);
};
