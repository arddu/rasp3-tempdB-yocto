#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 480
#define MAX_POINTS 100 // Max points of data on the graph

// Sensor data
int read_temp() {
    return 20 + (rand() % 20);
}

int main(){
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 36);
    if(!font){
        printf("Font could not be loaded. %s\n", TTF_GetError());
    }
    SDL_Event       event;
    SDL_Renderer*   renderer;
    SDL_Window*     window;
    int i;
    int current_temp = 0;
    int data[MAX_POINTS] = {0};
    int x2 = 0;
    int y2 = 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    int running = 1;

    while(running == 1){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    for (int i = 0; i < MAX_POINTS - 1; i++) { // Move old data from right to left
            data[i] = data[i + 1];
        }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Green
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    current_temp = read_temp();
    data[MAX_POINTS - 1] = current_temp;
    for (i = 0; i < MAX_POINTS - 1; i++)
    {
            int x1 = i * (WIN_WIDTH / (MAX_POINTS - 1));
                x2 = (i + 1) * (WIN_WIDTH / (MAX_POINTS - 1));
            int y1 = WIN_HEIGHT - (data[i] * (WIN_HEIGHT / 50)); 
                y2 = WIN_HEIGHT - (data[i + 1] * (WIN_HEIGHT / 50));
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
    if(font){
            char buffer[50];
            sprintf(buffer, "Temp: %d C", current_temp);
            SDL_Color white = {255, 255, 255, 255};
            SDL_Surface* surfText = TTF_RenderText_Solid(font, buffer, white);
            SDL_Texture* textText= SDL_CreateTextureFromSurface(renderer, surfText);

            SDL_Rect text;
            text.x = x2 - 225;
            text.y = 20;
            text.w = surfText->w;
            text.h = surfText->h;
            SDL_RenderCopy(renderer,textText,NULL,&text);
            SDL_DestroyTexture(textText);
            SDL_FreeSurface(surfText);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;

}