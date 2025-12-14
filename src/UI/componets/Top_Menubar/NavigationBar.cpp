//
// Created by DevAccount on 04/12/2025.
//

#include "UI/components/Top_Menubar/NavigationBar.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QStyle> // Added for standard icons

NavigationBar::NavigationBar(QWidget* parent) : QWidget(parent)
{
    initUi();
}

void NavigationBar::initUi()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(6);

    // Back button
    m_backBtn = new QPushButton(this);
    m_backBtn->setText(QString::fromUtf8("\xE2\x86\x90"));
    m_backBtn->setToolTip("Back");
    m_backBtn->setEnabled(false);
    m_backBtn->setFlat(true);
    m_backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_layout->addWidget(m_backBtn);

    // Forward button
    m_forwardBtn = new QPushButton(this);
    m_forwardBtn->setText(QString::fromUtf8("\xE2\x86\x92"));
    m_forwardBtn->setToolTip("Forward");
    m_forwardBtn->setEnabled(false);
    m_forwardBtn->setFlat(true);
    m_forwardBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_layout->addWidget(m_forwardBtn);

    // Refresh button
    m_refreshBtn = new QPushButton(this);
    m_refreshBtn->setText(QString::fromUtf8("\xE2\x8E\xAF"));
    m_refreshBtn->setToolTip("Refresh");
    m_refreshBtn->setFlat(true);
    m_refreshBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_layout->addWidget(m_refreshBtn);

    // Add stretch to push buttons to the left
    m_layout->addStretch();

    QString compactCss =
    "QPushButton{"
    "  padding: 0 6px;"      // horizontal padding per button
    "  min-width: 0;"
    "  min-height: 0;"
    "  border: none;"
    "}"
    "QPushButton:hover {"
   "    background: #a8c0ff;"
   "}";
    m_backBtn->setStyleSheet(compactCss);
    m_forwardBtn->setStyleSheet(compactCss);
    m_refreshBtn->setStyleSheet(compactCss);

    // Direct Signal Connections
    connect(m_backBtn, &QPushButton::clicked, this, &NavigationBar::backClicked);
    connect(m_forwardBtn, &QPushButton::clicked, this, &NavigationBar::forwardClicked);
    connect(m_refreshBtn, &QPushButton::clicked, this, &NavigationBar::refreshClicked);
}


void NavigationBar::setBackEnabled(bool enabled)
{
    if (m_backBtn) m_backBtn->setEnabled(enabled);
}

void NavigationBar::setForwardEnabled(bool enabled)
{
    if (m_forwardBtn) m_forwardBtn->setEnabled(enabled);
}

void NavigationBar::setRefreshEnabled(bool enabled)
{
    if (m_refreshBtn) m_refreshBtn->setEnabled(enabled);
}

void NavigationBar::onBackClicked()
{
}

void NavigationBar::onForwardClicked()
{
}

void NavigationBar::onRefreshClicked()
{
}
