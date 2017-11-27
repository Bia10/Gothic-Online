#include <QPainter>
#include <QPaintEvent>

#include "CCustomWindow.h"

CCustomWindow::CCustomWindow(QString background, QWidget *parent, EButtonWindowTitle type, QSize size, bool titleBar) :
    QWidget(parent),
    m_TitleBar(parent, this, type, titleBar)
{
    connect(this, SIGNAL(Style_windowTitleChanged(QString)),
            &m_TitleBar, SLOT(updateWindowTitle(QString)));

    if (background != "NO_BG")
        m_Background = QPixmap(background);
    else
        m_Background = QPixmap(size);

    m_MainLayout.setMargin(0);
    m_MainLayout.setSpacing(0);

    m_MainLayout.addWidget(&m_TitleBar, 0, 0, 1, 1);
    m_MainLayout.setRowStretch(1, 1);

    setLayout(&m_MainLayout);

    setFixedSize(m_Background.width(), m_Background.height());

    setWindowFlags(Qt::FramelessWindowHint);
}

CCustomWindow::CCustomWindow(QColor background, QWidget *parent, EButtonWindowTitle type, QSize size, bool titleBar) :
    QWidget(parent),
    m_TitleBar(parent, this, type, titleBar)
{
    connect(this, SIGNAL(Style_windowTitleChanged(QString)),
            &m_TitleBar, SLOT(updateWindowTitle(QString)));

    m_Background = QPixmap(size);
    m_Background.fill(background);

    m_MainLayout.setMargin(0);
    m_MainLayout.setSpacing(0);

    m_MainLayout.addWidget(&m_TitleBar, 0, 0, 1, 1);
    m_MainLayout.setRowStretch(1, 1);

    setLayout(&m_MainLayout);

    setFixedSize(size.width(), size.height());

    setWindowFlags(Qt::FramelessWindowHint);
}

CCustomWindow::~CCustomWindow()
{

}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CCustomWindow::setWindowTitle(const QString &title)
{
    QWidget::setWindowTitle(title);

    emit Style_windowTitleChanged(title);
}

void CCustomWindow::quit()
{
    emit Style_quit();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Protected method
//-------------------------------------------------------------------------------------------------------------------------------

void CCustomWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_Background);

    QBrush border(QColor(0, 0, 0, 200));
    painter.setBrush(border);
    painter.setPen(Qt::NoPen);

    painter.drawRect(0, 0, width(), BORDER_SIZE);
    painter.drawRect(0, BORDER_SIZE, BORDER_SIZE, height() - BORDER_SIZE * 2);
    painter.drawRect(width() - BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, height() - BORDER_SIZE * 2);
    painter.drawRect(0, height() - BORDER_SIZE, width(), height());
}
