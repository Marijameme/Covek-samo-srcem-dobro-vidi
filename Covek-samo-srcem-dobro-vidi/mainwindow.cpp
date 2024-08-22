#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include <QWidget>
#include <iostream>

#include "ImageFormats.h"
#include "colorfilter.h"
#include "metadata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    ui->wHidden->hide();

    connect(ui->pbUploadImage, &QPushButton::clicked, this, &MainWindow::uploadImage);
    connect(ui->pbExif, &QPushButton::clicked, this, &MainWindow::print_metadata);
    connect(ui->pbShowLayer, &QPushButton::clicked, this, &MainWindow::exposeLayer);
    connect(ui->pbNext, &QPushButton::clicked, this, &MainWindow::nextImage);
    connect(ui->pbPrevious, &QPushButton::clicked, this, &MainWindow::previousImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadImage()
{
    if (ui->imgView->scene())
        ui->imgView->scene()->clear();

    this->m_fName =
        QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    if (this->m_fName.isEmpty())
        return;

    const std::string format = Metadata::get_image_format(this->m_fName);
    auto it = toImageFormat.find(format);
    if (it != toImageFormat.end())
    {
        this->m_format = it->second;
    }
    else
    {
        this->m_format = imageFormat::UNKNOWN;
    }

    QPixmap pMap(this->m_fName);

    if (!ui->imgView->scene())
    {
        qDebug() << "No Scene!";

        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->imgView->setScene(scene);
    }

    ui->imgView->scene()->addPixmap(pMap);
    // std::cout << m_fName .toStdString()<< std::endl;
}

void MainWindow::print_metadata()
{
    if (this->m_fName.size() == 0)
    {
        MainWindow::showMessage(*this, "Please sellect an image first");
        return;
    }

    auto f = Metadata::read_data(this->m_fName);
    if (f.size() == 0)
    {
        MainWindow::showMessage(*this, "No metadata was extracted");
        return;
    }

    QWidget *metadataWindow = new QWidget();
    this->openedWindows.emplace_back(metadataWindow);
    metadataWindow->setWindowTitle("Image metadata");
    metadataWindow->setFixedSize(600, 800);

    QTableWidget *metadataTable = new QTableWidget(metadataWindow);
    metadataTable->setMinimumSize(600, 800);
    metadataTable->setColumnCount(2);
    metadataTable->setColumnWidth(0, 200);
    metadataTable->setColumnWidth(1, 400);
    int numRows = f.size();
    metadataTable->setRowCount(numRows);
    QStringList headers = {"Feature Name", "Feature Value"};
    metadataTable->setHorizontalHeaderLabels(headers);

    int rowCount = 0;
    for (const auto &md : f)
    {
        QTableWidgetItem *featureName = new QTableWidgetItem(QString::fromStdString(md.first));
        metadataTable->setItem(rowCount, 0, featureName);
        QTableWidgetItem *fetureValue = new QTableWidgetItem(QString::fromStdString(md.second));
        metadataTable->setItem(rowCount, 1, fetureValue);
        rowCount++;
    }
    metadataWindow->show();
}

void MainWindow::exposeLayer()
{
    if (this->m_fName.isEmpty())
    {
        MainWindow::showMessage(*this, "Please sellect an image first");
        return;
    }
    this->currImage = 0;

    ColorFilter::Layer layer = ColorFilter::toLayer(ui->cbColor->currentText());
    auto cf = new ColorFilter(this->m_fName, layer);
    this->layerImages = cf->getImages();

    ui->wHidden->setVisible(true);
    this->showImage(this->layerImages[0]);
}

void MainWindow::nextImage()
{
    if (this->layerImages.empty())
    {
        MainWindow::showMessage(*this, "No images to show");
        return;
    }

    this->currImage++;
    this->currImage = this->currImage % 8;
    this->showImage(this->layerImages[this->currImage]);
}

void MainWindow::previousImage()
{
    if (this->layerImages.empty())
    {
        MainWindow::showMessage(*this, "No images to show");
        return;
    }

    this->currImage--;
    if (this->currImage < 0)
        this->currImage += 8;
    this->currImage = this->currImage % 8;
    this->showImage(this->layerImages[this->currImage]);
}

void MainWindow::showImage(QImage &image)
{

    QPixmap pMap(QPixmap::fromImage(image));

    if (!ui->imgView->scene())
    {
        qDebug() << "No Scene!";

        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->imgView->setScene(scene);
    }
    ui->imgView->scene()->addPixmap(pMap);
}

void MainWindow::showMessage(QWidget &parent, QString message)
{
    QMessageBox::information(&parent, "", message);
}
