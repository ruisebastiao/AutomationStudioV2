#ifndef ARRAYNODE_H
#define ARRAYNODE_H

#include "flownode.h"

class ArrayNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant array READ array WRITE setArray NOTIFY arrayChanged REVISION 30)
    Q_PROPERTY(QVariant arrayItem READ arrayItem WRITE setArrayItem NOTIFY arrayItemChanged REVISION 31)

    Q_PROPERTY(int arrayIndex READ arrayIndex WRITE setArrayIndex NOTIFY arrayIndexChanged USER("serialize"))

    Q_PROPERTY(QVariantList arrayList READ arrayList WRITE setArrayList NOTIFY arrayListChanged)



public:
    ArrayNode();
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    QVariant array() const
    {
        return m_array;
    }

    QVariant arrayItem() const
    {
        return m_arrayItem;
    }

    int arrayIndex() const
    {
        return m_arrayIndex;
    }



    QVariantList arrayList() const
    {
        return m_arrayList;
    }

public slots:
    void setArray(QVariant array)
    {



        m_array = array;


        QVariantList arraylist=m_array.value<QVariantList>();

        setArrayList(arraylist);

        emit arrayChanged(m_array);

        if(m_arrayIndex<m_arrayList.length() && m_arrayIndex>=0){
            setArrayItem(m_arrayList.at(m_arrayIndex));
        }
        else{
            setArrayItem(QVariant());
        }


    }

    void setArrayItem(QVariant arrayItem)
    {


        m_arrayItem = arrayItem;
        emit arrayItemChanged(m_arrayItem);
    }

    void setArrayIndex(int arrayIndex)
    {
        if (m_arrayIndex == arrayIndex)
            return;

        m_arrayIndex = arrayIndex;

        if(m_arrayIndex<m_arrayList.length() && m_arrayIndex>=0){
            setArrayItem(m_arrayList.at(m_arrayIndex));
        }
        else{
            setArrayItem(QVariant());
        }
        emit arrayIndexChanged(m_arrayIndex);
    }



    void setArrayList(QVariantList arrayList)
    {

        m_arrayList = arrayList;
        emit arrayListChanged(m_arrayList);
    }

signals:
    void arrayChanged(QVariant array);

    void arrayItemChanged(QVariant arrayItem);

    void arrayIndexChanged(int arrayIndex);




    void arrayListChanged(QVariantList arrayList);

private:

    QVariant m_array=QVariant();
    QVariant m_arrayItem=QVariant();
    int m_arrayIndex=-1;


    QVariantList m_arrayList;
};

#endif // ARRAYNODE_H
