#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QDate>
#include <QFile>
#include <QLineEdit>
#include <cmath>
#include <QPainter>

class mainScreenWidget : public QWidget
{
    Q_OBJECT

public:
    mainScreenWidget(QWidget *parent = nullptr);
    ~mainScreenWidget();
    QVBoxLayout *mainScreenLayout = NULL;
    QPushButton *buttonSettings = NULL;
    QLabel *labelConsumption = NULL;
    QPushButton *buttonAddConsumption = NULL;
    QLabel *labelSpace1 = NULL;
    QLabel *labelSpace2 = NULL;
    //окно ввода расхода
    QLineEdit *editConsumption = NULL;
    QPushButton *buttonCancel = NULL;
    QPushButton *buttonAdd = NULL;

private slots:
    void slotAddCons();

signals:
    void signalOpenSettings();

};
#endif // MAINSCREEN_H
