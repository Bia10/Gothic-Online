#ifndef SLAUNCHER_H
#define SLAUNCHER_H

#include <QApplication>
#include <QSplashScreen>

#include "Style/CCustomWindow.h"
#include "CLanguage.h"
#include "CServerManager.h"
#include "CSettings.h"
#include "CInternetManager.h"
#include "CFavoriteManager.h"
#include "CNetwork.h"
#include "CAddons.h"
#include "COptions.h"
#include "CInject.h"
#include "CVersion.h"

#define LAUNCHER SLauncher::getInstance()

#define LEN_SKEY 64
static const char SKEY[LEN_SKEY + 1] = "cd3921bf336aa733e72ef9310383f2dbf99c965df6d58fe0563cf7d953f26f00";

namespace Ui {
    class SLauncher;
}

class SLauncher : public CCustomWindow
{
    Q_OBJECT

private:
    explicit SLauncher(QWidget *parent = 0);

public:
    ~SLauncher();

    // Static method
    static SLauncher& getInstance();

    // Normal Method
    void init();
    std::string getString(int amount, ...);
    std::string cryptString(int amount, ...);
    std::string decryptString(std::string cryptedStr);
    void setStatus(const QString status) const;
    QString getVersion();
    void enable();
    void disable();
    void translate();

    inline Ui::SLauncher*       getUI()                    { return ui; }
    inline CLanguage&           getLanguage()              { return m_Language; }
    inline CSettings&           getSettings()              { return m_Settings; }
    inline CServerManager*      getServerInternetManager() { return m_ServerInternet; }
    inline CServerManager*      getServerFavoriteManager() { return m_ServerFavorite; }
    inline CNetwork&            getNetwork()               { return m_Network; }
    inline CInternetManager&    getInternetManager()       { return m_InternetManager; }
    inline CFavoriteManager&    getFavoriteManager()       { return m_FavoriteManager; }
    inline CInject&             getInjector()              { return m_Injector; }
    inline CVersion&            getVersionManager()        { return m_Version; }

private:
    // Normal Method
    void initWidgets();
    void initConnections();
    void initMetaType();
    void loadCSS(QString filename);

    Ui::SLauncher *ui;
    CLanguage m_Language;
    QSplashScreen m_SplashScreen;
    CSettings m_Settings;
    CServerManager *m_ServerInternet, *m_ServerFavorite;
    CInternetManager m_InternetManager;
    CFavoriteManager m_FavoriteManager;
    CNetwork m_Network;
    CInject m_Injector;
    CVersion m_Version;

    CAddons *m_AddonWidget;
    COptions *m_OptionWidget;

    QString m_VersionName;

    // Version label
    QLabel m_VersionLabel;

private slots:
    void onQuit();
    void onRefresh();

friend class CNetwork;
};

#endif // SLAUNCHER_H
