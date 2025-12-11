#pragma once

#include "textures/exporter.h"
#include "textures/loader.h"
#include "states/editor_state.h"

typedef struct _film_grain
{
    std::vector<unsigned char> pixels_data;

    bool load(const std::string &filename, loader &loader);
    bool apply(loader &loader, sdl_state *sdl_pstate, int &strength);
} film_grain;