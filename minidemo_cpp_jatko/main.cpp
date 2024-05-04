#include <algorithm>
#include <random>

#include "sort.h"

int main(int argc, char* args[]) {

	SDL_Window* window = SDL_CreateWindow("Nimi", 0, 0, 1200, 640, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, 0);

	if (window == nullptr || renderer == nullptr) {
		return 1;
	}

	//SDL_CreateWindowAndRenderer(1200, 640, SDL_FLIP_HORIZONTAL, &window, &renderer);	
	SDL_RenderSetScale(renderer, 6, 1);

	SDL_Init(SDL_INIT_EVERYTHING);

	std::vector<int> v;
	std::random_device rd;
	std::uniform_int_distribution d(1, 500);

	for (int i = 0; i < 200; ++i) {
		v.push_back(d(rd));
	}
	int n = v.size();

	pancake_sort(v, n, renderer);

	//gnome_sort(v, n, renderer);

	//sleep_sort(renderer);

	SDL_Delay(5000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}