#pragma once
#include "VolunteerRepository.h"
#include "Department.h"

class Controller {
private:
	VolunteerRepository* repository;

public:
	Controller(VolunteerRepository* repo) : repository{ repo } {}

	vector<Volunteer> getAllInDepartmentSortedByName(const Department& department) const;
	vector<Volunteer> getAllUnassignedVolunteers() const;
	vector<Volunteer> getAllVolunteers() const { return repository->getAll(); }
	void addVolunteer(string name, string email, vector<string>& interests);
	void deleteVolunteer(string name, string email);
	vector<Volunteer> getMostSuitableThreeUnassigned(const Department& department) const;
	void assignVolunteer(string name, string email, const Department& department);
	void unassignVolunteer(string name, string email);
	vector<string> getAllNamesOfNonemptyDepartments() const;
	int getMemberCount(string departmentName) const;

private:
	static double getSuitability(const Department& department, const Volunteer& volunteer);
	Volunteer getVolunteerByNameEmail(string name, string email) const;
	bool existsWithNameAndEmail(string name, string email) const;
};
