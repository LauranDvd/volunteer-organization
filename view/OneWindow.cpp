#include "OneWindow.h"

OneWindow::OneWindow(Controller* controller, QWidget* parent) :
	QWidget{ parent }, controller{ controller } {
	ui.setupUi(this);
}

void OneWindow::addTabAtBeginning(QWidget* widget, string name) {
	ui.tabWidget->insertTab(0, widget, QString::fromStdString(name));
	ui.tabWidget->setCurrentIndex(0);
}
