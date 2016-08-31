/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsTimerDialog.cpp
 * Author: nils
 * 
 * Created on 29. August 2016, 10:16
 */

#include "GlightsTimerDialog.h"
using namespace Gtk;

GlightsTimerDialog::GlightsTimerDialog(Window& parent) {
    Glib::RefPtr<Builder> builder = Builder::create();
    builder->add_from_file("GLights.glade", "GlightsTimerDialog");
    builder->get_widget("GlightsTimerDialog", dia);
    
    Glib::RefPtr<Adjustment> adj;
    
    adj = Adjustment::create(0,0,5);
    builder->get_widget("hour_spin", hours_spin);
    hours_spin->set_adjustment(adj);
    
    adj = Adjustment::create(0,0,59);
    builder->get_widget("minute_spin", minutes_spin);
    minutes_spin->set_adjustment(adj);
    
    adj = Adjustment::create(0,0,59);
    builder->get_widget("second_spin", seconds_spin);
    seconds_spin->set_adjustment(adj);
    
    Button *b;
    builder->get_widget("cancel_button2", b);
    b->signal_clicked().connect(sigc::mem_fun(*this, &GlightsTimerDialog::on_cancel));
    
    builder->get_widget("ok_button1", b);
    b->signal_clicked().connect(sigc::mem_fun(*this, &GlightsTimerDialog::on_ok));
    
    dia->set_transient_for(parent);
}

GlightsTimerDialog::~GlightsTimerDialog() {
}

int GlightsTimerDialog::run() {
    return dia->run();
}

int GlightsTimerDialog::get_hours() {
    return hours_spin->get_value();
}

int GlightsTimerDialog::get_minutes() {
    return minutes_spin->get_value();
}

int GlightsTimerDialog::get_seconds() {
    return seconds_spin->get_value();
}


void GlightsTimerDialog::on_cancel() {
    dia->response(RESPONSE_CANCEL);
    dia->hide();
}

void GlightsTimerDialog::on_ok() {
    dia->response(RESPONSE_OK);
    dia->hide();
}