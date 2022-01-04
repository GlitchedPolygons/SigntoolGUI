#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "constants.h"
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings settings;

    const QString pfxFile = settings.value(Constants::Settings::pfxFile, QVariant("")).toString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browsePfxFilePushButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, "Select .pfx/.p12 file for signing", "", "PFX/P12 Signing File (*.p12 *.pfx)");

    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);

    if (!file.exists()) [[unlikely]]
    {
        QMessageBox msgBox;
        msgBox.setText("File does not exist or access to it failed.");
        msgBox.exec();
        return;
    }

    ui->pfxFileLineEdit->setText(fileName);
}

void MainWindow::on_showPfxFilePasswordPushButton_pressed()
{
    ui->pfxFilePasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
    ui->showPfxFilePasswordPushButton->setText("Hide");
}

void MainWindow::on_showPfxFilePasswordPushButton_released()
{
    ui->pfxFilePasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
    ui->showPfxFilePasswordPushButton->setText("Show");
}

void MainWindow::on_signPushButton_clicked()
{
    if (busy)
    {
        return;
    }

    busy = true;

    const QString fileName = ui->pfxFileLineEdit->text();

    if (fileName.isEmpty())
    {
        ui->signOutputTextEdit->setText("No .pfx/.p12 file selected... Please provide a valid file to use for signing!\n\nUse the \"Browse\" button above and select the code signing certificate to use!");
        busy = false;
        return;
    }

    QFile file(fileName);

    if (!file.exists()) [[unlikely]]
    {
        ui->signOutputTextEdit->setText("The specified .pfx/.p12 file does not exist or access to it failed.");
        busy = false;
        return;
    }

    // TODO: sign all files here
    busy = false;
}

void MainWindow::on_clearFilesToSignListPushButton_clicked()
{
    ui->filesToSignListWidget->clear();
}

void MainWindow::on_verifyFilesPushButton_clicked()
{
    if (busy)
    {
        return;
    }

    busy = true;

    if (ui->filesToVerifyListWidget->count() == 0)
    {
        ui->filesVerificationOutputTextEdit->setText("No files to verify.\n\nPlease drag & drop one or more binaries into the list above to proceed!");
        busy = false;
        return;
    }

    // TODO: verify list of files here

    busy = false;
}

void MainWindow::on_clearFilesToVerifyListPushButton_clicked()
{
    ui->filesToVerifyListWidget->clear();
}
