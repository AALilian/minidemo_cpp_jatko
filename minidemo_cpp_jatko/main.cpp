//#include <algorithm>
#include <random>

#include "sort.h"

int main(int argc, char* args[]) {

	SDL_Window* window = SDL_CreateWindow("Sort", 0, 0, 800, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, 0);
	//SDL_CreateWindowAndRenderer(1200, 640, SDL_FLIP_HORIZONTAL, &window, &renderer);	
	if (window == nullptr || renderer == nullptr) {
		return 1;
	}	

	SDL_Init(SDL_INIT_EVERYTHING);

	//! vectors for pancake sort, gnome sort and sleep sort 
	std::vector<int> p; 
	std::vector<int> g;
	std::vector<int> s = { 13, 2, 4, 5, 1, 6, 16, 20, 21, 22 }; // max 100

	//std::random_device rd;
	//std::uniform_int_distribution d(1, 500);

	for (int i = 0; i < 100; ++i) {
		//v.push_back(d(rd));
		p.push_back(i);
	}

	for (int i = 0; i < 20; ++i) {
		g.push_back(i);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(p.begin(), p.end(), std::default_random_engine(seed));
	std::shuffle(g.begin(), g.end(), std::default_random_engine(seed));

	pancake_sort(p, renderer);

	gnome_sort(g, renderer);

	sleep_sort(s, renderer);

	SDL_Delay(5000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}