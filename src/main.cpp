#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include "imfilebrowser.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <iostream>

SDL_Texture *LoadTexture(const char *filePath, SDL_Renderer *renderer, SDL_FRect *src)
{

    SDL_Surface *surface = IMG_Load(filePath);
    if (!surface)
    {
        std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        return NULL;
    }

    src->w = texture->w;
    src->h = texture->h;

    SDL_DestroySurface(surface);

    return texture;
}

SDL_FRect src_texture = {
    .x = 0.0f,
    .y = 0.0f,
    .w = 0.0f,
    .h = 0.0f};

SDL_FRect dst_texture = {
    .x = 400.0f,
    .y = 200.0f,
    .w = 400.0f,
    .h = 400.0f};

SDL_Texture *texture = NULL;
bool is_texture_dragging = false;
float drag_offset_x = 0.0f, drag_offset_y = 0.0f;

bool is_dragging(SDL_FRect *dst_rect, const float *mouse_x, const float *mouse_y, float *drag_offset_x, float *drag_offset_y)
{
    // Check if mouse click collides with the texture's dst_rect
    if (*mouse_x >= dst_rect->x && *mouse_x < dst_rect->x + dst_rect->w &&
        *mouse_y >= dst_rect->y && *mouse_y < dst_rect->y + dst_rect->h)
    {
        // Calculate offset to keep the drag relative to click position
        *drag_offset_x = *mouse_x - dst_rect->x;
        *drag_offset_y = *mouse_y - dst_rect->y;
        return true;
    }
    return false;
}

// Main code
int main(int, char **)
{
    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return 1;
    }

    // Create window with SDL_Renderer graphics context
    SDL_Window *window = SDL_CreateWindow("Texture Editor v0.0.1",
                                          1280, 720,
                                          SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        printf("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return 1;
    }

    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    // Texture module

    const ImVec2 init_position{10.0f, 10.0f};
    const ImVec2 init_size{250.0f, (float)height - 30.0f};

    int init_window_flags = 0;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style appearance
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Load Fonts
    ImGuiIO &io_fonts = ImGui::GetIO();
    io_fonts.Fonts->AddFontDefault();

    init_window_flags |= ImGuiWindowFlags_NoMove;
    init_window_flags |= ImGuiWindowFlags_NoCollapse;
    init_window_flags |= ImGuiWindowFlags_NoResize;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // File Dialog for textures
    ImGui::FileBrowser fileDialog;

    // (optional) set browser properties
    fileDialog.SetTitle("Choose Texture");
    fileDialog.SetTypeFilters({".png", ".jpeg", ".jpg", ".bmp"});

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
                done = true;

            switch (event.type)
            {
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    float mouse_x = event.button.x;
                    float mouse_y = event.button.y;
                    is_texture_dragging = is_dragging(&dst_texture, &mouse_x, &mouse_y, &drag_offset_x, &drag_offset_y);
                }
                break;

            case SDL_EVENT_MOUSE_MOTION:
                if (is_texture_dragging)
                {
                    // Update dst_rect position based on mouse motion
                    dst_texture.x = event.motion.x - drag_offset_x;
                    dst_texture.y = event.motion.y - drag_offset_y;
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_texture_dragging = false; // Release the texture
                }
                break;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Texture", NULL, init_window_flags);

        ImGui::SetWindowPos(init_position);
        ImGui::SetWindowSize(init_size);

        if (ImGui::CollapsingHeader("File"))
        {
            ImGui::SeparatorText("Select your texture");
            if (ImGui::Button("Open"))
            {
                fileDialog.Open();
            }
        }

        ImGui::End();

        fileDialog.Display();

        if (fileDialog.HasSelected())
        {
            std::cout << "Selected filenames " << std::endl;

            for (auto selected : fileDialog.GetMultiSelected())
            {
                std::cout << "File: " << selected.string() << std::endl;
                texture = LoadTexture(selected.c_str(), renderer, &src_texture);
            }

            fileDialog.ClearSelected();
        }

        // Rendering
        ImGui::Render();

        ImGui::EndFrame();

        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        if (texture)
        {
            SDL_RenderTexture(renderer, texture, &src_texture, &dst_texture);
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}