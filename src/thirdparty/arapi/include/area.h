/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef AREA_H
#define AREA_H

#include "ar.h"
#include "arplugin.h"

#define AREA_PLUGIN_VERSION        2

                                       /* loginStatus                       */
#define AREA_LOGIN_SUCCESS         0   /* Successful login                  */
#define AREA_LOGIN_UNKNOWN_USER    1   /* User not known to the system      */
#define AREA_LOGIN_FAILED          2   /* Login failed to authenticate      */
#define AREA_LOGIN_LOCK_OUT        3   /* User Locked out from Auth System  */

                                        /* licenseMask                      */
#define AREA_LICENSE_MASK_WRITE     0x1 /* Setting write license            */
#define AREA_LICENSE_MASK_FULL_TEXT 0x2 /* Setting Full Text Search license */
#define AREA_LICENSE_MASK_RESERVED1 0x4
#define AREA_LICENSE_MASK_APPS      0x8 /* Setting Application License      */
#define AREA_LICENSE_MASK_ALL       0x0F

typedef struct AREAResponseStruct {
         unsigned int  licenseMask;        /* AREA_LICENSE_MASK_*           */
         unsigned int  licenseWrite;       /* AR_LICENSE_TYPE_* from AR API */
         unsigned int  licenseFTS;         /* AR_LICENSE_TYPE_* from AR API */
         unsigned int  licenseRes1;        /* AR_LICENSE_TYPE_* from AR API */
         char         *licenseApps;        /* AR_LICENSE_TYPE_* from AR API */
         char         *groups;             /* semi-colon separated list     */
         unsigned int  notifyMech;         /* AR_NOTIFY_* from AR API       */
         char         *email;
         unsigned int  loginStatus;        /* AREA_LOGIN_*                  */
         char         *messageText;
         char         *logText;
         ARTimestamp   modTime;
} AREAResponseStruct;


EXTERN_FUNCTION (ARPLUGIN_EXPORT void AREAVerifyLoginCallback, (
                               void *object,
                               ARAccessNameType  user,
                               ARAccessNameType  password,
                               ARAccessNameType  networkAddr,
                               ARNameType        authString,
                               AREAResponseStruct **response));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int AREANeedToSyncCallback, (
                               void *object));

EXTERN_FUNCTION (ARPLUGIN_EXPORT void AREAFreeCallback, (
                               void *object,
                               AREAResponseStruct *response));

#endif /* AREA_H */
