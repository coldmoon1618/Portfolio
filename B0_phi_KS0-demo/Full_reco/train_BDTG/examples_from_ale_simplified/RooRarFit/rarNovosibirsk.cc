/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: RooRarFit
 *    File: $Id: rarNovosibirsk.cc,v 1.2 2007/06/29 08:37:37 zhanglei Exp $
 * Authors: Karsten Koeneke, Lei Zhang
 * History:
 * 
 * Copyright (C) 2006 Massachusetts Institute of Technology, Cambridge
 *  and          2005 University of California, Riverside
 *****************************************************************************/

// -- CLASS DESCRIPTION [RooRarFit] --
// This class provides Novosibirsk Pdf class for RooRarFit

#include "RooRarFit/rarVersion.hh"

#include <iostream>
#include <fstream>
using namespace std;

#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
#include "RooStringVar.h"

#include "RooNovosibirsk.h"

#include "RooRarFit/rarNovosibirsk.hh"

/// \brief Trivial ctor
///
/// Usually the objects should be created using other ctors.
rarNovosibirsk::rarNovosibirsk()
  : rarBasePdf(),
    _x(0), _peak(0), _width(0), _tail(0)
{
  init();
}

/// \brief Default ctor
///
/// \param configFile The config file
/// \param configSec The config section
/// \param configStr The config string
/// \param theDatasets Available datasets
/// \param theData Default dataset for this PDF
/// \param name The name
/// \param title The title
///
/// The default ctor first initializes data members,
/// and then calls #init.
rarNovosibirsk::rarNovosibirsk(const char *configFile, const char *configSec,
			       const char *configStr,
			       rarDatasets *theDatasets, RooDataSet *theData,
			       const char *name, const char *title)
  : rarBasePdf(configFile, configSec, configStr,
	       theDatasets, theData, name, title),
    _x(0), _peak(0), _width(0), _tail(0)
{
  init();
}

rarNovosibirsk::~rarNovosibirsk()
{
}

/// \brief Initial function called by ctor
///
/// \p init is called by the ctor.
/// It first creates the parameters by calling #createAbsReal,
/// and finally it builds the RooNovosibirsk PDF.
void rarNovosibirsk::init()
{
  cout<<"init of rarNovosibirsk for "<<GetName()<<":"<<endl;
  
  // first get its obs
  _x=createAbsReal("x", "observable"); assert(_x);
  // Config pdf params
  _peak=createAbsReal("peak", "peak", 0, -10, 10);
  _width=createAbsReal("width", "width", 0, -10, 10);
  _tail=createAbsReal("tail", "tail", 0, -10, 10);
  _params.Print("v");
  
  // create pdf
  _thePdf=new RooNovosibirsk(Form("the_%s", GetName()),_pdfType+" "+GetTitle(),
			     *_x, *_peak, *_width, *_tail);
}
