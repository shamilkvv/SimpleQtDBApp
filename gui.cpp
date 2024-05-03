#include "gui.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPropertyAnimation>

DbGui::DbGui(QWidget *parent)
    : QWidget(parent)
{
    m_dbManager = new DbManager("mydatabase.db");
    QLabel *titleLabel = new QLabel("Database Manager");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333333;");
    QLabel *nameLabel = new QLabel("Name:");
    m_nameEdit = new QLineEdit;
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *removeButton = new QPushButton("Remove");
    QPushButton *printButton = new QPushButton("Print All");
    QPushButton *removeAllButton = new QPushButton("Remove All");
    QPushButton *checkButton = new QPushButton("Check Person");
    m_outputLabel = new QLabel;


    connect(addButton, &QPushButton::clicked, this, &DbGui::addPerson);
    connect(removeButton, &QPushButton::clicked, this, &DbGui::removePerson);
    connect(printButton, &QPushButton::clicked, this, &DbGui::printAll);
    connect(removeAllButton, &QPushButton::clicked, this, &DbGui::removeAll);
    connect(checkButton, &QPushButton::clicked, this, &DbGui::checkPerson);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(titleLabel, 0, 0, 1, 2);
    layout->addWidget(nameLabel, 1, 0);
    layout->addWidget(m_nameEdit, 1, 1);
    layout->addWidget(addButton, 2, 0);
    layout->addWidget(removeButton, 2, 1);
    layout->addWidget(printButton, 3, 0, 1, 2);
    layout->addWidget(removeAllButton, 4, 0, 1, 2);
    layout->addWidget(checkButton, 5, 0, 1, 2);
    layout->addWidget(m_outputLabel, 6, 0, 1, 2);
    setLayout(layout);

    setWindowTitle("Database GUI");
    QString styleSheet = " \
        QWidget { \
            background-color: #f0f0f0; \
    } \
        QPushButton { \
            background-color: #ffffff; \
            font-family: Courier New, sans-serif; \
            font-size: 30px; \
            font-weight: bold; \
            color: #333333; \
            border: 1px solid #cccccc; \
            margin: 0; \
            padding: 10px; \
            min-width: 80px; \
            min-height: 80px; \
    } \
        QPushButton:hover { \
            background-color: #eaeaea; \
    } \
        QPushButton:pressed { \
            background-color: #d9d9d9; \
    } \
        QLineEdit { \
            background-color: #ffffff; \
            color: #333333; \
            font-family: Courier New, sans-serif; \
            font-size: 20px; \
            font-weight: bold; \
            border: 1px solid #cccccc; \
            margin: 0; \
            padding: 10px; \
            min-height: 80px; \
    } \
        QPushButton[text='='] { \
            background-color: #b19cd9; \
            color: #ffffff; \
            border: 1px solid #9278b3; \
    } \
        QPushButton[text='C'] { \
            background-color: #ff867d; \
            color: #ffffff; \
            border: 1px solid #cc4b38; \
    } \
        QPushButton:not([text='=']):not([text='C']) { \
            font-weight: normal; \
    }";

        this->setStyleSheet(styleSheet);


    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollWidget = new QWidget;
    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea, 7, 0, 1, 2);

    nameLabel->setStyleSheet(" \
        font-size: 20px; \
        font-weight: bold; \
        color: #333333; \
    ");




}






DbGui::~DbGui()
{
    delete m_dbManager;
}

void DbGui::addPerson()
{
    if (m_dbManager->addPerson(m_nameEdit->text())) {
        m_outputLabel->setText("Person added successfully");
    } else {
        m_outputLabel->setText("Failed to add person");
    }
}

void DbGui::checkPerson()
{
    if (m_dbManager->personExists(m_nameEdit->text())) {
        m_outputLabel->setText("Person exists");
    } else {
        m_outputLabel->setText("Person does not exist");
    }
}

void DbGui::removePerson()
{
    if (m_dbManager->removePerson(m_nameEdit->text())) {
        m_outputLabel->setText("Person removed successfully");
    } else {
        m_outputLabel->setText("Failed to remove person");
    }
}

void DbGui::printAll()
{

    QLayoutItem* child;
    while ((child = scrollLayout->takeAt(0)) != nullptr)
    {
        if (child->widget())
        {
            delete child->widget();
        }
        delete child;
    }


    QString output;
    QSqlQuery query("SELECT * FROM people");
    int idIndex = query.record().indexOf("id");
    int nameIndex = query.record().indexOf("name");
    while (query.next()) {
        int id = query.value(idIndex).toInt();
        QString name = query.value(nameIndex).toString();
        output += QString::number(id) + ": " + name + "\n";
    }
    QLabel* peopleLabel = new QLabel(output);
    scrollLayout->addWidget(peopleLabel);
}


void DbGui::removeAll()
{
    if (m_dbManager->removeAll(scrollLayout)) {
        m_outputLabel->setText("All persons removed successfully");
    } else {
        m_outputLabel->setText("Failed to remove all persons");
    }
}

