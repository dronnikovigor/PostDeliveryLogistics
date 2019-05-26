#include "userscreen.h"

Ui::UserScreen::UserScreen(QWidget *widget)
    : Ui::Screen(widget)
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

    logoutBtn->setFixedHeight(45);
    getDirBtn->setFixedHeight(45);

    fromSelect->setReadOnly(true);
    toSelect->setReadOnly(true);

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

    std::list<std::string> stdListString = Serialize<std::string>::getInstance().getVertices();
    for (std::string it: stdListString) {
        fromCityList->addItem(QString::fromStdString(it));
        toCityList->addItem(QString::fromStdString(it));
    }

    graph.clear();
    std::list<std::string> vertices = Serialize<std::string>::getInstance().getVertices();
    std::vector<std::pair<std::string, std::string>> edges = Serialize<std::string>::getInstance().getEdges();
    for (std::string it: vertices) {
        graph.insert_vertex(it);
    }
    for (std::pair<std::string, std::string> it: edges) {
        graph.insert_vertex_pair(it.first, it.second);
    }
    connect(logoutBtn, SIGNAL(clicked()), this, SIGNAL(logout()));
    connect(getDirBtn, SIGNAL(clicked()), this, SLOT(getDirections()));
    connect(fromCityList, &QListWidget::itemClicked, this , &UserScreen::handleFromSelectChanged);
    connect(toCityList, &QListWidget::itemClicked, this , &UserScreen::handleToSelectChanged);

    widget->setLayout(gridLayout);
}

void Ui::UserScreen::getDirections()
{
    resultList->clear();
    if (!fromSelect->text().isEmpty() && !fromSelect->text().isEmpty()) {
        std::list<std::string> result = graph.search_dist(fromSelect->text().toStdString(), toSelect->text().toStdString());
        typename std::list<std::string>::iterator print_it = result.begin();
        for(; print_it != result.end(); ++print_it) {
            resultList->addItem(QString::fromStdString(*print_it));
        }
    } else {
        resultList->addItem("Choose cities");
    }
}

void Ui::UserScreen::handleFromSelectChanged(QListWidgetItem *item)
{
    fromSelect->setText(item->text());
}

void Ui::UserScreen::handleToSelectChanged(QListWidgetItem *item)
{
    toSelect->setText(item->text());
}
