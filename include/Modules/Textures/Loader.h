#pragma once

#include "common.h"

class Loader
{
    SDL_Surface *surface{NULL};
    SDL_Texture *texture{NULL};

    bool is_texture{false};

    std::string file_path;

public:
    Loader()
    {
    }
    SDL_Texture *texture_load(const char *filePath, SDL_Renderer *renderer, SDL_FRect *src);

    SDL_Surface *get_surface() const
    {
        return this->surface;
    }

    SDL_Texture *get_texture() const
    {
        return this->texture;
    }

    bool is_texture_loaded()
    {
        return this->is_texture;
    }

    void set_file_path(const std::string path)
    {
        this->file_path = path;
    }

    std::string get_file_path()
    {
        return this->file_path;
    }

    void cleanup();
};