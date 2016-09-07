//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
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

#include <cstdlib>
#include <gtkmm.h>
#include <iostream>
#include <time.h>
#include "GlightsConnectDialog.h"
#include "GlightsNewRoundDialog.h"
#include "Communicator.h"
#include "aipprotocol.h"
#include "GlightsAboutDialog.h"
#include "GlightsTimerDialog.h"
#include "UpdateThread.h"

using namespace std;
using namespace Gtk;

Glib::RefPtr<Builder> builder;
Window *window;
Label *timer_label, *group_label, *ends_label;
Box *bg_box;
MenuItem *m_item, *connect_menu_item, *disconnect_menu_item;
Button *connect_button, *disconnect_button, *add_end_button, *del_end_button, *next_button, *clock_button, *timer_button, *new_button, *runtext_button;
Entry *runtext_entry;
UpdateThread *thread_obj;

Communicator* comm[4];
int communicators = 0;

void send_time_updates() {
    time_t rawtime;
    time(&rawtime);
    struct tm * tme;
    tme = localtime(&rawtime);

    char date[15];
    strftime(date, 15, "%Y%m%d%H%M%S", tme);
    date[14] = (char)127;

    for(int i = 0; i < communicators; i++) {
        comm[i]->SendMessage(aip::SYNC, date);
    }
}

void on_connect() {
    GlightsConnectDialog dia(*window);
    if(dia.run() == RESPONSE_OK) {
        communicators = dia.get_ammount();
        char addr[12] = "192.168.0.1";
        
        for(int i = 0; i < communicators; i++) {
            addr[11] = '0' + i;
            comm[i] = new Communicator(addr);
        }
        
        send_time_updates();
        thread_obj = new UpdateThread(comm[0], bg_box, timer_label, group_label, ends_label);
        thread_obj->run();
        
        connect_button->set_sensitive(false);
        disconnect_button->set_sensitive();
        connect_menu_item->set_sensitive(false);
        disconnect_menu_item->set_sensitive();
        clock_button->set_sensitive();
        next_button->set_sensitive();
        timer_button->set_sensitive();
        new_button->set_sensitive();
        runtext_entry->set_sensitive();
        runtext_button->set_sensitive();
    }
}

void on_disconnect() {
    MessageDialog dia("Wirklich trennen?", false, MESSAGE_QUESTION, BUTTONS_YES_NO, true);
    dia.set_secondary_text("Dies führt zur Unkontrollierbarkeit aller bisher angeschlossenen Displays!");
    dia.set_transient_for(*window);
    
    if(dia.run() == RESPONSE_YES) {
        delete thread_obj;
        for(int i = 0; i < communicators; i++) {
            delete comm[i];
        }

        connect_button->set_sensitive();
        disconnect_button->set_sensitive(false);
        connect_menu_item->set_sensitive();
        disconnect_menu_item->set_sensitive(false);
        add_end_button->set_sensitive(false);
        del_end_button->set_sensitive(false);
        next_button->set_sensitive(false);
        clock_button->set_sensitive(false);
        timer_button->set_sensitive(false);
        new_button->set_sensitive(false);
        runtext_entry->set_sensitive(false);
        runtext_button->set_sensitive(false);
    }
}

void on_quit() {
    window->hide();
}

void on_about() {
    GlightsAboutDialog dia(*window);
    dia.run();
}

void on_del_end() {
    for(int i = 0; i < communicators; i++) {
        comm[i]->SendMessage(aip::DEL_END);
    }
}

void on_add_end() {
    for(int i = 0; i < communicators; i++) {
        comm[i]->SendMessage(aip::ADD_END);
    }
}

void on_next() {
    MessageDialog dia("Wirklich weitergehen?", false, MESSAGE_QUESTION, BUTTONS_YES_NO, true);
    dia.set_secondary_text("Damit wird unwiederbringlich zum nächsten Schritt gesprungen!");
    dia.set_transient_for(*window);
    
    if(dia.run() == RESPONSE_YES) {
        for(int i = 0; i < communicators; i++) {
            comm[i]->SendMessage(aip::NEXT);
        }
    }
}

void on_clock() {
    for(int i = 0; i < communicators; i++) {
        comm[i]->SendMessage(aip::TIME);
    }
}

void on_timer() {
    GlightsTimerDialog dia(*window);
    
    if(dia.run() == RESPONSE_OK) {
        Glib::ustring opts;
        opts.push_back((char)dia.get_hours());
        opts.push_back((char)dia.get_minutes());
        opts.push_back((char)dia.get_seconds());
        opts.push_back((char)127);
        
        for(int i = 0; i < communicators; i++) {
            comm[i]->SendMessage(aip::TIMER, opts);
        }
    }
}

void on_new() {
    GlightsNewRoundDialog dia(*window);
    
    if(dia.run() == RESPONSE_OK) {
        Glib::ustring opts;
        int du1, du2, tmp;
        tmp = dia.get_duration();
        du1 = tmp / 10;
        du2 = tmp - du1*10;
        char group = (dia.get_group()) ? '1' : '0';
        
        opts.push_back((char)dia.get_ammount());
        opts.push_back((char)dia.get_preparation());
        opts.push_back((char)du1);
        opts.push_back((char)du2);
        opts.push_back(group);
        opts.push_back((char)127);
        
        for(int i = 0; i < communicators; i++) {
            comm[i]->SendMessage(aip::NEW_ROUND, opts);
        }
        
        next_button->set_sensitive();
        add_end_button->set_sensitive();
        del_end_button->set_sensitive();
    }
}

void on_runtext_send() {
    Glib::ustring message = runtext_entry->get_text();
    message.push_back((char)127);
    
    if(message.size() > 0) {
        for(int i = 0; i < communicators; i++) {
            comm[i]->SendMessage(aip::RUNTEXT, message);
        }
    }
}


int main(int argc, char** argv) {
    Glib::RefPtr<Application> app = Application::create(argc, argv, "de.friedapps.glights");
    
    builder = Builder::create();
    MenuItem *menuItem;
    
    builder->add_from_file("./GLights.glade", "GlightsWindow");
    
    builder->get_widget("GlightsWindow", window);
    builder->get_widget("connect_menu_item", connect_menu_item);
    builder->get_widget("disconnect_menu_item", disconnect_menu_item);
    builder->get_widget("connect_button1", connect_button);
    builder->get_widget("disconnect_button", disconnect_button);
    builder->get_widget("add_end_button", add_end_button);
    builder->get_widget("del_end_button", del_end_button);
    builder->get_widget("next_button", next_button);
    builder->get_widget("clock_button", clock_button);
    builder->get_widget("timer_button", timer_button);
    builder->get_widget("new_button", new_button);
    builder->get_widget("runtext_entry", runtext_entry);
    builder->get_widget("runtext_button", runtext_button);
    builder->get_widget("label_box", bg_box);
    builder->get_widget("timer_label", timer_label);
    builder->get_widget("group_label", group_label);
    builder->get_widget("end_label", ends_label);
    
    connect_button->signal_clicked().connect(sigc::ptr_fun(on_connect));
    disconnect_button->signal_clicked().connect(sigc::ptr_fun(on_disconnect));
    connect_menu_item->signal_activate().connect(sigc::ptr_fun(on_connect));
    disconnect_menu_item->signal_activate().connect(sigc::ptr_fun(on_disconnect));
    
    builder->get_widget("quit_menu_item", menuItem);
    menuItem->signal_activate().connect(sigc::ptr_fun(on_quit));
    
    
    builder->get_widget("about_menu_item", menuItem);
    menuItem->signal_activate().connect(sigc::ptr_fun(on_about));
    
    del_end_button->signal_clicked().connect(sigc::ptr_fun(on_del_end));
    add_end_button->signal_clicked().connect(sigc::ptr_fun(on_add_end));
    next_button->signal_clicked().connect(sigc::ptr_fun(on_next));
    clock_button->signal_clicked().connect(sigc::ptr_fun(on_clock));
    timer_button->signal_clicked().connect(sigc::ptr_fun(on_timer));
    new_button->signal_clicked().connect(sigc::ptr_fun(on_new));
    runtext_button->signal_clicked().connect(sigc::ptr_fun(on_runtext_send));
    
    app->run(*window);
    
    return 0;
}
