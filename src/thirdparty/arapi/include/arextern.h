/*  File: arextern.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

/* External declarations of the API for the AR System */

#ifndef AR_EXTERN_DEFINED
#define AR_EXTERN_DEFINED

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

#include <stdio.h>
#include "ar.h"

                         /**  Entry  **/
EXTERN_FUNCTION (int ARGetEntry, (ARControlStruct *, ARNameType,
                       AREntryIdList *, ARInternalIdList *, ARFieldValueList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARSetEntry, (ARControlStruct *, ARNameType,
                       AREntryIdList *, ARFieldValueList *, ARTimestamp,
                       unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARCreateEntry, (ARControlStruct *, ARNameType,
                       ARFieldValueList *, AREntryIdType, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteEntry, (ARControlStruct *, ARNameType,
                       AREntryIdList *, unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARCloseNetworkConnections, (ARControlStruct *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARMergeEntry, (ARControlStruct *, ARNameType,
                       ARFieldValueList *, unsigned int, ARQualifierStruct   *query,
                       unsigned int multimatchOption, AREntryIdType,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListEntry, (ARControlStruct *, ARNameType,
                       ARQualifierStruct *, AREntryListFieldList *,
                       ARSortList *, unsigned int, unsigned int, ARBoolean,
                       AREntryListList *, unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListEntryWithFields, (ARControlStruct *, ARNameType,
                       ARQualifierStruct *, AREntryListFieldList *,
                       ARSortList *, unsigned int, unsigned int, ARBoolean,
                       AREntryListFieldValueList *, unsigned int *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetOneEntryWithFields, (ARControlStruct *, ARNameType,
                       ARQualifierStruct *, AREntryListFieldList *,
                       ARSortList *, ARBoolean,
                       AREntryListFieldValueList *, unsigned int *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListEntryBlocks, (ARControlStruct *, ARNameType,
                       ARQualifierStruct *, AREntryListFieldList *,
                       ARSortList *, unsigned int, unsigned int, unsigned int,
                       ARBoolean, AREntryBlockList *, unsigned int *,
                       unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARGetEntryBlock, (AREntryBlockList *, unsigned int,
                       AREntryListFieldValueList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetEntryStatistics, (ARControlStruct *, ARNameType,
                       ARQualifierStruct *, ARFieldValueOrArithStruct *,
                       unsigned int, ARInternalIdList *,
                       ARStatisticsResultList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleEntries, (ARControlStruct *, ARNameType,
                       AREntryIdListList *, ARInternalIdList *, ARBooleanList *,
                       ARFieldValueListList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetEntryBLOB, (ARControlStruct *, ARNameType,
                       AREntryIdList *, ARInternalId, ARLocStruct *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARServiceEntry, (ARControlStruct *, ARNameType,
                       AREntryIdList *, ARFieldValueList *, ARInternalIdList *,
                       ARFieldValueList *, ARStatusList *));
                         /**  Help with data structures  **/
EXTERN_FUNCTION (int ARLoadARQualifierStruct, (ARControlStruct *, ARNameType,
                       ARNameType, char *, ARQualifierStruct *,
                       ARStatusList *));
                         /**  Schema  **/
EXTERN_FUNCTION (int ARGetSchema, (ARControlStruct *, ARNameType,
                       ARCompoundSchema *, ARSchemaInheritanceList *,
                       ARPermissionList *, ARPermissionList *,
                       ARInternalIdList *, AREntryListFieldList *, ARSortList *,
                       ARIndexList *, ARArchiveInfoStruct *, ARAuditInfoStruct *, ARNameType, char **,
                       ARTimestamp *, ARAccessNameType, ARAccessNameType,
                       char **, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetSchema, (ARControlStruct *, ARNameType, ARNameType,
                       ARCompoundSchema *, ARSchemaInheritanceList *,
                       ARPermissionList *, ARInternalIdList *,
                       AREntryListFieldList *, ARSortList *, ARIndexList *,
                       ARArchiveInfoStruct *, ARAuditInfoStruct *, ARNameType, char *,
                       ARAccessNameType, char *, ARPropList *, unsigned int,
                       char *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARCreateSchema, (ARControlStruct *, ARNameType,
                       ARCompoundSchema *, ARSchemaInheritanceList *,
                       ARPermissionList *, ARInternalIdList *,
                       AREntryListFieldList *, ARSortList *,
                       ARIndexList *, ARArchiveInfoStruct *, ARAuditInfoStruct *, ARNameType, char *,
                       ARAccessNameType, char *, ARPropList *,
                       char *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteSchema, (ARControlStruct *, ARNameType,
                       unsigned int, char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListSchema, (ARControlStruct *, ARTimestamp,
                       unsigned int, ARNameType, ARInternalIdList *,
                       ARPropList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleSchemas, (ARControlStruct *, ARTimestamp,
                       ARUnsignedIntList *, ARNameList *, ARInternalIdList *,
                       ARBooleanList *, ARNameList *, ARCompoundSchemaList *,
                       ARSchemaInheritanceListList *,
                       ARPermissionListList *,
                       ARPermissionListList *,
                       ARInternalIdListList *,
                       AREntryListFieldListList *, ARSortListList *,
                       ARIndexListList *, ARArchiveInfoList *, ARAuditInfoList *, ARNameList *,
                       ARTextStringList *, ARTimestampList *, ARAccessNameList *,
                       ARAccessNameList *, ARTextStringList *, ARPropListList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListSchemaWithAlias, (ARControlStruct *, ARTimestamp,
                       unsigned int, ARNameType, ARInternalIdList *, ARNameType,
                       ARPropList *, ARNameList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListExtSchemaCandidates, (ARControlStruct *,
                       unsigned int, ARCompoundSchemaList *, ARStatusList *));
                         /**  Field  **/
EXTERN_FUNCTION (int ARGetField, (ARControlStruct *, ARNameType, ARInternalId,
                       ARNameType, ARFieldMappingStruct *, unsigned int *,
                       unsigned int *, unsigned int *, unsigned int *, ARValueStruct *,
                       ARPermissionList *, ARPermissionList *,
                       ARFieldLimitStruct *,
                       ARDisplayInstanceList *, char **, ARTimestamp *,
                       ARAccessNameType, ARAccessNameType, char **,
                       ARPropList*,
                       ARStatusList *));
EXTERN_FUNCTION (int ARSetField, (ARControlStruct *, ARNameType, ARInternalId,
                       ARNameType, ARFieldMappingStruct *, unsigned int *,
                       unsigned int *, unsigned int *, ARValueStruct *, ARPermissionList *,
                       ARFieldLimitStruct *, ARDisplayInstanceList *, char *,
                       ARAccessNameType, char *,
                       unsigned int setFieldOptions, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetMultipleFields, (ARControlStruct *, ARNameType,
                       ARInternalIdList *, ARNamePtrList *, ARFieldMappingPtrList *,
                       ARUnsignedIntPtrList *, ARUnsignedIntPtrList *,
                       ARUnsignedIntPtrList *, ARValuePtrList *, ARPermissionListPtrList *,
                       ARFieldLimitPtrList *, ARDisplayInstanceListPtrList *,
                       ARTextStringList *, ARAccessNamePtrList *, ARTextStringList *,
                       ARUnsignedIntList *, ARPropListList *,
                       ARStatusListList *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateField, (ARControlStruct *, ARNameType,
                       ARInternalId *, ARBoolean, ARNameType,
                       ARFieldMappingStruct *, unsigned int, unsigned int,
                       unsigned int, unsigned int, ARValueStruct *, ARPermissionList *,
                       ARFieldLimitStruct *, ARDisplayInstanceList *, char *,
                       ARAccessNameType, char *, ARPropList *, 
                       ARStatusList *));
EXTERN_FUNCTION (int ARCreateMultipleFields, (ARControlStruct *, ARNameType,
                       ARInternalIdList *, ARBooleanList *, ARNamePtrList *,
                       ARFieldMappingList *, ARUnsignedIntList *, ARUnsignedIntList *,
                       ARUnsignedIntList *, ARUnsignedIntList *, ARValuePtrList *,
                       ARPermissionListPtrList *, ARFieldLimitPtrList *,
                       ARDisplayInstanceListPtrList *, ARTextStringList *,
                       ARAccessNamePtrList *, ARTextStringList *, 
                       ARPropListList *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteField, (ARControlStruct *, ARNameType,
                       ARInternalId, unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteMultipleFields, (ARControlStruct *, ARNameType,
                       ARInternalIdList *, unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARGetListField, (ARControlStruct *, ARNameType,
                       ARULong32, ARTimestamp, ARPropList *objPropList,
                       ARInternalIdList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleFields, (ARControlStruct *, ARNameType,
                       ARInternalIdList *, ARBooleanList *, ARInternalIdList *,
                       ARNameList *, ARFieldMappingList *, ARUnsignedIntList *,
                       ARUnsignedIntList *, ARUnsignedIntList *, ARUnsignedIntList *, ARValueList *,
                       ARPermissionListList *, ARPermissionListList *,
                       ARFieldLimitList *,
                       ARDisplayInstanceListList *, ARTextStringList *,
                       ARTimestampList *, ARAccessNameList *,
                       ARAccessNameList *, ARTextStringList *, ARPropListList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleExtFieldCandidates, (ARControlStruct *,
                       ARCompoundSchema *, ARFieldMappingList *,
                       ARFieldLimitList *, ARUnsignedIntList *,
                       ARStatusList *));
                         /**  Character Menu **/
EXTERN_FUNCTION (int ARGetCharMenu, (ARControlStruct *, ARNameType,
                       unsigned int *, ARCharMenuStruct *, char **,
                       ARTimestamp *, ARAccessNameType, ARAccessNameType,
                       char **, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetCharMenu, (ARControlStruct *, ARNameType, ARNameType,
                       unsigned int *, ARCharMenuStruct *, char *,
                       ARAccessNameType, char *, ARPropList *, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateCharMenu, (ARControlStruct *, ARNameType,
                       unsigned int, ARCharMenuStruct *, char *,
                       ARAccessNameType, char *, ARPropList *, char *, 
                       ARStatusList *));
EXTERN_FUNCTION (int ARDeleteCharMenu, (ARControlStruct *, ARNameType,
                       unsigned int, char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListCharMenu, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARNameList *, ARPropList *,
                       ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleCharMenus, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARBooleanList *, ARNameList *,
                       ARUnsignedIntList *, ARCharMenuStructList *,
                       ARTextStringList *, ARTimestampList *,
                       ARAccessNameList *, ARAccessNameList *,
                       ARTextStringList *, ARPropListList *, ARStatusList *));
EXTERN_FUNCTION (int ARExpandCharMenu, (ARControlStruct *, ARCharMenuStruct *,
                       unsigned int maxRetrieve, ARCharMenuStruct *, unsigned int *numMatches, ARStatusList *));
EXTERN_FUNCTION (int ARExpandSSMenu, (ARControlStruct *, ARCharMenuSSStruct *,
                       ARCharMenuStruct *, ARStatusList *));
                         /**  Filter  **/
EXTERN_FUNCTION (int ARGetFilter, (ARControlStruct *, ARNameType,
                       unsigned int *, ARWorkflowConnectStruct *,unsigned int *,
                       unsigned int *, ARQualifierStruct *,
                       ARFilterActionList *, ARFilterActionList *, char **,
                       ARTimestamp *, ARAccessNameType, ARAccessNameType,
                       char **, ARPropList *, unsigned int *, ARNameType, ARStatusList *));
EXTERN_FUNCTION (int ARSetFilter, (ARControlStruct *, ARNameType, ARNameType,
                       unsigned int *, ARWorkflowConnectStruct *,unsigned int *,
                       unsigned int *, ARQualifierStruct *,
                       ARFilterActionList *, ARFilterActionList *, char *,
                       ARAccessNameType, char *, ARPropList *, unsigned int *,
                       ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateFilter, (ARControlStruct *, ARNameType,
                       unsigned int, ARWorkflowConnectStruct *, unsigned int,
                       unsigned int, ARQualifierStruct *, ARFilterActionList *,
                       ARFilterActionList *, char *, ARAccessNameType, char *,
                       ARPropList *, unsigned int, ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteFilter, (ARControlStruct *, ARNameType,
                       unsigned int, char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListFilter, (ARControlStruct *, ARNameType,
                       ARTimestamp, ARPropList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleFilters, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARBooleanList *, ARNameList *,
                       ARUnsignedIntList *, ARWorkflowConnectList *,
                       ARUnsignedIntList *, ARUnsignedIntList *,
                       ARQualifierList *, ARFilterActionListList *,
                       ARFilterActionListList *, ARTextStringList *,
                       ARTimestampList *, ARAccessNameList *,
                       ARAccessNameList *, ARTextStringList *,
                       ARPropListList *,
                       ARUnsignedIntList *, ARNameList *, ARStatusList *));
                         /**  Escalation  **/
EXTERN_FUNCTION (int ARGetEscalation, (ARControlStruct *, ARNameType,
                       AREscalationTmStruct *, ARWorkflowConnectStruct *,
                       unsigned int *, ARQualifierStruct *,
                       ARFilterActionList *, ARFilterActionList *, char **,
                       ARTimestamp *, ARAccessNameType, ARAccessNameType,
                       char **, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetEscalation, (ARControlStruct *, ARNameType,
                       ARNameType, AREscalationTmStruct *,
                       ARWorkflowConnectStruct *, unsigned int *,
                       ARQualifierStruct *, ARFilterActionList *,
                       ARFilterActionList *, char *, ARAccessNameType, char *,
                       ARPropList *, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateEscalation, (ARControlStruct *, ARNameType,
                       AREscalationTmStruct *, ARWorkflowConnectStruct *,
                       unsigned int, ARQualifierStruct *, ARFilterActionList *,
                       ARFilterActionList *, char *, ARAccessNameType, char *,
                       ARPropList *, char *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteEscalation, (ARControlStruct *, ARNameType,
                       unsigned int, char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListEscalation, (ARControlStruct *, ARNameType,
                       ARTimestamp, ARPropList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleEscalations, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARBooleanList *, ARNameList *,
                       AREscalationTmList *, ARWorkflowConnectList *,
                       ARUnsignedIntList *, ARQualifierList *,
                       ARFilterActionListList *, ARFilterActionListList *,
                       ARTextStringList *, ARTimestampList *,
                       ARAccessNameList *, ARAccessNameList *,
                       ARTextStringList *, ARPropListList *, ARStatusList *));
                         /**  Active Link  **/
EXTERN_FUNCTION (int ARGetActiveLink, (ARControlStruct *, ARNameType,
                       unsigned int *, ARWorkflowConnectStruct *,
                       ARInternalIdList *, ARInternalIdList *,
                       unsigned int *, ARInternalId *,
                       ARInternalId *, unsigned int *, ARQualifierStruct *,
                       ARActiveLinkActionList *, ARActiveLinkActionList *,
                       char **, ARTimestamp *, ARAccessNameType,
                       ARAccessNameType, char **, ARPropList *,
                       unsigned int*, ARNameType, ARStatusList *));
EXTERN_FUNCTION (int ARSetActiveLink, (ARControlStruct *, ARNameType,
                       ARNameType, unsigned int *, ARWorkflowConnectStruct *,
                       ARInternalIdList *, unsigned int *, ARInternalId *,
                       ARInternalId *, unsigned int *, ARQualifierStruct *,
                       ARActiveLinkActionList *, ARActiveLinkActionList *,
                       char *, ARAccessNameType, char *, ARPropList *,
                       unsigned int *, ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateActiveLink, (ARControlStruct *, ARNameType,
                       unsigned int, ARWorkflowConnectStruct *,
                       ARInternalIdList *, unsigned int, ARInternalId *,
                       ARInternalId *, unsigned int, ARQualifierStruct *,
                       ARActiveLinkActionList *, ARActiveLinkActionList *,
                       char *, ARAccessNameType, char *, ARPropList *,
                       unsigned int, ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteActiveLink, (ARControlStruct *, ARNameType,
                       unsigned int, char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListActiveLink, (ARControlStruct *, ARNameType,
                       ARTimestamp, ARPropList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleActiveLinks, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARBooleanList *, ARNameList *,
                       ARUnsignedIntList *, ARWorkflowConnectList *,
                       ARInternalIdListList *, ARInternalIdListList *,
                       ARUnsignedIntList *,
                       ARInternalIdList *, ARInternalIdList *,
                       ARUnsignedIntList *, ARQualifierList *,
                       ARActiveLinkActionListList *,
                       ARActiveLinkActionListList *, ARTextStringList *,
                       ARTimestampList *, ARAccessNameList *,
                       ARAccessNameList *, ARTextStringList *, ARPropListList *,
                       ARUnsignedIntList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListSQLForActiveLink, (ARControlStruct *, ARNameType,
                       unsigned int, int, ARTimestamp, ARFieldValueList *,
                       ARFieldValueList *, unsigned int, ARValueListList *,
                       unsigned int *, char **, ARStatusList *));
EXTERN_FUNCTION (int ARExecuteProcessForActiveLink, (ARControlStruct *,
                       ARNameType, unsigned int, int, int, ARTimestamp,
                       ARFieldValueList *, ARFieldValueList *, int *, char **,
                       char **, ARStatusList *));
                         /**  VUI  **/
EXTERN_FUNCTION (int ARGetVUI, (ARControlStruct *, ARNameType, ARInternalId,
                       ARNameType, ARLocaleType, unsigned int *, ARPropList *,
                       char **, ARTimestamp *, ARAccessNameType,
                       ARAccessNameType, char **, ARPropList *objPropList, ARStatusList *));
EXTERN_FUNCTION (int ARSetVUI, (ARControlStruct *, ARNameType, ARInternalId,
                       ARNameType, ARLocaleType, unsigned int *, ARPropList *,
                       char *, ARAccessNameType, char *, 
                       ARPropList *objPropList, ARStatusList *));
EXTERN_FUNCTION (int ARCreateVUI, (ARControlStruct *, ARNameType,
                       ARInternalId *, ARNameType, ARLocaleType, unsigned int,
                       ARPropList *, char *, ARAccessNameType, char *,
                       ARPropList *objPropList, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteVUI, (ARControlStruct *, ARNameType, ARInternalId,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListVUI, (ARControlStruct *, ARNameType, ARTimestamp,
                 ARPropList *objPropList, ARInternalIdList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleVUIs, (ARControlStruct *, ARNameType schema,
                       ARInternalIdList *wantList, ARTimestamp changedSince,
                       ARBooleanList *existList, ARInternalIdList *gotList,
                       ARNameList *nameList, ARLocaleList *,
                       ARUnsignedIntList *, ARPropListList *,
                       ARTextStringList *, ARTimestampList *,
                       ARAccessNameList *, ARAccessNameList *,
                       ARTextStringList *, ARPropListList *objPropListList, ARStatusList *));
                         /**  Support File  **/
EXTERN_FUNCTION (int ARGetSupportFile, (ARControlStruct *, unsigned int,
                       ARNameType, ARInternalId, ARInternalId, FILE *,
                       ARTimestamp *, ARStatusList *));
EXTERN_FUNCTION (int ARSetSupportFile, (ARControlStruct *, unsigned int,
                       ARNameType, ARInternalId, ARInternalId, FILE *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARCreateSupportFile, (ARControlStruct *, unsigned int,
                       ARNameType, ARInternalId, ARInternalId, FILE *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARDeleteSupportFile, (ARControlStruct *, unsigned int,
                       ARNameType, ARInternalId, ARInternalId, ARStatusList *));
EXTERN_FUNCTION (int ARGetListSupportFile, (ARControlStruct *, unsigned int,
                       ARNameType, ARInternalId, ARTimestamp,
                       ARInternalIdList *, ARStatusList *));
                         /**  Container  **/
EXTERN_FUNCTION (int ARGetContainer, (ARControlStruct *, ARNameType,
                       ARReferenceTypeList *,
                       ARPermissionList *, ARPermissionList *,
                       ARInternalIdList *, ARContainerOwnerObjList *, char **,
                       char **, unsigned int *, ARReferenceList *, char **,
                       ARAccessNameType, ARTimestamp *, ARAccessNameType,
                       char **, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetContainer, (ARControlStruct *, ARNameType, ARNameType,
                       ARPermissionList *, ARInternalIdList *,
                       ARContainerOwnerObjList *, char *, char *,
                       unsigned int *, ARReferenceList *, ARBoolean, char *,
                       ARAccessNameType, char *, ARPropList *, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateContainer, (ARControlStruct *, ARNameType,
                       ARPermissionList *, ARInternalIdList *,
                       ARContainerOwnerObjList *, char *, char *, unsigned int,
                       ARReferenceList *, ARBoolean, char *, ARAccessNameType,
                       char *, ARPropList *, char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListContainer, (ARControlStruct *, ARTimestamp,
                       ARContainerTypeList *, unsigned int,
                       ARContainerOwnerObjList *, ARPropList *,
                       ARContainerInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleContainers, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARContainerTypeList *, unsigned int,
                       ARContainerOwnerObjList *, ARReferenceTypeList *,
                       ARBooleanList *, ARNameList *,
                       ARPermissionListList *, ARPermissionListList *,
                       ARInternalIdListList *, ARContainerOwnerObjListList *,
                       ARTextStringList *, ARTextStringList *,
                       ARUnsignedIntList *, ARReferenceListList *,
                       ARTextStringList *, ARAccessNameList *,
                       ARTimestampList *, ARAccessNameList *,
                       ARTextStringList *, ARPropListList *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteContainer, (ARControlStruct *, ARNameType,
                       unsigned int, char *, ARStatusList *));
                         /**  Miscellaneous  **/
EXTERN_FUNCTION (int ARVerifyUser, (ARControlStruct *, ARBoolean *, ARBoolean *,
                       ARBoolean *, ARStatusList *));
EXTERN_FUNCTION (int ARVerifyUser2, (ARControlStruct *,
      ARBoolean *, ARBoolean *, ARBoolean *,
      ARBoolean *, ARBoolean *, ARBoolean *,
      ARBoolean *,
      ARStatusList *));
EXTERN_FUNCTION (int ARGetListServer, (ARControlStruct *, ARServerNameList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListGroup, (ARControlStruct *, ARAccessNameType,
                       ARAccessNameType, ARGroupInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListUser, (ARControlStruct *, unsigned int, ARTimestamp,
                       ARUserInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARExport, (ARControlStruct *, ARStructItemList *,
                       ARNameType, unsigned int, unsigned int, ARWorkflowLockStruct *,
                       char **, ARStatusList *));
EXTERN_FUNCTION (int ARExportToFile, (ARControlStruct *, ARStructItemList *,
                       ARNameType, unsigned int, unsigned int, ARWorkflowLockStruct *,
                       FILE *, ARStatusList *));
EXTERN_FUNCTION (int ARImport, (ARControlStruct *, ARStructItemList *, char *,
                       unsigned int, char *, ARStatusList *));
EXTERN_FUNCTION (int ARUnImport, (ARControlStruct *, ARStructItemList *, char *,
                       unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARGetServerInfo, (ARControlStruct *,
                       ARServerInfoRequestList *, ARServerInfoList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARSetServerInfo, (ARControlStruct *, ARServerInfoList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARSignal, (ARControlStruct *, ARSignalList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetFullTextInfo, (ARControlStruct *,
                       ARFullTextInfoRequestList *, ARFullTextInfoList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARSetFullTextInfo, (ARControlStruct *,
                       ARFullTextInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetServerStatistics, (ARControlStruct *,
                       ARServerInfoRequestList *, ARServerInfoList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListSQL, (ARControlStruct *, char *, unsigned int,
                       ARValueListList *, unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARExecuteProcess, (ARControlStruct *, char *, int *,
                       char **, ARStatusList *));
EXTERN_FUNCTION (int ARSetServerPort, (ARControlStruct *, ARNameType,
                       int, int, ARStatusList *));
EXTERN_FUNCTION (char *ARGetTextForErrorMessage, (int));
EXTERN_FUNCTION (int ARSetLogging, (ARControlStruct *, ARULong32,
                       ARULong32, FILE *, ARStatusList *));
EXTERN_FUNCTION (int ARValidateFormCache, (ARControlStruct *, ARNameType,
                       ARTimestamp, ARTimestamp, ARTimestamp, ARTimestamp *,
                       int *, int *, ARNameList *, ARTimestamp *, ARTimestamp *,
                       ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetLocalizedValue, (ARControlStruct *,
                     ARLocalizedRequestStruct *, ARValueStruct *,
                     ARTimestamp *, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleLocalizedValues, (ARControlStruct *,
                     ARLocalizedRequestList *, ARValueList *,
                     ARTimestampList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetSessionConfiguration, (ARControlStruct *,
                       unsigned int, ARValueStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARGetSessionConfiguration, (ARControlStruct *,
                       unsigned int, ARValueStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARGetCacheEvent, (ARControlStruct *, ARInternalIdList *,
                       unsigned int, ARInternalIdList *, unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARSetGetEntry, (ARControlStruct *, ARNameType,
                       AREntryIdList *, ARFieldValueList *, ARTimestamp,
                       unsigned int, ARInternalIdList *, ARFieldValueList *, ARStatusList *, ARStatusList *));
                         /**  Alert  **/
EXTERN_FUNCTION (int ARCreateAlertEvent, (ARControlStruct *, ARAccessNameType,
                       char *, int, ARNameType, ARServerNameType, ARNameType,
                       char *, AREntryIdType, ARStatusList *));
EXTERN_FUNCTION (int ARRegisterForAlerts, (ARControlStruct *, int,
                       unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARDeregisterForAlerts, (ARControlStruct *, int,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListAlertUser, (ARControlStruct *,
                       ARAccessNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetAlertCount, (ARControlStruct *,
                       ARQualifierStruct *, unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARDecodeAlertMessage, (ARControlStruct *, unsigned char *,
                       unsigned int, ARTimestamp *, unsigned int *,
                       unsigned int *, char **, char **, char **, char **,
                       char **, char **, ARStatusList *));
                         /**  Startup/Shutdown  **/
EXTERN_FUNCTION (int ARInitialization, (ARControlStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARTermination, (ARControlStruct *, ARStatusList *));
                         /** Encode/Decode **/
EXTERN_FUNCTION (int AREncodeARAssignStruct, (ARControlStruct *,
                       ARAssignStruct *, char **, ARStatusList *));
EXTERN_FUNCTION (int ARDecodeARAssignStruct, (ARControlStruct *, char *,
                       ARAssignStruct *, ARStatusList *));
EXTERN_FUNCTION (int AREncodeARQualifierStruct, (ARControlStruct *,
                       ARQualifierStruct *, char **, ARStatusList *));
EXTERN_FUNCTION (int ARDecodeARQualifierStruct, (ARControlStruct *, char *,
                       ARQualifierStruct *, ARStatusList *));
EXTERN_FUNCTION (int AREncodeStatusHistory, (ARControlStruct *,
                       ARStatusHistoryList *, char **, ARStatusList *));
EXTERN_FUNCTION (int ARDecodeStatusHistory, (ARControlStruct *, char *,
                       ARStatusHistoryList *, ARStatusList *));
EXTERN_FUNCTION (int AREncodeDiary, (ARControlStruct *, ARDiaryList *, char **,
                       ARStatusList *));
EXTERN_FUNCTION (int ARDecodeDiary, (ARControlStruct *, char *, ARDiaryList *,
                       ARStatusList *));
                         /**  License  **/
EXTERN_FUNCTION (int ARValidateLicense, (ARControlStruct *, ARLicenseNameType,
                       ARLicenseValidStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARValidateMultipleLicenses, (ARControlStruct *,
                       ARLicenseNameList *, ARLicenseValidList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARGetListLicense, (ARControlStruct *, ARLicenseNameType,
                       ARLicenseInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateLicense, (ARControlStruct *, ARLicenseInfoStruct *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARDeleteLicense, (ARControlStruct *, ARLicenseNameType,
                       ARLicenseKeyType, ARStatusList *));
EXTERN_FUNCTION (int ARImportLicense, (ARControlStruct *, char *,
                       unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARExportLicense, (ARControlStruct *, char **, ARStatusList *));
                         /**  Currency  **/
EXTERN_FUNCTION (int ARGetMultipleCurrencyRatioSets, (ARControlStruct *,
                       ARTimestampList *, ARTextStringList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetCurrencyRatio, (ARControlStruct *, char *,
                       ARCurrencyCodeType, ARCurrencyCodeType, ARValueStruct *,
                       ARStatusList *));
                         /**  XML  **/
EXTERN_FUNCTION (int ARParseXMLDocument, (ARControlStruct*, ARXMLInputDoc*,
                       ARStructItemList*, ARXMLParsedStream*, ARStructItemList*,
                       ARNameList *, ARStatusList*));
EXTERN_FUNCTION (int ARGetListXMLObjects, (ARControlStruct*, ARXMLInputDoc*,
                       ARObjectInfoList *, ARStatusList*));
EXTERN_FUNCTION (int ARGetImageFromXML, (ARControlStruct*, ARXMLParsedStream*,
                        ARNameType, ARNameType, char **, unsigned int *,
                        char **, ARTimestamp *, char **, ARAccessNameType,
                        ARAccessNameType, char **helpText, char **, ARPropList  *, char **content,
                        ARStatusList *));
EXTERN_FUNCTION (int ARGetSchemaWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,ARNameType,ARNameType,
                        ARCompoundSchema *,ARPermissionList *,ARPermissionList *,ARInternalIdList *,
                        ARInternalIdList *,AREntryListFieldList *,ARSortList *,ARIndexList *,
                        ARIndexList *,ARArchiveInfoStruct *,ARAuditInfoStruct *,ARNameType,     
                        ARInternalId *,ARULong32 *,int *,ARExportFieldInfoList *,ARVuiInfoList *,
                        ARAccessNameType, ARAccessNameType, ARTimestamp *,char **,char **,
                        ARPropList *,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetSchemaFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, ARCompoundSchema*, ARPermissionList*,
                       ARInternalIdList*, AREntryListFieldList*, ARSortList*,
                       ARIndexList*, ARArchiveInfoStruct *, ARAuditInfoStruct *, ARNameType,
                       ARInternalId*, ARULong32 *, int*, ARFieldInfoList*,
                       ARVuiInfoList*, ARAccessNameType, ARAccessNameType, ARTimestamp*,
                       char**, char**, ARPropList*, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARGetFilterWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,
                        ARNameType,ARNameType,unsigned int *,ARWorkflowConnectStruct *,ARWorkflowConnectStruct *,
                        unsigned int *,unsigned int *,ARQualifierStruct *,ARFilterActionList *,ARFilterActionList *,
                        ARAccessNameType,ARAccessNameType,ARTimestamp *,char **,char **,ARPropList *,
                        unsigned int *,ARNameType,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetFilterFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, unsigned int*, ARWorkflowConnectStruct*,
                       unsigned int*, unsigned int*, ARQualifierStruct*,
                       ARFilterActionList*, ARFilterActionList*, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char**, char**, ARPropList*,
                       unsigned int*, ARNameType, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARGetActiveLinkWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,
                        ARNameType, ARNameType,unsigned int *,ARWorkflowConnectStruct *,
                        ARWorkflowConnectStruct *,ARInternalIdList *,ARInternalIdList *,
                        unsigned int *,ARInternalId *,ARInternalId *,unsigned int *,ARQualifierStruct *,
                        ARActiveLinkActionList *,ARActiveLinkActionList *,ARSupportFileInfoList *,
                        ARAccessNameType ,ARAccessNameType ,ARTimestamp *,char **,char **,
                        ARPropList *,unsigned int *,ARNameType ,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetActiveLinkFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, unsigned int*, ARWorkflowConnectStruct*,
                       ARInternalIdList*, unsigned int*, ARInternalId*, ARInternalId*,
                       unsigned int*, ARQualifierStruct*, ARActiveLinkActionList*,
                       ARActiveLinkActionList*, ARSupportFileInfoList*, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char**, char**, ARPropList*,
                       unsigned int*, ARNameType, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARGetEscalationWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,
                        ARNameType,ARNameType,AREscalationTmStruct *,ARWorkflowConnectStruct *,
                        ARWorkflowConnectStruct *,unsigned int *,ARQualifierStruct *,ARFilterActionList *,
                        ARFilterActionList *,ARAccessNameType,ARAccessNameType,ARTimestamp *,
                        char **,char **,ARPropList *,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetEscalationFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, AREscalationTmStruct*, ARWorkflowConnectStruct*,
                       unsigned int*, ARQualifierStruct*, ARFilterActionList*,
                       ARFilterActionList*, ARAccessNameType, ARAccessNameType,
                       ARTimestamp*, char**, char**, ARPropList*, unsigned int*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARGetContainerWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,ARNameType,
                        ARNameType,ARPermissionList *,ARPermissionList *,ARInternalIdList *,ARInternalIdList *,
                        ARContainerOwnerObjList *,ARContainerOwnerObjList *,char **,char **,unsigned int *,
                        ARReferenceList *,ARAccessNameType,ARAccessNameType,ARTimestamp *,char **,
                        char **,ARPropList *,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetContainerFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, ARPermissionList*, ARInternalIdList*,
                       ARContainerOwnerObjList*, char**, char**, unsigned int*,
                       ARReferenceList*, ARAccessNameType, ARAccessNameType,
                       ARTimestamp*, char**, char**, ARPropList*, unsigned int*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARGetMenuFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, unsigned int*, ARCharMenuStruct*,
                       ARAccessNameType, ARAccessNameType, ARTimestamp*, char**,
                       char**, ARPropList*, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARGetVUIWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,
                        ARNameType,ARNameType,ARVuiInfoList *,ARExportFieldInfoList *,
                        ARTimestamp *,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetVUIFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, ARVuiInfoList*, ARFieldInfoList*,
                       ARTimestamp*, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARGetDSOMappingFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, ARNameType, ARServerNameType,
                       ARNameType, ARServerNameType, unsigned int*, unsigned int*,
                       unsigned int*, unsigned int*, unsigned int*, unsigned int*,
                       unsigned int*, unsigned int*, unsigned int*, ARLong32*,
                       char**, char**, char**, char**, char**, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char**, char**, ARPropList*,
                       unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARGetDSOPoolFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, unsigned int*, unsigned int*,
                       ARLong32*, char**, unsigned int*, unsigned int*,
                       ARAccessNameType, ARAccessNameType, ARTimestamp*,
                       char**, char**, ARPropList*, unsigned int*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARGetFieldWithExtensionsFromXML, (ARControlStruct *,ARXMLParsedStream *,
                        ARNameType,ARNameType,ARInternalId *,ARFieldMappingStruct *,unsigned int *,
                        unsigned int *,unsigned int *,unsigned int *,ARValueStruct *,ARPermissionList *,
                        ARPermissionList *,ARFieldLimitStruct *,ARDisplayInstanceList *,ARAccessNameType,
                        ARAccessNameType,ARTimestamp *,char **,char **,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARGetFieldFromXML, (ARControlStruct*, ARXMLParsedStream*,
                       ARNameType, ARNameType, ARInternalId*, ARFieldMappingStruct*,
                       unsigned int*, unsigned int*, unsigned int*, unsigned int*, ARValueStruct*,
                       ARPermissionList*, ARFieldLimitStruct*, ARDisplayInstanceList*,
                       ARAccessNameType, ARAccessNameType, ARTimestamp*, char**,
                       char**, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetDocHeaderToXML,(ARControlStruct*, ARXMLOutputDoc*, ARStatusList*));
EXTERN_FUNCTION (int ARSetDocFooterToXML, (ARControlStruct*, ARXMLOutputDoc*, ARStatusList*));
EXTERN_FUNCTION (int ARSetImageToXML, (ARControlStruct*, ARXMLOutputDoc *xmlOutputDoc,
                       ARBoolean, ARNameType, char *, char *, char *, char *, ARPropList *,
                       char *, ARTimestamp *, ARImageDataStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARSetSchemaWithExtendedFieldsToXML, (ARControlStruct *,ARXMLOutputDoc *,
                     ARBoolean,ARNameType,ARCompoundSchema *,ARPermissionList *,ARInternalIdList *,
                     AREntryListFieldList *,ARSortList *,ARIndexList *,ARArchiveInfoStruct *,ARAuditInfoStruct *,
                     ARNameType,ARInternalId *,ARULong32 *,int *,ARExportFieldInfoList *,ARVuiInfoList *,
                     ARAccessNameType,ARAccessNameType,ARTimestamp *,char *,char *,ARPropList *,
                     unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARSetSchemaToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, ARCompoundSchema*, ARPermissionList*, ARInternalIdList*,
                       AREntryListFieldList*, ARSortList*, ARIndexList*, ARArchiveInfoStruct *,
                       ARAuditInfoStruct *, ARNameType, ARInternalId*, ARULong32*,
                       int*, ARFieldInfoList*,
                       ARVuiInfoList*, ARAccessNameType, ARAccessNameType, ARTimestamp*,
                       char*, char*, ARPropList*, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetFilterToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, unsigned int*, ARWorkflowConnectStruct*, unsigned int*,
                       unsigned int*, ARQualifierStruct*, ARFilterActionList*,
                       ARFilterActionList*, ARAccessNameType, ARAccessNameType,
                       ARTimestamp*, char*, char*, ARPropList*,
                       unsigned int *, ARNameType, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetActiveLinkToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, unsigned int*, ARWorkflowConnectStruct*, ARInternalIdList*,
                       unsigned int*, ARInternalId*, ARInternalId*, unsigned int*,
                       ARQualifierStruct*, ARActiveLinkActionList*,
                       ARActiveLinkActionList*, ARSupportFileInfoList*,
                       ARAccessNameType, ARAccessNameType, ARTimestamp*,
                       char*, char*, ARPropList*,
                       unsigned int *, ARNameType, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetEscalationToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, AREscalationTmStruct*, ARWorkflowConnectStruct*,
                       unsigned int*, ARQualifierStruct*, ARFilterActionList*,
                       ARFilterActionList*, ARAccessNameType, ARAccessNameType,
                       ARTimestamp*, char*, char*, ARPropList*, unsigned int*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARSetContainerToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, ARPermissionList*, ARInternalIdList*, ARContainerOwnerObjList*,
                       char*, char*, unsigned int*, ARReferenceList*, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char*, char*, ARPropList*,
                       unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetMenuToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, unsigned int*, ARCharMenuStruct*, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char*, char*, ARPropList*, unsigned int*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARSetVUIWithExtendedFieldsToXML, (ARControlStruct *,ARXMLOutputDoc *,
                        ARBoolean,ARNameType,ARVuiInfoList *,ARExportFieldInfoList *,
                        ARTimestamp *,unsigned int *,ARStatusList *));
EXTERN_FUNCTION (int ARSetVUIToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, ARVuiInfoList*, ARFieldInfoList*, ARTimestamp*,
                       unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetDSOMappingToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, ARNameType, ARServerNameType, ARNameType, ARServerNameType,
                       unsigned int*, unsigned int*, unsigned int*, unsigned int*,
                       unsigned int*, unsigned int*, unsigned int*, unsigned int*, unsigned int*,
                       ARLong32*, char*, char*, char*, char*, char*, ARAccessNameType, ARAccessNameType,
                       ARTimestamp*, char*, char*, ARPropList*, unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetDSOPoolToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, unsigned int*, unsigned int*, ARLong32*, char*,
                       unsigned int*, unsigned int*, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char*, char*, ARPropList*,
                       unsigned int*, ARStatusList*));
EXTERN_FUNCTION (int ARSetFieldToXML, (ARControlStruct*, ARXMLOutputDoc*, ARBoolean,
                       ARNameType, ARInternalId*, ARFieldMappingStruct*, unsigned int*,
                       unsigned int*, unsigned int*, unsigned int *, ARValueStruct*, ARPermissionList*,
                       ARFieldLimitStruct*, ARDisplayInstanceList*, ARAccessNameType,
                       ARAccessNameType, ARTimestamp*, char*, char*, unsigned int*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARDateToJulianDate, (ARControlStruct *, ARDateStruct *, int *,
                       ARStatusList*));
EXTERN_FUNCTION (int ARJulianDateToDate, (ARControlStruct *, int, ARDateStruct *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARXMLCreateEntry, (ARControlStruct *, char *, char *, char *, char *,
                       char **, ARStatusList *));
EXTERN_FUNCTION (int ARXMLSetEntry, (ARControlStruct *, char *, char *, char *, char *,
                       char *, char *, char **, ARStatusList *));
EXTERN_FUNCTION (int ARXMLGetEntry, (ARControlStruct *, char *, char *, char *, char *,
                       char **, ARStatusList *));
EXTERN_FUNCTION (int ARXMLServiceEntry, (ARControlStruct *, char *, char *, char *, char *,
                       char *, char *, char **, ARStatusList *));

EXTERN_FUNCTION (int ARGetMultipleEntryPoints, (ARControlStruct *, ARTimestamp,
                       ARNameList *, ARReferenceTypeList *, ARNameType *, unsigned int *,
                       unsigned int, ARNameList *, ARUnsignedIntList *, ARTextStringList *,
                       ARNameList *, ARTextStringList *, ARPermissionListList *,
                       ARContainerOwnerObjListList *, ARTextStringList *,
                       ARReferenceListList *, ARTextStringList *, ARTimestampList *,
                       ARPropListList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListRole, (ARControlStruct *, ARNameType, ARAccessNameType,
                       ARAccessNameType, ARRoleInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListApplicationState, (ARControlStruct*, ARNameList*,
                       ARStatusList*));
EXTERN_FUNCTION (int ARGetApplicationState, (ARControlStruct*, ARNameType,
                       ARNameType, ARStatusList*));
EXTERN_FUNCTION (int ARSetApplicationState, (ARControlStruct* ,ARNameType,
                       ARNameType, ARStatusList*));
EXTERN_FUNCTION (int ARBeginBulkEntryTransaction, (ARControlStruct *, ARStatusList *));
EXTERN_FUNCTION (int AREndBulkEntryTransaction, (ARControlStruct * ,unsigned int,
                       ARBulkEntryReturnList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetServerCharSet, (ARControlStruct*, char*, ARStatusList*));
EXTERN_FUNCTION (int ARGetClientCharSet, (ARControlStruct*, char*, ARStatusList*));
EXTERN_FUNCTION (int ARSetImpersonatedUser, (ARControlStruct*, ARAccessNameType, ARStatusList*));
EXTERN_FUNCTION (int ARGetListImage, (ARControlStruct *, ARNameList *, ARTimestamp, char *,
                       ARPropList *, ARNameList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetImage, (ARControlStruct *, ARNameType, ARImageDataStruct *,
                       char **imageType, ARTimestamp *, char **checkSum,
                       char **description, char **helpText, ARAccessNameType owner,
                       ARAccessNameType lastChanged, char **changeDiary,
                       ARPropList *objPropList, ARStatusList *));
EXTERN_FUNCTION (int ARGetMultipleImages, (ARControlStruct *, ARTimestamp, ARNameList *,
                       ARBooleanList *, ARNameList *, ARTextStringList *, ARTimestampList *,
                       ARTextStringList *, ARTextStringList*, ARAccessNameList *, ARAccessNameList *,
                       ARTextStringList *, ARPropListList *, ARTextStringList *, ARImageDataList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARSetImage, (ARControlStruct *, ARNameType, ARNameType,
                       ARImageDataStruct *, char *, char *, char *, ARAccessNameType,
                       char *, ARPropList *, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateImage, (ARControlStruct *, ARNameType, ARImageDataStruct *,
                       char *, char *, char *, ARAccessNameType, char *, ARPropList *,
                       char *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteImage, (ARControlStruct *, ARNameType, ARBoolean,
                       char *, ARStatusList *));
EXTERN_FUNCTION (int ARGetObjectChangeTimes, (ARControlStruct *, ARObjectChangeTimestampList *,
                       ARStatusList *));
EXTERN_FUNCTION (int ARWfdExecute, (ARControlStruct *, unsigned int,
                 unsigned int *, unsigned int *, unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdGetCurrentLocation, (ARControlStruct *, unsigned int,
                                               ARWfdCurrentLocation *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdGetFieldValues, (ARControlStruct *, unsigned int, ARFieldValueList *, ARFieldValueList *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdSetFieldValues, (ARControlStruct *, ARFieldValueList *, ARFieldValueList *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdGetDebugMode, (ARControlStruct *, unsigned int *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdSetDebugMode, (ARControlStruct *, unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARWfdGetFilterQual, (ARControlStruct *, ARQualifierStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdSetQualifierResult, (ARControlStruct *, ARBoolean, ARStatusList *));
EXTERN_FUNCTION (int ARRunEscalation, (ARControlStruct *, ARNameType, ARStatusList *));
EXTERN_FUNCTION (int ARWfdTerminateAPI, (ARControlStruct *, unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARBeginClientManagedTransaction, (ARControlStruct *, char **transactionHandle, ARStatusList *));

EXTERN_FUNCTION (int ARGetListEntryWithMultiSchemaFields, (ARControlStruct *, ARMultiSchemaFuncQueryFromList *,
                     ARMultiSchemaFieldFuncList *, ARMultiSchemaQualifierStruct *, ARMultiSchemaSortList *,
                     unsigned int, unsigned int, ARBoolean, ARMultiSchemaFieldIdList *, ARMultiSchemaFuncQualifierStruct *, 
                     ARMultiSchemaFieldFuncValueListList *, unsigned int *, ARStatusList *));

EXTERN_FUNCTION (int AREndClientManagedTransaction, (ARControlStruct *, int transactionFlag, ARStatusList *));
EXTERN_FUNCTION (int ARRemoveClientManagedTransaction, (ARControlStruct *,ARStatusList *));
EXTERN_FUNCTION (int ARSetClientManagedTransaction, (ARControlStruct *,char *transactionHandle, ARStatusList *));
EXTERN_FUNCTION (int ARWfdGetKeywordValue, (ARControlStruct *, unsigned int, ARValueStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdSetBreakpoint, (ARControlStruct *, ARWfdRmtBreakpoint *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdClearBreakpoint, (ARControlStruct *, unsigned int, ARStatusList *));
EXTERN_FUNCTION (int ARWfdListBreakpoints, (ARControlStruct *, ARWfdRmtBreakpointList *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdClearAllBreakpoints, (ARControlStruct *, ARStatusList *));
EXTERN_FUNCTION (int ARWfdGetUserContext, (ARControlStruct *, unsigned int, ARWfdUserContext *, ARStatusList *));

EXTERN_FUNCTION (int ARCreateTask, (ARControlStruct *, ARNameType, char *, ARPropList *, ARVercntlObjectList *, ARStatusList *));
EXTERN_FUNCTION (int ARSetTask, (ARControlStruct *, ARNameType, ARNameType, char *, ARAccessNameType, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteTask, (ARControlStruct *, ARNameType, ARStatusList *));
EXTERN_FUNCTION (int ARCommitTask, (ARControlStruct *, ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARRollbackTask, (ARControlStruct *, ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateCheckpoint, (ARControlStruct *, ARNameType, ARNameType, char *, ARPropList *, ARStatusList *));
EXTERN_FUNCTION (int ARDeleteCheckpoint, (ARControlStruct *, ARNameType, ARNameType, ARStatusList *));
EXTERN_FUNCTION (int ARRollbackToCheckpoint, (ARControlStruct *, ARNameType, ARNameType, char *, ARStatusList *));
EXTERN_FUNCTION (int ARAddObjects, (ARControlStruct *, ARNameType,  ARVercntlObjectList *,ARStatusList *));
EXTERN_FUNCTION (int ARRemoveObjects, (ARControlStruct *, ARNameType, ARVercntlObjectList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetTask, (ARControlStruct *, ARNameType, int, ARTask *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListTask, (ARControlStruct *, ARAccessNameType, ARTimestamp, int, int, ARTaskInfoList *, ARStatusList *));
EXTERN_FUNCTION (int ARGetListCheckpoint, (ARControlStruct *, ARNameType, ARTimestamp, int, ARTaskCheckpointList *, ARStatusList *));
EXTERN_FUNCTION (int ARCreateOverlay, (ARControlStruct *, AROverlaidStruct *, char *objectModificationLogLabel,   
                 ARNameType, ARInternalId *overlayId, ARStatusList *));
EXTERN_FUNCTION (int ARCreateOverlayFromObject, (ARControlStruct *, AROverlaidStruct *, AROverlaidStruct *, char *objectModificationLogLabel,  
                 ARNameType, ARInternalId *overlayId, ARStatusList *));

#endif
