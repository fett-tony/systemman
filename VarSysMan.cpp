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

NETZ_IF VARSYSMAN::NETZWERK_IF[];
GW_ROUTE VARSYSMAN::GATEWAY_IF[];
//####################################################
//-------------Uhrzeit_Handler------------------------
time_t VARSYSMAN::Zeitstempel;
tm *VARSYSMAN::UHRZEIT;
char VARSYSMAN::UHRZEITchar[19];
string VARSYSMAN::UHRZEITstr;
struct sigaction VARSYSMAN::sa;
struct itimerval VARSYSMAN::timer;
pthread_t VARSYSMAN::Tzeit, VARSYSMAN::KeyCat;
//----------------------------------------------------
string VARSYSMAN::filename;
std::vector<std::string> VARSYSMAN::ConfigDateiList;
int VARSYSMAN::CountConfigDatei = 0;
sig_atomic_t VARSYSMAN::signaled = 0;
//####################################################
//-------Color-Hauptmenue-----------------------------
int VARSYSMAN::HaMeFe_HG = 06,//Fenster_Background----
VARSYSMAN::HaMe_FG = 01,//Hauptmenue_Foreground-------
VARSYSMAN::HaMe_HG = 06,//Hauptmenue_Background-------
VARSYSMAN::HaMe_grey = 04,//Hauptmenue_inaktive-------
VARSYSMAN::UMeFe_HG = 01;//Fenster_Untermenue---------
//####################################################
//-------Color-InApp-Menues---------------------------
int VARSYSMAN::IlMeFe_HG = 61,//Fenster_Background----
VARSYSMAN::IlMe_FG = 42,//InnLineMenue_Foreground-----
VARSYSMAN::IlMe_HG = 63,//InnLineMenue_Background-----
VARSYSMAN::IlMe_grey = 63,//InnLineMenue_inaktive-----
VARSYSMAN::IlUMeFe_HG = 35;//Fenster_Untermenue-------
//----------------------------------------------------
//####################################################
//eigenes zählwerk um von forn an fangen zu können
//aktuelle zahl, string ob + oder -, maximale höchste zahl
int VARSYSMAN::zahlenwerk(int zahlen, string i, int max)
{
    int tmp = 0;
    if (strcmp(i.c_str(),"++")==0){
        if(zahlen>=max){
            tmp = 1;
        }else if(zahlen==0){
            tmp = 1;
        }else if (zahlen>0){
            tmp = ++zahlen;
        }else if (zahlen<max){
            tmp = ++zahlen;
        }
    }else if(strcmp(i.c_str(),"--")==0){
        if(zahlen<=0){
            tmp = max;
        }else if (zahlen==1){
            tmp = max;
        }else if (zahlen>1){
            tmp = --zahlen;
        }else if(zahlen<=max){
            tmp = --zahlen;
        }
    }else{
        tmp = 1;
    }
    return tmp;
}

int VARSYSMAN::ZahlenBerechnen(int posa, RANGE range, string wahl)
{
    int tmp;
    if (wahl.compare("+") == 0){
        posa++;
    }else if (wahl.compare("-") == 0){
        posa--;
    }

    if (posa >= range.min && posa <= range.max){
        tmp = ((posa - range.min) + range.min);
    }else if (posa >= range.min && posa > range.max){
        tmp = (posa - range.max);// + range.min;
        while(tmp > range.max){
            tmp = (tmp - range.max);// + range.min;
        }
    }else if (posa < range.min && posa <= range.max){
        tmp = range.max + posa;
        while(tmp < range.min){
            if(tmp == 0){tmp = range.max;}
            else{tmp = range.max + tmp;}
        }
    }else if (posa == 0){
        tmp = range.max;
    }else{tmp = posa;}

    return tmp;
}

int VARSYSMAN::ZahlenWerk(int mina, int posa, int maxa, string wahl){
    vector<RANGE> list;
    int included;
    RANGE range;

    range.min = mina;
    range.max = maxa;
    range.count();
    range.range = 1;
    list.push_back(range);

    do {
        included = VARSYSMAN::ZahlenBerechnen(posa, range, wahl);
    }while (included > range.max);
    return included;
}

WINDOW *VARSYSMAN::clearwindow(WINDOW *tmpW)
{
    clearok(tmpW,true);
    return tmpW;
}

WINDOW *VARSYSMAN::DelTmpWin(WINDOW *tmpW)
{
    chtype test = getbkgd(tmpW);
    if (test == static_cast<unsigned long>(61)){
    int max_tw_yr,max_tw_xc;
    getmaxyx(tmpW, max_tw_yr, max_tw_xc);
    wbkgd(tmpW,COLOR_PAIR(0));
    for (int I1 =0;I1<=max_tw_yr;I1++){ mvwhline(tmpW, I1, 0, ' ', max_tw_yr);}
    for (int I2 =0;I2<=max_tw_xc;I2++){ mvwvline(tmpW, 0, I2, ' ', max_tw_xc);}
    wborder(tmpW, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wclear(tmpW);
    werase(tmpW);
    //delwin(tmpW);
    //endwin();
    }
    return tmpW;
}

void VARSYSMAN::termquit(int)
{
    VARSYSMAN::signaled = 1;
    VARSYSMAN::ConfigDateiList.clear();
    vector<string>().swap(VARSYSMAN::ConfigDateiList);
    STARTSYSMAN::DeletHMmenu("Ende");
    clear();
    pthread_kill(VARSYSMAN::Tzeit,SIGKILL);
    exit(EXIT_SUCCESS);
    //STARTSYSMAN::ClearScreen();
}

int VARSYSMAN::Datei_Letzte_Line(string DateiName)
{
    int NrLine = 0;
    ifstream in(DateiName.c_str());
    while ( in.good() )
    {
       std::string line;
       std::getline(in, line);
       ++NrLine;
    }
    return NrLine;
}

string VARSYSMAN::Datei_Zeile_Nr(string Datei, int zeile)
{
    std::ifstream infile(Datei.c_str(), std::ios::in);
    std::string file(Datei);
    int lines_read = 0;
    std::string line;
    if (infile.is_open()) {
        while (infile) {
            getline(infile, line);
            lines_read++ ;
            if (lines_read == zeile) {
                break;
            }
        }
        infile.close();
        if (lines_read < zeile){
            std::cout << "No " << zeile << " lines in " << file << " !\n" ;
        }
    }else{
        std::cerr << "Could not find file " << file << " !\n" ;
    }
    return line;
}

void VARSYSMAN::Folder(void){
    //"/home/aktony/Dokumente/Qt_workplace/SysMan/config.txt";
    string AppDir = string(get_current_dir_name());
    string ConfFile = "config.txt";
    AppDir.append("/");
    AppDir.append(ConfFile);
    VARSYSMAN::filename = AppDir;
}

void VARSYSMAN::timer_handler(int)
{
  /* Ganz einfacher Signalhandler */
  static int count = 0;
  VARSYSMAN::Zeitstempel = time(nullptr);
  VARSYSMAN::UHRZEIT = localtime(&VARSYSMAN::Zeitstempel);
  strftime(VARSYSMAN::UHRZEITchar, size_t(VARSYSMAN::UHRZEITchar), "%d.%m.%Y %T", VARSYSMAN::UHRZEIT);
  VARSYSMAN::UHRZEITstr = string(VARSYSMAN::UHRZEITchar);
  wattr_on(HMenu::MENEU[0].HMWin, COLOR_PAIR(05)|A_STANDOUT,nullptr);//|A_BOLD,0);
  mvwaddnstr(HMenu::MENEU[0].HMWin, 0, STARTSYSMAN::max_xc-20, UHRZEITstr.c_str(), -1);
  ++count;
  wattr_off(HMenu::MENEU[0].HMWin, COLOR_PAIR(05)|A_STANDOUT,nullptr);//|A_BOLD,0);
  refresh();
  wrefresh(STARTSYSMAN::START.TMPWin1);
  wrefresh(HMenu::MENEU[0].HMWin);
} /*---------timer_für_Uhrzeit----------------------*/

void *VARSYSMAN::uhrzeit_anzeigen(void*)
{
    try {
        /* Installiere timer_handler als
         * Signal Handler fuer SIGVTALRM. */
        memset(&VARSYSMAN::sa, 0, sizeof (VARSYSMAN::sa));
        sigemptyset(&VARSYSMAN::sa.sa_mask);
        VARSYSMAN::sa.sa_handler = &VARSYSMAN::timer_handler;
        sigaction(SIGVTALRM, &VARSYSMAN::sa, nullptr);
        /* Timer konfigurieren fuer 500 ms */
        VARSYSMAN::timer.it_value.tv_sec = 0;
        VARSYSMAN::timer.it_value.tv_usec = 500000;
        /* und alle 500 ms danach */
        VARSYSMAN::timer.it_interval.tv_sec = 0;
        VARSYSMAN::timer.it_interval.tv_usec = 500000;
        /* Timer starten */
        setitimer(ITIMER_VIRTUAL, &VARSYSMAN::timer, nullptr);
        while(VARSYSMAN::signaled==0){
        }
    } catch (const std::exception &e) {
      endwin();
      std::cerr << "Exception: " << e.what() << std::endl;
      //res = EXIT_FAILURE;
    }
} /*---Time THREAD---*/

bool VARSYSMAN::DirectoryExists(const char* pzPath){
    DIR *pDir;
    bool bExists = false;
    pDir = opendir (pzPath);
    if (pDir != nullptr){
        bExists = true;
        closedir (pDir);
    }
    return bExists;
}

void VARSYSMAN::KEYCATCH_handler(void *)
{
    int c;
    while((c=getch()) !=KEY_F(10))
    {
        switch (c)
        {
        case 0x1b: /*ESC*/
            //waddstr(STARTSYSMAN::START.TMPWin2,"ESC \n");
            STARTSYSMAN::DeletHMmenu("Ende");
            exit(EXIT_SUCCESS);
            //break;
        case 0x161: /*TAB + shift*/
            //waddstr(STARTSYSMAN::START.TMPWin2,"TAB + shift \n");
            break;
        case 0x9: /*TAB*/
            //waddstr(STARTSYSMAN::START.TMPWin2,"TAB \n");
            break;
        case 0xA: /*ENTER*/
            //waddstr(STARTSYSMAN::START.TMPWin2,"ENTER \n");
            break;
        case KEY_F(9):
            pos_menu_cursor(HMenu::MENEU[0].HMMenu);
            set_current_item(HMenu::MENEU[0].HMMenu, HMenu::MENEU[0].HMItem[HMenu::MeInAl]);
            menu_driver(HMenu::tmpMe("",HMenu::MeInAl), REQ_DOWN_ITEM);
            wrefresh(HMenu::MENEU[0].HMWin);
            HMenu::MenuStart();
            break;
        }
        sleep(1);
    }
}
// 0x1b,0027, "ESC" // 0xa,0015, "ENTER" //
// 0x9,0011, "TAB" // 0x161,0541, "RTAB" //

string VARSYSMAN::IP_Uint_to_IP_String(unsigned long IP)
{
  ostringstream IPstream;
  IPstream << ((IP &0x000000ff))
           << "." << ((IP &0x0000ff00) >> 8)
           << "." << ((IP &0x00ff0000) >> 16)
           << "." << ((IP &0xff000000) >> 24);
  return IPstream.str();
}

void VARSYSMAN::find_and_replace(string& source, string const& find, string const& replace)
{
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

string VARSYSMAN::TERM_AUSGABE(string cmd)
{
    string data;
    FILE * stream;
    char buffer[BUFSIZE];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
        {
            if (fgets(buffer, BUFSIZE, stream) != nullptr)
            {
                data.append(buffer);
            }
        }
        pclose(stream);
    }
    return data;
}

string VARSYSMAN::exec(string cmd) {
    char buffer[BUFSIZE];
    string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, BUFSIZE, pipe) != nullptr)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

string VARSYSMAN::ssystem(string cmd2) {
    char tmpname [L_tmpnam];
    //std::tmpnam ( tmpname );
    mkstemp ( tmpname );
    std::string scommand = cmd2;
    std::string cmd = scommand + " >> " + tmpname;
    std::system(cmd.c_str());
    //shell_exec(cmd.c_str());
    std::ifstream file(tmpname, std::ifstream::in );
    std::string result;
        if (file) {
      while (!file.eof()) result.push_back(static_cast<char>(file.get()));
          file.close();
    }
    remove(tmpname);
    return result;
}

void VARSYSMAN::test(void)
{
    for(unsigned long X = 18; X <= 43; X++){
        wprintw(VARSYSMAN::BEFEHLE.TMPWin1,"%s \n" ,VARSYSMAN::ConfigDateiList[X].c_str());
    }
}

//VARSYSMAN::VARSYSMAN(){}
VARSYSMAN::~VARSYSMAN(){}
