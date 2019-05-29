#include "credentials.h"

Credentials::Credentials(const QString &login, const QString &pass) :
    login(login), pass(pass)
{
}

qint8 Credentials::checkCredentials() {
    qint8 grants = -1;
    if (login == "admin" && pass == "admin") {
        grants = 1;
    }
    if (login == "user" && pass == "pass") {
        grants = 0;
    }
    std::cout << Manip::Manipulator::getInstance().grants(grants);
    return grants;
}
