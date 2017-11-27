#include <QPainter>
#include <QMouseEvent>

#include "StyleDefines.h"
#include "CWindowTitleBar.h"
#include "CCustomWindow.h"

CWindowTitleBar::CWindowTitleBar(QWidget *parent, CCustomWindow *window, EButtonWindowTitle type, bool titleBar) :
    QWidget(parent),
    m_Cache(NULL),
    m_Title(this),
    m_ButtonMinimize(NULL),
    m_ButtonClose(NULL),
    m_CanMove(false),
    m_TitleBar(titleBar)
{

    switch (type)
    {
    case BUTTON_ALL:
        m_ButtonMinimize = new CWindowButton(CWindowButton::BUTTON_MINIMIZE, this);
        m_ButtonClose = new CWindowButton(CWindowButton::BUTTON_CLOSE, this);

        connect(m_ButtonMinimize, SIGNAL(clicked()),
                this, SLOT(minimized()));

        connect(m_ButtonClose, SIGNAL(clicked()),
                window, SLOT(quit()));
        break;

    case BUTTON_CLOSE:
        m_ButtonClose = new CWindowButton(CWindowButton::BUTTON_CLOSE, this);

        connect(m_ButtonClose, SIGNAL(clicked()),
                window, SLOT(quit()));
        break;
    }

    setFixedHeight(25);

    m_Title.setStyleSheet("color: white; font-family: Sans; font-weight: bold; font-size: 14px");
    m_Title.move(BORDER_SIZE + 5, 4);
}

CWindowTitleBar::~CWindowTitleBar()
{
    if (m_ButtonMinimize) delete m_ButtonMinimize;
    if (m_ButtonClose) delete m_ButtonClose;

    delete m_Cache;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CWindowTitleBar::updateWindowTitle(QString title)
{
    m_Title.setText(title);
}

void CWindowTitleBar::minimized()
{
    window()->showMinimized();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Protected method
//-------------------------------------------------------------------------------------------------------------------------------

void CWindowTitleBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    delete m_Cache;

    m_Cache = new QPixmap(size());
    // Fill transparent
    m_Cache->fill(Qt::transparent);

    if (m_TitleBar)
    {
        QPainter painter(m_Cache);

        QLinearGradient gradient(BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, height() - BORDER_SIZE - 2);

        QColor gradFirst("#555");
        QColor gradSecond("#111");

        gradFirst.setAlpha(150);
        gradSecond.setAlpha(150);

        gradient.setColorAt(0, gradFirst);
        gradient.setColorAt(1, gradSecond);

        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);

        painter.drawRect(BORDER_SIZE, BORDER_SIZE, width() - BORDER_SIZE - 2, height() - BORDER_SIZE - 2);
    }

    if (m_ButtonMinimize) m_ButtonMinimize->move(width() - m_ButtonMinimize->width() * 2 - BORDER_SIZE * 3, BORDER_SIZE * 2);
    if (m_ButtonClose) m_ButtonClose->move(width() - m_ButtonClose->width() - BORDER_SIZE * 2, BORDER_SIZE * 2);
}

void CWindowTitleBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if(m_Cache)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_Cache);
    }
}

void CWindowTitleBar::mousePressEvent(QMouseEvent *event)
{
    m_CanMove = true;
    m_ShiftDiff = event->pos();
}

void CWindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_CanMove = false;
}

void CWindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_CanMove)
    {
        QPoint point = event->globalPos();

        window()->move(point - m_ShiftDiff);
    }
}

