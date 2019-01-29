#ifndef ARRAYNODE_H
#define ARRAYNODE_H

#include "flownode.h"

class ArrayListModel : public QAbstractListModel
{
public:
    enum MyRoles {
        valueRole = Qt::UserRole + 1
    };

    ArrayListModel(QObject *parent = nullptr);
    ~ArrayListModel();


private:

    QVariant m_internalList=QVariant();

    int listsize=-1;

    // QAbstractItemModel interface
public:

    QVariant data(const QModelIndex &index, int role) const override;


    QHash<int, QByteArray> roleNames() const override;
    QVariant internalList() const;
    void setInternalList(const QVariant &internalList);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
};

class ArrayNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant array READ array WRITE setArray NOTIFY arrayChanged REVISION 30)
    Q_PROPERTY(QVariant arrayItem READ arrayItem WRITE setArrayItem NOTIFY arrayItemChanged REVISION 31)

    Q_PROPERTY(int arrayIndex READ arrayIndex WRITE setArrayIndex NOTIFY arrayIndexChanged USER("serialize"))

//    Q_PROPERTY(ArrayListModel* listArray READ listArray WRITE setListArray NOTIFY listArrayChanged)


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


    ArrayListModel* listArray() const
    {
        return m_listArray;
    }

public slots:
    void setArray(QVariant array)
    {
        if (m_array == array)
            return;


        m_array = array;


        m_listArray->setInternalList(m_array);
        emit arrayChanged(m_array);
    }

    void setArrayItem(QVariant arrayItem)
    {
        if (m_arrayItem == arrayItem)
            return;

        m_arrayItem = arrayItem;
        emit arrayItemChanged(m_arrayItem);
    }

    void setArrayIndex(int arrayIndex)
    {
        if (m_arrayIndex == arrayIndex)
            return;

        m_arrayIndex = arrayIndex;
        emit arrayIndexChanged(m_arrayIndex);
    }


    void setListArray(ArrayListModel* listArray)
    {
        if (m_listArray == listArray)
            return;

        m_listArray = listArray;
        emit listArrayChanged(m_listArray);
    }

signals:
    void arrayChanged(QVariant array);

    void arrayItemChanged(QVariant arrayItem);

    void arrayIndexChanged(int arrayIndex);


    void listArrayChanged(ArrayListModel* listArray);

private:

    QVariant m_array=QVariant();
    QVariant m_arrayItem=QVariant();
    int m_arrayIndex=-1;

    ArrayListModel* m_listArray= new ArrayListModel();
};

#endif // ARRAYNODE_H
