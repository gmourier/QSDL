#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initScreen(unsigned int  w, unsigned int  h, const char * title) {
 
  if (w < 1 || h < 1) {
    printf("ERROR: width / height are invalid\n");
    return -1;
  }
  
  //SDL_INIT_EVERYTHING flag to init all SDL components
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("ERROR: Unable to init SDL: %s\n", SDL_GetError());	
    SDL_Quit();
    return -1;
  }

  //Init window
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("ERROR: Unable to create window: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  //Init renderer to take advantage of GPU 
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    printf("ERROR: Unable to create renderer: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  
  return 0;
}


SDL_Surface* loadTexture(const char * fpath) {
  SDL_Surface* texture = NULL;

  if (strlen(fpath) == 0) {
    printf("ERROR: No path given\n");
  }
  else {
    texture = SDL_LoadBMP(fpath);
    if (texture == NULL) {
      printf("ERROR: %s\n", SDL_GetError());
    }
  }

  return texture;
}

int main() {
  initScreen(640, 480, "Main");
  SDL_Quit();
  return EXIT_SUCCESS;
}	
