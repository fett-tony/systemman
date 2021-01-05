#ifndef WPA_CONNECT_H
#define WPA_CONNECT_H

#include <VarSysMan.h>
#include <StartSysMan.h>

class WPA_CONNECT
{
public:
    static string wlanstatus;
    static string VG1;
    //#####################################
    static void fensterdesign(void);
    static void GetStdoutFromCommand(string cmd, int opt);
    static void Wlan_button(void);
    static void Wlan_Iface(void);
    static void BefZusa(string name);
    static void Connection(void);
    static string GetStdoutFromCommand2(string cmd);
    static void QuitWPACon();
private:

protected:

};

#endif // WPA_CONNECT_H
