/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsNewRoundDialog.cpp
 * Author: nils
 * 
 * Created on 25. August 2016, 19:05
 */

#include "GlightsNewRoundDialog.h"

using namespace Gtk;

GlightsNewRoundDialog::GlightsNewRoundDialog(Window& parent) {
    Glib::RefPtr<Builder> builder = Builder::create();
    
    builder->add_from_file("./GLights.glade", "GlightsNewRoundDialog");
    
    builder->get_widget("GlightsNewRoundDialog", dia);
    builder->get_widget("ammount_spin1", ammount_spin1);
    builder->get_widget("preparation_spin", preparation_spin);
    builder->get_widget("duration_spin", duration_spin);
    builder->get_widget("group_checkbox", group_checkbox);
    
    Button *b;
    builder->get_widget("cancel_button1", b);
    b->signal_clicked().connect(sigc::mem_fun(*this, &GlightsNewRoundDialog::on_cancel));
    
    builder->get_widget("ok_button", b);
    b->signal_clicked().connect(sigc::mem_fun(*this, &GlightsNewRoundDialog::on_ok));
    
    RadioButton *rb;
    builder->get_widget("indoor_radio", rb);
    rb->signal_clicked().connect(sigc::mem_fun(*this, &GlightsNewRoundDialog::on_indoor));
    
    builder->get_widget("outdoor_radio", rb);
    rb->signal_clicked().connect(sigc::mem_fun(*this, &GlightsNewRoundDialog::on_outdoor));
    
    builder->get_widget("liga_radio", rb);
    rb->signal_clicked().connect(sigc::mem_fun(*this, &GlightsNewRoundDialog::on_liga));
    
    builder->get_widget("custom_radio", rb);
    rb->signal_clicked().connect(sigc::mem_fun(*this, &GlightsNewRoundDialog::on_custom));
    
    Glib::RefPtr<Adjustment> adj;
    ammount_spin1->set_adjustment(adj = Adjustment::create(10, 1, 10));
    preparation_spin->set_adjustment(adj = Adjustment::create(10, 1, 20));
    duration_spin->set_adjustment(adj = Adjustment::create(120, 20, 240));
    
    dia->set_transient_for(parent);
}

int GlightsNewRoundDialog::run() {
    return dia->run();
}

int GlightsNewRoundDialog::get_ammount() {
    return ammount_spin1->get_value();
}

int GlightsNewRoundDialog::get_duration() {
    return duration_spin->get_value();
}

int GlightsNewRoundDialog::get_preparation() {
    return preparation_spin->get_value();
}

bool GlightsNewRoundDialog::get_group() {
    return group_checkbox->get_active();
}


GlightsNewRoundDialog::~GlightsNewRoundDialog() {
}

void GlightsNewRoundDialog::on_cancel() {
    dia->response(RESPONSE_CANCEL);
    dia->hide();
}

void GlightsNewRoundDialog::on_ok() {
    dia->response(RESPONSE_OK);
    dia->hide();
}

void GlightsNewRoundDialog::on_indoor() {
    sensitive(false);
    ammount_spin1->set_value(10);
    preparation_spin->set_value(10);
    duration_spin->set_value(120);
    group_checkbox->set_active(true);
}

void GlightsNewRoundDialog::on_outdoor() {
    sensitive(false);
    ammount_spin1->set_value(6);
    preparation_spin->set_value(10);
    duration_spin->set_value(240);
    group_checkbox->set_active(true);
}

void GlightsNewRoundDialog::on_liga() {
    sensitive(false);
    ammount_spin1->set_value(10);
    preparation_spin->set_value(10);
    duration_spin->set_value(120);
    group_checkbox->set_active(false);
}

void GlightsNewRoundDialog::on_custom() {
    sensitive();
}

void GlightsNewRoundDialog::sensitive(bool set) {
    ammount_spin1->set_sensitive(set);
    preparation_spin->set_sensitive(set);
    duration_spin->set_sensitive(set);
    group_checkbox->set_sensitive(set);
}