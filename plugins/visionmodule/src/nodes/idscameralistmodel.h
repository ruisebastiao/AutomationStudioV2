#ifndef IDSCAMERALISTMODEL_H
#define IDSCAMERALISTMODEL_H

#include "idscamera.h"
#include "uEye.h"

#include <QAbstractListModel>



class IDSCameraListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(CameraRoles)
public:

    enum CameraRoles {
        NameRole = Qt::UserRole + 1

    };

    IDSCameraListModel();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;


    IDSCamera* findByID(int id);



    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE int count();

    void AddCamera(IDSCamera *idscamera);

    void MergeCameras(UEYE_CAMERA_LIST *idscameralist);

    void clear();


    QHash<int, QByteArray> roleNames() const;

public slots:
    IDSCamera *getItemAt(int index);
    int indexOfID(int id);

private:
    QList<IDSCamera*> m_IDSCameras;
};



#endif // IDSCAMERALISTMODEL_H
