#ifndef MOVIELIST_H
#define MOVIELIST_H

#include "movie.h"
#include <string>
#include <vector>
#include <iostream>
#include <list>
using namespace std;

class MovieList{
	
	private:
		Movie* head;
	public:
		MovieList();
		void Insert(string title, string leadActorActress, string description, int yearReleased);
		void Insert(Movie* movie);
		bool Delete(string title);
		Movie* Search(string title);
		Movie* DetachAndGetFirst();
		vector<Movie> GetElements();
		void PrintList();
};

#endif
