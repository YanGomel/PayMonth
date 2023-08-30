#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include <cmath>
#include <QDateTime>

class settingsScreenWidget : public QWidget
{
    Q_OBJECT
public:
    settingsScreenWidget(QWidget *parent = nullptr);
    ~settingsScreenWidget();
    QVBoxLayout *mainLayout = NULL;
    QLabel *labelHeader = NULL;
    QLabel *labelCurrentSalary = NULL;
    QLabel *labelSpace = NULL;
    QLineEdit *editSalary = NULL;
    QPushButton *buttonOK = NULL;
    QPushButton *buttonBack = NULL;
    QDate dateSalary;
    QString dateSalaryString;

signals:
    void signalBackToMenu();
    void signalSetSalary();
private slots:
    void slotTakeSalary();
};

#endif // SETTINGSSCREEN_H
