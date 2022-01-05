#include "qfileslistdraganddrop.h"

#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QMessageBox>

QFilesListDragAndDrop::QFilesListDragAndDrop(QWidget* parent) : QListWidget { parent }
{
    // nop
}

void QFilesListDragAndDrop::dragEnterEvent(QDragEnterEvent* e)
{
    if (!e->mimeData()->hasUrls())
    {
        e->setAccepted(false);
        return;
    }

    e->setAccepted(true);
}

void QFilesListDragAndDrop::dropEvent(QDropEvent* e)
{
    if (!e->mimeData()->hasUrls())
    {
        e->setAccepted(false);
        return;
    }

    const QList<QUrl> urls = e->mimeData()->urls();

    for (const QUrl& url : urls)
    {
        this->addItem(url.toLocalFile());
    }

    e->setAccepted(true);
}
