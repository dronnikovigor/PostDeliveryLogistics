#include "adminscreen.h"

Ui::AdminScreen::AdminScreen(QWidget *widget)
{
    QGridLayout *gridLayout = new QGridLayout();
    QVBoxLayout *vertLayout = new QVBoxLayout();
    QPushButton *addCityBtn = new QPushButton("Add new city");
    QPushButton *delCityBtn = new QPushButton("Delete city");
    QPushButton *importCitiesBtn = new QPushButton("Import cities from file");
    QPushButton *exportCitiesBtn = new QPushButton("Export cities to file");
    QPushButton *logoutBtn = new QPushButton("Log out");

    addCityBtn->setFixedHeight(45);
    delCityBtn->setFixedHeight(45);
    importCitiesBtn->setFixedHeight(45);
    exportCitiesBtn->setFixedHeight(45);
    logoutBtn->setFixedHeight(45);

    QFont font = addCityBtn->font();
    font.setPointSize(12);
    addCityBtn->setFont(font);
    delCityBtn->setFont(font);
    importCitiesBtn->setFont(font);
    exportCitiesBtn->setFont(font);
    logoutBtn->setFont(font);

    QImage *logoImg = new QImage(":/images/delivery-512.png");
    QLabel *imgDisplayLabel = new QLabel("");
    imgDisplayLabel->setPixmap(QPixmap::fromImage(*logoImg));
    imgDisplayLabel->adjustSize();

    vertLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertLayout->addWidget(addCityBtn);
    vertLayout->addWidget(delCityBtn);
    vertLayout->addWidget(importCitiesBtn);
    vertLayout->addWidget(exportCitiesBtn);
    vertLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertLayout->addWidget(logoutBtn);
    gridLayout->addLayout(vertLayout, 0, 0, 0, 1);
    gridLayout->addWidget(new GraphWidget(), 0, 1, 1, 1);

    ///TODO: connect btns to func's here
    connect(logoutBtn, SIGNAL(clicked()), this, SIGNAL(logout()));

    widget->setLayout(gridLayout);
}
