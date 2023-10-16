#pragma once
#include <QtWidgets/QMainWindow>
#include "Observer.h"
#include "ui_OneWindow.h"
#include "Controller.h"

class OneWindow : public QWidget
{
    Q_OBJECT

public:
    OneWindow(Controller* controller, QWidget* parent = nullptr);
    ~OneWindow() {};
    void addTabAtBeginning(QWidget* widget, string name);

private:
    Ui::OneWindow ui;
    Controller* controller;
};
