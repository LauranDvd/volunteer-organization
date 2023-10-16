#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Volunteer {
public:
	static const string EMPTY_DEPARTMENT;

private:
	string name, email;
	vector<string> interests;
	string department;

public:
	Volunteer() {}
	Volunteer(string name, string email, vector<string> interests) : name{ name }, email{ email }, interests{ interests }, department{ EMPTY_DEPARTMENT } {}

	static pair<string, string> getFieldsFromStrShowingNameEmail(string stringFormShowingNameEmail);

	string getName() const { return name; }
	string getEmail() const { return email; }
	const vector<string>& getInterests() const { return interests; }
	string getDepartment() const { return department; }
	string toStringShowingNameEmail() const { return name + " | " + email; }
	string toStringShowingNameEmailDepartment() const;

	void setDepartment(string given) { department = given; }

	bool operator==(const Volunteer& other) {
		return name == other.name && email == other.email;
	}

	friend istream& operator>>(istream& reader, Volunteer& volunteer) {
		do {
			getline(reader, volunteer.name);
		} while (volunteer.name.empty() && !reader.eof());
		if (reader.eof()) {
			return reader;
		}

		reader >> volunteer.email;

		volunteer.interests.clear();
		int noInterests;
		reader >> noInterests;
		while (noInterests--) {
			string interest;
			reader >> interest;
			volunteer.interests.push_back(interest);
		}

		do {
			getline(reader, volunteer.department);
		} while (volunteer.department.empty());


		return reader;
	}

	friend ostream& operator<<(ostream& writer, Volunteer& volunteer) {
		writer << volunteer.name << "\n" << volunteer.email << "\n" << volunteer.interests.size() << "\n";
		for (auto interest : volunteer.interests) {
			writer << interest << "\n";
		}

		writer << volunteer.getDepartment() << "\n";

		return writer;
	}

	void clearDepartment() { department = EMPTY_DEPARTMENT; }
};
