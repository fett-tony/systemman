TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += create_prl

unix:!macx: LIBS += -lncurses++w
unix:!macx: LIBS += -lncursesw
unix:!macx: LIBS += -lmenuw
unix:!macx: LIBS += -lmenu
unix:!macx: LIBS += -lformw
unix:!macx: LIBS += -lpanelw
unix:!macx: LIBS += -pthread

RESOURCES += \
    Config/config.txt \
    Config/SystemMan.db-journal \
    Config/SystemMan.db \
    Config/config.yaml \
    Config/config.xml \
    Config/Systemman.icon.png 

SUBDIRS += \
    SystemMan.pro

ICON = Systemman.icon.png

HEADERS += \
    DateiBefehle.h \
    DateiManPage.h \
    HMenu.h \
    SoftAKInst.h \
    StartSysMan.h \
    SysDateiRechte.h \
    SysNetzIface.h \
    SysNetzMenu.h \
    SysNetzwerk.h \
    SysNetzWPACon.h \
    SysNetzWPAScan.h \
    test.h \
    VarSysMan.h \

SOURCES += \
    DateiBefehle.cpp \
    DateiManPage.cpp \
    HMenu.cpp \
    SoftAKInst.cpp \
    StartSysMan.cpp \
    SysDateiRechte.cpp \
    SysNetzIface.cpp \
    SysNetzMenu.cpp \
    SysNetzwerk.cpp \
    SysNetzWPACon.cpp \
    SysNetzWPAScan.cpp \
    test.cpp \
    VarSysMan.cpp

DISTFILES += \
    Config/SystemMan.db-journal \
    Config/SystemMan.db \
    Config/config.yaml \
    Config/config.xml \
    Config/Systemman.icon.png \ 
    Config/config.txt

# Copy files to build directory
copydata0.commands = $(COPY_DIR) $$PWD/Config/config.txt $$OUT_PWD
copydata1.commands = $(COPY_DIR) $$PWD/Config/SystemMan.db $$OUT_PWD
first.depends = $(first) copydata0 copydata1
export(first.depends)
export(copydata0.commands)
export(copydata1.commands)
QMAKE_EXTRA_TARGETS += first copydata0 copydata1

#QFile DbFile;
#QString DatabaseDataStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
#DbFile.setFileName("assets:/MyDatabase.sqlite");
#DbFile.copy(DatabaseDataStoragePath + "/MyDatabase.sqlite")
#QFile::setPermissions(DatabaseDataStoragePath + "/MyDatabase.sqlite", QFile::WriteOwner | QFile::ReadOwner);


