//
// Created by DevAccount on 30/12/2025.
//

#ifndef TASKHELPER_BASENAVTREE_H
#define TASKHELPER_BASENAVTREE_H
#pragma once
#include <QWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QDynamicPropertyChangeEvent>

class BaseNavTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit BaseNavTree(QWidget* parent = nullptr) : QTreeWidget(parent) {
        setHeaderHidden(true);
        setIndentation(15);
        setFrameShape(QFrame::NoFrame);
        setFocusPolicy(Qt::NoFocus); // Removes dotted border
        setAnimated(true);

        // Fix for standard Qt height issues
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        setStyleSheet(R"(
            QTreeWidget {
                background: transparent;
                border: none;
                outline: none;
                color: #A0A0A0;
            }
            QTreeWidget::item {
                padding: 6px;
                border-radius: 4px;
                border-left: 3px solid transparent;
                margin-bottom: 1px;
            }
            QTreeWidget::item:hover {
                background-color: #1A1D2D;
                color: white;
            }
            QTreeWidget::item:selected {
                /* The Glow Effect */
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(50, 150, 255, 40), stop:1 rgba(0, 0, 0, 0));
                border-left: 3px solid #64B5F6;
                color: white;
            }
            /* Tree Arrows */
            QTreeView::branch:has-children:!has-siblings:closed,
            QTreeView::branch:closed:has-children:has-siblings { image: url(:/icons/chevron-right.svg); }
            QTreeView::branch:open:has-children:!has-siblings,
            QTreeView::branch:open:has-children:has-siblings { image: url(:/icons/chevron-down.svg); }
        )");


    }
};


#endif //TASKHELPER_BASENAVTREE_H