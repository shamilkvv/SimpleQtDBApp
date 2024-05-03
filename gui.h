#ifndef DBGUI_H
#define DBGUI_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "dbmanager.h"

class DbGui : public QWidget
{
    Q_OBJECT

public:
    DbGui(QWidget *parent = nullptr);
    ~DbGui();

private slots:
    void addPerson();
    void removePerson();
    void printAll();
    void removeAll();
    void checkPerson();

private:
    DbManager *m_dbManager;
    QLineEdit *m_nameEdit;
    QLabel *m_outputLabel;
    QVBoxLayout *scrollLayout;
};

#endif // DBGUI_H
