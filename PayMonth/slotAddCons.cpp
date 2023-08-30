#include "mainScreen.h"

void mainScreenWidget::slotAddCons()
{
    editConsumption = new QLineEdit();
    editConsumption->setPlaceholderText(tr("Введите трату"));
    editConsumption->setText("-");
    editConsumption->setMinimumHeight(75);
    editConsumption->setStyleSheet("font-size: 40px;");
    labelConsumption->hide();
    mainScreenLayout->replaceWidget(labelConsumption, editConsumption);
    connect(editConsumption, &QLineEdit::textChanged, this, [&](const QString& text) {
        buttonAdd->setEnabled(!text.isEmpty());
    });

    buttonAdd = new QPushButton();
    buttonAdd->setText(tr("Ввод"));
    buttonAdd->setMinimumHeight(75);
    buttonAddConsumption->hide();
    buttonAdd->setDisabled(true);
    mainScreenLayout->replaceWidget(buttonAddConsumption, buttonAdd);


    connect(buttonAdd, &QPushButton::clicked, this, [&]{
        QString cons = editConsumption->text();
        cons.replace(',','.');
        bool flag = false;
        int count = 0;
        for(int i = 0; i < cons.length(); i++)
        {
            if(cons[i] == '.') flag = true;
            if(flag) count++;
        }
        if(count>3)
        {
            editConsumption->setText(tr("Ошибка"));
        }
        else
        {

            //Преобразование в число
            float floatCons = cons.toFloat();
            if(std::isinf(floatCons)) editConsumption->setText(tr("Ошибка"));
            else
            {
                QString consFile;
                QFile fileCons("Consumption");
                if(fileCons.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QTextStream out(&fileCons);
                    consFile = out.readLine();
                    fileCons.close();
                }
                float floatConsFile = consFile.toFloat();
                float sum = floatCons + floatConsFile;
                QString strSum1 = QString::number(sum); qDebug()<<"Сумма первая = "<<strSum1;
                QString strSum;

                bool flag1 = true;
                bool flag2 = false;
                int count1=0;
                for(int i = 0; i < strSum1.length(); i++)
                {
                    if(flag1 == true){
                        strSum += strSum1[i];
                        if(strSum1[i] == '.') flag2 = true;
                        if(flag2) count1++;
                        if(count1 > 2) flag1=false;
                    }
                }

                QString strLabel;

                if(strSum.toFloat() > 0){ strLabel = "<font color='green'>+"; strLabel += strSum; strLabel +="</font>";}
                else{strLabel = "<font color='red'>"; strLabel += strSum; strLabel += "</font>";}
                labelConsumption->setText(strLabel);

                if(fileCons.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
                {
                    QTextStream in(&fileCons);
                    in << strSum;
                    fileCons.close();
                }
            }
            editConsumption->hide();
            labelConsumption->show();
            mainScreenLayout->replaceWidget(editConsumption,labelConsumption);
            buttonAdd->hide();
            buttonAddConsumption->show();
            mainScreenLayout->replaceWidget(buttonAdd, buttonAddConsumption);
            buttonCancel->hide();
            buttonSettings->show();
            mainScreenLayout->replaceWidget(buttonCancel ,buttonSettings);
        }
    });

    buttonCancel = new QPushButton();
    buttonCancel->setText(tr("Отмена"));
    buttonCancel->setMinimumHeight(75);
    buttonSettings->hide();
    mainScreenLayout->replaceWidget(buttonSettings, buttonCancel);

    connect(buttonCancel, &QPushButton::clicked, this, [&]{
        editConsumption->hide();
        labelConsumption->show();
        mainScreenLayout->replaceWidget(editConsumption,labelConsumption);
        buttonAdd->hide();
        buttonAddConsumption->show();
        mainScreenLayout->replaceWidget(buttonAdd, buttonAddConsumption);
        buttonCancel->hide();
        buttonSettings->show();
        mainScreenLayout->replaceWidget(buttonCancel ,buttonSettings);
    });
}
