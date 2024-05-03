#ifndef CLASS_H

#define CLASS_H


#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QtSql>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>


class DbManager: public QObject

{

   // Q_OBJECT

public:

    DbManager(const QString& path);

    bool addPerson(const QString&name);

    bool personExists(const QString&name);

    bool removePerson(const QString&name);

    void printAll()const;

   // bool removeAll();
    bool removeAll(QVBoxLayout* scrollLayout);

    ~DbManager();

private:

    QSqlDatabase m_db;

    bool createDatabase();


};


#endif // CLASS_H
