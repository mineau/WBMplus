/******************************************************************************

GHAAS Water Balance/Transport Model V3.0
Global Hydrologic Archive and Analysis System
Copyright 1994-2011, UNH - CCNY/CUNY

MDIrrSoilMoisture.c

dominik.wisser@unh.edu

*******************************************************************************/

#include <stdio.h>
#include <cm.h>
#include <MF.h>
#include <MD.h>

static int _MDOutIrrSoilMoistureID = MFUnset;

enum { MDnone, MDinput, MDcalculate };

int MDIrrSoilMoistureDef() {
	int optID = MFUnset, ret;
	const char *optStr, *optName = MDOptIrrigation;
	const char *options [] = { MDNoneStr, MDInputStr, MDCalculateStr, (char *) NULL };

	if ((optStr = MFOptionGet (optName)) != (char *) NULL) optID = CMoptLookup (options, optStr, true);
		
	if ((optID == MDnone) || (optID == MDinput) || (_MDOutIrrSoilMoistureID != MFUnset)) return (_MDOutIrrSoilMoistureID);

	if ((ret = MDIrrGrossDemandDef ()) == CMfailed) return (CMfailed);
	if (ret == MFUnset) return (MFUnset);
	_MDOutIrrSoilMoistureID = MFVarGetID (MDVarIrrSoilMoisture,     "mm",   MFInput, MFFlux,  MFBoundary);
    return (_MDOutIrrSoilMoistureID);
}
