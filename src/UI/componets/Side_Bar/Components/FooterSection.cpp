//
// Created by DevAccount on 23/12/2025.
//
#include <UI/components/SIde_Bar/componets/FooterSection.h>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>

FooterSection::FooterSection(QWidget* parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    // 1. The Toggle Button
    modeBtn = new QToolButton(this);
    modeBtn->setCursor(Qt::PointingHandCursor);
    modeBtn->setObjectName("FooterModeBtn");
    modeBtn->setIcon(QIcon(":/icons/menu_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg"));
    modeBtn->setIconSize(QSize(20, 20));

    // 2. Sync Status
    syncDot = new QLabel("●", this);
    syncDot->setStyleSheet("color: #2ecc71; font-size: 10px;");

    syncStatus = new QLabel("Synced", this);
    syncStatus->setObjectName("FooterStatus");
    syncStatus->setStyleSheet("color: #666; font-size: 12px;");

    layout->addWidget(modeBtn);
    layout->addStretch();
    layout->addWidget(syncDot);
    layout->addWidget(syncStatus);

    // Style the button
    setStyleSheet(R"(
        QToolButton#FooterModeBtn {
            background: transparent;
            border: 1px solid transparent;
            color: #A0A0A0;
            text-align: left;
            font-weight: bold;
            border-radius: 4px;
            padding: 4px;
        }
        QToolButton#FooterModeBtn:hover {
            color: white;
            background-color: rgba(255,255,255,0.05);
        }
    )");

    // 3. Connect Click to Signal
    connect(modeBtn, &QToolButton::clicked, this, &FooterSection::modeCycleRequested);

    // Set the initial state
    setMode(SideBar::Mode::Default);
}
void FooterSection::setMode(SideBar::Mode mode) {
    m_currentMode = mode;

    // Update visuals based on mode
    if (m_currentMode == SideBar::Mode::Compact) {
        modeBtn->setText(""); // No text in compact
        modeBtn->setToolButtonStyle(Qt::ToolButtonIconOnly); // Center the icon
        modeBtn->setToolTip("Expand Sidebar");
        syncStatus->hide();
        syncDot->hide();
        layout()->setContentsMargins(5, 10, 5, 10); // Tight margins for rail
    } else {
        modeBtn->setText(" Sidebar Mode");
        modeBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); // Reset to default
        modeBtn->setToolTip("Change View");
        syncStatus->show();
        syncDot->show();
        layout()->setContentsMargins(10, 10, 10, 10);
    }
}
void FooterSection::changeEvent(QEvent *event) {
    if (event->type() == QEvent::DynamicPropertyChange) {
        // This handles if the mode is set via property instead of direct method call
        // (Optional safety net matching your other classes)
    }
    QWidget::changeEvent(event);
}