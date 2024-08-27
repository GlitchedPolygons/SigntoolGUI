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

    ui->buttonGroupHashAlgo->setId(ui->radioButtonHashAlgoSHA256, 0);
    ui->buttonGroupHashAlgo->setId(ui->radioButtonHashAlgoSHA384, 1);
    ui->buttonGroupHashAlgo->setId(ui->radioButtonHashAlgoSHA512, 2);

    ui->buttonGroupTimestampHashAlgo->setId(ui->radioButtonTimestampHashAlgoSHA256, 0);
    ui->buttonGroupTimestampHashAlgo->setId(ui->radioButtonTimestampHashAlgoSHA384, 1);
    ui->buttonGroupTimestampHashAlgo->setId(ui->radioButtonTimestampHashAlgoSHA512, 2);

    ui->labelAboutText->setText(QString("About Signtool GUI - v%1").arg(Constants::appVersion));

    loadSettings();
}

MainWindow::~MainWindow()
{
    QSettings settings;

    const bool saveHashAlgo = ui->checkBoxSaveHashAlgoOnQuit->isChecked();
    const bool saveWindowSize = ui->checkBoxSaveWindowSizeOnQuit->isChecked();
    const bool savePfxFilePath = ui->checkBoxSavePfxFilePathOnQuit->isChecked();
    const bool saveTimestampHashAlgo = ui->checkBoxSaveTimestampHashAlgoOnQuit->isChecked();
    const bool saveTimestampServerUrl = ui->checkBoxSaveTimestampServerUrlOnQuit->isChecked();

    settings.setValue(Constants::Settings::saveHashAlgoOnQuit, QVariant(saveHashAlgo));
    settings.setValue(Constants::Settings::saveWindowSizeOnQuit, QVariant(saveWindowSize));
    settings.setValue(Constants::Settings::savePfxFilePathOnQuit, QVariant(savePfxFilePath));
    settings.setValue(Constants::Settings::saveTimestampHashAlgoOnQuit, QVariant(saveTimestampHashAlgo));
    settings.setValue(Constants::Settings::saveTimestampServerUrlOnQuit, QVariant(saveTimestampServerUrl));

    if (saveHashAlgo)
    {
        settings.setValue(Constants::Settings::hashAlgo, QVariant(ui->buttonGroupHashAlgo->checkedId()));
    }

    if (savePfxFilePath)
    {
        settings.setValue(Constants::Settings::pfxFile, QVariant(ui->lineEditPfxFile->text()));
    }

    if (saveTimestampHashAlgo)
    {
        settings.setValue(Constants::Settings::timestampHashAlgo, QVariant(ui->buttonGroupTimestampHashAlgo->checkedId()));
    }

    if (saveTimestampServerUrl)
    {
        settings.setValue(Constants::Settings::timestampServerUrl, QVariant(ui->lineEditTimestampServer->text()));
    }

    if (saveWindowSize)
    {
        settings.setValue(Constants::Settings::windowWidth, QVariant(width()));
        settings.setValue(Constants::Settings::windowHeight, QVariant(height()));
    }

    delete ui;
}

void MainWindow::loadSettings()
{
    QSettings settings;

    const QString pfxFile = settings.value(Constants::Settings::pfxFile, QVariant("")).toString();
    const bool saveWindowSize = settings.value(Constants::Settings::saveWindowSizeOnQuit, QVariant(Constants::Settings::DefaultValues::saveWindowSizeOnQuit)).toBool();
    const bool saveHashAlgo = settings.value(Constants::Settings::saveHashAlgoOnQuit, QVariant(Constants::Settings::DefaultValues::saveHashAlgoOnQuit)).toBool();
    const bool savePfxFilePath = settings.value(Constants::Settings::savePfxFilePathOnQuit, QVariant(Constants::Settings::DefaultValues::savePfxFilePathOnQuit)).toBool();
    const bool saveTimestampHashAlgo = settings.value(Constants::Settings::saveTimestampHashAlgoOnQuit, QVariant(Constants::Settings::DefaultValues::saveTimestampHashAlgoOnQuit)).toBool();
    const bool saveTimestampServerUrl = settings.value(Constants::Settings::saveTimestampServerUrlOnQuit, QVariant(Constants::Settings::DefaultValues::saveTimestampServerUrlOnQuit)).toBool();

    ui->checkBoxSaveHashAlgoOnQuit->setChecked(saveHashAlgo);
    ui->checkBoxSavePfxFilePathOnQuit->setChecked(savePfxFilePath);
    ui->checkBoxSaveWindowSizeOnQuit->setChecked(saveWindowSize);
    ui->checkBoxSaveTimestampHashAlgoOnQuit->setChecked(saveTimestampHashAlgo);
    ui->checkBoxSaveTimestampServerUrlOnQuit->setChecked(saveTimestampServerUrl);

    if (saveHashAlgo)
    {
        switch (settings.value(Constants::Settings::hashAlgo, QVariant(Constants::Settings::DefaultValues::hashAlgo)).toInt())
        {
            default:
                ui->radioButtonHashAlgoSHA256->setChecked(true);
                break;
            case 1:
                ui->radioButtonHashAlgoSHA384->setChecked(true);
                break;
            case 2:
                ui->radioButtonHashAlgoSHA512->setChecked(true);
                break;
        }
    }

    if (saveTimestampHashAlgo)
    {
        switch (settings.value(Constants::Settings::timestampHashAlgo, QVariant(Constants::Settings::DefaultValues::timestampHashAlgo)).toInt())
        {
            default:
                ui->radioButtonTimestampHashAlgoSHA256->setChecked(true);
                break;
            case 1:
                ui->radioButtonTimestampHashAlgoSHA384->setChecked(true);
                break;
            case 2:
                ui->radioButtonTimestampHashAlgoSHA512->setChecked(true);
                break;
        }
    }

    if (savePfxFilePath)
    {
        ui->lineEditPfxFile->setText(settings.value(Constants::Settings::pfxFile, QVariant(Constants::Settings::DefaultValues::pfxFile)).toString());
    }

    if (saveTimestampServerUrl)
    {
        ui->lineEditTimestampServer->setText(settings.value(Constants::Settings::timestampServerUrl, QVariant(Constants::Settings::DefaultValues::timestampServerUrl)).toString());
    }

    if (saveWindowSize)
    {
        const int w = settings.value(Constants::Settings::windowWidth, QVariant(minimumSize().width())).toInt();
        const int h = settings.value(Constants::Settings::windowHeight, QVariant(minimumSize().height())).toInt();

        this->resize(w > 0 ? w : -w, h > 0 ? h : -h);
    }
}

void MainWindow::on_pushButtonBrowsePfxFile_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, "Select .pfx/.p12 file for signing", "", "PFX/P12 Signing File (*.p12 *.pfx)");

    if (fileName.isEmpty())
    {
        return;
    }

    if (!QFile::exists(fileName)) [[unlikely]]
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

static inline const QString hashAlgoStringFromId(const int id)
{
    switch (id)
    {
        default:
            return QString("SHA256");
        case 1:
            return QString("SHA384");
        case 2:
            return QString("SHA512");
    }
}

void MainWindow::on_pushButtonSign_clicked()
{
    if (busy)
    {
        return;
    }

    busy = true;

    if (ui->lineEditTimestampServer->text().isEmpty())
        ui->lineEditTimestampServer->setText(Constants::Settings::DefaultValues::timestampServerUrl);

    const QString pfxFilePath = ui->lineEditPfxFile->text();
    const QString timestampServer = ui->lineEditTimestampServer->text();

    if (pfxFilePath.isEmpty())
    {
        ui->textEditSignOutput->setText("No .pfx/.p12 file selected... Please provide a valid file to use for signing!\n\nUse the \"Browse\" button above and select the code signing certificate to use!");
        busy = false;
        return;
    }

    const bool useSHA1 = !QFile::exists(pfxFilePath) && pfxFilePath.length() == 40;

    if (!QFile::exists(pfxFilePath) && !useSHA1) [[unlikely]]
    {
        ui->textEditSignOutput->setText("The specified .pfx/.p12 file does not exist or access to it failed.");
        busy = false;
        return;
    }

    if (ui->listWidgetFilesToSign->count() == 0)
    {
        ui->textEditSignOutput->setText("No files to sign.\n\nPlease drag & drop one or more binaries into the list above to proceed!");
        busy = false;
        return;
    }

    ui->textEditSignOutput->setText("Signing above specified files...");
    repaint();

    QString cmdBase =

    useSHA1
        ?
            QString("signtool.exe sign /sha1 \"%1\" /tr \"%2\" /td \"%3\" /fd \"%4\" ")
                .arg
            (
                pfxFilePath,
                timestampServer,
                hashAlgoStringFromId(ui->buttonGroupTimestampHashAlgo->checkedId()),
                hashAlgoStringFromId(ui->buttonGroupHashAlgo->checkedId())
            )
        :
            QString("signtool.exe sign /fd \"%1\" /td \"%2\" /tr \"%3\" /f \"%4\" /p \"%5\" ")
            .arg
            (
                hashAlgoStringFromId(ui->buttonGroupHashAlgo->checkedId()),
                hashAlgoStringFromId(ui->buttonGroupTimestampHashAlgo->checkedId()),
                timestampServer,
                pfxFilePath,
                ui->lineEditPfxFilePassword->text()
            );

    QString output;
    output.reserve(1024);

    int failures = 0;

    for (int i = 0; i < ui->listWidgetFilesToSign->count(); ++i)
    {
        const QListWidgetItem* fileToSign = ui->listWidgetFilesToSign->item(i);
        const QString filePath = fileToSign->text();

        QString cmd;
        cmd.reserve(512);
        cmd.append(cmdBase);
        cmd.append(QString("\"%1\"").arg(filePath));

        STARTUPINFOW startupInfo;
        memset(&startupInfo, 0x00, sizeof(startupInfo));
        startupInfo.cb = sizeof(startupInfo);

        PROCESS_INFORMATION processInformation;
        memset(&processInformation, 0x00, sizeof(processInformation));

        BOOL success = CreateProcessW(NULL, const_cast<wchar_t*>(cmd.toStdWString().c_str()), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation);

        DWORD error = 0;
        if (success)
        {
            // Wait until process completes.
            WaitForSingleObject(processInformation.hProcess, 1024 * 64);

            // Check process exit code.
            GetExitCodeProcess(processInformation.hProcess, &error);

            // Avoid memory leak by closing process handle.
            CloseHandle(processInformation.hProcess);

            if (error == 0)
            {
                output.append(QString("✅  Signed \"%1\" successfully! \n").arg(filePath));
            }
            else
            {
                ++failures;
                output.append(QString("❌  Failed to sign \"%1\" \n").arg(filePath));
            }

            ui->textEditSignOutput->setText(output);
            repaint();
        }
        else
        {
            ++failures;
            error = GetLastError();

            output.append(QString("❌  Failed to sign \"%1\" - Error %2\nPlease make sure that you have signtool.exe installed and available in your $PATH\n").arg(filePath).arg(error));

            ui->textEditSignOutput->setText(output);
            repaint();
        }
    }

    output.append(QString("----------------------------------------------------------------------\n Signed %1 / %2 files successfully! \n\n").arg(ui->listWidgetFilesToSign->count() - failures).arg(ui->listWidgetFilesToSign->count()));

    ui->textEditSignOutput->setText(output);
    repaint();

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

    QString cmdBase = "signtool.exe verify /pa ";

    QString output;
    output.reserve(1024);

    int failures = 0;

    for (int i = 0; i < ui->listWidgetFilesToVerify->count(); ++i)
    {
        const QListWidgetItem* fileToVerify = ui->listWidgetFilesToVerify->item(i);
        const QString filePath = fileToVerify->text();

        QString cmd;
        cmd.reserve(512);
        cmd.append(cmdBase);
        cmd.append(QString("\"%1\"").arg(filePath));

        STARTUPINFOW startupInfo;
        memset(&startupInfo, 0x00, sizeof(startupInfo));
        startupInfo.cb = sizeof(startupInfo);

        PROCESS_INFORMATION processInformation;
        memset(&processInformation, 0x00, sizeof(processInformation));

        BOOL success = CreateProcessW(NULL, const_cast<wchar_t*>(cmd.toStdWString().c_str()), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation);

        DWORD error = 0;
        if (success)
        {
            WaitForSingleObject(processInformation.hProcess, 1024 * 64);
            GetExitCodeProcess(processInformation.hProcess, &error);
            CloseHandle(processInformation.hProcess);

            if (error == 0)
            {
                output.append(QString("✅  \"%1\" \n").arg(filePath));
            }
            else
            {
                ++failures;
                output.append(QString("❌  \"%1\" \n").arg(filePath));
            }

            ui->textEditFilesVerificationOutput->setText(output);
            repaint();
        }
        else
        {
            ++failures;
            error = GetLastError();

            output.append(QString("❌  \"%1\" - Error %2\nPlease make sure that you have signtool.exe installed and available in your $PATH\n").arg(filePath).arg(error));

            ui->textEditFilesVerificationOutput->setText(output);
            repaint();
        }
    }

    output.append(QString("----------------------------------------------------------------------\n %1 / %2 files verified successfully! \n\n").arg(ui->listWidgetFilesToVerify->count() - failures).arg(ui->listWidgetFilesToVerify->count()));

    ui->textEditFilesVerificationOutput->setText(output);
    repaint();

    busy = false;
}

void MainWindow::on_pushButtonClearFilesToVerifyList_clicked()
{
    ui->listWidgetFilesToVerify->clear();
}

void MainWindow::on_pushButtonPasteDigiCertTimestampServer_clicked()
{
    ui->lineEditTimestampServer->setText("http://timestamp.digicert.com");
}

void MainWindow::on_pushButtonPasteSectigoTimestampServer_clicked()
{
    ui->lineEditTimestampServer->setText("http://timestamp.sectigo.com");
}

void MainWindow::on_pushButtonPasteGlobalSignTimestampServer_clicked()
{
    ui->lineEditTimestampServer->setText("http://timestamp.globalsign.com/tsa/r6advanced1");
}

void MainWindow::on_pushButtonPasteCertumTimestampServer_clicked()
{
    ui->lineEditTimestampServer->setText("http://time.certum.pl");
}

void MainWindow::on_pushButtonRevertAllSettingsToDefaultValues_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you absolutely sure?");
    msgBox.setInformativeText("This action is irreversible! Do you really want to revert all settings to their default values?\n\nThis also clears the .pfx/.p12 file path and password fields.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    const int r = msgBox.exec();
    if (r != QMessageBox::Yes)
    {
        return;
    }

    ui->checkBoxSaveHashAlgoOnQuit->setChecked(true);
    ui->checkBoxSavePfxFilePathOnQuit->setChecked(true);
    ui->checkBoxSaveTimestampHashAlgoOnQuit->setChecked(true);
    ui->checkBoxSaveTimestampServerUrlOnQuit->setChecked(true);
    ui->checkBoxSaveWindowSizeOnQuit->setChecked(false);

    ui->radioButtonHashAlgoSHA512->setChecked(true);
    ui->radioButtonTimestampHashAlgoSHA512->setChecked(true);

    ui->lineEditTimestampServer->setText(Constants::Settings::DefaultValues::timestampServerUrl);

    ui->lineEditPfxFile->clear();
    ui->lineEditPfxFilePassword->clear();

    resize(minimumWidth(), minimumHeight());
}
