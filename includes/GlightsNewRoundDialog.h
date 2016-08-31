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

