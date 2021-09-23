#include "movielist.h"

	MovieList::MovieList(){
		head = nullptr;
	}

	void MovieList::Insert(string title, string leadActorActress, string description, int yearReleased){
		Movie* newMovie = new Movie(title, leadActorActress, description, yearReleased);
		Insert(newMovie);	
	}

	void MovieList::Insert(Movie* movie){
		
		if(head == nullptr){
			head = movie;
			head->SetNext(nullptr);
			head->SetPrev(nullptr);
		}

		else{
			movie->SetNext(head);
			head->SetPrev(movie);
			head = movie; 
		}
	}
	
	bool MovieList::Delete(string title){
		Movie* ptr;

				
		for(ptr = head; ptr != nullptr; ptr = ptr->GetNext()){
	
			if(ptr->GetNext() == nullptr){
				if(ptr->GetPrev() == nullptr){
					head = nullptr;
					delete ptr;
					return true;
				}
				else{
					Movie* tempPrev = ptr->GetPrev();
					tempPrev->SetNext(nullptr);
					delete ptr;
					return true;
				}
			}

			if(ptr->GetTitle() == title){
				Movie* tempPrev;
				Movie* tempAfter;

				tempPrev = ptr->GetPrev();
				tempPrev->SetNext(ptr->GetNext());
				tempAfter = ptr->GetNext();
				tempAfter->SetPrev(tempPrev);

				delete ptr;
				return true;
			}
		}

		return false;
	}

	Movie* MovieList::Search(string title){
		Movie* ptr;

		for(ptr = head; ptr != nullptr; ptr = ptr->GetNext()){
			if(ptr->GetTitle() == title){
				return ptr;
			}	
		}
		
		return nullptr;
		
	}

	Movie* MovieList::DetachAndGetFirst(){
		Movie* ptr;
		if(head != nullptr){
			ptr = head;
			
			head = ptr->GetNext();

			return ptr;
			/**
			if(ptr->GetNext() != nullptr){
		
				Movie* tempAfter = ptr->GetNext();
				tempAfter->SetPrev(nullptr);
				head->SetNext(nullptr);
				head = ptr->GetNext();
				return ptr;
			
			}
			else{
				head = nullptr;
				return ptr;
			}
		*/
		}
		else
			return nullptr;
	}

	vector<Movie> MovieList::GetElements(){
		vector<Movie> allMovies;
		Movie* ptr;

		for(ptr = head; ptr != nullptr; ptr = ptr->GetNext()){
			allMovies.push_back(*ptr);
		}

		return allMovies;
	}

	void MovieList::PrintList(){
		Movie* ptr;

		for(ptr = head; ptr != nullptr; ptr = ptr->GetNext()){
			cout << "Title: " << ptr->GetTitle() << endl;
			cout << "Lead Actor Actress: " << ptr->GetLeadActorActress() << endl;
			cout << "Description: " << ptr->GetDescription() << endl;
			cout << "Year Released: " << ptr->GetYearReleased() << endl;
		}
	}

