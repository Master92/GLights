//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
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