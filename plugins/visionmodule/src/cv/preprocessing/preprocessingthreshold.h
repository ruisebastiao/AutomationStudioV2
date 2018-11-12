#ifndef PREPROCESSINGTHRESHOLD_H
#define PREPROCESSINGTHRESHOLD_H

#include "preprocessing.h"

#include <QObject>

class PreProcessingThreshold : public PreProcessing
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER("serialize"))

private:

    int m_value=125;

public:
PreProcessingThreshold();
int value() const
{
    return m_value;
}
public slots:
void setValue(int value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}
signals:
void valueChanged(int value);
};

#endif // PREPROCESSINGTHRESHOLD_H
