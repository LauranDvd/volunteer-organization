#include <qmessagebox.h>
#include "DepartmentWidget.h"
#include "Controller.h"
#include "Department.h"
#include "utilities.h"
#include "ControllerException.h"

DepartmentWidget::DepartmentWidget(Department department, Controller* controller, QWidget* parent) :
	QWidget{ parent }, controller{ controller }, department{ department } {
	ui.setupUi(this);

	setWindowTitle(QString::fromStdString(department.getName()));
	ui.descriptionText->setText(QString::fromStdString(department.getDescription()));

	connectSignalsAndSlots();
	populateMyVolunteersList();
	populateUnassignedList();
}

DepartmentWidget::~DepartmentWidget() {
}

void DepartmentWidget::connectSignalsAndSlots() {
	QObject::connect(ui.showMostSuitable, &QPushButton::clicked, this, &DepartmentWidget::showMostSuitable);
	QObject::connect(ui.assignButton, &QPushButton::clicked, this, &DepartmentWidget::assignSelected);
	QObject::connect(ui.unassignButton, &QPushButton::clicked, this, &DepartmentWidget::unassignSelected);
}

void DepartmentWidget::populateMyVolunteersList() {
	ui.myVolunteersList->clear();

	const vector<Volunteer>& myVolunteers = controller->getAllInDepartmentSortedByName(department);
	for (const Volunteer& volunteer : myVolunteers) {
		ui.myVolunteersList->addItem(QString::fromStdString(volunteer.toStringShowingNameEmail()));
	}
}

void DepartmentWidget::populateUnassignedList() {
	ui.unassignedList->clear();

	const vector<Volunteer>& allUnassigned = controller->getAllUnassignedVolunteers();
	for (const Volunteer& volunteer : allUnassigned) {
		ui.unassignedList->addItem(QString::fromStdString(volunteer.toStringShowingNameEmail()));
	}
}

void DepartmentWidget::showMostSuitable() {
	ui.unassignedList->clear();

	const auto& mostSuitable = controller->getMostSuitableThreeUnassigned(department);
	for (const Volunteer& volunteer : mostSuitable) {
		ui.unassignedList->addItem(QString::fromStdString(volunteer.toStringShowingNameEmail()));
	}
}

void DepartmentWidget::assignSelected() {
	const auto& selected = ui.unassignedList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;

	string strFormShowingNameEmail = ui.unassignedList->currentItem()->text().toStdString();
	pair<string, string> nameAndEmail = Volunteer::getFieldsFromStrShowingNameEmail(strFormShowingNameEmail);

	controller->assignVolunteer(nameAndEmail.first, nameAndEmail.second, department);
}

void DepartmentWidget::unassignSelected() {
	const auto& selected = ui.myVolunteersList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;

	string strFormShowingNameEmail = ui.myVolunteersList->currentItem()->text().toStdString();
	pair<string, string> nameAndEmail = Volunteer::getFieldsFromStrShowingNameEmail(strFormShowingNameEmail);

	controller->unassignVolunteer(nameAndEmail.first, nameAndEmail.second);
}

void DepartmentWidget::update() {
	// reset both lists
	populateMyVolunteersList();
	populateUnassignedList();  // TODO show best suited, if they were shown before (maybe)
}
