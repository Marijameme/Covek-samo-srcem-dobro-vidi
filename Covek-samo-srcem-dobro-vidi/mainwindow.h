#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <vector>

#include "ImageFormats.h"

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
    void print_metadata();
    void exposeLayer();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QString m_fName;
    imageFormat m_format;
    std::vector<QWidget*> openedWindows;
    void showMessage(QWidget *parent, QString message);

};
#endif // MAINWINDOW_H
