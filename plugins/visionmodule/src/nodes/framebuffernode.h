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
                PushFrameBuffer();
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
    Q_PROPERTY(QMat* frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged )
    Q_PROPERTY(FlowNodePort* frameSourcePort READ frameSourcePort WRITE setFrameSourcePort NOTIFY frameSourcePortChanged USER("serialize"))

    Q_PROPERTY(bool readNextFrame READ readNextFrame WRITE setReadNextFrame NOTIFY readNextFrameChanged )
    Q_PROPERTY(FlowNodePort* readNextFramePort READ readNextFramePort WRITE setReadNextFramePort NOTIFY readNextFramePortChanged USER("serialize"))


    Q_PROPERTY(int numBuffers READ numBuffers WRITE setNumBuffers NOTIFY numBuffersChanged USER("serialize"))
    Q_PROPERTY(FlowNodePort* numBuffersPort READ numBuffersPort WRITE setNumBuffersPort NOTIFY numBuffersPortChanged USER("serialize"))


    /////OUT ports

    Q_PROPERTY(QMat* frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged)
    Q_PROPERTY(FlowNodePort* frameSinkPort READ frameSinkPort WRITE setFrameSinkPort NOTIFY frameSinkPortChanged USER("serialize"))

    Q_PROPERTY(bool frameStored READ frameStored WRITE setFrameStored NOTIFY frameStoredChanged)
    Q_PROPERTY(FlowNodePort* frameStoredPort READ frameStoredPort WRITE setFrameStoredPort NOTIFY frameStoredChanged USER("serialize"))

    Q_PROPERTY(bool bufferFull READ bufferFull WRITE setBufferFull NOTIFY bufferFullChanged)
    Q_PROPERTY(FlowNodePort* bufferFullPort READ bufferFullPort WRITE setBufferFullPort NOTIFY bufferFullChanged USER("serialize"))



    Q_PROPERTY(FrameBufferListModel* frameBuffers READ frameBuffers WRITE setFrameBuffers NOTIFY frameBuffersChanged)

    Q_PROPERTY(int writeIndex READ writeIndex WRITE setWriteIndex NOTIFY writeIndexChanged)
    Q_PROPERTY(int readIndex READ readIndex WRITE setReadIndex NOTIFY readIndexChanged)

    Q_PROPERTY(bool autoIncrementWriteIndex READ autoIncrementWriteIndex WRITE setAutoIncrementWriteIndex NOTIFY autoIncrementWriteIndexChanged USER("serialize"))
    Q_PROPERTY(bool autoIncrementReadIndex READ autoIncrementReadIndex WRITE setAutoIncrementReadIndex NOTIFY autoIncrementReadIndexChanged USER("serialize"))

private:
    int m_numBuffers=0;

    FlowNodePort* m_numBuffersPort=nullptr;

    QMat* m_frameSink=new QMat();

    FlowNodePort* m_frameSinkPort=nullptr;
    QMat* m_frameSource=nullptr;

    FlowNodePort* m_frameSourcePort=nullptr;

    bool m_frameStored=false;

    FlowNodePort* m_frameStoredPort=nullptr;

    FrameBufferListModel* m_frameBuffers=nullptr;

    int m_writeIndex=0;

    int m_readIndex=0;

    bool m_autoIncrementWriteIndex=false;

    bool m_autoIncrementReadIndex=false;

    bool m_readNextFrame=false;

    FlowNodePort* m_readNextFramePort=nullptr;

    bool m_bufferFull=false;

    FlowNodePort* m_bufferFullPort=nullptr;

public:
    FrameBufferNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    int numBuffers() const
    {
        return m_numBuffers;
    }
    FlowNodePort* numBuffersPort() const
    {
        return m_numBuffersPort;
    }

    QMat* frameSink() const
    {
        return m_frameSink;
    }

    FlowNodePort* frameSinkPort() const
    {
        return m_frameSinkPort;
    }

    QMat* frameSource() const
    {
        return m_frameSource;
    }

    FlowNodePort* frameSourcePort() const
    {
        return m_frameSourcePort;
    }

    bool frameStored() const
    {
        return m_frameStored;
    }

    FlowNodePort* frameStoredPort() const
    {
        return m_frameStoredPort;
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

    FlowNodePort* readNextFramePort() const
    {
        return m_readNextFramePort;
    }

    bool bufferFull() const
    {
        return m_bufferFull;
    }

    FlowNodePort* bufferFullPort() const
    {
        return m_bufferFullPort;
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
    void setNumBuffersPort(FlowNodePort* numBuffersPort)
    {
        if (m_numBuffersPort == numBuffersPort)
            return;

        m_numBuffersPort = numBuffersPort;
        emit numBuffersPortChanged(m_numBuffersPort);
    }

    void setFrameSink(QMat* frameSink)
    {


        m_frameSink = frameSink;
        emit frameSinkChanged(m_frameSink);
    }

    void setFrameSinkPort(FlowNodePort* frameSinkPort)
    {
        if (m_frameSinkPort == frameSinkPort)
            return;

        m_frameSinkPort = frameSinkPort;
        emit frameSinkPortChanged(m_frameSinkPort);
    }

    void setFrameSource(QMat* frameSource);

    void setFrameSourcePort(FlowNodePort* frameSourcePort)
    {
        if (m_frameSourcePort == frameSourcePort)
            return;

        m_frameSourcePort = frameSourcePort;
        emit frameSourcePortChanged(m_frameSourcePort);
    }

    void setFrameStored(bool frameStored)
    {

        m_frameStored = frameStored;
        emit frameStoredChanged(m_frameStored);
    }

    void setFrameStoredPort(FlowNodePort* frameStoredPort)
    {
        if (m_frameStoredPort == frameStoredPort)
            return;

        m_frameStoredPort = frameStoredPort;
        emit frameStoredChanged(m_frameStoredPort);


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

    void setReadNextFramePort(FlowNodePort* readNextFramePort)
    {
        if (m_readNextFramePort == readNextFramePort)
            return;

        m_readNextFramePort = readNextFramePort;
        emit readNextFramePortChanged(m_readNextFramePort);
    }

    void setBufferFull(bool bufferFull)
    {


        m_bufferFull = bufferFull;
        emit bufferFullChanged(m_bufferFull);
    }

    void setBufferFullPort(FlowNodePort* bufferFullPort)
    {
        if (m_bufferFullPort == bufferFullPort)
            return;

        m_bufferFullPort = bufferFullPort;
        emit bufferFullChanged(m_bufferFullPort);
    }

signals:
    void numBuffersChanged(int numBuffers);
    void numBuffersPortChanged(FlowNodePort* numBuffersPort);
    void frameSinkChanged(QMat* frameSink);
    void frameSinkPortChanged(FlowNodePort* frameSinkPort);
    void frameSourceChanged(QMat* frameSource);
    void frameSourcePortChanged(FlowNodePort* frameSourcePort);
    void frameStoredChanged(bool frameStored);
    void frameBuffersChanged(FrameBufferListModel* frameBuffers);
    void writeIndexChanged(int writeIndex);
    void readIndexChanged(int readIndex);
    void autoIncrementWriteIndexChanged(bool autoIncrementWriteIndex);
    void autoIncrementReadIndexChanged(bool autoIncrementReadIndex);
    void readNextFrameChanged(bool readNextFrame);
    void readNextFramePortChanged(FlowNodePort* readNextFramePort);
    void bufferFullChanged(bool bufferFull);
};

#endif // FRAMEBUFFERNODE_H
