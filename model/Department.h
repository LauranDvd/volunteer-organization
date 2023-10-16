#pragma once
#include <string>
using namespace std;

class Department {
private:
	string name, description;

public:
	Department() {}
	Department(string name, string description) : name{ name }, description{ description } {}

	string getName() const { return name; }
	string getDescription() const { return description; }

	friend istream& operator>>(istream& reader, Department& department) {
		do {
			getline(reader, department.name);
		} while (department.name.empty() && !reader.eof());
		if (reader.eof()) {
			return reader;
		}

		getline(reader, department.description);

		return reader;
	}
};
