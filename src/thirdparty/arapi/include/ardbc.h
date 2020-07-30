/*  File: ardbc.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef ardbc_h
#define ardbc_h

#include "ar.h"
#include "arplugin.h"

#define ARDBC_PLUGIN_VERSION        3

typedef struct ARVendorFieldStruct {
                  ARNameType      fieldName;
                  ARInternalId    fieldId;
                  int             dataType;
               } ARVendorFieldStruct;

typedef struct ARVendorFieldList {
                  unsigned int                numItems;
                  struct ARVendorFieldStruct *fieldList;
               } ARVendorFieldList;

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCCreateEntry, (
        void              *object,        /* IN; plug-in instance */
        char              *tableName,      /*IN; vendor's table name */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId       transId,       /* IN; transaction ID */
        ARFieldValueList  *fieldValueList,/* IN; list of field/value pairs */
        AREntryIdList     *entryId,       /* OUT; id of entry just created */
        ARStatusList      *status         /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCGetEntry, (
        void              *object,  /* IN; plug-in instance */
        char             *tableName,/* IN; information about the schema holding entry */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId      transId,  /* IN; transaction ID */
        AREntryIdList    *entryId,  /* IN; id of the entry are getting */
        ARInternalIdList *idList,   /* IN; list of fields to return; numItems=0 == ALL*/
        ARFieldValueList *fieldList,/* OUT; list of field/value pairs retrieved */
        ARStatusList     *status    /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCSetEntry, (
        void              *object,        /* IN; plug-in instance */
        char              *tableName,      /*IN; schema to set */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId       transId,       /* IN; transaction ID */
        AREntryIdList     *entryId,       /* IN; key value for the record */
        ARFieldValueList  *fieldValueList,/* IN; list of field/value pairs for entry */
        ARTimestamp        getTimestamp,  /* IN; time at which get of record was done */
        ARStatusList      *status         /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCDeleteEntry, (
        void              *object,    /* IN; plug-in instance */
        char              *tableName, /* IN; info about the schema holding entry */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId       transId,   /* IN; transaction ID */
        AREntryIdList     *entryId,   /* IN; id of the entry to find */
        ARStatusList      *status     /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCGetEntryBLOB, (
        void              *object,    /* IN; plug-in instance */
        char              *tableName, /* IN; info about the schema holding entry */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId       transId,   /* IN; transaction ID */
        AREntryIdList     *entryId,   /* IN; entry id of the entry to get */
        ARInternalId       fieldId,   /* IN; field id of the data to get  */
        ARLocStruct       *loc,       /* OUT; place to put the data */
        ARStatusList      *status     /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCGetListEntryWithFields, (
        void              *object,     /* IN; plug-in instance */
        char              *tableName,  /* IN; info about the schema holding entry */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId       transId,    /* IN; transaction ID */
        ARQualifierStruct *qualifier,  /* IN; qualification(s) for entries to select */
        ARSortList        *sortList,   /* IN; list of fields to sort on in result list*/
        AREntryListFieldList *getListFields,/* IN; fields to be returned in data area */
        unsigned int       firstRetrieve,/*IN; entry to start with (skip ones before) */
        unsigned int       maxRetrieve,/* IN; max number of entries to retrieve */
        AREntryListFieldValueList   *entryList,  /* OUT; list of entries selected */
        unsigned int      *numMatches, /* OUT; number of matches for qualifier; NULL */
                                       /*      if this number not wanted             */
        ARStatusList      *status      /* OUT; status of the operation */));


EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCGetEntryStatistics, (
        void              *object,        /* IN; plug-in instance */
        char              *tableName,     /* IN; info about the schema holding entry */
        ARVendorFieldList *vendorFieldList,/*IN; list of vendor field info */
        ARInternalId       transId,       /* IN; transaction ID */
        ARQualifierStruct *qualifier,     /* IN; qual for entries to select */
        ARFieldValueOrArithStruct *target,/* IN; per entry operation to perform*/
        unsigned int       statistic,     /* IN; statistic to calculate */
        ARInternalIdList  *groupByList,   /* IN; fields on which to group statistics*/
        ARStatisticsResultList *results,  /* OUT; result for each grouping */
        ARStatusList      *status         /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCCommitTransaction, (
        void              *object,  /* IN; plug-in instance */
        ARInternalId       transId, /* IN; transaction ID */
        ARStatusList      *status   /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCRollbackTransaction, (
        void              *object,  /* IN; plug-in instance */
        ARInternalId       transId, /* IN; transaction ID */
        ARStatusList      *status   /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCGetListSchemas, (
        void              *object,  /* IN; plug-in instance */
        ARCompoundSchemaList *schema,/*OUT; list of forms plug-in exposes */
        ARStatusList      *status   /* OUT; status of the operation */));

EXTERN_FUNCTION (ARPLUGIN_EXPORT int ARDBCGetMultipleFields, (
        void              *object,  /* IN; plug-in instance */
        ARCompoundSchema  *schema,  /* IN; form containing the data */
        ARFieldMappingList *mapping,/* OUT; list of fields */
        ARFieldLimitList  *limit,   /* OUT; corresponding field limits */
        ARUnsignedIntList *dataType,/* OUT; corresponding data types */
        ARStatusList      *status   /* OUT; status of the operation */));


#endif /* ardbc_h */
