#ifndef APPTRANSLATOR_H
#define APPTRANSLATOR_H

#include <QObject>
#include <QtGui>
#include <QtQuick>
#include <Logger.h>


class AppTranslator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentLanguage READ currentLanguage WRITE setCurrentLanguage NOTIFY currentLanguageChanged)
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY currentLanguageChanged)

    Q_PROPERTY(QString filesLocation READ filesLocation WRITE setFilesLocation NOTIFY filesLocationChanged)


    QString m_currentLanguage="pt";

private:
    QTranslator *translator_pt;
    QTranslator *translator_fr;
    QTranslator *translator_es;
    QString m_emptyString="";

    QString m_filesLocation;

public:
    explicit AppTranslator(QObject *parent = 0);


    QString currentLanguage() const
    {
        return m_currentLanguage;
    }

    QString getEmptyString() const
    {
        return m_emptyString;
    }

    QString filesLocation() const
    {
        return m_filesLocation;
    }

signals:

    void currentLanguageChanged(QString currentLanguage);

    void filesLocationChanged(QString filesLocation);

public slots:
    void setCurrentLanguage(QString currentLanguage)
    {
        if (m_currentLanguage == currentLanguage)
            return;

        LOG_INFO()<<"Changing language to:"<<currentLanguage;

        if(currentLanguage.contains("fr")) {
            bool loadok=translator_fr->load(filesLocation()+"/tr_fr", ".");
            if(loadok){
                qApp->installTranslator(translator_fr);
            }
            else{
                LOG_INFO()<<"language file not found:"<<filesLocation()+"/tr_fr";
            }
        }

        if(currentLanguage.contains("es")) {
            bool loadok=translator_es->load(filesLocation()+"/tr_es", ".");
            if(loadok){
                qApp->installTranslator(translator_es);
            }
            else{
                LOG_INFO()<<"language file not found:"<<filesLocation()+"/tr_es";
            }
        }


        if(currentLanguage.contains("pt")) {
            bool loadok=translator_pt->load(filesLocation()+"/tr_pt", ".");
            if(loadok){
                qApp->installTranslator(translator_pt);
            }
            else{
                LOG_INFO()<<"language file not found:"<<filesLocation()+"/tr_pt";
            }
        }


        if(currentLanguage.contains("en")) {
            qApp->removeTranslator(translator_pt);
            qApp->removeTranslator(translator_fr);
            qApp->removeTranslator(translator_es);
        }


        m_currentLanguage = currentLanguage;
        emit currentLanguageChanged(currentLanguage);
    }
    void setFilesLocation(QString filesLocation)
    {
        if (m_filesLocation == filesLocation)
            return;

        m_filesLocation = filesLocation;
        emit filesLocationChanged(filesLocation);
    }
};

#endif // APPTRANSLATOR_H
