/*
Name:Haohan Liu
Class: CPSC 122, Spring 2023
Programming Assignment 5
Description: This program reads song data from a file and save them in an dynamically allocated Linked List. Each song
have four features: title, artist, genre and rating. The user can remove, add, edit each song in the song library.
This program also allow user to sort songs by their feactures, display the song library and store them in a file.

Note: The songlibrary copy constructor is the hardest part in this PA. At first, my code can compile but core dumped
after exit the program, and valgrind warn there's something wrong with the copy constructor. It took me a lot of time
to figure out that my code didn't creating a copy of the list that other.head points to. Instead, it directly inserts
the nodes from the other list into the new list using 'performInsertSongInOrder()' function.
*/
#include "PA6.h"

int main() {
	runMusicManager();

	return 0;
}
