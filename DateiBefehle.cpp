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

VARSYSMAN::FENSTERBEFEHLE VARSYSMAN::BEFEHLE;

void DATEIBEFEHLE::FensterDesign(void)
{
    VARSYSMAN::BEFEHLE.FEID = 3;
    VARSYSMAN::BEFEHLE.FENAME = string("Befehle");
    if (STARTSYSMAN::START.TMPWin3){werase(STARTSYSMAN::START.TMPWin3);delwin(STARTSYSMAN::START.TMPWin3);}
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-1,STARTSYSMAN::max_xc,1,0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    mvwhline(STARTSYSMAN::START.TMPWin3, 6, 1, ACS_HLINE, STARTSYSMAN::max_xc-2);
    mvwvline(STARTSYSMAN::START.TMPWin3, 6, 0, ACS_LTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 6, STARTSYSMAN::max_xc-1, ACS_RTEE,1);
    mvwhline(STARTSYSMAN::START.TMPWin3, 9, 1, ACS_HLINE, STARTSYSMAN::max_xc-2);
    mvwvline(STARTSYSMAN::START.TMPWin3, 9, 0, ACS_LTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 9, STARTSYSMAN::max_xc-1, ACS_RTEE,1);
    wrefresh(STARTSYSMAN::START.TMPWin3);

    VARSYSMAN::BEFEHLE.TMPWin1 = newwin(5, STARTSYSMAN::max_xc - 2, 2, 1); //-23
    //STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::BEFEHLE.TMPWin1, 5, STARTSYSMAN::max_xc - 2, 1, 1);
    VARSYSMAN::BEFEHLE.TMPWin1 = derwin(STARTSYSMAN::START.TMPWin3, 5, STARTSYSMAN::max_xc - 2, 1, 1);
    wbkgd(VARSYSMAN::BEFEHLE.TMPWin1,COLOR_PAIR(61));

    VARSYSMAN::BEFEHLE.TMPWin2 = newwin(2, STARTSYSMAN::max_xc - 2, 9, 1); //-23
    VARSYSMAN::BEFEHLE.TMPWin2 = derwin(STARTSYSMAN::START.TMPWin3, 2, STARTSYSMAN::max_xc - 2, 7, 1);
    wbkgd(VARSYSMAN::BEFEHLE.TMPWin2,COLOR_PAIR(61));

    VARSYSMAN::BEFEHLE.TMPWin3 = newpad(STARTSYSMAN::max_yr-12, STARTSYSMAN::max_xc-2);
    wbkgd(VARSYSMAN::BEFEHLE.TMPWin3,COLOR_PAIR(11));
    wsetscrreg(VARSYSMAN::BEFEHLE.TMPWin3, 1, STARTSYSMAN::max_yr-13);
    scrollok(VARSYSMAN::BEFEHLE.TMPWin3, true);
    scroll(VARSYSMAN::BEFEHLE.TMPWin3);
    idlok(VARSYSMAN::BEFEHLE.TMPWin3, true);
    clearok(VARSYSMAN::BEFEHLE.TMPWin2,true);
    clearok(VARSYSMAN::BEFEHLE.TMPWin3,true);
}

void DATEIBEFEHLE::befehlsmenu(void)
{
    scrollok(VARSYSMAN::BEFEHLE.TMPWin1, true);
    unsigned long X=0,Y=0;
    int mrows, mcols;
    VARSYSMAN::BEFEHLE.TMPItem1 = static_cast<ITEM **>(calloc(70, sizeof(ITEM *)));
    for(X=23; X<=89; X++){
        VARSYSMAN::BEFEHLE.TMPItem1[Y] = new_item(VARSYSMAN::ConfigDateiList[X].c_str(),"");
        Y++;
    }
    VARSYSMAN::BEFEHLE.TMPItem1[Y+1] = nullptr;
    VARSYSMAN::BEFEHLE.TMPMenu1 = new_menu(VARSYSMAN::BEFEHLE.TMPItem1);
    set_menu_win(VARSYSMAN::BEFEHLE.TMPMenu1, VARSYSMAN::BEFEHLE.TMPWin1);
    set_menu_sub (VARSYSMAN::BEFEHLE.TMPMenu1, derwin(VARSYSMAN::BEFEHLE.TMPWin1, STARTSYSMAN::max_yr-19, 34, 2, 1));
    set_menu_format(VARSYSMAN::BEFEHLE.TMPMenu1, STARTSYSMAN::max_yr-19, 1);
    scale_menu(VARSYSMAN::BEFEHLE.TMPMenu1, &mrows, &mcols);
    set_menu_mark(VARSYSMAN::BEFEHLE.TMPMenu1, "-");
    menu_opts_off(VARSYSMAN::BEFEHLE.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::BEFEHLE.TMPMenu1, COLOR_PAIR(61)|A_REVERSE|A_BOLD);
    set_menu_back(VARSYSMAN::BEFEHLE.TMPMenu1, COLOR_PAIR(61)|A_BOLD);
    post_menu(VARSYSMAN::BEFEHLE.TMPMenu1);
}

void DATEIBEFEHLE::Form_Interakt(void)
{
    VARSYSMAN::BEFEHLE.TMPField = static_cast<FIELD **>(calloc(2, sizeof(FIELD *)));
    VARSYSMAN::BEFEHLE.TMPField[0] = new_field(1, STARTSYSMAN::max_xc - 2, 1, 0, 0, 0);
    VARSYSMAN::BEFEHLE.TMPField[1] = nullptr;
    VARSYSMAN::BEFEHLE.TMPForm = new_form(VARSYSMAN::BEFEHLE.TMPField);
    scale_form(VARSYSMAN::BEFEHLE.TMPForm, &STARTSYSMAN::fmyr, &STARTSYSMAN::fmxc);
    set_field_fore( VARSYSMAN::BEFEHLE.TMPField[0], COLOR_PAIR(32)); //|A_REVERSE);
    set_field_back( VARSYSMAN::BEFEHLE.TMPField[0], COLOR_PAIR(32));
    //field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_VISIBLE | O_ACTIVE | O_PUBLIC | O_EDIT | O_WRAP | O_STATIC);
    field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_VISIBLE);
    field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_ACTIVE);
    field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_PUBLIC);
    field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_EDIT);
//    field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_WRAP);
//    field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_STATIC);
//    field_opts_off( VARSYSMAN::BEFEHLE.TMPField[0], O_BLANK);
//    field_opts_off( VARSYSMAN::BEFEHLE.TMPField[0], O_AUTOSKIP);
//    field_opts_off( VARSYSMAN::BEFEHLE.TMPField[0], O_NULLOK);
//    field_opts_off( VARSYSMAN::BEFEHLE.TMPField[0], O_PASSOK);
//    set_form_opts(VARSYSMAN::BEFEHLE.TMPForm, O_BS_OVERLOAD);
//    set_field_type(VARSYSMAN::BEFEHLE.TMPField[0],TYPE_REGEXP,"[: and :]");
    set_field_buffer(VARSYSMAN::BEFEHLE.TMPField[0], 0, "");
    set_form_win(VARSYSMAN::BEFEHLE.TMPForm, VARSYSMAN::BEFEHLE.TMPWin2);
    set_form_sub(VARSYSMAN::BEFEHLE.TMPForm, VARSYSMAN::BEFEHLE.TMPWin2);
    data_ahead(VARSYSMAN::BEFEHLE.TMPForm);
    data_behind(VARSYSMAN::BEFEHLE.TMPForm);
    post_form(VARSYSMAN::BEFEHLE.TMPForm);
    mvwaddstr( VARSYSMAN::BEFEHLE.TMPWin2, 0, 0, "Eigene Befehlseingabe");
}

void delform(WINDOW *tmpwin, FORM *tmpform, FIELD **tmpfield){
    int mx,my,bx,by;
    getbegyx(tmpwin,by,bx);
    getmaxyx(tmpwin,my,mx);
    unpost_form(tmpform);
    SAFE_DELETE(tmpform);
    SAFE_DELETE_ARRAY(tmpfield);
    free_form(tmpform);
    for(int Q=0;Q<=field_count(tmpform);Q++){
        free_field(tmpfield[Q]);
    }
    wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    touchline(tmpwin,bx,mx);
    delwin(tmpwin);
    endwin();
    refresh();
}

void DATEIBEFEHLE::befehle_main()
{
    DATEIBEFEHLE::FensterDesign();
    DATEIBEFEHLE::befehlsmenu();
    DATEIBEFEHLE::Form_Interakt();

    refresh();
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::BEFEHLE.TMPWin1));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::BEFEHLE.TMPWin2));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::BEFEHLE.TMPWin3),
             0, 0, 11, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);

    keypad(STARTSYSMAN::START.TMPWin3, true);

    int MinPadRow = STARTSYSMAN::max_yr-11;
    int ROWS = 0;
    int c;
    int tabspace = 1;

    while ((c = getch()) != KEY_F(10))
    {
        switch(tabspace){
        case 1: //########################-Menu-#############################################
            switch(c){
            case KEY_UP:
                menu_driver(VARSYSMAN::BEFEHLE.TMPMenu1, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::BEFEHLE.TMPMenu1, REQ_DOWN_ITEM);
                break;
            case KEY_NPAGE:
                menu_driver(VARSYSMAN::BEFEHLE.TMPMenu1, REQ_LAST_ITEM);
                break;
            case KEY_PPAGE:
                menu_driver(VARSYSMAN::BEFEHLE.TMPMenu1, REQ_FIRST_ITEM);
                break;
            case 0x09:
                tabspace = VARSYSMAN::zahlenwerk(1,"++",3);
                break;
            case KEY_BTAB:
                tabspace = VARSYSMAN::zahlenwerk(1,"--",3);
                break;
            case 10:
                string ls = VARSYSMAN::TERM_AUSGABE(string(item_name(current_item(VARSYSMAN::BEFEHLE.TMPMenu1))));
                VARSYSMAN::BEFEHLE.TMPWinHigh = SOFTAKINSTALL::Zeilen(ls, STARTSYSMAN::max_xc-2);
                VARSYSMAN::BEFEHLE.TMPWin3 = newpad(VARSYSMAN::BEFEHLE.TMPWinHigh, STARTSYSMAN::max_xc-2);
                STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::BEFEHLE.TMPWin3, MinPadRow, STARTSYSMAN::max_xc-2, 11, 1);
                mvwaddstr(VARSYSMAN::BEFEHLE.TMPWin3, 0, 0, ls.c_str());
                break;
            }
            set_field_buffer(VARSYSMAN::BEFEHLE.TMPField[0], 0, item_name(current_item(VARSYSMAN::BEFEHLE.TMPMenu1)));
            break;
        case 2: //##############################-FORM-#########################################
            field_opts_on( VARSYSMAN::BEFEHLE.TMPField[0], O_ACTIVE);
            switch(c){
            case KEY_LEFT:
                form_driver(VARSYSMAN::BEFEHLE.TMPForm, REQ_LEFT_CHAR);
                break;
            case KEY_RIGHT:
                form_driver(VARSYSMAN::BEFEHLE.TMPForm, REQ_RIGHT_CHAR);
                break;
            case KEY_BACKSPACE:
            case 127:
                form_driver(VARSYSMAN::BEFEHLE.TMPForm, REQ_DEL_PREV);
                break;
            case KEY_DC:
                form_driver(VARSYSMAN::BEFEHLE.TMPForm, REQ_DEL_CHAR);
                break;
            case 0x09:
                tabspace = VARSYSMAN::zahlenwerk(2,"++",3);
                break;
            case KEY_BTAB:
                tabspace = VARSYSMAN::zahlenwerk(2,"--",3);
                break;
            default:
                form_driver(VARSYSMAN::BEFEHLE.TMPForm, c);
                break;
            case 10:
                form_driver(VARSYSMAN::BEFEHLE.TMPForm, REQ_VALIDATION);
                string ls = VARSYSMAN::TERM_AUSGABE(string(field_buffer(VARSYSMAN::BEFEHLE.TMPField[0],0)));
                VARSYSMAN::BEFEHLE.TMPWinHigh = SOFTAKINSTALL::Zeilen(ls, STARTSYSMAN::max_xc-2);
                VARSYSMAN::BEFEHLE.TMPWin3 = newpad(VARSYSMAN::BEFEHLE.TMPWinHigh, STARTSYSMAN::max_xc-2);
                STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::BEFEHLE.TMPWin3, MinPadRow, STARTSYSMAN::max_xc-2, 10, 1);
                mvwaddstr(VARSYSMAN::BEFEHLE.TMPWin3, 0, 0, ls.c_str());
                wscrl(VARSYSMAN::BEFEHLE.TMPWin3,-ROWS);
                ROWS = 0;
                break;
            }
            break;
        case 3: //##########################-WINDOW-#############################################
            switch(c){
            case KEY_UP:
                if (ROWS <= 0){
                    continue;
                }else {
                    ROWS--;
                }
                break;
            case KEY_DOWN:
                if ((ROWS + MinPadRow +10) >= VARSYSMAN::BEFEHLE.TMPWinHigh){
                    continue;
                }else {
                    ROWS++;
                }
                break;
            case 0x09:
                tabspace = VARSYSMAN::zahlenwerk(3,"++",3);
                break;
            case KEY_BTAB:
                tabspace = VARSYSMAN::zahlenwerk(3,"--",3);
                break;
            }
            break;
        }
        refresh();
        touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
        wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::BEFEHLE.TMPWin1));
        //wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::BEFEHLE.TMPWin2));
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::BEFEHLE.TMPWin3),
                 ROWS, 0, 11, 1, STARTSYSMAN::max_yr -2, STARTSYSMAN::max_xc -1);  //pmiry, pmixc, smiry, smixc, smary, smaxc
    }
    DATEIBEFEHLE::QuitBefehl();
}

void DATEIBEFEHLE::QuitBefehl()
{
    int e,i;
    e = item_count(VARSYSMAN::BEFEHLE.TMPMenu1);
    unpost_menu(VARSYSMAN::BEFEHLE.TMPMenu1);
    for(i=0; i<=e-1; i++) {
        free_item(VARSYSMAN::BEFEHLE.TMPItem1[i]);
    }
    free_menu(VARSYSMAN::BEFEHLE.TMPMenu1);

    e = field_count(VARSYSMAN::BEFEHLE.TMPForm);
    unpost_form(VARSYSMAN::BEFEHLE.TMPForm);
    for(i=0; i<=e-1; i++) {
        free_field(VARSYSMAN::BEFEHLE.TMPField[i]);
    }
    free_form(VARSYSMAN::BEFEHLE.TMPForm);

    delwin(VARSYSMAN::BEFEHLE.TMPWin1);
    delwin(VARSYSMAN::BEFEHLE.TMPWin2);
    delwin(VARSYSMAN::BEFEHLE.TMPWin3);
    endwin();

    refresh();
}
