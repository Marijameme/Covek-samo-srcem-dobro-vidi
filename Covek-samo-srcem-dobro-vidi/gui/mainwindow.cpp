#include "mainwindow.h"

#include "./ui_mainwindow.h"

#include <exception>

#include <QAbstractItemView>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "cvqt.h"
#include "stegcore/BitPlane.h"
#include "stegcore/Metadata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800, 600);
    ui->wHidden->hide();

    connect(ui->pbUploadImage, &QPushButton::clicked, this, &MainWindow::uploadImage);
    connect(ui->pbExif, &QPushButton::clicked, this, &MainWindow::showMetadata);
    connect(ui->pbShowLayer, &QPushButton::clicked, this, &MainWindow::exposeLayer);
    connect(ui->pbNext, &QPushButton::clicked, this, &MainWindow::nextImage);
    connect(ui->pbPrevious, &QPushButton::clicked, this, &MainWindow::previousImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ensureScene()
{
    if (!ui->imgView->scene())
        ui->imgView->setScene(new QGraphicsScene(this));
}

void MainWindow::displayImage(const QImage &image)
{
    ensureScene();
    QGraphicsScene *scene = ui->imgView->scene();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(scene->itemsBoundingRect());
}

void MainWindow::info(const QString &message)
{
    QMessageBox::information(this, QString(), message);
}

void MainWindow::uploadImage()
{
    const QString path = QFileDialog::getOpenFileName(
        this, tr("Open Image"), QString(),
        tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif *.tif *.tiff)"));
    if (path.isEmpty())
        return;

    try
    {
        m_image = stegcore::ImageContext::load(path.toStdString());
    }
    catch (const std::exception &e)
    {
        info(tr("Could not open image: %1").arg(e.what()));
        return;
    }

    m_planes.clear();
    m_currentPlane = 0;
    ui->wHidden->hide();
    displayImage(QImage(path));
}

void MainWindow::showMetadata()
{
    if (!m_image)
    {
        info(tr("Please select an image first."));
        return;
    }

    const std::vector<stegcore::MetadataEntry> entries = stegcore::Metadata::readAll(m_image->path());
    if (entries.empty())
    {
        info(tr("No metadata was found in this image."));
        return;
    }

    QWidget *window = new QWidget(this, Qt::Window);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setWindowTitle(tr("Image metadata"));
    window->resize(700, 600);

    QTableWidget *table = new QTableWidget(static_cast<int>(entries.size()), 3, window);
    table->setHorizontalHeaderLabels({tr("Group"), tr("Tag"), tr("Value")});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int row = 0;
    for (const stegcore::MetadataEntry &entry : entries)
    {
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.group)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(entry.key)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(entry.value)));
        ++row;
    }
    table->resizeColumnsToContents();

    QVBoxLayout *layout = new QVBoxLayout(window);
    layout->addWidget(table);
    window->show();
}

void MainWindow::exposeLayer()
{
    if (!m_image)
    {
        info(tr("Please select an image first."));
        return;
    }
    if (m_image->pixels().empty())
    {
        info(tr("This image could not be decoded for pixel analysis."));
        return;
    }

    try
    {
        const stegcore::BitPlane::Channel channel =
            stegcore::BitPlane::channelFromString(ui->cbColor->currentText().toStdString());
        const std::vector<cv::Mat> planes =
            stegcore::BitPlane::extract(m_image->pixels(), channel);

        m_planes.clear();
        m_planes.reserve(planes.size());
        for (const cv::Mat &plane : planes)
            m_planes.push_back(cvqt::matToQImage(plane));
    }
    catch (const std::exception &e)
    {
        info(tr("Bit-plane extraction failed: %1").arg(e.what()));
        return;
    }

    m_currentPlane = 0;
    ui->wHidden->setVisible(true);
    displayImage(m_planes.front());
}

void MainWindow::nextImage()
{
    if (m_planes.empty())
        return;
    m_currentPlane = (m_currentPlane + 1) % static_cast<int>(m_planes.size());
    displayImage(m_planes[m_currentPlane]);
}

void MainWindow::previousImage()
{
    if (m_planes.empty())
        return;
    const int count = static_cast<int>(m_planes.size());
    m_currentPlane = (m_currentPlane - 1 + count) % count;
    displayImage(m_planes[m_currentPlane]);
}
