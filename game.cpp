#include "SDL2/SDL.h"
#include <iostream>
#include <vector>

using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = SCREEN_WIDTH;

vector<vector<int>> grid(4, vector<int>(4, 0));

void clearBackground()
{
    SDL_SetRenderDrawColor(renderer, 150, 121, 105, 255);
    SDL_RenderClear(renderer);
    SDL_RenderSetViewport(renderer, NULL);
    SDL_SetRenderTarget(renderer, NULL);
}

void renderGrid()
{
    int tileSize = SCREEN_WIDTH / 5;
    int spacing = SCREEN_WIDTH / 25;
    int gridSize = 4 * tileSize + 3 * spacing;
    int offsetX = (SCREEN_WIDTH - gridSize) / 2;
    int offsetY = (SCREEN_HEIGHT - gridSize) / 2;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            int value = grid[i][j];
            if (value == 0)
            {
                SDL_SetRenderDrawColor(renderer, 196, 164, 132, 255); // Empty tile color
            }
            else if (value == 2)
            {
                SDL_SetRenderDrawColor(renderer, 234, 221, 202, 255); // Color for 2
            }
            else if (value == 4)
            {
                SDL_SetRenderDrawColor(renderer, 218, 160, 109, 255); // Color for 4
            }

            SDL_Rect tile = {offsetX + j * (tileSize + spacing), offsetY + i * (tileSize + spacing), tileSize, tileSize};
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

vector<vector<int>> generateFirstNumbers()
{
    vector<vector<int>> grid(4, vector<int>(4, 0));
    int x1 = rand() % 4;
    int y1 = rand() % 4;
    int x2, y2;

    do
    {
        x2 = rand() % 4;
        y2 = rand() % 4;
    } while (x1 == x2 && y1 == y2);

    grid[x1][y1] = 2;
    grid[x2][y2] = 4;

    return grid;
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

        srand(time(0));

        SDL_Event e;
        bool quit = false;

        grid = generateFirstNumbers();

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