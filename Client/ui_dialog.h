/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEditUId;
    QPushButton *btnLogin;
    QPushButton *btnLogout;
    QLabel *label_2;
    QLineEdit *lineEdit_RUId;
    QGroupBox *groupBox_2;
    QTextEdit *textEditReceive;
    QPushButton *btnSend;
    QTextEdit *textEditSend;
    QGroupBox *groupBox_4;
    QListWidget *lstHistory;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(927, 626);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(611, 40, 301, 91));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 23, 54, 16));
        lineEditUId = new QLineEdit(groupBox);
        lineEditUId->setObjectName(QStringLiteral("lineEditUId"));
        lineEditUId->setGeometry(QRect(60, 20, 113, 20));
        btnLogin = new QPushButton(groupBox);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(220, 20, 75, 23));
        btnLogout = new QPushButton(groupBox);
        btnLogout->setObjectName(QStringLiteral("btnLogout"));
        btnLogout->setGeometry(QRect(220, 60, 75, 23));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 62, 81, 16));
        lineEdit_RUId = new QLineEdit(groupBox);
        lineEdit_RUId->setObjectName(QStringLiteral("lineEdit_RUId"));
        lineEdit_RUId->setGeometry(QRect(93, 60, 113, 20));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(611, 140, 301, 331));
        textEditReceive = new QTextEdit(groupBox_2);
        textEditReceive->setObjectName(QStringLiteral("textEditReceive"));
        textEditReceive->setGeometry(QRect(10, 20, 281, 251));
        textEditReceive->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textEditReceive->setReadOnly(true);
        btnSend = new QPushButton(groupBox_2);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setGeometry(QRect(240, 280, 51, 41));
        textEditSend = new QTextEdit(groupBox_2);
        textEditSend->setObjectName(QStringLiteral("textEditSend"));
        textEditSend->setGeometry(QRect(10, 280, 221, 41));
        groupBox_4 = new QGroupBox(Dialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(610, 490, 301, 121));
        lstHistory = new QListWidget(groupBox_4);
        lstHistory->setObjectName(QStringLiteral("lstHistory"));
        lstHistory->setGeometry(QRect(10, 30, 281, 71));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("Dialog", "\350\201\224\346\234\272\345\257\271\346\210\230", nullptr));
        label->setText(QApplication::translate("Dialog", "\350\264\246\345\217\267\357\274\232", nullptr));
        btnLogin->setText(QApplication::translate("Dialog", "\347\231\273\345\275\225", nullptr));
        btnLogout->setText(QApplication::translate("Dialog", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QApplication::translate("Dialog", "\345\257\271\346\210\230\347\216\251\345\256\266:", nullptr));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\345\257\271\350\257\235", nullptr));
        btnSend->setText(QApplication::translate("Dialog", "\345\217\221\351\200\201", nullptr));
        groupBox_4->setTitle(QApplication::translate("Dialog", "\346\243\213\347\233\230\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
