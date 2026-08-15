#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextStream>
#include <QFile>

BankSystem::BankSystem(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Secure Smart Banking System");
    setFixedSize(400, 300);
    loadData();

    // Login Layout
    QLabel *title = new QLabel("Login");
    title->setAlignment(Qt::AlignCenter);
    QLabel *userLabel = new QLabel("Username:");
    QLabel *passLabel = new QLabel("Password:");
    username = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    loginBtn = new QPushButton("Login");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(userLabel);
    layout->addWidget(username);
    layout->addWidget(passLabel);
    layout->addWidget(password);
    layout->addWidget(loginBtn);
    setLayout(layout);

    connect(loginBtn, &QPushButton::clicked, this, &BankSystem::checkLogin);
}

// ---------------- Slots ----------------
void BankSystem::checkLogin() {
    if(username->text() == "admin" && password->text() == "12345") {
        showDashboard();
    } else {
        QMessageBox::critical(this, "Error", "Invalid Credentials!");
    }
}

void BankSystem::showDashboard() {
    QLayout *old = layout();
    if(old) delete old;

    QWidget *dashWidget = new QWidget(this);
    QVBoxLayout *dashLayout = new QVBoxLayout(dashWidget);

    QLabel *dashTitle = new QLabel("Bank Dashboard");
    dashTitle->setAlignment(Qt::AlignCenter);
    dashTitle->setStyleSheet("font-size:18px; font-weight:bold;");

    QPushButton *createBtn = new QPushButton("Create Account");
    QPushButton *viewBtn = new QPushButton("View Customers");
    QPushButton *searchBtn = new QPushButton("Search Account");
    QPushButton *updateBtn = new QPushButton("Update Account");
    QPushButton *transactionBtn = new QPushButton("Transactions");
    QPushButton *deleteBtn = new QPushButton("Delete Account");

    dashLayout->addWidget(dashTitle);
    dashLayout->addWidget(createBtn);
    dashLayout->addWidget(viewBtn);
    dashLayout->addWidget(searchBtn);
    dashLayout->addWidget(updateBtn);
    dashLayout->addWidget(transactionBtn);
    dashLayout->addWidget(deleteBtn);

    setLayout(dashLayout);

    connect(createBtn, &QPushButton::clicked, this, &BankSystem::createAccount);
    connect(viewBtn, &QPushButton::clicked, this, &BankSystem::viewCustomers);
    connect(searchBtn, &QPushButton::clicked, this, &BankSystem::searchAccount);
    connect(updateBtn, &QPushButton::clicked, this, &BankSystem::updateAccount);
    connect(transactionBtn, &QPushButton::clicked, this, &BankSystem::transactions);
    connect(deleteBtn, &QPushButton::clicked, this, &BankSystem::deleteAccount);
}

// ---------------- Account Functions ----------------
void BankSystem::createAccount() {
    Person p;
    bool ok;
    p.name = QInputDialog::getText(this, "Create Account", "Name:", QLineEdit::Normal, "", &ok); if(!ok) return;
    p.ID = QInputDialog::getText(this, "Create Account", "ID:", QLineEdit::Normal, "", &ok); if(!ok) return;
    p.address = QInputDialog::getText(this, "Create Account", "Address:", QLineEdit::Normal, "", &ok); if(!ok) return;
    p.contact = QInputDialog::getInt(this, "Create Account", "Contact:", 0, 0, 999999999, 1, &ok); if(!ok) return;
    p.cash = QInputDialog::getInt(this, "Create Account", "Initial Cash:", 0, 0, 10000000, 1, &ok); if(!ok) return;

    customers.push_back(p);
    saveData();
    QMessageBox::information(this, "Success", "Account Created Successfully");
}

void BankSystem::viewCustomers() {
    QDialog dialog(this);
    dialog.setWindowTitle("Customer List");
    QVBoxLayout layout;
    QTableWidget table(customers.size(), 5);
    table.setHorizontalHeaderLabels({"Name", "ID", "Address", "Contact", "Cash"});
    table.horizontalHeader()->setStretchLastSection(true);
    for(int i=0;i<customers.size();i++){
        table.setItem(i,0,new QTableWidgetItem(customers[i].name));
        table.setItem(i,1,new QTableWidgetItem(customers[i].ID));
        table.setItem(i,2,new QTableWidgetItem(customers[i].address));
        table.setItem(i,3,new QTableWidgetItem(QString::number(customers[i].contact)));
        table.setItem(i,4,new QTableWidgetItem(QString::number(customers[i].cash)));
    }
    layout.addWidget(&table);
    dialog.setLayout(&layout);
    dialog.exec();
}

void BankSystem::searchAccount() {
    bool ok;
    QString searchID = QInputDialog::getText(this,"Search Account","Enter ID:",QLineEdit::Normal,"",&ok);
    if(!ok) return;
    for(auto &c : customers){
        if(c.ID == searchID){
            QMessageBox::information(this,"Account Found",
                                     "Name: " + c.name + "\nID: " + c.ID + "\nAddress: " + c.address +
                                         "\nContact: " + QString::number(c.contact) + "\nCash: " + QString::number(c.cash));
            return;
        }
    }
    QMessageBox::warning(this,"Not Found","No such account found");
}

void BankSystem::updateAccount() {
    bool ok;
    QString searchID = QInputDialog::getText(this,"Update Account","Enter ID:",QLineEdit::Normal,"",&ok);
    if(!ok) return;
    for(auto &c : customers){
        if(c.ID == searchID){
            c.name = QInputDialog::getText(this, "Update", "New Name:", QLineEdit::Normal, c.name, &ok); if(!ok) return;
            c.address = QInputDialog::getText(this, "Update", "New Address:", QLineEdit::Normal, c.address, &ok); if(!ok) return;
            c.contact = QInputDialog::getInt(this, "Update", "New Contact:", c.contact, 0, 999999999, 1, &ok); if(!ok) return;
            saveData();
            QMessageBox::information(this, "Success", "Account Updated");
            return;
        }
    }
    QMessageBox::warning(this,"Not Found","No such account found");
}

void BankSystem::transactions() {
    bool ok;
    QString searchID = QInputDialog::getText(this,"Transactions","Enter ID:",QLineEdit::Normal,"",&ok);
    if(!ok) return;
    for(auto &c : customers){
        if(c.ID == searchID){
            int choice = QInputDialog::getInt(this,"Transactions","1. Deposit\n2. Withdraw\nChoose:",1,1,2,1,&ok); if(!ok) return;
            int amount = QInputDialog::getInt(this,"Transactions","Enter Amount:",0,0,1000000,1,&ok); if(!ok) return;
            if(choice==1){ c.cash += amount; }
            else if(choice==2){
                if(amount>c.cash){ QMessageBox::warning(this,"Error","Insufficient Balance"); return; }
                c.cash -= amount;
            }
            saveData();
            QMessageBox::information(this,"Success","Transaction Completed");
            return;
        }
    }
    QMessageBox::warning(this,"Not Found","No such account found");
}

void BankSystem::deleteAccount() {
    bool ok;
    QString searchID = QInputDialog::getText(this,"Delete Account","Enter ID:",QLineEdit::Normal,"",&ok);
    if(!ok) return;
    for(int i=0;i<customers.size();i++){
        if(customers[i].ID == searchID){
            customers.erase(customers.begin()+i);
            saveData();
            QMessageBox::information(this,"Deleted","Account Deleted");
            return;
        }
    }
    QMessageBox::warning(this,"Not Found","No such account found");
}

// ---------------- Data ----------------
void BankSystem::saveData() {
    QFile file("bankdata.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << customers.size() << "\n";
        for(auto &c:customers){
            out << c.name << ' ' << c.ID << ' ' << c.address << ' ' << c.contact << ' ' << c.cash << "\n";
        }
        file.close();
    }
}

void BankSystem::loadData() {
    QFile file("bankdata.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        int n; in >> n; in.readLine();
        for(int i=0;i<n;i++){
            Person c;
            in >> c.name >> c.ID >> c.address >> c.contact >> c.cash;
            in.readLine();
            customers.push_back(c);
        }
        file.close();
    }
}
