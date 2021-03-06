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

#include <string.h>
#include <math.h>
#include <cairo-dock.h>

#include "rendering-desklet-tree.h"

#define TREE_WIDTH 150
#define TREE_HEIGHT 161
static int s_iLeafPosition[2][3*3] = {{-30,30,1 , 60,107,0 , -45,115,1},{-60,65,0 , 55,115,1 , -30,115,0}};


static CDTreeParameters *configure (CairoDesklet *pDesklet, CairoDeskletRendererConfigPtr pConfig)
{
	CDTreeParameters *pTree = g_new0 (CDTreeParameters, 1);
	return pTree;
}


static void load_data (CairoDesklet *pDesklet)
{
	CDTreeParameters *pTree = (CDTreeParameters *) pDesklet->pRendererData;
	if (pTree == NULL)
		return ;
	
	double fImageWidth = TREE_WIDTH * pTree->fTreeWidthFactor, fImageHeight = TREE_HEIGHT * pTree->fTreeHeightFactor;
	gchar *cImageFilePath = g_strconcat (MY_APPLET_SHARE_DATA_DIR, "/branche1.svg", NULL);
	
	pTree->pBrancheSurface[0] = cairo_dock_create_surface_from_image_simple (cImageFilePath,
		fImageWidth,
		fImageHeight);
	
	cImageFilePath[strlen(cImageFilePath)-5] = '2';
	pTree->pBrancheSurface[0] = cairo_dock_create_surface_from_image_simple (cImageFilePath,
		fImageWidth,
		fImageHeight);
	g_free (cImageFilePath);
}


static void free_data (CairoDesklet *pDesklet)
{
	cd_message ("");
	CDTreeParameters *pTree = (CDTreeParameters *) pDesklet->pRendererData;
	if (pTree == NULL)
		return ;
	
	cairo_surface_destroy (pTree->pBrancheSurface[0]);
	cairo_surface_destroy (pTree->pBrancheSurface[1]);
	
	g_free (pTree);
	pDesklet->pRendererData = NULL;
}

/*  Not used
static void set_icon_size (CairoDesklet *pDesklet, Icon *pIcon)
{
	CDTreeParameters *pTree = (CDTreeParameters *) pDesklet->pRendererData;
	if (pTree == NULL)
		return ;
	
	if (pIcon == pDesklet->pIcon)
	{
		pIcon->fWidth = 0.;
		pIcon->fHeight = 0.;
	}
	else
	{
		pIcon->fWidth = 48 * MIN (pTree->fTreeWidthFactor, pTree->fTreeHeightFactor);
		pIcon->fHeight = 48 * MIN (pTree->fTreeWidthFactor, pTree->fTreeHeightFactor);
	}
}
*/

static void calculate_icons (CairoDesklet *pDesklet)
{
	g_return_if_fail (pDesklet != NULL);
	CDTreeParameters *pTree = (CDTreeParameters *) pDesklet->pRendererData;
	if (pTree == NULL)
		return ;
	
	Icon *pIcon = pDesklet->pIcon;
	if (pIcon != NULL)  // on ne veut pas charger cette icone.
	{
		pIcon->fWidth = -1;
		pIcon->fHeight = -1;
	}
	
	// on compte le nombre d'icones.
	GList *pIconsList = pDesklet->icons;
	if (pIconsList == NULL)
		return ;
	
	int iNbIcons = 0;
	GList *ic;
	for (ic = pIconsList; ic != NULL; ic = ic->next)
	{
		pIcon = ic->data;
		if (! CAIRO_DOCK_ICON_TYPE_IS_SEPARATOR (pIcon))
			iNbIcons ++;
	}
	
	// on en deduit les parametres de l'arbre.
	pTree->iNbIconsInTree = iNbIcons;
	pTree->iNbBranches = (int) ceil (1.*iNbIcons/3.);
	
	double h = pDesklet->container.iHeight, w = pDesklet->container.iWidth;
	pTree->fTreeWidthFactor = (w > TREE_WIDTH ? 1 : w / TREE_WIDTH);
	pTree->fTreeHeightFactor = h / (pTree->iNbBranches * TREE_HEIGHT);
	
	cd_message (" -> %d icones, %d branches, proportions : %.2fx%.2f", pTree->iNbIconsInTree, pTree->iNbBranches, pTree->fTreeWidthFactor, pTree->fTreeHeightFactor);
	
	// on calcule les tailles de chaque icone.
	for (ic = pIconsList; ic != NULL; ic = ic->next)
	{
		pIcon = ic->data;
		if (CAIRO_DOCK_ICON_TYPE_IS_SEPARATOR (pIcon))
		{
			pIcon->fWidth = 0;
			pIcon->fHeight = 0;
		}
		else
		{
			pIcon->fWidth = 48 * MIN (pTree->fTreeWidthFactor, pTree->fTreeHeightFactor);
			pIcon->fHeight = 48 * MIN (pTree->fTreeWidthFactor, pTree->fTreeHeightFactor);
		}
		cairo_dock_icon_set_allocated_size (pIcon, pIcon->fWidth, pIcon->fHeight);
	}
}


static void render (cairo_t *pCairoContext, CairoDesklet *pDesklet)
{
	CDTreeParameters *pTree = (CDTreeParameters *) pDesklet->pRendererData;
	cd_message ("");
	if (pTree == NULL)
		return ;
	
	double h = pDesklet->container.iHeight, w = pDesklet->container.iWidth;
	int i;
	for (i = 0; i < pTree->iNbBranches; i ++)
	{
		cairo_save (pCairoContext);
		//g_print (" branche %d en (%.2f;%.2f)\n", i, (w - pTree->fTreeWidthFactor * TREE_WIDTH) / 2, h - i * TREE_HEIGHT * pTree->fTreeHeightFactor);
		cairo_translate (pCairoContext, (w - pTree->fTreeWidthFactor * TREE_WIDTH) / 2, h - (i + 1) * TREE_HEIGHT * pTree->fTreeHeightFactor);
		cairo_set_source_surface (pCairoContext, pTree->pBrancheSurface[i%2], 0, 0);
		cairo_paint (pCairoContext);
		cairo_restore (pCairoContext);
	}
	
	
	int iBrancheNumber=0, iBrancheType=0, iLeafNumber=0;
	double x, y;
	int sens;
	Icon *pIcon;
	GList *ic;
	for (ic = pDesklet->icons; ic != NULL; ic = ic->next)
	{
		pIcon = ic->data;
		if (CAIRO_DOCK_ICON_TYPE_IS_SEPARATOR (pIcon))
			continue;
		
		x = s_iLeafPosition[iBrancheType][3*iLeafNumber];
		y = s_iLeafPosition[iBrancheType][3*iLeafNumber+1];
		sens = s_iLeafPosition[iBrancheType][3*iLeafNumber+2];
		
		pIcon->fDrawX = w / 2 + x * pTree->fTreeWidthFactor - pIcon->fWidth / 2;
		pIcon->fDrawY = h - (iBrancheNumber * TREE_HEIGHT + y) * pTree->fTreeHeightFactor - sens * pIcon->fHeight;
		pIcon->fScale = 1;
		pIcon->fAlpha = 1;
		pIcon->fWidthFactor = 1;
		pIcon->fHeightFactor = 1;
		
		cairo_save (pCairoContext);
		cairo_dock_render_one_icon_in_desklet (pIcon, CAIRO_CONTAINER (pDesklet), pCairoContext, TRUE);
		cairo_restore (pCairoContext);
		
		iLeafNumber ++;
		if (iLeafNumber == 3)
		{
			iLeafNumber = 0;
			iBrancheNumber ++;
			iBrancheType = iBrancheNumber % 2;
		}
	}
}


void rendering_register_tree_desklet_renderer (void)
{
	CairoDeskletRenderer *pRenderer = g_new0 (CairoDeskletRenderer, 1);
	pRenderer->render = render ;
	pRenderer->configure = (CairoDeskletConfigureRendererFunc)configure;
	pRenderer->load_data = load_data;
	pRenderer->free_data = free_data;
	pRenderer->calculate_icons = calculate_icons;
	
	cairo_dock_register_desklet_renderer (MY_APPLET_TREE_DESKLET_RENDERER_NAME, pRenderer);
}
