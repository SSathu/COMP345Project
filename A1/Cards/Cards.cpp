#include <iostream>
#include "Cards.h"

void Deck::insertCard(Card* cardToInsert)
{
	deckCards->push_back(cardToInsert); //Inserts a pointer to a card into the deck
};

void Hand::insertCard(Card* cardToInsert)
{
	handCards->push_back(cardToInsert);
	cardToInsert = NULL;
};;





Card* Hand::exchangeCard(int cardType, void* currentDeck)
{
	int index = -1; //beginning index, if card is never found then it will remain negative 1

	Deck* deck = static_cast<Deck*>(currentDeck); //Casting void pointer to Deck, need to consider another option in the future to prevent errors

	for (int i = 0; i < handCards->size(); i++)
	{
		Card* card = handCards->at(i); //just an easy way to access pointer
		if (*card->getCardType() == cardType) //Find first instance of card in hand
		{
			index = i;
			card = NULL;
			break;
		}
		card = NULL;
	}

	if (index == -1)
	{
		return NULL; //If card is not found then return null
	}
	Card* chosenCard = handCards->at(index);
	handCards->erase(handCards->begin() + index); // erase the card from the hand
	deck = NULL; // prevent dangling pointer
	return chosenCard;
};



Card::Card()
{
	cardType = -1; //default value
};;

Card::Card(int typeCard) //0 Bomb, 1 Reinforcement, 2 Blockade, 3 Airlift, 4 Diplomacy
{
	cardType = typeCard;
};


Card::Card(Card* otherCard)
{
	if (otherCard == NULL) //Double checking that card being copied exists
	{
		cardType = -1;
		return;
	}

	cardType = *otherCard->getCardType();
};;


int* Card::getCardType()
{
	return &cardType;
}
Card& Card::operator=(Card* otherCard)
{
	cardType = *otherCard->getCardType();
	return *this;
}
;



Order* Hand::play(Card* cardToPlay, void* deck)
{
	//Go through player hand, find first instance of card type in hand, and move the hand to currentDeck, erasing the card from the hand of the player.
	
	Deck* currentDeck = static_cast<Deck*>(deck);
	Hand* currentHand = this;
	int* cardType = cardToPlay->getCardType();

	Card* cardPulledFromDeck = currentHand->exchangeCard(*cardType, currentDeck);
	if (cardPulledFromDeck == NULL)
	{
		std::cout << "Card was not found in current hand!";
	}
	currentDeck->insertCard(cardPulledFromDeck);
	cardPulledFromDeck = NULL; //preventing dangling pointer


	switch (*cardType) //Match the given cardType to the order type that needs to be returned
	{
	case 0:
		return new BombOrder();
	case 1:
		return new DeployOrder();
	case 2:
		return new BlockadeOrder();
	case 3:
		return new AirliftOrder();
	case 4:
		return new NegotiateOrder();
	default:
		return NULL;
	} //
};;

Hand& Hand::operator=(Hand* otherHand)
{
	clearCards();
	handCards = otherHand->getHandCards();
	return *this;

}

Hand::Hand()
{
	handCards = new vector<Card*>;
};;



Hand::Hand(Hand* otherHand)
{
	this->handCards = otherHand->getHandCards();
};;


vector<Card*>* Hand::getHandCards()
{
	return handCards;
};;

void Hand::clearCards()
{
	while (!handCards->empty())
	{
		delete(handCards->back());
		handCards->back() = NULL;
		handCards->pop_back();
	}
};

void Deck::clearCards()
{
	while (!deckCards->empty())
	{
		delete(deckCards->back());
		deckCards->back() = NULL;
		deckCards->pop_back();
	}
};
vector<Card*>* Deck::getDeckCards()
{
	return deckCards;
};

Deck::Deck(Deck* otherDeck)
{
	this->deckCards = otherDeck->getDeckCards();
};

Deck::Deck()
{
	deckCards = new vector<Card*>;

}
Deck& Deck::operator=(Deck* otherDeck)
{
	clearCards();
	deckCards = otherDeck->getDeckCards();
	return *this;
}
;

Card* Deck::draw(Hand* playerHand)
{

	if (deckCards->empty())
	{
		cout << "Deck is empty!";
		return 0;
	}

	srand(time(NULL)); //initial random seed

	int totalNumberOfCards = deckCards->size();

	//Pick a random index from deck of cards
	int randomIndex = (rand() % totalNumberOfCards);
	Card* chosenCard = deckCards->at(randomIndex);
	playerHand->insertCard(chosenCard); //We are handing the pointer to the playerHand here.
	deckCards->at(randomIndex) = 0; // Preventing dangling pointer (NULL is same as 0)
	deckCards->erase(deckCards->begin() + randomIndex); //No need to use delete keyword here, transferring "ownership" of memory and deleting pointer from deck

	return chosenCard;
};

string Hand::cardsInHand()
{
	string values = "";



	for(Card i : *handCards)
	{
		values = values + to_string(*i.getCardType()) + " ";
	}
	return values;
}

string Deck::cardsInDeck()
{
	string values = "";



	for (Card i : *deckCards)
	{
		values = values + to_string(*i.getCardType()) + " ";
	}

	return values;
}



ostream& operator<<(ostream& os, Card* card)
{
	return os << *card->getCardType();
}

ostream& operator<<(ostream& os, Hand hand)
{
	string values = "{";

	if (hand.getHandCards() == NULL)
	{
		return os << "{ }\n";
	}

	for (Card i : *hand.getHandCards())
	{
		values = values + to_string(*i.getCardType()) + " ";
	}
	values = values + "} \n";

	return os << values;
}

ostream& operator<<(ostream& os, Deck deck)
{
	string values = "{";

	if (deck.getDeckCards() == NULL)
	{
		return os << "{ }";
	}

	for (Card i : *deck.getDeckCards())
	{
		values = values + to_string(*i.getCardType()) + " ";
	}
	values = values + "} \n";

	return os << values;
}
