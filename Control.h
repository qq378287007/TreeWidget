#pragma once

#include "Project.h"
#include "TreeWidget.h"

#include <QObject>
#include <QSharedPointer>
#include <QVector>

#include <QDebug>
#include <QAction>
#include <QMenu>

/*
Qt::UserRole + 1    工程节点
Qt::UserRole + 2    节点所在工程id
Qt::UserRole + 3    右键关联action

*/

class Control : QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = nullptr)
        : QObject(parent)
    {
        m_TreeWidget.reset(new TreeWidget());

        m_AddAct = new QAction(QStringLiteral("增加"), this);
        m_RemoveAct = new QAction(QStringLiteral("删除"), this);
        m_Current = nullptr;
        popMenu = new QMenu();


        connect(m_AddAct, &QAction::triggered, this, [=](){
            addItem(m_Current);
        });
        connect(m_RemoveAct, &QAction::triggered, this, [=](){
            removeItem(m_Current);
        });

        connect(m_TreeWidget.data(), &QTreeWidget::currentItemChanged, this, [this](QTreeWidgetItem *current, QTreeWidgetItem *previous){
            if(current != nullptr){
                QVariant v = current->data(0, Qt::UserRole + 1);
                m_index =  current->data(0, Qt::UserRole + 2).toInt();
            } else {
                m_index = -1;
            }
        });

        connect(m_TreeWidget.data(), &QTreeWidget::customContextMenuRequested, this, [this](const QPoint &pos){
            m_Current = m_TreeWidget.data()->itemAt(pos); //获取当前被点击的节点
            if(m_Current == nullptr)
                return;

            QVariant v = m_Current->data(0, Qt::UserRole + 3);
            if(v.isNull())
                return;

            popMenu->clear();
            switch (v.toInt()) {
            case 1:{
                popMenu->addAction(m_AddAct);
                popMenu->exec(QCursor::pos());
            }
                break;
            case 2:{
                popMenu->addAction(m_RemoveAct);
                popMenu->exec(QCursor::pos());
            }
                break;
            default:
                break;

            }
        });
    }

    const QSharedPointer<TreeWidget> &treeWidget() const {
        return m_TreeWidget;
    }

public:
    void addProject(){
        QSharedPointer<ProjectBase> p{new Project()};

        QTreeWidgetItem * item = p->createItem();
        m_TreeWidget->addTopLevelItem(item);
        m_TreeWidget->expandItem(item);
        m_TreeWidget->setCurrentItem(item);

        m_index = m_Project.size();
        m_Project.append(p);

        updateProjectId(item, m_index);
    }

    void removeProject(){
        if(m_index == -1)
            return;

        m_Project.removeAt(m_index);
        delete m_TreeWidget->topLevelItem(m_index);

        for(int id = 0; id < m_Project.size(); id++)
            updateProjectId(m_TreeWidget->topLevelItem(id), id);

        m_TreeWidget->setCurrentItem(nullptr);
        m_index = -1;
    }

    void addItem(QTreeWidgetItem *current = nullptr){
        if(m_index == -1)
            return;

        QTreeWidgetItem *item = m_Project.at(m_index)->addItem(current);
        m_TreeWidget->setCurrentItem(item);
        item->setData(0, Qt::UserRole + 3, 2);
    }

    void removeItem(QTreeWidgetItem *current = nullptr){
        if(m_index == -1)
            return;

        m_Project.at(m_index)->removeItem(current);
        m_TreeWidget->setCurrentItem(nullptr);
    }

private:
    void updateProjectId(QTreeWidgetItem * item, int id){
        item->setData(0, Qt::UserRole + 2, id);
        for(int i=0; i<item->childCount();i++)
            updateProjectId(item->child(i), id);
    }

private:
    QVector<QSharedPointer<ProjectBase>> m_Project;
    QSharedPointer<TreeWidget> m_TreeWidget;
    int m_index{-1};

    QAction* m_AddAct;
    QAction* m_RemoveAct;
    QTreeWidgetItem* m_Current;
    QMenu *popMenu;
};
