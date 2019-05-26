#include "manipulator.h"

Manip::Manipulator::Manipulator()
{

}

Ui::Screen *Manip::Manipulator::showScreen(qint8 adminRights, QWidget *widget) {
    switch (adminRights) {
    case 0: {
        return new Ui::UserScreen(widget);
    }
    case 1: {
        return new Ui::AdminScreen(widget);
    }
    case 2: {
        return new Ui::LoginScreen(widget);
    }
    }
    return nullptr;
}

Ui::Screen *Manip::Manipulator::showScreen(QWidget *widget) {
    return Manip::Manipulator::showScreen(qint8(2),widget);
}

QWidget *Manip::Manipulator::buildWidget(QWidget *widget){
    if (widget != nullptr) {
        delete widget;
        widget = nullptr;
    }
    return new QWidget();
}
