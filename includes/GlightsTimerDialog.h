/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsTimerDialog.h
 * Author: nils
 *
 * Created on 29. August 2016, 10:16
 */

#ifndef GLIGHTSTIMERDIALOG_H
#define GLIGHTSTIMERDIALOG_H
#include <gtkmm.h>

class GlightsTimerDialog {
public:
    GlightsTimerDialog(Gtk::Window& parent);
    virtual ~GlightsTimerDialog();
    
    int run();
    int get_hours();
    int get_minutes();
    int get_seconds();
private:
    void on_cancel();
    void on_ok();
    
    Gtk::Dialog *dia;
    Gtk::SpinButton *hours_spin, *minutes_spin, *seconds_spin;
};

#endif /* GLIGHTSTIMERDIALOG_H */

