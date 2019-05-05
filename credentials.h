#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <QString>

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
