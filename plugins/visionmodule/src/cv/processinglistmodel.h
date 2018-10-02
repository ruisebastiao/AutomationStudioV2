#ifndef PROCESSINGLISTMODEL_H
#define PROCESSINGLISTMODEL_H

#include "processing.h"

#include <QAbstractListModel>
#include <jsonserializable.h>


#include <QJsonArray>
#include <QQuickItem>

class ProcessingListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ProcessingRoles {
        ProcessingRole = Qt::UserRole + 1,
        ProcessingNameRole
    };

    explicit ProcessingListModel(QObject* parent = nullptr);

private:
    QList<Processing*>  m_list;

public slots:
    void addProcessing(Processing* item);
    Processing* at(int index);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;



    QHash<int, QByteArray> roleNames() const;

    int size() const;
signals:
    void newProcessingAdded(Processing* item);
};




#endif // PROCESSINGLISTMODEL_H
