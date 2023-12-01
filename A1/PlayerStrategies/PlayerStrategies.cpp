#include "PlayerStrategies.h";
#include "../Map/Map.h"


vector<Territory*>* NeutralPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				if (!(std::find(*list->begin(), *list->end(), neighboringTerritory) != *list->end()))
				{
					list->push_back(neighboringTerritory);
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
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				containsEnemyNeighbor = true;
			}

		}
		if (containsEnemyNeighbor)
		{
			list->push_back(s);
		}
	}
	return list;
}

vector<Territory*>* CheaterPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				if (!(std::find(*list->begin(), *list->end(), neighboringTerritory) != *list->end()))
				{
					list->push_back(neighboringTerritory);
				}
			}

		}
	}
	return list;
}

vector<Territory*>* CheaterPlayerStrategy::toDefend()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				containsEnemyNeighbor = true;
			}

		}
		if (containsEnemyNeighbor)
		{
			list->push_back(s);
		}
	}
	return list;
}

vector<Territory*>* HumanPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				if (!(std::find(*list->begin(), *list->end(), neighboringTerritory) != *list->end()))
				{
					list->push_back(neighboringTerritory);
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
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				containsEnemyNeighbor = true;
			}

		}
		if (containsEnemyNeighbor)
		{
			list->push_back(s);
		}
	}
	return list;
}

vector<Territory*>* AggressivePlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				if (!(std::find(*list->begin(), *list->end(), neighboringTerritory) != *list->end()))
				{
					list->push_back(neighboringTerritory);
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
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				containsEnemyNeighbor = true;
			}

		}
		if (containsEnemyNeighbor)
		{
			list->push_back(s);
		}
	}
	return list;
}

vector<Territory*>* BenevolentPlayerStrategy::toAttack()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				if (!(std::find(*list->begin(), *list->end(), neighboringTerritory) != *list->end()))
				{
					list->push_back(neighboringTerritory);
				}
			}

		}
	}
	return list;
}

vector<Territory*>* BenevolentPlayerStrategy::toDefend()
{
	vector<Territory*>* list = new vector<Territory*>;
	for (Territory* s : *p->territory) {
		bool containsEnemyNeighbor = false;
		for (int i = 0; i < s->neighbors->size(); i++)
		{
			Territory* neighboringTerritory = s->neighbors->at(i);

			if (!(std::find(*p->territory->begin(), *p->territory->end(), neighboringTerritory) != *p->territory->end()))
			{
				containsEnemyNeighbor = true;
			}

		}
		if (containsEnemyNeighbor)
		{
			list->push_back(s);
		}
	}
	return list;
}
