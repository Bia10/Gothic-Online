#ifndef CMESSAGEBOXLIST_H
#define CMESSAGEBOXLIST_H

#include <QVector>

#include "CMessageBox.h"

typedef QVector<CMessageBox> ListBox;

class CMessageBoxList
{
public:
    inline ListBox& getListBox() { return m_ListBox; }

private:
    ListBox m_ListBox;
};

#endif // CMESSAGEBOXLIST_H
