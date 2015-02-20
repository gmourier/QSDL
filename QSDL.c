#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//SDL_Window / SDL_Renderer init func
int init_screen(unsigned int  w, unsigned int  h, const char * title) {
 
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

  //Init renderer to take advantage of GPU Vram 
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("ERROR: Unable to create renderer: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  
  return 0;
}

int main(int argc, const char * argv[]) {
  unsigned int width = 600;
  unsigned int height = 600;

  if (init_screen(width, height, "test") == 0) {
    SDL_Delay(2000);
  }
  SDL_Quit();

  return EXIT_SUCCESS;
}	
