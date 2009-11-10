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

//\________________ Add your name in the copyright file (and / or modify your name here)

#include <string.h>
#include <cairo-dock.h>

#include "applet-struct.h"
#include "applet-rss.h"
#include "applet-config.h"

//\_________________ Here you have to get all your parameters from the conf file. Use the macros CD_CONFIG_GET_BOOLEAN, CD_CONFIG_GET_INTEGER, CD_CONFIG_GET_STRING, etc. myConfig has been reseted to 0 at this point. This function is called at the beginning of init and reload.
CD_APPLET_GET_CONFIG_BEGIN

	double couleur[4] = {0., 0., 0.5, 1.};
	
	//\___________________ Section Configuration
	myConfig.cUrl 			= CD_CONFIG_GET_STRING ("Configuration", "url_rss_feed");
	myConfig.iRefreshTime 		= 60 * CD_CONFIG_GET_INTEGER ("Configuration", "refresh_time");
	myConfig.iNbLinesInDialog 	= CD_CONFIG_GET_INTEGER ("Configuration", "lines_rss_feed");
	myConfig.iMaxLines 		= CD_CONFIG_GET_INTEGER ("Configuration", "max_lines_for_feed_lines");  /// pas franchement utile...
	myConfig.cSpecificWebBrowser 	= CD_CONFIG_GET_STRING ("Configuration", "specific_web_browser");  // si NULL, on ouvrira l'URL avec les fonctions du dock, xdg-open est loin d'etre installe partout.
	myConfig.bDialogIfFeedChanged = CD_CONFIG_GET_BOOLEAN ("Configuration", "dialog_feed_changed");
	myConfig.cAnimationIfFeedChanged = CD_CONFIG_GET_STRING ("Configuration", "animation_feed_changed");
	myConfig.iDialogsDuration 	= 1000 * CD_CONFIG_GET_INTEGER ("Configuration", "dialogs_duration");
	
	//\___________________ Section Appearance
	// logo
	myConfig.bDisplayLogo 		= CD_CONFIG_GET_BOOLEAN ("Appearance", "display_logo");
	myConfig.fLogoSize 		= CD_CONFIG_GET_DOUBLE ("Appearance", "logo_size");
	
	// decoration
	myConfig.bDisplayBackground = CD_CONFIG_GET_BOOLEAN ("Appearance", "display_background");
	CD_CONFIG_GET_COLOR_WITH_DEFAULT ("Appearance", "background_color1", myConfig.fBackgroundColor1, couleur);
	CD_CONFIG_GET_COLOR_WITH_DEFAULT ("Appearance", "background_color2", myConfig.fBackgroundColor2, couleur);
	myConfig.iBackgroundRadius = CD_CONFIG_GET_INTEGER ("Appearance", "background_radius");
	myConfig.iBorderThickness = CD_CONFIG_GET_INTEGER ("Appearance", "border_thickness");
	CD_CONFIG_GET_COLOR_WITH_DEFAULT ("Appearance", "border_color", myConfig.fBorderColor, couleur);
	
	// titre
	CD_CONFIG_GET_COLOR_WITH_DEFAULT ("Appearance", "title_color", myConfig.fTitleTextColor, couleur);
	myConfig.cTitleFont = CD_CONFIG_GET_STRING ("Appearance", "title_font");  // avec Pango il suffit de lui passer la chaine issue du GtkFontWidget.
	myConfig.fTitleAlignment = CD_CONFIG_GET_DOUBLE ("Appearance", "title_align");  // alignement a gauche du titre
	
	// texte
	CD_CONFIG_GET_COLOR_WITH_DEFAULT ("Appearance", "text_color", myConfig.fTextColor, couleur);
	myConfig.cFont = CD_CONFIG_GET_STRING ("Appearance", "font");  // avec Pango il suffit de lui passer la chaine issue du GtkFontWidget.
	myConfig.iTextMargin = CD_CONFIG_GET_INTEGER ("Appearance", "text_margin");  // marge a gauche du texte.
	myConfig.iSpaceBetweenFeedLines = CD_CONFIG_GET_INTEGER ("Appearance", "space_between_feed_lines");
	
	// Other
	myConfig.cLogoPath 		= CD_CONFIG_GET_FILE_PATH ("Icon", "icon", "icon.svg");
	myConfig.cUserTitle 		= CD_CONFIG_GET_STRING ("Icon", "name");
CD_APPLET_GET_CONFIG_END


//\_________________ Here you have to free all ressources allocated for myConfig. This one will be reseted to 0 at the end of this function. This function is called right before you get the applet's config, and when your applet is stopped, in the end.
CD_APPLET_RESET_CONFIG_BEGIN
	g_free (myConfig.cUrl);
	g_free (myConfig.cUserTitle);
	g_free (myConfig.cSpecificWebBrowser);
	g_free (myConfig.cLogoPath);
	g_free (myConfig.cTitleFont);
	g_free (myConfig.cFont);
CD_APPLET_RESET_CONFIG_END


//\_________________ Here you have to free all ressources allocated for myData. This one will be reseted to 0 at the end of this function. This function is called when your applet is stopped, in the very end.
CD_APPLET_RESET_DATA_BEGIN
	cairo_dock_free_task (myData.pTask);  // stoppe et detruit la tache.
	g_free (myData.cTaskBridge);
	cd_rssreader_free_item_list (myApplet);
CD_APPLET_RESET_DATA_END