/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsNewRoundDialog.h
 * Author: nils
 *
 * Created on 25. August 2016, 19:05
 */

#ifndef GLIGHTSNEWROUNDDIALOG_H
#define GLIGHTSNEWROUNDDIALOG_H
#include <gtkmm.h>

#include "aipprotocol.h"

class GlightsNewRoundDialog {
public:
    GlightsNewRoundDialog(Gtk::Window& parent);
    virtual ~GlightsNewRoundDialog();
    int run();
    
    int get_ammount();
    int get_preparation();
    int get_duration();
    bool get_group();
    int get_mode();
private:
    void on_cancel();
    void on_ok();
    void on_indoor();
    void on_outdoor();
    void on_liga();
    void on_custom();
    
    void sensitive(bool set = true);
    
    Gtk::Dialog *dia;
    Gtk::SpinButton *ammount_spin1, *preparation_spin, *duration_spin;
    Gtk::CheckButton *group_checkbox;
};

#endif /* GLIGHTSNEWROUNDDIALOG_H */

