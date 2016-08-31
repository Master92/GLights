/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsConnectDialog.h
 * Author: nils
 *
 * Created on 22. August 2016, 16:09
 */

#ifndef GLIGHTSCONNECTDIALOG_H
#define GLIGHTSCONNECTDIALOG_H
#include <gtkmm.h>

class GlightsConnectDialog {
public:
    GlightsConnectDialog(Gtk::Window& parent);
    virtual ~GlightsConnectDialog();
    int run();
    int get_ammount();
private:
    void on_cancel();
    void on_connect();
    
    Gtk::Dialog *dia;
    Gtk::SpinButton *spin;
};

#endif /* GLIGHTSCONNECTDIALOG_H */

