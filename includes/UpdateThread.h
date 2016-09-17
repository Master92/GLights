//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program; if not, write to the Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA,
//  or see see <http://gnu.org/licenses/gpl-2.0.txt>

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

