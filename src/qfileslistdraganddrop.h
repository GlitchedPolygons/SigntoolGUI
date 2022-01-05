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
    void dragEnterEvent(QDragEnterEvent* e) override;
    void dragMoveEvent(QDragMoveEvent* e) override;
    void dropEvent(QDropEvent* e) override;
};

#endif // QFILESLISTDRAGANDDROP_H
