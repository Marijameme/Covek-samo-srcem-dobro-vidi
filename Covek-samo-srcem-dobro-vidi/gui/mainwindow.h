#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <optional>
#include <vector>

#include <QImage>
#include <QMainWindow>

#include "stegcore/ImageContext.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void uploadImage();
    void showMetadata();
    void exposeLayer();
    void nextImage();
    void previousImage();

  private:
    void ensureScene();
    void displayImage(const QImage &image);
    void info(const QString &message);

    Ui::MainWindow *ui;
    std::optional<stegcore::ImageContext> m_image;
    std::vector<QImage> m_planes;
    int m_currentPlane = 0;
};

#endif // MAINWINDOW_H
