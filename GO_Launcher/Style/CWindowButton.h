#ifndef CWINDOWBUTTON_H
#define CWINDOWBUTTON_H

#include <QAbstractButton>
#include <QPixmap>

class CWindowButton : public QAbstractButton
{
    Q_OBJECT

public:
    enum EButtonType
    {
        BUTTON_MINIMIZE,
        BUTTON_CLOSE
    };

    CWindowButton(EButtonType type, QWidget *parent = 0);
    ~CWindowButton();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

    enum EButtonStatus
    {
        STATE_NORMAL,
        STATE_HOVERED,
        STATE_CLICKED
    };

    void initPixmaps();
    void initPixmap(QPixmap **pixmap);
    void initMinimize();
    void initClose();

    EButtonType m_ButtonType;
    EButtonStatus m_ButtonStatus;

    QPixmap *m_Normal, *m_Hovered, *m_Clicked;
};

#endif // CWINDOWBUTTON_H
