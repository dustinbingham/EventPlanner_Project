#include "eventplanner.h"
#include "eventadminmode.h"
#include "addingmode.h"
#include "session.h"
#include "loginpage.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    /*!
     * \mainpage
     * \author Team Jayhawk
     * \details The %Event Planner is a project created for EECS 448 course at the Univerty of Kansas.
     * \details This project was created using <a href="https://www.qt.io/qt-features-libraries-apis-tools-and-ide/" target="_blank">Qt Creator IDE</a> version 5.9.1.
     * \details Qt framework is used under <a href="https://www.gnu.org/licenses/lgpl.txt" target="_blank">LGPL</a>.
     * \details Details about the Qt classes used can be found on the <a href="http://doc.qt.io/qt-5/classes.html" target="_blank">Qt Documentation Website</a>.
     */
    Session session;
    session.readEventsFromFile();
    QApplication prog(argc, argv);
    QDesktopWidget* qDesk = QApplication::desktop();
    LoginPage login(&session);
    EventPlanner w;
    EventAdminMode mode1(&session);
    AddingMode mode2(&session);
    login.setStyleSheet("QMainWindow {background: rgb(245,245,245);}");
    w.setStyleSheet("QMainWindow {background: rgb(253,253,253);}");
    mode1.setStyleSheet("QMainWindow {background: rgb(245,245,245);}");
    mode2.setStyleSheet("QMainWindow {background: rgb(245,245,245);}");

    login.move((qDesk->width() - w.width())/2,(qDesk->height() - w.height())/2); // set window in the middle
    w.move((qDesk->width() - w.width())/2,(qDesk->height() - w.height())/2); // set window in the middle
    mode1.move((qDesk->width() - mode1.width())/2,(qDesk->height() - mode1.height())/2);// same
    mode2.move((qDesk->width() - mode2.width())/2,(qDesk->height() - mode2.height())/2);// same
   login.show();

    QObject::connect(&login, SIGNAL(goToEventPlanner()), &w, SLOT(receiveShow()));
    QObject::connect(&mode1,SIGNAL(showEventPlanner()),&w,SLOT(getMode1()));
    QObject::connect(&w,SIGNAL(AdminModeshow()),&mode1,SLOT(receiveshow()));
    QObject::connect(&w, SIGNAL(Logout()), &login, SLOT(receiveShow()));

    QObject::connect(&mode2,SIGNAL(showEventPlanner()),&w,SLOT(getMode2()));//connect signal
    QObject::connect(&w,SIGNAL(AddingModeshow()),&mode2,SLOT(receiveshow()));//   with differen windows
    return (prog.exec());
}
