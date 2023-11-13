#include "LoggingObserver.h"
#include <iostream>;
#include <fstream>;

using namespace std;


Subject::Subject() {
	_observers = new list<Observer*>;
};

ILoggable::ILoggable()
{

}

ILoggable::ILoggable(ILoggable* copy)
{
}

ILoggable::~ILoggable()
{

}

Subject::~Subject()
{
	delete _observers;
};

Observer::Observer() {
}
Observer::Observer(Observer* o)
{
}
;
Observer::~Observer() {
};


void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};

void Subject::Detach(Observer* o) {
	_observers->remove(o);
};

void Subject::Notify(ILoggable* log) {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(log);
}
Subject::Subject(Subject* sub)
{
	_observers = sub->_observers;
}
;


LogObserver::LogObserver()
{

}
LogObserver::LogObserver(LogObserver* logO)
{
}
;

LogObserver::~LogObserver()
{
};

void LogObserver::Update(ILoggable* log)
{
	string* theString = log->stringToLog();
	ofstream output;
	std::cout << *theString;
	output.open("gamelog.txt", std::ios_base::app);
	output << *theString << endl;
	output.close();
	
}

