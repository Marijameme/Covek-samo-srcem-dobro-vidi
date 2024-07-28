#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
<<<<<<< HEAD
=======
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QTableWidget>
#include <QString>
#include <QCloseEvent>
>>>>>>> 6e3e0c1 (feat: add metadata extraction using ExifTool)

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbUploadImage, &QPushButton::clicked, this, &MainWindow::uploadImage);
<<<<<<< HEAD
=======
    connect(ui->pbExif, &QPushButton::clicked, this, &MainWindow::print_metadata);

>>>>>>> 6e3e0c1 (feat: add metadata extraction using ExifTool)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadImage()
{
    if(ui->imgView->scene())
        ui->imgView->scene()->clear();

<<<<<<< HEAD
    QString fName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    if(fName != nullptr){
        QPixmap pMap(fName);
=======
    this->m_fName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    const std::string format = Metadata::get_image_format(this->m_fName);
    std::cout << format << std::endl;
    auto it = toImageFormat.find(format);
    if (it != toImageFormat.end()) {
        this->m_format = it->second;
    } else {
        this->m_format = imageFormat::UNKNOWN;
    }

    if(this->m_fName != nullptr){
        QPixmap pMap(this->m_fName);
>>>>>>> 6e3e0c1 (feat: add metadata extraction using ExifTool)

        if (! ui->imgView->scene()) {
            qDebug() << "No Scene!";

            QGraphicsScene *scene = new QGraphicsScene(this);
            ui->imgView->setScene(scene);
        }

        ui->imgView->scene()->addPixmap(pMap);
        std::cout << fName .toStdString()<< std::endl;
    }
}
<<<<<<< HEAD
=======

void MainWindow::print_metadata()
{
    // if(exifCompatible.find(this->m_format) == exifCompatible.end()){
    //     std::cout << toStdString.find(this->m_format)->second << std::endl;
    //     std::cout << "Format nije podrzan\n";
    //     QMessageBox *formatNotComaptible = new QMessageBox(this);
    //     formatNotComaptible->setWindowTitle("Format not supported");
    //     formatNotComaptible->setText("Image fomat doesn't support metadata extracion");
    //     formatNotComaptible->show();
    //     return;
    // }
    auto f = Metadata::read_data(this->m_fName);

    QWidget *metadataWindow = new QWidget();
    this->openedWindows.emplace_back(metadataWindow);
    metadataWindow->setWindowTitle("Image metadata");
    metadataWindow->setFixedSize(400, 800);

    QTableWidget *metadataTable = new QTableWidget(metadataWindow);
    metadataTable->setMinimumSize(400,800) ;
    metadataTable->setColumnCount(2);
    metadataTable->setColumnWidth(0, 200);
    metadataTable->setColumnWidth(1, 200);
    int numRows = f.size();
    metadataTable->setRowCount(numRows);
    QStringList headers = {"Feature Name", "Feature Value"};
    metadataTable->setHorizontalHeaderLabels(headers);

    int rowCount = 0;
    for(const auto &md : f){
        QTableWidgetItem *featureName = new QTableWidgetItem(QString::fromStdString(md.first));
        metadataTable->setItem(rowCount, 0, featureName);
        QTableWidgetItem *fetureValue = new QTableWidgetItem(QString::fromStdString(md.second));
        metadataTable->setItem(rowCount, 1, fetureValue);
        rowCount ++;
        // std::cout << md.first << " " << md.second << std::endl;
    }
    metadataWindow->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    for(auto w : this->openedWindows)
        w->close();
    event->accept();
}
>>>>>>> 6e3e0c1 (feat: add metadata extraction using ExifTool)
