#ifndef CCUSTOMWINDOW_H
#define CCUSTOMWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPixmap>

#include "StyleDefines.h"
#include "CWindowTitleBar.h"

class CCustomWindow : public QWidget
{
    Q_OBJECT

signals:
    void Style_windowTitleChanged(const QString &title);
    void Style_quit();

public:
    CCustomWindow(QString background, QWidget *parent = 0, EButtonWindowTitle type = BUTTON_ALL, QSize size = QSize(800, 400), bool titleBar = false);
    CCustomWindow(QColor background, QWidget *parent = 0, EButtonWindowTitle type = BUTTON_ALL, QSize size = QSize(800, 400), bool titleBar = false);
    ~CCustomWindow();

    void setWindowTitle(const QString &title);

public slots:
    void quit();

protected:
    void paintEvent(QPaintEvent *event);

private:
    CWindowTitleBar m_TitleBar;
    QGridLayout m_MainLayout;

    QPixmap m_Background;
};

#endif // CCUSTOMWINDOW_H
