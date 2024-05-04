#include "sort.h"

/* ------------------------------------------ PANCAKE SORT ------------------------------------------ */
void draw_state(std::vector<int>& v, SDL_Renderer* r, int sorted, int max_val) {
	int index;

	//! draw black screen
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderClear(r);

	for (int i = 0; i < v.size(); ++i) {
		int index = v[i];

		//! lines are pink, if they have been sorted
		if (i >= sorted) {
			SDL_SetRenderDrawColor(r, 255, 0, 255, 255);
			SDL_RenderDrawLine(r, i, 0, i, index);
		}
		//! red line indicating the max value
		else if (i == max_val) {
			SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
			SDL_RenderDrawLine(r, i, 0, i, index);
		}
		//! the rest will be white
		else {
			SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
			SDL_RenderDrawLine(r, i, 0, i, index);
		}
		//SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
		//SDL_RenderDrawPoint(r, i, index);
		index++;
	}

	//! update the screen with any rendering performed since previous call
	SDL_RenderPresent(r);
	SDL_Delay(100);
}

void flip(std::vector<int>& v, int i) {
	int temp, start = 0;
	while (start < i) {
		temp = v[start];
		v[start] = v[i];
		v[i] = temp;
		start++;
		i--;
	}
}

int find_max(std::vector<int>& v, int n) {
	int mi, i;

	for (mi = 0, i = 0; i < n; ++i) {
		if (v[i] > v[mi]) {
			mi = i;
		}
	}

	return mi;
}

void pancake_sort(std::vector<int>& v, int n, SDL_Renderer* r) {
	for (int current_size = n; current_size > 1; --current_size) {
		int max_i = find_max(v, current_size);

		draw_state(v, r, current_size, max_i);

		if (max_i != current_size - 1) {
			//! move max to beginning
			flip(v, max_i);

			//! move max to end by reversing current vector
			flip(v, current_size - 1);
		}
	}
}

/* ------------------------------------------ PANCAKE SORT ------------------------------------------ */