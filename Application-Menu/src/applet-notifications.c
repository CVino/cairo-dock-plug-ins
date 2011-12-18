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

#include <stdlib.h>
#include <string.h>
#include "gdk/gdkx.h"

#include "applet-struct.h"
#include "applet-menu.h"
#include "applet-app.h"
#include "applet-notifications.h"


static void _show_menu (void)
{
	if (myData.pMenu != NULL)
	{
		cairo_dock_popup_menu_on_icon (myData.pMenu, myIcon, myContainer);
	}
	else  /// either show a message, or remember the user demand, so that we pop the menu as soon as we get it...
	{
		cairo_dock_show_temporary_dialog_with_icon (D_("The application didn't send its menu to us."), myIcon, myContainer, 4000., "same icon");
	}
}

//\___________ Define here the action to be taken when the user left-clicks on your icon or on its subdock or your desklet. The icon and the container that were clicked are available through the macros CD_APPLET_CLICKED_ICON and CD_APPLET_CLICKED_CONTAINER. CD_APPLET_CLICKED_ICON may be NULL if the user clicked in the container but out of icons.
CD_APPLET_ON_CLICK_BEGIN
	_show_menu ();
CD_APPLET_ON_CLICK_END


//\___________ Same as ON_CLICK, but with middle-click.
CD_APPLET_ON_MIDDLE_CLICK_BEGIN
	/// some action ?...
	
CD_APPLET_ON_MIDDLE_CLICK_END


//\___________ Same as ON_CLICK, but with scroll. Moreover, CD_APPLET_SCROLL_UP tels you is the user scrolled up, CD_APPLET_SCROLL_DOWN the opposite.
CD_APPLET_ON_SCROLL_BEGIN
	/// minimize...
	
CD_APPLET_ON_SCROLL_END


//\___________ Define here the entries you want to add to the menu when the user right-clicks on your icon or on its subdock or your desklet. The icon and the container that were clicked are available through the macros CD_APPLET_CLICKED_ICON and CD_APPLET_CLICKED_CONTAINER. CD_APPLET_CLICKED_ICON may be NULL if the user clicked in the container but out of icons. The menu where you can add your entries is available throught the macro CD_APPLET_MY_MENU; you can add sub-menu to it if you want.
CD_APPLET_ON_BUILD_MENU_BEGIN
	/// add the usual window actions ...
		
CD_APPLET_ON_BUILD_MENU_END


void cd_app_menu_on_keybinding_pull (const gchar *keystring, CairoDockModuleInstance *myApplet)
{
	CD_APPLET_ENTER;
	_show_menu ();
	CD_APPLET_LEAVE();
}


static void _check_dock_is_active (gchar *cDockName, CairoDock *pDock, Window *data)
{
	Window xActiveWindow = data[0];
	if (gldi_container_get_Xid (CAIRO_CONTAINER (pDock)) == xActiveWindow)
		data[1] = 1;
}
gboolean cd_app_menu_on_active_window_changed (gpointer pUserData, Window *XActiveWindow)
{
	if (XActiveWindow == NULL)
		return CAIRO_DOCK_LET_PASS_NOTIFICATION;
	
	// check if a dock has the focus (we don't want to control the dock, it wouldn't make sense anyway).
	/// TODO: check each container...
	Window data[2] = {*XActiveWindow, 0};
	cairo_dock_foreach_docks ((GHFunc) _check_dock_is_active, data);
	
	if (data[1] == 0)  // not a dock, so let's take it.
	{
		// take this new window
		cd_app_menu_set_current_window (*XActiveWindow);
	}
	return CAIRO_DOCK_LET_PASS_NOTIFICATION;
}