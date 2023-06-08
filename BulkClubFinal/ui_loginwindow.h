/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLabel *label;
    QLineEdit *userNameBox;
    QLineEdit *passWordBox;
    QPushButton *loginButton;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(584, 485);
        label = new QLabel(LoginWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 40, 371, 91));
        userNameBox = new QLineEdit(LoginWindow);
        userNameBox->setObjectName("userNameBox");
        userNameBox->setGeometry(QRect(270, 150, 141, 41));
        passWordBox = new QLineEdit(LoginWindow);
        passWordBox->setObjectName("passWordBox");
        passWordBox->setGeometry(QRect(270, 210, 141, 41));
        passWordBox->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(200, 310, 241, 81));
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 140, 91, 61));
        label_3 = new QLabel(LoginWindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 200, 91, 61));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "Welcome to the Bulk Club. Enter your login info below.", nullptr));
        userNameBox->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        passWordBox->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "LOGIN", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "USERNAME", nullptr));
        label_3->setText(QCoreApplication::translate("LoginWindow", "PASSWORD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
