#include "SongLibrary.h"

//This SongLibrary member function iterates through the list and deletes each node.
void SongLibrary :: destroyList(){
	Song * currSong = head;
	Song * nextSong = NULL;
	while(currSong != NULL){
		nextSong = currSong -> getNext();
		delete currSong;
		currSong = nextSong;
	}
	head = NULL;
}

//This member function iterates through the linked list and 
//displays the information for each song in the list.
void SongLibrary :: displayList(){
	Song * currSong = head;
	while(currSong != NULL){
		currSong -> displaySong();
		currSong = currSong->getNext();
		cout << endl;
	}
}

//This constructor initializes the linked list to an empty list and 
//sets the default sort attribute to "title".
SongLibrary::SongLibrary() {
	// initialize to empty list
	head = NULL; 
	// default sort attribute is title
	sortAttribute = "title";
}

// TODO: finish SongLibrary copy constructor
//This is a copy constructor for the SongLibrary class, 
//which is used to create a new instance of the class that is a copy of an existing instance.
SongLibrary::SongLibrary(const SongLibrary& other) {
	sortAttribute = other.sortAttribute;
	if(other.head == NULL){
		head = NULL;
	}
	else{
		//creats a new song object by calling the song copy constructor 
		//and passes in the song object that other.head points to
		head = new Song(*(other.head));

		Song * currSong = head;
		Song * otherSong = other.head -> getNext();

		while(otherSong != NULL){

			//creates a new song object and passes in the song obhect that otherSong points to;
			currSong->setNext(new Song(*otherSong));

			//set currSong points to its next node
			currSong = currSong -> getNext();

			//set otherSong points to its next node
			otherSong = otherSong -> getNext();
		}
	}
}

// TODO: finish SongLibrary destructor
//Destructor of the SongLibrary class. It frees the memory allocated for the linked list.
SongLibrary::~SongLibrary() {
	cout << "hello from the destructor \n" ;
	destroyList();
}

//Getter function that returns a pointer to the head of the linked list
Song * SongLibrary::getHead() const {
	return head;
}

// TODO: finish this function
/*This member function takes a new head pointer as input and sets it as the head of the linked list. 
If the list already has a head, it first destroys the old list using the destroyList() function 
to avoid memory leaks.*/
void SongLibrary::setHead(Song * newHead) {
	if (head != NULL) {
		// TODO: free old list here!!
		destroyList();
	}
	head = newHead;
}

/*This member function returns the current value of the sortAttribute member variable.*/
string SongLibrary::getSortAttribute() const {
	return sortAttribute;
}

/*This member function sets a new value for the sortAttribute member variable.*/
void SongLibrary::setSortAttribute(string newSortAttribute) {
	sortAttribute = newSortAttribute;
}

// TODO: finish this function
/*The function performLoad loads songs from a file and adds them to the song library. 
It first destroys any existing list in the library. 
Then, it opens the file specified by the filename parameter and reads in the songs line by line.
For each song, it creates a new Song object with the attributes read from the file, 
and adds the song to the list using the performInsertSongInOrder function. */
void SongLibrary::performLoad(string filename) {
	//destroying any existing list
	destroyList();

	//open the file to read:
	ifstream infile;
	infile.open(filename);

	if(!infile.is_open()){
		cout << "Can not open the input file" << endl;
	}
	
	string line;// to release buffer  

	string currtitle = "", currartist = "", currgenre = "";
	int currrating = 0;

	while(!infile.eof()){ 
		getline(infile, currtitle);
		getline(infile, currartist);
		getline(infile, currgenre);
		infile >> currrating;
		getline(infile, line);//release the buffer
		infile.ignore();
		infile.ignore();

		//new song object
		Song *currSong = new Song(currtitle, currartist, currgenre, currrating);

		//call the add function to add song to the list
		performInsertSongInOrder(currSong);
	}
	infile.close();
}

// TODO: finish this function
/*This function saves the current state of the SongLibrary object to a file specified by the filename parameter. 
It opens the file for writing and then iterates through each Song in the linked list,*/
void SongLibrary::performSave(string filename) {
	ofstream outfile(filename);
	Song * currSong = head;
	while(currSong!=NULL){
		outfile << currSong -> getTitle() << endl;
		outfile << currSong -> getArtist() << endl;
		outfile << currSong -> getGenre() << endl;
		outfile << currSong -> getRating() << endl;
		outfile << endl;
		currSong = currSong -> getNext();
	}
}

// TODO: finish this function
/* This function performs a sort of the song list in ascending order based on the sort attribute 
specified for the SongLibrary object. It creates a new list by traversing the original list 
and inserting each node into the new list in the correct order using the performInsertSongInOrder() function. 
Finally, it deletes the original list and sets the head of the SongLibrary object to point to the new sorted list.*/
void SongLibrary::performSort() {
	if(head == NULL){
		cout << "The list is empty!" << endl;
	}
	
	Song * currSong = head;
	Song * prevSong = NULL;
	head = NULL;

	while(currSong != NULL){
		Song * newSong = new Song(*currSong);
		performInsertSongInOrder(newSong);
		prevSong = currSong;
		currSong = currSong -> getNext();
		delete prevSong;
	}
}

// TODO: finish this function
/* This function searches the list for a song with a specific attribute value.
If found, it sets the "found" parameter to true, sets the "index" parameter to the index of the song,
and returns a pointer to the song. If not found, it sets "found" to false, sets "index" to -1,
and returns NULL.*/
Song * SongLibrary::performSearch(string searchAttribute, string searchAttributeValue, bool * found, int * index) {
	if(head == NULL){
		cout << "The list is empty!" << endl;
		return NULL;
	}
	else{
		Song * currSong = head;
		int currIndex = 0;
		while(currSong != NULL){
			if(currSong ->getStringAttributeValue(searchAttribute) == searchAttributeValue){
				*found = true;
				*index = currIndex;
				return currSong;
			}
			currSong = currSong->getNext();
			currIndex++;
		}
		*found = false;
		*index = -1;
		return NULL; 
	}
	
}

// TODO: finish this function
/*This function inserts a song into the list in order based on a specific attribute.
If the list is empty, it sets the head to the song to insert. Otherwise, it iterates through the list
until it finds the appropriate place to insert the song.*/
void SongLibrary::performInsertSongInOrder(Song * songToInsert) {
	if (head == NULL){
		head = songToInsert;
	}
	else{
		Song * currSong = head;
		Song * prevSong = NULL;

		while(currSong != NULL && currSong->getStringAttributeValue(sortAttribute) 
		< songToInsert->getStringAttributeValue(sortAttribute)){
			prevSong = currSong;
			currSong = currSong->getNext();
		}

		if(prevSong == NULL){
			songToInsert->setNext(head);
			head=songToInsert;
		}
		else{
			songToInsert->setNext(currSong);
			prevSong->setNext(songToInsert);
		}
	}
}


// TODO: finish this function
/*This function removes a specific song from the list. If the list is empty, it prints the list is emoty
and does nothing. If the song to remove is the head, it sets the head to the next song and deletes the removed song.
Otherwise, it iterates through the list until it finds the song to remove, removes it from the list,
and deletes the song.*/
void SongLibrary::performRemoveSong(Song * songToRemove) {
	if(head == NULL){
		cout << "The list is empty";
		return;
	}

	if(songToRemove == head){
		head = head -> getNext();
		delete songToRemove;
		return;
	}

	Song * currSong = head;
	Song * prevSong = NULL;

	while(currSong != NULL && currSong != songToRemove){
		prevSong = currSong;
		currSong = currSong -> getNext();
	}

	if(currSong == NULL){
		cout << "Song not found in the list!" << endl;
		return;
	}

	prevSong -> setNext(currSong ->getNext());
	delete currSong;
}

// TODO: finish this function
/*This function edits a specific attribute of a song. If the attribute is "title", "artist", "genre", or "rating",
it updates the corresponding attribute of the song. If the attribute is not recognized, it prints invalid attribute
and does nothing.*/
void SongLibrary::performEditSong(Song * songToEdit, string attribute, string newAttributeValue) {	
	if(songToEdit == NULL) {
		cout << "Song to edit is NULL" << endl;
		return;
	}

	int newRating;

	if(attribute == "title"){
		songToEdit -> setTitle(newAttributeValue);
    } 
	else if (attribute == "artist") {
        songToEdit -> setArtist(newAttributeValue);
    } 
	else if (attribute == "genre") {
       	songToEdit -> setGenre(newAttributeValue);
    } 
	else if (attribute == "rating") {
		newRating = stoi(newAttributeValue);//convert string to int
		songToEdit -> setRating(newRating);
	}
	else{
		cout << "Invalid attribute" << endl;
		return;
	}
}
