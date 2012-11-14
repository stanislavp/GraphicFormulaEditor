#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	w.Show();

	w.__try__();
	w.__try2__();

	return a.exec();
}
