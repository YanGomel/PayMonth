#include <settingsScreen.h>

void settingsScreenWidget::slotTakeSalary(){
    //взяли текст
    QString salary = editSalary->text();
    salary.replace(',','.');
    bool flag = false;
    int count = 0;
    for(int i = 0; i < salary.length(); i++)
    {
        if(salary[i] == '.') flag = true;
        if(flag) count++;
    }
    if(count>3)
    {
        editSalary->setText(tr("Неправильный формат"));
    }
    else
    {

        //Преобразование в число
        float floatSalary = salary.toFloat();
        if(floatSalary <= 0 || std::isinf(floatSalary)) editSalary->setText(tr("Неправильный формат"));
        else
        {
            // Считаем
            QDate currentDate = QDate::currentDate();
            int currentYear = currentDate.year();
            int currentMonth = currentDate.month();
            int currentDay = currentDate.day();

            QDate nextMonthDate(currentYear, currentMonth, currentDay);
            nextMonthDate = nextMonthDate.addMonths(1);
            int daysToNextMonth = currentDate.daysTo(nextMonthDate);

            float floatDaySalary = floatSalary/daysToNextMonth;
            QString formattedDaySalary = QString::number(floatDaySalary, 'f', 2);
            QFile fileDaySalary("DaySalary");
            if(fileDaySalary.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            {
                QTextStream in1(&fileDaySalary);
                in1 << formattedDaySalary;
                fileDaySalary.close();
            }
            emit signalSetSalary();

            QString labelSalary = "Текущая зарплата ";
            labelSalary += salary;
            labelSalary += " BYN";
            labelCurrentSalary->setText(labelSalary);

            //Запись зарплаты в файл
            QFile fileSalary("Salary");
            if(fileSalary.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            {
                QTextStream out(&fileSalary);
                out << salary;
                fileSalary.close();
            }
        }
        dateSalary = QDate::currentDate();
        dateSalaryString = dateSalary.toString("dd.MM.yyyy");
        QFile fileDateSalary("DateSalary");
        if(fileDateSalary.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        { //Стартовая дата
            QTextStream in(&fileDateSalary);
            in << dateSalaryString;
            fileDateSalary.close();
        }
        // Дата вчерашнего дня
        QFile fileDate("YDate");
        if(fileDate.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream input(&fileDate);
            input << dateSalaryString;
            fileDate.close();
        }
    }

}
