#include "arraynode.h"

using namespace std;

ArrayNode::ArrayNode()
{
    m_type=Type::ArrayNode;
}


QQmlComponent *ArrayNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ArrayNodeItem.qml"));
    return delegate.get();

}


ArrayListModel::ArrayListModel(QObject *parent)
{

}

ArrayListModel::~ArrayListModel()
{

}

QVariant ArrayListModel::data(const QModelIndex &index, int role) const
{
    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>listsize)
    {
        return QVariant();
    }




    if (role == valueRole){



        //return QVariant::fromValue(project);
    }


    return QVariant();
}

QHash<int, QByteArray> ArrayListModel::roleNames() const
{
    return {
        { valueRole, "itemValue" }

    };
}

QVariant ArrayListModel::internalList() const
{
    return m_internalList;
}

void ArrayListModel::setInternalList(const QVariant &internalList)
{
    m_internalList = internalList;

    QVariantList teste;
    if(m_internalList.isValid()){

        teste=m_internalList.toList();

    }


    //if(strcmp(m_input1.typeName(),"std::vector<cv::Rect>"){



}

int ArrayListModel::rowCount(const QModelIndex &parent) const
{


    return listsize;

}
