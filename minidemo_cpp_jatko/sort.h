#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <exception>

#include <SDL.h>

//! pancake and gnome sorting algorithsm from https://www.geeksforgeeks.org/

//! print the vector to the console
void print_array(std::vector<int> v, int n)
{
	for (int i = 0; i < n; ++i)
		std::cout << v[i] << " ";
}

//! this function is called every time the vector is updated/changed and we want to draw the new state of the sorting
void draw_state(std::vector<int>& v, SDL_Renderer* r, int sorted = -1, int max_val = -1) {
	int index;

	//! draw black screen
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderClear(r);

	for (int i = v.size() - 1; i > 0; --i) {
		int index = v[i];

		//! last sorted line will be pink
		if (i == sorted) {
			SDL_SetRenderDrawColor(r, 255, 0, 255, 255);
		}
		//! red line indicating the max value
		else if (i == max_val) {
			SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		}
		//! the rest will be white
		else {
			SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		}
		
		SDL_RenderDrawLine(r, i, 0, i, index);

		//SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
		//SDL_RenderDrawPoint(r, i, index);
		index--;
	}

	//! update the screen with any rendering performed since previous call
	SDL_RenderPresent(r);
	SDL_Delay(100);
}

/* ------------------------------------------ PANCAKE SORT ------------------------------------------ */

//! help function for pancake sort: flips the vector[0...i]
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

//! main function for pancake sort algorithm
void pancake_sort(std::vector<int>& v, int n, SDL_Renderer* r) {
	std::cout << "PANCAKE!!!\n";

	for (int current_size = n; current_size > 1; --current_size) {
		//! help (lambda)function for pancake sort: return the index of the max value in given vector
		auto find_max = [](std::vector<int>& v, int n) {
			int mi, i;

			for (mi = 0, i = 0; i < n; ++i) {
				if (v[i] > v[mi]) {
					mi = i;
				}
			}
			return mi;
		};

		int max_i = find_max(v, current_size);

		draw_state(v, r, current_size, max_i);

		if (max_i != current_size - 1) {
			//! move max to beginning
			flip(v, max_i);

			//! move max to end by reversing current vector
			flip(v, current_size - 1);
		}
	}
	
	std::cout << "sorted: ";
	print_array(v, n);
}

/* ------------------------------------------ GNOME SORT ------------------------------------------ */

//! based on garden gnome sorting flower pots. compares two values (or pots) and if they are in the right order, continues forward. 
//! if not, two values are swapped until the order is right and the algorithm (or gnome) can continue
void gnome_sort(std::vector<int>& v, int n, SDL_Renderer* r) {
	std::cout << "GNOME!!!!\n";
	
	int index = 0;
	while (index < n) {
		if (index == 0) index++;

		if (v[index] >= v[index - 1]) {
			index++;
		}
		else {
			std::swap(v[index], v[index - 1]);
			index--;
		}

		draw_state(v, r, index);
	}

	std::cout << "sorted: ";
	print_array(v, n);
}

/* ------------------------------------------ SLEEP SORT ------------------------------------------ */

#define MAX 100
static int lookup_table[MAX] = { 0 };

void draw_vector(std::vector<int>& v, SDL_Renderer* r) {
	//! draw black screen
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderClear(r);

	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

	for (int i = 0; i < MAX; ++i) {

		if (lookup_table[i] == 1) {
			SDL_RenderDrawLine(r, i, 0, i, v[i]);
		}
	}
	SDL_RenderPresent(r);
}

//! sleep sort with a smaller vector 
//! all threads asleep at first
//! "each thread sleeps for an amount of time which is proportional to the value of corresponding array element" 
//! thread wakes up to print the corresponding number
//! lmao what is this 
void sleep_sort(SDL_Renderer* r) {
	std::cout << "SLEEP!!!\n";
	std::vector<int> s = { 13, 2, 4, 5, 1, 6 , 16, 20, 21, 22 }; // max 100

	SDL_RenderSetScale(r, 60, 20); // heh
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderClear(r);
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

	std::vector<std::thread> threads;

	//! loop through the vector, create a new thread for every vector element
	for (int i = 0; i < s.size(); ++i) {
		threads.emplace_back([i, &s, r]() {
			std::this_thread::sleep_for(std::chrono::seconds(s[i]));
			std::cout << s[i] << "\n";

			lookup_table[i] = 1; 
			draw_vector(s, r);
			});
	}

	//! wait for all threads to finish
	for (auto& thread : threads) {
		thread.join();
	}
}
