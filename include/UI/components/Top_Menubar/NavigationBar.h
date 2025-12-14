//
// Created by DevAccount on 21/11/2025.
//

#ifndef TASKHELPER_ACTIONBAR_H
#define TASKHELPER_ACTIONBAR_H
#pragma once
#include "QWidget"
#include "QGridLayout"


class QPushButton;
class QHBoxLayout;

class NavigationBar  : public QWidget
{
    Q_OBJECT



private:
    void initUi();
    QHBoxLayout *m_layout;
    QPushButton *m_backBtn;
    QPushButton *m_forwardBtn;
    QPushButton *m_refreshBtn;

public:
    explicit NavigationBar(QWidget* parent = nullptr);

    void setBackEnabled(bool enabled);
    void setForwardEnabled(bool enabled);
    void setRefreshEnabled(bool enabled);

public slots:
    // Slots to handle button clicks
    void onBackClicked();
    void onForwardClicked();
    void onRefreshClicked();

signals:
    // Used for signaling navigation actions (e.g., back, forward)
    void backClicked();
    void forwardClicked();
    void refreshClicked();


};





#endif //TASKHELPER_ACTIONBAR_H