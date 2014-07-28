/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QComboBox *cbDepth;
    QLabel *label_4;
    QSpinBox *sbFreq;
    QLabel *label_5;
    QSpinBox *sbAmp;
    QLabel *label_7;
    QSpinBox *sbSec;
    QPushButton *btPlay;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *vlFrame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QSpinBox *sbDx;
    QLabel *label_2;
    QSpinBox *sbDy;
    QLabel *label_3;
    QSpinBox *sbZoom;
    QPushButton *btRecalc;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1089, 660);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        centralWidget->setSizeIncrement(QSize(0, 0));
        centralWidget->setAutoFillBackground(false);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        cbDepth = new QComboBox(centralWidget);
        cbDepth->setObjectName(QStringLiteral("cbDepth"));

        horizontalLayout_2->addWidget(cbDepth);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        sbFreq = new QSpinBox(centralWidget);
        sbFreq->setObjectName(QStringLiteral("sbFreq"));
        sbFreq->setMaximum(99999999);
        sbFreq->setValue(60);

        horizontalLayout_2->addWidget(sbFreq);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        sbAmp = new QSpinBox(centralWidget);
        sbAmp->setObjectName(QStringLiteral("sbAmp"));
        sbAmp->setMaximum(999999999);
        sbAmp->setValue(100);

        horizontalLayout_2->addWidget(sbAmp);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        sbSec = new QSpinBox(centralWidget);
        sbSec->setObjectName(QStringLiteral("sbSec"));

        horizontalLayout_2->addWidget(sbSec);

        btPlay = new QPushButton(centralWidget);
        btPlay->setObjectName(QStringLiteral("btPlay"));

        horizontalLayout_2->addWidget(btPlay);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        vlFrame = new QVBoxLayout();
        vlFrame->setSpacing(6);
        vlFrame->setObjectName(QStringLiteral("vlFrame"));

        verticalLayout_2->addLayout(vlFrame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(20, -1, -1, -1);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        sbDx = new QSpinBox(centralWidget);
        sbDx->setObjectName(QStringLiteral("sbDx"));
        sbDx->setMaximum(99999999);

        horizontalLayout->addWidget(sbDx);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);

        sbDy = new QSpinBox(centralWidget);
        sbDy->setObjectName(QStringLiteral("sbDy"));
        sbDy->setMinimum(-99999999);
        sbDy->setMaximum(99999999);

        horizontalLayout->addWidget(sbDy);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_3);

        sbZoom = new QSpinBox(centralWidget);
        sbZoom->setObjectName(QStringLiteral("sbZoom"));

        horizontalLayout->addWidget(sbZoom);

        btRecalc = new QPushButton(centralWidget);
        btRecalc->setObjectName(QStringLiteral("btRecalc"));

        horizontalLayout->addWidget(btRecalc);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_6->setText(QApplication::translate("MainWindow", "Depth:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Frequency:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Amplitude:", 0));
        label_7->setText(QApplication::translate("MainWindow", "Segundos: ", 0));
        btPlay->setText(QApplication::translate("MainWindow", "Play", 0));
        label->setText(QApplication::translate("MainWindow", "Dx: ", 0));
        label_2->setText(QApplication::translate("MainWindow", "Dy: ", 0));
        label_3->setText(QApplication::translate("MainWindow", "Zoom: ", 0));
        btRecalc->setText(QApplication::translate("MainWindow", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
