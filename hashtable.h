#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "movie.h"
#include "movielist.h"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class HashTable{

	private:
		MovieList* table;
		int size;
		double movieCount;
		void Resize();
		void Merge(vector<Movie>& allMovies, int left, int middle, int right);
		void Sort(vector<Movie>& allMovies, int left, int right);
	public:
		HashTable();
		HashTable(int size);
		~HashTable();
		int Hash(string key);
		int GetSize();
		void Insert(string title, string leadActorActress, string description, int yearReleased);
		bool Delete(string title);
		Movie* Search(string title);
		void PrintYearFrequency();
		void PrintTable();
		void PrintSorted();

};

#endif
