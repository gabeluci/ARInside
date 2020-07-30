//Copyright (C) 2009 Stefan Nerlich | stefan.nerlich@hotmail.com
//
//This file is part of ARInside.
//
//    ARInside is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 2 of the License.
//
//    ARInside is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <ar.h>
#include <arfree.h>
#include <arstruct.h>
#include <arerrno.h>
#include <arextern.h>
#include "util/Memory.h"

// this is just a little workaround for a bug in ar.h version 7.5
#ifndef AR_FILTER_ERRHANDLER_ENABLE
#ifdef AR_ERRHANDLER_ENABLE
#define AR_FILTER_ERRHANDLER_ENABLE AR_ERRHANDLER_ENABLE
#else
#define AR_FILTER_ERRHANDLER_ENABLE 1
#endif
#endif

// this is just a workarround for a missing definition in ar.h version 7.6.04
#ifdef AR_SESS_CONTROL_PROP_DESIGN_OVERLAYGROUP
#undef AR_SESS_CONTROL_PROP_DESIGN_OVERLAYGROUP
#endif
#define AR_SESS_CONTROL_PROP_DESIGN_OVERLAYGROUP 1961

#ifdef AR_SESS_CONTROL_PROP_API_OVERLAYGROUP
#undef AR_SESS_CONTROL_PROP_API_OVERLAYGROUP
#endif
#define AR_SESS_CONTROL_PROP_API_OVERLAYGROUP 1962

#ifndef AR_RESERV_OVERLAY_STRING
#define AR_RESERV_OVERLAY_STRING "__o"
#endif

#ifndef AR_ORIGINAL_OBJECT
#define AR_ORIGINAL_OBJECT 0
#endif
#ifndef AR_OVERLAID_OBJECT
#define AR_OVERLAID_OBJECT 1
#endif
#ifndef AR_OVERLAY_OBJECT
#define AR_OVERLAY_OBJECT 2
#endif
#ifndef AR_CUSTOM_OBJECT
#define AR_CUSTOM_OBJECT 4
#endif

// normally audit forms are just regular form, but to distinct we define and use our own constant
#define AR_SCHEMA_AUDIT        100
#define AR_SCHEMA_ARCHIVE      101

// to support our own xml object types used in lists
#define AR_STRUCT_ITEM_USER    500
#define AR_STRUCT_ITEM_GROUP   501
#define AR_STRUCT_ITEM_ROLE    502

#define AR_STRUCT_ITEM_XML_USER       (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_USER)
#define AR_STRUCT_ITEM_XML_GROUP      (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_GROUP)
#define AR_STRUCT_ITEM_XML_ROLE       (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_ROLE)

// api version definitions (see AR_CURRENT_API_VERSION in ar.h)
#define AR_API_VERSION_450 7
#define AR_API_VERSION_500 8			// TODO: check this again !!
#define AR_API_VERSION_510 9
#define AR_API_VERSION_600 10
#define AR_API_VERSION_630 11
#define AR_API_VERSION_700 12
#define AR_API_VERSION_710 13
#define AR_API_VERSION_750 14
#define AR_API_VERSION_763 17
#define AR_API_VERSION_764 18
#define AR_API_VERSION_800 19
#define AR_API_VERSION_810 20

// see AR_EXPORT_VERSION in arstruct.h for definition
#define AR_XML_VERSION_450 5
#define AR_XML_VERSION_500 6
#define AR_XML_VERSION_510 7
#define AR_XML_VERSION_600 8
#define AR_XML_VERSION_630 8
#define AR_XML_VERSION_700 9
#define AR_XML_VERSION_710 10
#define AR_XML_VERSION_750 11
