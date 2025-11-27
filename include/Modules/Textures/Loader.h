#pragma once

#include "common.h"

typedef struct Loader
{
    SDL_Texture *texture{NULL};

    bool is_texture{false};

    std::string filename_path;
    SDL_Texture *texture_load(const char *filePath, SDL_Renderer *renderer, SDL_FRect *src);
    void cleanup();
} Loader;