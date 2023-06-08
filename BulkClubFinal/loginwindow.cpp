#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"



LoginWindow::LoginWindow(QWidget* parent) : QDialog(parent), ui2(new Ui::LoginWindow)
{
    ui2->setupUi(this);

    // Set up valid accounts
    Account adminAccount;
    adminAccount.username = "theadmin";
    adminAccount.password = "password";
    adminAccount.role = "admin";

    Account managerAccount;
    managerAccount.username = "themanager";
    managerAccount.password = "password";
    managerAccount.role = "manager";

    // Store the valid accounts in a QMap for easy lookup
    validAccounts.insert(adminAccount.username, adminAccount);
    validAccounts.insert(managerAccount.username, managerAccount);

    connect(ui2->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui2;
}

void LoginWindow::onLoginClicked()
{
    QString enteredUsername = ui2->userNameBox->text();
    QString enteredPassword = ui2->passWordBox->text();

    // Look up the entered account in the validAccounts QMap
    if (validAccounts.contains(enteredUsername))
    {
        account = validAccounts.value(enteredUsername);
        if (account.password == enteredPassword)
        {

            MainWindow* myWindow = new MainWindow(account.role);
            hide();
            myWindow->show();

        } else {

            QMessageBox::warning(this, "Login Failed", "Invalid password.");

        }

    } else {


    QMessageBox::warning(this, "Login Failed", "Invalid username or password.");

    }

    emit loginClicked();  // Emit the loginClicked signal with the role



}
