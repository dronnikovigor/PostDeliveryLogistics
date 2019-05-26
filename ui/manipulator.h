#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <QWidget>

#include "ui/screen.h"
#include "ui/adminscreen.h"
#include "ui/userscreen.h"
#include "ui/loginscreen.h"

namespace Manip {

class Manipulator
{
public:
    Manipulator();
    QWidget *buildWidget(QWidget *widget);
    Ui::Screen *showScreen(qint8 adminRights, QWidget *widget);
    Ui::Screen *showScreen(QWidget *widget);
};
}
#endif // MANIPULATOR_H
