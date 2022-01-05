#include "qfileslistdraganddrop.h"

#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
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
    if (!e->mimeData()->hasUrls())
    {
        e->ignore();
        return;
    }

    e->setDropAction(Qt::DropAction::CopyAction);
    e->accept();
}

void QFilesListDragAndDrop::dragMoveEvent(QDragMoveEvent* e)
{
    if (!e->mimeData()->hasUrls())
    {
        e->ignore();
        return;
    }

    e->setDropAction(Qt::DropAction::CopyAction);
    e->accept();
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
        const QString filePath = url.toLocalFile();
        const QFileInfo fileInfo(filePath);

        if (!fileInfo.exists() || fileInfo.isDir() || !findItems(filePath, Qt::MatchFixedString).empty())
            continue;

        this->addItem(filePath);
    }

    e->setAccepted(true);
}
