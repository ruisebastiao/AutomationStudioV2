#ifndef STRINGBUILDERNODE_H
#define STRINGBUILDERNODE_H

#include "flownode.h"



class StringBuilderNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant in READ in WRITE setIn NOTIFY inChanged REVISION 30)
    Q_PROPERTY(QVariant clear READ clear WRITE setClear NOTIFY clearChanged REVISION 30)

    Q_PROPERTY(QVariant out READ out WRITE setOut NOTIFY outChanged REVISION 31)
    Q_PROPERTY(QString extractProperty READ extractProperty WRITE setExtractProperty NOTIFY extractPropertyChanged USER("serializable"))
    Q_PROPERTY(QString separator READ separator WRITE setSeparator NOTIFY separatorChanged USER("serializable"))



public:
    StringBuilderNode();
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    QVariant in() const
    {
        return m_in;
    }

    QVariant out() const
    {
        return m_out;
    }

    QString extractProperty() const
    {
        return m_extractProperty;
    }

    QString separator() const
    {
        return m_separator;
    }

    QVariant clear() const
    {
        return m_clear;
    }

public slots:
    void setIn(QVariant in)
    {


        m_in = in;
        emit inChanged(m_in);

        if(extractProperty()!=""){

            QObject * obj = qvariant_cast<QObject *>(m_in);

            if(obj){
                int index= obj->metaObject()->indexOfProperty(qPrintable(extractProperty()));
                if(index>=0){
                    QMetaProperty prop=obj->metaObject()->property(index);

                    QVariant val=prop.read(obj);

                    setOut(val.toString());
                }
            }
        }
        else{
            setOut(in.toString());
        }
    }

    void setOut(QVariant out)
    {

        if(out.isValid()){


            QString outstr=out.value<QString>();
            QString joinedstr=m_out.value<QString>();
            if(outstr.isEmpty()==false){
                joinedstr=joinedstr+separator()+outstr;
                m_out = QVariant::fromValue(joinedstr);
                emit outChanged(m_out);
            }
        }
    }

    void setExtractProperty(QString extractProperty)
    {
        if (m_extractProperty == extractProperty)
            return;

        m_extractProperty = extractProperty;
        emit extractPropertyChanged(m_extractProperty);
    }

    void setSeparator(QString separator)
    {
        if (m_separator == separator)
            return;

        m_separator = separator;
        emit separatorChanged(m_separator);
    }

    void setClear(QVariant clear)
    {


        m_clear = clear;
        if(m_clear.value<bool>()){
            m_out = QVariant::fromValue(QString(""));
            emit outChanged(m_out);
            m_clear=false;
        }
        emit clearChanged(m_clear);
    }

signals:
    void inChanged(QVariant in);

    void outChanged(QVariant out);

    void extractPropertyChanged(QString extractProperty);

    void separatorChanged(QString separator);

    void clearChanged(QVariant clear);

private:


    QVariant m_in=QVariant::fromValue(QString(""));
    QVariant m_out=QVariant::fromValue(QString(""));
    QString m_extractProperty="";
    QString m_separator="|";
    QVariant m_clear=QVariant::fromValue(false);
};

#endif // STRINGBUILDERNODE_H
