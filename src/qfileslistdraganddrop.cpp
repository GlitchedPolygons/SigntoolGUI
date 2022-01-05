#include "qfileslistdraganddrop.h"

#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QMessageBox>

QFilesListDragAndDrop::QFilesListDragAndDrop(QWidget* parent) : QListWidget { parent }
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setMouseTracking(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDropIndicatorShown(true);
    setAcceptDrops(true);
    viewport()->setAcceptDrops(true);

}

void QFilesListDragAndDrop::dragEnterEvent(QDragEnterEvent* e)
{
    e->setAccepted(e->mimeData()->hasUrls());
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
