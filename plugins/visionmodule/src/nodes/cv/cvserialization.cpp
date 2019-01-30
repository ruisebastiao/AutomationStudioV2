#include "cvserialization.h"

#include <qjsondocument.h>
#include <qjsonobject.h>

using namespace cv;
using namespace std;

cvSerialization::cvSerialization(QObject*)
{

}



QString cvSerialization::serializer(QVariant value) const{

    if(value.canConvert<QVariantList>()){

    }
    else if(value.canConvert<Rect>()){
        Rect rect=value.value<Rect>();
        QJsonObject center;





        center=QJsonObject{ {"x", rect.x+rect.width/2},{"y", rect.y+rect.height/2} };


        QJsonObject serializedObject{
            {"x", rect.x},
            {"y", rect.y},
            {"width", rect.width},
            {"height", rect.height},
            {"center",center},
        };

        QJsonDocument serializedDoc(serializedObject);



        return serializedDoc.toJson(QJsonDocument::Indented);
    }
    return "";
}
