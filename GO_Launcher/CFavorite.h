#ifndef CFAVORITE_H
#define CFAVORITE_H

#include <QWidget>

#include "Style/CCustomWindow.h"

#define ALLOWED_CHAR_SIZE 11

namespace Ui {
    class CFavorite;
}

class CFavorite : public CCustomWindow
{
    Q_OBJECT

signals:
    void signalButtonOkClicked(QString host, QString port);

public:
    explicit CFavorite(QWidget *parent = 0);
    ~CFavorite();

    void translate();

private:
    void initConnections();

    Ui::CFavorite *ui;
    static char allowedChars[ALLOWED_CHAR_SIZE + 1];

private slots:
    void onButtonOkClicked();

friend class CFavoriteManager;
};

#endif // CFAVORITE_H
