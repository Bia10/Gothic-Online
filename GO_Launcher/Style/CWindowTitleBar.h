#ifndef CWINDOWTITLEBAR_H
#define CWINDOWTITLEBAR_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>

#include "CWindowButton.h"
#include "StyleDefines.h"

class CCustomWindow;

class CWindowTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CWindowTitleBar(QWidget *parent, CCustomWindow *window, EButtonWindowTitle type = BUTTON_ALL, bool titleBar = false);
    ~CWindowTitleBar();

public slots:
    void updateWindowTitle(QString title);
    void minimized();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPixmap *m_Cache;
    QLabel m_Title;
    QPoint m_ShiftDiff;

    CWindowButton *m_ButtonMinimize, *m_ButtonClose;

    bool m_CanMove, m_TitleBar;
};

#endif // CWINDOWTITLEBAR_H
