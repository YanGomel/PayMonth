#include "settingsScreen.h"

settingsScreenWidget::settingsScreenWidget(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    labelHeader = new QLabel(tr("Изменение зарплаты / сброс даты"));
    mainLayout->addWidget(labelHeader, 0, Qt::AlignCenter);

    labelCurrentSalary = new QLabel;
    QString labelSalary;
    QFile fileSalary("Salary");
    if(fileSalary.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&fileSalary);
        labelSalary = in.readLine();
        fileSalary.close();
    }
    QString labelSalaryText = "Текущая зарплата: ";
    labelSalaryText += labelSalary;
    labelSalaryText += " BYN";
    labelCurrentSalary->setText(labelSalaryText);
    labelCurrentSalary->setMinimumHeight(100);
    mainLayout->addWidget(labelCurrentSalary, 0, Qt::AlignCenter);

    editSalary = new QLineEdit();
    editSalary->setMinimumHeight(35);
    editSalary->setPlaceholderText(tr("Ваша зарплата"));
    mainLayout->addWidget(editSalary, 0);


    buttonOK = new QPushButton(tr("Ввод"));
    buttonOK->setDisabled(true);
    buttonOK->setMinimumHeight(75);
    mainLayout->addWidget(buttonOK, 1, Qt::AlignBottom);

    buttonBack = new QPushButton(tr("Назад"));
    buttonBack->setMinimumHeight(75);
    mainLayout->addWidget(buttonBack, 0, Qt::AlignBottom);

    //кнопка в меню
    connect(buttonBack, &QPushButton::clicked, this, &settingsScreenWidget::signalBackToMenu);

    //активация кнопки при введении текста
    connect(editSalary, &QLineEdit::textChanged, this, [&](const QString& text) {
        buttonOK->setEnabled(!text.isEmpty());
    });

    //кнопка ввода, оценка правильности текста и приём его
    connect(buttonOK, &QPushButton::clicked, this, &settingsScreenWidget::slotTakeSalary);

}

settingsScreenWidget::~settingsScreenWidget()
{

}

