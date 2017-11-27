#include "PCH.h"

char CFavorite::allowedChars[ALLOWED_CHAR_SIZE + 1] = "0123456789.";

CFavorite::CFavorite(QWidget *parent) :
    CCustomWindow(QColor("#333"), parent, BUTTON_CLOSE, QSize(240, 85), true),
    ui(new Ui::CFavorite)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    ui->setupUi(this);

    initConnections();
    translate();
}

CFavorite::~CFavorite()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    delete ui;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CFavorite::translate()
{
    ui->buttonOk->setText(TRANSLATE("F_OK"));
    ui->labelIP->setText(TRANSLATE("F_ADRESS"));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CFavorite::initConnections()
{
    connect(this, SIGNAL(Style_quit()),
            this, SLOT(close()));

    connect(ui->buttonOk, SIGNAL(released()),
            this, SLOT(onButtonOkClicked()));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CFavorite::onButtonOkClicked()
{
    if (ui->editIP->text().isEmpty())
    {
        CMessageBox::warrning(TRANSLATE("L_FAVORITE"), TRANSLATE("F_ERR_01"));
        return;
    }

    // Check port
    int iter = 0;
    bool found = false;

    while ((iter = ui->editIP->text().indexOf(":")) != -1 && !found)
    {
        found = true;
    }

    QString serverHost, serverPort;
    if (found)
    {
        serverHost = ui->editIP->text().mid(0, iter);
        serverPort = ui->editIP->text().mid(iter + 1);
    }
    else
    {
        serverHost = ui->editIP->text();
        serverPort = TOSTRING(DEFAULT_PORT);
    }

    for (int i = 0; i < serverHost.length(); ++i)
    {
        bool exist = false;
        for (int j = 0; j < ALLOWED_CHAR_SIZE; ++j)
            if (serverHost[i] == allowedChars[j])
                exist = true;

        if (!exist)
        {
            CMessageBox::warrning(TRANSLATE("L_FAVORITE"), TRANSLATE("F_ERR_02"));
            return;
        }
    }

    for (int i = 0; i < serverPort.length(); ++i)
    {
        bool exist = false;
        for (int j = 0; j < ALLOWED_CHAR_SIZE - 1; ++j)
            if (serverPort[i] == allowedChars[j])
                exist = true;

        if (!exist)
        {
            CMessageBox::warrning(TRANSLATE("L_FAVORITE"), TRANSLATE("F_ERR_03"));
            return;
        }
    }

    close();

    emit signalButtonOkClicked(serverHost, serverPort);
}
