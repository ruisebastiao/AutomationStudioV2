/****************************************************************************
**
** Copyright (C) 2014-2018 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#include "settings.h"
#include <QVariant>
#include <QDir>
#include <QQmlEngine>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSysInfo>
#include <qdebug.h>

namespace as{

Settings::Settings(QObject *parent, QString baseconfigpath)
    : QObject(parent)
{
    m_baseconfigpath=baseconfigpath;



    m_sysInfo=QSysInfo::kernelType();
    m_cpuType=QSysInfo::currentCpuArchitecture();

    // LOG_INFO("Running on "+m_sysInfo+"/"+m_cpuType);


    //    QList<QString> teste=Utilities::QtEnumsToStrings<User::UserRole>(false);

    m_projects= new ProjectsListModel();
    m_users= new UsersListModel();


}

Settings::~Settings(){

}

bool Settings::load(QString basePath)
{

    if(m_source.isEmpty()) {
        qWarning() << "Empty document: " << m_source;
        setLoaded(false);
        return false;
    }


    QFile settingsFile(basePath+'/'+m_source);
    if(!settingsFile.exists()) {
        qWarning() << "Does not exits: " << m_source;
        setLoaded(false);
        return false;
    }

    if (!settingsFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray settingsData = settingsFile.readAll();

    QJsonDocument settings(QJsonDocument::fromJson(settingsData ));

    m_settingsobject=settings.object();

    read(m_settingsobject);

    setLoaded(true);

    return true;
}

bool Settings::save()
{
    QFile saveFile(m_source);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    write(m_settingsobject);

    QJsonDocument saveDoc(m_settingsobject);


    QByteArray jsondoc = saveDoc.toJson();


    saveFile.write(jsondoc);

    //    emit settingsSaved();
    return true;

}

void Settings::updateBaseSettings()
{

}

void Settings::loadBaseSettings()
{
    QFile basesettingsFile(m_baseconfigpath);

    if(!basesettingsFile.exists()) {
        qWarning() << "Base file does not exits: " <<m_baseconfigpath;

        basesettingsFile.open(QIODevice::WriteOnly);
        QByteArray basesettingsData = basesettingsFile.readAll();

        QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

        QJsonObject settingsobject=settings.object();

        settingsobject["location"]="";
        QJsonDocument saveDoc(settingsobject);
        QByteArray json = saveDoc.toJson();
        basesettingsFile.write(json);
        basesettingsFile.close();

    }

    if (!basesettingsFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return;
    }


    QByteArray basesettingsData = basesettingsFile.readAll();

    QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

    QJsonObject settingsobject=settings.object();


    m_source=settingsobject["location"].toString();


    setBasefileLoaded(true);

    return;
}

void Settings::setBasefileLoaded(bool basefileLoaded)
{
    if (m_basefileLoaded == basefileLoaded)
        return;

    m_basefileLoaded = basefileLoaded;
    emit basefileLoadedChanged(m_basefileLoaded);

}

void Settings::read(const QJsonObject &json)
{
    setSelectedanguage(json["language"].toString());

    m_projects->clear();


    QJsonArray projectArray = json["projects"].toArray();
    for (int projectIndex = 0; projectIndex < projectArray.size(); ++projectIndex) {
        QJsonObject projectObject = projectArray[projectIndex].toObject();

        Project *project= new Project();
        project->DeSerialize(projectObject);

        m_projects->AddProject(project);

    }

    m_users->clear();

    QJsonArray usersArray = json["users"].toArray();
    for (int userIndex = 0; userIndex < usersArray.size(); ++userIndex) {
        QJsonObject userObject = usersArray[userIndex].toObject();

        User *user= new User();
        user->read(userObject);
        if(user->isDefault()){
            setCurrentUser(user);
        }
        m_users->AddUser(user);

    }

}

void Settings::write(QJsonObject &json) const
{

}



}// namespace
