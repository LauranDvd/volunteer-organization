#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DepartmentWidget.h"
#include "Controller.h"
#include "Department.h"

class DepartmentWidget : public QWidget, public Observer
{
    Q_OBJECT

public:
    DepartmentWidget(Department department, Controller* controller, QWidget* parent = nullptr);
    ~DepartmentWidget();

private:
    Ui::DepartmentWidget ui;
    Controller* controller;
    Department department;

    void connectSignalsAndSlots();
    void populateMyVolunteersList();
    void populateUnassignedList();

    void showMostSuitable();
    void assignSelected();
    void unassignSelected();

    void update() override;  // Observer
};
