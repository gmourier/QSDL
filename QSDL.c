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
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  //Init renderer to take advantage of GPU 
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    printf("ERROR: Unable to create renderer: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return -1;
  }
  
  return 0;
}


SDL_Texture* loadTexture(const char * fpath) {
  
  SDL_Texture* texture = NULL;
  SDL_Surface* surface = NULL;

  if (strlen(fpath) == 0) {
    printf("ERROR: No path given\n");
  }
  else {
    surface  = SDL_LoadBMP(fpath);
    if (surface == NULL) {
      printf("ERROR: %s\n", SDL_GetError());
    }
    else {
      texture = SDL_CreateTextureFromSurface(renderer, surface);
      if (texture == NULL) {
        printf("ERROR: %s\n", SDL_GetError());
	SDL_DestroyTexture(texture);
      }
      SDL_FreeSurface(surface);
    }
  }

  return texture;
}

void drawTexture(SDL_Texture * texture) {
  
  if (texture == NULL) {
    printf("ERROR: Can't draw an undefined texture\n");
  }

  SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void clear() {
  SDL_RenderClear(renderer);
}

void update() {
  SDL_RenderPresent(renderer);
}

//Texture processing helper
void generateTexture(unsigned int  w, unsigned int h, char operator) {
  Uint8 c;

  for(unsigned int x = 0; x < w; x++) {
    for(unsigned int y = 0; y < h; y++) {
      switch (operator) {
        case '^':
	  c = x ^ y;
	  break;
	case '&':
	  c = x & y;
	  break;
	case '|':
	  c = x | y;
	  break;
	default:
	  c = x ^ y;
      }
      SDL_SetRenderDrawColor(renderer, c, c, c, 0xFF);
      SDL_Rect rect = {x, y, 1, 1};
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

int main() {
  initScreen(640, 480, "Main");
  
  clear();
  generateTexture(256, 256, '^');
  update();

  SDL_Delay(3000);

  renderer = NULL;
  window = NULL;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
  SDL_Quit();
  return EXIT_SUCCESS;
}	
