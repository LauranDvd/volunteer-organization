#include "OverviewWidget.h"
#include "Controller.h"
#include <set>
#include "ControllerException.h"
#include <qmessagebox.h>
#include "utilities.h"

OverviewWidget::OverviewWidget(Controller* controller, vector<string> allDepartmentNames, QWidget* parent) :
	QWidget{ parent }, controller{ controller }, allDepartmentNames{ allDepartmentNames } {
	ui.setupUi(this);

	populateDepartmentList();
	populateVolunteerList();
	connectSignalsAndSlots();
}

OverviewWidget::~OverviewWidget() {
}

void OverviewWidget::populateDepartmentList() {
	ui.departmentsList->clear();

	const vector<string>& nonemptyDepartments = controller->getAllNamesOfNonemptyDepartments();
	for (string depName : nonemptyDepartments) {
		ui.departmentsList->addItem(QString::fromStdString(depName + ": " + to_string(controller->getMemberCount(depName))) + " people");
	}

	for (auto depName : allDepartmentNames) {
		if (std::find(nonemptyDepartments.begin(), nonemptyDepartments.end(), depName) == nonemptyDepartments.end()) {
			ui.departmentsList->addItem(QString::fromStdString(depName + " didnt interest anybody yet"));
		}
	}
}

void OverviewWidget::populateVolunteerList() {
	ui.volunteersList->clear();

	const vector<Volunteer>& allVolunteers = controller->getAllVolunteers();
	for (const Volunteer& volunteer : allVolunteers) {
		ui.volunteersList->addItem(QString::fromStdString(volunteer.toStringShowingNameEmailDepartment()));
	}
}

void OverviewWidget::connectSignalsAndSlots() {
	QObject::connect(ui.addVolunteerButton, &QPushButton::clicked, this, &OverviewWidget::addVolunteer);
	QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &OverviewWidget::deleteSelectedVolunteer);
}

void OverviewWidget::addVolunteer() {
	string name = ui.volunteerNameInput->text().toStdString();
	string email = ui.volunteerEmailInput->text().toStdString();

	string interestsStr = ui.volunteerInterestsInput->text().toStdString();
	vector<string> interestsVector = stringToVectorBySpaces(interestsStr);

	try {
		controller->addVolunteer(name, email, interestsVector);
	}
	catch (ControllerException& caught) {
		QMessageBox::critical(this, "ERROR", caught.what());
	}
}

void OverviewWidget::deleteSelectedVolunteer() {
	const auto& selected = ui.volunteersList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;

	string strFormShowingNameEmail = ui.volunteersList->currentItem()->text().toStdString();
	pair<string, string> nameAndEmail = Volunteer::getFieldsFromStrShowingNameEmail(strFormShowingNameEmail);

	try {
		controller->deleteVolunteer(nameAndEmail.first, nameAndEmail.second);
	}
	catch (ControllerException& caught) {
		QMessageBox::critical(this, "ERROR", caught.what());
	}
}

void OverviewWidget::update() {
	populateDepartmentList();
	populateVolunteerList();
}
