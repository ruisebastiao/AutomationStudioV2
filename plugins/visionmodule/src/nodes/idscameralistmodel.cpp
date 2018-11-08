#include "idscameralistmodel.h"


IDSCameraListModel::IDSCameraListModel()
{


}

int IDSCameraListModel::rowCount(const QModelIndex &parent) const
{
    int cnt=m_IDSCameras.count();
    return cnt;
}

IDSCamera *IDSCameraListModel::findByID(int id)
{
    for (int index = 0; index < m_IDSCameras.length(); ++index) {
        IDSCamera* camera=m_IDSCameras.at(index);
        if(camera->camID()==id){
            return camera;
        }
    }

    return nullptr;
}

int IDSCameraListModel::indexOfID(int id)
{
    for (int index = 0; index < m_IDSCameras.length(); ++index) {
        IDSCamera* camera=m_IDSCameras.at(index);
        if(camera->camID()==id){
            return index;
        }
    }

    return -1;
}

QVariant IDSCameraListModel::data(const QModelIndex &index, int role) const
{

       //std::lock_guard<decltype(mainQueueMutex)> lg(mainQueueMutex);

    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_IDSCameras.size())
    {
        return QVariant();
    }

    IDSCamera* idscamera = m_IDSCameras.at(index.row());
    if (role == NameRole){
        if(idscamera==nullptr){
            return QVariant();
        }
        QString temp(idscamera->serialnumber()+"("+QString::number(idscamera->camID())+")");
        return temp;
    }

    //        if (role == ProjectRole){
    //            //        QVariant var
    //            return QVariant::fromValue(project);
    //        }


    if (role == Qt::DisplayRole){


        return QVariant::fromValue(idscamera);
    }

    return QVariant();
}

int IDSCameraListModel::count()

{
    return m_IDSCameras.count();
}

void IDSCameraListModel::AddCamera(IDSCamera *idscamera)
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_IDSCameras.append(idscamera);

    endInsertRows();
}

void IDSCameraListModel::MergeCameras(UEYE_CAMERA_LIST *idscameralist)

{

    int iCamera;

    QList<int> removeindexs;

        //solution is here:



    QList<IDSCamera*>::iterator i = m_IDSCameras.begin();
    while (i != m_IDSCameras.end())
    {
        INT cameraid= (*i)->camID();

        bool cameraExists=false;

        for (iCamera = 0; iCamera < (int)idscameralist->dwCount; iCamera++) {


            QString camid(QString::number(idscameralist->uci[iCamera].dwCameraID));
            if(cameraid==camid){
                cameraExists=true;
                break;
            }


        }

        if (!cameraExists)
        {
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

            m_IDSCameras.erase(i++);  // alternatively, i = items.erase(i);
            endInsertRows();
        }
        else
        {

            ++i;
        }
    }


    for (iCamera = 0; iCamera < (int)idscameralist->dwCount; iCamera++) {

        //Test output of camera info on the screen

        int camid=idscameralist->uci[iCamera].dwCameraID;

        bool cameraExists=false;

        for (int camindex = 0; camindex < m_IDSCameras.length(); ++camindex) {
            auto camera =m_IDSCameras.at(camindex);
            if(camera->camID()==camid){
                cameraExists=true;
                break;
            }
        }


        if (!cameraExists)
        {
            IDSCamera* newcamera=new IDSCamera();
            newcamera->setSerialnumber(idscameralist->uci[iCamera].SerNo);
            newcamera->setCamID(camid);

            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass
            m_IDSCameras.append(newcamera);
            endInsertRows();
        }

    }



}

void IDSCameraListModel::clear()

{
    beginRemoveRows(QModelIndex(),0, rowCount(QModelIndex())-1);   // kindly provided by superclass

    m_IDSCameras.clear();

    endRemoveRows();
}

QHash<int, QByteArray> IDSCameraListModel::roleNames() const

{
    return {

        { NameRole, "name" }

    };
}

IDSCamera *IDSCameraListModel::getItemAt(int index)
{
    return m_IDSCameras.at(index);
}
