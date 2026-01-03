//
// Created by DevAccount on 23/12/2025.
//
#include <UI/components/SIde_Bar/componets/CoreNavigationSection.h>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QShortcut>
#include <QVariant>

const QString kGlowStyle = R"(
    QListWidget#CoreNavList {
        background: transparent;
        border: none;
        outline: none;
        color: #A0A0A0; /* Dimmed text color from image */
    }
    QListWidget#CoreNavList::item {
        padding: 8px 5px; /* Slightly taller for modern feel */
        border-radius: 4px; /* Rounded corners */
        border-left: 3px solid transparent; /* Reserve space for the accent bar */
        margin-bottom: 2px;
    }
    QListWidget#CoreNavList::item:hover {
        background-color: #1A1D2D; /* Subtle dark hover */
        color: #FFFFFF;
    }
    QListWidget#CoreNavList::item:selected {
        /* THE GLOW: Linear gradient from blue-ish transparency to transparent */
        background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 rgba(50, 150, 255, 40), stop:1 rgba(0, 0, 0, 0));

        /* THE ACCENT BAR: Sharp Cyan/Blue line on the left */
        border-left: 3px solid #64B5F6;

        color: #FFFFFF;
    }
)";

CoreNavigationSection::CoreNavigationSection(QWidget* parent)
{
    auto* lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);

    navList = new QListWidget(this);
    navList->setObjectName("CoreNavList");
    navList->setSelectionMode(QAbstractItemView::SingleSelection);

    // Apply the Glow Style
    navList->setStyleSheet(kGlowStyle);

    auto add = [&](const QString& text, const QString& iconPath) // Changed to path for simplicity in example
    {
        // Ideally use your resource path here
        QIcon icon(iconPath);
        auto* it = new QListWidgetItem(icon, text);
        it->setSizeHint(QSize(0, 36)); // Height matching the image
        it->setData(Qt::UserRole + 1, text);
        navList->addItem(it);
    };

    add("Inbox", ":/icons/inbox.svg");
    add("Today", ":/icons/star.svg");
    add("Upcoming", ":/icons/calendar.svg");
    add("Dashboard", ":/icons/dashboard.svg");

    lay->addWidget(navList);

    navList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    navList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    navList->setIconSize(QSize(18, 18)); // Slightly smaller icons usually look cleaner

    connect(navList, &QListWidget::currentRowChanged, this, [this](int row){
        if(row >= 0) emit itemSelected(static_cast<Item>(row));
    });

    // Default Selection (e.g., Today)
    navList->setCurrentRow(1);

    // Dynamic height based on count
    navList->setFixedHeight(navList->count() * 40);
}


void CoreNavigationSection::setActiveItem(Item item) {
    navList->setCurrentRow(static_cast<int>(item));
}

void CoreNavigationSection::changeEvent(QEvent* event) {
    if (event->type() == QEvent::DynamicPropertyChange) {
        auto* propEvent = static_cast<QDynamicPropertyChangeEvent*>(event);
        if (propEvent->propertyName() == "compact") {
            bool compact = property("compact").toBool();
            for (int i = 0; i < navList->count(); ++i) {
                auto* it = navList->item(i);
                if (compact) {
                    it->setText("");
                    it->setTextAlignment(Qt::AlignCenter);
                } else {
                    it->setText(it->data(Qt::UserRole + 1).toString());
                    it->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                }
            }
            // Re-apply style (CSS handles alignment, logic handles text)
            navList->setStyleSheet(kGlowStyle);
        }
    }
    QWidget::changeEvent(event);
}