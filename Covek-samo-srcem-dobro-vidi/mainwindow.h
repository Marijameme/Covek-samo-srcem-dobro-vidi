#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void uploadImage();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
<<<<<<< HEAD
=======
    QString m_fName;
    imageFormat m_format;
    std::vector<QWidget*> openedWindows;

>>>>>>> 6e3e0c1 (feat: add metadata extraction using ExifTool)
};
#endif // MAINWINDOW_H
