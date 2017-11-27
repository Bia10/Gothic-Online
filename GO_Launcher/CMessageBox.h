#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <memory>
#include <QVector>

#include "Style/CCustomWindow.h"

namespace Ui {
    class CMessageBox;
}

class CMessageBox;

typedef std::shared_ptr<CMessageBox> Ref_CMessageBox;

class CMessageBox : public CCustomWindow
{
    Q_OBJECT

public:
    explicit CMessageBox(bool showButtonOk = true);
    explicit CMessageBox(QSize size);
    ~CMessageBox();

    static void clearData();
    static void warrning(const QString title, const QString message, QSize size = QSize(380, 140));

    void setText(QString text);

private:
    Ui::CMessageBox *ui;
    Ref_CMessageBox m_This;
    static QVector<Ref_CMessageBox> m_ListBox;

private slots:
    void onButtonOkClicked();

friend class CMessageBox;
};

#endif // CMESSAGEBOX_H
