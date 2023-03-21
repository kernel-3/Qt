/********************************************************************************
** Form generated from reading UI file 'reagentdiskscanningdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REAGENTDISKSCANNINGDIALOG_H
#define UI_REAGENTDISKSCANNINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReagentDiskScanningDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnSelectAll;
    QSpacerItem *verticalSpacer;
    QPushButton *btnScan;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnExit;
    QSpacerItem *verticalSpacer_4;
    QTableWidget *ReaDiskScanningView;

    void setupUi(QDialog *ReagentDiskScanningDialog)
    {
        if (ReagentDiskScanningDialog->objectName().isEmpty())
            ReagentDiskScanningDialog->setObjectName(QString::fromUtf8("ReagentDiskScanningDialog"));
        ReagentDiskScanningDialog->resize(768, 470);
        gridLayout_2 = new QGridLayout(ReagentDiskScanningDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        btnSelectAll = new QPushButton(ReagentDiskScanningDialog);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));

        verticalLayout->addWidget(btnSelectAll);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnScan = new QPushButton(ReagentDiskScanningDialog);
        btnScan->setObjectName(QString::fromUtf8("btnScan"));

        verticalLayout->addWidget(btnScan);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btnExit = new QPushButton(ReagentDiskScanningDialog);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        verticalLayout->addWidget(btnExit);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        ReaDiskScanningView = new QTableWidget(ReagentDiskScanningDialog);
        ReaDiskScanningView->setObjectName(QString::fromUtf8("ReaDiskScanningView"));

        gridLayout->addWidget(ReaDiskScanningView, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnMinimumWidth(0, 3);
        gridLayout->setColumnMinimumWidth(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(ReagentDiskScanningDialog);

        QMetaObject::connectSlotsByName(ReagentDiskScanningDialog);
    } // setupUi

    void retranslateUi(QDialog *ReagentDiskScanningDialog)
    {
        ReagentDiskScanningDialog->setWindowTitle(QApplication::translate("ReagentDiskScanningDialog", "Dialog", nullptr));
        btnSelectAll->setText(QApplication::translate("ReagentDiskScanningDialog", "\345\205\250\351\200\211", nullptr));
        btnScan->setText(QApplication::translate("ReagentDiskScanningDialog", "\346\211\253\346\217\217", nullptr));
        btnExit->setText(QApplication::translate("ReagentDiskScanningDialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReagentDiskScanningDialog: public Ui_ReagentDiskScanningDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REAGENTDISKSCANNINGDIALOG_H
