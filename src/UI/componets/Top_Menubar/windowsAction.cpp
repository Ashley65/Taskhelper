#include <UI/components/Top_Menubar/windowsAction.h>

#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QEvent>


WindowsActionsBar::WindowsActionsBar(QWidget* parent)
    : QWidget(parent)
{
    initUi();
    connectSignals();
}

void WindowsActionsBar::initUi()
{
    // Layout
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    // Buttons
    m_minimiseBtn = new QPushButton(this);
    m_minimiseBtn->setObjectName("winActionMinimise");
    m_minimiseBtn->setText("-");
    m_minimiseBtn->setFlat(true);
    m_minimiseBtn->setToolTip("Minimise");

    m_maximiseBtn = new QPushButton(this);
    m_maximiseBtn->setObjectName("winActionMaximise");
    m_maximiseBtn->setText("□");
    m_maximiseBtn->setFlat(true);
    m_maximiseBtn->setToolTip("Maximise");

    m_closeBtn = new QPushButton(this);
    m_closeBtn->setObjectName("winActionClose");
    m_closeBtn->setText("×");
    m_closeBtn->setFlat(true);
    m_closeBtn->setToolTip("Close");

    // Add to the layout (typical order: minimise, maximise, close)
    m_layout->addWidget(m_minimiseBtn);
    m_layout->addWidget(m_maximiseBtn);
    m_layout->addWidget(m_closeBtn);

    QFont smallFont = font();
    smallFont.setPointSizeF(15.0);
    m_minimiseBtn->setFont(smallFont);
    m_maximiseBtn->setFont(smallFont);
    m_closeBtn->setFont(smallFont);

    QString compactCss =
    "QPushButton{"
    "  padding: 0 6px;"
    "  min-width: 0;"
    "  min-height: 0;"
    "  border: none;"
    "}"
    "QPushButton:hover {"
   "    background: #a8c0ff;"
   "}";

    m_minimiseBtn->setStyleSheet(compactCss);
    m_maximiseBtn->setStyleSheet(compactCss);
    m_closeBtn->setStyleSheet(compactCss   + "QPushButton:hover { background: #ff4444; color: white; }");

    const int btnW = 25;
    const int btnH = 20;
    m_minimiseBtn->setFixedSize(btnW, btnH);
    m_maximiseBtn->setFixedSize(btnW, btnH);
    m_closeBtn->setFixedSize(btnW, btnH);

    setFixedHeight(btnH);
    // Remove this line: setMaximumWidth(btnW * 3);
}


void WindowsActionsBar::connectSignals()
{
    // Relay button clicks as high-level signals
    connect(m_minimiseBtn, &QPushButton::clicked, this, [this]() {
        emit minimiseRequested();
    });

    connect(m_maximiseBtn, &QPushButton::clicked, this, [this]() {
        emit maximiseRestoreRequested();
    });

    connect(m_closeBtn, &QPushButton::clicked, this, [this]() {
        emit closeRequested();
    });
}

void WindowsActionsBar::setMaximised(bool maximised)
{
    if (m_isMaximised == maximised)
        return;

    m_isMaximised = maximised;
    if (m_isMaximised) {
        // When maximised, show a RESTORE glyph and tooltip
        m_maximiseBtn->setText("❐");
        m_maximiseBtn->setToolTip("Restore");
    } else {
        // When normal, show a MAXIMISE glyph and tooltip
        m_maximiseBtn->setText("□");
        m_maximiseBtn->setToolTip("Maximise");
    }
}

void WindowsActionsBar::mousePressEvent(QMouseEvent* event)
{
    // Treat double-click on the bar as maximise/restore toggle
    if (event && event->type() == QEvent::MouseButtonDblClick && event->button() == Qt::LeftButton) {
        emit maximiseRestoreRequested();
        event->accept();
        return;
    }
    QWidget::mousePressEvent(event);
}
