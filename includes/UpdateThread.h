/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UpdateThread.h
 * Author: nils
 *
 * Created on 30. August 2016, 11:19
 */

#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include <gtkmm.h>

#include "Communicator.h"

class UpdateThread {
public:
    UpdateThread(Communicator *comm, Gtk::Box *box, Gtk::Label *timer, Gtk::Label *group, Gtk::Label *end);
    void run();
    void quit();
    
    virtual ~UpdateThread();
private:
    void do_sth();
    
    bool m_run;
    Communicator *comm;
    Gtk::Box *box;
    Gtk::Label *timer, *group, *end;
    Glib::Thread *m_thread;
};

#endif /* UPDATETHREAD_H */

