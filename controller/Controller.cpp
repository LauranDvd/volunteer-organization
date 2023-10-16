#include <algorithm>
#include <map>
#include <set>
#include "utilities.h"
#include "Controller.h"
#include "ControllerException.h"

vector<Volunteer> Controller::getAllInDepartmentSortedByName(const Department& department) const {
	auto allVolunteers = repository->getAll();

	sort(allVolunteers.begin(), allVolunteers.end(), [](const Volunteer& before, const Volunteer& after) {
		return before.getName() < after.getName();
		});

	vector<Volunteer> inDepartment;
	copy_if(allVolunteers.begin(), allVolunteers.end(), back_inserter(inDepartment), [&department](const Volunteer& tested) {
		return tested.getDepartment() == department.getName();
		});
	return inDepartment;
}

vector<Volunteer> Controller::getAllUnassignedVolunteers() const {
	auto allVolunteers = repository->getAll();

	vector<Volunteer> unassignedOnes;
	copy_if(allVolunteers.begin(), allVolunteers.end(), back_inserter(unassignedOnes), [](const Volunteer& tested) {
		return tested.getDepartment() == Volunteer::EMPTY_DEPARTMENT;
		});
	return unassignedOnes;
}

void Controller::addVolunteer(string name, string email, vector<string>& interests) { 
	if (name.empty() || email.empty()) {
		throw ControllerException("Name or email empty");
	}

	if (existsWithNameAndEmail(name, email)) {
		throw ControllerException("Someone with the same name and email exists");
	}

	Volunteer volunteer{ name, email, interests };
	repository->addItem(volunteer);
}

void Controller::deleteVolunteer(string name, string email) {
	if (name.empty() || email.empty()) {
		throw ControllerException("Name or email empty");
	}

	Volunteer toBeDeleted = getVolunteerByNameEmail(name, email);
	repository->deleteItem(toBeDeleted);
}



vector<Volunteer> Controller::getMostSuitableThreeUnassigned(const Department& department) const {
	// top 3

	vector<Volunteer> allUnassigned = getAllUnassignedVolunteers();
	sort(allUnassigned.begin(), allUnassigned.end(), [&department](const Volunteer& before, const Volunteer& after) {
		double scoreBefore = getSuitability(department, before);
		double scoreAfter = getSuitability(department, after);

		return scoreBefore > scoreAfter;
		});

	return vector<Volunteer>(allUnassigned.begin(), allUnassigned.begin() + min((int)allUnassigned.size(), 3));
}

void Controller::assignVolunteer(string name, string email, const Department& department) {
	Volunteer volunteer = getVolunteerByNameEmail(name, email);
	repository->assignVolunteer(volunteer, department.getName());
}

void Controller::unassignVolunteer(string name, string email) {
	Volunteer volunteer = getVolunteerByNameEmail(name, email);
	repository->unassignVolunteer(volunteer);
}

vector<string> Controller::getAllNamesOfNonemptyDepartments() const {
	set<string> allDepartmentNames;
	for (const Volunteer& volunteer : repository->getAll()) {
		if (volunteer.getDepartment() != Volunteer::EMPTY_DEPARTMENT) {
			allDepartmentNames.insert(volunteer.getDepartment());
		}
	}
	return vector<string>(allDepartmentNames.begin(), allDepartmentNames.end());
}

int Controller::getMemberCount(string departmentName) const {
	vector<Volunteer> all = repository->getAll();
	return count_if(all.begin(), all.end(), [&departmentName](const Volunteer& volunteer) {
		return volunteer.getDepartment() == departmentName;
		});
}


double Controller::getSuitability(const Department& department, const Volunteer& volunteer) {
	// score=(no. words from volunteer' list which are in description) / (no. words in description)

	const string& departmentDescription = department.getDescription();
	const vector<string>& volunteerInterests = volunteer.getInterests();

	int countFound = count_if(volunteerInterests.begin(), volunteerInterests.end(), [&departmentDescription](const string& volunteerInterest) {
		return departmentDescription.find(volunteerInterest) != string::npos;
		});

	return 1.00 * countFound / countWordsInString(department.getDescription());
}

Volunteer Controller::getVolunteerByNameEmail(string name, string email) const {
	auto allVolunteers = repository->getAll();

	return *find_if(allVolunteers.begin(), allVolunteers.end(), [&name, &email](const Volunteer& iterated) {
		return name == iterated.getName() && email == iterated.getEmail();
		});
}

bool Controller::existsWithNameAndEmail(string name, string email) const {
	const vector<Volunteer> all = repository->getAll();

	return find_if(all.begin(), all.end(), [&name, &email](const Volunteer& tested) {
		return tested.getName() == name && tested.getEmail() == email;
		}) != all.end();
}
