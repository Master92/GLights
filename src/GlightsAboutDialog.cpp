/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlightsAboutDialog.cpp
 * Author: nils
 * 
 * Created on 27. August 2016, 16:13
 */

#include "GlightsAboutDialog.h"

GlightsAboutDialog::GlightsAboutDialog(Gtk::Window& parent) {
    this->set_name("GLights");
    this->set_version("0.1b");
    this->set_transient_for(parent);
    this->set_license_type(Gtk::LICENSE_GPL_3_0);
    this->set_copyright("Nils Friedchen");
    
    std::vector<Glib::ustring> authors;
    authors.push_back("Nils Friedchen");
    this->set_authors(authors);
}

GlightsAboutDialog::~GlightsAboutDialog() {
}

