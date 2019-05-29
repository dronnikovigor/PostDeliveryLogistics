#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <iostream>
#include <QString>
#include "ui/manipulator.h"

class Credentials
{
public:
    Credentials(const QString &login, const QString &pass);
    qint8 checkCredentials();

private:
    const QString login;
    const QString pass;
};
#endif // CREDENTIALS_H
