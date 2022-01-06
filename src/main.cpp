#include "mainwindow.h"
#include "constants.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication::setApplicationName(Constants::appName);
    QApplication::setApplicationVersion(Constants::appVersion);
    QApplication::setApplicationDisplayName("Signtool GUI");
    QApplication::setOrganizationName(Constants::orgName);
    QApplication::setOrganizationDomain(Constants::orgDomain);

    QApplication application(argc, argv);
    application.setWindowIcon(QIcon(":/img/icon.png"));

    MainWindow window;
    window.show();

    return application.exec();
}
