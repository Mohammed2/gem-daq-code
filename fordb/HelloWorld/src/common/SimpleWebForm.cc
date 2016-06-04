// $Id: SimpleWebForm.cc,v 1.2 2006/05/04 15:12:32 xdaq Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#include "SimpleWebForm.h"

//
// provides factory method for instantion of SimpleWeb application
//
XDAQ_INSTANTIATOR_IMPL(SimpleWebForm)

SimpleWebForm::SimpleWebForm(xdaq::ApplicationStub * s)
	throw (xdaq::exception::Exception): xdaq::Application(s)
{	
	xgi::bind(this,&SimpleWebForm::Default, "Default");
	xgi::bind(this,&SimpleWebForm::setParameter, "setParameter");
	
	// initialize parameter to a default value
	myParameter_ = 0;
	
	getApplicationInfoSpace()->fireItemAvailable("myParameter", &myParameter_);
}
	
void SimpleWebForm::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{
	out->getHTTPResponseHeader().addHeader("Content-Type", "text/html");
	*out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
	*out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
	*out << cgicc::title("Simple Web Form") << std::endl;
	
	// This method can be invoked using Linux 'wget' command
	// e.g http://lxcmd101:1972/urn:xdaq-application:lid=23/setParameter?value=24
	std::string method = toolbox::toString("/%s/setParameter",getApplicationDescriptor()->getURN().c_str());
	
	*out << cgicc::fieldset().set("style","font-size: 10pt;  font-family: arial;") << std::endl;
        *out << cgicc::legend("Set the value of myParameter") << cgicc::p() << std::endl;
	*out << cgicc::form().set("method","GET").set("action", method) << std::endl;
	*out << cgicc::input().set("type","text").set("name","value").set("value", myParameter_.toString())   << std::endl;
	*out << cgicc::input().set("type","submit").set("value","Apply")  << std::endl;
	*out << cgicc::form() << std::endl;
	*out << cgicc::fieldset();
	
	
}

void SimpleWebForm::setParameter(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{	
	try
        {
                cgicc::Cgicc cgi(in);
		
		// retrieve value and update exported variable
		myParameter_ = cgi["value"]->getIntegerValue();
		
		// re-display form page 
		this->Default(in,out);		
        }
        catch (const std::exception & e)
        {
                 XCEPT_RAISE(xgi::exception::Exception, e.what());
        }	
}
