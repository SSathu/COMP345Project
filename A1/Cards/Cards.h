#pragma once
#include <string>
#include "../Orders/Orders.h"
#include <iostream>
#include <vector>
#include <algorithm> //Sorting, find, etc
#include <cstdlib> //for random numbers
#include <iterator> 
#include <ctime> //Part of generating seed


//bomb, reinforcement, blockade, airlift and diplomacy are the types of Cards


using namespace std;


class Card {
public:
	//For purpose of getting card type, numbers will be used
	Card(); // constructor
	Card(int cardType); //constructor
	Card(Card* otherCard);
	//Copy constructor
	int* getCardType(); //Getter function
	Card& operator=(Card* otherCard); //Check if two cards have the same type
	friend ostream& operator<<(ostream& os,Card* card); //outputs cardType




private:
	int cardType;

};



class Hand {
public:
	Hand& operator=(Hand* otherHand); //Check if two cards have the same type
	Hand(); // constructor
	Hand(Hand* otherHand);
	Order* play(Card* cardToPlay, void* currentDeck);
	vector<Card*>* getHandCards(); //Returns the vector containing the cards
	string cardsInHand();// Returns a string containing all the cards in hand
	void insertCard(Card* cardToInsert);
	void clearCards();//deletes all pointers and clears vector
	Card* exchangeCard(int cardType, void* deckCards); //Goes through player's hand searching for card in parameter, and then returns the pointer to that Card as well as removing the Card from the hand.
	vector<Card*>* handCards; //For Cards in hand
	friend ostream& operator<<(ostream& os, Hand hand); //outputs all cards in hand;

};


class Deck {
public:
	Deck();
	Deck& operator=(Deck* otherDeck); //Check if two cards have the same type
	Card* draw(Hand* playerHand);//Function that will draw a card and place in given hand in parameter.
	Deck(Deck* otherDeck);
	void insertCard(Card* cardToInsert); //Adds card to Deck
	vector<Card*>* getDeckCards(); //Returns the vector containing the cards
	void clearCards(); //deletes all pointers and clears vector
	string cardsInDeck(); // Returns a string containing all the cards in deck
	friend ostream& operator<<(ostream& os, Deck deck); //outputs all cards in deck

	vector<Card*>* deckCards; // For Cards in Deck
};








