//
// Created by DevAccount on 14/12/2025.
//


#include "UI/components/Top_Menubar/MenuButtonBar.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QMenu>
#include <QIcon>

MenuButtonBar::MenuButtonBar(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void MenuButtonBar::initUi()
{
    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    constexpr int buttonSize = 28;
    constexpr QSize iconSize(16, 16);

    auto loadIcon = [](const QString &name) -> QIcon {
        QIcon ic = QIcon::fromTheme(name);
        if (!ic.isNull())
            return ic;
        return QIcon(QStringLiteral(":/icons/") + name + QStringLiteral(".svg"));
    };

    m_menuBtn = new QPushButton(this);
    m_menuBtn->setToolTip("Menu");
    m_menuBtn->setAccessibleName("Menu");
    m_menuBtn->setFlat(true);
    m_menuBtn->setFixedSize(buttonSize, buttonSize);
    m_menuBtn->setIcon(loadIcon(QStringLiteral("menu_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24")));
    m_menuBtn->setIconSize(iconSize);

    const QString css =
        "QPushButton {"
        "  padding: 0px;"
        "  border: none;"
        "  border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "    background: #a8c0ff;"
        "}"
        "QPushButton:pressed {"
        "  background-color: rgba(255, 255, 255, 0.32);"
        "}";

    m_menuBtn->setStyleSheet(css);
    layout->addWidget(m_menuBtn);   // <- actually add the button to the layout

    auto *menu = new QMenu(this);
    auto *settingsAct = menu->addAction("Settings");
    auto *aboutAct    = menu->addAction("About");
    menu->addSeparator();
    auto *exitAct     = menu->addAction("Exit");

    connect(settingsAct, &QAction::triggered, this, &MenuButtonBar::settingRequested);
    connect(aboutAct,    &QAction::triggered, this, &MenuButtonBar::aboutRequested);
    connect(exitAct,     &QAction::triggered, this, &MenuButtonBar::exitRequested);

    m_menuBtn->setMenu(menu);
}

QMenu *MenuButtonBar::menuBar() const
{
    return m_menuBtn ? m_menuBtn->menu() : nullptr;
}
