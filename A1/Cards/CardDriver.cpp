#include "Cards.h"
#include <iostream>
void testCards()
{
    Card* card5 = new Card(5);
    Card* card2 = new Card(2);
    Card* card1 = new Card(1);
    Card* card3 = new Card(3);
    Card* card4 = new Card(4);
    Card* card0 = new Card(1);

    Deck* deck = new Deck();
    Hand* hand = new Hand();

    deck->insertCard(card1);
    deck->insertCard(card2);
    deck->insertCard(card3);
    deck->insertCard(card4);
    deck->insertCard(card5);
    deck->insertCard(card0);
    cout << "Cards in Deck: \n";
    cout << *deck;
    cout << "Cards in Hand: \n";
    cout << *hand;


    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);



    cout << "Cards in Deck: \n";
    cout << *deck;
    cout << "Cards in Hand: \n" ;
    cout << *hand;

    hand->play(card1, deck);
    hand->play(card2, deck);
    hand->play(card3, deck);
    hand->play(card4, deck);
    hand->play(card5, deck);
    hand->play(card0, deck);

    cout << "Cards in Deck: \n";
    cout << *deck;
    cout << "Cards in Hand: \n";
    cout << *hand << "\n";




}

/*int main() {
testCards();
return 0;
}*/
