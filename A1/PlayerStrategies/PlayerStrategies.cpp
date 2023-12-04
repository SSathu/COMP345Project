#include "PlayerStrategies.h";
#include "../Map/Map.h"
#include <queue>



void NeutralPlayerStrategy::issueOrder()
{
}

vector<Territory*>* NeutralPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(s);
				}
			}

		}

	}
	return list;
}

vector<Territory*>* NeutralPlayerStrategy::toDefend()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(def);
				}
			}

		}

	}
	return list;
	}
	


void CheaterPlayerStrategy::issueOrder()
{
	vector<Territory*>* conqueringList = this->toAttack();

	for (Territory* attacking : *conqueringList)
	{
		AdvanceOrder* order = new AdvanceOrder();
		order->cheater = true;
		order->issuingPlayer = p;
		order->destination = attacking;
		
		p->orderList->push_back(order);

	}
}

vector<Territory*>* CheaterPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(s);
				}
			}

		}

	}
	return list;
}

vector<Territory*>* CheaterPlayerStrategy::toDefend()
{
//
	return nullptr;
}

void HumanPlayerStrategy::issueOrder()
{
	vector<Territory*>* toAttack = this->toAttack();
	vector<Territory*>* toDefend = this->toDefend();
	int value;
	int reinforcementPool = p->reinforcementPool;
	while (reinforcementPool > 0)
	{
		std::cout << "Select territory to deploy armies on: " << endl << "Current army pool: " << reinforcementPool << endl;
		for (int i=0;i<toDefend->size();i++)
		{
			std::cout << i << ". " << toDefend->at(i)->getName() + ": " << *toDefend->at(i)->numArmies << endl;
		}
		std::cin >> value;

		if (value > toDefend->size() || value < 0)
		{
			std::cout << "Territory # does not exist!" << endl;;
			continue;
		}

		std::cout << "Select how many reinforcement armies to send: " << endl;

		int value2;
		std::cin >> value2;

		if (value2 > reinforcementPool || value2 < 1)
		{
			std::cout << "You do not have that number of armies to send!" << endl;
			continue;
		}
		reinforcementPool = reinforcementPool - value2;
		p->orderList->push_back(new DeployOrder(p, value2, toDefend->at(value)));
	}
	
	

	

	bool continueTurn = true;
	vector<Territory*>* territoriesToAttackFrom = new vector<Territory*>;

	Order* orderBeingMade;

	while (continueTurn)
	{
		std::cout << "Choose next action: " << endl << "1. Attack territory " << endl << "2. Use Card" << endl << "3. End turn" << endl;
		int value3;
		std::cin >> value3;
		switch (value3)
		{
		case 1:
		{
			territoriesToAttackFrom->clear();
			std::cout << "Select territory to attack: " << endl;
			for (int i = 0; i < toAttack->size(); i++)
			{
				std::cout << i << ". " << toAttack->at(i)->getName() + ": " << *toAttack->at(i)->numArmies << endl;
			}
			int territoryPicked;
			std::cin >> territoryPicked;

			if (territoryPicked > toAttack->size() || territoryPicked < 0)
			{
				std::cout << "This territory does not exist!";
				break;
			}

			Territory* territoryBeingAttacked = toAttack->at(territoryPicked);



			for (Territory* terr : *territoryBeingAttacked->neighbors)
			{
				if (std::find(toDefend->begin(), toDefend->end(), terr) != toDefend->end())
				{
					territoriesToAttackFrom->push_back(terr);
				}
			}

			std::cout << "Choose territory to send armies from for attack: " << endl;
			for (int i = 0; i < territoriesToAttackFrom->size(); i++)
			{
				std::cout << i<< ". " << toDefend->at(i)->getName() + ": " << *toDefend->at(i)->numArmies << endl;
			}

			int terrToAttF;
			std::cin >> terrToAttF;

			if (terrToAttF > territoriesToAttackFrom->size() || terrToAttF < 0)
			{
				std::cout << "This territory does not exist!";
				break;
			}

			Territory* terrPicked = territoriesToAttackFrom->at(terrToAttF);

			std::cout << "Choose the number of armies to send " << endl << "Available armies: " << *terrPicked->numArmies;

			int attackingArmies;

			std::cin >> attackingArmies;

			if (attackingArmies > *terrPicked->numArmies || attackingArmies < 1)
			{
				std::cout << "Invalid number of armies to send" << endl;
				break;
			}

			p->orderList->push_back(new AdvanceOrder(p, terrPicked, territoryBeingAttacked, attackingArmies));
			std::cout << "Added new Advance Order";
			break;
		}


		case 2:
		{
			vector<Card*>* handCards = p->hand->handCards;
			std::cout << "Select Card to play: ";
			for (int i = 0; i < handCards->size(); i++)
			{
				std::cout << i + ". " << handCards->at(i)->getcardName() << endl;
			}
			int cardPicked;
			std::cin >> cardPicked;

			if (cardPicked > handCards->size() || cardPicked < 0)
			{
				std::cout << "This card does not exist!";
				break;
			}
			Card* cardBeingPlayed = handCards->at(cardPicked);
			int cardType = *cardBeingPlayed->getCardType();

			switch (cardType)
			{
			case 0:
			{
				Order* orderBeingMade = p->hand->play(cardBeingPlayed, p->deck);
				BombOrder* bomborder = static_cast<BombOrder*>(orderBeingMade);

				bomborder->issuingPlayer = p;

				std::cout << "Select territory to bomb: " << endl;
				for (int i = 0; i < toAttack->size(); i++)
				{
					std::cout << i + ". " << toAttack->at(i)->getName() + ": " << toAttack->at(i)->numArmies << endl;
				}
				int territoryPicked;
				std::cin >> territoryPicked;

				if (territoryPicked > toAttack->size() || territoryPicked < 0)
				{
					std::cout << "This territory does not exist!";
					break;
				}
				Territory* territoryBeingAttacked = toAttack->at(territoryPicked);

				bomborder->attackedTerritory = territoryBeingAttacked;

				p->orderList->push_back(bomborder);
				std::cout << "Added new Bomb Order";
				break;
			}

			case 1:
			{
				orderBeingMade = p->hand->play(cardBeingPlayed, p->deck);
				DeployOrder* deployOrder = static_cast<DeployOrder*>(orderBeingMade);
				int defendTerr;
				std::cout << "Select territory to deploy armies on: " << endl;
				for (int i = 0; i < toDefend->size(); i++)
				{
					std::cout << i + ". " << toDefend->at(i)->getName() + ": " << toDefend->at(i)->numArmies << endl;
				}
				std::cin >> defendTerr;

				if (defendTerr > toDefend->size() || defendTerr < 0)
				{
					std::cout << "Territory # does not exist!" << endl;;
					break;
				}

				Territory* defendingTerritory = toDefend->at(defendTerr);

				deployOrder->issuingPlayer = p;
				deployOrder->numberOfArmies = 3;
				deployOrder->area = defendingTerritory;

				p->orderList->push_back(deployOrder);
				std::cout << "Added new Deploy Order";
				break;
			}

			case 2:
			{
				orderBeingMade = p->hand->play(cardBeingPlayed, p->deck);
				BlockadeOrder* blockadeOrder = static_cast<BlockadeOrder*>(orderBeingMade);
				int defendTerr;
				std::cout << "Select territory to blockade: " << endl;
				for (int i = 0; i < toDefend->size(); i++)
				{
					std::cout << i + ". " << toDefend->at(i)->getName() + ": " << toDefend->at(i)->numArmies << endl;
				}
				std::cin >> defendTerr;

				if (defendTerr > toDefend->size() || defendTerr < 0)
				{
					std::cout << "Territory # does not exist!" << endl;;
					break;
				}

				Territory* blockadeTerritory = toDefend->at(defendTerr);

				blockadeOrder->area = blockadeTerritory;
				blockadeOrder->issuingPlayer = p;

				p->orderList->push_back(blockadeOrder);
				std::cout << "Added new Blockade Order";
				break;
			}

			case 3:
			{
				Order* orderBeingMade = p->hand->play(cardBeingPlayed, p->deck);
				AirliftOrder* airliftOrder = static_cast<AirliftOrder*>(orderBeingMade);
				int defendTerr;

				airliftOrder->issuingPlayer = p;

				std::cout << "Select territory to airlift armies from: " << endl;
				for (int i = 0; i < p->territory->size(); i++)
				{
					std::cout << i + ". " << p->territory->at(i)->getName() + ": " << p->territory->at(i)->numArmies << endl;
				}
				std::cin >> defendTerr;

				if (defendTerr > p->territory->size() || defendTerr < 0)
				{
					std::cout << "Territory # does not exist!" << endl;;
					break;
				}



				Territory* defendingTerritory = toDefend->at(defendTerr);
				airliftOrder->start = defendingTerritory;

				int numArmiesAirlifted;
				std::cout << "Select number of armies to airlift: " << endl;
				std::cout << "Number of armies available: " << defendingTerritory->numArmies << endl;
				std::cin >> numArmiesAirlifted;
				if (numArmiesAirlifted > *defendingTerritory->numArmies || numArmiesAirlifted < 1)
				{
					std::cout << "Invalid number of armies to airlift" << endl;;
					break;
				}

				airliftOrder->numberOfArmies = numArmiesAirlifted;

				std::cout << "Select territory to airlift armies to: " << endl;
				for (int i = 0; i < toDefend->size(); i++)
				{
					std::cout << i + ". " << toDefend->at(i)->getName() + ": " << toDefend->at(i)->numArmies << endl;
				}
				int destinationTerr;
				std::cin >> destinationTerr;

				if (destinationTerr > toDefend->size() || destinationTerr < 0)
				{
					std::cout << "Territory # does not exist!" << endl;;
					break;
				}
				Territory* destinationTerritory = toDefend->at(destinationTerr);

				airliftOrder->destination = destinationTerritory;

				p->orderList->push_back(airliftOrder);
				std::cout << "Added new Airlift Order";
				break;
			}


			case 4:
			{
				Order* orderBeingMade = p->hand->play(cardBeingPlayed, p->deck);
				NegotiateOrder* negotiateOrder = static_cast<NegotiateOrder*>(orderBeingMade);

				for (int i = 0; i < toAttack->size(); i++)
				{
					std::cout << i + ". " << toAttack->at(i)->getPlayer().name + ": " << toAttack->at(i)->numArmies << endl;
				}
				int territoryPicked;
				std::cin >> territoryPicked;

				if (territoryPicked > toAttack->size() || territoryPicked < 0)
				{
					std::cout << "This player does not exist!";
					break;
				}
				Player* player = toAttack->at(territoryPicked)->playerOwner;

				negotiateOrder->issuingPlayer = p;
				negotiateOrder->targetPlayer = player;

				p->orderList->push_back(negotiateOrder);
				std::cout << "Added new Negotiate Order";
				break;
			}


			}
		}




		case 3:
		{
			std::cout << "Ending turn." << endl;
			continueTurn = false;
			break;
		}

		}


	}

}

vector<Territory*>* HumanPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(s);
				}
			}

		}

	}
	return list;
}

vector<Territory*>* HumanPlayerStrategy::toDefend()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(def);
				}
			}

		}

	}
	return list;
}

void AggressivePlayerStrategy::issueOrder()
{
	vector<Territory*>* defendingTerritories = toDefend();
	vector<Territory*>* attackingTerritories = toAttack();

	int armiesToDeploy = p->reinforcementPool;

	for (Territory* t : *defendingTerritories)
	{
		DeployOrder* d = new DeployOrder(p, armiesToDeploy, t);
		p->orderList->push_back(d);

		for (Territory* h : *attackingTerritories)
		{
			AdvanceOrder* a = new AdvanceOrder(p, t, h, *t->numArmies);
			p->orderList->push_back(a);
		}

	}

	bool usedACard = false;


	for (Card* card : *p->hand->handCards)
	{
		if (usedACard == false)
		{
			int getCardType = *card->getCardType();;
			

			switch (getCardType)
			{
			case 0:
			{
				Order* orderBeingMade = p->hand->play(card, p->deck);
				BombOrder* bomborder = static_cast<BombOrder*>(orderBeingMade);
				bomborder->attackedTerritory = *attackingTerritories->begin();
				bomborder->issuingPlayer = p;
				p->orderList->push_back(bomborder);
				usedACard = true;
				break;
			}

			default:
				break;
			}


		}


	}




}

vector<Territory*>* AggressivePlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(s);
				}
			}

		}

	}
	return list;

	

}

vector<Territory*>* AggressivePlayerStrategy::toDefend()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(s);
				}
			}

		}

	}

	int numOfArmies = 0;

	for (int i=0; i<list->size();i++)
	{
		if (numOfArmies < *list->at(i)->numArmies)
		{
			numOfArmies = *list->at(i)->numArmies;
		}
		else
		{
			list->erase(list->begin() + i);
		}
	}
	return list;
}

void BenevolentPlayerStrategy::issueOrder()
{
	vector<Territory*>* defendingTerritories = toDefend();

	int armiesToDeploy = p->reinforcementPool;

	for (Territory* t : *defendingTerritories)
	{
		DeployOrder* d = new DeployOrder(p, armiesToDeploy, t);
		p->orderList->push_back(d);
	}

	bool usedACard = false;
	Order* orderBeingMade;

	for (Card* card : *p->hand->handCards)
	{
		if (usedACard == false)
		{
			int getCardType = *card->getCardType();;


			switch (getCardType)
			{
			case 1:
			{
				orderBeingMade = p->hand->play(card, p->deck);
				DeployOrder* deployOrder;
				deployOrder = static_cast<DeployOrder*>(orderBeingMade);
				int armiesToDeploy;
				armiesToDeploy = p->reinforcementPool;
				deployOrder->area = defendingTerritories->front();
				deployOrder->issuingPlayer = p;
				deployOrder->numberOfArmies = armiesToDeploy;

				p->orderList->push_back(deployOrder);
				usedACard = true;
				break;
			}
				 
			case 2:
			{
				orderBeingMade = p->hand->play(card, p->deck);
				BlockadeOrder* blockadeOrder;
				blockadeOrder = static_cast<BlockadeOrder*>(orderBeingMade);
				blockadeOrder->area = defendingTerritories->front();
				blockadeOrder->issuingPlayer = p;

				p->orderList->push_back(blockadeOrder);
				usedACard = true;
				break;
			}
				 
			case 3:
			{
				orderBeingMade = p->hand->play(card, p->deck);
				AirliftOrder* airLiftOrder;
				airLiftOrder = static_cast<AirliftOrder*>(orderBeingMade);
				airLiftOrder->issuingPlayer = p;
				airLiftOrder->destination = defendingTerritories->front();

				int numOfArmies;
				numOfArmies = 0;
				Territory* starting;
				for (Territory* terr : *p->territory)
				{
					if (!(terr->getName() == defendingTerritories->front()->getName()) && *terr->numArmies > numOfArmies)
					{
						numOfArmies = *terr->numArmies;
						starting = terr;
					}
				}
				airLiftOrder->start = starting;
				airLiftOrder->numberOfArmies = numOfArmies / 2;

				p->orderList->push_back(airLiftOrder);
				usedACard = true;
				break;
			}
				
			case 4: 
			{
				orderBeingMade = p->hand->play(card, p->deck);
				NegotiateOrder* negotiateOrder;
				negotiateOrder = static_cast<NegotiateOrder*>(orderBeingMade);
				negotiateOrder->issuingPlayer = p;
				negotiateOrder->targetPlayer = toAttack()->front()->playerOwner;



				p->orderList->push_back(negotiateOrder);
				usedACard = true;
				break;
			}
				 
			default:
			{
				usedACard = true;
				break;
			}
				
			}


		}


	}
}

vector<Territory*>* BenevolentPlayerStrategy::toAttack()
{
	return nullptr;
}

vector<Territory*>* BenevolentPlayerStrategy::toDefend()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;

		for (Territory* def : *s->neighbors)
		{
			if (def->playerOwner != s->playerOwner)
			{
				bool alreadyInList = false;
				for (Territory* inList : *list)
				{
					if (inList->getName() == def->getName())
					{
						alreadyInList = true;
					}


				}
				if (!alreadyInList)
				{
					list->push_back(s);
				}
			}

		}

	}

	int numOfArmies = 10000;

	for (int i = 0; i < list->size(); i++)
	{
		if (numOfArmies > *list->at(i)->numArmies)
		{
			list->erase(list->begin() + i);
		}
		else
		{
			numOfArmies = *list->at(i)->numArmies;
		}
	}
	return list;
}




