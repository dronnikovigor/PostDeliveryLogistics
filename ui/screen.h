#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>
#include <QWidget>
#include <singleton.h>

namespace Ui {
class Screen : public QObject
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);

};
}
#endif // SCREEN_H
