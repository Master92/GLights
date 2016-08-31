/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsAboutDialog.h
 * Author: nils
 *
 * Created on 27. August 2016, 16:13
 */

#ifndef GLIGHTSABOUTDIALOG_H
#define GLIGHTSABOUTDIALOG_H
#include <gtkmm.h>

class GlightsAboutDialog : public Gtk::AboutDialog {
public:
    GlightsAboutDialog(Gtk::Window& parent);
    virtual ~GlightsAboutDialog();
private:

};

#endif /* GLIGHTSABOUTDIALOG_H */

