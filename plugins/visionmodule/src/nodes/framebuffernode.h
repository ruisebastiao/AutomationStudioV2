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
    Q_PROPERTY(QMat* frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged REVISION 30)


    Q_PROPERTY(bool readNextFrame READ readNextFrame WRITE setReadNextFrame NOTIFY readNextFrameChanged REVISION 30)



    Q_PROPERTY(int numBuffers READ numBuffers WRITE setNumBuffers NOTIFY numBuffersChanged USER("serialize") REVISION 30)



    /////OUT ports

    Q_PROPERTY(QMat* frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged REVISION 31)


    Q_PROPERTY(bool frameStored READ frameStored WRITE setFrameStored NOTIFY frameStoredChanged REVISION 31)


    Q_PROPERTY(bool bufferFull READ bufferFull WRITE setBufferFull NOTIFY bufferFullChanged REVISION 31)




    Q_PROPERTY(FrameBufferListModel* frameBuffers READ frameBuffers WRITE setFrameBuffers NOTIFY frameBuffersChanged  REVISION 31)

    Q_PROPERTY(int writeIndex READ writeIndex WRITE setWriteIndex NOTIFY writeIndexChanged)
    Q_PROPERTY(int readIndex READ readIndex WRITE setReadIndex NOTIFY readIndexChanged)

    Q_PROPERTY(bool autoIncrementWriteIndex READ autoIncrementWriteIndex WRITE setAutoIncrementWriteIndex NOTIFY autoIncrementWriteIndexChanged USER("serialize"))
    Q_PROPERTY(bool autoIncrementReadIndex READ autoIncrementReadIndex WRITE setAutoIncrementReadIndex NOTIFY autoIncrementReadIndexChanged USER("serialize"))

private:
    int m_numBuffers=0;
    QMat* m_frameSink=new QMat();

    QMat* m_frameSource=nullptr;


    bool m_frameStored=false;


    FrameBufferListModel* m_frameBuffers=nullptr;

    int m_writeIndex=0;

    int m_readIndex=0;

    bool m_autoIncrementWriteIndex=false;

    bool m_autoIncrementReadIndex=false;

    bool m_readNextFrame=false;
    bool m_fullBufferReaded=false;


    bool m_bufferFull=false;


public:
    FrameBufferNode();

    Q_INVOKABLE void processCurrent();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    int numBuffers() const
    {
        return m_numBuffers;
    }

    QMat* frameSink() const
    {
        return m_frameSink;
    }


    QMat* frameSource() const
    {
        return m_frameSource;
    }


    bool frameStored() const
    {
        return m_frameStored;
    }


    FrameBufferListModel* frameBuffers() const
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

    bool readNextFrame() const
    {
        return m_readNextFrame;
    }


    bool bufferFull() const
    {
        return m_bufferFull;
    }


public slots:
    void setNumBuffers(int numBuffers)
    {
        if (m_numBuffers == numBuffers)
            return;

        m_numBuffers = numBuffers;
        m_frameBuffers->SetNewSize(numBuffers);
        emit numBuffersChanged(m_numBuffers);
    }

    void setFrameSink(QMat* frameSink)
    {


        m_frameSink = frameSink;
        emit frameSinkChanged(m_frameSink);
    }


    void setFrameSource(QMat* frameSource);


    void setFrameStored(bool frameStored)
    {

        m_frameStored = frameStored;
        emit frameStoredChanged(m_frameStored);
    }


    void setFrameBuffers(FrameBufferListModel* frameBuffers)
    {
        if (m_frameBuffers == frameBuffers)
            return;

        m_frameBuffers = frameBuffers;
        emit frameBuffersChanged(m_frameBuffers);
    }

    void setWriteIndex(int writeIndex)
    {
        if (m_writeIndex == writeIndex)
            return;

        m_writeIndex = writeIndex;
        if(m_writeIndex>=m_numBuffers){
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

        if(m_readIndex>=m_numBuffers){
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

    void setReadNextFrame(bool readNextFrame);

    void setBufferFull(bool bufferFull)
    {


        m_bufferFull = bufferFull;
        if(m_bufferFull){
            m_fullBufferReaded=false;
        }
        emit bufferFullChanged(m_bufferFull);
    }


signals:
    void numBuffersChanged(int numBuffers);

    void frameSinkChanged(QMat* frameSink);

    void frameSourceChanged(QMat* frameSource);

    void frameStoredChanged(bool frameStored);
    void frameBuffersChanged(FrameBufferListModel* frameBuffers);
    void writeIndexChanged(int writeIndex);
    void readIndexChanged(int readIndex);
    void autoIncrementWriteIndexChanged(bool autoIncrementWriteIndex);
    void autoIncrementReadIndexChanged(bool autoIncrementReadIndex);
    void readNextFrameChanged(bool readNextFrame);
    void bufferFullChanged(bool bufferFull);

    // FlowNode interface
public:
    
};

#endif // FRAMEBUFFERNODE_H
