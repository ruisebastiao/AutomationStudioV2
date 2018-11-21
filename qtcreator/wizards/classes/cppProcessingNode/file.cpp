%{Cpp:LicenseTemplate}\
#include "%{HdrFileName}"
%{JS: Cpp.openNamespaces('%{Class}')}
@if '%{IncludeQSharedData}'
class %{CN}Data : public QSharedData
{
public:

};

@endif
@if '%{Base}' === 'QObject'
%{CN}::%{CN}(QObject *parent) : QObject(parent)%{JS: ('%{SharedDataInit}') ? ', %{SharedDataInit}' : ''}
@elsif '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow'
%{CN}::%{CN}(QWidget *parent) : %{Base}(parent)%{JS: ('%{SharedDataInit}') ? ', %{SharedDataInit}' : ''}
@else
%{CN}::%{CN}()%{JS: ('%{SharedDataInit}') ? ' : %{SharedDataInit}' : ''}
@endif
{
	m_processingType=ProcessingType::%{CN}Node;  
    m_processingTypeTable[m_processingType]=;
}


QQmlComponent *%{CN}::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/%{CN}Item.qml"));
    return delegate.get();

}

@if '%{IncludeQSharedData}'

%{CN}::%{CN}(const %{CN} &rhs) : data(rhs.data)
{

}

%{CN} &%{CN}::operator=(const %{CN} &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

%{CN}::~%{CN}()
{

}
@endif
%{JS: Cpp.closeNamespaces('%{Class}')}\
