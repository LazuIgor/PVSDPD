#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "QDialog"
#include "QLineEdit"


class LoginDialog : public QDialog
{
    Q_OBJECT;

public:
    LoginDialog(QWidget *parent = nullptr);

    QString getName() const { return nameLineEdit->text(); }
    QString getSurname() const { return surnameLineEdit->text(); }
    QString getPosition() const { return positionLineEdit->text(); }

private slots:
    void onLoginButtonClicked();

private:
    QLineEdit *nameLineEdit;
    QLineEdit *surnameLineEdit;
    QLineEdit *positionLineEdit;
};

#endif // LOGINDIALOG_H
