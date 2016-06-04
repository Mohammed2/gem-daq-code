// $Id: SimpleWebForm.h,v 1.1 2005/06/07 10:27:13 xdaq Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _SimpleWebForm_h_
#define _SimpleWebForm_h_

#include "xdaq/WebApplication.h"
#include "xgi/Method.h"
#include "xdata/UnsignedLong.h"
#include "cgicc/HTMLClasses.h"

class SimpleWebForm: public xdaq::Application 
{
	public:
	
	XDAQ_INSTANTIATOR();
	
	SimpleWebForm(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
	
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	void setParameter(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	protected:
	
	xdata::UnsignedLong myParameter_;
	
};

#endif
