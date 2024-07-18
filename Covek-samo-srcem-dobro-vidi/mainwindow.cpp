#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbUploadImage, &QPushButton::clicked, this, &MainWindow::uploadImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadImage()
{
    if(ui->imgView->scene())
        ui->imgView->scene()->clear();

    QString fName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    if(fName != nullptr){
        QPixmap pMap(fName);

        if (! ui->imgView->scene()) {
            qDebug() << "No Scene!";

            QGraphicsScene *scene = new QGraphicsScene(this);
            ui->imgView->setScene(scene);
        }

        ui->imgView->scene()->addPixmap(pMap);
        std::cout << fName .toStdString()<< std::endl;
    }
}
