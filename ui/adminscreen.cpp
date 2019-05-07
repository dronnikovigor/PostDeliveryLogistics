#include "adminscreen.h"

Ui::AdminScreen::AdminScreen(QWidget *widget)
{
    graphWidget = new GraphWidget();

    QGridLayout *gridLayout = new QGridLayout();
    QVBoxLayout *vertLayout = new QVBoxLayout();
    QPushButton *addEdgeBtn = new QPushButton("Add new edge");
    QPushButton *delCityBtn = new QPushButton("Delete city");
    QPushButton *delEdgeBtn = new QPushButton("Delete edge");
    QPushButton *importCitiesBtn = new QPushButton("Import cities from file");
    QPushButton *exportCitiesBtn = new QPushButton("Export cities to file");
    QPushButton *logoutBtn = new QPushButton("Log out");

    addEdgeBtn->setFixedHeight(45);
    delCityBtn->setFixedHeight(45);
    delEdgeBtn->setFixedHeight(45);
    importCitiesBtn->setFixedHeight(45);
    exportCitiesBtn->setFixedHeight(45);
    logoutBtn->setFixedHeight(45);

    QFont font = addEdgeBtn->font();
    font.setPointSize(12);
    addEdgeBtn->setFont(font);
    delCityBtn->setFont(font);
    delEdgeBtn->setFont(font);
    importCitiesBtn->setFont(font);
    exportCitiesBtn->setFont(font);
    logoutBtn->setFont(font);

    vertLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertLayout->addWidget(addEdgeBtn);
    vertLayout->addWidget(delCityBtn);
    vertLayout->addWidget(delEdgeBtn);
    vertLayout->addWidget(importCitiesBtn);
    vertLayout->addWidget(exportCitiesBtn);
    vertLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertLayout->addWidget(logoutBtn);
    gridLayout->addLayout(vertLayout, 0, 0, 0, 1);
    gridLayout->addWidget(graphWidget, 0, 1, 1, 1);

    ///TODO: connect btns to func's here
    connect(addEdgeBtn, SIGNAL(clicked()), this, SLOT(addNewEdge()));
    connect(delCityBtn, SIGNAL(clicked()), this, SLOT(deleteVertex()));
    connect(delEdgeBtn, SIGNAL(clicked()), this, SLOT(deleteEdge()));
    connect(importCitiesBtn, SIGNAL(clicked()), graphWidget, SLOT(importFromFileAndDraw()));
    connect(exportCitiesBtn, SIGNAL(clicked()), graphWidget, SLOT(exportToFile()));
    connect(logoutBtn, SIGNAL(clicked()), this, SIGNAL(logout()));

    widget->setLayout(gridLayout);
}

void Ui::AdminScreen::addNewEdge()
{
    edgeWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *fromLabel = new QLabel("From city:");
    QLabel *toLabel = new QLabel("To city:");
    QListWidget *fromCityList = new QListWidget();
    QListWidget *toCityList = new QListWidget();
    QPushButton *selectBtn = new QPushButton("Add direction");
    selectBtn->setFixedHeight(45);

    QFont font = fromLabel->font();
    font.setPointSize(12);
    fromLabel->setFont(font);
    toLabel->setFont(font);
    fromCityList->setFont(font);
    toCityList->setFont(font);
    selectBtn->setFont(font);

    std::list<int> stdListInt = graphWidget->getVertices();
    for (int it: stdListInt) {
        fromCityList->addItem(QString::number(it));
        toCityList->addItem(QString::number(it));
    }

    gridLayout->addWidget(fromLabel, 0, 0);
    gridLayout->addWidget(fromCityList, 1, 0, 2, 2);
    gridLayout->addWidget(toLabel, 0, 2);
    gridLayout->addWidget(toCityList, 1, 2, 2, 2);
    gridLayout->addWidget(selectBtn, 4, 1, 2, 2);

    edgeWidget->setLayout(gridLayout);
    edgeWidget->show();

    connect(fromCityList, &QListWidget::itemClicked, this , &AdminScreen::handleFromSelectChanged);
    connect(toCityList, &QListWidget::itemClicked, this , &AdminScreen::handleToSelectChanged);
    connect(selectBtn, SIGNAL(clicked()), this, SLOT(addEdgesToGraph()));
}

void Ui::AdminScreen::deleteEdge()
{
    edgeWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *fromLabel = new QLabel("From city:");
    QLabel *toLabel = new QLabel("To city:");
    QListWidget *fromCityList = new QListWidget();
    QListWidget *toCityList = new QListWidget();
    QPushButton *selectBtn = new QPushButton("Delete direction");
    selectBtn->setFixedHeight(45);

    QFont font = fromLabel->font();
    font.setPointSize(12);
    fromLabel->setFont(font);
    toLabel->setFont(font);
    fromCityList->setFont(font);
    toCityList->setFont(font);
    selectBtn->setFont(font);

    std::list<int> stdListInt = graphWidget->getVertices();
    for (int it: stdListInt) {
        fromCityList->addItem(QString::number(it));
        toCityList->addItem(QString::number(it));
    }

    gridLayout->addWidget(fromLabel, 0, 0);
    gridLayout->addWidget(fromCityList, 1, 0, 2, 2);
    gridLayout->addWidget(toLabel, 0, 2);
    gridLayout->addWidget(toCityList, 1, 2, 2, 2);
    gridLayout->addWidget(selectBtn, 4, 1, 2, 2);

    edgeWidget->setLayout(gridLayout);
    edgeWidget->show();

    connect(fromCityList, &QListWidget::itemClicked, this , &AdminScreen::handleFromSelectChanged);
    connect(toCityList, &QListWidget::itemClicked, this , &AdminScreen::handleToSelectChanged);
    connect(selectBtn, SIGNAL(clicked()), this, SLOT(delEdgeFromGraph()));
}

void Ui::AdminScreen::deleteVertex()
{
    edgeWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *fromLabel = new QLabel("Vertex:");
    QListWidget *vertexList = new QListWidget();
    QPushButton *selectBtn = new QPushButton("Delete vertex");
    selectBtn->setFixedHeight(45);

    QFont font = fromLabel->font();
    font.setPointSize(12);
    fromLabel->setFont(font);
    vertexList->setFont(font);
    selectBtn->setFont(font);

    std::list<int> stdListInt = graphWidget->getVertices();
    for (int it: stdListInt) {
        vertexList->addItem(QString::number(it));
    }

    gridLayout->addWidget(fromLabel, 0, 0);
    gridLayout->addWidget(vertexList, 1, 0, 2, 2);
    gridLayout->addWidget(selectBtn, 4, 0, 2, 2);

    edgeWidget->setLayout(gridLayout);
    edgeWidget->show();

    connect(vertexList, &QListWidget::itemClicked, this , &AdminScreen::handleVertexSelectChanged);
    connect(selectBtn, SIGNAL(clicked()), this, SLOT(delVertexFromGraph()));
}

void Ui::AdminScreen::handleFromSelectChanged(QListWidgetItem *item)
{
    fromCity = item->text();
}

void Ui::AdminScreen::handleToSelectChanged(QListWidgetItem *item)
{
    toCity = item->text();
}

void Ui::AdminScreen::handleVertexSelectChanged(QListWidgetItem *item)
{
    vertex = item->text();
}

void Ui::AdminScreen::addEdgesToGraph()
{
    std::cout<<"addEdgesToGraph()";
    if (fromCity != "" && toCity != "" && fromCity != toCity){
        std::cout<<"addEdgesToGraph()";
        graphWidget->addNewEdge(fromCity, toCity);
        edgeWidget->close();
        edgeWidget->deleteLater();
    }
}

void Ui::AdminScreen::delEdgeFromGraph()
{
    if (fromCity != "" && toCity != "" && fromCity != toCity){
        graphWidget->deleteEdge(fromCity, toCity);
        edgeWidget->close();
        edgeWidget->deleteLater();
    }
}

void Ui::AdminScreen::delVertexFromGraph()
{
    if (vertex != ""){
        graphWidget->deleteVertex(vertex);
        edgeWidget->close();
        edgeWidget->deleteLater();
    }
}
