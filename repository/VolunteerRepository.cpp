#include <fstream>
#include "VolunteerRepository.h"

const Volunteer& VolunteerRepository::getByNameEmail(string name, string email) const {
	return *find_if(allItems.begin(), allItems.end(), [&name, &email](const Volunteer& iterated) {
		return name == iterated.getName() && email == iterated.getEmail();
		});
}

void VolunteerRepository::assignVolunteer(const Volunteer& volunteer, string departmentName) {
	for (Volunteer& iterationVolunteer : allItems) {
		if (iterationVolunteer == volunteer) {
			iterationVolunteer.setDepartment(departmentName);
		}
	}

	notifyObservers();
	saveToFile();
}

void VolunteerRepository::unassignVolunteer(const Volunteer& volunteer) {
	for (Volunteer& iterationVolunteer : allItems) {
		if (iterationVolunteer == volunteer) {
			iterationVolunteer.clearDepartment();
		}
	}

	notifyObservers();
	saveToFile();
}
