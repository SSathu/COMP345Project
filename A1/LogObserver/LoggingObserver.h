#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable {
public:
	virtual string* stringToLog() = 0;
	ILoggable();
	ILoggable(ILoggable* copy);
	~ILoggable();
};



class Observer {
public:
	~Observer();
	virtual void Update(ILoggable* log) = 0;
protected:
	Observer();
	Observer(Observer* o);

};

class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(ILoggable* log);
	Subject(Subject* sub);
	Subject();
	~Subject();
private:
	list<Observer*>* _observers;
};


class LogObserver : public Observer {
public:
	LogObserver();
	LogObserver(LogObserver* logO);
	~LogObserver();
	void Update(ILoggable* log);
};