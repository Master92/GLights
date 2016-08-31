/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsConnectDialog.cpp
 * Author: nils
 * 
 * Created on 22. August 2016, 16:09
 */

#include "GlightsConnectDialog.h"

using namespace Gtk;

Dialog *dia;

GlightsConnectDialog::GlightsConnectDialog(Window& parent) {
    Glib::RefPtr<Builder> builder = Builder::create();
    
    builder->add_from_file("GLights.glade", "GlightsConnectDialog");
    
    builder->get_widget("GlightsConnectDialog", dia);
    
    Button *b;
    builder->get_widget("cancel_button", b);
    b->signal_clicked().connect(sigc::mem_fun(*this, &GlightsConnectDialog::on_cancel));
    
    builder->get_widget("connect_button", b);
    b->signal_clicked().connect(sigc::mem_fun(*this, &GlightsConnectDialog::on_connect));
    
    Glib::RefPtr<Gtk::Adjustment> adj(Adjustment::create(1,1,4));
    builder->get_widget("ammount_spin", spin);
    spin->set_adjustment(adj);
    
    dia->set_transient_for(parent);
}

int GlightsConnectDialog::run() {
    return dia->run();
}

int GlightsConnectDialog::get_ammount() {
    return spin->get_value();
}

GlightsConnectDialog::~GlightsConnectDialog() {
}

void GlightsConnectDialog::on_cancel() {
    dia->response(RESPONSE_CANCEL);
    dia->hide();
}

void GlightsConnectDialog::on_connect() {
    dia->response(RESPONSE_OK);
    dia->hide();
}