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
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDropIndicatorShown(true);
    viewport()->setAcceptDrops(true);

}

static const inline bool isValidFileExtension(const QUrl& url)
{
    if (url.toLocalFile().endsWith(".exe", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".msi", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".dll", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".cab", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".cat", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".vbs", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".ps1", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".msix", Qt::CaseInsensitive)
     || url.toLocalFile().endsWith(".appx", Qt::CaseInsensitive))
    {
        return true;
    }

    return false;
}

void QFilesListDragAndDrop::dragEnterEvent(QDragEnterEvent* event)
{
    if (!event->mimeData()->hasUrls())
    {
        event->ignore();
        return;
    }

    bool valid = false;

    for (const QUrl& url : event->mimeData()->urls())
    {
        if (isValidFileExtension(url))
        {
            valid = true;
            break;
        }
    }

    if (!valid)
    {
        event->ignore();
        return;
    }

    event->setDropAction(Qt::DropAction::CopyAction);
    event->accept();
}

void QFilesListDragAndDrop::dragMoveEvent(QDragMoveEvent* event)
{
    if (!event->mimeData()->hasUrls())
    {
        event->ignore();
        return;
    }

    event->setDropAction(Qt::DropAction::CopyAction);
    event->accept();
}

void QFilesListDragAndDrop::dropEvent(QDropEvent* event)
{
    if (!event->mimeData()->hasUrls())
    {
        event->setAccepted(false);
        return;
    }

    for (const QUrl& url : event->mimeData()->urls())
    {
        if (!isValidFileExtension(url))
        {
            continue;
        }

        const QString filePath = url.toLocalFile();
        const QFileInfo fileInfo(filePath);

        if (!fileInfo.exists() || fileInfo.isDir() || !findItems(filePath, Qt::MatchFixedString).empty())
        {
            continue;
        }

        this->addItem(filePath);
    }

    event->setAccepted(true);
}

void QFilesListDragAndDrop::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key::Key_Delete)
    {
        for (QListWidgetItem* selectedItem : this->selectedItems())
        {
            delete this->takeItem(this->row(selectedItem));
        }
    }
}
