#include "PA6.h"


void displayMenu() {
	cout << endl << "Welcome to the CPSC 122 Music Manager!!" << endl;
	cout << "Please choose from the following options: " << endl;
	cout << "1) Load library" << endl;
	cout << "2) Store library" << endl;
	cout << "3) Display library" << endl;
	cout << "4) Sort library" << endl;
	cout << "5) Search library" << endl;
	cout << "6) Insert song in order" << endl;
	cout << "7) Remove song" << endl;
	cout << "8) Edit song" << endl;
	cout << "9) Exit" << endl;
}

int getValidChoice() {
	int choice = -1;
	string temp;
	do {
		cout << "Choice: ";
		cin >> choice;
		if (choice < FIRST_OPTION || choice > LAST_OPTION) {
			cout << "That is not a valid option. Please try again." << endl;
		}
	} while (choice < FIRST_OPTION || choice > LAST_OPTION);
	getline(cin, temp); // flush the newline outta the buffer
	return choice;
}

void executeUserChoice(int choice, SongLibrary& lib) {
	string inPut1 = "";
	string searchAttribute, searchValue;
	string title, artist, genre;
	string titleToRemove;
	string aTTribute, newAttributeValue;
	Song * songToRemove = NULL, * searchResult = NULL, * newSong = NULL, * songToEdit = NULL;
	int rating;
	bool found;
	int inDex;
	switch (choice) {
		case 1:
			// TODO: call a member function, something like lib.loadLibrary();
			cout << "input file name: " << endl;
			getline(cin, inPut1);
			lib.performLoad(inPut1);
			break;
		case 2:
			// TODO: call a member function, something like lib.saveLibrary();
			cout << "Please enter input file name: " << endl;
			getline(cin, inPut1);
			lib.performSave(inPut1);
			break;
		case 3: 
			// TODO: call a member function, something like lib.displayLibrary();
			lib.displayList();
			break;
		case 4:
			// TODO: call a member function, something like lib.sortLibrary();
			cout << "What song attribute do you want to sort?(title, artist, genre or rating)" << endl;
			getline(cin, inPut1);
			lib.setSortAttribute(inPut1);
			lib.performSort();
			break;
		case 5:
			// TODO: call a member function, something like lib.searchLibrary();
			
			cout << "Enter the attribute to search for (title, artist, genre, rating): ";
    		cin >> searchAttribute;
    		cout << "Enter the value to search for: ";
    		cin >> searchValue;

			searchResult = lib.performSearch(searchAttribute, searchValue, &found, &inDex);
			if(found) {
				cout << "Song found at index " << inDex << ":" << endl;
				searchResult ->displaySong();
			}else{
				cout << "Song not found" << endl;
			}
			break;
		case 6:
			// TODO: call a member function, something like lib.insertSongInLibraryOrder();
        	
        	cout << "Enter the title of the song: ";
       	 	getline(cin, title);
        	cout << "Enter the artist of the song: ";
        	getline(cin, artist);
        	cout << "Enter the genre of the song: ";
        	getline(cin, genre);
        	cout << "Enter the rating of the song: ";
        	cin >> rating;

			newSong = new Song(title, artist, genre, rating);
			lib.performInsertSongInOrder(newSong);
			cout << "Song added to library." << endl;
			break;
		case 7:
			// TODO: call a member function, something like lib.removeSongFromLibrary();
			cout << "Enter the title of the song to remove: ";
			getline(cin, titleToRemove);
			songToRemove = lib.performSearch("title", titleToRemove, &found, &inDex);
			if(found){
				lib.performRemoveSong(songToRemove);
				cout << "Song removed successfully!" << endl;
			}else{
				cout << "Song not found in the list!" << endl;
			}
			break;
		case 8:
			// TODO: call a member function, something like lib.editSongInLibrary();
			
			cout << "Enter the attribute to search for: ";
			getline(cin, searchAttribute);
			cout << "Enter the value to search for: ";
			getline(cin,searchValue);

			songToEdit = lib.performSearch(searchAttribute, searchValue, &found, &inDex);

			if(!found){
				cout << "Song not found." << endl;
			}else{
				cout << "Enter the attribute to edit: ";
				getline(cin, aTTribute);
				cout << "Enter the new value: ";
				getline(cin, newAttributeValue);

				lib.performEditSong(songToEdit, aTTribute, newAttributeValue);
			}

			break;
		default:
			cout << "Unrecognized menu choice" << endl;
			break;
	}
}

void runMusicManager() {
	SongLibrary lib;
	
	int choice = -1;
	do {
		displayMenu();
		choice = getValidChoice();
		if (choice != QUIT_OPTION) {
			executeUserChoice(choice, lib);
		}
	} while (choice != QUIT_OPTION);
	cout << "Thanks for you using the CPSC 122 Music Manager!!" << endl;
}
