#include "mainScreen.h"
#include "settingsScreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainScreenWidget mainScreen;
    settingsScreenWidget settingsScreen;
    mainScreen.show();

    QObject::connect(&mainScreen, &mainScreenWidget::signalOpenSettings, &mainScreen, [&]()
                     {
                         settingsScreen.show();
                         mainScreen.hide();
                     });

    QObject::connect(&settingsScreen, &settingsScreenWidget::signalBackToMenu, &settingsScreen, [&](){
        mainScreen.show();
        settingsScreen.hide();
    });

    QObject::connect(&settingsScreen, &settingsScreenWidget::signalSetSalary, &settingsScreen, [&](){
        QString salary ="<font color='green'>+";
        QString salary1;
        QFile file("DaySalary");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            salary += out.readLine();
            salary1 = out.readLine();
            file.close();
            salary += "</font>";
            mainScreen.labelConsumption->setText(salary);
        }
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            salary1 = out.readLine();
            file.close();
        }
        QFile fileS("Consumption");
        if(fileS.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream out(&fileS);
            out << salary1;
            fileS.close();
        }
    });

    return a.exec();
}

