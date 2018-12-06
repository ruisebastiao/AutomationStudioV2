#ifndef FRAMEBUFFERNODE_H
#define FRAMEBUFFERNODE_H

#include <QObject>
#include <flownode.h>

#include <QtConcurrent>
#include <cv/qmat.h>




class FrameBufferListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(FrameBufferRoles)
public:
    enum FrameBufferRoles {
        MatRole = Qt::UserRole + 1

    };

    FrameBufferListModel()
    {

    }

    void indexDataChanged(int itemindex)
    {
        emit dataChanged(index(itemindex),index(itemindex));
    }

    inline int rowCount(const QModelIndex &parent) const
    {
        return m_buffers.length();
    }


    inline QHash<int, QByteArray> roleNames() const

    {
        return {

            { MatRole, "itemMat" }

        };
    }


    inline int bufferSize(){
        return m_buffers.length();
    }

    inline QVariant data(const QModelIndex &index, int role) const
    {

           //std::lock_guard<decltype(mainQueueMutex)> lg(mainQueueMutex);

        //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
        if (index.row()<0 || index.row()>=m_buffers.size())
        {
            return QVariant();
        }

        int idx=index.row();
        QMat* mat = getItemAt(idx);
        if (role == MatRole){

          return QVariant::fromValue(mat);
        }



        return QVariant();
    }


    inline QMat *getItemAt(int index) const
    {
        if(index>=m_buffers.length()){
            return nullptr;
        }
        return m_buffers.at(index);
    }

    inline void PushFrameBuffer()
    {
        beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

        m_buffers.append(new QMat());

        endInsertRows();
    }

    inline void PopFrameBuffer()
    {
        if(m_buffers.length()>0){
            beginRemoveRows(QModelIndex(), rowCount(QModelIndex())-1, rowCount(QModelIndex())-1);   // kindly provided by superclass

            m_buffers.removeLast();

            endRemoveRows();
        }
    }

    inline void SetNewSize(int newsize){
        int buffers_size=m_buffers.length();
        if(newsize>buffers_size){
            for (int var = 0; var < newsize-buffers_size; ++var) {
                PushFrameBuffer();
            }
        }
        else if(newsize<buffers_size){
            for (int var = 0; var <buffers_size-newsize; ++var) {
                PopFrameBuffer();
            }
        }
    }


private:

    QList<QMat*> m_buffers;
};

class FrameBufferNode : public FlowNode
{
    Q_OBJECT


    /// IN ports
    Q_PROPERTY(QVariant frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged REVISION 30)


    Q_PROPERTY(QVariant readNextFrame READ readNextFrame WRITE setReadNextFrame NOTIFY readNextFrameChanged REVISION 30)

    Q_PROPERTY(QVariant resetIndexes READ resetIndexes WRITE setResetIndexes NOTIFY resetIndexesChanged REVISION 30)

    Q_PROPERTY(QVariant numBuffers READ numBuffers WRITE setNumBuffers NOTIFY numBuffersChanged USER("serialize") REVISION 30)



    /////OUT ports

    Q_PROPERTY(QVariant frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged REVISION 31)


    Q_PROPERTY(QVariant frameStored READ frameStored WRITE setFrameStored NOTIFY frameStoredChanged REVISION 31)


    Q_PROPERTY(QVariant bufferFull READ bufferFull WRITE setBufferFull NOTIFY bufferFullChanged REVISION 31)




    Q_PROPERTY(QVariant frameBuffers READ frameBuffers WRITE setFrameBuffers NOTIFY frameBuffersChanged  REVISION 31)

    Q_PROPERTY(int writeIndex READ writeIndex WRITE setWriteIndex NOTIFY writeIndexChanged)
    Q_PROPERTY(int readIndex READ readIndex WRITE setReadIndex NOTIFY readIndexChanged)

    Q_PROPERTY(bool autoIncrementWriteIndex READ autoIncrementWriteIndex WRITE setAutoIncrementWriteIndex NOTIFY autoIncrementWriteIndexChanged USER("serialize"))
    Q_PROPERTY(bool autoIncrementReadIndex READ autoIncrementReadIndex WRITE setAutoIncrementReadIndex NOTIFY autoIncrementReadIndexChanged USER("serialize"))

private:

    QVariant m_numBuffers=QVariant::fromValue(0);
    QVariant m_frameSink=QVariant::fromValue(new QMat());
    QVariant m_frameSource=QVariant::fromValue(new QMat());

    QVariant m_frameStored=QVariant::fromValue(false);
    QVariant m_frameBuffers=QVariant::fromValue(new FrameBufferListModel());

    QVariant m_readNextFrame=QVariant::fromValue(false);

    int m_writeIndex=0;

    int m_readIndex=0;

    bool m_autoIncrementWriteIndex=false;

    bool m_autoIncrementReadIndex=false;

    bool m_fullBufferReaded=false;


    QVariant m_bufferFull=QVariant::fromValue(false);


    QVariant m_resetIndexes=QVariant::fromValue(false);

public:
    FrameBufferNode();

    Q_INVOKABLE void processCurrent();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    QVariant numBuffers() const
    {
        return m_numBuffers;
    }

    QVariant frameSink() const
    {
        return m_frameSink;
    }


    QVariant frameSource() const
    {
        return m_frameSource;
    }


    QVariant frameStored() const
    {
        return m_frameStored;
    }


    QVariant frameBuffers() const
    {
        return m_frameBuffers;
    }

    int writeIndex() const
    {
        return m_writeIndex;
    }

    int readIndex() const
    {
        return m_readIndex;
    }

    bool autoIncrementWriteIndex() const
    {
        return m_autoIncrementWriteIndex;
    }

    bool autoIncrementReadIndex() const
    {
        return m_autoIncrementReadIndex;
    }

    QVariant readNextFrame() const
    {
        return m_readNextFrame;
    }


    QVariant bufferFull() const
    {
        return m_bufferFull;
    }


public slots:
    void setNumBuffers(QVariant numBuffers)
    {

        if(m_numBuffers.value<int>()==numBuffers.value<int>()){
            return;
        }

        m_numBuffers = numBuffers;
        int newsize=m_numBuffers.value<int>();
        FrameBufferListModel* framebuffers=m_frameBuffers.value<FrameBufferListModel*>();
        framebuffers->SetNewSize(newsize);
        emit numBuffersChanged(m_numBuffers);
    }

    void setFrameSink(QVariant  frameSink)
    {


        m_frameSink = frameSink;
        emit frameSinkChanged(m_frameSink);
    }


    void setFrameSource(QVariant frameSource);


    void setFrameStored(QVariant frameStored)
    {

        m_frameStored = frameStored;
        emit frameStoredChanged(m_frameStored);
    }


    void setFrameBuffers(QVariant frameBuffers)
    {


        m_frameBuffers = frameBuffers;
        emit frameBuffersChanged(m_frameBuffers);
    }

    void setWriteIndex(int writeIndex)
    {
        if (m_writeIndex == writeIndex)
            return;

        m_writeIndex = writeIndex;

        if(m_writeIndex>=m_numBuffers.value<int>()){
            setBufferFull(true);
            m_writeIndex=0;
        }
        emit writeIndexChanged(m_writeIndex);
    }

    void setReadIndex(int readIndex)
    {
        if (m_readIndex == readIndex)
            return;

        m_readIndex = readIndex;

        if(m_readIndex>=m_numBuffers.value<int>()){
            m_fullBufferReaded=true;
            m_readIndex=0;
        }

        emit readIndexChanged(m_readIndex);
    }

    void setAutoIncrementWriteIndex(bool autoIncrementWriteIndex)
    {
        if (m_autoIncrementWriteIndex == autoIncrementWriteIndex)
            return;

        m_autoIncrementWriteIndex = autoIncrementWriteIndex;
        emit autoIncrementWriteIndexChanged(m_autoIncrementWriteIndex);
    }

    void setAutoIncrementReadIndex(bool autoIncrementReadIndex)
    {
        if (m_autoIncrementReadIndex == autoIncrementReadIndex)
            return;

        m_autoIncrementReadIndex = autoIncrementReadIndex;
        emit autoIncrementReadIndexChanged(m_autoIncrementReadIndex);
    }

    void setReadNextFrame(QVariant readNextFrame);

    void setBufferFull(QVariant bufferFull)
    {


        m_bufferFull = bufferFull;
        if(m_bufferFull.value<bool>()){
            m_fullBufferReaded=false;
        }
        emit bufferFullChanged(m_bufferFull);
    }


    void setResetIndexes(QVariant resetIndexes)
    {

        m_resetIndexes = resetIndexes;
        emit resetIndexesChanged(m_resetIndexes);
        if(m_resetIndexes.value<bool>()){
            setWriteIndex(0);
            setReadIndex(0);
            m_resetIndexes=QVariant::fromValue(false);
        }
    }

signals:
    void numBuffersChanged(QVariant numBuffers);

    void frameSinkChanged(QVariant frameSink);

    void frameSourceChanged(QVariant frameSource);

    void frameStoredChanged(QVariant frameStored);
    void frameBuffersChanged(QVariant frameBuffers);
    void writeIndexChanged(int writeIndex);
    void readIndexChanged(int readIndex);
    void autoIncrementWriteIndexChanged(bool autoIncrementWriteIndex);
    void autoIncrementReadIndexChanged(bool autoIncrementReadIndex);
    void readNextFrameChanged(QVariant readNextFrame);
    void bufferFullChanged(QVariant bufferFull);

    // FlowNode interface
    void resetIndexesChanged(QVariant resetIndexes);

public:

QVariant resetIndexes() const
{
    return m_resetIndexes;
}
};

#endif // FRAMEBUFFERNODE_H
