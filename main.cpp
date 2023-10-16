#include "VolunteeringApp.h"
#include <QtWidgets/QApplication>
#include "DepartmentWidget.h"
#include "VolunteerRepository.h"
#include "Controller.h"
#include "Department.h"
#include <fstream>
#include "OverviewWidget.h"
#include "OneWindow.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	VolunteerRepository* repo = new VolunteerRepository{ "volunteers.txt" };
	Controller* controller = new Controller{ repo };

	// the window which contains all the tabs
	OneWindow oneWindow{ controller };


	// start one tab for each department 
	ifstream fin("departments.txt");

	Department department;
	vector<string> allDepartmentNames;
	vector<DepartmentWidget*> allDepartmentWidgets;
	while (fin >> department) {
		allDepartmentNames.push_back(department.getName());

		DepartmentWidget* w = new DepartmentWidget{ department, controller };
		allDepartmentWidgets.push_back(w);
		repo->addObserver(w);
		oneWindow.addTabAtBeginning(w, department.getName());
	}

	fin.close();

	// the overview tab
	OverviewWidget w{ controller, allDepartmentNames };
	repo->addObserver(&w);
	oneWindow.addTabAtBeginning(&w, "Overview");

	oneWindow.setWindowState(Qt::WindowMaximized);
	oneWindow.show();

	return a.exec();
}
