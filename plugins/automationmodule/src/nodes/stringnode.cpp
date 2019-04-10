#include "stringnode.h"

StringNode::StringNode()
{

    m_type=Type::StringNode;

}


QQmlComponent*  StringNode::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/StringNodeItem.qml"));
    return delegate.get();
}

void StringNode::inputsChanged(bool process){

    if(!process) return;

    if(inputType()==InputType::InputSuffix){
        setStringOutput(stringValue().value<QString>()+QVariant(m_stringInput).toString());

    }else if(inputType()==InputType::InputSerialize){
        setStringOutput(serialize_input());
    }
    else if(inputType()==InputType::InputPrefix){
        setStringOutput(m_stringInput.value<QString>()+stringValue().value<QString>());
    }
    else if(inputType()==InputType::InputExtract) {
        updateExtract();
    }
    else if(inputType()==InputType::InputCompare){
        compareStrings();
    }
    else if(inputType()==InputType::InputJoin){
        QString inputstr=m_stringInput.value<QString>();
        QString inputstr2=m_stringInput2.value<QString>();


        QString joined=m_stringInput.value<QString>().append(m_stringValue.value<QString>()).append(inputstr2);
        setStringOutput(joined);
    }
    else if(inputType()==InputType::InputParse){
        QString parsed_str;
        if(m_stringInput.isValid()==false || m_stringInput.isNull() || m_stringInput.canConvert<double>()==false){
            parsed_str="NAN";
        }
        else{
            QString strval=m_stringInput.value<QString>();
            bool valid=true;
            double converted = strval.toDouble(&valid);
            parsed_str=QString::number(converted, 'f', 2);
        }

        setStringOutput(parsed_str);
    }
    else if(inputType()==InputType::InputReadFile){
        QFile count(m_stringInput.value<QString>());

        if(count.exists()){

            if (!count.open(QFile::ReadOnly | QFile::Text)) return;
            QTextStream in(&count);
            QString content=in.readAll();
            setStringOutput(content);
            count.close();

        }


    }
    else if(inputType()==InputType::InputWriteFile){
        QFile count(m_stringInput.value<QString>());

        if(count.exists()){

            if (!count.open(QFile::WriteOnly )) return;
            QTextStream out(&count);
            out << m_stringInput2.value<QString>();
            count.close();
            setStringOutput(m_stringInput2);

        }


    }

    else if(inputType()==InputType::InputNone){
        setStringOutput(m_stringValue);

    }

}

void StringNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void StringNode::DeSerialize(QJsonObject &json)
{



    FlowNode::DeSerialize(json);

    updateports();
}

void StringNode::initializeNode(int id)
{
    FlowNode::initializeNode(id);
    updateports();
}


