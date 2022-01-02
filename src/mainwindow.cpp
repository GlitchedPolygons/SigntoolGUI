#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "constants.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

