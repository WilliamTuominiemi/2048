#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = SCREEN_WIDTH;

void clearBackground()
{
    SDL_SetRenderDrawColor(renderer, 193, 154, 107, 255);
    SDL_RenderClear(renderer);
    SDL_RenderSetViewport(renderer, NULL);
    SDL_SetRenderTarget(renderer, NULL);
}

void renderGrid()
{
    SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255);
    int tileSize = SCREEN_WIDTH / 5;
    int spacing = SCREEN_WIDTH / 25;
    int gridSize = 4 * tileSize + 3 * spacing;
    int offsetX = (SCREEN_WIDTH - gridSize) / 2;
    int offsetY = (SCREEN_HEIGHT - gridSize) / 2;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
            SDL_Rect tile = {offsetX + j * (tileSize + spacing), offsetY + i * (tileSize + spacing), tileSize, tileSize};
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Failed to initialize SDL: %s\n"
             << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cerr << "Failed to create window: %s\n"
             << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        cerr << "Failed to create renderer: %s\n"
             << SDL_GetError() << endl;
        return false;
    }

    clearBackground();

    return true;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

int main(int argc, char *args[])
{
    if (!init())
    {
        cout << "Failed to initialize. " << endl;
    }
    else
    {
        cout << "Initialized. " << endl;

        SDL_Event e;
        bool quit = false;

        clearBackground();

        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;
                }
            }

            clearBackground();
            renderGrid();
            SDL_RenderPresent(renderer);
        }
    }

    close();

    return 0;
}