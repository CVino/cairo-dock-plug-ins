/**
* This file is a part of the Cairo-Dock project
*
* Copyright : (C) see the 'copyright' file.
* E-mail    : see the 'copyright' file.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __APPLET_RSS__
#define  __APPLET_RSS__

#include <cairo-dock.h>
#include "applet-struct.h"


void cd_rssreader_cut_line (gchar *cLine, PangoLayout *pLayout, int iMaxWidth);


void cd_rssreader_free_item_list (GldiModuleInstance *myApplet);


void cd_rssreader_launch_task (GldiModuleInstance *myApplet);


void cd_rssreader_show_dialog (GldiModuleInstance *myApplet);


#endif
