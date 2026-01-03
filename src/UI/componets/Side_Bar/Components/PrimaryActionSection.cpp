//
// Created by DevAccount on 23/12/2025.
//

#include <UI/components/SIde_Bar/componets/PrimaryActionSection.h>
#include <QVBoxLayout>
#include <QEvent>
#include <QToolButton>
#include <QDynamicPropertyChangeEvent>

PrimaryActionSection::PrimaryActionSection(QWidget *parent) : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    // Margins: Top/Bottom 10px, Left/Right 5px
    layout->setContentsMargins(5, 10, 5, 10);
    layout->setSpacing(0);

    mainBtn = new QToolButton(this); // Changed from QPushButton
    mainBtn->setObjectName("PrimaryBtn");
    mainBtn->setCursor(Qt::PointingHandCursor);


    mainBtn->setIcon(QIcon(":/icons/dashboard.svg"));
    mainBtn->setIconSize(QSize(20, 20));

    layout->addWidget(mainBtn);

    // Initial State: Default (Not Compact)
    updateStyle(false);

    connect(mainBtn, &QToolButton::clicked, this, &PrimaryActionSection::triggered); // Changed from QPushButton
}

void PrimaryActionSection::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::DynamicPropertyChange) {
        auto* propEvent = dynamic_cast<QDynamicPropertyChangeEvent*>(event);
        if (propEvent->propertyName() == "compact") {
            bool isCompact = property("compact").toBool();
            updateStyle(isCompact);
        }
    }
    QWidget::changeEvent(event);
}

void PrimaryActionSection::updateStyle(bool compact)
{
    if (compact) {
        // --- COMPACT MODE ---
        mainBtn->setText(""); // Hide Text
        mainBtn->setToolTip("Personal Workspace");
        mainBtn->setToolButtonStyle(Qt::ToolButtonIconOnly); // Centre the icon

        // Centre the icon, make it look like a square button
        mainBtn->setStyleSheet(R"(
            QPushButton#PrimaryBtn {
                background-color: transparent;
                border: 1px solid transparent;
                border-radius: 6px;
                padding: 6px;
            }
            QPushButton#PrimaryBtn:hover {
                background-color: #1A1D2D;
                border: 1px solid #333646;
            }
        )");
    } else {
        // --- DEFAULT MODE ---
        mainBtn->setText(" Personal Workspace ▼");
        mainBtn->setToolTip("");
        mainBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); // Reset to default

        // Left-align text, add padding for the "Wide" look
        mainBtn->setStyleSheet(R"(
            QPushButton#PrimaryBtn {
                background-color: transparent;
                color: #E0E0E0;
                font-weight: bold;
                font-size: 14px;
                border: 1px solid transparent;
                border-radius: 6px;
                padding: 8px 12px;
                text-align: left; /* Left align text */
            }
            QPushButton#PrimaryBtn:hover {
                background-color: #1A1D2D;
                border: 1px solid #333646;
            }
        )");
    }
}
