#ifndef DATEIMANPAGE_H
#define DATEIMANPAGE_H

#include <VarSysMan.h>
#include <StartSysMan.h>

class DATEIMANPAGE
{
public:
    static unsigned long count;
    static std::vector<std::string> LXTermApps;
//###############################################################
    static void FensterDesign();
    static void FolderList(void);
    static unsigned long DirCount(string Pfad);
    static void Start_ManP(void);
    static void ManPageMenu();
    static void QUIT_MANP();
    DATEIMANPAGE();

private:

protected:
};

#endif // DATEIMANPAGE_H
