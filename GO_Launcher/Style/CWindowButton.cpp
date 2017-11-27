#include <QPainter>

#include "CWindowButton.h"

CWindowButton::CWindowButton(EButtonType type, QWidget *parent) :
    QAbstractButton(parent),
    m_ButtonType(type),
    m_ButtonStatus(STATE_NORMAL),
    m_Normal(NULL),
    m_Hovered(NULL),
    m_Clicked(NULL)
{
    setFixedSize(15, 15);
}

CWindowButton::~CWindowButton()
{
    delete m_Normal;
    delete m_Hovered;
    delete m_Clicked;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Protected method
//-------------------------------------------------------------------------------------------------------------------------------

void CWindowButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    initPixmaps();
}

void CWindowButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    if(isEnabled())
    {
        switch(m_ButtonStatus)
        {
        case STATE_NORMAL:
            if (m_Normal != NULL) painter.drawPixmap(0, 0, *m_Normal);
        break;

        case STATE_HOVERED:
            if (m_Hovered != NULL) painter.drawPixmap(0, 0, *m_Hovered);
        break;

        case STATE_CLICKED:
            if (m_Clicked != NULL) painter.drawPixmap(0, 0, *m_Clicked);
        break;
        }
    }
    else
        if (m_Normal != NULL) painter.drawPixmap(0, 0, *m_Normal);
}

void CWindowButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_ButtonStatus = STATE_HOVERED;

    //setCursor(Qt::PointingHandCursor);
    update();
}

void CWindowButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_ButtonStatus = STATE_NORMAL;

    //setCursor(Qt::ArrowCursor);
    update();
}

void CWindowButton::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);

    m_ButtonStatus = STATE_CLICKED;

    update();
}

void CWindowButton::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractButton::mouseReleaseEvent(event);

    if(underMouse()) m_ButtonStatus = STATE_HOVERED;
    else m_ButtonStatus = STATE_NORMAL;

    update();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CWindowButton::initPixmaps()
{
    initPixmap(&m_Normal);
    initPixmap(&m_Hovered);
    initPixmap(&m_Clicked);

    switch(m_ButtonType)
    {
    case BUTTON_MINIMIZE:
        initMinimize();
    break;

    case BUTTON_CLOSE:
        initClose();
    break;
    }
}

void CWindowButton::initPixmap(QPixmap **pixmap)
{
    delete *pixmap;

    *pixmap = new QPixmap(size());
    (*pixmap)->fill(Qt::transparent);
}

void CWindowButton::initMinimize()
{
  QColor colorStart(0, 0, 0, 0);
  QColor colorEnd(0, 0, 0, 220);

  QLinearGradient gradient(0, 0, 0, height());
  gradient.setColorAt(0, colorStart);
  gradient.setColorAt(1, colorEnd);

  QLinearGradient gradientInvert(0, 0, 0, height());
  gradientInvert.setColorAt(0, colorEnd);
  gradientInvert.setColorAt(1, colorStart);

  QPainter painter;

  painter.begin(m_Normal);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(gradient));

  painter.drawEllipse(0, 0, width(), height());

  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::black));

  painter.drawRect(QRect(QPoint(3, height() - 7), QPoint(width() - 4, height() - 5)));

  painter.end();

  painter.begin(m_Hovered);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(gradient));

  painter.drawEllipse(0, 0, width(), height());

  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(QColor(200, 200, 200)));

  painter.drawRect(QRect(QPoint(3, height() - 7), QPoint(width() - 4, height() - 5)));

  painter.end();

  painter.begin(m_Clicked);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(gradientInvert));

  painter.drawEllipse(0, 0, width(), height());

  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::white));

  painter.drawRect(QRect(QPoint(3, height() - 7), QPoint(width() - 4, height() - 5)));

  painter.end();
}

void CWindowButton::initClose()
{
    QLine line1(QPoint(5, 5), QPoint(width() - 5, height() - 5)), line2(QPoint(width() - 5, 5), QPoint(5, height() - 5));

    QColor colorStart(0, 0, 0, 0);
    QColor colorEnd(0, 0, 0, 220);

    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, colorStart);
    gradient.setColorAt(1, colorEnd);

    QLinearGradient gradientInvert(0, 0, 0, height());
    gradientInvert.setColorAt(0, colorEnd);
    gradientInvert.setColorAt(1, colorStart);

    QPainter painter;

    painter.begin(m_Normal);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QBrush(gradient));

    painter.drawEllipse(0, 0, width(), height());

    painter.setPen(QPen(QBrush(Qt::black), 2.0));

    painter.drawLine(line1);
    painter.drawLine(line2);

    painter.end();

    painter.begin(m_Hovered);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QBrush(gradient));

    painter.drawEllipse(0, 0, width(), height());

    painter.setPen(QPen(QBrush(QColor(200, 200, 200)), 2.0));

    painter.drawLine(line1);
    painter.drawLine(line2);

    painter.end();

    painter.begin(m_Clicked);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QBrush(gradientInvert));

    painter.drawEllipse(0, 0, width(), height());

    painter.setPen(QPen(QBrush(Qt::white), 2.0));

    painter.drawLine(line1);
    painter.drawLine(line2);

    painter.end();
}

