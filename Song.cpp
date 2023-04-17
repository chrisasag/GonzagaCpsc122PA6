#include "Song.h"

// TODO: finish this function
// This function convert string to lower case string
string convertToLowercase(string s) {
	int length = s.length();
	for (int i=0; i < length;i++){
		if(s.at(i) >= 'A' && s.at(i) <= 'Z'){
			s.at(i) += 32;
		}
	}
	return s;
}

// TODO: finish Song default value constructor
//Song class DVC
Song::Song() {
	title = "";
	artist = "";
	genre = "";
	rating = 1;
	next = NULL;
}

// TODO: finish Song explicit value constructor]
//Song class EVC, all string parameters are convert to lower case
Song::Song(string titleParam, string artistParam, string genreParam, int ratingParam) {
	title = convertToLowercase(titleParam);
	artist = convertToLowercase(artistParam);
	genre = convertToLowercase(genreParam);
	setRating(ratingParam);
	next = NULL;
}

// TODO: finish Song copy constructor
//Song class copy constructor 
Song::Song(const Song& other) {
	title = other.title;
	artist = other.artist;
	genre = other.genre;
	rating = other.rating;
	next = NULL;
}

//Song class title getter 
string Song::getTitle() {
	return title;
}

//Song class title setter
void Song::setTitle(string newTitle) {
	title = convertToLowercase(newTitle);
}

//Song class artist getter
string Song::getArtist() {
	return artist;
}

//Song class artist setter
void Song::setArtist(string newArtist) {
	artist = convertToLowercase(newArtist);
}

//Song class genre getter
string Song::getGenre() {
	return genre;
}

//Song class genre setter
void Song::setGenre(string newGenre) {
	genre = convertToLowercase(newGenre);
}

//Song class rating getter
int Song::getRating() {
	return rating;
}

//Song class rating setter
void Song::setRating(int newRating) {
	if (newRating < MIN_RATING || newRating > MAX_RATING) {
		cout << "Rating must be in [" << MIN_RATING << ", " << MAX_RATING << "]" << endl;
	}
	if (newRating < MIN_RATING) {
		rating = MIN_RATING;
	}
	else if (newRating > MAX_RATING) {
		rating = MAX_RATING;
	}
	else {
		rating = newRating;
	}
}

//Song class pointer getter
Song * Song::getNext() {
	return next;
}

//Song class pointer setter
void Song::setNext(Song * newNext) {
	next = newNext;
}

// TODO: finish this function
// This member function return attribute of song
string Song::getStringAttributeValue(string attribute) {
	if(attribute ==  "title"){
		return getTitle();
	} else if (attribute == "artist") {
        return getArtist();
    } else if (attribute == "genre") {
        return getGenre();
    } else if (attribute == "rating") {
		// change int type to string type to avoid extra boolean contral statement when sorting song library
        return to_string(getRating());
    } else {
        return "";
    }
}

// TODO: finish this function
// member function of Song, display object
void Song::displaySong() {
	cout << "Title: " << title << endl;
	cout << "Artist: " << artist << endl;
    cout << "Genre: " << genre << endl;
    cout << "Rating: " << rating << endl;
}

