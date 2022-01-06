#ifndef QFILESLISTDRAGANDDROP_H
#define QFILESLISTDRAGANDDROP_H

#include <QWidget>
#include <QListWidget>

class QFilesListDragAndDrop : public QListWidget
{
    Q_OBJECT

public:
    explicit QFilesListDragAndDrop(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent*) override;
    void dragMoveEvent(QDragMoveEvent*) override;
    void dropEvent(QDropEvent*) override;
};

#endif // QFILESLISTDRAGANDDROP_H
