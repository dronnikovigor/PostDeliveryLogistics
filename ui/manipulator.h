#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <QWidget>
#include <iostream>
#include <iomanip>

#include "ui/screen.h"
#include "ui/adminscreen.h"
#include "ui/userscreen.h"
#include "ui/loginscreen.h"
#include "singleton.h"

namespace Manip {

template<class T>
class OMANIP {
    T i;
    std::ostream& (*f) (std::ostream&,T);
public:
    OMANIP(std::ostream& (*ff) (std::ostream&,T), T ii)
        : f(ff), i(ii) { }

    friend std::ostream& operator<<(std::ostream& os, OMANIP m)
    { return (*m.f)(os,m.i); }
};

class Manipulator : public Singleton<Manipulator>
{

protected:
    friend std::ostream &writeCredentials(std::ostream &stream, int grants);
public:
    QWidget *buildWidget(QWidget *widget);
    Ui::Screen *showScreen(qint8 adminRights, QWidget *widget);
    Ui::Screen *showScreen(QWidget *widget);
    Manip::OMANIP<int> grants(int length);

private:
    friend Manip::OMANIP<int>;
    friend class Singleton<Manipulator>;
    Manipulator();
};

}
#endif // MANIPULATOR_H
