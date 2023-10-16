#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OverviewWidget.h"
#include "Controller.h"
#include "Observer.h"

class OverviewWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	OverviewWidget(Controller* controller, vector<string> allDepartmentNames, QWidget* parent = nullptr);
	~OverviewWidget();

private:
	Ui::OverviewWidget ui;
	Controller* controller;
	vector<string> allDepartmentNames;

	void populateDepartmentList();
	void populateVolunteerList();
	void connectSignalsAndSlots();

	void addVolunteer();
	void deleteSelectedVolunteer();

	void update() override;  // Observer
};
