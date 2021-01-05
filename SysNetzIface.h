#ifndef SYSNETZIFACE_H
#define SYSNETZIFACE_H

#include <VarSysMan.h>

class SYSNETZIFACE
{
public:
    static std::vector<std::string::size_type> finden;
//#############################################################
    static void SYSNETZIFACE_START();
    static void Einstellung_IF_Menu(void);
    static void Netz_einstellung();
    static void NETZ_KEY_PAD();
    static void Netzwerk_IF_Menu(void);
    static void Menu_Ausfuehren(string Button, int Button_ID);
    static void InterfacesIfaceNr();
    static void InterfacesDatei();
    static void next_Iface();
    static void FensterDesign();

private:
    //struct to hold collected information
    struct signalInfo {
        char mac[18];
        char ssid[33];
        int bitrate;
        int level;
    };
    static int getSignalInfo(signalInfo *sigInfo, char *iwname);

protected:

};

#endif // SYSNETZIFACE_H
