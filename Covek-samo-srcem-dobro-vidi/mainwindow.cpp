#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QTableWidget>
#include <QString>
#include <QCloseEvent>

#include "metadata.h"
#include "ImageFormats.h"
#include "colorfilter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    ui->wHidden->hide();

    connect(ui->pbUploadImage, &QPushButton::clicked, this, &MainWindow::uploadImage);
    connect(ui->pbExif, &QPushButton::clicked, this, &MainWindow::print_metadata);
    connect(ui->pbShowLayer, &QPushButton::clicked, this, &MainWindow::exposeLayer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadImage()
{
    if(ui->imgView->scene())
        ui->imgView->scene()->clear();

    this->m_fName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    if(this->m_fName.isEmpty())
        return;

    const std::string format = Metadata::get_image_format(this->m_fName);
    auto it = toImageFormat.find(format);
    if (it != toImageFormat.end()) {
        this->m_format = it->second;
    } else {
        this->m_format = imageFormat::UNKNOWN;
    }

    QPixmap pMap(this->m_fName);

    if (! ui->imgView->scene()) {
        qDebug() << "No Scene!";

        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->imgView->setScene(scene);
    }

    ui->imgView->scene()->addPixmap(pMap);
    std::cout << m_fName .toStdString()<< std::endl;

}

void MainWindow::print_metadata()
{
    if(this->m_fName.size() == 0){
        MainWindow::showMessage(this, "Please sellect an image first");
        return;
    }

    auto f = Metadata::read_data(this->m_fName);
    if(f.size() == 0){
        MainWindow::showMessage(this, "No metadata was extracted");
        return;
    }

    QWidget *metadataWindow = new QWidget();
    this->openedWindows.emplace_back(metadataWindow);
    metadataWindow->setWindowTitle("Image metadata");
    metadataWindow->setFixedSize(600, 800);

    QTableWidget *metadataTable = new QTableWidget(metadataWindow);
    metadataTable->setMinimumSize(600,800) ;
    metadataTable->setColumnCount(2);
    metadataTable->setColumnWidth(0, 200);
    metadataTable->setColumnWidth(1, 400);
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
    }
    metadataWindow->show();
}

void MainWindow::exposeLayer()
{
    if(this->m_fName.size() == 0){
        MainWindow::showMessage(this, "Please sellect an image first");
        return;
    }
    ColorFilter::Layer layer = ColorFilter::toLayer(ui->cbColor->currentText());
    auto cf = new ColorFilter(this->m_fName, layer);
    std::vector<QImage> images = cf->getImages();

    ui->wHidden->setVisible(true);
    QPixmap pMap(QPixmap::fromImage(images[0]));

    if(!ui->imgView->scene()){
        qDebug() << "No Scene!";

        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->imgView->setScene(scene);
    }
    ui->imgView->scene()->addPixmap(pMap);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    for(auto w : this->openedWindows)
        w->close();
    event->accept();
}

void MainWindow::showMessage(QWidget *parent, QString message)
{
    QMessageBox *noData = new QMessageBox(parent);
    noData->setText(message);
    noData->show();
}
