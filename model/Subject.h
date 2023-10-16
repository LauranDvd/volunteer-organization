#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Subject {
private:
	vector<Observer*> allObservers;

public:
	void addObserver(Observer* toAdd) { allObservers.push_back(toAdd); }
	void deleteObserver(Observer* toDelete) { allObservers.erase(find(allObservers.begin(), allObservers.end(), toDelete)); }

	void notifyObservers();
};
