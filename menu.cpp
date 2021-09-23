#include "menu.h"

	int Menu::GetSelection(){
		int selection = 0;
		cin >> selection;

		return selection;
	}

	void Menu::AddMovie(){
		string title;
		string leadActorActress;
		string description;
		int yearReleased;

		cout << "Enter movie's title: " ;
		cin >> title;
		cout << "Enter movie's lead actor/actress: ";
		cin >> leadActorActress;
		cout << "Enter movie's description: ";
		cin >> description;
		cout << "Enter movie's year released: ";
	       	cin >> yearReleased;
		
		movieTable->Insert(title, leadActorActress, description, yearReleased);

	}

	void Menu::SearchMovie(){
		string title;
		Movie* newMovie;
		cout << "Enter title to search: ";
		cin >> title;

		newMovie = movieTable->Search(title);

		if(newMovie == nullptr){
			cout << "Movie doesn't exist." << endl;
		}
		else{
			cout << "Movie title: " << newMovie->GetTitle() << endl;
			cout << "Lead Actor / Actress: " << newMovie->GetLeadActorActress() << endl;
			cout << "Description: " << newMovie->GetDescription() << endl;
			cout << "Year Released: " << newMovie->GetYearReleased() << endl;
		}
	}

	Menu::Menu(){
		movieTable = new HashTable();
	}

	void Menu::LoadMovies(string fileName){
		ifstream movieFile;
		movieFile.open(fileName);
		
		string title;
		string leadActorActress;
		string description;
		int yearReleased;	
		string placeholder; // for white space

		while(!movieFile.eof()){
			getline(movieFile, title, ',');
			getline(movieFile, leadActorActress, ',');
			getline(movieFile, description, ',');
			movieFile >> yearReleased;
			getline(movieFile, placeholder, '\n');
		
			if(title != ""){ 
				movieTable->Insert(title, leadActorActress, description, yearReleased);
			}
		}
	
	}

	HashTable* Menu::GetMovieTable(){
		return movieTable;
	}

	void Menu::StartMenu(){

		int selection = 0;

		do{
			cout << endl;
			cout << "-----Make a choice:-----" << endl;
			cout << "Read database file (1)" << endl;
			cout << "Add a new movie (2)" << endl;
			cout << "Search for a movie by title (3)" << endl;
			cout << "Delete a movie (4)" << endl;
			cout << "Display all movies (5)" << endl;
			cout << "Display movies sorted by release date (6)" << endl;
			cout << "List member of movies per year (7)" << endl;
			cout << "Exit (-1)" << endl;
			cout << "---------------------" << endl;
			cout << "Your choice: ";
		selection = GetSelection();
			cout << endl;
		switch(selection){
			
			case 1:
			{
				string fileName;
				cout << "Enter File Name: ";
				cin >> fileName;
				LoadMovies(fileName);
				break;
			}
			case 2:
				AddMovie();
				break;
			case 3:
				SearchMovie();
				break;
			case 4:
			{
				string movieName;
				cout << "Enter Movie's name to be deleted: ";
				cin >> movieName;
				Movie* ptr = movieTable->Search(movieName);

				if(ptr != nullptr){
					movieTable->Delete(movieName);
					cout << "Deleted Movie: " << movieName << endl;
				}
				
				else
					cout << "Couldn't Find Movie: " << movieName << endl;
				break;
			}
			case 5:
				movieTable->PrintTable();
				break;

			case 6:
				movieTable->PrintSorted();
				break;
			case 7:
				movieTable->PrintYearFrequency();
				break;
		
			case -1:
				break;
			
			default: 
				cout << "Please enter 1-7, or -1 to exit" << endl;
				break;
		}
		}while(selection != -1);
	}

