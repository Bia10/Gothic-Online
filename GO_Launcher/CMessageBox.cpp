#include "PCH.h"

QVector<Ref_CMessageBox> CMessageBox::m_ListBox;

CMessageBox::CMessageBox(bool showButtonOk) :
    CCustomWindow(QColor("#333"), NULL, BUTTON_NONE, QSize(380, 140), true),
    ui(new Ui::CMessageBox)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    ui->setupUi(this);

    if (showButtonOk)
        connect(ui->buttonOk, SIGNAL(released()),
                this, SLOT(close()));
    else
        ui->buttonOk->hide();

    ui->labelMessage->setOpenExternalLinks(true);

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

CMessageBox::CMessageBox(QSize size) :
    CCustomWindow(QColor("#333"), NULL, BUTTON_NONE, size, true),
    ui(new Ui::CMessageBox)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    ui->setupUi(this);

    ui->labelMessage->setOpenExternalLinks(true);

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

CMessageBox::~CMessageBox()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    delete ui;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CMessageBox::clearData()
{
    m_ListBox.clear();
}

void CMessageBox::warrning(const QString title, const QString message, QSize size)
{
    m_ListBox.append(Ref_CMessageBox(new CMessageBox(size)));

    Ref_CMessageBox messageBox = m_ListBox.last();

    messageBox->m_This = messageBox;
    messageBox->setWindowTitle(title);
    messageBox->ui->labelMessage->setText(message);

    connect(messageBox->ui->buttonOk, SIGNAL(released()),
            messageBox.get(), SLOT(onButtonOkClicked()));

    messageBox->show();
}

void CMessageBox::setText(QString text)
{
    ui->labelMessage->setText(text);
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CMessageBox::onButtonOkClicked()
{
    m_ListBox.removeOne(m_This);
    m_This = NULL; // Destroy, safe way
}
