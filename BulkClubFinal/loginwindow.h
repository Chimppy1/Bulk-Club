#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>
#include <QMap>

namespace Ui
{
class LoginWindow;
}



struct Account {
    QString username;
    QString password;
    QString role;
};

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

    QString getRole();

private:
    Ui::LoginWindow* ui2;

    QString validUsername;

    QString validPassword;

    Account account;


    QMap<QString, Account> validAccounts;  // Declaration of validAccounts


private slots:

    void onLoginClicked();

signals:

    void loginClicked();
};

#endif // LOGINWINDOW_H
