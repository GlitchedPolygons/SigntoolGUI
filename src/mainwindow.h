#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_browsePfxFilePushButton_clicked();

    void on_showPfxFilePasswordPushButton_pressed();

    void on_showPfxFilePasswordPushButton_released();

    void on_signPushButton_clicked();

    void on_clearFilesToSignListPushButton_clicked();

    void on_verifyFilesPushButton_clicked();

    void on_clearFilesToVerifyListPushButton_clicked();

private:
    Ui::MainWindow* ui;
    bool busy = false;
};
#endif // MAINWINDOW_H
