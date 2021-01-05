#include <VarSysMan.h>
#include <StartSysMan.h>
#include <DateiBefehle.h>
#include <DateiManPage.h>
#include <HMenu.h>
#include <SoftAKInst.h>
#include <SysDateiRechte.h>
#include <SysNetzwerk.h>
#include <SysNetzIface.h>
#include <SysNetzMenu.h>
#include <SysNetzWPACon.h>
#include <SysNetzWPAScan.h>
#include <test.h>

VARSYSMAN::FENSTERWLANSCAN VARSYSMAN::WLANSCAN;

void WPA_WLANSCAN::FensterDesign(void)
{
    STARTSYSMAN::START.TMPWin3 = VARSYSMAN::DelTmpWin(STARTSYSMAN::START.TMPWin3);
    delwin(STARTSYSMAN::START.TMPWin3);
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-2,STARTSYSMAN::max_xc,2,0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    VARSYSMAN::WLANSCAN.TMPWinHigh1 = STARTSYSMAN::max_yr-9;
    VARSYSMAN::WLANSCAN.TMPWin1 = newpad(VARSYSMAN::WLANSCAN.TMPWinHigh1, STARTSYSMAN::max_xc-2);
    wbkgd(VARSYSMAN::WLANSCAN.TMPWin1,COLOR_PAIR(11));
    STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::WLANSCAN.TMPWin1, VARSYSMAN::WLANSCAN.TMPWinHigh1, STARTSYSMAN::max_xc-2, 8, 1);
    wsetscrreg(VARSYSMAN::WLANSCAN.TMPWin1, 0, STARTSYSMAN::max_yr-3);
    scrollok(VARSYSMAN::WLANSCAN.TMPWin1, true);
    //  scroll(WPA_WLANSCAN::TMPWIN1);
}

void WPA_WLANSCAN::WPA_Start()
{
    VARSYSMAN::WLANSCAN.FEID = 7;
    VARSYSMAN::WLANSCAN.FENAME = string("WPA");

    WPA_WLANSCAN::FensterDesign();

    refresh();
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WLANSCAN.TMPWin1));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WLANSCAN.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);

    const char *tmpNA = nullptr;
    tmpNA = item_description(current_item(HMenu::MENEU[3].HMMenu));
    mvwaddstr(VARSYSMAN::WLANSCAN.TMPWin1, 10, 5, tmpNA);

    refresh();
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WLANSCAN.TMPWin1));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WLANSCAN.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
}
