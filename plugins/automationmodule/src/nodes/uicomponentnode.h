#ifndef UICOMPONENTNODE_H
#define UICOMPONENTNODE_H

#include <flownode.h>



class UIComponentNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(UIComponentType uiComponentType READ uiComponentType WRITE setUiComponentType NOTIFY uiComponentTypeChanged USER("serialize"))

public:

    enum class UIComponentType {
        Button,
        ButtonGroup
    };
    Q_ENUM(UIComponentType )

    UIComponentNode();

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    UIComponentType uiComponentType() const
    {
        return m_uiComponentType;
    }

public slots:
    void setUiComponentType(UIComponentType uiComponentType)
    {
        if (m_uiComponentType == uiComponentType)
            return;

        m_uiComponentType = uiComponentType;
        emit uiComponentTypeChanged(m_uiComponentType);
    }

signals:
    void uiComponentTypeChanged(UIComponentType uiComponentType);

private:

    UIComponentType m_uiComponentType=UIComponentType::Button;
};

#endif // UICOMPONENTNODE_H
