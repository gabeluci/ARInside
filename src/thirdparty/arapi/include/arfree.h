/*  File:  arfree.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

/* External references for the AR System Free routines */

#ifndef AR_FREE_EXTERN_DEFINED
#define AR_FREE_EXTERN_DEFINED

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

EXTERN_FUNCTION(void FreeARFileNameList, (ARFileNameList *, ARBoolean ));
EXTERN_FUNCTION(void FreeARAccessNameList, (ARAccessNameList *, ARBoolean));
EXTERN_FUNCTION(void FreeARPasswordList, (ARPasswordList *, ARBoolean));
EXTERN_FUNCTION(void FreeARActiveLinkActionList, (ARActiveLinkActionList *,
                                                  ARBoolean));
EXTERN_FUNCTION(void FreeARActiveLinkActionListList, (
                                                   ARActiveLinkActionListList *,
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARActiveLinkActionStruct, (ARActiveLinkActionStruct *,
                                                    ARBoolean));
EXTERN_FUNCTION(void FreeARActiveLinkSvcActionStruct, (ARActiveLinkSvcActionStruct *,
                                                      ARBoolean));
EXTERN_FUNCTION(void FreeARArithOpAssignStruct, (ARArithOpAssignStruct *,
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARArithOpStruct, (ARArithOpStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAssignFieldStruct, (ARAssignFieldStruct *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARAssignSQLStruct, (ARAssignSQLStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAssignStruct, (ARAssignStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAttachStruct, (ARAttachStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAutomationStruct, (ARAutomationStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARBooleanList, (ARBooleanList *, ARBoolean));
EXTERN_FUNCTION(void FreeARBooleanListList, (ARBooleanListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARBufStruct, (ARBufStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARBulkEntryReturn, (ARBulkEntryReturn *, ARBoolean));
EXTERN_FUNCTION(void FreeARBulkEntryReturnList, (ARBulkEntryReturnList *,
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARByteList, (ARByteList *, ARBoolean));
EXTERN_FUNCTION(void FreeARCallGuideStruct, (ARCallGuideStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARCharMenuItemStruct, (ARCharMenuItemStruct *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARCharMenuList, (ARCharMenuList *, ARBoolean));
EXTERN_FUNCTION(void FreeARCharMenuSSStruct, (ARCharMenuSSStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARCharMenuStruct, (ARCharMenuStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARCharMenuStructList, (ARCharMenuStructList *,
                                                ARBoolean));

EXTERN_FUNCTION(void FreeARComplexEntryServiceList, (ARComplexEntryServiceList*, ARBoolean));
EXTERN_FUNCTION(void FreeARComplexEntryService, (ARComplexEntryService *, ARBoolean));
EXTERN_FUNCTION(void FreeARComplexEntryServiceOutList, (ARComplexEntryServiceOutList *, ARBoolean));
EXTERN_FUNCTION(void FreeARComplexEntryServiceOut, (ARComplexEntryServiceOut *, ARBoolean));

EXTERN_FUNCTION(void FreeARCOMMethodList, (ARCOMMethodList *, ARBoolean));
EXTERN_FUNCTION(void FreeARCOMMethodParmList, (ARCOMMethodParmList *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARCOMMethodParmStruct, (ARCOMMethodParmStruct *,
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARCOMMethodStruct, (ARCOMMethodStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARCOMValueStruct, (ARCOMValueStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARCompoundSchema, (ARCompoundSchema *, ARBoolean));
EXTERN_FUNCTION(void FreeARCompoundSchemaList, (ARCompoundSchemaList *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARContainerInfoList, (ARContainerInfoList *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARContainerOwnerObjList, (ARContainerOwnerObjList *,
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARContainerTypeList, (ARContainerTypeList *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARCoordList, (ARCoordList *, ARBoolean));
EXTERN_FUNCTION(void FreeARCurrencyStruct, (ARCurrencyStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARCurrencyList, (ARCurrencyList *, ARBoolean));
EXTERN_FUNCTION(void FreeARDDEStruct, (ARDDEStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARDiaryList, (ARDiaryList *, ARBoolean));
EXTERN_FUNCTION(void FreeARDisplayInstanceList, (ARDisplayInstanceList *,
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARDisplayInstanceListList,(ARDisplayInstanceListList *,
                                                    ARBoolean));
EXTERN_FUNCTION(void FreeARDisplayInstanceStruct, (ARDisplayInstanceStruct *,
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARDisplayList, (ARDisplayList *, ARBoolean));
EXTERN_FUNCTION(void FreeAREntryIdList, (AREntryIdList *, ARBoolean));
EXTERN_FUNCTION(void FreeAREntryIdListList, (AREntryIdListList *, ARBoolean));
EXTERN_FUNCTION(void FreeAREntryListFieldListList, (AREntryListFieldListList *,
                                                    ARBoolean));
EXTERN_FUNCTION(void FreeAREntryListFieldList, (AREntryListFieldList *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeAREntryListFieldValueList,(AREntryListFieldValueList *,
                                                     ARBoolean));
EXTERN_FUNCTION(void FreeAREntryListList, (AREntryListList *, ARBoolean));
EXTERN_FUNCTION(void FreeAREnumItemList, (AREnumItemList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldAssignList, (ARFieldAssignList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldAssignStruct, (ARFieldAssignStruct *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARFieldInfoList, (ARFieldInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARExportFieldInfoList, (ARExportFieldInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldInfoStruct, (ARFieldInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARExportFieldInfoStruct, (ARExportFieldInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldLimitList, (ARFieldLimitList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldLimitStruct, (ARFieldLimitStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldMappingList, (ARFieldMappingList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldValueList, (ARFieldValueList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldValueListList, (ARFieldValueListList *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARFieldValueOrArithStruct,(ARFieldValueOrArithStruct *,
                                                    ARBoolean));
EXTERN_FUNCTION(void FreeARFieldValueStruct, (ARFieldValueStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARFilterActionList, (ARFilterActionList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFilterActionListList, (ARFilterActionListList *,
                                                  ARBoolean));
EXTERN_FUNCTION(void FreeARFilterActionStruct, (ARFilterActionStruct *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARFilterActionNotifyAdvanced, (ARFilterActionNotifyAdvanced **,
                                                        ARBoolean));
EXTERN_FUNCTION(void FreeARFullTextInfoList, (ARFullTextInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFullTextInfoRequestList,(ARFullTextInfoRequestList *,
                                                    ARBoolean));
EXTERN_FUNCTION(void FreeARFunctionAssignStruct, (ARFunctionAssignStruct *,
                                                  ARBoolean));
EXTERN_FUNCTION(void FreeARGotoGuideLabelStruct, (ARGotoGuideLabelStruct *,
                                                  ARBoolean));
EXTERN_FUNCTION(void FreeARGroupInfoList, (ARGroupInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARImageDataStruct, (ARImageDataStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARImageDataList, (ARImageDataList *, ARBoolean));
EXTERN_FUNCTION(void FreeARIndexListList, (ARIndexListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARIndexList, (ARIndexList *, ARBoolean));
EXTERN_FUNCTION(void FreeARInternalIdList, (ARInternalIdList *, ARBoolean));
EXTERN_FUNCTION(void FreeARInternalIdListList, (ARInternalIdListList *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARLicenseInfoList, (ARLicenseInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARLicenseInfoStruct, (ARLicenseInfoStruct *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARLicenseNameList, (ARLicenseNameList *, ARBoolean));
EXTERN_FUNCTION(void FreeARLicenseValidList, (ARLicenseValidList *, ARBoolean));
EXTERN_FUNCTION(void FreeARLicenseValidStruct, (ARLicenseValidStruct *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARLocStruct, (ARLocStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARNameList, (ARNameList *, ARBoolean));
EXTERN_FUNCTION(void FreeAROpenDlgStruct, (AROpenDlgStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARPermissionList, (ARPermissionList *, ARBoolean));
EXTERN_FUNCTION(void FreeARPermissionListList, (ARPermissionListList *,
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARPropList, (ARPropList *, ARBoolean));
EXTERN_FUNCTION(void FreeARPropListList, (ARPropListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARPropStruct, (ARPropStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARPushFieldsList, (ARPushFieldsList *, ARBoolean));
EXTERN_FUNCTION(void FreeARQualifierStruct, (ARQualifierStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARQualifierList, (ARQualifierList *, ARBoolean));
EXTERN_FUNCTION(void FreeARReferenceList, (ARReferenceList *, ARBoolean));
EXTERN_FUNCTION(void FreeARReferenceStruct, (ARReferenceStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARRelOpStruct, (ARRelOpStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARServerInfoList, (ARServerInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARServerInfoRequestList, (ARServerInfoRequestList *,
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARServerNameList, (ARServerNameList *, ARBoolean));
EXTERN_FUNCTION(void FreeARSignalList, (ARSignalList *, ARBoolean));
EXTERN_FUNCTION(void FreeARSortListList, (ARSortListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARSortList, (ARSortList *, ARBoolean));
EXTERN_FUNCTION(void FreeARSQLStruct, (ARSQLStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARStatisticsResultList, (ARStatisticsResultList *,
                                                  ARBoolean));
EXTERN_FUNCTION(void FreeARStatusHistoryList, (ARStatusHistoryList *,
                                               ARBoolean));
EXTERN_FUNCTION(void FreeARStatusList, (ARStatusList *, ARBoolean));
EXTERN_FUNCTION(void FreeARStructItemList, (ARStructItemList *, ARBoolean));
EXTERN_FUNCTION(void FreeARStructItemStruct, (ARStructItemStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARSupportFileInfoList, (ARSupportFileInfoList *,
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARSupportFileInfoStruct, (ARSupportFileInfoStruct *,
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARTextStringList, (ARTextStringList *, ARBoolean));
EXTERN_FUNCTION(void FreeARTimestampList, (ARTimestampList *, ARBoolean));
EXTERN_FUNCTION(void FreeARUnsignedIntList, (ARUnsignedIntList *, ARBoolean));
EXTERN_FUNCTION(void FreeARUserInfoList, (ARUserInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARUserLicenseList, (ARUserLicenseList *, ARBoolean));
EXTERN_FUNCTION(void FreeARValueList, (ARValueList *, ARBoolean));
EXTERN_FUNCTION(void FreeARValueListList, (ARValueListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARValueStruct, (ARValueStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARVuiInfoList, (ARVuiInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARVuiInfoStruct, (ARVuiInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARWaitStruct, (ARWaitStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARWorkflowConnectStruct, (ARWorkflowConnectStruct*,
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARWorkflowConnectList, (ARWorkflowConnectList *,
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARXMLParserHandle, (ARXMLParserHandle *, ARBoolean));
EXTERN_FUNCTION(void FreeARXMLParsedStream, (ARXMLParsedStream *, ARBoolean));
EXTERN_FUNCTION(void FreeARXMLInputDoc, (ARXMLInputDoc *, ARBoolean));
EXTERN_FUNCTION(void FreeARXMLOutputDoc, (ARXMLOutputDoc *, ARBoolean ));
EXTERN_FUNCTION(void FreeListARCharMenuStruct, (ARCharMenuStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMacroParmList, (ARMacroParmList *, ARBoolean));
EXTERN_FUNCTION(void FreeARHostIDTypeList, (ARHostIDTypeList *, ARBoolean));
EXTERN_FUNCTION(void FreeARContainerOwnerObjListList, (ARContainerOwnerObjListList *,
                                                      ARBoolean));
EXTERN_FUNCTION(void FreeARReferenceListList, (ARReferenceListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARReferenceTypeList, (ARReferenceTypeList *, ARBoolean));
EXTERN_FUNCTION(void FreeARRoleInfoList, (ARRoleInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARUserLicenseStruct, (ARUserLicenseStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAssociationsToFollowInfoStruct,(ARAssociationsToFollowInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAssociationsToFollowInfoList,(ARAssociationsToFollowInfoList  *, ARBoolean));
EXTERN_FUNCTION(void FreeARArchiveInfoStruct, (ARArchiveInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARArchiveInfoList, (ARArchiveInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARAuditInfoStruct, (ARAuditInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAuditInfoList, (ARAuditInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARObjectInfoStruct,  (ARObjectInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARObjectInfoList,    (ARObjectInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeAREntryListFieldValueStruct, (AREntryListFieldValueStruct *,
                                                       ARBoolean freeStruct));
EXTERN_FUNCTION(void FreeAREntryBlockStruct, (AREntryBlockStruct *,
                                              ARBoolean freeStruct));
EXTERN_FUNCTION(void FreeAREntryBlockList, (AREntryBlockList *,
                                            ARBoolean freeStruct));
EXTERN_FUNCTION(void FreeARLocaleList, (ARLocaleList *,
                                        ARBoolean freeStruct));
EXTERN_FUNCTION(void FreeARSchemaInheritanceListList, (ARSchemaInheritanceListList *, 
                                                       ARBoolean));
EXTERN_FUNCTION(void FreeARSchemaInheritanceList, (ARSchemaInheritanceList *, 
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARSchemaInheritanceStruct, (ARSchemaInheritanceStruct *, 
                                                     ARBoolean));
EXTERN_FUNCTION(void FreeARDataMappingInfoList, (ARDataMappingInfoList *, 
                                                 ARBoolean));
EXTERN_FUNCTION(void FreeARDataMappingInfoStruct, (ARDataMappingInfoStruct *, 
                                                   ARBoolean));
EXTERN_FUNCTION(void FreeARUnsignedIntPtrList, (ARUnsignedIntPtrList *, 
                                                ARBoolean));
EXTERN_FUNCTION(void FreeARNamePtrList, (ARNamePtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldMappingPtrList, (ARFieldMappingPtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARValuePtrList, (ARValuePtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARPermissionListPtrList, (ARPermissionListPtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARFieldLimitPtrList, (ARFieldLimitPtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARDisplayInstanceListPtrList, (ARDisplayInstanceListPtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARAccessNamePtrList, (ARAccessNamePtrList *, ARBoolean));
EXTERN_FUNCTION(void FreeARStatusListList, (ARStatusListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARWfdCurrentLocation, (ARWfdCurrentLocation *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldValueOrArithStruct, (ARMultiSchemaFieldValueOrArithStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaArithOpStruct, (ARMultiSchemaArithOpStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaRelOpStruct, (ARMultiSchemaRelOpStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaQualifierStruct, (ARMultiSchemaQualifierStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldIdList, (ARMultiSchemaFieldIdList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaSortList, (ARMultiSchemaSortList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaQueryFromStruct, (ARMultiSchemaQueryFromStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaQueryFromList, (ARMultiSchemaQueryFromList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFuncQueryFromStruct, (ARMultiSchemaFuncQueryFromStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFuncQueryFromList, (ARMultiSchemaFuncQueryFromList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaRecursiveQueryStruct, (ARMultiSchemaRecursiveQueryStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaRecursiveFuncQueryStruct, (ARMultiSchemaRecursiveFuncQueryStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldValueStruct, (ARMultiSchemaFieldValueStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldValueList, (ARMultiSchemaFieldValueList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldValueListList, (ARMultiSchemaFieldValueListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldFuncValueStruct, (ARMultiSchemaFieldFuncValueStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldFuncValueList, (ARMultiSchemaFieldFuncValueList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldFuncValueListList, (ARMultiSchemaFieldFuncValueListList *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaValueSetQueryStruct, (ARMultiSchemaValueSetQueryStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaValueSetFuncQueryStruct, (ARMultiSchemaValueSetFuncQueryStruct *, ARBoolean));                     
EXTERN_FUNCTION(void FreeARTask, (ARTask *, ARBoolean ));
EXTERN_FUNCTION(void FreeARTaskCheckpoint, (ARTaskCheckpoint *, ARBoolean ));
EXTERN_FUNCTION(void FreeARTaskCheckpointList, (ARTaskCheckpointList *, ARBoolean ));
EXTERN_FUNCTION(void FreeARTaskCheckpointObj, (ARTaskCheckpointObj *, ARBoolean ));
EXTERN_FUNCTION(void FreeARTaskCheckpointObjList, (ARTaskCheckpointObjList *, ARBoolean ));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldFuncList, (ARMultiSchemaFieldFuncList *, ARBoolean));

EXTERN_FUNCTION(void FreeARMultiSchemaFuncQualifierStruct, (ARMultiSchemaFuncQualifierStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFuncArithOpStruct, (ARMultiSchemaFuncArithOpStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFieldFuncValueOrArithStruct, (ARMultiSchemaFieldFuncValueOrArithStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARMultiSchemaFuncRelOpStruct, (ARMultiSchemaFuncRelOpStruct *, ARBoolean));

EXTERN_FUNCTION(void FreeARAssociationMappingStruct, (ARAssociationMappingInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARAssociationMappingList, (ARAssociationMappingInfoList *, ARBoolean));
EXTERN_FUNCTION(void FreeARAssociationFormMappingInfo,(ARAssociationFormMappingInfoStruct *, ARBoolean));
EXTERN_FUNCTION(void FreeARPKFKMappingInfoList,(ARPKFKMappingInfoList *, ARBoolean));



#endif

