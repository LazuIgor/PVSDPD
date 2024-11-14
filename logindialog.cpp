#include "logindialog.h"
#include "QFormLayout"
#include "QPushButton"
#include "QMessageBox"
//#include "realiselogger.cpp"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    QFormLayout *formLayout = new QFormLayout(this);

    nameLineEdit = new QLineEdit(this);
    formLayout->addRow("Имя:", nameLineEdit);

    surnameLineEdit = new QLineEdit(this);
    formLayout->addRow("Фамлия:", surnameLineEdit);

    positionLineEdit = new QLineEdit(this);
    formLayout->addRow("Должность:", positionLineEdit);

    QPushButton *loginButton = new QPushButton("Войти", this);
    formLayout->addRow(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginButtonClicked);
}

void LoginDialog::onLoginButtonClicked() {
    if (nameLineEdit->text().isEmpty() || surnameLineEdit->text().isEmpty() || positionLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
    } else {
        accept();
    }
}

