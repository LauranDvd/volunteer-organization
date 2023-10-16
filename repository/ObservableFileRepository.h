#pragma once
#include "Subject.h"
#include <string>
#include <vector>
#include <fstream>

template <class T>
class ObservableFileRepository : public Subject {
protected:
	const std::string filename;
	vector<T> allItems;

public:
	ObservableFileRepository(std::string filename) : filename{ filename } { loadFromFile(); }

	vector<T> getAll() const { return allItems; }
	void addItem(T toAdd);
	void deleteItem(const T& item);

protected:
	void loadFromFile();
	void saveToFile();
};


template<class T>
void ObservableFileRepository<T>::addItem(T toAdd) {
	allItems.push_back(toAdd);

	notifyObservers();
	saveToFile();
}

template <class T>
void ObservableFileRepository<T>::deleteItem(const T& item) {
	allItems.erase(find(allItems.begin(), allItems.end(), item));

	notifyObservers();
	saveToFile();
}

template <class T>
void ObservableFileRepository<T>::loadFromFile() {
	ifstream fin(filename);

	T justRead;
	while (fin >> justRead) {
		allItems.push_back(justRead);
	}

	fin.close();
}

template <class T>
void ObservableFileRepository<T>::saveToFile() {
	ofstream fout(filename);

	for (T& item : allItems) {
		fout << item << "\n";
	}

	fout.close();
}
