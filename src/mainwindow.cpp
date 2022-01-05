#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <stdio.h>
#include <windows.h>

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

static const inline BOOL FileExists(LPCWSTR filePath)
{
    const DWORD attributes = GetFileAttributesW(filePath);
    return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}

void MainWindow::on_pushButtonBrowsePfxFile_clicked()
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

    ui->lineEditPfxFile->setText(fileName);
}

void MainWindow::on_pushButtonShowPfxFilePassword_pressed()
{
    ui->lineEditPfxFilePassword->setEchoMode(QLineEdit::EchoMode::Normal);
    ui->pushButtonShowPfxFilePassword->setText("Hide");
}

void MainWindow::on_pushButtonShowPfxFilePassword_released()
{
    ui->lineEditPfxFilePassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->pushButtonShowPfxFilePassword->setText("Show");
}

void MainWindow::on_pushButtonSign_clicked()
{
    if (busy)
    {
        return;
    }

    busy = true;

    const QString fileName = ui->lineEditPfxFile->text();

    if (fileName.isEmpty())
    {
        ui->textEditSignOutput->setText("No .pfx/.p12 file selected... Please provide a valid file to use for signing!\n\nUse the \"Browse\" button above and select the code signing certificate to use!");
        busy = false;
        return;
    }

    QFile file(fileName);

    if (!file.exists()) [[unlikely]]
    {
        ui->textEditSignOutput->setText("The specified .pfx/.p12 file does not exist or access to it failed.");
        busy = false;
        return;
    }

    // TODO: sign all files here
    busy = false;
}

void MainWindow::on_pushButtonClearFilesToSignList_clicked()
{
    ui->listWidgetFilesToSign->clear();
}

void MainWindow::on_pushButtonVerifyFiles_clicked()
{
    if (busy)
    {
        return;
    }

    busy = true;

    if (ui->listWidgetFilesToVerify->count() == 0)
    {
        ui->textEditFilesVerificationOutput->setText("No files to verify.\n\nPlease drag & drop one or more binaries into the list above to proceed!");
        busy = false;
        return;
    }

    // TODO: verify list of files here

    busy = false;
}

void MainWindow::on_pushButtonClearFilesToVerifyList_clicked()
{
    ui->listWidgetFilesToVerify->clear();
}
