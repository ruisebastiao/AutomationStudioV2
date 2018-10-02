#ifndef IDSCAMERA_H
#define IDSCAMERA_H
#include <uEye.h>
#include <QObject>

class IDSCamera : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString serialnumber READ serialnumber WRITE setSerialnumber NOTIFY serialnumberChanged USER("serialize"))
    Q_PROPERTY(int camID READ camID WRITE setCamID NOTIFY camIDChanged USER("serialize"))

public:
    IDSCamera();



    QString serialnumber() const
    {
        return m_serialnumber;
    }



    HIDS* getCamID(){
        return (HIDS*)(&m_camID);
    }



    int camID() const
    {
        return m_camID;
    }

    char* frameAddress() const
    {
        return m_frameAddress;
    }

signals:
    void serialnumberChanged(QString serialnumber);
    void camIDChanged(int camID);


    void frameAddressChanged(char* frameAddress);

public slots:
    void setSerialnumber(QString serialnumber)
    {
        if (m_serialnumber == serialnumber)
            return;

        m_serialnumber = serialnumber;
        emit serialnumberChanged(m_serialnumber);
    }





    void setCamID(int camID)
    {
        if (m_camID == camID)
            return;

        m_camID = camID;
        emit camIDChanged(m_camID);
    }

    void setFrameAddress(char* frameAddress)
    {
        if (m_frameAddress == frameAddress)
            return;

        m_frameAddress = frameAddress;
        emit frameAddressChanged(m_frameAddress);
    }

private:


    QString m_serialnumber;



    int m_camID=-1;
    char* m_frameAddress=0;
};


#endif // IDSCAMERA_H
