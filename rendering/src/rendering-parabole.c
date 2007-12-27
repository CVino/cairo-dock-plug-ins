/******************************************************************************

This file is a part of the cairo-dock program, 
released under the terms of the GNU General Public License.

Written by Fabrice Rey (for any bug report, please mail me to fabounet_03@yahoo.fr)

******************************************************************************/
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include <cairo.h>

#ifdef HAVE_GLITZ
#include <gdk/gdkx.h>
#include <glitz-glx.h>
#include <cairo-glitz.h>
#endif

#include <rendering-parabole.h>

extern double my_fParabolePower;
extern double my_fParaboleFactor;

double my_fParaboleCurvature = 0.5;  // puissance de x (alpha).
double my_fParaboleRatio = .33;  // ratio hauteur / largeur fixe => coef de la parabole (lambda).

#define fCurve(x, lambda, alpha) (lambda * pow (x, alpha))
#define fCurve_(x, lambda, alpha) (x != 0 ? lambda * alpha * pow (x, alpha - 1) : (alpha > 1 ? 0 : alpha < 1 ? 1e6 : alpha * lambda))
#define fCurveInv(y, lambda, alpha) pow (y / lambda, 1. / alpha)
#define fCurveInv_(y, lambda, alpha) (y != 0 ? alpha * y * pow (lambda / y, 1. / alpha) : (alpha > 1 ? 0 : alpha < 1 ? 1e6 : alpha * pow (lambda, 1. / alpha)))

void cd_rendering_set_subdock_position_parabole (Icon *pPointedIcon, CairoDock *pDock)
{
	CairoDock *pSubDock = pPointedIcon->pSubDock;
	int iMouseX = pDock->iMouseX;
	//int iX = iMouseX + (-iMouseX + pPointedIcon->fDrawX + pPointedIcon->fWidth * pPointedIcon->fScale / 2) / 2;
	int iX = iMouseX;
	
	if (pDock->iWindowPositionX + pPointedIcon->fDrawX < g_iScreenWidth[pDock->bHorizontalDock] / 2)
	{
		iX = iMouseX + (-iMouseX + pPointedIcon->fDrawX + pPointedIcon->fWidth * pPointedIcon->fScale / 2) / 2;
		pSubDock->fAlign = 0;
		pSubDock->iGapY = (pDock->iGapY + pDock->iMaxDockHeight);
		pSubDock->iGapX = iX + pDock->iWindowPositionX - pSubDock->iMaxDockHeight / 2;
	}
	else
	{
		iX = iMouseX + pPointedIcon->fWidth;
		pSubDock->fAlign = 1;
		pSubDock->iGapY = (pDock->iGapY + pDock->iMaxDockHeight);
		pSubDock->iGapX =  pDock->iWindowPositionX + iX - g_iScreenWidth[pDock->bHorizontalDock];
	}
}


void cd_rendering_calculate_max_dock_size_parabole (CairoDock *pDock)
{
	pDock->pFirstDrawnElement = cairo_dock_calculate_icons_positions_at_rest_linear (pDock->icons, pDock->iFlatDockWidth, pDock->iScrollOffset);
	//pDock->iMaxDockWidth = ceil (cairo_dock_calculate_max_dock_width (pDock, pDock->pFirstDrawnElement, pDock->iFlatDockWidth, 1., 0));
	GList* ic;
	Icon *icon;
	for (ic = pDock->icons; ic != NULL; ic = ic->next)
	{
		icon = ic->data;
		icon->fXMax = icon->fXAtRest + 2*icon->fWidth;
		icon->fXMin = icon->fXAtRest - 2*icon->fWidth;
	}
	
	pDock->iMaxDockWidth = MIN (pDock->iFlatDockWidth, g_iMaxAuthorizedWidth) + 10;
	
	int iParabolicDeviation = my_fParaboleFactor * pDock->iMaxDockWidth;
	pDock->iMaxDockHeight = iParabolicDeviation + pDock->iMaxIconHeight * (1 + 0) + g_iLabelSize;  // pDock->iMaxIconHeight/2 en haut et en bas.
	
	pDock->iDecorationsWidth = 0;
	pDock->iDecorationsHeight = 0;
	
	pDock->iMinDockWidth = pDock->iFlatDockWidth;
	pDock->iMinDockHeight = pDock->iMaxIconHeight;
}

void cd_rendering_calculate_next_point (double xn, double yn, double ds, double lambda, double alpha, double *fXNext, double *fYNext, double *fOrientation)
{
	if (ds <= 0)
	{
		return ;
	}
	double k1, k2, k3, k4, k;
	double Txn, Tyn, Tn;
	double Txnplus1_2, Tynplus1_2, Tnplus1_2, xnplus1_2, ynplus1_2;
	double  xnplus1, ynplus1;
	
	// k1.
	k1 = fCurve_ (xn, lambda, alpha);
	
	// k2.
	Tn = sqrt (1 + k1 * k1);
	Txn = 1. / Tn;
	Tyn = k1 / Tn;
	*fOrientation = atan (Txn / Tyn);
	if (k1 > 1)
	{
		
		ynplus1_2 = yn + ds/2 * Tyn;
		k2 = fCurveInv_ (ynplus1_2, lambda, alpha);
	}
	else
	{
		
		xnplus1_2 = xn + ds/2 * Txn;
		k2 =fCurve_ (xnplus1_2, lambda, alpha);
	}
	
	// k3.
	Tnplus1_2 = sqrt (1 + k2 * k2);
	if (k2 > 1)
	{
		Tynplus1_2 = k2 / Tnplus1_2;
		ynplus1_2 = yn + ds/2 * Tynplus1_2;
		k3 = fCurveInv_ (ynplus1_2, lambda, alpha);
	}
	else
	{
		Txnplus1_2 = 1. / Tnplus1_2;
		xnplus1_2 = xn + ds/2 * Txnplus1_2;
		k3 = fCurve_ (xnplus1_2, lambda, alpha);
	}
	
	// k4.
	Tnplus1_2 = sqrt (1 + k3 * k3);
	if (k3 > 1)
	{
		Tynplus1_2 = k3 / Tnplus1_2;
		ynplus1 = yn + ds * Tynplus1_2;
		k4 = fCurveInv_ (ynplus1, lambda, alpha);
	}
	else
	{
		Txnplus1_2 = 1. / Tnplus1_2;
		xnplus1 = xn + ds * Txnplus1_2;
		k4 = fCurve_ (xnplus1, lambda, alpha);
	}
	
	// k.
	k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	
	// (xn+1, yn+1).
	Tn = sqrt (1 + k * k);
	Txn = 1. / Tn;
	Tyn = k / Tn;
	*fXNext = xn+ ds * Txn;
	*fYNext = yn+ ds * Tyn;
	*fOrientation = atan (Txn / Tyn);
}


void cd_rendering_calculate_construction_parameters_parabole (Icon *icon, int iCurrentWidth, int iCurrentHeight, int iFlatDockWidth, gboolean bDirectionUp, double fAlign, gboolean bHorizontalDock)
{
	double fXIconCenter = icon->fX + icon->fWidth * icon->fScale / 2;  // abscisse du centre de l'icone.
	//g_print ("fXIconCenter : %.2f / %d\n", fXIconCenter, iCurrentWidth);
	//double fYIconCenter = my_fParaboleFactor * iCurrentWidth * pow (fXIconCenter / iCurrentWidth, my_fParabolePower);
	double fMaxYIconCenter = pow (1.*iCurrentWidth, 1./my_fParabolePower);
	double fYIconCenter = my_fParaboleFactor * pow (fMaxYIconCenter - pow ((fAlign == 0 ? iCurrentWidth - fXIconCenter : fXIconCenter), 1./my_fParabolePower), my_fParabolePower);
	//if (fAlign == 1.)
	//	fYIconCenter = fMaxYIconCenter - fYIconCenter;
	if (bDirectionUp)
		fYIconCenter = iCurrentHeight - fYIconCenter;
	
	icon->fWidthFactor = 1.;
	icon->fHeightFactor = 1.;
	
	icon->fDrawX = icon->fX;
	if (icon->fDrawX >= 0 && icon->fDrawX + icon->fWidth * icon->fScale <= iCurrentWidth)
		icon->fAlpha = 1;
	else
		icon->fAlpha = .85;
	
	icon->fDrawY = fYIconCenter - icon->fHeight * icon->fScale / 2;
	icon->fOrientation = .7;
}



void cd_rendering_render_parabole (CairoDock *pDock)
{
	//\____________________ On cree le contexte du dessin.
	cairo_t *pCairoContext = cairo_dock_create_context_from_window (pDock);
	g_return_if_fail (cairo_status (pCairoContext) == CAIRO_STATUS_SUCCESS);
	
	cairo_set_tolerance (pCairoContext, 0.5);  // avec moins que 0.5 on ne voit pas la difference.
	cairo_set_source_rgba (pCairoContext, 0.0, 0.0, 0.0, 0.0);
	cairo_set_operator (pCairoContext, CAIRO_OPERATOR_SOURCE);
	cairo_paint (pCairoContext);
	cairo_set_operator (pCairoContext, CAIRO_OPERATOR_OVER);
	
	//\____________________ On trace le cadre.
	
	
	//\____________________ On dessine les decorations dedans.
	
	//\____________________ On dessine le cadre.
	
	
	//\____________________ On dessine la ficelle qui les joint.
	if (g_iStringLineWidth > 0)
		cairo_dock_draw_string (pCairoContext, pDock, g_iStringLineWidth, FALSE, FALSE);
	
	//\____________________ On dessine les icones et les etiquettes.
	double fRatio = (pDock->iRefCount == 0 ? 1 : g_fSubDockSizeRatio);
	cairo_dock_render_icons_linear (pCairoContext, pDock, fRatio);
	
	cairo_destroy (pCairoContext);
#ifdef HAVE_GLITZ
	if (pDock->pDrawFormat && pDock->pDrawFormat->doublebuffer)
		glitz_drawable_swap_buffers (pDock->pGlitzDrawable);
#endif
}

CairoDockMousePositionType cd_rendering_check_if_mouse_inside_parabole (CairoDock *pDock)
{
	CairoDockMousePositionType iMousePositionType = (pDock->bInside ? CAIRO_DOCK_MOUSE_INSIDE : CAIRO_DOCK_MOUSE_OUTSIDE);
	
	/// A completer.
	return iMousePositionType;
}


Icon *cairo_dock_apply_no_wave_effect (CairoDock *pDock)
{
	//\_______________ On calcule la position du curseur dans le referentiel du dock a plat.
	int dx = pDock->iMouseX - pDock->iCurrentWidth / 2;  // ecart par rapport au milieu du dock a plat.
	int x_abs = dx + pDock->iFlatDockWidth / 2;  // ecart par rapport a la gauche du dock minimal  plat.
	
	//\_______________ On calcule l'ensemble des parametres des icones.
	double fMagnitude = 0.;
	Icon *pPointedIcon = cairo_dock_calculate_wave_with_position_linear (pDock->icons, pDock->pFirstDrawnElement, x_abs, fMagnitude, pDock->iFlatDockWidth, pDock->iCurrentWidth, pDock->iCurrentHeight, pDock->fAlign, pDock->fFoldingFactor);
	return pPointedIcon;
}

Icon *cd_rendering_calculate_icons_parabole (CairoDock *pDock)
{
	Icon *pPointedIcon = cairo_dock_apply_no_wave_effect (pDock);
	
	CairoDockMousePositionType iMousePositionType = cd_rendering_check_if_mouse_inside_parabole (pDock);
	
	cairo_dock_manage_mouse_position (pDock, iMousePositionType);
	
	//\____________________ On calcule les position/etirements/alpha des icones.
	cd_rendering_check_if_mouse_inside_parabole (pDock);
	
	Icon* icon, *prev_icon;
	GList* ic;
	double x = 0, y = 0, theta = 0;
	double alpha = my_fParaboleCurvature, lambda = my_fParaboleRatio * pow (pDock->iCurrentWidth, 1 - alpha), ds;
	for (ic = pDock->icons; ic != NULL; ic = ic->next)
	{
		icon = ic->data;
		cd_rendering_calculate_construction_parameters_parabole (icon, pDock->iCurrentWidth, pDock->iCurrentHeight, pDock->iFlatDockWidth, g_bDirectionUp, pDock->fAlign, pDock->bHorizontalDock);
		cairo_dock_manage_animations (icon, pDock);
		
		if (ic->prev != NULL)
		{
			prev_icon = ic->prev->data;
			ds = (prev_icon->fHeight + g_iIconGap) * (1 - pDock->fFoldingFactor);
			cd_rendering_calculate_next_point (prev_icon->fX, prev_icon->fY, ds, lambda, alpha, &x, &y, &theta);
			g_print ("ds = %.2f => (%.2f;%.2f), %.2fdeg\n", ds, x, y, theta/G_PI*180);
			
			ds += (prev_icon->fWidth / 2 * tan (theta - prev_icon->fOrientation)) * (1 - pDock->fFoldingFactor);
			cd_rendering_calculate_next_point (prev_icon->fX, prev_icon->fY, ds, lambda, alpha, &x, &y, &theta);
			g_print ("  ds = %.2f => (%.2f;%.2f), %.2fdeg\n", ds, x, y, theta/G_PI*180);
			icon->fX = x;
			icon->fY = y;
		}
		else
		{
			icon->fX = 0;
			icon->fY = 0;
		}
		
		icon->fDrawX = icon->fX - 0*icon->fWidth/2 * cos (theta);
		icon->fDrawY = pDock->iCurrentHeight - icon->fY - icon->fHeight - 0*icon->fWidth/2 * sin (theta);
		icon->fOrientation = theta;
	}
	
	return (iMousePositionType == CAIRO_DOCK_MOUSE_INSIDE ? pPointedIcon : NULL);
}


void cd_rendering_register_parabole_renderer (void)
{
	CairoDockRenderer *pRenderer = g_new0 (CairoDockRenderer, 1);
	pRenderer->cReadmeFilePath = g_strdup_printf ("%s/readme-parabolic-view", MY_APPLET_SHARE_DATA_DIR);
	pRenderer->calculate_max_dock_size = cd_rendering_calculate_max_dock_size_parabole;
	pRenderer->calculate_icons = cd_rendering_calculate_icons_parabole;  // cairo_dock_apply_no_wave_effect;
	pRenderer->render = cd_rendering_render_parabole;
	pRenderer->render_optimized = NULL;
	pRenderer->set_subdock_position = cd_rendering_set_subdock_position_parabole;
	
	cairo_dock_register_renderer (MY_APPLET_PARABOLIC_VIEW_NAME, pRenderer);
}
