#include <SDL2/SDL.h>
#include <stdio.h>

// Taille du carr�
#define SQUARE_SIZE 50

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Cr�ation de la fen�tre
    SDL_Window *window = SDL_CreateWindow("Carr� SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la cr�ation de la fen�tre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Cr�ation du rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la cr�ation du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Effacer le rendu
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur de fond blanche
        SDL_RenderClear(renderer);

        // Dessiner le carr�
        SDL_Rect square = { 375, 275, SQUARE_SIZE, SQUARE_SIZE }; // Position du carr�
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Couleur rouge
        SDL_RenderFillRect(renderer, &square);

        // Mettre � jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Lib�rer les ressources et quitter SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



