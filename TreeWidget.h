#pragma once

#include <QTreeWidget>
#include <QTreeWidgetItem>

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr)
        : QTreeWidget(parent)
    {
        setHeaderHidden(true);
        setContextMenuPolicy(Qt::CustomContextMenu);//右键菜单
    }
};
