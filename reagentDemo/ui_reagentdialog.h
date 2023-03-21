/********************************************************************************
** Form generated from reading UI file 'reagentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REAGENTDIALOG_H
#define UI_REAGENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReagentDialog
{
public:
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *reaSetting;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableView *reaInfoTable;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *manualRegistration;
    QSpacerItem *horizontalSpacer;
    QPushButton *deleteReagentInfo;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *reagentDiskScanning;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *reagentDIskRoation;
    QSpacerItem *horizontalSpacer_5;
    QWidget *reaStatus;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QTableView *selectSection;
    QTableView *displaySection;

    void setupUi(QWidget *ReagentDialog)
    {
        if (ReagentDialog->objectName().isEmpty())
            ReagentDialog->setObjectName(QString::fromUtf8("ReagentDialog"));
        ReagentDialog->resize(800, 600);
        gridLayout_3 = new QGridLayout(ReagentDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(ReagentDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        reaSetting = new QWidget();
        reaSetting->setObjectName(QString::fromUtf8("reaSetting"));
        gridLayout = new QGridLayout(reaSetting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        reaInfoTable = new QTableView(reaSetting);
        reaInfoTable->setObjectName(QString::fromUtf8("reaInfoTable"));

        verticalLayout->addWidget(reaInfoTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        manualRegistration = new QPushButton(reaSetting);
        manualRegistration->setObjectName(QString::fromUtf8("manualRegistration"));

        horizontalLayout->addWidget(manualRegistration);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        deleteReagentInfo = new QPushButton(reaSetting);
        deleteReagentInfo->setObjectName(QString::fromUtf8("deleteReagentInfo"));

        horizontalLayout->addWidget(deleteReagentInfo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        reagentDiskScanning = new QPushButton(reaSetting);
        reagentDiskScanning->setObjectName(QString::fromUtf8("reagentDiskScanning"));

        horizontalLayout->addWidget(reagentDiskScanning);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        reagentDIskRoation = new QPushButton(reaSetting);
        reagentDIskRoation->setObjectName(QString::fromUtf8("reagentDIskRoation"));

        horizontalLayout->addWidget(reagentDIskRoation);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(reaSetting, QString());
        reaStatus = new QWidget();
        reaStatus->setObjectName(QString::fromUtf8("reaStatus"));
        gridLayout_2 = new QGridLayout(reaStatus);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        selectSection = new QTableView(reaStatus);
        selectSection->setObjectName(QString::fromUtf8("selectSection"));

        horizontalLayout_2->addWidget(selectSection);

        displaySection = new QTableView(reaStatus);
        displaySection->setObjectName(QString::fromUtf8("displaySection"));

        horizontalLayout_2->addWidget(displaySection);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 4);

        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(reaStatus, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(ReagentDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ReagentDialog);
    } // setupUi

    void retranslateUi(QWidget *ReagentDialog)
    {
        ReagentDialog->setWindowTitle(QApplication::translate("ReagentDialog", "Reagent", nullptr));
        manualRegistration->setText(QApplication::translate("ReagentDialog", "\346\263\250\345\206\214", nullptr));
        deleteReagentInfo->setText(QApplication::translate("ReagentDialog", "\345\210\240\351\231\244", nullptr));
        reagentDiskScanning->setText(QApplication::translate("ReagentDialog", "\350\257\225\345\211\202\347\233\230\346\211\253\346\217\217", nullptr));
        reagentDIskRoation->setText(QApplication::translate("ReagentDialog", "\350\257\225\345\211\202\347\233\230\347\277\273\350\275\254", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(reaSetting), QApplication::translate("ReagentDialog", "\350\257\225\345\211\202\350\256\276\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(reaStatus), QApplication::translate("ReagentDialog", "\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReagentDialog: public Ui_ReagentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REAGENTDIALOG_H
