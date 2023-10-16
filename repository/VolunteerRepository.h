#pragma once
#include "Volunteer.h"
#include "Subject.h"
#include "ObservableFileRepository.h"

class VolunteerRepository : public ObservableFileRepository<Volunteer> {
private:

public:
	VolunteerRepository(string filename) : ObservableFileRepository{ filename } {}

	const Volunteer& getByNameEmail(string name, string email) const;
	void assignVolunteer(const Volunteer& volunteer, string departmentName);
	void unassignVolunteer(const Volunteer& volunteer);
};
