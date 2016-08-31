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

