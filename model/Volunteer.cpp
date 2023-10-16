#include <string>
#include "Volunteer.h"
using namespace std;

const string Volunteer::EMPTY_DEPARTMENT = "-";


pair<string, string> Volunteer::getFieldsFromStrShowingNameEmail(string stringFormShowingNameEmail) {
	int delimiterPos = stringFormShowingNameEmail.find('|');
	string name = stringFormShowingNameEmail.substr(0, delimiterPos - 1);
	string email = stringFormShowingNameEmail.substr(delimiterPos + 2, stringFormShowingNameEmail.size() - (delimiterPos + 2));

	return make_pair(name, email);
}

string Volunteer::toStringShowingNameEmailDepartment() const {
	string departmentStr = "";
	if (department != Volunteer::EMPTY_DEPARTMENT) {
		departmentStr = " -- " + department;
	}

	return name + " (" + email + ")" + departmentStr;
}
