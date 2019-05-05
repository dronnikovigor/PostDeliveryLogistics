#include "userscreen.h"

UserScreen::UserScreen(QWidget *widget)
{
    QGridLayout *gridLayout = new QGridLayout();
    fromCityList = new QListWidget();
    toCityList = new QListWidget();
    resultList = new QListWidget();
    fromSelect = new QLineEdit();
    toSelect = new QLineEdit();
    QLabel *fromLabel = new QLabel("From city:");
    QLabel *toLabel = new QLabel("To city:");
    QLabel *selectedLabel = new QLabel("Selected city:");
    QLabel *selectedLabel2 = new QLabel("Selected city:");
    QLabel *resultLabel = new QLabel("Result:");
    QPushButton *logoutBtn = new QPushButton("Log out");
    QPushButton *getDirBtn = new QPushButton("Get directions");
    QPushButton *plotBtn = new QPushButton("Plot graph");

    logoutBtn->setFixedHeight(45);
    getDirBtn->setFixedHeight(45);
    plotBtn->setFixedHeight(45);

    QFont font = fromCityList->font();
    font.setPointSize(12);
    fromCityList->setFont(font);
    toCityList->setFont(font);
    resultList->setFont(font);
    fromSelect->setFont(font);
    toSelect->setFont(font);
    fromLabel->setFont(font);
    toLabel->setFont(font);
    selectedLabel->setFont(font);
    selectedLabel2->setFont(font);
    resultLabel->setFont(font);
    logoutBtn->setFont(font);
    getDirBtn->setFont(font);
    plotBtn->setFont(font);

    gridLayout->addWidget(fromLabel, 0, 0);
    gridLayout->addWidget(fromCityList, 1, 0, 2, 2);
    gridLayout->addWidget(toLabel, 3, 0);
    gridLayout->addWidget(toCityList, 4, 0, 2, 2);
    gridLayout->addWidget(selectedLabel, 0, 3);
    gridLayout->addWidget(selectedLabel2, 3, 3);
    gridLayout->addWidget(fromSelect, 1, 3);
    gridLayout->addWidget(toSelect, 4, 3);
    gridLayout->addWidget(logoutBtn, 6, 0);
    gridLayout->addWidget(getDirBtn, 6, 3);
    gridLayout->addWidget(resultLabel, 0, 4);
    gridLayout->addWidget(resultList, 1, 4, 5, 1);
    gridLayout->addWidget(plotBtn, 6, 4);

    ///TODO: connect btns to func's here
    connect(logoutBtn, SIGNAL(clicked()), this, SIGNAL(logout()));
    connect(fromCityList, &QListWidget::itemChanged, this , &UserScreen::handleFromSelectChanged);
    connect(toCityList, &QListWidget::itemChanged, this , &UserScreen::handleToSelectChanged);

    widget->setLayout(gridLayout);
}

void UserScreen::handleFromSelectChanged(QListWidgetItem *item)
{
    fromSelect->setText(item->text());
}

void UserScreen::handleToSelectChanged(QListWidgetItem *item)
{
    fromSelect->setText(item->text());
}
