#include "mainScreen.h"

mainScreenWidget::mainScreenWidget(QWidget *parent)
    : QWidget(parent)
{

    // Устанавливаем разметку для основного поля
    mainScreenLayout = new QVBoxLayout();
    setLayout(mainScreenLayout);

    mainScreenLayout->setContentsMargins(10, 100,10,10); //чотступы от границ экрана

    // Текстовое поле расходов
    labelConsumption = new QLabel;


    // просмотр файла с текущим расходом и запись этого числа в окно

    QFile fileCons2("Consumption");
    QString c,c1;
    if(fileCons2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream out(&fileCons2);
        c = out.readLine();
        if(c.toFloat() > 0){ c1 = "<font color='green'>+"; c1 +=c; c1 +="</font>";}
            else{c1 = "<font color='red'>"; c1 += c; c1 += "</font>";}
        fileCons2.close();
    }
    if(c.isEmpty()) labelConsumption->setText("00,00");
    else labelConsumption->setText(c1);
    QFont fontConsumption("Arial", 50);
    labelConsumption->setFont(fontConsumption);
    mainScreenLayout->addWidget(labelConsumption, 0, Qt::AlignCenter);

    // Кнопка ввода расхода
    buttonAddConsumption = new QPushButton(tr("Добавить расход"));
    buttonAddConsumption->setMinimumHeight(75);
    mainScreenLayout->addWidget(buttonAddConsumption, 1, Qt::AlignBottom);
    connect(buttonAddConsumption, &QPushButton::clicked, this, &mainScreenWidget::slotAddCons);

    // Кнопка настройки
    buttonSettings = new QPushButton(tr("Настройки"));
    buttonSettings->setMinimumHeight(75);
    mainScreenLayout->addWidget(buttonSettings, 0, Qt::AlignBottom);

    connect(buttonSettings, &QPushButton::clicked, this, &mainScreenWidget::signalOpenSettings);
    QDate currentDate = QDate::currentDate();
    QString curDateStr = currentDate.toString("dd.MM.yyyy");
    QDate lastDate;
    QString strLastDate;
    QFile fileDate("YDate");
    QString strDaySalary;
    QString strCurCons;
    float curCons;
    float daySalary;

    //проверка на конец месяца
    QFile fileDateSalary("DateSalary");
    QString dateSalary;
    if(fileDateSalary.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream out(&fileDateSalary);
        dateSalary = out.readLine();
        fileDateSalary.close();
    }
    QDate dateSalaryDate = QDate::fromString(dateSalary, "dd.MM.yyyy");
    int daysto = dateSalaryDate.addMonths(1).daysTo(currentDate);
    qDebug()<<"DAy::"<<daysto;

    bool flagLabelConsumption = true; // чтобы после конца месяца текст не втавлялся.

    if(daysto >= 1)
    {
        // начало куска кода
        buttonAddConsumption->setDisabled(true);
        qDebug()<<"SFff";
        labelConsumption->setText("Новый месяц, зайдите в настройки");
        QFont fontConsumption1("Arial", 12);
        labelConsumption->setFont(fontConsumption1);
        flagLabelConsumption = false;
        //конец куска кода
    }

    if(fileDate.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream out(&fileDate);
        strLastDate = out.readLine();
        lastDate = QDate::fromString(strLastDate, "dd.MM.yyyy");
    }

    int days=lastDate.daysTo(currentDate);
     qDebug()<<days;
    qDebug()<<"Date: "<<lastDate;
     qDebug()<<"DateToday: "<<currentDate;

    if(days!=0)
    {
        QFile fileSalary("DaySalary");
        if(fileSalary.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream out(&fileSalary);
            strDaySalary = out.readLine();
            fileSalary.close();
        }
        daySalary = strDaySalary.toFloat();
        QFile fileCons("Consumption");
        if(fileCons.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream out(&fileCons);
            strCurCons = out.readLine();
            fileCons.close();
        }
        curCons = strCurCons.toFloat();
        float sum = (curCons + (days * daySalary));
        QString strSum;
        if(sum > 0){ strSum +="<font color='green'>+"; strSum += QString::number(sum); strSum += "</font>"; }
        else {strSum += "<font color='red'>"; strSum+=QString::number(sum); strSum += "</font>"; }
        if(flagLabelConsumption) labelConsumption->setText(strSum);

        QFile fileCons1("Consumption");
        if(fileCons1.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&fileCons1);
            in << QString::number(sum);
            fileCons1.close();
        }

        QFile fileYDate("YDate");
        if(fileYDate.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&fileYDate);
            in << curDateStr;
            fileYDate.close();
        }
    }

}


mainScreenWidget::~mainScreenWidget()
{
}
