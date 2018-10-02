#include "selectableedge.h"



QQmlComponent*  SelectableEdge::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   CustomEdge_delegate;
    if ( !CustomEdge_delegate )
        CustomEdge_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Edges/SelectableEdgeItem.qml"));
    return CustomEdge_delegate.get();
}

qan::EdgeStyle* SelectableEdge::style() noexcept
{
    static std::unique_ptr<qan::EdgeStyle>  SelectableEdge_style;
    if ( !SelectableEdge_style )
        SelectableEdge_style = std::make_unique<qan::EdgeStyle>();
    return SelectableEdge_style.get();
}

