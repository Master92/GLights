//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation version 2
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