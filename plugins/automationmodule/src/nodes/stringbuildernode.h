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

    Q_PROPERTY(int stringsAdded READ stringsAdded WRITE setStringsAdded NOTIFY stringsAddedChanged)
    Q_PROPERTY(int stringsToComplete READ stringsToComplete WRITE setStringsToComplete NOTIFY stringsToCompleteChanged USER("serializable"))


    Q_PROPERTY(QVariant completed READ completed WRITE setCompleted NOTIFY completedChanged REVISION 31)

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

    int stringsAdded() const
    {
        return m_stringsAdded;
    }

    int stringsToComplete() const
    {
        return m_stringsToComplete;
    }

    QVariant completed() const
    {
        return m_completed;
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

                joinedstr=joinedstr+outstr+separator();
                m_out = QVariant::fromValue(joinedstr);
                emit outChanged(m_out);
                setStringsAdded(m_stringsAdded+1);
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
        setStringsAdded(0);
        emit clearChanged(m_clear);
    }



    void setStringsToComplete(int stringsToComplete)
    {
        if (m_stringsToComplete == stringsToComplete)
            return;

        m_stringsToComplete = stringsToComplete;
        emit stringsToCompleteChanged(m_stringsToComplete);
    }

    void setCompleted(QVariant completed)
    {


        m_completed = completed;
        emit completedChanged(m_completed);

        Utilities::NonBlockingWait(500);

        m_completed = false;
        emit completedChanged(m_completed);
    }

signals:
    void inChanged(QVariant in);

    void outChanged(QVariant out);

    void extractPropertyChanged(QString extractProperty);

    void separatorChanged(QString separator);

    void clearChanged(QVariant clear);

    void stringsAddedChanged(int stringsAdded);

    void stringsToCompleteChanged(int stringsToComplete);

    void completedChanged(QVariant completed);

private:


    QVariant m_in=QVariant::fromValue(QString(""));
    QVariant m_out=QVariant::fromValue(QString(""));
    QString m_extractProperty="";
    QString m_separator="|";
    QVariant m_clear=QVariant::fromValue(false);
    int m_stringsAdded=0;
    int m_stringsToComplete=1;
    QVariant m_completed=QVariant::fromValue(false);

    void setStringsAdded(int stringsAdded)
    {
        if (m_stringsAdded == stringsAdded)
            return;

        m_stringsAdded = stringsAdded;
        emit stringsAddedChanged(m_stringsAdded);

        if(m_stringsAdded==m_stringsToComplete){
            setCompleted(true);
        }
    }

};

#endif // STRINGBUILDERNODE_H
