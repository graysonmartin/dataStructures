#include "hashtable.h"

	HashTable::HashTable(){
		size = 13;
		table= new MovieList[size];
		movieCount = 0;
	}

	HashTable::HashTable(int sizeR){
		size = sizeR;
		table = new MovieList[sizeR];
	}

	HashTable::~HashTable(){
		/**
		MovieList* ptr;
		string title;

		
		for(int i = 0; i < size; i++){
			ptr = &table[i];

			while(ptr != nullptr){
				Movie* tempPtr = ptr->DetachAndGetFirst();
				ptr->Delete(tempPtr->GetTitle());
				delete tempPtr;
			}	
		}

		delete[] table;
		*/
	}

	void HashTable::Resize(){
		int oldSize = GetSize();
		int newSize = oldSize * 2;
		size = size * 2;
		Movie* ptr;
		HashTable newTable(newSize);
		string first;
		string second;
		string third;
		int number; 

		for(int i = 0; i < oldSize; i++){
			ptr = table[i].DetachAndGetFirst();

			if(ptr != nullptr){
				first = ptr->GetTitle();
				second = ptr->GetLeadActorActress();
				third = ptr->GetDescription();
				number = ptr->GetYearReleased();
				newTable.Insert(first, second, third, number);
			}
		}

		delete[] table;
		table = newTable.table;
		
		// probably have to delete new table
	}
	
	void HashTable::Merge(vector<Movie>& allMovies, int left, int middle, int right){
	

		/**
		 * Mostly used chapter 15.4 example for this. 
		 */

		int* mergedNumbers = new int [right - left + 1];
		int leftPos = left;
		int rightPos = middle + 1;
		int mergePos = 0;

		while(leftPos <= middle && rightPos <= right){
			if(allMovies.at(leftPos).GetYearReleased()  <= allMovies.at(rightPos).GetYearReleased()){
				mergedNumbers[mergePos] = allMovies.at(leftPos).GetYearReleased();
				leftPos++;
			}
			else{

				mergedNumbers[mergePos] = allMovies.at(rightPos).GetYearReleased();
				middle++;
			}
			mergePos++;
		}

		while(leftPos <= middle){
			mergedNumbers[mergePos] = allMovies.at(leftPos).GetYearReleased();
			leftPos++;
			mergePos++;
		}

		while(rightPos <= right){
			mergedNumbers[mergePos] = allMovies.at(rightPos).GetYearReleased();
			rightPos++;
			mergePos++;
		}

		for(mergePos = 0; mergePos < right - left + 1; mergePos++){
			allMovies.at(leftPos + mergePos).SetYearReleased(mergedNumbers[mergePos]);
		}
	}

	void HashTable::Sort(vector<Movie>& allMovies, int left, int right){
		int middle = 0;

		if(left < right){
			middle = (left + right) / 2;

			Sort(allMovies, left, middle);
			Sort(allMovies, middle+1, right);
			Merge(allMovies, left, middle, right);
		
		}
	}

	int HashTable::Hash(string key){
		int stringHash = 5381;

		for(int i = 0; i < key.length(); i++){
			stringHash = (stringHash * 33) + (int)key.at(i);
		}

	
		return stringHash % GetSize();
	}

	int HashTable::GetSize(){
		return size;
	}

	void HashTable::Insert(string title, string leadActorActress, string description, int yearReleased){
		int bucket = Hash(title);
		double loadFactor;
			
		Movie* newMovie = new Movie(title, leadActorActress, description, yearReleased);
		table[bucket].Insert(newMovie);
		movieCount++;
		
		loadFactor = movieCount / size;
	
		if(loadFactor > 0.5){
			Resize();
		}
		
	}

	bool HashTable::Delete(string title){
		int bucketNum = Hash(title);
		Movie* newMovie = Search(title);

		if(newMovie != nullptr){
			table[bucketNum].Delete(title);
			return true;
		}
		else
			return false;
	}

	Movie* HashTable::Search(string title){
		int bucket = Hash(title);

		if(table[bucket].Search(title) != nullptr){
			Movie* newMovie = table[bucket].Search(title);
			return newMovie;
		}

		else
			return nullptr;
	}

	void HashTable::PrintYearFrequency(){
		Movie* ptr;
		vector<Movie>allMovies;
		int yearReleased;
		unordered_map<int, int> map;
		unordered_map<int, int>::iterator j;
		
		for(int i = 0; i < GetSize(); i++){
			allMovies = table[i].GetElements();

			for(int i = 0; i < allMovies.size(); i++){

				yearReleased = allMovies.at(i).GetYearReleased();
				map[yearReleased]++;
			}		
		}

		for(j = map.begin(); j != map.end(); j++){
			cout << "*********" << endl;
			cout << "Movies Released in year " << j->first << ": " << j->second << endl;
			cout << "*********" << endl;
		}
	
	}

	void HashTable::PrintTable(){
		Movie* ptr;
		vector<Movie>allMovies;

		for(int i = 0; i < GetSize(); i++){
			allMovies = table[i].GetElements();


			for(int i = 0; i < allMovies.size(); i++){
				cout << "**********" << endl;
				cout << "Title: " << allMovies.at(i).GetTitle() << endl;
				cout << "Lead Actor / Actress: " << allMovies.at(i).GetLeadActorActress() << endl;
				cout << "Description: " << allMovies.at(i).GetDescription() << endl;
				cout << "Year Released: " << allMovies.at(i).GetYearReleased() << endl;
				cout << "**********" << endl;
			}
		}
	}

	void HashTable::PrintSorted(){
		vector<Movie>allMovies;
		Movie* ptr;
		vector<Movie>moviesTemp;

		// Commented out the function as it causes the program to crash if called. 

		/**
		for(int i = 0; i < GetSize(); i++){
			moviesTemp = table[i].GetElements();

			if(!moviesTemp.empty()){		
			
				for(int i = 0; i < moviesTemp.size(); i++){
					allMovies.push_back(moviesTemp.at(i));			
				}
			}
		}

		Sort(allMovies, 0, allMovies.size() - 1);
		
		for(int i = 0; i < allMovies.size(); i++){
			cout << "*********" << endl;
			cout << "Title: " << allMovies.at(i).GetTitle() << endl;
			cout << "Year: " << allMovies.at(i).GetYearReleased() << endl;
			cout << "*********" << endl;
		}
	*/
	}
