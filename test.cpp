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

using namespace std;

const char *TEST::arrayshow() //const char *option)
{
    unsigned long ef;
    STARTSYSMAN::configR();
    for (ef = 0; ef <= 54; ef++){
        //int num;
        //const char neu1 = STARTSYSMAN::ConfigDateiList[ef].find_first_of(option,size_t(num));
        //mvwaddstr(STARTSYSMAN::START.TMPWin3,2+ef,1,ConfigDateiList[ef].c_str());
        return VARSYSMAN::ConfigDateiList[ef].c_str();
    }
    //return ConfigDateiList[ef].c_str();
    return nullptr;
}

void TEST::FolderList(void)
{
    string Pfad = string(get_current_dir_name());
    //"/home/aktony/Dokumente/Qt_workplace/sichern";
    //unsigned char dtype;
    DIR *Folder = opendir(Pfad.c_str()); //, *SubFolder;
    struct dirent *datei;
    while((datei = readdir(Folder)) != nullptr){
        //dtype = datei->d_type;
        //if (SubFolder = opendir(datei->d_name)){
        if(datei->d_type==4){
            wattrset(STARTSYSMAN::START.TMPWin2,COLOR_PAIR(14));
            waddstr(STARTSYSMAN::START.TMPWin2,datei->d_name);
            waddstr(STARTSYSMAN::START.TMPWin2,const_cast<char*>("\n"));
            //prefresh(STARTSYSMAN::START.TMPWin2::softpad3, 0, 0, 10, 21, STARTSYSMAN::myr-1, STARTSYSMAN::mxc-2);
            wrefresh(STARTSYSMAN::START.TMPWin2);
            //closedir(SubFolder);
        }else {
            wattrset(STARTSYSMAN::START.TMPWin2,COLOR_PAIR(01));
            waddstr(STARTSYSMAN::START.TMPWin2,datei->d_name);
            waddstr(STARTSYSMAN::START.TMPWin2,const_cast<char*>("\n"));
            //prefresh(Soft_Joe::softpad3, 0, 0, 10, 21, STARTSYSMAN::myr-1, STARTSYSMAN::mxc-2);
            wrefresh(STARTSYSMAN::START.TMPWin2);
        }
    }
    closedir(Folder);
}

void TEST::Anzeigen()
{
    for (int X=0;X<(SYSNETZWERK::maxIface+1);X++){
        wprintw(STARTSYSMAN::START.TMPWin2,"ID:            %d \n", VARSYSMAN::NETZWERK_IF[X].IF_ID);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Name:          ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Netzwerk Typ:  ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_Typ.c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"IP v 4:        ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_IPv4[0].c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"IP v 6:        ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_IPv6[0].c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"MAC Adresse:   ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_MAC.c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Netzmaske:     ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_NETMASK[0].c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Gateway:       ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].GW_IPv4[0].c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"MTU:           ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_MTU.c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Broadcast:     ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_BROADCAST[0].c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Hardware Name: ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_DeviceName.c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,"Treiber Name:  ",-1);
        waddnstr(STARTSYSMAN::START.TMPWin2,VARSYSMAN::NETZWERK_IF[X].IF_DRIVER.c_str(),-1);
        waddnstr(STARTSYSMAN::START.TMPWin2," \n",-1);
    }
}

void TEST::Colortest()
{
    WINDOW *test;
    WINDOW *test2;
    WINDOW *test3;
    WINDOW *test4;
    test = newwin(5, 10, 5, 5);
    test2 = newwin(5, 10, 5, 15);
    test3 = newwin(5, 10, 5, 30);
    test4 = newwin(5, 10, 5, 45);
    int d,c;
    short R=0,G=0,B=0;

    while((1) || (c=getch() != KEY_F(10)))
    {
        for(d= 0; d <= 1000; d++)
        {
            short COLOR_TEST=100, COLOR_TEST2=100, COLOR_TEST3=250, COLOR_TEST4=240;

            color_content(COLOR_TEST, &R, &G, &B);
            init_pair(61, COLOR_RED,COLOR_TEST);

            wbkgd(test,COLOR_PAIR(61));

            mvwprintw(STARTSYSMAN::START.TMPWin2,1,5,"%i R\n",R);
            mvwprintw(STARTSYSMAN::START.TMPWin2,2,5,"%i G\n",G);
            mvwprintw(STARTSYSMAN::START.TMPWin2,3,5,"%i B\n",B);

            init_color(COLOR_TEST2, R, G, static_cast<short int>(d));
            init_pair(62, COLOR_RED,COLOR_TEST2);

            wbkgd(test2,COLOR_PAIR(62));

            mvwprintw(STARTSYSMAN::START.TMPWin2,1,15,"%i R\n",COLOR_TEST2);
            mvwprintw(STARTSYSMAN::START.TMPWin2,2,15,"%i G\n",d);
            mvwprintw(STARTSYSMAN::START.TMPWin2,3,15,"%i B\n",B);

            init_color(COLOR_TEST3, R, G, static_cast<short int>(300));
            init_pair(63, COLOR_RED,COLOR_TEST3);
            wbkgd(test3,COLOR_PAIR(63));

            init_color(COLOR_TEST4, R, G, static_cast<short int>(850));
            init_pair(64, COLOR_RED,COLOR_TEST4);
            wbkgd(test4,COLOR_PAIR(64));

            refresh();
            wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));
            wrefresh(VARSYSMAN::clearwindow(test));
            wrefresh(VARSYSMAN::clearwindow(test2));
            wrefresh(VARSYSMAN::clearwindow(test3));
            wrefresh(VARSYSMAN::clearwindow(test4));
            //sleep(1);
        }
        d = 0;
        //use_default_colors();
        //assume_default_colors(-1,-1);
    }
}

bool TEST::DirectoryExists( const char* pzPath ){
    DIR *pDir;
    bool bExists = false;
    pDir = opendir (pzPath);
    if (pDir != nullptr){
        bExists = true;
        closedir (pDir);
    }
    return bExists;
}

bool FileExists(const std::string & StrFileName)
{
    ifstream filecheck(StrFileName);
    bool test = false;
    if (filecheck){
        test = true;
    }
    return test;
}

void TEST::VendorDevice(string Interface)
{
    string path1 = "/sys/class/net/";
    string path2 = "/device/";
    string Device = "device";
    string Vendor = "vendor";
    string tmppath;
    string tmppath2;
    int IF_ID = 0;

    tmppath = path1;
    tmppath.append(Interface);

    for (int i = 0;i <= SYSNETZWERK::maxIface;i++)
    {   if (strcmp(Interface.c_str(),VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str())==0)
        {
            if (DirectoryExists(tmppath.c_str()) == true)
            {
                IF_ID = i;
                tmppath.append(path2);
                tmppath2 = tmppath;
                tmppath2.append(Vendor);
                string lesen;
                ifstream filestream(tmppath2.c_str());
                string delim = "x";
                size_t strchk;
                if (filestream.is_open())
                {
                    while (getline(filestream,lesen)) //(d<=54)
                    {
                        streampos oldpos = filestream.tellg();
                        strchk = size_t(lesen.find(delim));
                        if(strchk != std::string::npos){
                            filestream.seekg (oldpos);
                            std::string token = lesen.substr(lesen.find(delim)+1,lesen.length()-1);
                            VARSYSMAN::NETZWERK_IF[i].IF_VendorID = token;
                        }else{
                            filestream.seekg (oldpos);
                        }
                    }
                    filestream.close();
                }else {
                    cout << "File opening is fail."<<endl;
                }
                tmppath2 = tmppath;
                tmppath2.append(Device);
                ifstream filestream2(tmppath2.c_str());
                if (filestream2.is_open())
                {
                    while (getline(filestream2,lesen))
                    {
                        streampos oldpos = filestream2.tellg();
                        strchk = size_t(lesen.find(delim));
                        if(strchk != std::string::npos){
                            filestream2.seekg (oldpos);
                            std::string token = lesen.substr(lesen.find(delim)+1,lesen.length()-1);
                            VARSYSMAN::NETZWERK_IF[i].IF_DeviceID = token;
                        }else{
                            filestream2.seekg (oldpos);
                        }
                    }
                    filestream2.close();
                }else {
                    cout << "File opening is fail."<<endl;
                }
            } else {
                mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3,7,33,Interface.c_str());
                wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin1));
                prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin3), 0, 0, 7, 1, STARTSYSMAN::max_yr,STARTSYSMAN::max_xc-1);
                prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin4), 0, 0, 20,39,22,79);
            }
        }
    }
    TEST::NAMENsuche(IF_ID);
}

void TEST::NAMENsuche(int ifid)
{
    string PCI_ID = "/usr/share/misc/pci.ids";

    ifstream filestream_pci(PCI_ID.c_str());
    string line_pci;
    string Kontrolle;

    if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorID.c_str(),"")!=0)
    {
        while(std::getline(filestream_pci, line_pci))
        {
            if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName.c_str(),"")==0
                    && strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName.c_str(),"")==0)
            {
                if(line_pci.substr(0,4).compare(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorID.c_str()) == 0
                        && line_pci.at(5) == ' ' )
                {
                    unsigned long lenge = line_pci.length();
                    VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName = line_pci.substr(6,lenge);
                    Kontrolle = line_pci.substr(6,lenge);
                }
            }else if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName.c_str(),Kontrolle.c_str())==0
                      && strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName.c_str(),"") == 0){
                string puffer = "\t";
                puffer.append(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceID.c_str());
                if(line_pci.substr(0,5).compare(puffer.c_str()) == 0
                        && line_pci.at(6) == ' ' )
                {
                    unsigned long lenge2 = line_pci.length();
                    VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName = line_pci.substr(7,lenge2);
                    break;
                }
            }
        }
    }
    filestream_pci.close();
}

void TEST::HWname()
{
    string t1 = "";
    string ls = "";
    string t2 = "";
    unsigned long len = 0;

    for (int X =0;X<=SYSNETZWERK::maxIface;X++)
    {
        t1 = "lshw -short -c network | grep -e ";
        //t1 = "hwinfo --netcard --only ";
        t1.append(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str());
        //t1.append(" | grep -e Model:"); // -e Driver: -e 'HW Address:'");
        ls = VARSYSMAN::TERM_AUSGABE(t1);
        len = ls.length();

        if (ls.length()>0){
            t2 = ls.substr(42,len-3);
            VARSYSMAN::find_and_replace(t2, "\n", "");
            //            VARSYSMAN::NETZWERK_IF[X].IF_HWNA = t2;
        }

        t1 = "ethtool -i ";
        t1.append(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str());
        t1.append(" | grep -e driver:");
        ls = VARSYSMAN::TERM_AUSGABE(t1);
        len = ls.length();

        if (ls.length()>0){
            t2 = ls.substr(8,len);
            VARSYSMAN::find_and_replace(t2, "\n", "");
            VARSYSMAN::NETZWERK_IF[X].IF_DRIVER = t2;
        }
    }
}

char *TEST::ntoa(int addr){
    static char buffer[18];
    sprintf(buffer, "%d.%d.%d.%d",
            (addr & 0x000000FF),
            (addr & 0x0000FF00) >>  8,
            (addr & 0x00FF0000) >> 16,
            (addr & 0xFF000000) >> 24);
    return buffer;
}

void TEST::InterfacesDatei()
{
    int letzteLineNr = VARSYSMAN::Datei_Letzte_Line(VARSYSMAN::ConfigDateiList[0]);
    int lineNr = 1;
    string Lesen;
    string NextLesen;
    for (int Q = 0; Q <= SYSNETZWERK::maxIface; Q++)
    {
        lineNr = 1;
        ifstream filestream(VARSYSMAN::ConfigDateiList[0].c_str());
        if (filestream.is_open())
        {
            while (getline(filestream,Lesen))
            {
                if (letzteLineNr>=(lineNr+1)){
                    NextLesen = VARSYSMAN::Datei_Zeile_Nr(VARSYSMAN::ConfigDateiList[0],lineNr+1);
                }
                unsigned long LesenLeange = Lesen.length();
                std::string::size_type FIFname = Lesen.find(VARSYSMAN::NETZWERK_IF[Q].IF_Name[0]);
                std::string::size_type Fauto = Lesen.find("auto");
                std::string::size_type Fallow_hotplug = Lesen.find("allow-hotplug");
                std::string::size_type Fmanual = Lesen.find("manual");
                std::string::size_type FLoopback = Lesen.find("loopback");
                std::string::size_type Fdhcp = Lesen.find("dhcp");
                std::string::size_type Fstatic = Lesen.find("static");

                if (Lesen.substr(0,1).compare("#") == 0){
                    //continue;
                }else if(lineNr >= static_cast<int>(*VARSYSMAN::NETZWERK_IF[Q].IF_Name[0].c_str()) && LesenLeange > 0) {
                    if(FIFname!=std::string::npos){
                        if(Fauto!=std::string::npos){ //auto
                            VARSYSMAN::NETZWERK_IF[Q].IF_CLASS = "auto";
                        }else if(Fallow_hotplug!=std::string::npos){ //allow-hotplug
                            VARSYSMAN::NETZWERK_IF[Q].IF_CLASS = "allow-hotplug";
                        }else if(Fmanual!=std::string::npos){ //manual
                            VARSYSMAN::NETZWERK_IF[Q].IF_CLASS = "manual";
                        }else if(FLoopback!=std::string::npos) { //loopback
                            VARSYSMAN::NETZWERK_IF[Q].IF_MODE = Lesen.substr(LesenLeange-8,LesenLeange);
                        }else if(Fdhcp!=std::string::npos) { //dhcp
                            VARSYSMAN::NETZWERK_IF[Q].IF_MODE = Lesen.substr(LesenLeange-4,LesenLeange);
                        }else if(Fstatic!=std::string::npos) { //static
                            VARSYSMAN::NETZWERK_IF[Q].IF_MODE = Lesen.substr(LesenLeange-6,LesenLeange);
                        }
                    }else if(FIFname == std::string::npos){
                        if(Lesen.substr(0,8).compare("\taddress") == 0 && Lesen.at(8) == ' '){ //\taddresss
                            VARSYSMAN::NETZWERK_IF[Q].IF_IPv4[0] = Lesen.substr(9,LesenLeange);
                        }else if(Lesen.substr(0,7).compare("address") == 0 && Lesen.at(7) == ' '){ //address
                            VARSYSMAN::NETZWERK_IF[Q].IF_IPv4[0] = Lesen.substr(8,LesenLeange);
                        }else if(Lesen.substr(0,8).compare("\tnetmask") == 0 && Lesen.at(8) == ' '){ //\tnetmask
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETMASK[0] = Lesen.substr(9,LesenLeange);
                        }else if(Lesen.substr(0,7).compare("netmask") == 0 && Lesen.at(7) == ' ') { //netmask
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETMASK[0] = Lesen.substr(8,LesenLeange);
                        }else if(Lesen.substr(0,8).compare("\tgateway") == 0 && Lesen.at(8) == ' ') { //\tgateway
                            VARSYSMAN::NETZWERK_IF[Q].GW_IPv4[0] = Lesen.substr(9,LesenLeange);
                        }else if(Lesen.substr(0,7).compare("gateway") == 0 && Lesen.at(7) == ' ') { //gateway
                            VARSYSMAN::NETZWERK_IF[Q].GW_IPv4[0] = Lesen.substr(8,LesenLeange);
                        }else if(Lesen.substr(0,8).compare("\tnetwork") == 0 && Lesen.at(8) == ' ') { //\tnetwork
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETWORK[0] = Lesen.substr(9,LesenLeange);
                        }else if(Lesen.substr(0,7).compare("network") == 0 && Lesen.at(7) == ' ') { //network
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETWORK[0] = Lesen.substr(11,LesenLeange);
                        }else if(Lesen.substr(0,10).compare("\tbroadcast") == 0 && Lesen.at(10) == ' ') {//\tbroadcast
                            VARSYSMAN::NETZWERK_IF[Q].IF_BROADCAST[0] = Lesen.substr(11,LesenLeange);
                        }else if(Lesen.substr(0,9).compare("broadcast") == 0 && Lesen.at(9) == ' ') { //broadcast
                            VARSYSMAN::NETZWERK_IF[Q].IF_BROADCAST[0] = Lesen.substr(10,LesenLeange);
                        }else if(Lesen.substr(0,16).compare("\tdns-nameservers") == 0 && Lesen.at(16) == ' ') { //\tdns-nameservers
                            VARSYSMAN::NETZWERK_IF[Q].DNS_NAMESERVERS[0] = Lesen.substr(17,LesenLeange);
                        }else if(Lesen.substr(0,15).compare("dns-nameservers") == 0 && Lesen.at(15) == ' ') { //dns-nameservers
                            VARSYSMAN::NETZWERK_IF[Q].DNS_NAMESERVERS[0] = Lesen.substr(16,LesenLeange);
                        }else if(Lesen.substr(0,11).compare("\tdns-search") == 0 && Lesen.at(11) == ' ') { //\tdns-search
                            VARSYSMAN::NETZWERK_IF[Q].DNS_SEARCH[0] = Lesen.substr(12,LesenLeange);
                        }else if(Lesen.substr(0,10).compare("dns-search") == 0 && Lesen.at(10) == ' ') { //dns-search
                            VARSYSMAN::NETZWERK_IF[Q].DNS_SEARCH[0] = Lesen.substr(11,LesenLeange);
                        }else if(Lesen.substr(0,11).compare("\twpa-driver") == 0 && Lesen.at(11) == ' ') { //\twpa-driver
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_Driver[0] = Lesen.substr(12,LesenLeange);
                        }else if(Lesen.substr(0,10).compare("wpa-driver") == 0 && Lesen.at(10) == ' ') { //wpa-driver
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_Driver[0] = Lesen.substr(11,LesenLeange);
                        }else if(Lesen.substr(0,9).compare("\twpa-conf") == 0 && Lesen.at(9) == ' ') { //\twpa-conf
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_CONF[0] = Lesen.substr(10,LesenLeange);
                        }else if(Lesen.substr(0,8).compare("wpa-conf") == 0 && Lesen.at(8) == ' ') { //wpa-conf
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_CONF[0] = Lesen.substr(9,LesenLeange);
                        }
                    }
                }else if(lineNr >= static_cast<int>(*VARSYSMAN::NETZWERK_IF[Q].IF_Name[1].c_str()) && LesenLeange <= 0) {
                    break;
                }
                lineNr++;
            }
        }else {
            cout << "File opening is fail."<<endl;
        }
        filestream.close();
    }
}

void TEST::test()
{

}



