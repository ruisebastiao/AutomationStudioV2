#ifndef QPROJECTCONTAINER_H
#define QPROJECTCONTAINER_H

#include <QQuickItem>

class QProjectContainer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString projectsFile READ projectsFile WRITE setProjectsFile NOTIFY projectsFileChanged)

public:
    QProjectContainer(QQuickItem *parent=nullptr);
    QProjectContainer(const QProjectContainer& other){ }

    QString projectsFile() const
    {
        return m_projectsFile;
    }

signals:

    void projectsFileChanged(QString projectsFile);

public slots:

void setProjectsFile(QString projectsFile)
{
    if (m_projectsFile == projectsFile)
        return;

    m_projectsFile = projectsFile;
    emit projectsFileChanged(m_projectsFile);
}

private:

QString m_projectsFile="";
};

#endif // QPROJECTCONTAINER_H
