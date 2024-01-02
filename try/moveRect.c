#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
int MOVE_SPEED = 2;
void moveRectangle(int *x1, int *x2, int target1, int target2) {
    if (*x1 != target1) {
        if (*x1 < target1) {
            *x1 += MOVE_SPEED;
        } else {
            *x1 -= MOVE_SPEED;
        }
    }

    if (*x2 != target2) {
        if (*x2 < target2) {
            *x2 += MOVE_SPEED;
        } else {
            *x2 -= MOVE_SPEED;
        }
    }
}
