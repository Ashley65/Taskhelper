//
// Created by DevAccount on 18/12/2025.
//
#ifndef TASKHELPER_PRIMARYACTIONSECTION_H
#define TASKHELPER_PRIMARYACTIONSECTION_H
#pragma once

#include <QWidget>
#include <QPushButton>

class PrimaryActionSection : public QWidget
{
    Q_OBJECT
public:
    explicit PrimaryActionSection(QWidget *parent = nullptr);

    signals:
        void triggered();

protected:
    // Listen for the "compact" property change from SideBar.cpp
    void changeEvent(QEvent *event) override;

private:
    QToolButton* mainBtn;
    void updateStyle(bool compact);
};

#endif //TASKHELPER_PRIMARYACTIONSECTION_H