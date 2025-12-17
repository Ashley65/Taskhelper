//
// Created by DevAccount on 21/11/2025.
//

#ifndef TASKHELPER_WINDOWSACTION_H
#define TASKHELPER_WINDOWSACTION_H

#pragma once
#include <QWidget>
#include <QGridLayout>


class QPushButton;
class QHBoxLayout;
class QMouseEvent;

class WindowsActionsBar : public QWidget
{
    Q_OBJECT

signals:
    void minimiseRequested();
    void maximiseRestoreRequested();
    void closeRequested();

public:
    explicit WindowsActionsBar(QWidget *parent = nullptr);
    void setButtonStyleSheet(const QString &css);


protected:
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void setMaximised(bool maximised);

private:
    void initUi();
    void connectSignals();

    QHBoxLayout* m_layout{nullptr};
    QPushButton* m_minimiseBtn{nullptr};
    QPushButton* m_maximiseBtn{nullptr};
    QPushButton* m_closeBtn{nullptr};
    bool m_isMaximised{false};


};

#endif //TASKHELPER_WINDOWSACTION_H