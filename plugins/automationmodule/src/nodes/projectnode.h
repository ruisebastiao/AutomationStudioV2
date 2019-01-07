#ifndef PROJECTNODE_H
#define PROJECTNODE_H

#include "flownode.h"

#include <QObject>
#include <project.h>

class ProjectNode : public FlowNode
{
      Q_OBJECT

    Q_PROPERTY(QString projectProperty READ projectProperty WRITE setProjectProperty NOTIFY projectPropertyChanged USER("serialize"))
    Q_PROPERTY(Project* project READ project WRITE setProject NOTIFY projectChanged)

    Q_PROPERTY(QStringList projectProperties READ projectProperties WRITE setProjectProperties NOTIFY projectPropertiesChanged)


public:
    ProjectNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    Project* project() const
    {
        return m_project;
    }

    QStringList projectProperties() const
    {
        return m_projectProperties;
    }

    QString projectProperty() const
    {
        return m_projectProperty;
    }

public slots:
    void setProject(Project* project)
    {
        if (m_project == project)
            return;

        m_project = project;

        if(m_project){

            m_projectProperties.clear();
            for (int i = 0; i < m_project->metaObject()->propertyCount(); i++)
            {

                QMetaProperty property = m_project->metaObject()->property(i);
                const char* propName=property.name();


                if(property.isReadable() && property.isWritable() && property.revision()==2){


                    m_projectProperties.append(propName);

                }


            }
            emit projectPropertiesChanged(m_projectProperties);



        }

        emit projectChanged(m_project);
    }

    void setProjectProperties(QStringList projectProperties)
    {
        if (m_projectProperties == projectProperties)
            return;

        m_projectProperties = projectProperties;
        emit projectPropertiesChanged(m_projectProperties);
    }

    void setProjectProperty(QString projectProperty)
    {
        if (m_projectProperty == projectProperty)
            return;

        m_projectProperty = projectProperty;
        emit projectPropertyChanged(m_projectProperty);

        emit bindProjectProperty(m_project,m_projectProperty);
    }

signals:
    void projectChanged(Project* project);

    void projectPropertiesChanged(QStringList projectProperties);

    void projectPropertyChanged(QString projectProperty);

    void bindProjectProperty(Project* moduleObject,QString projectProperty);

private:

    Project* m_project=nullptr;
    QStringList m_projectProperties;
    QString m_projectProperty;
};

#endif // PROJECTNODE_H
