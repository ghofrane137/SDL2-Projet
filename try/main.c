#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include"utils.h"
int main(int argc, char *argv[]) {
    int n ;
    do {
            printf("Enter a the number of values");
            scanf("%d", &n);
        } while (n > 10 );

    int tab[10];
    for (int i = 0; i < n; i++) {
        do {
            printf("Enter a value for tab[%d]: ", i);
            scanf("%d", &tab[i]);
        } while (tab[i] > 10 || tab[i] == 0);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, 0);

    if (window == NULL || Renderer == NULL) {
        printf("SDL CreateWindow or CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        printf("SDL_ttf Init Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (font == NULL) {
        printf("Font could not be loaded! TTF_Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    buttons button[5];
    button[4].button = (SDL_Rect){800, 0, 200, 50};
      button[3].button = (SDL_Rect){0, 0, 200, 50};
    button[0].button = (SDL_Rect){200, 0, 200, 50};
    button[1].button = (SDL_Rect){400, 0, 200, 50};
    button[2].button = (SDL_Rect){600, 0, 200, 50};
    SDL_Rect rectangles[10];

    int delayTime = 50;
    bool run = true;

    while (run) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        if (mouseX >= button[0].button.x && mouseX < button[0].button.x + button[0].button.w &&
                            mouseY >= button[0].button.y && mouseY < button[0].button.y + button[0].button.h) {
                            printf("Button 1 clicked!\n");
                            int j = 300;
                            for (int i = 0; i < n; i++) {
                                rectangles[i] = (SDL_Rect){j, 1000 - 350 - tab[i] * 50, 50, tab[i] * 50};
                                j = j + 70;
                            }
                        } else if (mouseX >= button[1].button.x && mouseX < button[1].button.x + button[1].button.w &&
                                   mouseY >= button[1].button.y && mouseY < button[1].button.y + button[1].button.h) {
                            printf("Button 2 clicked!\n");
                            run = false;
                        } else if (mouseX >= button[2].button.x && mouseX < button[2].button.x + button[2].button.w &&
                                   mouseY >= button[2].button.y && mouseY < button[2].button.y + button[2].button.h) {
                            printf("Button 3 clicked!\n");
                            int j = 300;
                            for (int i = 0; i < n; i++) {
                                rectangles[i] = (SDL_Rect){j, 1000 - 350 - tab[i] * 50, 50, tab[i] * 50};
                                j = j + 70;
                            }

                        } else if (mouseX >= button[3].button.x && mouseX < button[3].button.x + button[3].button.w &&
                                   mouseY >= button[3].button.y && mouseY < button[3].button.y + button[3].button.h) {
                            printf("Button 4 clicked!\n");

                        } else if (mouseX >= button[4].button.x && mouseX < button[4].button.x + button[4].button.w &&
                                   mouseY >= button[4].button.y && mouseY < button[4].button.y + button[4].button.h) {
                            printf("Button 5 clicked!\n");

                        }
                        break;
                    }
            }
        }

        SDL_SetRenderDrawColor(Renderer, 220, 220, 220, 220);
        SDL_RenderClear(Renderer);

        drawRectangles(Renderer, rectangles, tab, n, font);
        SDL_Color textColor = {255, 255, 255, 255};
        const char *buttonText = "remove";
         drawButton(Renderer, button[3], font, buttonText, textColor);
        buttonText = "Show";
        drawButton(Renderer, button[0], font, buttonText, textColor);
        buttonText = "quit";
        drawButton(Renderer, button[1], font, buttonText, textColor);
        buttonText = "ordre";
        drawButton(Renderer, button[2], font, buttonText, textColor);
        buttonText = "add";
        drawButton(Renderer, button[4], font, buttonText, textColor);

        SDL_RenderPresent(Renderer);
    }

    close(font, Renderer, window);

    return 0;
}
