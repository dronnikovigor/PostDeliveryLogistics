#include "credentials.h"

Credentials::Credentials(const QString &login, const QString &pass) :
    login(login), pass(pass)
{
}

qint8 Credentials::checkCredentials() {
    if (login == "admin" && pass == "admin")
        return 1;
    if (login == "user" && pass == "pass")
        return 0;
    return -1;
}
