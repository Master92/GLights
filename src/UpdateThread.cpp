/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UpdateThread.cpp
 * Author: nils
 * 
 * Created on 30. August 2016, 11:19
 */

#include "UpdateThread.h"
using namespace Gtk;

UpdateThread::UpdateThread(Communicator *comm, Box *box, Label *timer, Label *group, Label *end) : m_run(false) {
    this->comm = comm;
    this->box = box;
    this->timer = timer;
    this->group = group;
    this->end = end;
}

UpdateThread::~UpdateThread() {
    this->quit();
}

void UpdateThread::run() {
    if(m_run)
        return;
    
    m_run = true;
    m_thread = Glib::Thread::create(sigc::mem_fun(*this, &UpdateThread::do_sth), true);
}

void UpdateThread::quit() {
    m_run = false;
    
    if(m_thread->joinable())
        m_thread->join();
}

void UpdateThread::do_sth() {
    while(m_run) {
        Communicator::return_values values;
        Gdk::RGBA color;
        values = comm->ReceiveMsg();
        
        if(values.color == aip::COLOR_GREEN)
            color.set_rgba(0,255,0,0.5);
        else if(values.color == aip::COLOR_YELLOW)
            color.set_rgba(255,255,0,0.5);
        else
            color.set_rgba(255,0,0,0.5);
        
        timer->set_text(Glib::ustring::format(values.time));
        Glib::ustring group;
        group = (values.group) ? "C/D" : "A/B";
        this->group->set_text(group);
        end->set_text("Passe " + Glib::ustring::format(values.end) + " von " + Glib::ustring::format(values.max_ends));
        box->override_background_color(color);
        Glib::usleep(500000);
    }
}