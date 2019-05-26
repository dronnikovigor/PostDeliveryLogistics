#include "loginscreen.h"

Ui::LoginScreen::LoginScreen(QWidget *widget)
    : Ui::Screen(widget)
{
    QGridLayout *gridLayout = new QGridLayout();
    QVBoxLayout *vertLayout = new QVBoxLayout();
    loginEdit = new QTextEdit("Login");
    passEdit = new QTextEdit("Password");
    QPushButton *loginBtn = new QPushButton("Log In");

    loginEdit->setFixedHeight(35);
    passEdit->setFixedHeight(35);
    loginBtn->setFixedHeight(45);

    QFont font = loginBtn->font();
    font.setPointSize(12);
    loginEdit->setFont(font);
    passEdit->setFont(font);
    loginBtn->setFont(font);

    QImage *logoImg = new QImage(":/images/delivery-512.png");
    QLabel *imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(*logoImg));
    imgDisplayLabel->adjustSize();

    vertLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertLayout->addWidget(loginEdit);
    vertLayout->addWidget(passEdit);
    vertLayout->addWidget(loginBtn);
    vertLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    gridLayout->addLayout(vertLayout, 0, 0, 0, 1);
    gridLayout->addWidget(imgDisplayLabel, 0, 1, 1, 1);

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(checkCredentials()));

    widget->setLayout(gridLayout);
}

void Ui::LoginScreen::checkCredentials()
{
    emit checkCredentialsSignal(loginEdit->toPlainText(), passEdit->toPlainText());
}
