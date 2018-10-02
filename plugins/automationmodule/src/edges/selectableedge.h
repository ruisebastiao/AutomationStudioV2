#ifndef SELECTABLEEDGE_H
#define SELECTABLEEDGE_H

#include <QFlags>
#include <QFlags>
#include <QObject>
#include <qanEdge.h>
#include <qanUtils.h>




class SelectableEdge : public qan::Edge
{
    Q_OBJECT

    Q_PROPERTY(bool isHidden READ isHidden WRITE setIsHidden NOTIFY isHiddenChanged)


public:

    explicit SelectableEdge() : qan::Edge{} { }
    virtual ~SelectableEdge() { /* Nil */ }
    SelectableEdge( const SelectableEdge& ) = delete;

public slots:


    void setIsHidden(bool isHidden)
    {
        if (m_isHidden == isHidden)
            return;

        m_isHidden = isHidden;
        emit isHiddenChanged(m_isHidden);
    }

public:


// SelectableEdge* insertedEdge= (SelectableEdge*)scene->insertEdge((*fromnode),(*tonode));

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;
    static  qan::EdgeStyle*     style() noexcept;


    bool isHidden() const
    {
        return m_isHidden;
    }

signals:


    void isHiddenChanged(bool isHidden);

private:

    bool m_isHidden=false;
};

#endif // SELECTABLEEDGE_H
