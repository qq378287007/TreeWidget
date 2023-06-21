#pragma once

#include <QTreeWidgetItem>

class ProjectBase{
public:
    virtual ~ProjectBase() = default;

    virtual QTreeWidgetItem * createItem(){ return nullptr;}
    virtual QTreeWidgetItem * addItem(QTreeWidgetItem *current = nullptr) {return nullptr;}
    virtual void removeItem(QTreeWidgetItem *current = nullptr) {}
};

/*
class StructModel
{

};

class StatorRotor{

};

class Wingding {

};

class Materail {

};


class Inial {

};


class MoveArea {

};

class VectorBoundary {

};


class SymmetricBoundary {

};
*/


class Project : public ProjectBase
{
public:
    virtual QTreeWidgetItem * createItem() override {
        QTreeWidgetItem *m_Rotar = new QTreeWidgetItem({"定子和转子"});
        QTreeWidgetItem *m_Wind = new QTreeWidgetItem({"绕组"});
        QTreeWidgetItem *m_Struct = new QTreeWidgetItem({"结构建模"});
        m_Struct->addChildren({m_Rotar, m_Wind});

        QTreeWidgetItem *m_Material = new QTreeWidgetItem({"材料"});

        QTreeWidgetItem *m_MoveArea = new QTreeWidgetItem({"运动区域"});
        QTreeWidgetItem *m_SBoundary = new QTreeWidgetItem({"矢量边界"});
        QTreeWidgetItem *m_MBoundary = new QTreeWidgetItem({"对称边界"});
        QTreeWidgetItem *m_inial = new QTreeWidgetItem({"初始化"});
        m_inial->addChildren({m_MoveArea, m_SBoundary, m_MBoundary});

        QTreeWidgetItem *m_Project = new QTreeWidgetItem({"新建工程"});
        m_Project->addChildren({m_Struct, m_Material, m_inial});

        //m_Project->setFlags(Qt::ItemIsEditable|m_Project->flags());
        m_Project->setData(0, Qt::UserRole + 1, 1);
        m_MoveArea->setData(0, Qt::UserRole + 3, 1);
        m_SBoundary->setData(0, Qt::UserRole + 3, 1);
        m_MBoundary->setData(0, Qt::UserRole + 3, 1);

        return m_Project;
    }

    virtual QTreeWidgetItem * addItem(QTreeWidgetItem *current = nullptr) override{
        if(current == nullptr)
            return nullptr;

        QTreeWidgetItem * item = new QTreeWidgetItem({"新增"});
        current->addChild(item);
        return item;
    }

    virtual void removeItem(QTreeWidgetItem *current = nullptr) override {
        if(current != nullptr){
            QTreeWidgetItem *parent = current->parent();
            if(parent != nullptr)
                parent->removeChild(current);
            delete current;
            current = nullptr;
        }
    }
    /*
private:
    StructModel m_StructModel;
    StatorRotor m_StatorRotor;
    Wingding m_Wingding;
    Materail m_Materail;
    Inial m_Inial;
    MoveArea m_MoveArea;
    VectorBoundary m_VectorBoundary;
    SymmetricBoundary m_SymmetricBoundary;
    */
};
