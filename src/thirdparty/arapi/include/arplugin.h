/*  File: arplugin.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef arplugin_h
#define arplugin_h

#include "ar.h"

#ifndef C_VARIETIES_H
#define C_VARIETIES_H

/* external definition macros extracted from the c_variables.h include file  */
/* Builds the correct external reference for the type of compiler being used */

#if defined(__cplusplus)
    /* Definitions for C++ 2.0 and later */
#   define EXTERN_FUNCTION( rtn, args ) extern "C" { rtn args; }
#   define STRUCT_TAG( tag_name ) /* the tag disappears */
#   define ENUM_BITFIELD( enum_type ) unsigned
#   define ENUM_TYPE( enum_sp, enum_ty ) enum_ty
#   define NAME_CONFLICT( name ) _/**/name
#   define DOTDOTDOT ...
#   define _VOID_ /* anachronism */

#else
#if defined(c_plusplus)
    /* Definitions for C++ 1.2 */
#   define EXTERN_FUNCTION( rtn, args ) rtn args
#   define STRUCT_TAG( tag_name )  /* the tag disappears */
#   define ENUM_BITFIELD( enum_type ) unsigned
#   define ENUM_TYPE( enum_sp, enum_ty ) enum_ty
#   define NAME_CONFLICT( name ) _/**/name
#   define DOTDOTDOT ...
#   define _VOID_ /* anachronism */

#else
#if defined(__STDC__) || defined(_WIN32)
    /* Definitions for ANSI C and Win32 .c files */
#   define EXTERN_FUNCTION( rtn, args ) rtn args
#   define STRUCT_TAG( tag_name ) tag_name
#   define ENUM_BITFIELD( enum_type ) unsigned
#   define ENUM_TYPE( enum_sp, enum_ty ) enum_sp enum_ty
#   define NAME_CONFLICT( name ) name
#   define DOTDOTDOT ...
#   define _VOID_ void

#else
    /* Definitions for Sun/K&R C */
#   define EXTERN_FUNCTION( rtn, args ) rtn()
#   define STRUCT_TAG( tag_name ) tag_name
#   define ENUM_BITFIELD( enum_type ) enum_type
#   define ENUM_TYPE( enum_sp, enum_ty ) enum_sp enum_ty
#   define NAME_CONFLICT( name ) name
#   define DOTDOTDOT
#   define _VOID_

#endif

#endif

#endif

#endif

/* Types of plug-ins */
#define AR_PLUGIN_TYPE_ARDBC  1
#define AR_PLUGIN_TYPE_FILTER 2
#define AR_PLUGIN_TYPE_AREA   3


/* Defines the event types received by ARPluginEvent()            */
#define ARPLUGIN_EVENT_CONFIG   1  /* Configuration has changed   */

/* Defines the property tags used in ARPluginSetProperties()      */
#define AR_PLUGIN_PROP_LOG_FUNCTION             1  /* BYTE: function pointer */
#define AR_PLUGIN_PROP_INSTALL_DIR              2  /* CHAR: AR System install*/
                                                   /*       directory        */
#define AR_PLUGIN_PROP_CONFIG_FILE              3  /* CHAR: ar.cfg/ar.conf   */
                                                   /*       path & file name */
#define AR_PLUGIN_PROP_GETUSER_FUNCTION         4  /* BYTE: function pointer */
#define AR_PLUGIN_PROP_GETAUTHSTRING_FUNCTION   5  /* BYTE: function pointer */
#define AR_PLUGIN_PROP_GETUSERAUTHINFO_FUNCTION 6  /* BYTE: function pointer */
#define AR_PLUGIN_PROP_REGISTERSIGNALHANDLER_FUNCTION 7 /* BYTE: function pointer */
#define AR_PLUGIN_PROP_INITTLS_FUNCTION         8  /* BYTE: function pointer */
#define AR_PLUGIN_PROP_GETCLIENTTYPE_FUNCTION   9  /* INTEGER: function pointer */

typedef struct {
   unsigned int type;      /* AR_PLUGIN_TYPE_...         */
   ARNameType   name;      /* name of plugin             */
   unsigned int version;   /* version of plugin, one of: */
                           /*        AREA_PLUGIN_VERSION */
                           /*       ARDBC_PLUGIN_VERSION */
                           /* ARFILTERAPI_PLUGIN_VERSION */
} ARPluginIdentification;

/* defines the types of native authentication info that can be fetched */
#define AR_NATIVE_AUTHENTICATION_TYPE           1  /* authentication information for current user */

typedef int (*AR_PLUGIN_LOG_FUNCTION)(
               ARPluginIdentification* id,
               int debugLevel, /* IN; the level this mesg is for; See above */
                               /*     "Log level for plug-in logging"       */
               char *text      /* IN; text to output */);

typedef int (*AR_PLUGIN_GETUSER_FUNCTION)(
               ARAccessNameType userName  /* OUT; Username invoking current api */);

typedef int (*AR_PLUGIN_GETAUTHSTRING_FUNCTION)(
               ARAuthType authString  /* OUT; authstring for user invoking current api */);

typedef int (*AR_PLUGIN_GETUSERAUTHINFO_FUNCTION)(
               int type,  /*IN: type of auth info requested. */
                         /*For Now only AR_NATIVE_AUTHENTICATION_TYPE can be requested */
               void **authInfo   /*OUT: The authentication info of the type requested */);

typedef int (*AR_PLUGIN_GETCLIENTTYPE_FUNCTION)(void);

#ifndef _WIN32

/* signature for the plugin's signal handler */
typedef void (AR_PLUGIN_SIGNAL_HANDLER)(int);

/* this is the function thats passed to the plugins for registering their signal handlers */
typedef void (*AR_PLUGIN_REGISTER_FOR_SIGNAL_FUNCTION)(
               int signalId,                          /* IN; the signal Id the handler is meant for */
               AR_PLUGIN_SIGNAL_HANDLER *signalHandler /* IN; pointer to the handler function        */
);
#endif
/* If a plug-in creates its own threads and these threads call any of the
plug-in server's  methods (that were given to plug-in via ARPluginSetProperties)
- the following function must be called from within those threads prior to 
the first plug-in server call. This function pointer is handed off to a plug-in
in ARPluginSetProperties similar to others. */
typedef int (*AR_PLUGIN_INIT_TLS)();

#ifdef _WIN32
#define ARPLUGIN_EXPORT __declspec(dllexport)
#else /* UNIX */
#define ARPLUGIN_EXPORT   
#endif

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginIdentify, (
                ARPluginIdentification*  id,       /* OUT; info about plugin */
                ARStatusList*            status    /* OUT; error message(s)*/));

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginSetProperties, (
                ARPropList*              propList, /* IN; list of properties */
                ARStatusList*            status    /* OUT; error message(s)*/));

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginInitialization, (
                int                      argc,     /*  IN; argc from main() */
                char**                   argv,     /*  IN; argv from main() */
                ARStatusList*            status    /* OUT; error message(s)*/));

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginTermination, (
                ARStatusList*            status    /* OUT; error message(s)*/));

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginCreateInstance, (
                void**                   object,   /* OUT; object created */
                ARStatusList*            status    /* OUT; error message(s)*/));

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginDeleteInstance, (
                void*                    object,   /* IN; object to delete */
                ARStatusList*            status    /* OUT; error message(s)*/));

EXTERN_FUNCTION(ARPLUGIN_EXPORT int ARPluginEvent, (
                unsigned int             eventID,  /* IN; ARPLUGIN_EVENT_... */
                ARStatusList*            status    /* OUT; status of the operation */));

/* These api calls can be invoked only from a plugin. */

EXTERN_FUNCTION (int ARSetUserNameSource, (
                ARControlStruct*,                  /* IN; control struct */ 
                AR_PLUGIN_GETUSER_FUNCTION,        /* IN; function ptr to fetch username */ 
                ARStatusList*                      /* OUT; status of the operation */));

EXTERN_FUNCTION (int ARSetAuthStringSource, (
                ARControlStruct*,                  /* IN; control struct */ 
                AR_PLUGIN_GETAUTHSTRING_FUNCTION,  /* IN; function ptr to fetch authstring */ 
                ARStatusList*                      /* OUT; status of the operation */));

EXTERN_FUNCTION (int ARSetNativeAuthenticationSource, (
                ARControlStruct*,                  /* IN; control struct */ 
                AR_PLUGIN_GETUSERAUTHINFO_FUNCTION,/* IN; function ptr to fetch authinfo */ 
                ARStatusList*                      /* OUT; status of the operation */));

#endif /* arplugin_h */

/* preserve this trailing newline for UNIX compilers */
