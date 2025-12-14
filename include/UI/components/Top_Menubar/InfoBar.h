//
// Created by DevAccount on 21/11/2025.
//

#ifndef TASKHELPER_INFOBAR_H
#define TASKHELPER_INFOBAR_H
#pragma once
#include <QWidget>
#include <QGridLayout>

class QLabel;
class QHBoxLayout;

class InfoBar : public QWidget
{
    Q_OBJECT

signals:
    // Emitted when user double-clicks the bar, to toggle maximise/restore
    void maximiseRestoreRequested();

private:
    void initUi();
    QHBoxLayout *m_layout;
    QLabel *m_appNameLabel;
    QLabel *m_currentScreenLabel;

protected:
    void mouseDoubleClickEvent(QMouseEvent *e) override;



public slots:
    void setCurrentScreenLabel(const QString& name);

public:
    explicit InfoBar(QWidget* parent = nullptr);

    void setAppName(const QString& name);

};


#endif //TASKHELPER_INFOBAR_H