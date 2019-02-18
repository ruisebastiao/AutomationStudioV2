#include "apptranslator.h"

AppTranslator::AppTranslator(QObject *parent) : QObject(parent)
{

     translator_pt = new QTranslator(this);
     translator_es = new QTranslator(this);
     translator_fr = new QTranslator(this);

}
