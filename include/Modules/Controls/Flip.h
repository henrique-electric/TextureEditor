
typedef struct _flip
{
    SDL_FlipMode flag;

    void controls(SDL_Event &event, message_state &message_vstate)
    {
        if (event.key.key == SDLK_H)
        {
            flag = SDL_FLIP_HORIZONTAL;

            message_vstate.init = true;
            message_vstate.message = "Flipped Horizontally";
        }

        if (event.key.key == SDLK_V)
        {
            flag = SDL_FLIP_VERTICAL;

            message_vstate.init = true;
            message_vstate.message = "Flipped Vertically";
        }

        if (event.key.key == SDLK_P)
        {
            flag = SDL_FLIP_NONE;

            message_vstate.init = true;
            message_vstate.message = "No Flip ( Default )";
        }
    }

} flip;
