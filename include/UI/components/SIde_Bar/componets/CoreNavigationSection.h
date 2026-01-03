//
// Created by DevAccount on 18/12/2025.
//

#ifndef TASKHELPER_CORENAVIGATIONSECTION_H
#define TASKHELPER_CORENAVIGATIONSECTION_H
#pragma once



#include "BaseNavTree.h"

class CoreNavigationSection : public QWidget
{
    Q_OBJECT

public:
    enum class Item
    {
        Dashboard,
        Upcoming,
        AI_Assistant
    };
    explicit CoreNavigationSection(QWidget *parent = nullptr);
    void setActiveItem(Item item);

protected:
    void changeEvent(QEvent *event) override;


signals:
    void itemSelected(Item item);
private:
    QListWidget* navList;

};


#endif //TASKHELPER_CORENAVIGATIONSECTION_H