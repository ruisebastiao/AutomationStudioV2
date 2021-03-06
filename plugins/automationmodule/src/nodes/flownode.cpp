#include "flownode.h"
#include "src/graphs/scenegraph.h"
#include "qautomationmodule.h"


FlowNode::FlowNode(QObject *parent):qan::Node(parent)
{



    //    return typeinfo;


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

    QMapIterator<string,FlowNodePort*> o(this->m_inPorts);
    while (o.hasNext()) {
        o.next();


        FlowNodePort* inport =o.value();

        if(inport){
            if(inport->getPortItem()->getInEdgeItems().size()>0){
                auto edgitem=inport->getPortItem()->getInEdgeItems().at(0);
                if(edgitem){
                    edgitem->deleteLater();
                }

            }

        }


    }

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
    initializePorts();
    setConfigsLoaded(true);

}

void FlowNode::remove()
{
    //    emit removeNode(this);
    this->getGraph()->removeNode(this);
}



FlowNodePort* FlowNode::createPort(QString portID,qan::PortItem::Type port_type){

    FlowNodePort* newport=nullptr;
    if(port_type==qan::PortItem::Type::In){


        newport= new FlowNodePort(this,port_type,portID);
        if(newport){
            //                newport->setHidden(true);
            string portkey=QString::number(id()).toStdString()+"|"+portID.toStdString();
            m_inPorts[portkey]=newport;
        }

    }

    // OUTPUT PORTS => Revision 31
    if(port_type==qan::PortItem::Type::Out){
        newport= new FlowNodePort(this,qan::PortItem::Type::Out,portID);
        if(newport){
            //                newport->setHidden(true);
            string portkey=QString::number(id()).toStdString()+"|"+portID.toStdString();
            m_outPorts[portkey]=newport;
        }

    }

    return newport;
}

QString FlowNode::typeInfo() const
{
    QString typeinfo="";
    const QMetaObject* metaobject=metaObject();
    while(metaobject){

        QString classname=metaobject->className();

        if(classname=="FlowNode"){
            break;
        }

        if(typeinfo!=""){
            typeinfo+="::";
        }
        typeinfo+=classname;

        if(metaobject==metaObject()->superClass()){
            break;
        }
        metaobject=metaObject()->superClass();
    }
    return typeinfo;
}




void FlowNode::initializePorts()
{

    if(!m_portsInitialized){

        for (int i = 0; i < this->metaObject()->propertyCount(); i++)
        {

            QMetaProperty property = this->metaObject()->property(i);
            const char* propName=property.name();


            // INPUT PORTS => Revision 30
            if(property.revision()==30){

                createPort(propName,qan::PortItem::Type::In);

                continue;
            }

            // OUTPUT PORTS => Revision 31
            if(property.revision()==31){
                createPort(propName,qan::PortItem::Type::Out);

                continue;
            }
        }
        setPortsInitialized(true);

    }


}

FlowNodePort *FlowNode::getPortFromKey(QString key) const
{
    string keystr=QString::number(id()).toStdString();
    keystr.append("|");
    keystr.append(key.toStdString());
    FlowNodePort* port=m_inPorts.value(keystr,nullptr);
    if(port){
        return port;

    }
    else{
        port=m_outPorts.value(keystr,nullptr);
        if(port){
            return port;

        }

    }

    return nullptr;
}


SceneGraph *FlowNode::getScenegraph() const
{
    return m_scenegraph;
}

void FlowNode::inNodeOutputChanged()
{

}

void FlowNode::setParentModule(QAutomationModule *parentModule)
{
    if (m_parentModule == parentModule)
        return;

    m_parentModule = parentModule;
    emit parentModuleChanged(m_parentModule);
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
        QString key=QString::fromStdString(i.key());

        if(nodeinport){
            QJsonObject inPort;

            //            if(nodeinport->)
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


    this->m_scenegraph=qobject_cast<SceneGraph*>(this->getGraph());

    JsonSerializable::DeSerialize(json,this);



    getItem()->setProperty("x",QVariant::fromValue(json["nodeX"].toDouble()));
    getItem()->setProperty("y",QVariant::fromValue(json["nodeY"].toDouble()));

    setNormalWidth(json["normalWidth"].toInt());
    setNormalHeight(json["normalHeight"].toInt());

    setEditWidth(json["editWidth"].toInt());

    setEditHeight(json["editHeight"].toInt());


    initializePorts();

    QJsonObject inPorts = json["inPorts"].toObject();
    foreach(const QString& key, inPorts.keys()) {
        string portkey=QString::number(id()).toStdString()+"|"+key.toStdString();
        FlowNodePort* port= m_inPorts.value(portkey);
        if(port){
            QJsonObject portobject=inPorts.value(key).toObject();
            port->DeSerialize(portobject);
        } // create dynamic property
        else{
            //            this->metaObject()-
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

    setConfigsLoaded(true);
}



FlowNodePort* FlowNode::getPortByID(QString id) const
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


