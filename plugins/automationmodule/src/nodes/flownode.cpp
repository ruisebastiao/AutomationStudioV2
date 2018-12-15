#include "flownode.h"
#include "src/graphs/scenegraph.h"
#include "qautomationmodule.h"

FlowNode::FlowNode(QObject *parent):qan::Node(parent)
{



}

QVariantList FlowNode::getCommonTypes()
{
    QVariantList ret;

    int enumscount=QMetaEnum::fromType<Type>().keyCount();
    for (int i = 0; i < enumscount; ++i) {
        Type nodetype= static_cast<Type>(QMetaEnum::fromType<Type>().value(i));

        QVariantMap map;


        switch (nodetype) {

        case Type::ObjectPropertyNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Object Property");

            break;

        case Type::BarcodeReaderNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Barcode Reader");

            break;
        case Type::ProxyInputNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"In/Out Proxy");

            break;

        case Type::StringNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"String");

            break;

        case Type::WebServiceNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"WebService");

            break;

        case Type::NumericNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Numeric");

            break;

        case Type::ModulePropertyBind:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Module Property Bind");
            break;

        case Type::StringBuilderNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"String Builder");

            break;


        default:
            //                static_assert(true, "");
            break;
        }

        if(map.empty()==false)
            ret.append(map);

    }


    return ret;
}

std::ostream& operator <<(std::ostream &out, const FlowNode &c)
{
    out <<c;

    return out;
}

QDataStream& operator <<(QDataStream &stream, FlowNode &c) {

    stream<< c;
    return stream;

}

FlowNode::~FlowNode()
{
    //
    LOG_INFO()<<"Deleting node:"<<this->id()<<"|"<<this->name();
//    QAutomationModule::flownodemanager->removeNode(this);

}




QQmlComponent*  FlowNode::delegate(QQmlEngine& engine) noexcept
{

    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/FlowNode.qml"));
    return qan_FlowNode_delegate.get();
}

void FlowNode::initializeNode(int id)
{
    setId(id);

    QJsonObject jo;
    initializePorts(jo);

    setConfigsLoaded(true);

}

//void FlowNode::remove()
//{
//    emit removeNode(this);
//}

void FlowNode::initializePorts(QJsonObject &json)
{
    for (int i = 0; i < this->metaObject()->propertyCount(); i++)
    {

        QMetaProperty property = this->metaObject()->property(i);
        const char* propName=property.name();


        // INPUT PORTS => Revision 30
        if(property.revision()==30){


            FlowNodePort* newport= new FlowNodePort(this,qan::PortItem::Type::In,propName);
            if(newport){
                //                newport->setHidden(true);
                string portkey=QString::number(id()).toStdString()+"|"+propName;
                m_inPorts[portkey]=newport;
            }
            continue;
        }

        // OUTPUT PORTS => Revision 31
        if(property.revision()==31){
            FlowNodePort* newport= new FlowNodePort(this,qan::PortItem::Type::Out,propName);
            if(newport){
                //                newport->setHidden(true);
                string portkey=QString::number(id()).toStdString()+"|"+propName;
                m_outPorts[portkey]=newport;
            }

            continue;
        }
    }



    QJsonObject inPorts = json["inPorts"].toObject();
    foreach(const QString& key, inPorts.keys()) {
        string portkey=QString::number(id()).toStdString()+"|"+key.toStdString();
        FlowNodePort* port= m_inPorts.value(portkey);
        if(port){
            QJsonObject portobject=inPorts.value(key).toObject();
            port->DeSerialize(portobject);
        }
    }



    QJsonObject outPorts = json["outPorts"].toObject();
    foreach(const QString& key, outPorts.keys()) {
        string portkey=QString::number(id()).toStdString()+"|"+key.toStdString();
        FlowNodePort* port= m_outPorts.value(portkey);
        if(port){
            QJsonObject portobject=outPorts.value(key).toObject();
            port->DeSerialize(portobject);
        }
    }


}

FlowNodePort *FlowNode::getPortFromKey(QString key)
{
    string keystr=QString::number(id()).toStdString();
    keystr.append("|");
    keystr.append(key.toStdString());
    FlowNodePort* port=m_inPorts.value(keystr);
    if(port){
        return port;
    }
    return m_outPorts.value(keystr);
}


SceneGraph *FlowNode::getScenegraph() const
{
    return m_scenegraph;
}

void FlowNode::inNodeOutputChanged()
{

}

QMap<string,FlowNodePort *> FlowNode::getOutPorts() const
{
    return m_outPorts;
}

QMap<string,FlowNodePort *> FlowNode::getInPorts() const
{
    return m_inPorts;
}



void FlowNode::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);

    QJsonObject inPorts;
    QMapIterator<string, FlowNodePort*> i(this->m_inPorts);
    while (i.hasNext()) {
        i.next();


        FlowNodePort* nodeinport =i.value();

        if(nodeinport){
            QJsonObject inPort;
            nodeinport->Serialize(inPort);
            inPorts[nodeinport->getPortItem()->getId()]=inPort;
        }
        else{
            LOG_ERROR()<<*this<<"| null value from key:"<<QString::fromStdString(i.key());
        }

    }
    json["inPorts"]=inPorts;

    QJsonObject outPorts;
    QMapIterator<string, FlowNodePort*> o(this->m_outPorts);
    while (o.hasNext()) {
        o.next();


        FlowNodePort* nodeoutport =o.value();

        if(nodeoutport){
            QJsonObject outPort;
            nodeoutport->Serialize(outPort);
            outPorts[nodeoutport->getPortItem()->getId()]=outPort;
        }
        else{
            LOG_ERROR()<<*this<<"| null value from key:"<<QString::fromStdString(o.key());
        }

    }
    json["outPorts"]=outPorts;


    json["nodeX"]=getItem()->x();
    json["nodeY"]=getItem()->y();



    json["editWidth"]=editWidth();
    json["editHeight"]=editHeight();

    json["normalWidth"]= normalWidth();
    json["normalHeight"]=normalHeight();

}


void FlowNode::DeSerialize(QJsonObject &json)
{




    JsonSerializable::DeSerialize(json,this);

    this->m_scenegraph=qobject_cast<SceneGraph*>(this->getGraph());

    getItem()->setProperty("x",QVariant::fromValue(json["nodeX"].toDouble()));
    getItem()->setProperty("y",QVariant::fromValue(json["nodeY"].toDouble()));

    setNormalWidth(json["normalWidth"].toInt());
    setNormalHeight(json["normalHeight"].toInt());

    setEditWidth(json["editWidth"].toInt());

    setEditHeight(json["editHeight"].toInt());

    initializePorts(json);

//    emit QAutomationModule::flownodemanager->onFlowNodeLoaded(this);

    setConfigsLoaded(true);
}



FlowNodePort* FlowNode::getPortByID(QString id)
{

    foreach (FlowNodePort* port, m_inPorts) {
        if(port->getPortItem()->getId()==id){
            return port;
        }
    }

    foreach (FlowNodePort* port, m_outPorts) {
        if(port->getPortItem()->getId()==id){
            return port;
        }
    }

    return nullptr;
}

void FlowNode::installBehaviour(std::unique_ptr<qan::NodeBehaviour> behaviour)
{

}


