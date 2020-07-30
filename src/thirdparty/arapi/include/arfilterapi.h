/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef ARFILTERAPI_H
#define ARFILTERAPI_H

#include "ar.h"
#include "arplugin.h"

#define ARFILTERAPI_PLUGIN_VERSION        1

EXTERN_FUNCTION (ARPLUGIN_EXPORT void ARFilterApiCall, (
                              void               *object,
                              ARValueList        *inValues,
                              ARValueList        *outValues,
                              ARStatusList       *status));

#endif /* ARFILTERAPI_H */
