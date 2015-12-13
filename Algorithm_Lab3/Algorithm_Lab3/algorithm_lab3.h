#ifndef ALGORITHM_LAB3_H
#define ALGORITHM_LAB3_H

#include <QtWidgets/QMainWindow>
#include "ui_algorithm_lab3.h"

class Algorithm_Lab3 : public QMainWindow
{
	Q_OBJECT

public:
	Algorithm_Lab3(QWidget *parent = 0);
	~Algorithm_Lab3();

private:
	Ui::Algorithm_Lab3Class ui;
};

#endif // ALGORITHM_LAB3_H
