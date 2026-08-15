#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <QString>

struct Person {
    QString name, ID, address;
    int contact;
    int cash;
};

class BankSystem : public QWidget {
    Q_OBJECT
public:
    explicit BankSystem(QWidget *parent = nullptr);

private slots:
    void checkLogin();
    void showDashboard();
    void createAccount();
    void viewCustomers();
    void searchAccount();
    void updateAccount();
    void transactions();
    void deleteAccount();

private:
    QLineEdit *username, *password;
    QPushButton *loginBtn;
    std::vector<Person> customers;

    void saveData();
    void loadData();
};

#endif // MAINWINDOW_H
