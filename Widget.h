#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "TreeWidget.h"
#include "Control.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        m_AddProject = new QPushButton("增加工程", this);
        m_RemoveProject = new QPushButton("删除工程", this);
        upLayout = new QHBoxLayout();
        upLayout->addWidget(m_AddProject);
        upLayout->addWidget(m_RemoveProject);
        upLayout->addStretch();

        mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(upLayout);

        const QSharedPointer<TreeWidget> &m_TreeWidget = m_Control.treeWidget();
        mainLayout->addWidget(m_TreeWidget.data(), 1);

        connect(m_AddProject, &QPushButton::pressed, this, [this](){
            m_Control.addProject();
        });

        connect(m_RemoveProject, &QPushButton::pressed, this, [this](){
            m_Control.removeProject();
        });
    }
private:
    QPushButton *m_AddProject;
    QPushButton *m_RemoveProject;

    QHBoxLayout *upLayout;
    QVBoxLayout *mainLayout;
    Control m_Control;
};
