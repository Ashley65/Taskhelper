#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QString>
#include <QMouseEvent>
#include <QCursor>
#include "UI/mainWIndow.h"

class CssToQtLayout : public QWidget {
public:
    CssToQtLayout(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("CSS Grid -> Qt Layout (C++)");
        resize(1000, 700);



        setStyleSheet("QWidget { background-color: #222; border: 10px solid #444; }");

        // ============================================================
        // 1. MAIN CONTAINER (.container)
        // ============================================================
        // CSS: display: grid; gap: 0px;
        QGridLayout *mainLayout = new QGridLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        // CSS: grid-template-columns: 0.5fr 1.5fr 1.1fr 1.1fr 1fr;
        // We map these float ratios to integer stretches (x10)
        mainLayout->setColumnStretch(0, 5);
        mainLayout->setColumnStretch(1, 15);
        mainLayout->setColumnStretch(2, 11);
        mainLayout->setColumnStretch(3, 11);
        mainLayout->setColumnStretch(4, 10);

        // CSS: grid-template-rows: 0.3fr 1.7fr 1fr;
        mainLayout->setRowStretch(0, 3);
        mainLayout->setRowStretch(1, 17);
        mainLayout->setRowStretch(2, 10);

        // Dark background for the main container
        setStyleSheet("background-color: #222;");

        // ============================================================
        // 2. TOP MENUBAR (.top_menubar)
        // ============================================================
        // CSS: grid-area: 1 / 1 / 2 / 6; (Row 0, Col 0, Span 1, Span 5)

        topBarFrame = new QFrame();
        topBarFrame->setStyleSheet("background-color: #333; border-bottom: 1px solid #555;");
        mainLayout->addWidget(topBarFrame, 0, 0, 1, 5);

        topBarFrame->installEventFilter(this);
        setMouseTracking(true);
        // Internal Grid for Top Bar
        QGridLayout *topLayout = new QGridLayout(topBarFrame);
        topLayout->setContentsMargins(0, 0, 0, 0);
        topLayout->setSpacing(0);

        // CSS: grid-template-columns: 1fr 1fr 1fr;
        topLayout->setColumnStretch(0, 1);
        topLayout->setColumnStretch(1, 1);
        topLayout->setColumnStretch(2, 1);

        // CSS: grid-template-rows: 1fr 0.5fr 2fr; -> (2 : 1 : 4)
        topLayout->setRowStretch(0, 2);
        topLayout->setRowStretch(1, 1);
        topLayout->setRowStretch(2, 4);

        // --- Application_info ---
        // Spans Row 0, Cols 0-1
        QFrame *appInfo = createWidget("Application_info", "#4a90e2");
        topLayout->addWidget(appInfo, 0, 0, 1, 2);

        // --- Window_action_bar ---
        // Spans Rows 0-1, Col 2
        QFrame *winAction = createWidget("Window_action_bar", "#e74c3c");
        topLayout->addWidget(winAction, 0, 2, 2, 1);

        // --- Menu_action_bar ---
        // Spans Row 2, Cols 0-2
        QFrame *menuAction = createWidget("Menu_action_bar", "#f1c40f");
        topLayout->addWidget(menuAction, 2, 0, 1, 3);


        // ============================================================
        // 3. SIDE BAR (.Side_bar)
        // ============================================================
        // CSS: grid-area: 2 / 1 / 4 / 2; (Row 1, Col 0, Span 2, Span 1)
        QFrame *sideBar = createWidget("Side_bar", "#2c3e50");
        mainLayout->addWidget(sideBar, 1, 0, 2, 1);

        // ============================================================
        // 4. CONTENT WINDOW (.Content_window)
        // ============================================================
        // CSS: grid-area: 2 / 2 / 4 / 6; (Row 1, Col 1, Span 2, Span 4)
        QFrame *content = createWidget("Content_window", "#ecf0f1", "color: #333;");
        mainLayout->addWidget(content, 1, 1, 2, 4);
    }

private:
    // Helper to create a styled QFrame that acts like a DIV
    QFrame* createWidget(const QString &text, const QString &color, const QString &extraStyle = "") {
        QFrame *frame = new QFrame();
        frame->setFrameShape(QFrame::Box);

        // Using CSS-like StyleSheets (QSS)
        QString style = QString("QFrame { background-color: %1; border: 1px solid rgba(0,0,0,0.2); %2 }")
                        .arg(color)
                        .arg(extraStyle);
        frame->setStyleSheet(style);

        // Add a label inside to identify it
        QGridLayout *layout = new QGridLayout(frame);
        QLabel *label = new QLabel(text);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("border: none; font-weight: bold; font-size: 14px;");
        layout->addWidget(label);

        return frame;
    }
    enum Region {
        None       = 0,
        Left       = 1 << 0,
        Right      = 1 << 1,
        Top        = 1 << 2,
        Bottom     = 1 << 3,
        TopLeft    = Top | Left,
        TopRight   = Top | Right,
        BottomLeft = Bottom | Left,
        BottomRight= Bottom | Right
    };

    Region hitTest(const QPoint &p) const {
        const int x = p.x();
        const int y = p.y();
        const int w = width();
        const int h = height();
        const int bw = borderWidth; // resize grip size in px

        const bool left   = (x <= bw);
        const bool right  = (x >= w - bw - 1);
        const bool top    = (y <= bw);
        const bool bottom = (y >= h - bw - 1);

        if (top && left)     return TopLeft;
        if (top && right)    return TopRight;
        if (bottom && left)  return BottomLeft;
        if (bottom && right) return BottomRight;
        if (left)            return Left;
        if (right)           return Right;
        if (top)             return Top;
        if (bottom)          return Bottom;
        return None;
    }

    void setCursorForRegion(Region r) {
        switch (r) {
        case TopLeft:
        case BottomRight:
            setCursor(Qt::SizeFDiagCursor); break;
        case TopRight:
        case BottomLeft:
            setCursor(Qt::SizeBDiagCursor); break;
        case Left:
        case Right:
            setCursor(Qt::SizeHorCursor); break;
        case Top:
        case Bottom:
            setCursor(Qt::SizeVerCursor); break;
        default:
            unsetCursor(); break;
        }
    }

    // Members
    QFrame *topBarFrame = nullptr; // the area used for dragging (like a title bar)
    bool dragging = false;
    bool resizing = false;
    QPoint dragStartGlobal;
    QRect startGeom;
    Region currentRegion = None;
    const int borderWidth = 6;


protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == topBarFrame) {
            if (event->type() == QEvent::MouseButtonPress) {
                auto *e = static_cast<QMouseEvent*>(event);
                if (e->button() == Qt::LeftButton) {
                    // Optional safety: if pointer is on the resize border, don’t start a drag
                    if (hitTest(mapFromGlobal(e->globalPosition().toPoint())) == None) {
                        dragging = true;
                        dragStartGlobal = e->globalPosition().toPoint();
                        startGeom = geometry();
                        return true; // handled
                    }
                }
            } else if (event->type() == QEvent::MouseMove) {
                auto *e = static_cast<QMouseEvent*>(event);
                if (dragging) {
                    const QPoint delta = e->globalPosition().toPoint() - dragStartGlobal;
                    setGeometry(QRect(startGeom.topLeft() + delta, startGeom.size()));
                    return true; // handled
                }
            } else if (event->type() == QEvent::MouseButtonRelease) {
                auto *e = static_cast<QMouseEvent*>(event);
                if (e->button() == Qt::LeftButton) {
                    dragging = false;
                    return true; // handled
                }
            }
        }
        return QWidget::eventFilter(obj, event);
    }
    void mousePressEvent(QMouseEvent *e) override {
        if (e->button() != Qt::LeftButton)
            return;

        currentRegion = hitTest(e->pos());
        if (currentRegion != None) {
            resizing = true;
            dragStartGlobal = e->globalPosition().toPoint();
            startGeom = geometry();
            e->accept();
            return;
        }
        QWidget::mousePressEvent(e);
    }

    void mouseMoveEvent(QMouseEvent *e) override {
        const QPoint pos = e->pos();
        if (resizing) {
            const QPoint delta = e->globalPosition().toPoint() - dragStartGlobal;
            QRect g = startGeom;

            const int minW = minimumWidth() > 0 ? minimumWidth() : 100;
            const int minH = minimumHeight() > 0 ? minimumHeight() : 80;

            if (currentRegion & Left)   g.setLeft(g.left() + delta.x());
            if (currentRegion & Right)  g.setRight(g.right() + delta.x());
            if (currentRegion & Top)    g.setTop(g.top() + delta.y());
            if (currentRegion & Bottom) g.setBottom(g.bottom() + delta.y());

            if (g.width() < minW) {
                if (currentRegion & Left)   g.setLeft(g.right() - minW);
                else                        g.setRight(g.left() + minW);
            }
            if (g.height() < minH) {
                if (currentRegion & Top)    g.setTop(g.bottom() - minH);
                else                        g.setBottom(g.top() + minH);
            }
            setGeometry(g);
            e->accept();
            return;
        }
        if (dragging) {
            const QPoint delta = e->globalPosition().toPoint() - dragStartGlobal;
            setGeometry(QRect(startGeom.topLeft() + delta, startGeom.size()));
            e->accept();
            return;
        }

        // Not resizing: update cursor based on proximity to edges
        setCursorForRegion(hitTest(pos));
        QWidget::mouseMoveEvent(e);
    }
    void mouseReleaseEvent(QMouseEvent *e) override {
        if (e->button() == Qt::LeftButton) {
            resizing = false;
            currentRegion = None;
            e->accept();
            return;
        }
        QWidget::mouseReleaseEvent(e);
    }

    void leaveEvent(QEvent *) override {
        if (!resizing) unsetCursor();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    window.show();
    return app.exec();
}