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
    void on_pushButtonBrowsePfxFile_clicked();

    void on_pushButtonShowPfxFilePassword_pressed();

    void on_pushButtonShowPfxFilePassword_released();

    void on_pushButtonSign_clicked();

    void on_pushButtonClearFilesToSignList_clicked();

    void on_pushButtonVerifyFiles_clicked();

    void on_pushButtonClearFilesToVerifyList_clicked();

    void on_pushButtonPasteDigiCertTimestampServer_clicked();

    void on_pushButtonPasteSectigoTimestampServer_clicked();

    void on_pushButtonPasteGlobalSignTimestampServer_clicked();

    void on_pushButtonPasteCertumTimestampServer_clicked();

    void on_pushButtonRevertAllSettingsToDefaultValues_clicked();

private:
    Ui::MainWindow* ui;
    bool busy = false;
    void loadSettings();
};
#endif // MAINWINDOW_H
