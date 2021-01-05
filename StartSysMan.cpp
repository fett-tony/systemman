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

FENSTER STARTSYSMAN::START;
int STARTSYSMAN::max_yr, STARTSYSMAN::rows, STARTSYSMAN::fmyr;
int STARTSYSMAN::max_xc, STARTSYSMAN::cols, STARTSYSMAN::fmxc;
static void finish(int sig);

void STARTSYSMAN::init_curse()
{
    setlocale(LC_CTYPE,"de_DE.UTF-8");
    initscr();
    cbreak();
    //raw();
    //(void) nonl();
    noecho();
    //clear();
    curs_set(0);
    //syncok(stdscr,true);
    keypad(stdscr, TRUE);

}

void STARTSYSMAN::AppColor()
{
    start_color();
    short MY_MARIN_BLUE=240, MY_LIGHT_BLUE=250;
    short R=0,G=0;//,B=0;
    init_color(MY_MARIN_BLUE, R, G, static_cast<short int>(300));
    init_color(MY_LIGHT_BLUE, R, G, static_cast<short int>(850));

    /* hintergrund Blau */
    init_pair(01, COLOR_WHITE, COLOR_BLUE);
    init_pair(02, COLOR_MAGENTA,COLOR_BLUE);
    init_pair(03, COLOR_RED,COLOR_BLUE);
    init_pair(04, COLOR_BLACK,COLOR_BLUE);
    init_pair(05, COLOR_YELLOW,COLOR_BLUE);
    init_pair(06, MY_MARIN_BLUE,COLOR_BLUE);
    /* hintergrund Schwarz */
    init_pair(11, COLOR_WHITE,COLOR_BLACK);
    init_pair(12, COLOR_RED,COLOR_BLACK);
    init_pair(13, COLOR_YELLOW,COLOR_BLACK);
    init_pair(14, COLOR_GREEN,COLOR_BLACK);
    init_pair(15, COLOR_CYAN,COLOR_BLACK);
    /* hintergrund gelb */
    init_pair(21, COLOR_BLUE, COLOR_YELLOW);
    init_pair(22, COLOR_BLACK,COLOR_YELLOW);
    init_pair(23, COLOR_GREEN,COLOR_YELLOW);
    /* hintergrund weiß */
    init_pair(31, COLOR_RED,COLOR_WHITE);
    init_pair(32, COLOR_BLACK,COLOR_WHITE);
    init_pair(33, COLOR_BLUE,COLOR_WHITE);
    init_pair(34, COLOR_YELLOW,COLOR_WHITE);
    init_pair(35, MY_MARIN_BLUE,COLOR_WHITE);
    /* hintergrund Rot */
    init_pair(41, COLOR_BLACK,COLOR_RED);
    init_pair(42, COLOR_WHITE,COLOR_RED);
    /**/
    init_pair(51, COLOR_WHITE,COLOR_CYAN);
    init_pair(52, COLOR_YELLOW,COLOR_CYAN);
    init_pair(53, COLOR_RED,COLOR_CYAN);
    /**/
    init_pair(61, COLOR_WHITE,MY_MARIN_BLUE);
    init_pair(62, COLOR_YELLOW,MY_MARIN_BLUE);
    init_pair(63, COLOR_RED,MY_MARIN_BLUE);
    /*  Light Blue hintergrund  */
    init_pair(71, COLOR_WHITE,MY_LIGHT_BLUE);
    init_pair(72, COLOR_YELLOW,MY_LIGHT_BLUE);
    init_pair(73, COLOR_RED,MY_LIGHT_BLUE);
} /*---------Programm_Farben------------------------*/

void STARTSYSMAN::FensterDesign(void)
{
    STARTSYSMAN::START.FEID = 0;
    STARTSYSMAN::START.FENAME = string("VARSYSMAN");
    STARTSYSMAN::START.TMPWin1 = newwin(1, STARTSYSMAN::max_xc, 0, 0);
    HMenu::MENEU[0].HMWin = derwin(STARTSYSMAN::START.TMPWin1, 1, STARTSYSMAN::max_xc, 0, 0);
    STARTSYSMAN::START.TMPWin2 = newwin(STARTSYSMAN::max_yr-1, STARTSYSMAN::max_xc, 1, 0);
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-3, STARTSYSMAN::max_xc-2, 2, 1);
    //STARTSYSMAN::START.TMPWin3 = subwin(STARTSYSMAN::START.TMPWin2, STARTSYSMAN::max_yr-3, STARTSYSMAN::max_xc-2, 2, 1);
    //STARTSYSMAN::START.TMPWin4 = derwin(STARTSYSMAN::START.TMPWin2, STARTSYSMAN::max_yr-3, STARTSYSMAN::max_xc-2, 2, 1);
    wbkgd(STARTSYSMAN::START.TMPWin1, COLOR_PAIR(VARSYSMAN::HaMeFe_HG));
    wbkgd(STARTSYSMAN::START.TMPWin2, COLOR_PAIR(61));
    wbkgd(STARTSYSMAN::START.TMPWin3, COLOR_PAIR(61));

    box(STARTSYSMAN::START.TMPWin2, 0,0);
    box(STARTSYSMAN::START.TMPWin3, 0,0);

    wsetscrreg(STARTSYSMAN::START.TMPWin2,0,STARTSYSMAN::max_yr-3);
    scrollok(STARTSYSMAN::START.TMPWin2,true);
    //scroll(STARTSYSMAN::START.TMPWin2);

    refresh();
    wrefresh(STARTSYSMAN::START.TMPWin1);
    touchwin(STARTSYSMAN::START.TMPWin1);
    wrefresh(HMenu::MENEU[0].HMWin);
    touchwin(HMenu::MENEU[0].HMWin);
    wrefresh(STARTSYSMAN::START.TMPWin2);
    touchwin(STARTSYSMAN::START.TMPWin2);
    wrefresh(STARTSYSMAN::START.TMPWin3);
    touchwin(STARTSYSMAN::START.TMPWin3);
} /* Fenster sub */

void STARTSYSMAN::einDa(void)
{
    //werase(STARTSYSMAN::START.TMPWin3);
    int i;
    //STARTSYSMAN::configR();
    int mf_xc = STARTSYSMAN::max_xc -4;
    STARTSYSMAN::START.TMPField1 = static_cast<FIELD **>(calloc(23, sizeof(FIELD *)));
    STARTSYSMAN::START.TMPField1[0] = new_field(1, mf_xc, 3, 1, 20, 0); // 2,34
    STARTSYSMAN::START.TMPField1[1] = new_field(1, mf_xc, 5, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[2] = new_field(1, mf_xc, 7, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[3] = new_field(1, mf_xc, 9, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[4] = new_field(1, mf_xc, 11, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[5] = new_field(1, mf_xc, 13, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[6] = new_field(1, mf_xc, 15, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[7] = new_field(1, mf_xc, 17, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[8] = new_field(1, mf_xc, 19, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[9] = new_field(1, mf_xc, 21, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[10] = new_field(1, mf_xc, 25, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[11] = new_field(1, mf_xc, 27, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[12] = new_field(1, mf_xc, 29, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[13] = new_field(1, mf_xc, 31, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[14] = new_field(1, mf_xc, 33, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[15] = new_field(1, mf_xc, 35, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[16] = new_field(1, mf_xc, 37, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[17] = new_field(1, mf_xc, 39, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[18] = new_field(1, mf_xc, 40, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[19] = new_field(15, mf_xc, 42, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[20] = new_field(1, mf_xc, 58, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[21] = new_field(1, mf_xc, 59, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[22] = new_field(1, mf_xc, 60, 1, 20, 0);
    STARTSYSMAN::START.TMPField1[23] = nullptr;

    STARTSYSMAN::START.TMPForm1 = new_form(STARTSYSMAN::START.TMPField1);
    scale_form(STARTSYSMAN::START.TMPForm1, &STARTSYSMAN::fmyr, &STARTSYSMAN::fmxc);

    for ( i = 0; i < field_count( STARTSYSMAN::START.TMPForm1 ); i++){
        set_field_fore( STARTSYSMAN::START.TMPField1[i], COLOR_PAIR(11)); //|A_REVERSE);
        set_field_back( STARTSYSMAN::START.TMPField1[i], COLOR_PAIR(11));
        field_opts_on( STARTSYSMAN::START.TMPField1[i], O_VISIBLE);
        field_opts_off( STARTSYSMAN::START.TMPField1[i], O_EDIT);
        field_opts_on( STARTSYSMAN::START.TMPField1[i], O_ACTIVE);
        field_opts_on( STARTSYSMAN::START.TMPField1[i], O_SELECTABLE);
    }
    field_opts_on( STARTSYSMAN::START.TMPField1[19], O_WRAP);

    set_field_buffer(STARTSYSMAN::START.TMPField1[0], 0, VARSYSMAN::ConfigDateiList[0].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[1], 0, VARSYSMAN::ConfigDateiList[1].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[2], 0, VARSYSMAN::ConfigDateiList[2].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[3], 0, VARSYSMAN::ConfigDateiList[3].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[4], 0, VARSYSMAN::ConfigDateiList[4].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[5], 0, VARSYSMAN::ConfigDateiList[5].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[6], 0, VARSYSMAN::ConfigDateiList[6].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[7], 0, VARSYSMAN::ConfigDateiList[7].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[8], 0, VARSYSMAN::ConfigDateiList[8].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[9], 0, VARSYSMAN::ConfigDateiList[9].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[10], 0, VARSYSMAN::ConfigDateiList[10].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[11], 0, VARSYSMAN::ConfigDateiList[11].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[12], 0, VARSYSMAN::ConfigDateiList[12].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[13], 0, VARSYSMAN::ConfigDateiList[13].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[14], 0, VARSYSMAN::ConfigDateiList[14].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[15], 0, VARSYSMAN::ConfigDateiList[15].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[16], 0, VARSYSMAN::ConfigDateiList[16].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[17], 0, VARSYSMAN::ConfigDateiList[17].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[18], 0, VARSYSMAN::ConfigDateiList[18].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[19], 0, VARSYSMAN::ConfigDateiList[19].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[20], 0, VARSYSMAN::ConfigDateiList[20].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[21], 0, VARSYSMAN::ConfigDateiList[21].c_str());
    set_field_buffer(STARTSYSMAN::START.TMPField1[22], 0, VARSYSMAN::ConfigDateiList[22].c_str());

    STARTSYSMAN::START.TMPWin4 = newpad(STARTSYSMAN::fmyr+2, STARTSYSMAN::max_xc-2);

    form_driver(STARTSYSMAN::START.TMPForm1, REQ_OVL_MODE);
    set_form_opts(STARTSYSMAN::START.TMPForm1, O_NL_OVERLOAD);
    set_form_opts(STARTSYSMAN::START.TMPForm1, O_BS_OVERLOAD);

    //######################################################################################
    //set_form_win(STARTSYSMAN::START.TMPForm1, STARTSYSMAN::START.TMPWin4);
    //set_form_sub(STARTSYSMAN::START.TMPForm1, STARTSYSMAN::START.TMPWin4);
    //STARTSYSMAN::START.TMPWin3 = derwin(STARTSYSMAN::START.TMPWin4, max_y-3, max_x-2, 2, 1);
    //set_form_sub(STARTSYSMAN::START.TMPForm1, derwin(STARTSYSMAN::START.TMPWin4, STARTSYSMAN::max_y -3,STARTSYSMAN::max_x - 2, 2, 1));
    //######################################################################################

    set_form_win(STARTSYSMAN::START.TMPForm1, STARTSYSMAN::START.TMPWin2);
    set_form_sub(STARTSYSMAN::START.TMPForm1, STARTSYSMAN::START.TMPWin4);
    //set_form_sub(STARTSYSMAN::START.TMPForm1, subwin(STARTSYSMAN::START.TMPWin4, STARTSYSMAN::max_y -3,STARTSYSMAN::mxc - 2, 2, 1));
    //STARTSYSMAN::START.TMPWin4 = subwin(win4, STARTSYSMAN::max_x-3, STARTSYSMAN::mxc-2, 3, 2);

    wsetscrreg(STARTSYSMAN::START.TMPWin4,0,STARTSYSMAN::fmyr-3);
    scrollok(STARTSYSMAN::START.TMPWin4,true);
    scroll(STARTSYSMAN::START.TMPWin4);
    //immedok(STARTSYSMAN::START.TMPWin3,true);
    wbkgd(STARTSYSMAN::START.TMPWin4, COLOR_PAIR(61));

    post_form(STARTSYSMAN::START.TMPForm1);

    wattrset(STARTSYSMAN::START.TMPWin4,A_BOLD);
    mvwaddstr(STARTSYSMAN::START.TMPWin4,0,1,"1. Systemeinstellung");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,2,1,"1.1. Pfad zur interface Datei");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,4,1,"1.2. Pfad zur Hosts Datei");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,6,1,"1.3. Pfad zur resolv.conf");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,8,1,"1.4. NetworkManager Einstellung");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,10,1,"1.5. NM Verbindungsordner");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,12,1,"1.6. Samba Client Datei");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,14,1,"1.7. ufw Firewall");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,16,1,"1.8. ufw Firewall");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,18,1,"1.9. Grub");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,20,1,"1.10. Grub");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,22,1,"2. Server Dateien");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,24,1,"2.1. LDAP");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,26,1,"2.2. PhpLDAPadmin");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,28,1,"2.3. Samba-Server");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,30,1,"2.4. Kerberos Server");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,32,1,"2.5. DHCP Server ISC");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,34,1,"2.6. Nameserver Bind9");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,36,1,"2.7. Nameserver Bind9");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,38,1,"2.8. Wlan Access Point");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,41,1,"3. Software");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,57,1,"4. VARSYSMAN Config");
    mvwaddstr(STARTSYSMAN::START.TMPWin4,61,1,"5. Befehle");

    refresh();
    //prefresh(STARTSYSMAN::START.TMPWin4, 0, 0, 2, 1, STARTSYSMAN::max_y -2, STARTSYSMAN::max_x -2);
    STARTSYSMAN::ScrollPad(STARTSYSMAN::START.TMPWin4,2,1,STARTSYSMAN::max_yr-2,STARTSYSMAN::max_xc-2,STARTSYSMAN::fmyr+2);
}

void STARTSYSMAN::ClearScreen()
{
    if (!cur_term)
    {
        int result;
        setupterm( nullptr, STDOUT_FILENO, &result );
        if (result <= 0) return;
    }
    putp( tigetstr( "clear" ) );
}

void STARTSYSMAN::configR()
{
    vector<string>().swap(VARSYSMAN::ConfigDateiList);
    VARSYSMAN::CountConfigDatei = VARSYSMAN::Datei_Letzte_Line(VARSYSMAN::filename);
    int d=0;
    string tmpstr1,tmpstr2;
    ifstream filestream(VARSYSMAN::filename.c_str());
    string delim = "=";
    size_t strchk;
    if (filestream.is_open())
    {
        while (getline(filestream,tmpstr1))
        {
            streampos oldpos = filestream.tellg();
            strchk = size_t(tmpstr1.find(delim));
            if(strchk != std::string::npos){
                filestream.seekg (oldpos);
                tmpstr2 = tmpstr1.substr(tmpstr1.find(delim)+1,tmpstr1.length()-1);
                VARSYSMAN::ConfigDateiList.push_back(tmpstr2);
                d++;
            }else{
                filestream.seekg (oldpos);
            }
        }
        filestream.close();
    }else {
        cout << "File opening is fail."<<endl;
    }
}

void STARTSYSMAN::fensterwahl(const char *wahl)
{
    if (strcmp(wahl, "Man Page")==0){
        DATEIMANPAGE::Start_ManP();
    }else if (strcmp(wahl,"Befehle")==0){
        DATEIBEFEHLE::befehle_main();
    }else if (strcmp(wahl,"Einstellung")==0){
        STARTSYSMAN::einDa();
    }else if (strcmp(wahl,"Beenden")==0){
        exit(0);
    }else if (strcmp(wahl,"Netzwerk")==0){
        SYSNETZMENU::sys_main();
    }else if (strcmp(wahl,"Samba-Client")==0){

    }else if (strcmp(wahl,"Firewall")==0){
        //arrayshow("netzwerk1");
    }else if (strcmp(wahl,"Service")==0){

    }else if (strcmp(wahl,"Hardware")==0){
        //arrayshow("netzwerk1");
    }else if (strcmp(wahl,"Benutzer")==0){
        TEST::test();
    }else if (strcmp(wahl,"LDAP")==0){
        //arrayshow("netzwerk1");
    }else if (strcmp(wahl,"Samba-Server")==0){

    }else if (strcmp(wahl,"AK-UB-conf")==0){
        SOFTAKINSTALL::AK_UB_start();
    }else if (strcmp(wahl,"Datei Rechte")==0){
        SYSDATEIRECHTE::Start_Rechte();
    }else{

    }
}

void STARTSYSMAN::ScrollPad(WINDOW * SubWin, int StartY, int StartX, int Height, int Width, int PadHeight)
{
    int Choice = 0, Key = 0;
    keypad(SubWin, true);
    refresh();
    int cols = 0;
    while (Choice == 0)
    {
        prefresh(SubWin, cols,0,StartY,StartX,Height,Width);
        Key = wgetch(SubWin);
        switch(Key)
        {
        case KEY_UP:
        {
            if (cols <= 0) continue;
            cols--;
            break;
        }
        case KEY_DOWN:
        {
            if (cols+Height+1 >= PadHeight) continue;
            cols++;
            break;
        }
        case KEY_PPAGE: /* Page Up */
        {
            if (cols <= 0) continue;
            cols -= Height;
            if (cols < 0) cols = 0;
            break;
        }
        case KEY_NPAGE: /* Page Down */
            if (cols+Height+1 >= PadHeight) continue;
            cols += Height;
            if (cols+Height+1 > PadHeight) cols = PadHeight-Height-1;
            break;
        case KEY_HOME:
            cols = 0;
            break;
        case KEY_END:
            cols = PadHeight-Height-1;
            break;
        case 10: /* Enter */
        {
            Choice = 1;
            break;
        }
        }
        refresh();
    }
    delwin(SubWin);
}

void STARTSYSMAN::endeapp()
{
    VARSYSMAN::ConfigDateiList.clear();
    vector<string>().swap(VARSYSMAN::ConfigDateiList);
    STARTSYSMAN::DeletHMmenu("Ende");
    clear();
    pthread_kill(VARSYSMAN::Tzeit,SIGKILL);
    //STARTSYSMAN::ClearScreen();
}

static void finish(int sig)
{
    endwin();
    //Un post form and free the memory
    //    int fieldCount = STARTSYSMAN::START.TMPForm1->maxfield;
    //    unpost_form(STARTSYSMAN::START.TMPForm1);
    //    free_form(STARTSYSMAN::START.TMPForm1);
    //    int i;
    //    for(i=0; i<fieldCount; i++)
    //      {
    //        free_field(STARTSYSMAN::START.TMPField1[i]);
    //      }
    //    endwin();
    //STARTSYSMAN::ClearScreen();
    /* do your non-curses wrapup here */
    CLEARSCR;
    exit(0);
}

int main() //int argc, char *argv[])
{
    try {
        STARTSYSMAN::init_curse();
        STARTSYSMAN::AppColor();
        int num = 0;
        (void) signal(SIGINT, finish);
        int ch;
        //#################################################
        //void (*prev_handler)(int);
        const int result_1 = std::atexit(STARTSYSMAN::endeapp);
        std::set_terminate (STARTSYSMAN::endeapp);
        if (result_1 != 0){
            std::cerr << "Registration failed\n";
            return EXIT_FAILURE;
        }
        void (*prev_handler)(int);
        prev_handler = signal (SIGHUP, VARSYSMAN::termquit);
        //#################################################

        getmaxyx(stdscr, STARTSYSMAN::max_yr, STARTSYSMAN::max_xc);
        VARSYSMAN::Folder();
        STARTSYSMAN::configR();
        SYSNETZWERK::Start_Route();
        SYSNETZWERK::IFACENAME();
        werase(stdscr);
        STARTSYSMAN::FensterDesign();
        HMenu::Hauptmenu();

        if (pthread_create(&VARSYSMAN::Tzeit, nullptr, VARSYSMAN::uhrzeit_anzeigen, nullptr) !=0){
            perror("thread create faild");
            exit(EXIT_FAILURE);}
        pthread_detach(VARSYSMAN::Tzeit);

        //if (pthread_create(&VARSYSMANLIB::KeyCat, NULL,  VARSYSMANLIB::KEYCATCH_handler, NULL) != 0) {
        //perror("thread create faild");
        //exit(EXIT_FAILURE);}
        //pthread_detach(VARSYSMANLIB::KeyCat);

        refresh();
        wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin1));
        wrefresh(VARSYSMAN::clearwindow(HMenu::MENEU[0].HMWin));
        wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));

        while ((ch=getch()) != KEY_F(10)) {
            switch (ch) {
            case KEY_F(9):
                pos_menu_cursor(HMenu::MENEU[0].HMMenu);
                set_current_item(HMenu::MENEU[0].HMMenu, HMenu::MENEU[0].HMItem[HMenu::MeInAl]);
                menu_driver(HMenu::tmpMe("",HMenu::MeInAl), REQ_DOWN_ITEM);
                //HMenu::MeAuWa = item_name(current_item(HMenu::tmpMe(HMenu::MeNa)));
                //wrefresh(tmpWi1);
                wrefresh(VARSYSMAN::clearwindow(HMenu::MENEU[0].HMWin));
                HMenu::MenuStart();
                break;
                //          case KEY_F(8):
                //            Soft_Joe::KEY_DRIVER_new();
                //            break;
            default:

                break;
            }
        }
        finish(0);
    } catch (const NCursesException *e) {
        endwin();
        std::cerr << e->message << std::endl;
        cout << e->errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        cout << e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        cout << EXIT_FAILURE;
    }
}

struct test{
    static WINDOW *testwin;
    static MENU *testmenu;
    static ITEM **testitem;
    void WinExit(WINDOW *testwin = test::testwin, MENU *testmenu = test::testmenu, ITEM **testitem = test::testitem)
    {
        //if (strcmp(name,HMenu::MENEU[0].HMName.c_str())==0){
        if (testwin){
            int E = item_count(testmenu);
            unpost_menu(testmenu);
            SAFE_DELETE(testmenu);
            SAFE_DELETE_ARRAY(testitem);
            wborder(testwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(testwin, 0, E+1);
            delwin(testwin);
            endwin();
        }
        //}
    }
};

void STARTSYSMAN::DeletHMmenu(const char *name)
{
    try
    {
        if (strcmp(name,"Ende")==0){
            werase(STARTSYSMAN::START.TMPWin1);
            delwin(STARTSYSMAN::START.TMPWin1);
            werase(STARTSYSMAN::START.TMPWin2);
            delwin(STARTSYSMAN::START.TMPWin2);
            delwin(STARTSYSMAN::START.TMPWin3);
            //_nc_freeall();
            endwin();
            //pthread_key_delete(VARSYSMANLIB::Tzeit);
            //pthread_key_delete(VARSYSMANLIB::KeyCat);
            //exit(EXIT_SUCCESS);
            //exit(-1);
        }

        refresh();
        CLEARSCR;
        //redrawwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));
        //wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));
    } catch (const NCursesException *e) {
        endwin();
        std::cerr << e->message << std::endl;
        cout << e->errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        cout << e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        cout << EXIT_FAILURE;
    }
}

STARTSYSMAN::STARTSYSMAN(){}
