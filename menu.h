#ifndef MENU_H
#define MENU_H

#include "hashtable.h"
#include <string>
#include <fstream>
using namespace std;

class Menu{

	private:
		HashTable* movieTable;
		int GetSelection();
		void AddMovie();
		void SearchMovie();
	public:
		Menu();
		void LoadMovies(string fileName);
		HashTable* GetMovieTable();
		void StartMenu();


};




#endif
