/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab8.c
 * Author: user
 *
 * Created on March 29, 2017, 4:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/*
 * 
 */

typedef struct node {
    char *songName;
    char *artistName;
    char *genre;
    struct node *link;
} Node;

int stringLength(char s[]) //function that counts number of character in the array
{
    int i = 0;
    while (s[i] != '\0') {
        i = i + 1;
    }
    return i;
}

void stringCopy(char *destination, char *source) { //function that copies strings
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

//Creating a new node

Node *newNode(char *songName, char *artistName, char *genre, Node *link) {
    Node *t = (Node *) malloc(sizeof (Node)); //dynamic allocating memory for this node
    if (t != NULL) { //if there is enough memory 
        t->songName = malloc(sizeof (char)*stringLength(songName)); //dynamically allocating memory for each of the 3 strings
        stringCopy(t->songName, songName); //copying the variable into the allocated memory    
        t->artistName = malloc(sizeof (char)*stringLength(artistName));
        stringCopy(t->artistName, artistName);
        t->genre = malloc(sizeof (char)*stringLength(genre));
        stringCopy(t->genre, genre);
        t->link = link;
    }
    return t;
}

//organizes the nodes in alphabetical list of the song name 

Node *insertIntoOrderedList(Node *head, char *songName, char *artistName, char *genre) {

    //if the value that user entered is smaller than the first node, or smaller than the head node
    if (head == NULL || (strcmp(songName, head->songName)) < 0) {
        return newNode(songName, artistName, genre, head); //a new head of the list       
    }
    Node *current = head;
    //if the value that user entered is bigger than the head
    while (current->link != NULL && (strcmp(songName, current->link->songName)) > 0) {
        current = current ->link;
    }
    current -> link = newNode(songName, artistName, genre, current ->link);
    return head;
}

bool searchForSongName(Node *head, char *songName) //function that searches for song name and if found, outputs the song name, artist, and genre
{
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current ->songName, songName) == 0) {
            printf("\nThe song name '%s' was found in the music library.\n", songName);
            printf("\n%s\n%s\n%s\n", current ->songName, current->artistName, current->genre);
            return true;
        }
        current = current ->link;
    }
    return false;
}
//function that checks if the song that user wants the input or delete is in the list

bool searchNameToBeInsertedOrDeleted(Node *head, char *songName) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current ->songName, songName) == 0) {
            return true;
        }
        current = current ->link;
    }
    return false;
}

Node *deleteSongName(Node *head, char *songName) //function that deletes the inputed song name if there exists one
{
    if (head == NULL) //if empty list
    {
        return NULL;
    }
    //if the first node is to be deleted
    if (strcmp(head ->songName, songName) == 0) {
        Node *secondNode = head ->link;
        free(head);
        return secondNode;
    }
    bool found = false;
    Node *current = head;
    while (!found && current -> link != NULL) {
        if (strcmp(current->link->songName, songName) == 0) //if the item to be deleted is found in one of the nodes
        {
            found = true;
        }
        else
            current = current ->link;
    }
    //if there exists a node that needs to be deleted
    if (current -> link != NULL) {
        Node *nodeToRemove = current ->link;
        current ->link = current ->link->link; //current points to the next next node
        free(nodeToRemove);
    }
    return head;
}
//Deleting all the nodes in the linked list

Node *deleteAllNodes(Node *head) {
    while (head != NULL) {
        printf("\nDeleting a song with name '%s' from the music library.\n", head->songName);
        Node *firstNode = head;
        head = head->link; //head points to the next node 
        free(firstNode); //free the allocated memory
        return head;
    }
    return NULL;
}

void printList(Node *head) { //function that prints everything in the node one at a time
    Node *current = head;
    while (current != NULL) {
        printf("\n%s\n", current ->songName);
        printf("%s\n", current->artistName);
        printf("%s\n", current ->genre);
        current = current ->link;
    }
}

void getStringFromUserInput(char s[], int arraySize) { //function that reads the inputted characters from u
    char c;
    int i = 0;
    while (i < arraySize && (c = getchar()) != '\n') {
        s[i++] = c;
    }

    s[i] = '\0';
}

void songNameDuplicate(char songName[]) {
    printf("\nA song with the name '%s' is already in the music library.\nNo new song entered.\n", songName);
}

void songNameFound(char songName[]) {
    printf("\nThe song name '%s' was found in the music library.\n", songName);
}

void songNameNotFound(char songName[]) {
    printf("\nThe song name '%s' was not found in the music library.\n", songName);
}

void songNameDeleted(char songName[]) {
    printf("\nDeleting a song with name '%s' from the music library.\n", songName);
}

void printMusicLibraryEmpty(void) //function to call when printing an empty music library
{
    printf("\nThe music library is empty.\n");
}

void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}
const int MAX_LENGTH = 1024;

int main(int argc, char** argv) {
    Node *head = NULL; //initializing head   
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n" "P (print), Q (quit).\n");

    //declaring variables
    char response;
    bool duplicate;
    char input[MAX_LENGTH + 1];
    char inputSongName[MAX_LENGTH + 1]; //array for the song name
    char inputArtistName[MAX_LENGTH + 1]; //array for the artist name
    char inputSongGenre [MAX_LENGTH + 1]; //array for the genre
    do {
        printf("\nCommand?: "); //prompt the user to enter a command 
        getStringFromUserInput(input, MAX_LENGTH); //reads user input
        response = toupper(input[0]); //convert to upper case to simplify comparison      
        
        if (response == 'I') { //inserting song order by song name
            printf("Song name: "); //prompting for data
            getStringFromUserInput(inputSongName, MAX_LENGTH);
            printf("Artist: ");
            getStringFromUserInput(inputArtistName, MAX_LENGTH);
            printf("Genre: ");
            getStringFromUserInput(inputSongGenre, MAX_LENGTH);

            duplicate = searchNameToBeInsertedOrDeleted(head, inputSongName); // check if the song that user inputs already exists in the link

            if (duplicate == true) //check for duplicates
            {
                songNameDuplicate(inputSongName);
            }
            else {
                head = insertIntoOrderedList(head, inputSongName, inputArtistName, inputSongGenre);

            }
        } else if (response == 'S') //searching the song in the list 
        {
            printf("\nEnter the name of the song to search for: ");
            getStringFromUserInput(inputSongName, MAX_LENGTH);

            if (searchForSongName(head, inputSongName) == true) { //do thing because the function will print the name, artist and genre               
            } else {
                songNameNotFound(inputSongName);
            }

        }
        else if (response == 'D') //delete the song from the list
        {
            printf("\nEnter the name of the song to be deleted: ");
            getStringFromUserInput(inputSongName, MAX_LENGTH);

            bool searchDeletedSong;
            searchDeletedSong = searchNameToBeInsertedOrDeleted(head, inputSongName);
            if (searchDeletedSong == true) //if the song entered is found in the link
            {
                songNameDeleted(inputSongName); //display the statement that the song has been deleted
                head = deleteSongName(head, inputSongName);
            }
            else {
                songNameNotFound(inputSongName);
            }
        }
        else if (response == 'P') //prints out everything in the list
        {
            if (head == NULL) {
                printMusicLibraryEmpty();
            }
            else {
                printMusicLibraryTitle();
                printList(head);
            }
        }

        else if (response == 'Q') {
            //Do nothing
        }
        else {
            //when no command matched 
            printf("\nInvalid command.\n");
        }

    } while (response != 'Q');

    while (head != NULL && head != NULL) //prints out delete statement one by one till the link is empty
    {
        head = deleteAllNodes(head);
    }
    if (head == NULL) {
        printMusicLibraryEmpty();
    }

    return (EXIT_SUCCESS);
}

