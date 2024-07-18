/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbDecode;
    QRadioButton *rbEncode;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cbColor;
    QPushButton *pbZstag;
    QPushButton *pbString;
    QPushButton *pbSteghide;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *imgView;
    QPushButton *pbUploadImage;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(801, 595);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 771, 541));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        rbDecode = new QRadioButton(horizontalLayoutWidget);
        rbDecode->setObjectName("rbDecode");

        verticalLayout->addWidget(rbDecode);

        rbEncode = new QRadioButton(horizontalLayoutWidget);
        rbEncode->setObjectName("rbEncode");

        verticalLayout->addWidget(rbEncode);

        line = new QFrame(horizontalLayoutWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        cbColor = new QComboBox(horizontalLayoutWidget);
        cbColor->addItem(QString());
        cbColor->addItem(QString());
        cbColor->addItem(QString());
        cbColor->addItem(QString());
        cbColor->setObjectName("cbColor");

        horizontalLayout_2->addWidget(cbColor);


        verticalLayout->addLayout(horizontalLayout_2);

        pbZstag = new QPushButton(horizontalLayoutWidget);
        pbZstag->setObjectName("pbZstag");

        verticalLayout->addWidget(pbZstag);

        pbString = new QPushButton(horizontalLayoutWidget);
        pbString->setObjectName("pbString");

        verticalLayout->addWidget(pbString);

        pbSteghide = new QPushButton(horizontalLayoutWidget);
        pbSteghide->setObjectName("pbSteghide");

        verticalLayout->addWidget(pbSteghide);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        imgView = new QGraphicsView(horizontalLayoutWidget);
        imgView->setObjectName("imgView");

        verticalLayout_2->addWidget(imgView);

        pbUploadImage = new QPushButton(horizontalLayoutWidget);
        pbUploadImage->setObjectName("pbUploadImage");

        verticalLayout_2->addWidget(pbUploadImage);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 801, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        rbDecode->setText(QCoreApplication::translate("MainWindow", "decode", nullptr));
        rbEncode->setText(QCoreApplication::translate("MainWindow", "encode", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "color filter:", nullptr));
        cbColor->setItemText(0, QCoreApplication::translate("MainWindow", "red", nullptr));
        cbColor->setItemText(1, QCoreApplication::translate("MainWindow", "green", nullptr));
        cbColor->setItemText(2, QCoreApplication::translate("MainWindow", "blue", nullptr));
        cbColor->setItemText(3, QCoreApplication::translate("MainWindow", "superimposed", nullptr));

        pbZstag->setText(QCoreApplication::translate("MainWindow", "zstag", nullptr));
        pbString->setText(QCoreApplication::translate("MainWindow", "string", nullptr));
        pbSteghide->setText(QCoreApplication::translate("MainWindow", "steghide", nullptr));
        pbUploadImage->setText(QCoreApplication::translate("MainWindow", "upload image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
