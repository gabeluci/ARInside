/*  File:  arstruct.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef AR_STRUCT_DEFINED
#define AR_STRUCT_DEFINED

#define AR_CORE_VERSION            2   /* version number of core definition   */
#define AR_EXPORT_VERSION          12  /* version number of export definition */

                                      /* default version number of internal server defn */
#define AR_INTERNAL_DEFN_DEFAULT_VERSION  0 

#define AR_ENTRY_ID_SEPARATOR      '|'/* join schema entry id separator */

#define AR_CORE_ENTRY_ID           1  /* field-ids of the core fields */
#define AR_CORE_SUBMITTER          2 
#define AR_CORE_CREATE_DATE        3 
#define AR_CORE_ASSIGNED_TO        4 
#define AR_CORE_LAST_MODIFIED_BY   5 
#define AR_CORE_MODIFIED_DATE      6 
#define AR_CORE_STATUS             7 
#define AR_CORE_SHORT_DESCRIPTION  8 
#define AR_CORE_STATUS_HISTORY    15 

#define AR_CORE_DESCRIPTION        9  /* field-ids of obsoleted core fields */
#define AR_CORE_DISPOSITION       10  /* Any existing definitions can       */
#define AR_CORE_RELATED_TO        11  /* remain and will be fully supported.*/
#define AR_CORE_NOTIFY_METHOD     12  /* Any change to the fields will      */
#define AR_CORE_SUBMIT_SEVERITY   13  /* retain the restrictions when these */
#define AR_CORE_ASSIGN_PRIORITY   14  /* were core fields.  They can be     */
                                      /* deleted if desired, but not created*/

#define AR_NUM_CORE_FIELDS         9

#define AR_MAX_CORE_FIELD_ID             99 
#define AR_MAX_RESERVED_FIELD_ID  536870911   /* 0x1fffffff */

#define AR_RESERV_WEIGHT          99  /* Reserved display only field - weight */
#define AR_LIKE_ID                98  /* Reserved for Push/Set Like Field id */
#define AR_SET_DEFAULTS_ID        97  /* Reserved for Set Field Defaults on  */
                                      /*   OpenWindow action.                */

#define AR_RESERV_USER_NAME      101  /* field-ids of the user/group fields */
#define AR_RESERV_PASSWORD       102 
#define AR_RESERV_EMAIL          103  /* these ids are reserved for defining */
#define AR_RESERV_GROUP_LIST     104  /*  users and groups within the AR     */
#define AR_RESERV_GROUP_NAME     105  /*  system                             */
#define AR_RESERV_GROUP_ID       106 
#define AR_RESERV_GROUP_TYPE     107 
#define AR_RESERV_USER_NOTIFY    108 
#define AR_RESERV_LICENSE_TYPE   109 
#define AR_RESERV_LIC_FULL_TEXT  110 
#define AR_RESERV_LIC_RESERVED1  111 
#define AR_RESERV_ASSIGNED_GROUP 112 
#define AR_RESERV_LIC_ASSET      113 
#define AR_RESERV_LIC_CHANGE     114 
#define AR_RESERV_GROUP_FLOATING_LIC      115 
#define AR_RESERV_GROUP_FLOATING_FTS_LIC  116 
#define AR_RESERV_AUTH_USER_NAME          117 
#define AR_RESERV_AUTH_STRING             118 
#define AR_RESERV_COMPUTED_GROUP_LIST     119 
#define AR_RESERV_GROUP_CATEGORY          120 
#define AR_RESERV_COMPUTED_GROUP_QUAL     121 
#define AR_RESERV_APP_LICENSE             122 
#define AR_RESERV_ENCRYPTED_STRING        123 
#define AR_RESERV_FORCE_PWD_CHANGE        124 
#define AR_RESERV_PWD_CHANGE_CONFIRM      125 
#define AR_RESERV_LAST_PWD_CHANGE         126 
#define AR_RESERV_NUM_WARN_DAYS           127 
#define AR_RESERV_NUM_DAYSTOEXPIRE        128
#define AR_RESERV_ZTEMP                   129
#define AR_RESERV_ACCOUNT_DISABLED_DATE   130
#define AR_RESERV_GROUP_PARENT            134
#define AR_RESERV_DISPLAY_GROUP_PARENT    135
#define AR_RESERV_GROUP_OVERLAY           136
#define AR_RESERV_DISPLAY_GROUP_OVERLAY   137
#define AR_RESERV_DISABLE_PWD_MANAGEMENT_FOR_USER 138
#define AR_RESERV_GROUP_APP_FLOATING_LIC  139
#define AR_RESERV_INSTANCE_ID             490000000 
#define AR_RESERV_OBJECT_ID               490000100 


/* Message Catalog reserved fields */

#define ARMC_RESERV_MESSAGE_CAT_STATUS                 7 
#define ARMC_RESERV_MESSAGE_CAT_NAME                   8 
#define ARMC_RESERV_MESSAGE_CAT_MSG_TYPE             150 
#define ARMC_RESERV_MESSAGE_CAT_FLD_ID_OR_MSG_NUM    151 
#define ARMC_RESERV_MESSAGE_CAT_LOCALE               152 

#define ARMC_RESERV_MESSAGE_CAT_RETURN_TYPE          155 
#define ARMC_RESERV_MESSAGE_CAT_MSG_TEXT             156 
#define ARMC_RESERV_MESSAGE_CAT_BIN_ATTACH_POOL      157 
#define ARMC_RESERV_MESSAGE_CAT_BIN_ATTACH_FLD       158 
#define ARMC_RESERV_MESSAGE_CAT_APPL_TAG             159 

#define AR_RESERV_LOCALE_LOCALIZED_SCHEMA            160 
#define AR_RESERV_LOCALE_MSG_TYPE_MENU               161 
#define AR_RESERV_LOCALE_BIN_ATTACH_LABEL            162 
#define AR_RESERV_LOCALE_LOC_SEARCH_CRIT_LABEL       163 
#define AR_RESERV_LOCALE_RETURNED_VALUE_LABEL        164 

                                      /* reserved for SetField action */
#define AR_RESERV_SETFIELD_SCHEMA_NAME    170 

                                      /* reserved for full text form search */
#define AR_RESERV_FTS_OP_TYPE             176   /* reserved for FTS operation type field */
                                                /* should be display only integer field  */
#define AR_RESERV_FTS_DOC_BOOST           177 
#define AR_RESERV_FTS_FORM_SEARCH         178 

                                      /* Reserved for the GUID (Globally Unique */
                                      /* ID) field of the current schema object.*/
                                      /* The field will be a character field    */
                                      /* with the length of 38 characters.      */
#define AR_RESERV_GUID                    179 

                                      /* reserved for Distributed Server */
/* Generic Fields */
#define AR_RESERV_CHANGE_DIARY            180 
#define AR_RESERV_HELP                    181 
#define AR_RESERV_OPROP                   182 

/* Mapping Schema */
#define ARDS_RESERV_DISTRIB_MAPPING_NAME  AR_CORE_SHORT_DESCRIPTION
#define ARDS_RESERV_DISTRIB_FROM_SCHEMA   200 
#define ARDS_RESERV_DISTRIB_FROM_SERVER   201 
#define ARDS_RESERV_DISTRIB_TO_SCHEMA     202 
#define ARDS_RESERV_DISTRIB_TO_SERVER     203 
#define ARDS_RESERV_DISTRIB_UPDATE_CODE   204 
#define ARDS_RESERV_DISTRIB_TRANS_MODE    205 
#define ARDS_RESERV_DISTRIB_MAP_TYPE      206 
#define ARDS_RESERV_DISTRIB_MAPPING       207 
#define ARDS_RESERV_DISTRIB_RTN_MAP_TYPE  208 
#define ARDS_RESERV_DISTRIB_RTN_MAPPING   209 
#define ARDS_RESERV_DISTRIB_DEFAULT_MAP   210 
#define ARDS_RESERV_DISTRIB_DUP_ACTION    211 
#define ARDS_RESERV_DISTRIB_RETRY_TIME    212 
#define ARDS_RESERV_DISTRIB_PATTERN_MATCH 213 
#define ARDS_RESERV_DISTRIB_REQUIRED_FIELDS   214 
#define ARDS_RESERV_DISTRIB_MATCH_QUAL    215 
#define ARDS_RESERV_DISTRIB_EXCL_LIST     217
#define ARDS_RESERV_DISTRIB_RTN_EXCL_LIST 218

/* Pending Schema */
#define ARDS_RESERV_DISTRIB_PENDING_NAME  AR_CORE_SHORT_DESCRIPTION
#define ARDS_RESERV_DISTRIB_SOURCE_ID     250 
#define ARDS_RESERV_DISTRIB_PENDING_TYPE  251 
#define ARDS_RESERV_DISTRIB_PENDING_OTHER 252 
#define ARDS_RESERV_DISTRIB_POOL          253 

/* Pending Errors Schema */
#define ARDS_RESERV_DISTRIB_ERR_PENDING_ID    260 
#define ARDS_RESERV_DISTRIB_ERR_PENDING_TYPE  261 
#define ARDS_RESERV_DISTRIB_ERR_PENDING_OTHER 262
#define ARDS_RESERV_DISTRIB_ERR_POOL          263 
#define ARDS_RESERV_DISTRIB_ERR_PENDING_ERR   264 

/* Pool Schema */
#define ARDS_RESERV_DISTRIB_POOL_NAME     AR_CORE_SHORT_DESCRIPTION
#define ARDS_RESERV_DISTRIB_EXEORDER      230 
#define ARDS_RESERV_DISTRIB_TCOUNT        275 
#define ARDS_RESERV_DISTRIB_CONNECT       276 
#define ARDS_RESERV_DISTRIB_DEFAULT       277 
#define ARDS_RESERV_DISTRIB_OPROP         278 
#define ARDS_RESERV_DISTRIB_POLLING       279
#define ARDS_RESERV_DISTRIB_POLL_INTERVAL 280

/* Logical Mapping Schema */
#define ARDS_RESERV_DISTRIB_LOGICAL_NAME   290
#define ARDS_RESERV_DISTRIB_PHYSICAL_NAME  291
#define ARDS_RESERV_DISTRIB_LOGICAL_SVRNAME_FLAG  292

/* User Schema Extensions */
#define ARDS_RESERV_DISTRIB_TO_MAPPING    300 
#define ARDS_RESERV_DISTRIB_TRANS_STATE   301 
#define ARDS_RESERV_DISTRIB_UPDATE_STATE  302 
#define ARDS_RESERV_DISTRIB_MASTER_FLAG   303 
#define ARDS_RESERV_DISTRIB_CUR_SCHEMA    304 
#define ARDS_RESERV_DISTRIB_CUR_SERVER    305 
#define ARDS_RESERV_DISTRIB_FROM_MAPPING  306 
#define ARDS_RESERV_DISTRIB_FROM_ENTRYID  307 
#define ARDS_RESERV_DISTRIB_TO_ENTRYID    308 
#define ARDS_RESERV_DISTRIB_MAP_HISTORY   309 
#define ARDS_RESERV_DISTRIB_FROM_SCHEMA_2 310 
#define ARDS_RESERV_DISTRIB_FROM_SERVER_2 311 
#define ARDS_RESERV_DISTRIB_TO_SCHEMA_2   312 
#define ARDS_RESERV_DISTRIB_TO_SERVER_2   313 
#define ARDS_RESERV_DISTRIB_UPDATE_CODE_2 314 
#define ARDS_RESERV_DISTRIB_TRANS_MODE_2  315 
#define ARDS_RESERV_DISTRIB_DUP_ACTION_2  316 
#define ARDS_RESERV_DISTRIB_RETRY_TIME_2  317 
#define ARDS_RESERV_DISTRIB_FROM_POOL     318 
#define ARDS_RESERV_DISTRIB_PATTERN_MATCH_2   319 
#define ARDS_RESERV_DISTRIB_REQUIRED_FIELDS_2 320 
#define ARDS_RESERV_DISTRIB_MATCH_QUAL_2  321 
#define ARDS_RESERV_DISTRIB_UNIQUE_ID     322

/* Reserved fields for AR System client menu items */
#define AR_RESERV_MENU_MIN                400 

#define AR_RESERV_MENU_MODIFYALL          401 
#define AR_RESERV_MENU_DELETE             402 
#define AR_RESERV_MENU_PREFERENCES        403 
#define AR_RESERV_MENU_MENU               404 
#define AR_RESERV_MENU_TOOLBAR            405 
#define AR_RESERV_MENU_APPLY              406 
#define AR_RESERV_MENU_POLLING            407 
#define AR_RESERV_MENU_REPORTING          408 
#define AR_RESERV_MENU_PRINT              409 
#define AR_RESERV_MENU_CLEARALL           410 
#define AR_RESERV_MENU_SETDEFAULT         411 
#define AR_RESERV_MENU_SEARCH             412 
#define AR_RESERV_MENU_NEW_SEARCH         413 
#define AR_RESERV_MENU_NEW_REQUEST        414 
#define AR_RESERV_MENU_SHOW_STAT_HIST     415 
#define AR_RESERV_MENU_HOME               416 
#define AR_RESERV_MENU_HELP               417 
#define AR_RESERV_MENU_ADVANCED_SEARCH    418 
#define AR_RESERV_MENU_LOGOUT             419 
#define AR_RESERV_MENU_SAVED_SEARCH       420 

/* Reserved field ids to identify a shadow form for archive & audit */
#define AR_RESERVE_ARCHIVE_AUDIT_ENTRY_ID    450 
#define AR_RESERVE_ARCHIVE_CREATE_DATE       451 
#define AR_RESERVE_AUDIT_MOD_DATE            452 
#define AR_RESERVE_AUDIT_LAST_CHANGED        453 
#define AR_RESERVE_AUDIT_ACTION              454 
#define AR_RESERVE_AUDIT_USER                455 
#define AR_RESERVE_AUDIT_FIELDS_CHANGED      456 
#define AR_RESERVE_AUDIT_FORM_NAME           457 
#define AR_RESERVE_AUDIT_GUID_FIELD          458 
#define AR_RESERVE_AUDIT_LOG                 459 
/* Reserved fields that are part of Log forms */
#define AR_RESERVE_AUDIT_LOG_KEY1            460 
#define AR_RESERVE_AUDIT_LOG_KEY2            461 
#define AR_RESERVE_AUDIT_LOG_KEY3            462 

#define AR_RESERVE_AUDIT_JOIN_KEY            463 

/* Reserved fields for Application support */
#define ARAPP_RESERV_APPLIC_CATEGORY      AR_CORE_SHORT_DESCRIPTION
#define ARAPP_RESERV_APPLIC_COMMAND       501 
#define ARAPP_RESERV_APPLIC_SCHEMA        502 
#define ARAPP_RESERV_APPLIC_ENTRY_ID      503 
#define ARAPP_RESERV_APPLIC_TAG           504 
#define ARAPP_RESERV_APPLIC_FIELD_1       505 
#define ARAPP_RESERV_APPLIC_FIELD_2       506 
#define ARAPP_RESERV_APPLIC_FIELD_3       507 
#define ARAPP_RESERV_APPLIC_OTHER_SHORT   508 
#define ARAPP_RESERV_APPLIC_OTHER_LONG    509 
                                      /* reserved for Business Time support */
                                      /* Holiday */
#define AR_RESERV_HOLIDAY_LIST            600
#define AR_RESERV_HOLIDAY_LEVEL           601 
                                      /* Workday */
#define AR_RESERV_WORKDAY_LEVEL             619 
#define AR_RESERV_WORKDAY_OPEN_SUN_0        620 
#define AR_RESERV_WORKDAY_OPEN_MON_0        621 
#define AR_RESERV_WORKDAY_OPEN_TUES_0       622 
#define AR_RESERV_WORKDAY_OPEN_WED_0        623 
#define AR_RESERV_WORKDAY_OPEN_THURS_0      624 
#define AR_RESERV_WORKDAY_OPEN_FRI_0        625 
#define AR_RESERV_WORKDAY_OPEN_SAT_0        626 
#define AR_RESERV_WORKDAY_CLOSE_SUN_0       630 
#define AR_RESERV_WORKDAY_CLOSE_MON_0       631 
#define AR_RESERV_WORKDAY_CLOSE_TUES_0      632 
#define AR_RESERV_WORKDAY_CLOSE_WED_0       633 
#define AR_RESERV_WORKDAY_CLOSE_THURS_0     634 
#define AR_RESERV_WORKDAY_CLOSE_FRI_0       635 
#define AR_RESERV_WORKDAY_CLOSE_SAT_0       636 
#define AR_RESERV_WORKDAY_OFFSET_HOURS      637 

#define AR_RESERV_WORKDAY_OPEN_SUN_1        639 
#define AR_RESERV_WORKDAY_OPEN_MON_1        640 
#define AR_RESERV_WORKDAY_OPEN_TUES_1       641 
#define AR_RESERV_WORKDAY_OPEN_WED_1        642 
#define AR_RESERV_WORKDAY_OPEN_THURS_1      643 
#define AR_RESERV_WORKDAY_OPEN_FRI_1        644 
#define AR_RESERV_WORKDAY_OPEN_SAT_1        645 
#define AR_RESERV_WORKDAY_CLOSE_SUN_1       646 
#define AR_RESERV_WORKDAY_CLOSE_MON_1       647 
#define AR_RESERV_WORKDAY_CLOSE_TUES_1      648 
#define AR_RESERV_WORKDAY_CLOSE_WED_1       649 
#define AR_RESERV_WORKDAY_CLOSE_THURS_1     652 
#define AR_RESERV_WORKDAY_CLOSE_FRI_1       653 
#define AR_RESERV_WORKDAY_CLOSE_SAT_1       654 

#define AR_RESERV_WORKDAY_OPEN_SUN_2        655 
#define AR_RESERV_WORKDAY_OPEN_MON_2        656 
#define AR_RESERV_WORKDAY_OPEN_TUES_2       657 
#define AR_RESERV_WORKDAY_OPEN_WED_2        658 
#define AR_RESERV_WORKDAY_OPEN_THURS_2      659 
#define AR_RESERV_WORKDAY_OPEN_FRI_2        660 
#define AR_RESERV_WORKDAY_OPEN_SAT_2        661 
#define AR_RESERV_WORKDAY_CLOSE_SUN_2       662 
#define AR_RESERV_WORKDAY_CLOSE_MON_2       663 
#define AR_RESERV_WORKDAY_CLOSE_TUES_2      664 
#define AR_RESERV_WORKDAY_CLOSE_WED_2       665 
#define AR_RESERV_WORKDAY_CLOSE_THURS_2     666 
#define AR_RESERV_WORKDAY_CLOSE_FRI_2       667 
#define AR_RESERV_WORKDAY_CLOSE_SAT_2       668 

/* Field ID's 670-678, 680-682, 695-699 */
/* Reserved by Business time form.      */
/* REMAINING WORKDAY reserved fields in */
/* the range of 820 - 880               */

/* Reserved fields for Alert support */
#define AR_RESERV_ALERT_FORM              701 
#define AR_RESERV_ALERT_REQUEST           702 
#define AR_RESERV_ALERT_SERVER            703 
#define AR_RESERV_ALERT_MESSAGE           704 
#define AR_RESERV_ALERT_PRIORITY          705 
#define AR_RESERV_ALERT_LIST_QLV          706
#define AR_RESERV_ALERT_SENT_SUCCESSFULLY 707

#define AR_RESERV_ALERT_COLUMN_READ       711 
#define AR_RESERV_ALERT_COLUMN_PRIORITY   712 
#define AR_RESERV_ALERT_COLUMN_SOURCE     713 
#define AR_RESERV_ALERT_COLUMN_CREATEDATE 714 
#define AR_RESERV_ALERT_COLUMN_MESSAGE    715 
#define AR_RESERV_ALERT_COLUMN_REQUEST    716 
#define AR_RESERV_ALERT_COLUMN_FORM       717 
#define AR_RESERV_ALERT_COLUMN_SERVER     718 

/* Reserved fields for Server Group support */
#define AR_RESERV_SG_OPERATION            731 
#define AR_RESERV_SG_SERVER_NAME          732 
#define AR_RESERV_SG_RANK                 733 
#define AR_RESERV_SG_DELINQ_THRESH        734

/* Reserved fields for Object Relationship View Form */
#define AR_RESERV_OBJ_REL_REL_TYPE        751
#define AR_RESERV_OBJ_REL_ACTION_NUM      752
#define AR_RESERV_OBJ_REL_OBJ_TYPE        753
#define AR_RESERV_OBJ_REL_OBJ_NAME        754
#define AR_RESERV_OBJ_REL_OBJ_ID          755
#define AR_RESERV_OBJ_REL_RLTD_OBJ_TYPE   756
#define AR_RESERV_OBJ_REL_RLTD_OBJ_NAME   757
#define AR_RESERV_OBJ_REL_RLTD_OBJ_ID     758
#define AR_RESERV_OBJ_REL_FORM_NAME       759
#define AR_RESERV_OBJ_REL_FORM_ID         760
#define AR_RESERV_OBJ_REL_CATEGORY        768
#define AR_RESERV_OBJ_REL_OVERLAY_GROUP   769

/* Reserved fields for the Server Event Schema */
#define AR_RESERV_SVR_EVENT_TYPE          800 
#define AR_RESERV_SVR_EVENT_CAUSE         801 
#define AR_RESERV_SVR_EVENT_DETAILS_1     802 
#define AR_RESERV_SVR_EVENT_DETAILS_2     803 
#define AR_RESERV_SVR_EVENT_DETAILS_3     804 

/* Reserved fields for Business Time Continued from Above */
#define AR_RESERV_WORKDAY_OPEN_SUN_3        820 
#define AR_RESERV_WORKDAY_OPEN_MON_3        821 
#define AR_RESERV_WORKDAY_OPEN_TUES_3       822 
#define AR_RESERV_WORKDAY_OPEN_WED_3        823 
#define AR_RESERV_WORKDAY_OPEN_THURS_3      824 
#define AR_RESERV_WORKDAY_OPEN_FRI_3        825 
#define AR_RESERV_WORKDAY_OPEN_SAT_3        826 
#define AR_RESERV_WORKDAY_CLOSE_SUN_3       827 
#define AR_RESERV_WORKDAY_CLOSE_MON_3       828 
#define AR_RESERV_WORKDAY_CLOSE_TUES_3      829 
#define AR_RESERV_WORKDAY_CLOSE_WED_3       830 
#define AR_RESERV_WORKDAY_CLOSE_THURS_3     831 
#define AR_RESERV_WORKDAY_CLOSE_FRI_3       832 
#define AR_RESERV_WORKDAY_CLOSE_SAT_3       833 
/* 835 to 840 used for Open and Close texts */
/* 841 to 880 reserved for Business Time */

/* Reserved fields for the Server Statistics Schema */
#define AR_RESERV_SVR_STATS_QUEUE                   900 
#define AR_RESERV_SVR_STATS_BAD_PASSWORD            902
#define AR_RESERV_SVR_STATS_NO_WRITE_TOKEN          903
#define AR_RESERV_SVR_STATS_NO_FULL_TOKEN           904
#define AR_RESERV_SVR_STATS_CURRENT_USERS           905
#define AR_RESERV_SVR_STATS_WRITE_FIXED             906
#define AR_RESERV_SVR_STATS_WRITE_FLOATING          907
#define AR_RESERV_SVR_STATS_WRITE_READ              908
#define AR_RESERV_SVR_STATS_FULL_FIXED              909
#define AR_RESERV_SVR_STATS_FULL_FLOATING           910
#define AR_RESERV_SVR_STATS_FULL_NONE               911
#define AR_RESERV_SVR_STATS_API_REQUESTS            912
#define AR_RESERV_SVR_STATS_API_TIME                913
#define AR_RESERV_SVR_STATS_ENTRY_TIME              914
#define AR_RESERV_SVR_STATS_RESTRUCT_TIME           915
#define AR_RESERV_SVR_STATS_OTHER_TIME              916
#define AR_RESERV_SVR_STATS_CACHE_TIME              917
#define AR_RESERV_SVR_STATS_GET_E_COUNT             918
#define AR_RESERV_SVR_STATS_GET_E_TIME              919
#define AR_RESERV_SVR_STATS_SET_E_COUNT             920
#define AR_RESERV_SVR_STATS_SET_E_TIME              921
#define AR_RESERV_SVR_STATS_CREATE_E_COUNT          922
#define AR_RESERV_SVR_STATS_CREATE_E_TIME           923
#define AR_RESERV_SVR_STATS_DELETE_E_COUNT          924
#define AR_RESERV_SVR_STATS_DELETE_E_TIME           925
#define AR_RESERV_SVR_STATS_MERGE_E_COUNT           926
#define AR_RESERV_SVR_STATS_MERGE_E_TIME            927
#define AR_RESERV_SVR_STATS_GETLIST_E_COUNT         928
#define AR_RESERV_SVR_STATS_GETLIST_E_TIME          929
#define AR_RESERV_SVR_STATS_E_STATS_COUNT           930
#define AR_RESERV_SVR_STATS_E_STATS_TIME            931
#define AR_RESERV_SVR_STATS_FILTER_PASSED           932
#define AR_RESERV_SVR_STATS_FILTER_FAILED           933
#define AR_RESERV_SVR_STATS_FILTER_DISABLE          934
#define AR_RESERV_SVR_STATS_FILTER_NOTIFY           935
#define AR_RESERV_SVR_STATS_FILTER_MESSAGE          936
#define AR_RESERV_SVR_STATS_FILTER_LOG              937
#define AR_RESERV_SVR_STATS_FILTER_FIELDS           938
#define AR_RESERV_SVR_STATS_FILTER_PROCESS          939
#define AR_RESERV_SVR_STATS_FILTER_TIME             940
#define AR_RESERV_SVR_STATS_ESCL_PASSED             941
#define AR_RESERV_SVR_STATS_ESCL_FAILED             942
#define AR_RESERV_SVR_STATS_ESCL_DISABLE            943
#define AR_RESERV_SVR_STATS_ESCL_NOTIFY             944
#define AR_RESERV_SVR_STATS_ESCL_LOG                945
#define AR_RESERV_SVR_STATS_ESCL_FIELDS             946
#define AR_RESERV_SVR_STATS_ESCL_PROCESS            947
#define AR_RESERV_SVR_STATS_ESCL_TIME               948
#define AR_RESERV_SVR_STATS_TIMES_BLOCKED           949
#define AR_RESERV_SVR_STATS_NUMBER_BLOCKED          950
#define AR_RESERV_SVR_STATS_CPU                     951
#define AR_RESERV_SVR_STATS_SQL_DB_COUNT            952
#define AR_RESERV_SVR_STATS_SQL_DB_TIME             953
#define AR_RESERV_SVR_STATS_FTS_SRCH_COUNT          954
#define AR_RESERV_SVR_STATS_FTS_SRCH_TIME           955
#define AR_RESERV_SVR_STATS_IDLE_TIME               957
#define AR_RESERV_SVR_STATS_NET_RESP_TIME           958
#define AR_RESERV_SVR_STATS_FILTER_FIELDP           959
#define AR_RESERV_SVR_STATS_ESCL_FIELDP             960
#define AR_RESERV_SVR_STATS_FILTER_SQL              961
#define AR_RESERV_SVR_STATS_ESCL_SQL                962
#define AR_RESERV_SVR_STATS_NUM_THREADS             963
#define AR_RESERV_SVR_STATS_FILTER_GOTO_ACTION      964
#define AR_RESERV_SVR_STATS_FILTER_CALL_GUIDE       965
#define AR_RESERV_SVR_STATS_FILTER_EXIT_GUIDE       966
#define AR_RESERV_SVR_STATS_FILTER_GOTO_GUIDE_LB    967
#define AR_RESERV_SVR_STATS_FILTER_FIELDS_SQL       968
#define AR_RESERV_SVR_STATS_FILTER_FIELDS_PROCESS   969
#define AR_RESERV_SVR_STATS_FILTER_FIELDS_FLTAPI    970
#define AR_RESERV_SVR_STATS_ESCL_FIELDS_SQL         971
#define AR_RESERV_SVR_STATS_ESCL_FIELDS_PROCESS     972
#define AR_RESERV_SVR_STATS_ESCL_FIELDS_FLTAPI      973
#define AR_RESERV_SVR_STATS_SERVER_NAME             974
#define AR_RESERV_SVR_STATS_SERVER_TCP_PORT         975
#define AR_RESERV_SVR_STATS_RESTRICTED_READ         976

/* Reserved fields for Application Statistics Configuration Form */

#define AR_RESERV_APP_STATS_CONFIG_LOGGING_INTERVAL 1101 
#define AR_RESERV_APP_STATS_CONFIG_LOGGING_TYPE     1102 
#define AR_RESERV_APP_STATS_CONFIG_NAME             1103 
#define AR_RESERV_APP_STATS_CONFIG_LOGGING_STATUS   1104 
#define AR_RESERV_APP_STATS_CONFIG_WINDOWS_VUI      1105 
#define AR_RESERV_APP_STATS_CONFIG_WEB_VUI          1106 


/* Reserved fields for Application Statistics Form */
#define AR_RESERV_APP_STATS_LOGGING_TYPE            1102 
#define AR_RESERV_APP_STATS_NAME                    1103 
#define AR_RESERV_APP_STATS_FIXED_LIC               1251 
#define AR_RESERV_APP_STATS_FLOATING_LIC            1252 
#define AR_RESERV_APP_STATS_ESCL_PF                 1254 
#define AR_RESERV_APP_STATS_ESCL_DIRECT_SQL         1255 
#define AR_RESERV_APP_STATS_ESCL_PROC_TIME          1256 
#define AR_RESERV_APP_STATS_SQL_COMMANDS            1257 
#define AR_RESERV_APP_STATS_SQL_PROC_TIME           1258 
#define AR_RESERV_APP_STATS_WINDOWS_VUI             1260 
#define AR_RESERV_APP_STATS_WEB_VUI                 1261 
#define AR_RESERV_APP_STATS_PAGEHOLDER              1262 
#define AR_RESERV_APP_STATS_PAGEFIELD_ENTRY         1263 
#define AR_RESERV_APP_STATS_PAGEFIELD_FILTER        1264 
#define AR_RESERV_APP_STATS_PAGEFIELD_ESCALATION    1265 
#define AR_RESERV_APP_STATS_PAGEFIELD_LICENSES      1266 
#define AR_RESERV_APP_STATS_FILTER_EXECS            1267 
#define AR_RESERV_APP_STATS_FILTER_SKIPPED          1268 
#define AR_RESERV_APP_STATS_DISABLED_FILTERS        1269 
#define AR_RESERV_APP_STATS_FILTER_NOTIFY           1270 
#define AR_RESERV_APP_STATS_FILTER_MSG              1272 
#define AR_RESERV_APP_STATS_FILTER_LOG              1271 
#define AR_RESERV_APP_STATS_FILTER_SF               1273 
#define AR_RESERV_APP_STATS_FILTER_SF_SQL           1274 
#define AR_RESERV_APP_STATS_FILTER_SF_PROC          1275 
#define AR_RESERV_APP_STATS_FILTER_SF_FLTAPI        1276 
#define AR_RESERV_APP_STATS_FILTER_RUN_PROC         1277 
#define AR_RESERV_APP_STATS_FILTER_PF               1278 
#define AR_RESERV_APP_STATS_FILTER_SQL              1279 
#define AR_RESERV_APP_STATS_FILTER_GOTO             1280 
#define AR_RESERV_APP_STATS_FILTER_CALL_GUIDE       1281 
#define AR_RESERV_APP_STATS_FILTER_EXIT_GUIDE       1282 
#define AR_RESERV_APP_STATS_FILTER_GOTO_GUIDE       1283 
#define AR_RESERV_APP_STATS_FILTER_PROC_TIME        1284 
#define AR_RESERV_APP_STATS_ESCL_EXEC               1285 
#define AR_RESERV_APP_STATS_ESCL_SKIPPED            1286 
#define AR_RESERV_APP_STATS_ESCL_DISABLED           1287 
#define AR_RESERV_APP_STATS_ESCL_NOTIFY             1288 
#define AR_RESERV_APP_STATS_ESCL_LOG                1289 
#define AR_RESERV_APP_STATS_ESCL_SF                 1290 
#define AR_RESERV_APP_STATS_ESCL_SF_SQL             1291 
#define AR_RESERV_APP_STATS_ESCL_SF_PROC            1292 
#define AR_RESERV_APP_STATS_ESCL_SF_FLTAPI          1293 
#define AR_RESERV_APP_STATS_ESCL_RUN_PROC           1294 
#define AR_RESERV_APP_STATS_FRM_GE                  1295 
#define AR_RESERV_APP_STATS_FRM_SE                  1296 
#define AR_RESERV_APP_STATS_FRM_GLE                 1297 
#define AR_RESERV_APP_STATS_FRM_CR_ENTRY            1298 
#define AR_RESERV_APP_STATS_FRM_DEL_ENTRY           1299 
#define AR_RESERV_APP_STATS_FRM_MERGE_ENTRY         1300 
#define AR_RESERV_APP_STATS_FRM_ENTRY_API_CALLS     1301 
#define AR_RESERV_APP_STATS_FRM_GLE_TIME            1302 
#define AR_RESERV_APP_STATS_FRM_GE_TIME             1303 
#define AR_RESERV_APP_STATS_FRM_SE_TIME             1304 
#define AR_RESERV_APP_STATS_FRM_CR_ENTRY_TIME       1305 
#define AR_RESERV_APP_STATS_FRM_MERGE_ENTRY_TIME    1306 
#define AR_RESERV_APP_STATS_FRM_DEL_ENTRY_TIME      1307 
#define AR_RESERV_APP_STATS_SERVER_START_TIME       1310 
#define AR_RESERV_APP_STATS_SERVER_NAME              974 
#define AR_RESERV_APP_STATS_SERVER_TCP_PORT          975 
#define AR_RESERV_APP_STATS_FLOATING_LIC_DENIED     1313 

/* Reserved fields for API/SQL performance statistics form */
#define AR_RESERV_STATS_APISQL_START         1400
#define AR_RESERV_STATS_APISQL_ELAPSED       1401
#define AR_RESERV_STATS_APISQL_USER          1402
#define AR_RESERV_STATS_APISQL_API_NAME      1403
#define AR_RESERV_STATS_APISQL_RPC_ID        1404
#define AR_RESERV_STATS_APISQL_THREAD_ID     1405
#define AR_RESERV_STATS_APISQL_CLIENT_TYPE   1406
#define AR_RESERV_STATS_APISQL_API_DATA      1407
#define AR_RESERV_STATS_APISQL_SQL_DATA      1408
#define AR_RESERV_STATS_APISQL_RESULT        1409
#define AR_RESERV_STATS_APISQL_DATA_SIZE     1000  /* Size of the short data field */
#define AR_RESERV_STATS_APISQL_EXT_DATA      1410  /* Extended data (unlimited CLOB) only fill in if needed */
#define AR_RESERV_STATS_APISQL_QUE_DELAY     1411  /* Extended data (unlimited CLOB) only fill in if needed */

/* Reserved fields for form actions and results */
#define AR_RESERV_FORM_ACTION_SUBMIT         1001 
#define AR_RESERV_FORM_ACTION_QUERY          1002 
#define AR_RESERV_FORM_ACTION_MODIFY         1003 
#define AR_RESERV_FORM_ACTION_MODIFYALL      1004 
#define AR_RESERV_FORM_ACTION_QUERYBAR       1005 
#define AR_RESERV_FORM_ACTION_CLEAR          1006 
#define AR_RESERV_FORM_ACTION_SETDEFAULT     1007 
#define AR_RESERV_FORM_ACTION_HELP           1008 
#define AR_RESERV_FORM_ACTION_NEWSEARCH      1009 
#define AR_RESERV_FORM_ACTION_NEWREQUEST     1010 
#define AR_RESERV_FORM_ACTION_SHOW_STATHST   1011 
#define AR_RESERV_FORM_ACTION_HOMEPAGE       1012 
#define AR_RESERV_FORM_ACTION_SAVEDSEARCHES  1013 
#define AR_RESERV_FORM_ACTION_QUICKREPORT    1014 

#define AR_RESERV_FORM_RESULTS_LIST          1020 

/* Reserved fields for Currency forms */
#define AR_RESERV_CURRENCY_DATE              1501 
#define AR_RESERV_CURRENCY_FROM              1502 
#define AR_RESERV_CURRENCY_TO                1503 
#define AR_RESERV_CURRENCY_RATIO             1504 

#define AR_RESERV_CURRENCY_CODE              1521 
#define AR_RESERV_CURRENCY_PRECISION         1522 
#define AR_RESERV_CURRENCY_LOCALE            1523 
#define AR_RESERV_CURRENCY_LABEL             1524 
#define AR_RESERV_CURRENCY_ACTIVE            1525 

/* Reserved fields for Home Page */
#define AR_RESERV_HOMEPAGE_FIELD             1575 
#define AR_RESERV_HOMEPAGE_SUBSET            1576 

/* Reserved fields for Auto-GUID generation */
#define AR_RESERV_AUTO_GUID                  1600 
#define AR_RESERV_AUTO_GUID_MIN              1600 
#define AR_RESERV_AUTO_GUID_MAX              1699 

/* Reserved fields for Role Mapping Schema */
#define AR_RESERV_ROLE_MAPPING_APPLICATION   1700 
#define AR_RESERV_ROLE_MAPPING_ROLE_NAME     1701 
#define AR_RESERV_ROLE_MAPPING_ROLE_ID       1702 

/* Reserved fields for Application States */
/* These fields will be treated as group fields by the server */
#define AR_RESERV_APP_STATE_MIN              2000 
#define AR_RESERV_APP_STATE_MAX              2199 

#define AR_RESERV_APP_STATE_ADMIN_ONLY       2000 
#define AR_RESERV_APP_STATE_TEST             2001 
#define AR_RESERV_APP_STATE_PRODUCTION       2002 

/* Reserved fields for Application States, not treated as group fields */
#define AR_RESERV_APP_STATE_APPLICATION      2200 
#define AR_RESERV_APP_STATE_STATE            2201 

/* Reserved fields for the Application License Form  */
#define AR_RESERV_APP_LIC_APPLICATION_TYPE   2210
#define AR_RESERV_APP_LIC_LICENSE_TYPE       2211
#define AR_RESERV_APP_LIC_COUNT_LICENSE      2212
#define AR_RESERV_APP_LIC_TIMESTAMP_TYPE     2213
#define AR_RESERV_APP_LIC_LICLIMIT_TYPE      2214

/* License form for the user */
#define AR_RESERV_APP_LIC_USER_NAME          2216
#define AR_RESERV_APP_LIC_OPERATION_TYPE     2217
#define AR_RESERV_APP_USER_APPLICATION_TYPE  2218
#define AR_RESERV_APP_LIC_TYPE_LICENSE       2219
#define AR_RESERV_APP_LIC_TOTAL_LICENSE      2220
#define AR_RESERV_APP_LIC_TIMESTAMP_LICENSE  2221
#define AR_RESERV_APP_LIC_POOL_NAME          2222  

/* Fields for the current license */
#define AR_RESERV_CURRENT_LIC_USER_NAME      2991
#define AR_RESERV_CURRENT_APPLICATION_TYPE   2994
#define AR_RESERV_CURRENT_TYPE_LICENSE       2995
#define AR_RESERV_CURRENT_SERVER_NAME        2996
#define AR_RESERV_CURRENT_LIC_TIMESTAMP      2997
#define AR_RESERV_CURRENT_LIC_GROUP_ID       2992
#define AR_RESERV_CURRENT_LIC_SERVERGR       2998

/* Form for the user snapshot */
#define AR_RESERV_SNAPSHOT_CURR_OR_REQD      2240          
#define AR_RESERV_SNAPSHOT_APPLICATION       2241
#define AR_RESERV_SNAPSHOT_LICENSETYPE       2242
#define AR_RESERV_SNAPSHOT_USER              2244          
#define AR_RESERV_SNAPSHOT_USEREMAIL         2243
#define AR_RESERV_SNAPSHOT_CONNECTTIME       2245
#define AR_RESERV_SNAPSHOT_DEFAULTNOTIFY     2246          
#define AR_RESERV_SNAPSHOT_FTSLIC            2247
#define AR_RESERV_SNAPSHOT_FTSWRITELIC       2248
#define AR_RESERV_SNAPSHOT_LASTACCESS        2249          
#define AR_RESERV_SNAPSHOT_WRITELIC          2250
#define AR_RESERV_SNAPSHOT_WRITELICPOOL      2251




/* Reserved fields for Recurrence Times 2300 - 2400 */

#define AR_RESERV_REC_TAG                    2300 
#define AR_RESERV_REC_TYPE                   2301 
/* yearly fields */
#define AR_RESERV_REC_YEARLY_BY_DOM          2302   /* every */
#define AR_RESERV_REC_YEARLY_DOM_MOY         2303 
#define AR_RESERV_REC_YEARLY_DOM_DOM         2304 
#define AR_RESERV_REC_YEARLY_BY_DOW          2305   /* the */
#define AR_RESERV_REC_YEARLY_DOW_WOM         2306 
#define AR_RESERV_REC_YEARLY_DOW_DOW         2307 
#define AR_RESERV_REC_YEARLY_DOW_MOY         2308 
/* monthly fields */
#define AR_RESERV_REC_MONTHLY_BY_DOM         2309 
#define AR_RESERV_REC_MONTHLY_DOM_DOM        2310 
#define AR_RESERV_REC_MONTHLY_DOM_FREQ       2311 
#define AR_RESERV_REC_MONTHLY_BY_DOW         2312 
#define AR_RESERV_REC_MONTHLY_DOW_WOM        2313 
#define AR_RESERV_REC_MONTHLY_DOW_DOW        2314 
#define AR_RESERV_REC_MONTHLY_DOW_FREQ       2315 
/* Weekly */
#define AR_RESERV_REC_WEEKLY_FREQ            2316 
#define AR_RESERV_REC_WEEKLY_SUNDAY          2317 
#define AR_RESERV_REC_WEEKLY_MONDAY          2318 
#define AR_RESERV_REC_WEEKLY_TUESDAY         2319 
#define AR_RESERV_REC_WEEKLY_WEDNESDAY       2320 
#define AR_RESERV_REC_WEEKLY_THURSDAY        2321 
#define AR_RESERV_REC_WEEKLY_FRIDAY          2322 
#define AR_RESERV_REC_WEEKLY_SATURDAY        2323 
/* Daily */
#define AR_RESERV_REC_DAILY_FREQ             2324 
/* Actual Dates */
#define AR_RESERV_REC_DATE_LIST              2325 
/* Types */
#define AR_RESERV_REC_TYPE_DETAIL            2326 
#define AR_RESERV_REC_YEARLY_TYPE            2327 
#define AR_RESERV_REC_MONTHLY_TYPE           2328 
#define AR_RESERV_REC_WEEKLY_TYPE            2329 
#define AR_RESERV_REC_DAILY_TYPE             2330 
#define AR_RESERV_REC_DATES_TYPE             2331 
/* Text */
#define AR_RESERV_REC_TEXT_OF                2332 
#define AR_RESERV_REC_TEXT_DAY_OF_EVERY      2333 
#define AR_RESERV_REC_TEXT_THE_OF_EVERY      2334 
#define AR_RESERV_REC_TEXT_DAY_MONTHS        2335 
#define AR_RESERV_REC_TEXT_THE_MONTHS        2336 
#define AR_RESERV_REC_TEXT_RECUR_EVERY       2337 
#define AR_RESERV_REC_TEXT_WEEKS_ON          2338 
#define AR_RESERV_REC_TEXT_EVERY             2339 
#define AR_RESERV_REC_TEXT_DAYS              2340 
#define AR_RESERV_REC_MONTHLY_LASTDOM        2341 

/* Reserved fields for Business Time Activity Form 2400 - 2499*/
/* NOTE: These fields below are only the data fields. There   */
/* are additional fields in this range that are hidden and    */
/* trim fields, that are not listed below.                    */
#define AR_RESERV_BUSTIME_INTERNAL_ID        2400 
#define AR_RESERV_BUSTIME_ACTIVITY_ENABLE    2401 
#define AR_RESERV_BUSTIME_LEVEL              2402 
#define AR_RESERV_BUSTIME_AVAILABILITY       2403 
/* 2404 to 2418 are used by workflow on this form */
#define AR_RESERV_BUSTIME_START_DATE         2418 
#define AR_RESERV_BUSTIME_END_DATE           2419 
#define AR_RESERV_BUSTIME_START_TIME         2422 
#define AR_RESERV_BUSTIME_END_TIME           2423 
#define AR_RESERV_BUSTIME_RECURRENCE_FLAG    2425 
#define AR_RESERV_BUSTIME_NONCONFLICT_ACT    2430 
#define AR_RESERV_BUSTIME_END_SEARCH_DATE    2436 
#define AR_RESERV_BUSTIME_EARLY_START_TIME   2437 
#define AR_RESERV_BUSTIME_DURATION           2438 
#define AR_RESERV_BUSTIME_LATE_END_TIME      2439 
#define AR_RESERV_BUSTIME_CREATEASDESCRIBED  2440 
#define AR_RESERV_BUSTIME_CREATENEXTFREE     2441 
#define AR_RESERV_BUSTIME_FINDNEXTFREE       2442 
#define AR_RESERV_BUSTIME_PUBLISH            2443 
#define AR_RESERV_BUSTIME_REMOVE             2444 
#define AR_RESERV_BUSTIME_DRAFT              2445 
#define AR_RESERV_BUSTIME_CATEGORY           2449 
#define AR_RESERV_BUSTIME_START_DATETIME     2465 
#define AR_RESERV_BUSTIME_END_DATETIME       2466 
#define AR_RESERV_BUSTIME_TZ_OFFSET          2480 
#define AR_RESERV_BUSTIME_END_OF_DAY         2481 
#define AR_RESERV_BUSTIME_TZ_MENU            2482 

/* Reserved fields for Business Entity Activity Association Form 2500 - 2550 */
#define AR_RESERV_BUSASSOCIATION_IDENTIFIER       2500 
#define AR_RESERV_BUSASSOCIATION_SCHEDULENAME     2501 
#define AR_RESERV_BUSASSOCIATION_ENTITY_OWNERID   2503 
/*2506, 2507 used as hidden fields*/

/* Reserved fields for Business Activity Association Join form 2550 2600 */
#define AR_RESERV_BUSASSOCJOIN_ACTIVITYID    2550 
#define AR_RESERV_BUSASSOCJOIN_ASSOCID       2551 
#define AR_RESERV_BUSASSOCJOIN_ASSOCDESC     2552 
#define AR_RESERV_BUSASSOCJOIN_ASSOCTITLE    2553 
#define AR_RESERV_BUSASSOCJOIN_ASSIGNEEGRP   2554 

/* Reserved fields for Shared Entity Form from 2601 to 2699 */
#define AR_RESERV_BUSSCHDSHRENTITY_TYPE           2601 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE1     2602 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE2     2603 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE3     2604 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE4     2605 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE5     2606 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE6     2607 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE7     2608 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE8     2609 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE9     2610 
#define AR_RESERV_BUSSCHDSHRENTITY_ATTRIBUTE10    2611 
#define AR_RESERV_BUSSCHDSHRENTITY_DELETED        2612 
#define AR_RESERV_BUSSCHDSHRENTITY_POID           2613 
#define AR_RESERV_BUSSCHDSHRENTITY_TYPEID         2614 
#define AR_RESERV_BUSSCHDSHRENTITY_DESC           2615 
#define AR_RESERV_BUSSCHDSHRENTITY_CLASSID        2617 
#define AR_RESERV_BUSSCHDSHRENTITY_DATASETID      2618 
#define AR_RESERV_BUSSCHDSHRENTITY_APPID          2619 

/* Reserved fields for Licensing related items from 2700 to 2750 */
/* License form */
#define AR_RESERV_LICENSE_FORM_FEATURE            2700
#define AR_RESERV_LICENSE_FORM_QUALIFIER          2701
#define AR_RESERV_LICENSE_FORM_NUMBER             2702
#define AR_RESERV_LICENSE_FORM_KEY                2703
#define AR_RESERV_LICENSE_FORM_EXPIRE             2704

/* AR System Tag form */
#define AR_RESERV_ARS_TAG_FORM_KEY                2730
#define AR_RESERV_ARS_TAG_FORM_LICENSE            2731
#define AR_RESERV_ARS_TAG_FORM_STRING             2732

/* Reserved fields for Version Control related items from 2800 to 2899 */
/* AR System Version Control: Object Reservation form */
#define AR_RESERV_VERCNTL_RESERVATION_OBJ_TYPE          2800
#define AR_RESERV_VERCNTL_RESERVATION_OBJ_NAME          2801
#define AR_RESERV_VERCNTL_RESERVATION_OBJ_SUBTYPE       2802
#define AR_RESERV_VERCNTL_RESERVATION_TASKID            2803
#define AR_RESERV_VERCNTL_RESERVATION_OBJ_RESOLVEDNAME  2804
#define AR_RESERV_VERCNTL_RESERVATION_OVERLAYGROUP      2805

/* AR System Version Control: Task form */
#define AR_RESERV_VERCNTL_TASK_COMMENT            2810
/* AR System Version Control: Object Modification Log form */
#define AR_RESERV_VERCNTL_OBJMODLOG_OBJ_TYPE      2820
#define AR_RESERV_VERCNTL_OBJMODLOG_OBJ_NAME      2821
#define AR_RESERV_VERCNTL_OBJMODLOG_OPERATION     2823
#define AR_RESERV_VERCNTL_OBJMODLOG_TAKS_ID       2825
#define AR_RESERV_VERCNTL_OBJMODLOG_LABEL         2826
#define AR_RESERV_VERCNTL_OBJMODLOG_ATTCH_POOL    2827
#define AR_RESERV_VERCNTL_OBJMODLOG_ATTCH_DEF     2828
#define AR_RESERV_VERCNTL_OBJMODLOG_COMMENTS      2829
#define AR_RESERV_VERCNTL_OBJMODLOG_OBJ_OLDNAME   2830
#define AR_RESERV_VERCNTL_OBJMODLOG_INSTANCE      2831
#define AR_RESERV_VERCNTL_OBJMODLOG_API_TARGET    2832
#define AR_RESERV_VERCNTL_OBJMODLOG_API_ID        2833
#define AR_RESERV_VERCNTL_OBJMODLOG_VERSION_ID    2834
#define AR_RESERV_VERCNTL_OBJMODLOG_LATEST_VER    2835
#define AR_RESERV_VERCNTL_OBJMODLOG_RESOLVEDNAME  2836
#define AR_RESERV_VERCNTL_OBJMODLOG_OVERLAYGROUP  2837

/* AR System Version Control: Label form */
#define AR_RESERV_VERCNTL_LABEL_DESC              2861
/* AR System Version Control: Labeled Object form */
#define AR_RESERV_VERCNTL_LABELEDOBJ_LABEL_ID     2870
#define AR_RESERV_VERCNTL_LABELEDOBJ_VERSION_ID   2871

/* Reserved fields for multi-form search form - 3000 to 3099 */
#define AR_RESERV_MFSEARCH_FORM_LIST              3000
#define AR_RESERV_MFSEARCH_TERM_MUST_HAVE         3001
#define AR_RESERV_MFSEARCH_TERM_MAY_HAVE          3002
#define AR_RESERV_MFSEARCH_TERM_MUST_NOT_HAVE     3003
#define AR_RESERV_MFSEARCH_SEARCH_RESULT_OPTION   3008
#define AR_RESERV_MFSEARCH_FILTER_STRING          3009
#define AR_RESERV_MFSEARCH_RESULT_FORM_NAME       3010
#define AR_RESERV_MFSEARCH_RESULT_ENTRY_ID        3011
#define AR_RESERV_MFSEARCH_RESULT_TITLE           3012
#define AR_RESERV_MFSEARCH_RESULT_EXCERPT         3013
#define AR_RESERV_MFSEARCH_RESULT_WEIGHT          3014
#define AR_RESERV_MFSEARCH_RESULT_DATE_CREATED    3015
#define AR_RESERV_MFSEARCH_RESULT_DATE_MODIFIED   3016
/* These are optional result fields */
#define AR_RESERV_MFSEARCH_RESULT_FIELD1          3020
#define AR_RESERV_MFSEARCH_RESULT_FIELD2          3021
#define AR_RESERV_MFSEARCH_RESULT_FIELD3          3022
#define AR_RESERV_MFSEARCH_RESULT_FIELD4          3023
#define AR_RESERV_MFSEARCH_RESULT_FIELD5          3024
#define AR_RESERV_MFSEARCH_RESULT_FIELD6          3025
#define AR_RESERV_MFSEARCH_RESULT_FIELD7          3026
#define AR_RESERV_MFSEARCH_RESULT_FIELD8          3027
#define AR_RESERV_MFSEARCH_RESULT_FIELD9          3028
#define AR_RESERV_MFSEARCH_RESULT_FIELD10         3029
#define AR_RESERV_MFSEARCH_RESULT_FIELD11         3030
#define AR_RESERV_MFSEARCH_RESULT_FIELD12         3031
#define AR_RESERV_MFSEARCH_RESULT_FIELD13         3032
#define AR_RESERV_MFSEARCH_RESULT_FIELD14         3033
#define AR_RESERV_MFSEARCH_RESULT_FIELD15         3034
#define AR_RESERV_MFSEARCH_RESULT_FIELD16         3035
#define AR_RESERV_MFSEARCH_RESULT_FIELD17         3036
#define AR_RESERV_MFSEARCH_RESULT_FIELD18         3037
#define AR_RESERV_MFSEARCH_RESULT_FIELD19         3038
#define AR_RESERV_MFSEARCH_RESULT_FIELD20         3039
/* trim fields */
#define AR_RESERV_MFSEARCH_NAME_TRIM_FIELD        3090

/* Reserved fields for multi-form search implementation form - 3100 to 3199 */

/* Reserved fields for form-based configuration - 3200 to 3299 */

/* Reserved fields for vendor forms from 4000 to 4099 */
#define AR_RESERV_VENDOR_LDAP_BASEDN              4000 
#define AR_RESERV_VENDOR_LDAP_CMP_TIME            4001 

/* Reserved fields for field changed fields in Audit forms 5000 to 5999 */
#define AR_RESERV_AUDIT_FIELD_CHANGED_MIN         5000 
#define AR_RESERV_AUDIT_FIELD_CHANGED_MAX         5999 


                 /* reserved field ids used to identify various SYSTEM LOG schemas */
#define AR_RESERV_LOG_FORM_FIELDS_MIN             6001 
#define AR_RESERV_LOG_FORM_FIELDS_MAX             6999

               /* Common reserved fields for Log Forms */
#define AR_RESERV_LOG_FORM_LG_TITLE               6001
#define AR_RESERV_LOG_FORM_LG_BOX10               6002
#define AR_RESERV_LOG_FORM_LG_BOX11               6003
#define AR_RESERV_LOG_FORM_LG_TAG                 6004
#define AR_RESERV_LOG_FORM_LG_RPC_ID              6005
#define AR_RESERV_LOG_FORM_LG_RPC_Q               6006
#define AR_RESERV_LOG_FORM_LG_CLNT_RPC            6007
#define AR_RESERV_LOG_FORM_LG_USR                 6008
#define AR_RESERV_LOG_FORM_LG_TIME                6009
#define AR_RESERV_LOG_FORM_LG_MSG                 6010
#define AR_RESERV_LOG_FORM_LG_THRD_ID             6011
#define AR_RESERV_LOG_FORM_LG_SVR_NAME            6022
#define AR_RESERV_LOG_FORM_LG_OVERLAY_GRP         6023

               /* reserved fields for SQL Log Form */
#define AR_RESERV_LOG_FORM_SQL_LG_LABEL           6012

               /* reserved fields for Alert Log Form */
#define AR_RESERV_LOG_FORM_ALRT_LG_LABEL          6013

               /* reserved fields for API Log Form */
#define AR_RESERV_LOG_FORM_API_LG_LABEL           6014

               /* reserved fields for Escalation Log Form */
#define AR_RESERV_LOG_FORM_ESC_LG_LABEL           6015

               /* reserved fields for Filter Log Form */
#define AR_RESERV_LOG_FORM_FILT_LG_LABEL          6016

               /* reserved fields for FullText Index Log Form */
#define AR_RESERV_LOG_FORM_FTS_LG_LABEL           6017

               /* reserved fields for Server Group Log Form */
#define AR_RESERV_LOG_FORM_SVR_GRP_LG_LABEL       6018

               /* reserved fields for Thread Log Form */
#define AR_RESERV_LOG_FORM_THRD_LG_LABEL          6019

               /* reserved fields for User Log Form */
#define AR_RESERV_LOG_FORM_USR_LG_LABEL           6020

               /* reserved fields for Common Log Form */
#define AR_RESERV_LOG_FORM_COMMON_LG_LABEL        6021


/* reserved field ids used to identify SHARE:Application_Interface schema */
#define AR_RESERV_SHARE_APP_INTERFACE_FORM_FIELDS_MIN 7000 
#define AR_RESERV_SHARE_APP_INTERFACE_FORM_FIELDS_MAX 7099

/* Common reserved fields for SHARE:Application_Interface Forms */
#define AR_RESERV_SHR_APP_INTFCE_CONSUMING_APP        7000
#define AR_RESERV_SHR_APP_INTFCE_PROVIDING_APP        7001
#define AR_RESERV_SHR_APP_INTFCE_MAJOR_REL            7003
#define AR_RESERV_SHR_APP_INTFCE_MINOR_REL            7004
#define AR_RESERV_SHR_APP_INTFCE_MAINT_REL            7005
#define AR_RESERV_SHR_APP_INTFCE_PATCH_NUM            7006
#define AR_RESERV_SHR_APP_INTFCE_ATTACH_POOL          7007
#define AR_RESERV_SHR_APP_INTFCE_INSTALLED            7008
#define AR_RESERV_SHR_APP_INTFCE_FILENAME             7009
#define AR_RESERV_SHR_APP_INTFCE_PG_HOLDER            7010
#define AR_RESERV_SHR_APP_INTFCE_PAGE                 7011
#define AR_RESERV_SHR_APP_INTFCE_CONSUMING_APP_ID     7012
#define AR_RESERV_SHR_APP_INTFCE_PROVIDING_APP_ID     7013
#define AR_RESERV_SHR_APP_INTFCE_SEQUENCE             7014
#define AR_RESERV_SHR_APP_INTFCE_INF_DESC             7015
#define AR_RESERV_SHR_APP_INTFCE_CONS_LOCALE_LANG     7016
#define AR_RESERV_SHR_APP_INTFCE_CONS_LOCALE_COUNTRY  7017
#define AR_RESERV_SHR_APP_INTFCE_INSTALLATION_ACTION  7018
#define AR_RESERV_SHR_APP_INTFCE_INSTALLATION_PARAMS  7019
#define AR_RESERV_SHR_APP_INTFCE_INSTALLATION_OPTIONS 7020

/* fields reserved for AR BMC Atrium Orchestrator Configuration form */
#define AR_RESERV_BAO_GRIDNAME                        8000
#define AR_RESERV_BAO_LOCATION                        8001
#define AR_RESERV_BAO_CONFIG_NAME                     AR_CORE_SHORT_DESCRIPTION
#define AR_RESERV_BAO_DESCRIPTION                     8002
#define AR_RESERV_BAO_USERNAME                        8004
#define AR_RESERV_BAO_PAGE_HOLDER                     8005
#define AR_RESERV_BAO_WEBSERVICE_TAB                  8006
#define AR_RESERV_BAO_ADMINISTRATION_TAB              8007
#define AR_RESERV_BAO_LINE1                           8008
#define AR_RESERV_BAO_EXAMPLE                         8009
#define AR_RESERV_BAO_LINE2                           8010
#define AR_RESERV_BAO_WS_TEXT                         8011
#define AR_RESERV_BAO_TITLE                           8012
/* Reserving fields till 8030 for this form */

/* Reserving fields for Registry form */
#define AR_RESERV_REG_GUID                      AR_RESERV_GUID
#define AR_RESERV_REG_PANEL_HOLDER              8030
#define AR_RESERV_REG_REGISTRY_PANEL            8031
#define AR_RESERV_REG_ADMIN_PANEL               8032
#define AR_RESERV_REG_BUSINESS_NAME             8033
#define AR_RESERV_REG_APPLICATION_NAME          8034
#define AR_RESERV_REG_WSDL_WEBSERVER_ADDRESS    8035
#define AR_RESERV_REG_WSDL_MIDTIER_LOCATION     8036
#define AR_RESERV_REG_WEB_SERVICE               8037
#define AR_RESERV_REG_WEB_SERVICE_VERSION       8038
#define AR_RESERV_REG_EP_WEBSERVER_ADDRESS      8039
#define AR_RESERV_REG_EP_MIDTIER_LOCATION       8040
#define AR_RESERV_REG_STATUS                    8041
#define AR_RESERV_REG_RECOMMEND                 8042
/* 8043 to 8049 taken up by hidden fields */
#define AR_RESERV_REG_EP_ARSERVER               8050
/* 8051 to 8058 taken up by hidden fields */
#define AR_RESERV_REG_WSDL_URL                  8059
#define AR_RESERV_REG_EP_URL                    8061
#define AR_RESERV_REG_PUBLISH                   8062
#define AR_RESERV_REG_WSDL_ARSERVER             8063
#define AR_RESERV_REG_TITLE                     8064

/* Reserving fields for Registry Pending form */
#define AR_RESERV_REG_PENDING_FORM_ID           8070

/* Reserving fields for Category form */
#define AR_RESERV_CAT_CATEGORY_NAME             8073
#define AR_RESERV_CAT_CATEGORY_VALUE            8074

#define AR_RESERV_REG_QUERY_CATEGORY_LIST       8086

/* Not a mandatory field but still kept it for consistency */
/* with Constants.java file */
#define AR_RESERV_REG_INTERFACE_VERSION         8088

/* Reserving fields for WS Security X509 form */
/* in the range from 9000 to 9034             */
#define AR_RESERV_WS_X509_CONFIGURATION_ID           AR_RESERV_GUID
#define AR_RESERV_WS_X509_SHORT_DESC                 AR_CORE_SHORT_DESCRIPTION
#define AR_RESERV_WS_X509_SECURITY_TOKEN_REF         9000
#define AR_RESERV_WS_X509_PROP_FILE_POOL             9001
#define AR_RESERV_WS_X509_KEYSTORE_POOL              9002
#define AR_RESERV_WS_X509_SECURITY_ACTION_REQ        9003
#define AR_RESERV_WS_X509_SECURITY_ACTION_RESP       9004
#define AR_RESERV_WS_X509_SIGN_ALIAS                 9005
#define AR_RESERV_WS_X509_ENCRYPTION_ALIAS           9006
#define AR_RESERV_WS_X509_KEYSTORE_FILE              9007
#define AR_RESERV_WS_X509_PROP_FILE                  9008
#define AR_RESERV_WS_X509_ENCRYPTION_ALIAS_PASS      9009
#define AR_RESERV_WS_X509_FORM_TITLE                 9010
#define AR_RESERV_WS_X509_SIGN_ALIAS_PASS            9011
#define AR_RESERV_WS_X509_TRIMLINE2                  9012
/*                           vui id                  9013 */
#define AR_RESERV_WS_X509_TRIMLINE1                  9014
#define AR_RESERV_WS_X509_LABEL_PROPERTY             9015
#define AR_RESERV_WS_X509_PANEL_HOLDER               9016
#define AR_RESERV_WS_X509_PANEL_CONFIGURATION        9017
#define AR_RESERV_WS_X509_PANEL_ADMINSTRATION        9018
#define AR_RESERV_WS_X509_APPLY_TO_HEADER            9019
#define AR_RESERV_WS_X509_LABEL_KEYSTORE             9020
#define AR_RESERV_WS_X509_TRIMLINE3                  9021
#define AR_RESERV_WS_X509_TEXT                       9022
#define AR_RESERV_WS_X509_ENABLE_SIGN_CONFIRM        9023
#define AR_RESERV_WS_X509_SYM_KEY                    9024
#define AR_RESERV_WS_X509_TEXT2                      9025

/* Reserved fields for Alert User Registration Form */
/* in the range from 9035 to 9059                   */
#define AR_RESERV_ALRT_USER_REG_FLAGS                9035
#define AR_RESERV_ALRT_USER_REG_PLUGIN_NAME          9037
#define AR_RESERV_ALRT_USER_REG_PLUGIN_VALUES        9038
#define AR_RESERV_ALRT_USER_REG_CLIENT_VERSION       9043
#define AR_RESERV_ALRT_USER_REG_CLIENT_CODESET       9044
#define AR_RESERV_ALRT_USER_REG_EXP_TIME             9045
#define AR_RESERV_ALRT_USER_REG_REREGISTER           9046
#define AR_RESERV_ALRT_USER_REG_TITLE                9048
#define AR_RESERV_ALRT_USER_REG_PANEL_HOLDER         9049
#define AR_RESERV_ALRT_USER_REG_REGISTRATION         9050
#define AR_RESERV_ALRT_USER_REG_ADMIN                9051
#define AR_RESERV_ALRT_UPDATE_SENT_FLAG              9057

#define AR_RESERV_ALRT_DELIVERY_REG_LABEL            9052
#define AR_RESERV_ALRT_DELIVERY_REG_NAME             9053
#define AR_RESERV_ALRT_DELIVERY_TITLE                9054

                 /* 400 reserved field ids to identify report schema */
#define AR_RESERV_REPORT_MIN                    17000 
#define AR_RESERV_REPORT_MAX                    17399 

#define AR_RESERV_REPORT_CREATOR_SCHEMA         17127 
#define AR_RESERV_REPORT_SCHEMA                 2010005 
#define AR_RESERV_REPORT_TYPE_SCHEMA            2010006 
#define AR_RESERV_REPORT_SELECTION_SCHEMA       2010007 
                 /* "Form Name" field on the "Report" schema */
#define AR_RESERV_REPORT_FORM_NAME              2000010 

               /* 2000 reserved field ids to identify email forms */
#define AR_RESERV_EMAIL_MIN                     18000 
#define AR_RESERV_EMAIL_MAX                     19999 
               /* shared among all email forms. */
#define AR_RESERV_EMAIL_GUID                    179 
#define AR_RESERV_EMAIL_HIDDEN                  18213 

/* Reserved fields for the Email Association form */
#define AR_RESERV_EMAIL_ASSOC_DEST_ID           18000 
#define AR_RESERV_EMAIL_ASSOC_SOURCE_TYPE       18001 
#define AR_RESERV_EMAIL_ASSOC_DEST_TYPE         18002 
#define AR_RESERV_EMAIL_ASSOC_BOX_10            18006    /* reused */
#define AR_RESERV_EMAIL_ASSOC_BOX_11            18007    /* reused */
#define AR_RESERV_EMAIL_ASSOC_SRC_ID            18134 
#define AR_RESERV_EMAIL_ASSOC_FORM_ID           19000    /* 30007L */
#define AR_RESERV_EMAIL_ASSOC_HDR_LABEL         18182    /* reused */
#define AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL    18193    /* reused */
#define AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR    18210    /* reused */

/* Reserved fields for the Email Attachments form */
#define AR_RESERV_EMAIL_ATTCH_ATTCHMNT_POOL     18003 
#define AR_RESERV_EMAIL_ATTCH_EMAIL_ATTACHMNT   18004 
#define AR_RESERV_EMAIL_ATTCH_TYPE              18005 
#define AR_RESERV_EMAIL_ATTCH_BOX_10            AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_ATTCH_BOX_11            AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_ATTCH_EMAIL_GUID        18051 
#define AR_RESERV_EMAIL_ATTCH_ATTCHMENT_NAME    18133 
#define AR_RESERV_EMAIL_ATTCH_SAVE              18151    /* reused */
#define AR_RESERV_EMAIL_ATTCH_FORM_ID           19001    /* 30008L */
#define AR_RESERV_EMAIL_ATTCH_SUB_HDR_LABEL     AR_RESERV_EMAIL_ASSOC_HDR_LABEL /* 18182L */
#define AR_RESERV_EMAIL_ATTCH_FORM_HDR_LABEL    AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL /* 18193L */
#define AR_RESERV_EMAIL_ATTCH_HIDDEN_PG_HLDR    AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */
#define AR_RESERV_EMAIL_ATTCH_COLUMN2           18225 
#define AR_RESERV_EMAIL_ATTCH_COLUMN            18226 
#define AR_RESERV_EMAIL_ATTCH_TEMP_INDEX        18249 
#define AR_RESERV_EMAIL_ATTCH_TEMP_NAME         18248 

/* Reserved fields for the Email Error Logs form */
#define AR_RESERV_EMAIL_ERR_LOG_MSG_BOX_10      AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_ERR_LOG_MSG_BOX_11      AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_ERR_LOG_MSG_TYPE        18019 
#define AR_RESERV_EMAIL_ERR_LOG_MSG_GEN_BY      18020 
#define AR_RESERV_EMAIL_ERR_LOG_MSG_NUM         18021 
#define AR_RESERV_EMAIL_ERR_LOG_MSG_TXT         18022    /* reused */
#define AR_RESERV_EMAIL_ERR_LOG_EMAIL_ID        18023 
#define AR_RESERV_EMAIL_ERR_LOG_CLASS_NAME      18024 
#define AR_RESERV_EMAIL_ERR_LOG_METHOD_NAME     18025 
#define AR_RESERV_EMAIL_ERR_LOG_CALL_STACK      18026 
#define AR_RESERV_EMAIL_ERR_LOG_MAILBOX_ID      AR_RESERV_EMAIL_MSG_MAILBOX_ID /* 18093L */
#define AR_RESERV_EMAIL_ERR_LOG_FORM_ID         19002    /* 30010L */
#define AR_RESERV_EMAIL_ERR_LOG_SUB_HDR_LABEL   18192    /* reused */
#define AR_RESERV_EMAIL_ERR_LOG_FORM_HDR_LABEL  AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL /* 18193L */
#define AR_RESERV_EMAIL_ERR_LOG_HIDDEN_PG_HLDR  AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */
#define AR_RESERV_EMAIL_ERR_LOG_COLUMN2         18227 
#define AR_RESERV_EMAIL_ERR_LOG_COLUMN3         18228 
#define AR_RESERV_EMAIL_ERR_LOG_COLUMN4         18229 
#define AR_RESERV_EMAIL_ERR_LOG_COLUMN5         18230 

/* Reserved fields for the Email Instruction Parameters form */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_BOX_10           AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_BOX_11           AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_NAME             18028 
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_ID               18029 
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_VALUE            18030 
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_ATTACHMNT        18031 
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_FORM_ID          19003    /* 30011L */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_SUB_HDR_LABEL    AR_RESERV_EMAIL_ERR_LOG_SUB_HDR_LABEL    /* 18192L */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_FORM_HDR_LABEL   AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL /* 18193L */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_HIDDEN_PG_HLDR   AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */
#define AR_RESERV_EMAIL_INSTRCTNS_PARMS_ATTCHMNT_POOL    18198    /* reused */

/* Reserved fields for the Email Instructions form */
#define AR_RESERV_EMAIL_INSTRCTNS_BOX_10           AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_INSTRCTNS_BOX_11           AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_INSTRCTNS_EMAIL_ID         18032 
#define AR_RESERV_EMAIL_INSTRCTNS_MAILBOX_ID       18033 
#define AR_RESERV_EMAIL_INSTRCTNS_INSTRCTN         18034 
#define AR_RESERV_EMAIL_INSTRCTNS_AR_SVR           18035 
#define AR_RESERV_EMAIL_INSTRCTNS_FORM_ID          19004    /* 30012L*/
#define AR_RESERV_EMAIL_INSTRCTNS_SUB_HDR_LABEL    AR_RESERV_EMAIL_ERR_LOG_SUB_HDR_LABEL    /* 18192L */
#define AR_RESERV_EMAIL_INSTRCTNS_FORM_HDR_LABEL   AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL /* 18193L */
#define AR_RESERV_EMAIL_INSTRCTNS_HIDDEN_PG_HLDR   AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */

/* Reserved fields for the Email Mailbox Configuration form */
#define AR_RESERV_EMAIL_CONFIG_BOX_10                    AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_CONFIG_BOX_11                    AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_CONFIG_MAILBOX_NAME              18037 
#define AR_RESERV_EMAIL_CONFIG_IN_MAILSVR_PORT           18038 
#define AR_RESERV_EMAIL_CONFIG_IN_MAILSVR_USER           18039 
#define AR_RESERV_EMAIL_CONFIG_IN_MAILSVR_TYPE           18041 
#define AR_RESERV_EMAIL_CONFIG_OUT_MAILSVR_TYPE          18045 
#define AR_RESERV_EMAIL_CONFIG_IN_MAILSVR_SSL            18046 
#define AR_RESERV_EMAIL_CONFIG_MAILBOX_FUNC              18049 
#define AR_RESERV_EMAIL_CONFIG_IN_POLL_INTVL             18050 
#define AR_RESERV_EMAIL_CONFIG_EMAIL_ACTION              18052 
#define AR_RESERV_EMAIL_CONFIG_DFLT_WKFLW_FORM           18053 
#define AR_RESERV_EMAIL_CONFIG_DFLT_FORM_ONLY            18054 
#define AR_RESERV_EMAIL_CONFIG_REPLY_W_RSLT              18055 
#define AR_RESERV_EMAIL_CONFIG_USER_NAME                 18056 
#define AR_RESERV_EMAIL_CONFIG_EMAIL_ADDRESS             18057 
#define AR_RESERV_EMAIL_CONFIG_REPLY_TO_ADDRESS          18058 
#define AR_RESERV_EMAIL_CONFIG_ORGANIZATION              18059 
#define AR_RESERV_EMAIL_CONFIG_DFLT_TO                   18069 
#define AR_RESERV_EMAIL_CONFIG_DFLT_CC                   18070 
#define AR_RESERV_EMAIL_CONFIG_DFLT_BCC                  18071 
#define AR_RESERV_EMAIL_CONFIG_HEADER_TMP                18074 
#define AR_RESERV_EMAIL_CONFIG_USE_SECURITY_IN           18076 
#define AR_RESERV_EMAIL_CONFIG_USE_EMAIL_ADDR_FRM_IN     18077 
#define AR_RESERV_EMAIL_CONFIG_USE_SUPPLIED_USER_INFO_IN 18078 
#define AR_RESERV_EMAIL_CONFIG_FOOTER_TMP                18079 
#define AR_RESERV_EMAIL_CONFIG_STATUS_TMP                18080 
#define AR_RESERV_EMAIL_CONFIG_RESULT_TMP                18081 
#define AR_RESERV_EMAIL_CONFIG_IN_MAIL_SVR_IP            18130 
#define AR_RESERV_EMAIL_CONFIG_HDR_TMP_NAME        18143 
#define AR_RESERV_EMAIL_CONFIG_FTR_TMP_NAME        18144 
#define AR_RESERV_EMAIL_CONFIG_STAT_TMP_NAME       18145 
#define AR_RESERV_EMAIL_CONFIG_RSLT_TMP_NAME       18146 
#define AR_RESERV_EMAIL_CONFIG_DFLT_MAILBOX        18147    /* out going */
#define AR_RESERV_EMAIL_CONFIG_ENABLE_MODIFICATION 18148 
#define AR_RESERV_EMAIL_CONFIG_SAVE                AR_RESERV_EMAIL_ATTCH_SAVE /* 18151L */
#define AR_RESERV_EMAIL_CONFIG_SUB_HDR_LABEL       AR_RESERV_EMAIL_ASSOC_HDR_LABEL /* 18182L */
#define AR_RESERV_EMAIL_CONFIG_FORM_HDR_LABEL      18183    /* reused */
#define AR_RESERV_EMAIL_CONFIG_PG_HLDR             18184 
#define AR_RESERV_EMAIL_CONFIG_MAILBOX_CNFG_TAB    18185 
#define AR_RESERV_EMAIL_CONFIG_ACTION_CNFG_TAB     18186 
#define AR_RESERV_EMAIL_CONFIG_ACTION_CNFG_LABEL   AR_RESERV_EMAIL_ERR_LOG_SUB_HDR_LABEL /* 18192L */
#define AR_RESERV_EMAIL_CONFIG_ACTION_CNFG_BOX     AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL  /* 18193L */
#define AR_RESERV_EMAIL_CONFIG_IN_SCRTY_CNFG_LABEL 18194 
#define AR_RESERV_EMAIL_CONFIG_IN_SCRTY_CNFG_BOX   18195 
#define AR_RESERV_EMAIL_CONFIG_DFLT_ADDR_LABEL     AR_RESERV_EMAIL_INSTRCTNS_PARMS_ATTCHMNT_POOL /* 18198L */
#define AR_RESERV_EMAIL_CONFIG_DFLT_ADDR_BOX       18199 
#define AR_RESERV_EMAIL_CONFIG_DFLT_TMP_LABEL      18200 
#define AR_RESERV_EMAIL_CONFIG_DFLT_TMP_BOX        18201 
#define AR_RESERV_EMAIL_CONFIG_REPLY_WITH_ENTRY    18205 
#define AR_RESERV_EMAIL_CONFIG_INBOX_PATH          18206 
#define AR_RESERV_EMAIL_CONFIG_PROFILE_NAME        18208 
#define AR_RESERV_EMAIL_CONFIG_HIDDEN_PG_HLDR      AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */
#define AR_RESERV_EMAIL_CONFIG_FORM_ID             19005    /* 30013L*/
#define AR_RESERV_EMAIL_CONFIG_PASSWORD            AR_RESERV_ENCRYPTED_STRING /* 123L */
#define AR_RESERV_EMAIL_CONFIG_ASSOCIATED_GUID     18216 
#define AR_RESERV_EMAIL_CONFIG_MAILBOX_ID          18217 
#define AR_RESERV_EMAIL_CONFIG_ASSOC_MAILBOX_NAME  18218 
#define AR_RESERV_EMAIL_CONFIG_DELETE_OUTGOING     18221 
#define AR_RESERV_EMAIL_CONFIG_DEFLT_OUTGOING2     18222 
#define AR_RESERV_EMAIL_CONFIG_SET_DEFAULT_PORT    18223 
#define AR_RESERV_EMAIL_CONFIG_COLUMN              18231 
#define AR_RESERV_EMAIL_CONFIG_COLUMN2             18232 
#define AR_RESERV_EMAIL_CONFIG_COLUMN3             18233 
#define AR_RESERV_EMAIL_CONFIG_DEFAULT_MAILBOX     18252 

/* Reserved fields for the Email Message form */
#define AR_RESERV_EMAIL_MSG_BOX_10                       AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_MSG_BOX_11                       AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_MSG_CNTNT_ATTCHMNT_ENCODING      18065 
#define AR_RESERV_EMAIL_MSG_VALUES_ATTCHMNT_ENCODING     18066 
#define AR_RESERV_EMAIL_MSG_MSG_ID                       18082 
#define AR_RESERV_EMAIL_MSG_DATE_SENT                    18083 
#define AR_RESERV_EMAIL_MSG_DATE_RECEIVED                18084 
#define AR_RESERV_EMAIL_MSG_TO                           18085 
#define AR_RESERV_EMAIL_MSG_FROM                         18086 
#define AR_RESERV_EMAIL_MSG_REPLY_TO                     18087 
#define AR_RESERV_EMAIL_MSG_CC                           18088 
#define AR_RESERV_EMAIL_MSG_BCC                          18089 
#define AR_RESERV_EMAIL_MSG_SUBJECT                      18090 
#define AR_RESERV_EMAIL_MSG_MSG_BODY                     18091 
#define AR_RESERV_EMAIL_MSG_MSG_TYPE                     18092 
#define AR_RESERV_EMAIL_MSG_MAILBOX_ID                   18093    /* reused */
#define AR_RESERV_EMAIL_MSG_ARSYS_SVR                    18094 
#define AR_RESERV_EMAIL_MSG_ATTCHMNT_POOL                18095 
#define AR_RESERV_EMAIL_MSG_PRIORITY                     18096 
#define AR_RESERV_EMAIL_MSG_SENT_AT                      18097 
#define AR_RESERV_EMAIL_MSG_PARSE_MSG                    18098 
#define AR_RESERV_EMAIL_MSG_SEND_MSG                     18099    /* reused */
#define AR_RESERV_EMAIL_MSG_EMAIL                        18100 
#define AR_RESERV_EMAIL_MSG_ARSYS_FORM                   18101 
#define AR_RESERV_EMAIL_MSG_CONTENT_TMP                  18102 
#define AR_RESERV_EMAIL_MSG_ORGANIZATION                 18103 
#define AR_RESERV_EMAIL_MSG_CONTENT                      18104 
#define AR_RESERV_EMAIL_MSG_FIELD_VALUE                  18106 
#define AR_RESERV_EMAIL_MSG_VALUES                       18107 
#define AR_RESERV_EMAIL_MSG_HEADER_TMP_ID                18108 
#define AR_RESERV_EMAIL_MSG_FOOTER_TEMPLATE              18109 
#define AR_RESERV_EMAIL_MSG_QUALIFICATION                18110 
#define AR_RESERV_EMAIL_MSG_ARSYS_TCP_PORT               18111 
#define AR_RESERV_EMAIL_MSG_ARSYS_RPC                    18112 
#define AR_RESERV_EMAIL_MSG_FORM_ID                      19006    /* 30014L */
#define AR_RESERV_EMAIL_MSG_LOG_MSG_TXT                  AR_RESERV_EMAIL_ERR_LOG_MSG_TXT /* 18022L */
#define AR_RESERV_EMAIL_MSG_HDR_TMP_NAME                 18135 
#define AR_RESERV_EMAIL_MSG_CNTNT_TMP_NAME               18136 
#define AR_RESERV_EMAIL_MSG_FTR_TMP_NAME                 18137 
#define AR_RESERV_EMAIL_MSG_MAILBOX_NAME                 18139    /* reused */
#define AR_RESERV_EMAIL_MSG_HTML_CNTNT                   18140 
#define AR_RESERV_EMAIL_MSG_HTML_CNTNT_ATTCHMNT_ENCODE   18141 
#define AR_RESERV_EMAIL_MSG_REPLY                        18149 
#define AR_RESERV_EMAIL_MSG_SEND_EMAIL                   18150 
#define AR_RESERV_EMAIL_MSG_SAVE                         AR_RESERV_EMAIL_ATTCH_SAVE /* 18151L */
#define AR_RESERV_EMAIL_MSG_ATTCH_TBL_FLD                18152    /* reused */
#define AR_RESERV_EMAIL_MSG_ATTCH_ID_CLMN                18153    /* reused */
#define AR_RESERV_EMAIL_MSG_ATTCH_NAME_CLMN              18154    /* reused */
#define AR_RESERV_EMAIL_MSG_ATTCH_TYPE_CLMN              18155    /* reused */
#define AR_RESERV_EMAIL_MSG_ERR_TABLE                    18157 
#define AR_RESERV_EMAIL_MSG_CLMN3                        18158 
#define AR_RESERV_EMAIL_MSG_CLMN7                        18159 
#define AR_RESERV_EMAIL_MSG_CLMN8                        18160 
#define AR_RESERV_EMAIL_MSG_LOG_MSG_ID                   18161 
#define AR_RESERV_EMAIL_MSG_MSG_PG_HLDR                  18162 
#define AR_RESERV_EMAIL_MSG_MSG_TAB                      18163 
#define AR_RESERV_EMAIL_MSG_ATTCH_TAB                    18164 
#define AR_RESERV_EMAIL_MSG_ADVANCE_OPT_TAB              18165 
#define AR_RESERV_EMAIL_MSG_MSG_INFO_TAB                 18166 
#define AR_RESERV_EMAIL_MSG_ERROR_TAB                    18167 
#define AR_RESERV_EMAIL_MSG_CRM_SUPPORT                  18168 
#define AR_RESERV_EMAIL_MSG_BODY_PG_HLDR                 18169 
#define AR_RESERV_EMAIL_MSG_HTML_BODY_PG                 18170 
#define AR_RESERV_EMAIL_MSG_ADD_ATTCH                    18171    /* reused */
#define AR_RESERV_EMAIL_MSG_MOD_ATTCH                    18172    /* reused */
#define AR_RESERV_EMAIL_MSG_DEL_ATTCH                    18173    /* reused */
#define AR_RESERV_EMAIL_MSG_EXISTING_ATTCH               18174    /* reused */
#define AR_RESERV_EMAIL_MSG_EXISTING_ATTCH_ID            18175    /* reused */
#define AR_RESERV_EMAIL_MSG_ADD_EXISTING                 18176    /* reused */
#define AR_RESERV_EMAIL_MSG_REFRESH_TBL                  18177    /* reused */
#define AR_RESERV_EMAIL_MSG_PG_HLDR2                     18178 
#define AR_RESERV_EMAIL_MSG_TMP_TAB                      18179 
#define AR_RESERV_EMAIL_MSG_VAR_REPLACE_TAB              18180 
#define AR_RESERV_EMAIL_MSG_ATTCH_ALTERNATIVE            18181 
#define AR_RESERV_EMAIL_MSG_PLAIN_TXT_BODY_PG            18191 
#define AR_RESERV_EMAIL_MSG_FORM_HDR_LABEL               AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL /* 18193L */
#define AR_RESERV_EMAIL_MSG_SUB_HDR_LABEL                18224 
#define AR_RESERV_EMAIL_MSG_RTF_CONTENT                  18209 
#define AR_RESERV_EMAIL_MSG_HIDDEN_PG_HLDR               AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */
#define AR_RESERV_EMAIL_MSG_ATTACHMENT_GUID_COLUMN       18212 
#define AR_RESERV_EMAIL_MSG_RTF_CONTENT_ENCODE           18215 
#define AR_RESERV_EMAIL_MSG_INCOMING_MAILBOX_ID          18220 
#define AR_RESERV_EMAIL_MSG_HTML_BODY                    18290 
#define AR_RESERV_EMAIL_MSG_CRM_READ_STAT                18291 
#define AR_RESERV_EMAIL_MSG_CRM_MAX_RETRIES              18292 
#define AR_RESERV_EMAIL_MSG_CRM_RETRY_COUNT              18293 
#define AR_RESERV_EMAIL_MSG_CRM_SMTP_SVR_RET_CODE        18294 
#define AR_RESERV_EMAIL_MSG_CRM_LAST_LOG_ENTRY           18295 
#define AR_RESERV_EMAIL_MSG_CRM_EMAIL_LOG                18296 
#define AR_RESERV_EMAIL_MSG_ATTCH                        18297 
#define AR_RESERV_EMAIL_MSG_CRM_SUBMITTED_FORM           18298    /* reused */
#define AR_RESERV_EMAIL_MSG_IN_REPLY_TO                  18299 
#define AR_RESERV_EMAIL_MSG_DISPLAY_ADVANCED_OPT         18304 
#define AR_RESERV_EMAIL_MSG_COLUMN                       18235 
#define AR_RESERV_EMAIL_MSG_COLUMN2                      18236 
#define AR_RESERV_EMAIL_MSG_COLUMN4                      18237 

/* Reserved fields for the Email Security form */
#define AR_RESERV_EMAIL_SEC_BOX_10                    AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_SEC_BOX_11                    AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_SEC_USER_NAME                 18113 
#define AR_RESERV_EMAIL_SEC_KEY                       18115 
#define AR_RESERV_EMAIL_SEC_FOR_MAILBOX_ONLY          18116 
#define AR_RESERV_EMAIL_SEC_EMAIL_ADDRESSES           18117 
#define AR_RESERV_EMAIL_SEC_USE_EMAIL_FROM_ADDRESSES  18118 
#define AR_RESERV_EMAIL_SEC_KEY_EXPIRE                18119 
#define AR_RESERV_EMAIL_SEC_EXPIRE_DATE_TIME          18120 
#define AR_RESERV_EMAIL_SEC_DESCRIPTION               18129 
#define AR_RESERV_EMAIL_SEC_SAVE                      AR_RESERV_EMAIL_ATTCH_SAVE /* 18151L */
#define AR_RESERV_EMAIL_SEC_FORM_ID                   19007    /* 30009L */
#define AR_RESERV_EMAIL_SEC_MAILBOX_ID                AR_RESERV_EMAIL_MSG_MAILBOX_ID /* 18093L */
#define AR_RESERV_EMAIL_SEC_MAILBOX_NAME              AR_RESERV_EMAIL_MSG_MAILBOX_NAME /* 18139L */
#define AR_RESERV_EMAIL_SEC_FORM_HDR_LABEL            AR_RESERV_EMAIL_CONFIG_FORM_HDR_LABEL /* 18183L */
#define AR_RESERV_EMAIL_SEC_SUB_HDR_LABEL             AR_RESERV_EMAIL_ERR_LOG_SUB_HDR_LABEL /* 18192L */
#define AR_RESERV_EMAIL_SEC_HIDDEN_PG_HLDR            AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR  /* 18210L */
#define AR_RESERV_EMAIL_SEC_COLUMN                    18238 
#define AR_RESERV_EMAIL_SEC_COLUMN2                   18239 
#define AR_RESERV_EMAIL_SEC_COLUMN3                   18240 
#define AR_RESERV_EMAIL_SEC_COLUMN4                   18241 
#define AR_RESERV_EMAIL_SEC_COLUMN5                   18242 

/* Reserved fields for the Email Templates form */
#define AR_RESERV_EMAIL_TMP_BOX_10              AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_TMP_BOX_11              AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_TMP_TMP_NAME            18121 
#define AR_RESERV_EMAIL_TMP_DESCRIPTION         18122 
#define AR_RESERV_EMAIL_TMP_ATTCHMNT_POOL       18123 
#define AR_RESERV_EMAIL_TMP_TMP_FORMAT          18125 
#define AR_RESERV_EMAIL_TMP_ENCODING            18132 
#define AR_RESERV_EMAIL_TMP_FORM_ID             19008    /* 30015L */
#define AR_RESERV_EMAIL_TMP_TMP_ATTCH           18124 
#define AR_RESERV_EMAIL_TMP_SAVE                AR_RESERV_EMAIL_ATTCH_SAVE /* 18151L */
#define AR_RESERV_EMAIL_TMP_ATTCH_TBL_FID       AR_RESERV_EMAIL_MSG_ATTCH_TBL_FLD /* 18152L */
#define AR_RESERV_EMAIL_TMP_ATTCH_ID_CLMN       AR_RESERV_EMAIL_MSG_ATTCH_ID_CLMN /* 18153L */
#define AR_RESERV_EMAIL_TMP_ATTCH_NAME_CLMN     AR_RESERV_EMAIL_MSG_ATTCH_NAME_CLMN/* 18154L */
#define AR_RESERV_EMAIL_TMP_ATTCH_TYP_CLMN      AR_RESERV_EMAIL_MSG_ATTCH_TYPE_CLMN/* 18155L */
#define AR_RESERV_EMAIL_TMP_ADD_ATTCH           AR_RESERV_EMAIL_MSG_ADD_ATTCH/* 18171L */
#define AR_RESERV_EMAIL_TMP_MOD_ATTCH           AR_RESERV_EMAIL_MSG_MOD_ATTCH/* 18172L */
#define AR_RESERV_EMAIL_TMP_DEL_ATTCH           AR_RESERV_EMAIL_MSG_DEL_ATTCH/* 18173L */
#define AR_RESERV_EMAIL_TMP_EXISTING_ATTCH      AR_RESERV_EMAIL_MSG_EXISTING_ATTCH/* 18174L */
#define AR_RESERV_EMAIL_TMP_EXISTING_ATTCH_ID   AR_RESERV_EMAIL_MSG_EXISTING_ATTCH_ID/* 18175L */
#define AR_RESERV_EMAIL_TMP_ADD_EXISTING        AR_RESERV_EMAIL_MSG_ADD_EXISTING/* 18176L */
#define AR_RESERV_EMAIL_TMP_REFRESH_TBL         AR_RESERV_EMAIL_MSG_REFRESH_TBL/* 18177L */
#define AR_RESERV_EMAIL_TMP_HDR_LABEL           AR_RESERV_EMAIL_ASSOC_HDR_LABEL/* 18182L */
#define AR_RESERV_EMAIL_TMP_SUB_HDR_LABEL       AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL/* 18193L */
#define AR_RESERV_EMAIL_TMP_PG_HLDR             18202 
#define AR_RESERV_EMAIL_TMP_TMP_INFO            18203 
#define AR_RESERV_EMAIL_TMP_TMP_ATTCHs          18204 
#define AR_RESERV_EMAIL_TMP_HIDDEN_PG_HLDR      AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR /* 18210L */
#define AR_RESERV_EMAIL_TMP_ATTACHMENT_GUID_COL AR_RESERV_EMAIL_MSG_ATTACHMENT_GUID_COLUMN /* 18212 */
#define AR_RESERV_EMAIL_TMP_COLUMN              18243 
#define AR_RESERV_EMAIL_TMP_COLUMN2             18244 
#define AR_RESERV_EMAIL_TMP_COLUMN3             18245 
#define AR_RESERV_EMAIL_TMP_COLUMN4             18246 
#define AR_RESERV_EMAIL_TMP_TEMP_INDEX          18250 
#define AR_RESERV_EMAIL_TMP_TEMP_NAME           18251 

/* Reserved fields for the Email User Instruction Template form */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_BOX_10           AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_BOX_11           AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_INSTRUCTION      18126 
#define AR_RESERV_EMAIL_INSTRCTN_TMP_TMP_ID           18127 
#define AR_RESERV_EMAIL_INSTRCTN_TMP_SAVE             AR_RESERV_EMAIL_ATTCH_SAVE /* 18151L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_FORM_ID          19009    /* 30016L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_MAILBOX_ID       AR_RESERV_EMAIL_MSG_MAILBOX_ID /* 18093L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_MAILBOX_NAME     AR_RESERV_EMAIL_MSG_MAILBOX_NAME/* 18139L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_TMP_NAME         18142 
#define AR_RESERV_EMAIL_INSTRCTN_TMP_SUB_HDR_LABEL    AR_RESERV_EMAIL_ERR_LOG_SUB_HDR_LABEL/* 18192L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_FORM_HDR_LABEL   AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL/* 18193L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_HIDDEN_PG_HLDR   AR_RESERV_EMAIL_ASSOC_HIDDEN_PG_HLDR/* 18210L */
#define AR_RESERV_EMAIL_INSTRCTN_TMP_COLUMN           18247 

/* Reserved fields for the Email Attachment join form */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_TYPE            AR_RESERV_EMAIL_ATTCH_TYPE    /* 18005L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_BOX_10          AR_RESERV_EMAIL_ASSOC_BOX_10  /* 18006L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_BOX_11          AR_RESERV_EMAIL_ASSOC_BOX_11  /* 18007L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_ATTCHMENT_NAME  AR_RESERV_EMAIL_ATTCH_ATTCHMENT_NAME  /* 18133L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_SRC_ID          AR_RESERV_EMAIL_ASSOC_SRC_ID  /* 18134L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_HDR_LABEL       AR_RESERV_EMAIL_ASSOC_HDR_LABEL /* 18182L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_SUB_HDR_LABEL   AR_RESERV_EMAIL_CONFIG_FORM_HDR_LABEL /* 18183L */
#define AR_RESERV_EMAIL_ATTCHMNT_JOIN_ATTCH_ID        AR_RESERV_EMAIL_ASSOC_FORM_HDR_LABEL/* 18193L */

                 /* reserved field ids unique within a schema */
                 /* but not across schemas */
#define AR_RESERV_SCHEMA_SPECIFIC_FIELD_MIN       20000 
#define AR_RESERV_SCHEMA_SPECIFIC_FIELD_MAX       29999 

                 /* reserved field ids to identify preference schemas */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_MIN       30000   /* 10,000 for AR System client  */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_MAX       39999   /* preference schema  */

#define AR_RESERV_PREFERENCE_ARS_SCHEMA_COMMON    30000   /* Reserved field IDs to identify */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_ADMIN     30001   /* pref schema holding pref files */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_USER      30002   /* (i.e. report, macro and etc.)  */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_WEBTIER   30003   /* and other client related       */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_ALERT     30004   /* schemas                        */
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_MIGRATOR  30005 
#define AR_RESERV_PREFERENCE_ARS_SCHEMA_FILES     30006

#define AR_RESERV_METADATA_ACTLINK                30020
#define AR_RESERV_METADATA_IMAGE                  30021
#define AR_RESERV_METADATA_FILTER                 30022
#define AR_RESERV_METADATA_ESCALATION             30023
#define AR_RESERV_METADATA_ARSCHEMA               30024
#define AR_RESERV_METADATA_ARCONTAINER            30025
#define AR_RESERV_METADATA_FIELD                  30026
#define AR_RESERV_METADATA_FIELD_DISPPROP         30027
#define AR_RESERV_METADATA_ACTLINK_MAPPING        30028
#define AR_RESERV_METADATA_ACTLINK_MACRO          30029
#define AR_RESERV_METADATA_ACTLINK_MACRO_PARM     30030
#define AR_RESERV_METADATA_ACTLINK_SET            30031
#define AR_RESERV_METADATA_ACTLINK_PROCESS        30032
#define AR_RESERV_METADATA_ACTLINK_MESSAGE        30033
#define AR_RESERV_METADATA_ACTLINK_SET_CHAR       30034
#define AR_RESERV_METADATA_ACTLINK_DDE            30035
#define AR_RESERV_METADATA_ACTLINK_AUTO           30036
#define AR_RESERV_METADATA_ACTLINK_PUSH           30037
#define AR_RESERV_METADATA_ACTLINK_SQL            30038
#define AR_RESERV_METADATA_ACTLINK_OPEN           30039
#define AR_RESERV_METADATA_ACTLINK_CALL           30040
#define AR_RESERV_METADATA_ACTLINK_GOTO           30041
#define AR_RESERV_METADATA_ACTLINK_WAIT           30042
#define AR_RESERV_METADATA_ACTLINK_SERVICEACTION  30043
#define AR_RESERV_METADATA_ESCAL_MAPPING          30044
#define AR_RESERV_METADATA_FILTER_MAPPING         30045
#define AR_RESERV_METADATA_FILTER_NOTIFY          30046
#define AR_RESERV_METADATA_FILTER_MESSAGE         30047
#define AR_RESERV_METADATA_FILTER_LOG             30048
#define AR_RESERV_METADATA_FILTER_SET             30049
#define AR_RESERV_METADATA_FILTER_PROCESS         30050
#define AR_RESERV_METADATA_FILTER_PUSH            30051
#define AR_RESERV_METADATA_FILTER_SQL             30052
#define AR_RESERV_METADATA_FILTER_CALL            30053
#define AR_RESERV_METADATA_FILTER_GOTO            30054
#define AR_RESERV_METADATA_FILTER_SERVICEACTION   30055
#define AR_RESERV_METADATA_CNTNR_OWNR_OBJ         30056
#define AR_RESERV_METADATA_ARREFERENCE            30057
#define AR_RESERV_METADATA_VUI                    30058
#define AR_RESERV_METADATA_CHAR_MENU_LIST         30059
#define AR_RESERV_METADATA_CHAR_MENU              30060
#define AR_RESERV_METADATA_FIELD_TABLE            30061
#define AR_RESERV_METADATA_FIELD_CURR             30062
#define AR_RESERV_METADATA_FIELD_ENUM_VALUES      30063
#define AR_RESERV_METADATA_FIELD_CHAR             30064
#define AR_RESERV_METADATA_VIEW_MAPPING           30065
#define AR_RESERV_METADATA_VENDOR_MAPPING         30066
#define AR_RESERV_METADATA_FIELD_ENUM             30067
#define AR_RESERV_METADATA_SCHEMA_ARCHIVE         30068
#define AR_RESERV_METADATA_SCHEMA_AUDIT           30069
#define AR_RESERV_METADATA_SCHEMA_JOIN            30070
#define AR_RESERV_METADATA_SCHEMA_INDEX           30071
#define AR_RESERV_METADATA_SCHEMA_GROUP_IDS       30072
#define AR_RESERV_METADATA_SCHEMA_LIST_FIELDS     30073
#define AR_RESERV_METADATA_SUBADMIN_GROUP         30074
#define AR_RESERV_METADATA_FIELD_PERMISSIONS      30075
#define AR_RESERV_METADATA_FIELD_COLUMN           30076
#define AR_RESERV_METADATA_ACTLINK_GROUP_IDS      30077
#define AR_RESERV_METADATA_ARCTR_GROUP_IDS        30078
#define AR_RESERV_METADATA_ARCTR_SUBADMIN         30079
#define AR_RESERV_METADATA_CHAR_MENU_FILE         30080
#define AR_RESERV_METADATA_CHAR_MENU_SQL          30081
#define AR_RESERV_METADATA_CHAR_MENU_DD           30082
#define AR_RESERV_METADATA_CHAR_MENU_QUERY        30083

#define AR_RESERV_IGNORE_ANALYZER_IGNORE_TYPE     30084

#define AR_RESERV_METADATA_OVERLAY_GROUP          30085
#define AR_RESERV_METADATA_OVERLAY_PROP           30086
#define AR_RESERV_METADATA_RESOLVED_NAME          30087
#define AR_RESERV_METADATA_RESOLVED_ID            30088


                 /* reserved field ids used to identify various flashboard schemas       */
                 /* The actual id values are available in the Flashboard server/midtier  */
                 /* and admin tool components. This define here is to reserve the range  */
                 /* so that no other module uses it                                      */
#define AR_RESERV_FLASHBOARD_FIELDS_MIN         40000 
#define AR_RESERV_FLASHBOARD_FIELDS_MAX         42000 

                  /* unique field ids used to identify flashboard forms */
#define AR_RESERV_FB_ALARM_EVENTS               40280 
#define AR_RESERV_FB_ALARM_MONITOR              40262 
#define AR_RESERV_FB_DATA_SOURCE                40056 
#define AR_RESERV_FB_DATA_SOURCE_VARIABLES      40250 
#define AR_RESERV_FB_FLASHBOARDS                40164 
#define AR_RESERV_FB_HISTORY                    40100 
#define AR_RESERV_FB_HISTORY_SUMMARY            40306 
#define AR_RESERV_FB_VARIABLE                   40075 
#define AR_RESERV_FB_VARIABLE_ATTRIBUTES        40201 

                  /* reserved flashboard fields */
#define AR_RESERV_FB_VARIABLE_ID                40000    /* Variable System ID */
#define AR_RESERV_FB_DATA_SOURCE_ID             40001    /* Data Source System ID */
#define AR_RESERV_FB_ALARM_SOURCE_ID            40260    /* Alarm System ID */
#define AR_RESERV_FB_NAME                       AR_CORE_SHORT_DESCRIPTION   /* Flashboard Name */


                /* reserved field ids for UDM forms */
#define AR_RESERV_SCHEMA_SPECIFIC_UDM_FIELD_MIN   46000 
#define AR_RESERV_SCHEMA_SPECIFIC_UDM_FIELD_MAX   47999 

                 /* reserved field ids for wireless forms */
#define AR_RESERV_SCHEMA_SPECIFIC_WIRELESS_FIELD_MIN   50000 
#define AR_RESERV_SCHEMA_SPECIFIC_WIRELESS_FIELD_MAX   50999 

                 /* reserved field ids for Searches Preference forms */
#define AR_RESERV_SCHEMA_SPECIFIC_SEARCHESPREF_FIELD_MIN   51000 
#define AR_RESERV_SCHEMA_SPECIFIC_SEARCHESPREF_FIELD_MAX   51999 

#define AR_RESERV_SEARCH_PREF_NAME           AR_CORE_SHORT_DESCRIPTION  /* Search Name */
#define AR_RESERV_SEARCH_PREF_USER           AR_CORE_SUBMITTER          /*User this search belongs to*/
#define AR_RESERV_SEARCH_PREF_QUALIFICATION  51000                      /*search criteria*/
#define AR_RESERV_SEARCH_PREF_FORM           51001                      /*form this search is associated with*/
#define AR_RESERV_SEARCH_PREF_DISABLE        51002                      /*enabled/disabled state of this search */
#define AR_RESERV_SEARCH_PREF_TYPE           51003                      /*search type:recent, user-defined, admin-defined */
#define AR_RESERV_SEARCH_PREF_SERVER         51004                      /*server on which the associated form resides*/

/* reserved field ids for AR System Skins application */
#define AR_RESERV_SCHEMA_SPECIFIC_SKINS_FIELD_MIN   52000 
#define AR_RESERV_SCHEMA_SPECIFIC_SKINS_FIELD_MAX   52999 

/* AR System Skin form */
#define AR_RESERV_SKIN_GUID                  AR_RESERV_GUID            /* Skin unique identifier */
#define AR_RESERV_SKIN_NAME                  AR_CORE_SHORT_DESCRIPTION /* Skin name */
#define AR_RESERV_SKIN_TYPE                  52000                     /* Skin type */
#define AR_RESERV_SKIN_TYPE_IDENTIFIER       52001                     /* Skin type identifier */
#define AR_RESERV_SKIN_STATE                 AR_CORE_STATUS            /* enabled/disabled state of skin */
#define AR_RESERV_SKIN_FORM                  52002                     /* Form name for view specific skin */
#define AR_RESERV_SKIN_ASSIGNED_GROUP        AR_RESERV_ASSIGNED_GROUP  /* Assigned group */
#define AR_RESERV_SKINS_RSV_FLD              3

/* AR System Skin Properties form */
#define AR_RESERV_SKIN_PROP_GUID                 AR_RESERV_GUID /* Skin Property unique identifier */
#define AR_RESERV_SKIN_PARENT_GUID               52100          /* GUID: Skin that owns this prop */
#define AR_RESERV_SKIN_PROPERTY_TYPE             52101          /* Skin property type */
#define AR_RESERV_SKIN_PROPERTY_TYPE_IDENTIFIER  52102          /* Skin property type identifier */
#define AR_RESERV_SKIN_PROPERTY_TAG              52103          /* Identify for AR property */
#define AR_RESERV_SKIN_PROPERTY_VALUE            52104          /* Value for AR property */
#define AR_RESERV_SKIN_PROP_RSV_FLD              5

/* AR System Skinnable Properties form */
#define AR_RESERV_SKINABLE_FIELD_TYPE            52200          /* Skinable field type */
#define AR_RESERV_SKINABLE_PROP_ID               52201          /* Skinable property ID */
#define AR_RESERV_SKINS_SKINABLE_RSV_FLD         2

/* reserved field ids for Query Builder Widget */
#define AR_RESERV_QBWIDGET_FIELD_MIN            53000
#define AR_RESERV_QBWIDGET_FIELD_MAX            53199
/* AR System Query Widget form */
#define AR_RESERV_QBWIDGET_FNAME_ID             53000
#define AR_RESERV_QBWIDGET_DFIELD_ID_ID         53004
#define AR_RESERV_QBWIDGET_DFIELD_SHOWMENU_ID   53005
/* AR System Query Fields form */
#define AR_RESERV_QBWIDGET_FIELD_ID_ID          53150
#define AR_RESERV_QBWIDGET_FIELD_SHOWMENU_ID    53151
#define AR_RESERV_QBWIDGET_FIELD_DESCRIPTION_ID 53152
/* AR System Query join form */
/*  field ids come from the above */

                 /* Reserved range for dynamic group ids and field ids */
                 /* Group ids below 14000 are for general use by customers */
#define AR_RESERV_GROUP_DYNAMIC_MIN          60000 
#define AR_RESERV_GROUP_DYNAMIC_MAX          60999 

                 /* Reserved field ids to enforce role level security */
                 /* on a system form. These field ids with another group field */
                 /* i.e.(112 or the range given above) should be in the form */
                 /* for this new permission model to work */
#define AR_RESERV_OBJECT_DEF_GROUPNROLE_ID   61000  /* Contains semicolon seperated group/role info */
#define AR_RESERV_OBJECT_DEF_APP_ID          61001  /* Contains an app name for computing the */
                                                    /* role info from the above field to groups */
#define AR_DATA_OBJECT_RSV_FLD                   3  /* Number of tags required to be Data Object form */
#define AR_APP_DATA_OBJECT_RSV_FLD               1  /* Number of tags required to be Data Object form */

#define AR_RSV_FLD_COUNT_ONE                     1 
/* Reserved fields for Homepage Layout form */
#define AR_RESERV_HOME_PAGE_LAYOUT           80100 
/* Reserved fields for Homepage Descriptor form */
#define AR_RESERV_HOME_PAGE_DESCRIPTOR       80101 

/* Reserved fields for Report Designer form */
#define AR_RESERV_REPORT_DESIGNER            91000 
/* Reserved fields for Reporting form */
#define AR_RESERV_REPORTING                  94001 

/*
 * Reserved field range for
 *   AR System Key Store
 *   AR System Server to Key Map
 */
#define AR_RESERV_DVM_PW_ENCRYPT_MIN 99000
#define AR_RESERV_DVM_PW_ENCRYPT_MAX 99009

                 /* Range of reserved field Ids for */
                 /* global fields.                  */
#define AR_RESERV_GLOBAL_FIELDS_MIN          1000000
#define AR_RESERV_GLOBAL_FIELDS_MAX          1999999

                 /* Range of reserved field Ids for */
                 /* workflow variables.             */
#define AR_RESERV_WORKFLOW_VARS_MIN          2000000
#define AR_RESERV_WORKFLOW_VARS_MAX          2999999

/* reserved field ids for SHARE:Application_Properties forms */
#define AR_RESERV_SHARE_APP_PROPS_INSTANCE_ID           179
#define AR_RESERV_SHARE_APP_PROPS_Z1G_INITCOMPLETE      1000049
#define AR_RESERV_SHARE_APP_PROPS_ALL_APP_PROPS         300339700
#define AR_RESERV_SHARE_APP_PROPS_TBL_APP_PROPS         300339800
#define AR_RESERV_SHARE_APP_PROPS_COL_PROP_NAME         300339900
#define AR_RESERV_SHARE_APP_PROPS_COL_PROP_VALUE        300340000
#define AR_RESERV_SHARE_APP_PROPS_PG_CORE_FIELDS        300340100
#define AR_RESERV_SHARE_APP_PROPS_APP_PROP_PG_HOLDER    300340200
#define AR_RESERV_SHARE_APP_PROPS_APP_NAME              400069400
#define AR_RESERV_SHARE_APP_PROPS_APP_GUID              400081600
#define AR_RESERV_SHARE_APP_PROPS_PROP_NAME             400081700
#define AR_RESERV_SHARE_APP_PROPS_PROP_VALUE            400081800

/* reserved field ids for SHARE:Application_Configuration_Registration forms */
#define AR_RESERV_SHARE_APP_CONFIG_REG_INSTANCE_ID                179
#define AR_RESERV_SHARE_APP_CONFIG_REG_COMPONENT_NAME             301628601
#define AR_RESERV_SHARE_APP_CONFIG_REG_COMPONENT_GROUP            301628602
#define AR_RESERV_SHARE_APP_CONFIG_REG_COMPONENT_INST_STATUS      301628603
#define AR_RESERV_SHARE_APP_CONFIG_REG_COMPONENT_CONF_LOCATION    301628605
#define AR_RESERV_SHARE_APP_CONFIG_REG_COMPONENT_PARAM            301628609
#define AR_RESERV_SHARE_APP_CONFIG_REG_COMPONENT_OPEN_METHOD      301628610


#define   inWFVariableRange(_l) ( (_l <= AR_RESERV_WORKFLOW_VARS_MAX) && (_l >= AR_RESERV_WORKFLOW_VARS_MIN) )
#define   getWFVariableType(_l)  ((_l % AR_RESERV_WORKFLOW_VARS_MIN) / 10000)
#define   getWFVariableScope(_l)  ((_l % 10000) / 1000)
/* Note that the following macros only check the guide or filter bit. */
/* You need to make sure the ID is in range and of a correct type     */
/* before using them.                                                 */
#define   isGuideVar(_l) ((_l / 1000) & 1)
#define   isFilterVar(_l) (!(_l / 1000) & 1)

                /* Per API/Execute On condition scope */
#define AR_RESERV_WF_EOC_INTEGER_VAR_MIN   2020000
#define AR_RESERV_WF_EOC_INTEGER_VAR_MAX   2020999
#define AR_RESERV_WF_EOC_REAL_VAR_MIN      2030000
#define AR_RESERV_WF_EOC_REAL_VAR_MAX      2030999
#define AR_RESERV_WF_EOC_CHAR_VAR_MIN      2040000
#define AR_RESERV_WF_EOC_CHAR_VAR_MAX      2040999
#define AR_RESERV_WF_EOC_ENUM_VAR_MIN      2060000
#define AR_RESERV_WF_EOC_ENUM_VAR_MAX      2060999
#define AR_RESERV_WF_EOC_TIMEOFDAY_VAR_MIN 2070000
#define AR_RESERV_WF_EOC_TIMEOFDAY_VAR_MAX 2070999
#define AR_RESERV_WF_EOC_DECIMAL_VAR_MIN   2100000
#define AR_RESERV_WF_EOC_DECIMAL_VAR_MAX   2100999
#define AR_RESERV_WF_EOC_CURRENCY_VAR_MIN  2120000
#define AR_RESERV_WF_EOC_CURRENCY_VAR_MAX  2120999
#define AR_RESERV_WF_EOC_DATE_VAR_MIN      2130000
#define AR_RESERV_WF_EOC_DATE_VAR_MAX      2130999
#define AR_RESERV_WF_EOC_TIME_VAR_MIN      2140000
#define AR_RESERV_WF_EOC_TIME_VAR_MAX      2140999

                /* Per Guide/Workflow Component scope */
#define AR_RESERV_WF_GUIDE_INTEGER_VAR_MIN   2021000
#define AR_RESERV_WF_GUIDE_INTEGER_VAR_MAX   2021999
#define AR_RESERV_WF_GUIDE_REAL_VAR_MIN      2031000
#define AR_RESERV_WF_GUIDE_REAL_VAR_MAX      2031999
#define AR_RESERV_WF_GUIDE_CHAR_VAR_MIN      2041000
#define AR_RESERV_WF_GUIDE_CHAR_VAR_MAX      2041999
#define AR_RESERV_WF_GUIDE_ENUM_VAR_MIN      2061000
#define AR_RESERV_WF_GUIDE_ENUM_VAR_MAX      2061999
#define AR_RESERV_WF_GUIDE_TIMEOFDAY_VAR_MIN 2071000
#define AR_RESERV_WF_GUIDE_TIMEOFDAY_VAR_MAX 2071999
#define AR_RESERV_WF_GUIDE_DECIMAL_VAR_MIN   2101000
#define AR_RESERV_WF_GUIDE_DECIMAL_VAR_MAX   2101999
#define AR_RESERV_WF_GUIDE_CURRENCY_VAR_MIN  2121000
#define AR_RESERV_WF_GUIDE_CURRENCY_VAR_MAX  2121999
#define AR_RESERV_WF_GUIDE_DATE_VAR_MIN      2131000
#define AR_RESERV_WF_GUIDE_DATE_VAR_MAX      2131999
#define AR_RESERV_WF_GUIDE_TIME_VAR_MIN      2141000
#define AR_RESERV_WF_GUIDE_TIME_VAR_MAX      2141999

                 /* Range of reserved field Ids for */
                 /* window global fields            */
#define AR_RESERV_WINDOW_GLOBAL_FIELDS_MIN   3000000
#define AR_RESERV_WINDOW_GLOBAL_FIELDS_MAX   3999999


/* Reserved range for user-actor based view selection  */

#define AR_RESERV_VIEWSEL_USER_APP_ACTOR       45001
#define AR_RESERV_VIEWSEL_ACTOR_VIEW           45002
#define AR_RESERV_VIEWSEL_ACTOR                45003
#define AR_RESERV_VIEWSEL_ACTOR_VIEW_VIEWLABEL 45004
#define AR_RESERV_VIEWSEL_USER_APP_ACTOR_ORDER 45005
#define AR_RESERV_VIEWSEL_ACTOR_VIEW_JOIN      45006
#define AR_RESERV_VIEWSEL_MAX                  45999



#define AR_GROUP_ID_PUBLIC            0  /* group-ids of the 'key' groups */
#define AR_GROUP_ID_ADMINISTRATOR     1 
#define AR_GROUP_ID_CUSTOMIZE         2 
#define AR_GROUP_ID_SUBMITTER         3 
#define AR_GROUP_ID_ASSIGNEE          4 
#define AR_GROUP_ID_SUB_ADMINISTRATOR 5 
#define AR_GROUP_ID_FLASH_ADMIN       6 
#define AR_GROUP_ID_ASSIGNEE_GROUP    7
#define AR_GROUP_ID_STRUCT_ADMIN      8 
#define AR_GROUP_ID_STRUCT_SUB_ADMIN  9 

/* Constants for workflow object relationship types */

#define AR_DEFNOBJ_TYPE_SCHEMA                            1
#define AR_DEFNOBJ_TYPE_FIELD                             2
#define AR_DEFNOBJ_TYPE_ACTIVE_LINK                       3
#define AR_DEFNOBJ_TYPE_FILTER                            4
#define AR_DEFNOBJ_TYPE_ESCALATION                        5
#define AR_DEFNOBJ_TYPE_MENU                              6
#define AR_DEFNOBJ_TYPE_ACTIVE_LINK_GUIDE                 7
#define AR_DEFNOBJ_TYPE_FILTER_GUIDE                      8
#define AR_DEFNOBJ_TYPE_MSGNUM                            9
#define AR_DEFNOBJ_TYPE_APPLICATION                      10
#define AR_DEFNOBJ_TYPE_PACKING_LIST                     11
#define AR_DEFNOBJ_TYPE_IMAGE                            12
#define AR_DEFNOBJ_TYPE_WEB_SERVICE                      13

#define AR_DEFNREL_TYPE_ALF_QUAL_FIELD                    1
#define AR_DEFNREL_TYPE_ALF_SET_TO_FIELD                  2
#define AR_DEFNREL_TYPE_ALF_MESSAGE_FIELD                 3
#define AR_DEFNREL_TYPE_ALF_SQLCOMMAND_FIELD              4
#define AR_DEFNREL_TYPE_ALF_GOTO_ACTION_FIELD             5
#define AR_DEFNREL_TYPE_ALF_PROCESS_FIELD                 6
#define AR_DEFNREL_TYPE_ALF_SET_FROM_FIELD                7
#define AR_DEFNREL_TYPE_ALF_SET_QUAL_FIELD                8
#define AR_DEFNREL_TYPE_ALF_PUSH_TO_FIELD                 9
#define AR_DEFNREL_TYPE_ALF_PUSH_FROM_FIELD              10
#define AR_DEFNREL_TYPE_ALF_PUSH_QUAL_FIELD              11
#define AR_DEFNREL_TYPE_ALF_SET_SQL_FIELD                12
#define AR_DEFNREL_TYPE_ALF_SET_PROCESS_FIELD            13
#define AR_DEFNREL_TYPE_ALF_CALL_GUIDE                   14
#define AR_DEFNREL_TYPE_ALF_MESSAGE_MSGNUM               15
#define AR_DEFNREL_TYPE_ALF_SERVICE_FORM                 33
#define AR_DEFNREL_TYPE_ALF_SERVICE_INPUT_TO_FIELD       34
#define AR_DEFNREL_TYPE_ALF_SERVICE_INPUT_FROM_FIELD     35
#define AR_DEFNREL_TYPE_ALF_SERVICE_OUTPUT_TO_FIELD      36
#define AR_DEFNREL_TYPE_ALF_SERVICE_OUTPUT_FROM_FIELD    37
#define AR_DEFNREL_TYPE_ALF_SERVICE_REQUESTID_FIELD      39
#define AR_DEFNREL_TYPE_ALF_CALL_GUIDE_TABLE_FIELD       41


#define AR_DEFNREL_TYPE_AL_FOCUS_FIELD                   16
#define AR_DEFNREL_TYPE_AL_CONTROL_FIELD                 17
#define AR_DEFNREL_TYPE_AL_CHANGE_FIELD                  18
#define AR_DEFNREL_TYPE_AL_SET_DDE_FIELD                 19
#define AR_DEFNREL_TYPE_AL_AUTOMATION_FIELD              20
#define AR_DEFNREL_TYPE_AL_DDE_FIELD                     21
#define AR_DEFNREL_TYPE_AL_OPENWIN_TARGET_LOC_FIELD      22
#define AR_DEFNREL_TYPE_AL_OPENWIN_MAP_OPEN_TO_FIELD     23
#define AR_DEFNREL_TYPE_AL_OPENWIN_MAP_OPEN_FROM_FIELD   24
#define AR_DEFNREL_TYPE_AL_OPENWIN_MAP_CLOSE_TO_FIELD    25
#define AR_DEFNREL_TYPE_AL_OPENWIN_MAP_CLOSE_FROM_FIELD  26
#define AR_DEFNREL_TYPE_AL_OPENWIN_QUAL_FIELD            27
#define AR_DEFNREL_TYPE_AL_OPENWIN_SORT_FIELD            28
#define AR_DEFNREL_TYPE_AL_OPENWIN_MESSAGE_FIELD         29
#define AR_DEFNREL_TYPE_AL_OPENWIN_REPORT_FIELD          30
#define AR_DEFNREL_TYPE_AL_OPENWIN_DIALOG_FORM           31
#define AR_DEFNREL_TYPE_AL_CHANGE_MENU                   42

#define AR_DEFNREL_TYPE_FLTR_NOTIFY_FIELD                32
#define AR_DEFNREL_TYPE_FLTR_SET_FILTERAPI_FIELD         38
#define AR_DEFNREL_TYPE_FLTR_SET_WEB_SERVICE_FIELD       40
  
#define AR_DEFNREL_TYPE_FIRST_ACTION                      1
#define AR_DEFNREL_TYPE_LAST_ACTION                      42

#define AR_DEFNREL_TYPE_ACTIVE_LINK_FORM                500
#define AR_DEFNREL_TYPE_ACTIVE_LINK_PRIMARY_FORM        501
#define AR_DEFNREL_TYPE_ACTIVE_LINK_SECONDARY_FORM      502
#define AR_DEFNREL_TYPE_FILTER_FORM                     503
#define AR_DEFNREL_TYPE_FILTER_PRIMARY_FORM             504
#define AR_DEFNREL_TYPE_FILTER_SECONDARY_FORM           505
#define AR_DEFNREL_TYPE_ESCALATION_FORM                 506
#define AR_DEFNREL_TYPE_ESCALATION_PRIMARY_FORM         507
#define AR_DEFNREL_TYPE_ESCALATION_SECONDARY_FORM       508
#define AR_DEFNREL_TYPE_FORM_REFERENCED_BY_FIELD        509
#define AR_DEFNREL_TYPE_IMAGE_REFERENCED_BY_FIELD       510
#define AR_DEFNREL_TYPE_IMAGE_REFERENCED_BY_FORM        511
#define AR_DEFNREL_TYPE_FILTER_ERROR_HANDLER_FILTER     512

#define AR_DEFNREL_TYPE_MENU_QUAL_FIELD                1000
#define AR_DEFNREL_TYPE_MENU_LABEL_FIELD               1001
#define AR_DEFNREL_TYPE_MENU_VALUE_FIELD               1002
#define AR_DEFNREL_TYPE_MENU_FORM                      1003
#define AR_DEFNREL_TYPE_MENU_REFERENCED_BY_FIELD       1004

#define AR_DEFNREL_TYPE_MENU_FIRST_REL_TYPE            1000
#define AR_DEFNREL_TYPE_MENU_LAST_REL_TYPE             1999

#define AR_DEFNREL_TYPE_ALGUIDE_ACTIVE_LINK            2000
#define AR_DEFNREL_TYPE_FILTERGUIDE_FILTER             2001
#define AR_DEFNREL_TYPE_ALGUIDE_FORM                   2002
#define AR_DEFNREL_TYPE_FILTERGUIDE_FORM               2003
#define AR_DEFNREL_TYPE_APPL_FORM                      2004
#define AR_DEFNREL_TYPE_APPL_PRIMARY_FORM              2005
#define AR_DEFNREL_TYPE_APPL_PACKING_LIST              2006
#define AR_DEFNREL_TYPE_PL_FORM                        2007
#define AR_DEFNREL_TYPE_PL_ACTIVE_LINK                 2008
#define AR_DEFNREL_TYPE_PL_FILTER                      2009
#define AR_DEFNREL_TYPE_PL_ESCALATION                  2010
#define AR_DEFNREL_TYPE_PL_MENU                        2011
#define AR_DEFNREL_TYPE_PL_ACTIVE_LINK_GUIDE           2012
#define AR_DEFNREL_TYPE_PL_FILTER_GUIDE                2013
#define AR_DEFNREL_TYPE_PL_APPLICATION                 2014
#define AR_DEFNREL_TYPE_PL_PACKING_LIST                2015
#define AR_DEFNREL_TYPE_PL_IMAGE                       2016
#define AR_DEFNREL_TYPE_PL_WEB_SERVICE                 2017
#define AR_DEFNREL_TYPE_WEB_SERVICE_FORM               2018
#define AR_DEFNREL_TYPE_WEB_SERVICE_FIELD              2019
#define AR_DEFNREL_TYPE_ALGUIDE_ENTRY_POINT            2020
#define AR_DEFNREL_TYPE_APPL_DATA_FORM                 2021

#define AR_DEFNREL_TYPE_CONTAINER_FIRST_REL_TYPE       2000
#define AR_DEFNREL_TYPE_CONTAINER_LAST_REL_TYPE        2999


/* Constants used for items in values returned from the server */

#define AR_DEFN_DIARY_SEP        '\03'     /* diary items separator */
#define AR_DEFN_DIARY_COMMA      '\04'     /* char between date/user/text */
                                           /*  within a diary item        */
#define AR_DEFN_STAT_HIST_SEP    '\03'     /* status history items separator */
#define AR_DEFN_STAT_HIST_COMMA  '\04'     /* char between user and time in a */
                                           /*  status history item            */
#define AR_DEFN_VUI_EXT_SEP      '\01'     /* vui extension separator  */
                                           /* within a vui label       */
#define AR_DEFN_LABEL_SIZE       20   /* length of the label portion of lines   */
                                      /*   in the export definition format file */
#define AR_DEFN_LABEL_ENCR_SIZE  20   /* length of the label portion of encrypted   */
                                      /* lines in the export definition format file */
#define AR_MAX_DEFN_LINE_SIZE    325  /* maximum length of a line in a defn file */
                                      /*   (excl "\n\0" at end of each line)     */

#define AR_NOTIFICATION_VUI      "ARNotification"
                                  /* VUI name used to identify the view to */
                                  /*  use for order of fields in an email  */
                                  /*  or other style notification          */

/* Constants holding label definitions for the fields in a definition file */

#define AR_DEFN_FILE_ALL_FIELDS    '*'     /* character to indicate ALL fields*/
#define AR_DEFN_FILE_CHNG_FIELDS   '@'     /* character to indicate CHNG field*/
#define AR_DEFN_FILE_COMMENT       '#'     /* character introducing a comment */
#define AR_DEFN_FILE_SEPARATOR     '\\'    /* character used to separate two */
                                           /*  or more values on one line    */
#define AR_DEFN_GROUP_ID_SEPARATOR ';'     /* character used to separate two */
                                           /*  or more group ids in a list   */
#define AR_DEFN_KEYWORD_PARM_TAG   '$'     /* character surrounding keywords */
                                           /*  and parameters in values      */
#define AR_DEFN_ATTACH_SEPARATOR   ';'     /* character used to separate     */
                                           /*  attributes of a stringified   */
                                           /*  attachment value              */

#define AR_DEFN_SINGLE_USER_GROUP_QUOTE   '\''  /* character that surrounds  */
                                                /* a single user group */

   /* There are some characters that can occur in labels and/or character */
   /* strings that conflict with the formatting characters that allow the */
   /* definition and processing of records.  When these characters are    */
   /* encountered, they are translated into a control character when the  */
   /* data is stored in the DB and then back into the "real" character on */
   /* retrieval.  The "EMBEDDED" definitions define these mappings.       */
#define AR_DEFN_EMBEDDED_RETURN  '\01'     /* character substituting for '\n' */
                                           /*  (record separator) in the DB   */
#define AR_DEFN_EMBEDDED_SEP     '\02'     /* character substituting for an */
                                           /*  embedded separator in the DB */
#define AR_DEFN_ALT_EMBEDDED_SEP '\04'     /* character subs for embedded     */
                                           /*  char if has meaning other than */
                                           /*  a mapping for something        */
#define AR_DEFN_EXPLICIT_NEWLINE '\05'     /* character substituting for '\n' */
                                           /*  while encrypting multiline     */
                                           /*  definition content */
#define AR_DEFN_EXPLICIT_RETURN  '\06'     /* character substituting for '\r' */
                                           /*  while encrypting multiline     */
                                           /*  definition content */
#define AR_DEFN_CONT_CHAR          '&'     /* line continuation character */

#define AR_DEFN_STRUCT_ACTIVE_LINK      "begin active link\n"
#define AR_DEFN_STRUCT_ADMIN_EXT        "begin admin ext\n"
#define AR_DEFN_STRUCT_CHAR_MENU        "begin char menu\n"
#define AR_DEFN_STRUCT_CONTAINER        "begin container\n"
#define AR_DEFN_STRUCT_DIST_MAPPING     "begin distributed mapping\n"
#define AR_DEFN_STRUCT_FILTER           "begin filter\n"
#define AR_DEFN_STRUCT_ESCALATION       "begin escalation\n"
#define AR_DEFN_STRUCT_GROUP            "begin group\n"
#define AR_DEFN_STRUCT_SCHEMA           "begin schema\n"
#define AR_DEFN_STRUCT_SCHEMA_DATA      "begin schema data\n"
#define AR_DEFN_STRUCT_DIST_POOL        "begin distributed pool\n"
#define AR_DEFN_STRUCT_VUI              "begin vui\n"
#define AR_DEFN_STRUCT_LOCK_BLOCK       "begin lock block\n"
#define AR_DEFN_STRUCT_APP              "begin application\n"
#define AR_DEFN_STRUCT_IMAGE            "begin image\n"

#define AR_DEFN_END_STRUCT              "end\n"

#define AR_DEFN_CLAUSE_FIELD            "field {\n"
#define AR_DEFN_CLAUSE_REFERENCE        "reference {\n"
#define AR_DEFN_CLAUSE_VUI              "vui  {\n"
#define AR_DEFN_END_CLAUSE              "}\n"
#define AR_DEFN_CLAUSE_ACTION           "   action {\n"
#define AR_DEFN_END_ACTION              "   }\n"
#define AR_DEFN_CLAUSE_ELSE             "   else {\n"
#define AR_DEFN_END_ELSE                "   }\n"
#define AR_DEFN_CLAUSE_FILE             "   support file {\n"
#define AR_DEFN_END_FILE                "   }\n"

/* above definitions without newline */

#define AR_DEFN_ENCRYPT_CHAR_SET        "  encrypt-char-set:  "
#define AR_DEFN_FILE_CHAR_SET           "char-set: "
#define AR_DEFN_FILE_EXPORT_TIMESTAMP   "export-timestamp: "

#define AR_DEFN_STRUCT_ACTIVE_LINK_NO_NL  "begin active link"
#define AR_DEFN_STRUCT_ADMIN_EXT_NO_NL    "begin admin ext"
#define AR_DEFN_STRUCT_CHAR_MENU_NO_NL    "begin char menu"
#define AR_DEFN_STRUCT_CONTAINER_NO_NL    "begin container"
#define AR_DEFN_STRUCT_DIST_MAPPING_NO_NL "begin distributed mapping"
#define AR_DEFN_STRUCT_FILTER_NO_NL       "begin filter"
#define AR_DEFN_STRUCT_ESCALATION_NO_NL   "begin escalation"
#define AR_DEFN_STRUCT_GROUP_NO_NL        "begin group"
#define AR_DEFN_STRUCT_SCHEMA_NO_NL       "begin schema"
#define AR_DEFN_STRUCT_SCHEMA_DATA_NO_NL  "begin schema data"
#define AR_DEFN_STRUCT_DIST_POOL_NO_NL    "begin distributed pool"
#define AR_DEFN_STRUCT_VUI_NO_NL          "begin vui"
#define AR_DEFN_STRUCT_LOCK_BLOCK_NO_NL   "begin lock block"
#define AR_DEFN_STRUCT_APP_NO_NL          "begin application"
#define AR_DEFN_STRUCT_IMAGE_NO_NL        "begin image"

#define AR_DEFN_END_STRUCT_NO_NL          "end"

#define AR_DEFN_CLAUSE_FIELD_NO_NL      "field {"
#define AR_DEFN_CLAUSE_REFERENCE_NO_NL  "reference {"
#define AR_DEFN_CLAUSE_VUI_NO_NL        "vui  {"
#define AR_DEFN_CLAUSE_VUI_NO_NL_ALT    "vui {"
#define AR_DEFN_END_CLAUSE_NO_NL        "}"
#define AR_DEFN_CLAUSE_ACTION_NO_NL     "   action {"
#define AR_DEFN_END_ACTION_NO_NL        "   }"
#define AR_DEFN_CLAUSE_ELSE_NO_NL       "   else {"
#define AR_DEFN_END_ELSE_NO_NL          "   }"
#define AR_DEFN_CLAUSE_FILE_NO_NL       "   support file {"
#define AR_DEFN_END_FILE_NO_NL          "   }"

#define AR_DEFN_LABEL_ACCESS_OPTION     "      access-opt  : "
#define AR_DEFN_LABEL_FIELD_CHAR_OPTION "      option      : "
#define AR_DEFN_LABEL_ACTLINK_FIELD     "   actlink-field  : "
#define AR_DEFN_LABEL_ACTLINK_FOCUS     "   actlink-focus  : "
#define AR_DEFN_LABEL_ACTLINK_CONTROL   "   actlink-control: "
#define AR_DEFN_LABEL_ACTLINK_MASK      "   actlink-mask   : "
#define AR_DEFN_LABEL_ACTLINK_QRY       "   actlink-query  : "
#define AR_DEFN_LABEL_ACTLINK_ORD       "   actlink-order  : "
#define AR_DEFN_LABEL_SVC_SERVER        "   service-server : "
#define AR_DEFN_LABEL_SVC_SCHEMA        "   service-schema : "
#define AR_DEFN_LABEL_SVC_RQST_MAP      "   svc-rqstId-map : "
#define AR_DEFN_LABEL_SVC_IN_FLD_MAP    "   svc-InFld-map  : "
#define AR_DEFN_LABEL_SVC_OUT_FLD_MAP   "   svc-OutFld-map : "
#define AR_DEFN_LABEL_SVC_SMPL_SERVER   " svc-sampleServer : "
#define AR_DEFN_LABEL_SVC_SMPL_SCHEMA   " svc-sampleSchema : "

#define AR_DEFN_LABEL_ALLOW_CODES       "   allow-codes    : "
#define AR_DEFN_LABEL_ADMIN_SUB_PERM    "   admin-sub-perm : "
#define AR_DEFN_LABEL_AD_COMMAND        "   command        : "
#define AR_DEFN_LABEL_CALLGUIDE         " call guide :"
#define AR_DEFN_LABEL_CHANGE_DIARY      "   change-diary   : "
#define AR_DEFN_LABEL_CHAR_MENU         "   char-menu      : "
#define AR_DEFN_LABEL_ENCR_CHAR_MENU    " encrypt-char-menu: "
#define AR_DEFN_LABEL_CHAR_MENU_2       "      char-menu   : "
#define AR_DEFN_LABEL_CLOSE_WND         "      close-wnd   : "
#define AR_DEFN_LABEL_CLOSE_WND_ALL     "      close-all   : "
#define AR_DEFN_LABEL_COMMAND           "      command     : "
#define AR_DEFN_LABEL_ENCR_COMMAND      "    encrypt-cmd   : "
#define AR_DEFN_LABEL_COMMIT_CHANGES    "    commit_changes: "
#define AR_DEFN_LABEL_CONTENT           "      content     : "
#define AR_DEFN_LABEL_CONTAINER_SUBADM  "   container-admin: "
#define AR_DEFN_LABEL_ADD_CONTAINER_SUBADM  "   add-ctnr-admn:   "
#define AR_DEFN_LABEL_CORE_VERS         "   core-version   : "
#define AR_DEFN_LABEL_UPGRD_VERS        "   upgrade-version: "
#define AR_DEFN_LABEL_CREATE_MODE       "   create-mode    : "
#define AR_DEFN_LABEL_FIELDOPTION       "   fieldOption    : "
#define AR_DEFN_LABEL_DATA              "   data           : "
#define AR_DEFN_LABEL_DATA_MAPPING      "   data-mapping   : "
#define AR_DEFN_LABEL_DATA_TYPE         "   datatype       : "
#define AR_DEFN_LABEL_DDE_ACTION        "      dde-action  : "
#define AR_DEFN_LABEL_DDE_COMMAND       "      dde-command : "
#define AR_DEFN_LABEL_DDE_FILE          "      dde-file    : "
#define AR_DEFN_LABEL_DDE_ITEM          "      dde-item    : "
#define AR_DEFN_LABEL_DDE_SERVICE       "      dde-service : "
#define AR_DEFN_LABEL_DDE_TOPIC         "      dde-topic   : "
#define AR_DEFN_LABEL_AUTO_SERVER       "      auto-server : "
#define AR_DEFN_LABEL_AUTO_CLSID        "      auto-clsId  : "
#define AR_DEFN_LABEL_AUTO_ACTION       "      auto-action : "
#define AR_DEFN_LABEL_AUTO_VISIBLE      "      auto-visible: "
#define AR_DEFN_LABEL_AUTO_COM          "      auto-COM    : "
#define AR_DEFN_LABEL_DIRECT_SQL        "      direct-sql  : "
#define AR_DEFN_LABEL_ENCR_AL_SQL       "      encrypt-sql : "
#define AR_DEFN_LABEL_DEFAULT           "   default        : "
#define AR_DEFN_LABEL_DEFAULT_VUI       "   default-vui    : "
#define AR_DEFN_LABEL_DESCRIPTION       "   description    : "
#define AR_DEFN_LABEL_DISPLAY           "   display        : "
#define AR_DEFN_LABEL_DISPLAY_2         "      display     : "
#define AR_DEFN_LABEL_DISPLAY_PROPLIST  "   display-prop   : "
#define AR_DEFN_LABEL_DISPLAY_INSTANCE  " display-instance : "
#define AR_DEFN_LABEL_DUP_ACTION        "   dup-action     : "
#define AR_DEFN_LABEL_PATTERN_MATCH     "   pat-match      : "
#define AR_DEFN_LABEL_REQUIRED_FIELDS   "   req-fields     : "
#define AR_DEFN_LABEL_ENABLE            "   enable         : "
#define AR_DEFN_LABEL_ENUM_VALUE        "   enum-value     : "
#define AR_DEFN_LABEL_ENUM_VALUE_NUM    "   enum-value-num : "
#define AR_DEFN_LABEL_ENUM_QRY_SCHEMA   "   enum-qry-schema: "
#define AR_DEFN_LABEL_ENUM_QRY_SERVER   "   enum-qry-server: "
#define AR_DEFN_LABEL_ENUM_QRY_QUERY    "   enum-qry-query : "
#define AR_DEFN_LABEL_ENUM_QRY_NAME     "   enum-qry-name  : "
#define AR_DEFN_LABEL_ENUM_QRY_NUM      "   enum-qry-num   : "
#define AR_DEFN_LABEL_TBLFLD_SCHEMA     "tablefield-schema : "
#define AR_DEFN_LABEL_TBLFLD_SERVER     "tablefield-server : "
#define AR_DEFN_LABEL_TBLFLD_QUERY      "tablefield-query  : "
#define AR_DEFN_LABEL_TBLFLD_NUMCOLS    "tablefield-numcols: "
#define AR_DEFN_LABEL_TBLFLD_MAXRET     "tablefield-maxret : "
#define AR_DEFN_LABEL_COLFLD_PARENT     "colfield-parent   : "
#define AR_DEFN_LABEL_COLFLD_DATAFIELD  "colfield-datafield: "
#define AR_DEFN_LABEL_COLFLD_DATATYPE   "colfield-datatype : "
#define AR_DEFN_LABEL_COLFLD_DATASOURCE "colfield-datasrc  : "
#define AR_DEFN_LABEL_COLFLD_COLLENGTH  "colfield-collength: "
#define AR_DEFN_LABEL_ESCALATION_HOUR   "   escl-hourmask  : "
#define AR_DEFN_LABEL_ESCALATION_INT    "   escl-interval  : "
#define AR_DEFN_LABEL_ESCALATION_MIN    "   escl-minute    : "
#define AR_DEFN_LABEL_ESCALATION_MON    "   escl-monthday  : "
#define AR_DEFN_LABEL_ESCALATION_QRY    "   escl-query     : "
#define AR_DEFN_LABEL_ESCALATION_TMTYPE "   escl-tmType    : "
#define AR_DEFN_LABEL_ESCALATION_WEEK   "   escl-weekday   : "
#define AR_DEFN_LABEL_EXCL_FLDS         "   exclude-fields : "
#define AR_DEFN_LABEL_EXPORT_VERS       "   export-version : "

#define AR_DEFN_LABEL_EXT_NAME          "   ext-name       : "
#define AR_DEFN_LABEL_EXT_FIELD         "   ext-field      : "
#define AR_DEFN_LABEL_EXT_TABLE         "   ext-table      : "
#define AR_DEFN_LABEL_FIELD_TYPE        "   fieldtype      : "
#define AR_DEFN_LABEL_FIELD_REF         "      field-ref   : "
#define AR_DEFN_LABEL_FILE_TYPE         "      file-type   : "
#define AR_DEFN_LABEL_FILTER_OP         "   filter-op      : "
#define AR_DEFN_LABEL_FILTER_ORD        "   filter-order   : "
#define AR_DEFN_LABEL_FILTER_QRY        "   filter-query   : "
#define AR_DEFN_LABEL_FOCUS             "      focus       : "
#define AR_DEFN_LABEL_FROM_SCHEMA       "   from-schema    : "
#define AR_DEFN_LABEL_FROM_SERVER       "   from-server    : "
#define AR_DEFN_LABEL_FULLTEXTOPTNS     "   fulltext-optns : "
#define AR_DEFN_LABEL_FUNC_CODES        "   func-codes     : "
#define AR_DEFN_LABEL_GET_LIST_FLDS     "   get-list-flds  : "
#define AR_DEFN_LABEL_HELP              "   help-text      : "
#define AR_DEFN_LABEL_ID                "   id             : "
#define AR_DEFN_LABEL_ID_2              "      id          : "
#define AR_DEFN_LABEL_INDEX             "   index          : "
#define AR_DEFN_LABEL_ADD_INDEX         "   add-index      : "
#define AR_DEFN_LABEL_JOIN_OPTION       "      join-option : "
#define AR_DEFN_LABEL_JOIN_PRIMARY      "      primary     : "
#define AR_DEFN_LABEL_JOIN_QRY          "      join-query  : "
#define AR_DEFN_LABEL_JOIN_SECONDARY    "      secondary   : "
#define AR_DEFN_LABEL_LABEL             "   label          : "
#define AR_DEFN_LABEL_LAST_CHANGED      "   last-changed   : "
#define AR_DEFN_LABEL_LENGTH_UNITS      "   length-units   : "
#define AR_DEFN_LABEL_CLOB_STORE_OPT    "   clob-store-opt : "
#define AR_DEFN_LABEL_LOG_FILE          "      log-file    : "
#define AR_DEFN_LABEL_MACRO_NAME        "      macro-name  : "
#define AR_DEFN_LABEL_MACRO_PARMS       "      macro-parms : "
#define AR_DEFN_LABEL_MACRO_TEXT        "      macro-text  : "
#define AR_DEFN_LABEL_MAP_FIELDID       "      mapfield    : "
#define AR_DEFN_LABEL_MAP_SCHEMA        "      mapschema   : "
#define AR_DEFN_LABEL_MAP_TYPE          "   map-type       : "
#define AR_DEFN_LABEL_MAPPING           "   mapping        : "
#define AR_DEFN_LABEL_MATCH_QUAL        "   match-qual     : "
#define AR_DEFN_LABEL_MAX_DATE          "   maxDate        : "
#define AR_DEFN_LABEL_MAX_LENGTH        "   maxlength      : "
#define AR_DEFN_LABEL_MAXSIZE           "   maxsize        : "
#define AR_DEFN_LABEL_MIN_DATE          "   minDate        : "
#define AR_DEFN_LABEL_ATTACH_TYPE       "   attachtype     : "
#define AR_DEFN_LABEL_MENU_STYLE        "   menu-style     : "
#define AR_DEFN_LABEL_MSG_NUM           "      message-num : "
#define AR_DEFN_LABEL_MSG_TEXT          "      message-text: "
#define AR_DEFN_LABEL_MSG_TYPE          "      message-type: "
#define AR_DEFN_LABEL_MSG_PANE          "      message-pane: "
#define AR_DEFN_LABEL_NAME              "   name           : "
#define AR_DEFN_LABEL_NOT_FIELDS        "      notify-field: "
#define AR_DEFN_LABEL_NOT_MECH          "      notify-mech : "
#define AR_DEFN_LABEL_NOT_PRIORITY      "      notify-pri  : "
#define AR_DEFN_LABEL_NOT_SUBJECT       "      notify-subj : "
#define AR_DEFN_LABEL_NOT_TEXT          "      notify-text : "
#define AR_DEFN_LABEL_NOT_USER          "      notify-user : "
#define AR_DEFN_LABEL_NOT_XREF          "      notify-xref : "
#define AR_DEFN_LABEL_NOT_BEHAVIOR      "      notify-behvr: "
#define AR_DEFN_LABEL_NOT_PERMISSION    "      notify-perm : "
#define AR_DEFN_LABEL_NOT_ADV_REPLY_TO  "      notify-reply: "
#define AR_DEFN_LABEL_NOT_ADV_FROM      "      notify-from : "
#define AR_DEFN_LABEL_NOT_ADV_CC        "      notify-cc   : "
#define AR_DEFN_LABEL_NOT_ADV_BCC       "      notify-bcc  : "
#define AR_DEFN_LABEL_NOT_ADV_ORG       "      notify-org  : "
#define AR_DEFN_LABEL_NOT_ADV_MAILBOX   "      notify-mlbox: "
#define AR_DEFN_LABEL_NOT_ADV_HDR_TMP   "      notify-hdrtm: "
#define AR_DEFN_LABEL_NOT_ADV_FTR_TMP   "      notify-ftrtm: "
#define AR_DEFN_LABEL_NOT_ADV_CNT_TMP   "      notify-cnttm: "
#define AR_DEFN_LABEL_NUM_FIELDS        "   num-fields     : "
#define AR_DEFN_LABEL_NUM_REFERENCES    "   num-references : "
#define AR_DEFN_LABEL_NUM_VUIS          "   num-vuis       : "
#define AR_DEFN_LABEL_STRUCTITEM_LIST   "  struct-item-list: "
#define AR_DEFN_LABEL_ENCR_TEXT         "  encrypt-text    : "
#define AR_DEFN_LABEL_CHECKSUM          "  checksum        : "
#define AR_DEFN_LABEL_OBJECT            "   object         : "
#define AR_DEFN_LABEL_OBJECT_PROP       "   object-prop    : "
#define AR_DEFN_LABEL_ENCR_OBJECT_PROP  "  encrypt-obj-prop: "
#define AR_DEFN_LABEL_OBJECT_PROP_INTERVAL "   interval       : "

#define AR_DEFN_LABEL_OPEN_DLG          "   open-dialog    : "
#define AR_DEFN_LABEL_OPEN_DLG_SERVER   "      open-server : "
#define AR_DEFN_LABEL_OPEN_DLG_SCHEMA   "      open-schema : "
#define AR_DEFN_LABEL_OPEN_DLG_VUI      "      open-vui    : "
#define AR_DEFN_LABEL_OPEN_DLG_BOX      "      open-close  : "
#define AR_DEFN_LABEL_OPEN_DLG_INPUT    "      open-input  : "
#define AR_DEFN_LABEL_OPEN_DLG_OUTPUT   "      open-output : "
#define AR_DEFN_LABEL_OPEN_DLG_WINMODE  "      open-winmod : "
#define AR_DEFN_LABEL_OPEN_DLG_TARGET   "      open-target : "
#define AR_DEFN_LABEL_OPEN_DLG_QUERY    "      open-query  : "
#define AR_DEFN_LABEL_OPEN_DLG_CONTINU  "      open-continu: "
#define AR_DEFN_LABEL_OPEN_DLG_SUPPRESS "      open-suppres: "
#define AR_DEFN_LABEL_OPEN_DLG_MSG_TYPE "      open-msgtype: "
#define AR_DEFN_LABEL_OPEN_DLG_MSG_NUM  "      open-msgnum : "
#define AR_DEFN_LABEL_OPEN_DLG_MSG_PANE "      open-msgpane: "
#define AR_DEFN_LABEL_OPEN_DLG_MSG_TEXT "      open-msgtext: "
#define AR_DEFN_LABEL_OPEN_DLG_POLLINT  "      open-pollint: "
#define AR_DEFN_LABEL_OPEN_DLG_RPTSTR   "      open-rptstr : "
#define AR_DEFN_LABEL_OPEN_DLG_SORTORD  "      open-sortord: "

#define AR_DEFN_LABEL_CALLGUIDE_SERVER  "      call-server : "
#define AR_DEFN_LABEL_CALLGUIDE_GUIDE   "      call-guide  : "
#define AR_DEFN_LABEL_CALLGUIDE_MODE    "      call-mode   : "
#define AR_DEFN_LABEL_CALLGUIDE_TABLEID "      call-tableid: "
#define AR_DEFN_LABEL_CALLGUIDE_INPUT   "      call-input  : "
#define AR_DEFN_LABEL_CALLGUIDE_OUTPUT  "      call-output : "

#define AR_DEFN_LABEL_EXITGUIDE         "      exit guide  : "
#define AR_DEFN_LABEL_GOTOGUIDE         "      goto guide  : "
#define AR_DEFN_LABEL_WAIT              "      wait        : "
#define AR_DEFN_LABEL_GOTOACTION        "      goto action : "

#define AR_DEFN_LABEL_OPTION            "   option         : "
#define AR_DEFN_LABEL_OWNER             "   owner          : "
#define AR_DEFN_LABEL_CONTAINER_OWNER   "   owning-obj     : "
#define AR_DEFN_LABEL_ADD_CONTAINER_OWNER  "   add-owning-obj : "
#define AR_DEFN_LABEL_CONTAINER_OWNER_NAME "   owning-obj-name: "
#define AR_DEFN_LABEL_CONTAINER_OWNER_TYPE "   owning-obj-type: "
#define AR_DEFN_LABEL_CONTAINER_NUM_OWNER  "   num-owning-obj : "
#define AR_DEFN_LABEL_PATTERN           "   pattern        : "
#define AR_DEFN_LABEL_PERMISSION        "   permission     : "
#define AR_DEFN_LABEL_ADD_PERMISSION    "   add-permission : "
#define AR_DEFN_LABEL_PRECISION         "   precision      : "
#define AR_DEFN_LABEL_REFERENCE_GROUPS  "   ref-groups     : "
#define AR_DEFN_LABEL_QBE_MATCH_OP      "   qbe-match-op   : "
#define AR_DEFN_LABEL_PUSH_FIELD        "      push-field  : "
#define AR_DEFN_LABEL_SAMPLE_SERVER     "      samp-server : "
#define AR_DEFN_LABEL_SAMPLE_SCHEMA     "      samp-schema : "
#define AR_DEFN_LABEL_SAMPLE_GUIDE      "      samp-guide  : "
#define AR_DEFN_LABEL_ENCR_FIELDP       "encrypt-push-field: "
#define AR_DEFN_LABEL_RANGE_HIGH        "   range-high     : "
#define AR_DEFN_LABEL_RANGE_LOW         "   range-low      : "
#define AR_DEFN_LABEL_REFRESH_CODE      "   refresh-code   : "
#define AR_DEFN_LABEL_RETRY_TIME        "   retry-time     : "
#define AR_DEFN_LABEL_RTN_EXCL_FLDS     "rtn-exclude-fields: "
#define AR_DEFN_LABEL_RTN_MAP_TYPE      "   rtn-map-type   : "
#define AR_DEFN_LABEL_RTN_MAPPING       "   rtn-mapping    : "
#define AR_DEFN_LABEL_WK_CONN_TYPE      "   wk-conn-type   : "
#define AR_DEFN_LABEL_NEXT_FIELD_ID     "   next-field-id  : "
#define AR_DEFN_LABEL_SCHEMA_NAME       "   schema-name    : "
#define AR_DEFN_LABEL_ADD_SCHEMA_NAME   "   add-schema-name: "
#define AR_DEFN_LABEL_SCHEMA_TYPE       "   schema-type    : "
#define AR_DEFN_LABEL_SCHEMA_SUBADM     "   schema-admin   : "
#define AR_DEFN_LABEL_ADD_SCHEMA_SUBADM "   add-schema-admn: "
#define AR_DEFN_LABEL_SET_FIELD         "      set-field   : "
#define AR_DEFN_LABEL_ENCR_SET_FIELD    " encrypt-set-field: "
#define AR_DEFN_LABEL_SMOPROP_LIST      "   obj-props      : "
#define AR_DEFN_LABEL_SORT_LIST         "   sort-list      : "
#define AR_DEFN_LABEL_TIMESTAMP         "   timestamp      : "
#define AR_DEFN_LABEL_TIMESTAMP_2       "      timestamp   : "
#define AR_DEFN_LABEL_TO_SCHEMA         "   to-schema      : "
#define AR_DEFN_LABEL_TO_SERVER         "   to-server      : "
#define AR_DEFN_LABEL_TRANSFER_MODE     "   transfer-mode  : "
#define AR_DEFN_LABEL_TYPE              "   type           : "
#define AR_DEFN_LABEL_UPDATE_CODE       "   update-code    : "
#define AR_DEFN_LABEL_VIEW_KEYFIELD     "      key-field   : "
#define AR_DEFN_LABEL_VIEW_NAME         "      ext-table   : "
#define AR_DEFN_LABEL_VIEW_QRY          "      view-query  : "
#define AR_DEFN_LABEL_VALUE             "   value          : "
#define AR_DEFN_LABEL_DISTRIB_TCOUNT    "   thread-count   : "
#define AR_DEFN_LABEL_DISTRIB_CONNECT   "   connection     : "
#define AR_DEFN_LABEL_VUI_LOCALE        "   vui-locale     : "
#define AR_DEFN_LABEL_VUI_TYPE          "   vui-type       : "
#define AR_DEFN_LABEL_POLLING           "   polling        : "
#define AR_DEFN_LABEL_POLLING_INTERVAL  " polling-interval : "

#define AR_DEFN_LABEL_ARCHIVEINFO       "   archive        : "
#define AR_DEFN_LABEL_ARCHIVEINFO_TIME  "      arch-time   : "
#define AR_DEFN_LABEL_ARCHIVEINFO_QRY   "      arch-query  : "
#define AR_DEFN_LABEL_ARCHIVEINFO_FROM  "      arch-from   : "

#define AR_DEFN_LABEL_AUDITINFO         "   audit          : "
#define AR_DEFN_LABEL_AUDITINFO_QRY     "      audt-query  : "
#define AR_DEFN_LABEL_AUDITINFO_FORM    "      audt-form   : "

#define AR_DEFN_LABEL_ERRORHANDLER_OPTIONS "   errhandler-opt : "
#define AR_DEFN_LABEL_ERRORHANDLER_NAME "   errhandler-name: "

/* Labels for image objects*/
#define AR_DEFN_LABEL_IMAGE_SIZE        "   imageSize      : "
#define AR_DEFN_LABEL_IMAGE_TYPE        "   imageType      : "
#define AR_DEFN_LABEL_IMAGE_CONTENT     "   imageContent   : "
#define AR_DEFN_LABEL_IMAGE_CHECKSUM    "   imageChecksum  : "

/* The time difference to write the license check sum */
#define AR_LICENSE_USAGE_RECORDING      "License-Usage-Recording:"
/* Maximum number of open connections allowed */
#define AR_MAX_CLIENT_MANAGED_TRANSACTIONS   "Maximum-Concurrent-Client-Managed-Transactions:"
/* Time without use before the server will roll back a client managed transaction */
#define AR_CLIENT_MANAGED_TRANSACTIONS_TIMEOUT   "Client-Managed-Transaction-Timeout:"

/* Constants used for processing the directory files */
#define AR_DIR_LABEL_ACTLINK_DIR             "Active-Link-Dir:"
#define AR_DIR_LABEL_ACTLINK_SHELL           "Active-Link-Shell:"
#define AR_DIR_LABEL_ADMIN_ONLY              "Admin-Only-Mode:"
#define AR_DIR_LABEL_ARERROR_EXCEPTION_LIST  "Arerror-Exception-List:"
#define AR_DIR_LABEL_ARF_JAVA_CLASS_PATH     "ARF-Java-Class-Path:"
#define AR_DIR_LABEL_ARF_JAVA_VM_OPTIONS     "ARF-Java-VM-Options:"
#define AR_DIR_LABEL_ARFORK_LOG_FILE         "Arfork-Log-File:"
#define AR_DIR_LABEL_ARSIGNALD_LOG_FILE      "Arsignald-Log-File:"
#define AR_DIR_LABEL_AS_SPEC_PORT            "Admin-Specific-Port:"
#define AR_DIR_LABEL_ALERT_CHECK_USERS       "Alert-Check-Users:"
#define AR_DIR_LABEL_ALERT_CONNECT_RETRIES   "Alert-Connect-Retries:"
#define AR_DIR_LABEL_ALERT_IGNORE_ACTUAL_IP  "Alert-Ignore-Actual-Client-IP:"
#define AR_DIR_LABEL_ALERT_LOG_FILE          "Alert-Log-File:"
#define AR_DIR_LABEL_ALERT_OUTBOUND_PORT     "Alert-Outbound-Port:"
#define AR_DIR_LABEL_ALERT_SEND_TIMEOUT      "Alert-Send-Timeout:"
#define AR_DIR_LABEL_ALLOW_GUEST             "Allow-Guest-Users:"
#define AR_DIR_LABEL_ALLOW_BACKQUOTE_IN_PROCESS "Allow-Backquote-In-Process-String:"
#define AR_DIR_LABEL_UNQUAL_QUERIES          "Allow-Unqual-Queries:"
#define AR_DIR_LABEL_API_LOG_FILE            "API-Log-File:"
#define AR_DIR_LABEL_STATS_APISQL_CONTROL    "API-SQL-Stats-Control:"
#define AR_DIR_LABEL_STATS_APISQL_MAX_SAVED  "API-SQL-Stats-Max-Saved-Long-Operations:"
#define AR_DIR_LABEL_STATS_APISQL_INTERVAL   "API-SQL-Stats-Flush-To-DB-Interval:"
#define AR_DIR_LABEL_STATS_APISQL_MIN_TIME   "API-SQL-Stats-Minimum-Elapsed-Time:"
#define AR_DIR_LABEL_APPLICATION_AUDIT       "Application-Audit-Info:"
#define AR_DIR_LABEL_APPLICATION_ENABLE      "Application-Enable:"
#define AR_DIR_LABEL_APPLICATION_TAG         "Application-Tag:"
#define AR_DIR_LABEL_AP_DEFN_CHECK_INT       "Approval-Defn-Check-Interval:"
#define AR_DIR_LABEL_APPROVAL_LOG_FILE       "Approval-Log-File:"
#define AR_DIR_LABEL_APPROVAL_NOTIFY         "Approval-Notify:"
#define AR_DIR_LABEL_AP_RPC_SOCKET           "Approval-RPC-Socket:"
#define AR_DIR_LABEL_AP_SPEC_PORT            "Approval-Specific-Port:"
#define AR_DIR_LABEL_AP_WEB_DOC_DIR          "Approval-Web-Doc-Dir:"
#define AR_DIR_LABEL_AP_DUE_SOON_INT         "Approval-Due-Soon:"
#define AR_DIR_LABEL_AP_RECENT_HISTORY_INT   "Approval-Recent-History:"
#define AR_DIR_LABEL_MAX_ATTACH_SIZE         "AR-Max-Attach-Size:"
#define AR_DIR_LABEL_ATRIUMSSO_ADMIN_PASSWORD "Atrium-SSO-Admin-Password:"
#define AR_DIR_LABEL_ATRIUMSSO_ADMIN_USER    "Atrium-SSO-Admin-User:"
#define AR_DIR_LABEL_ATRIUMSSO_LOCATION      "Atrium-SSO-Location:"
#define AR_DIR_LABEL_ATRIUMSSO_KEYSTORE_PATH "Atrium-SSO-Keystore-Path:"
#define AR_DIR_LABEL_ATRIUMSSO_KEYSTORE_PASSWORD "Atrium-SSO-Keystore-Password:"
#define AR_DIR_LABEL_AUTH_CHAINING_MODE      "Authentication-Chaining-Mode:"
#define AR_DIR_LABEL_CACHE_MODE              "Cache-Mode:"
#define AR_DIR_LABEL_CACHE_DISP_PROP         "Cache-Display-Properties:"
#define AR_DIR_LABEL_CANCEL_QUERY            "Cancel-Query-Option:"
#define AR_DIR_LABEL_CE_DEADLOCK_RETRIES     "Create-Entry-DeadLock-Retries:"
#define AR_DIR_LABEL_CE_DEADLOCK_RETRY_DELAY "Create-Entry-DeadLock-Retry-Delay:"
#define AR_DIR_LABEL_CMDB_INSTALL_DIR        "CMDB-Install-Directory:"
#define AR_DIR_LABEL_NO_CHANGED_CHECK        "Changed-By-Another-Check:"
#define AR_DIR_LABEL_CLUSTERED_INDEX         "Clustered-Index:"
#define AR_DIR_LABEL_COMPUTED_GROUP_LOGGING  "Computed-Group-Logging:"
#define AR_DIR_LABEL_CREATE_WORKFLOW_PLACEHOLDER "Create-Workflow-Placeholders:"
#define AR_DIR_LABEL_XREF_PASSWD             "Crossref-Blank-Password:"
#define AR_DIR_LABEL_CURRENCY_INTERVAL       "Currency-Ratio-Client-Refresh-Interval:"
#define AR_DIR_LABEL_DB_CASE_INSENSITIVE     "Db-Case-Insensitive:"
#define AR_DIR_LABEL_DB_CHAR_SET             "Db-Character-Set:"
#define AR_DIR_LABEL_DB_CONNECTION_RETRIES   "Db-Connection-Retries:"
#define AR_DIR_LABEL_DB_CONNECTION_TIMEOUT   "Db-Connection-Timeout:"
#define AR_DIR_LABEL_DB_DIR                  "Dbhome-directory:"
#define AR_DIR_LABEL_DB_MAX_TEXT_SIZE        "Db-Max-Text-Size:"
#define AR_DIR_LABEL_DB_MAX_ATTACH_SIZE      "Db-Max-Attach-Size:"
#define AR_DIR_LABEL_DB_NAME                 "Db-name:"
#define AR_DIR_LABEL_DB_PASSWORD             "Db-password:"
#define AR_DIR_LABEL_DB_USER                 "Db-user:"
#define AR_DIR_LABEL_DEBUG_GROUPID           "Debug-GroupId:"
#define AR_DIR_LABEL_DEBUG_MODE              "Debug-mode:"
#define AR_DIR_LABEL_DB2_DATABASE_ALIAS      "DB2-Database-Alias:"
#define AR_DIR_LABEL_DB2_SERVER              "DB2-Server-Name:"
#define AR_DIR_LABEL_DFLT_ALLOW_CURRENCIES   "Default-Allowable-Currencies:"
#define AR_DIR_LABEL_DFLT_FUNC_CURRENCIES    "Default-Functional-Currencies:"
#define AR_DIR_LABEL_DEFAULT_ORDER_BY        "Default-Order-By:"
#define AR_DIR_LABEL_DEFAULT_WEB_PATH        "Default-Web-Path:"
#define AR_DIR_LABEL_DELAY_RECACHE_TIME      "Delay-Recache-Time:"
#define AR_DIR_LABEL_DISABLE_ADMIN_OPS       "Disable-Admin-Ops:"
#define AR_DIR_LABEL_DISABLE_ALERTS          "Disable-Alerts:"
#define AR_DIR_LABEL_DISABLE_ARCHIVE         "Disable-Archive:"
#define AR_DIR_LABEL_DISABLE_ARSIGNALS       "Disable-ARSignals:"
#define AR_DIR_LABEL_DISABLE_AUDIT_ONLY_FIELDS "Disable-Audit-Only-Changed-Fields:"
#define AR_DIR_LABEL_DISABLE_CLIENT_OP       "Disable-Client-Operation:"
#define AR_DIR_LABEL_DISABLE_ESCALATIONS     "Disable-Escalations:"
#define AR_DIR_LABEL_DISABLE_NON_UNICODE_CLIENTS "Disable-Non-Unicode-Clients:"
#define AR_DIR_LABEL_DELAYED_CACHE           "Disable-Shared-Cache-Delay:"
#define AR_DIR_LABEL_SHARED_MEM              "Disable-Shared-Memory:"
#define AR_DIR_LABEL_USER_CACHE_UTILS        "Disable-User-Cache-Utilities:"
#define AR_DIR_LABEL_DISABLE_THREAD_RESTART  "Disable-Thread-Restart:"
#define AR_DIR_LABEL_GENERAL_AUTH_ERR        "Display-General-Auth-Message:"
#define AR_DIR_LABEL_DISTRIB_LOG_FILE        "Distrib-Log-File:"
#define AR_DIR_LABEL_DS_RPC_SOCKET           "Distributed-RPC-Socket:"
#define AR_DIR_LABEL_DOMAIN_NAME             "Domain-Name:"
#define AR_DIR_LABEL_DSO_CACHE_CHK_INTERVAL  "DSO-Cache-Check-Interval:"
#define AR_DIR_LABEL_DSO_ERROR_RETRY_OPTION  "DSO-Error-Retry-Option:"
#define AR_DIR_LABEL_DSO_HOST_NAME           "DSO-Host-Name:"
#define AR_DIR_LABEL_DSO_RPC_SOCKET          "DSO-Local-RPC-Socket:"
#define AR_DIR_LABEL_DSO_LOG_LEVEL           "DSO-Log-Level:"
#define AR_DIR_LABEL_DSO_MAIN_POLL_INTERVAL  "DSO-Main-Thread-Polling-Interval:"
#define AR_DIR_LABEL_DSO_PEND_RETRY_FL       "DSO-Mark-Pending-Retry-Flag:"
#define AR_DIR_LABEL_DSO_MAX_QUERY_SIZE      "DSO-Max-Pending-Records-Per-Query:"
#define AR_DIR_LABEL_DSO_MERGE_STYLE         "DSO-Merge-DupId-Overwrite:"
#define AR_DIR_LABEL_DSO_PLACEHOLDER         "DSO-Placeholder-Mode:"
#define AR_DIR_LABEL_DSO_POLL_INTERVAL       "DSO-Polling-Interval:"
#define AR_DIR_LABEL_DSO_DEST_PORT           "DSO-private-dest-port:"
#define AR_DIR_LABEL_DSO_REDIRECTOR_MODE     "DSO-Redirector-Mode:"
#define AR_DIR_LABEL_DSO_SOURCE_SERVER       "DSO-Source-Server:"
#define AR_DIR_LABEL_DSO_SUPPRESS_NO_SUCH_ENTRY_FOR_DELETE   "DSO-Suppress-No-Such-Entry-For-Delete:"
#define AR_DIR_LABEL_DSO_TARGET_CONNECT      "DSO-Target-Connection:"
#define AR_DIR_LABEL_DSO_TARGET_PASSWD       "DSO-Target-Password:"
#define AR_DIR_LABEL_DSO_TIMEOUT_NORMAL      "DSO-Timeout-Normal:"
#define AR_DIR_LABEL_DSO_USER_PASSWD         "DSO-User-Password:"
#define AR_DIR_LABEL_EMAIL_SYSTEM            "Email-Delivery-System:"
#define AR_DIR_LABEL_EMAIL_FROM              "Email-Notify-From:"
#define AR_DIR_LABEL_EMAIL_TIMEOUT           "Email-Timeout:"
#define AR_DIR_LABEL_EMAIL_NOTIFY_MAILBOX_ID "Email-Notification-MailboxID:"
#define AR_DIR_LABEL_EMAIL_IMPORT_BY_DEFAULT "Email-Import-Form-By-Default:"
#define AR_DIR_LABEL_EMAIL_AIX_USE_OLD_EMAIL "Email-AIX-Use-Old-System:"
#define AR_DIR_LABEL_SHARED_CACHE            "Enable-Shared-Cache:"
#define AR_DIR_LABEL_ENCR_AL_SQL             "Encrypt-AL-Direct-SQL:"
#define AR_DIR_LABEL_ENC_DATA_ENCR_ALG       "Encrypt-Data-Encryption-Algorithm:"
#define AR_DIR_LABEL_ENC_DATA_KEY_EXP        "Encrypt-Symmetric-Data-Key-Expire:"
#define AR_DIR_LABEL_ENC_PUB_KEY_ALG         "Encrypt-Public-Key-Algorithm:"
#define AR_DIR_LABEL_ENC_PUB_KEY_EXP         "Encrypt-Public-Key-Expire:"
#define AR_DIR_LABEL_ENC_SEC_POLICY          "Encrypt-Security-Policy:"
#define AR_DIR_LABEL_ENC_SESS_H_ENTRIES      "Encrypt-Session-Hash-Entries:"
#define AR_DIR_LABEL_ENV_VARIABLE            "Environment-variable:"
#define AR_DIR_LABEL_ESCALATION_DAEMON       "Escalation-Daemon:"
#define AR_DIR_LABEL_ESCALATION_LOG_FILE     "Escalation-Log-File:"
#define AR_DIR_LABEL_ES_SPEC_PORT            "Escalation-Specific-Port:"
#define AR_DIR_LABEL_EXCEPTION_DIAGNOSTIC_OPTION  "Exception-Diagnostic-Option:"
#define AR_DIR_LABEL_EXPORT_SVR_OPS          "Export-Server-Operations:"
#define AR_DIR_LABEL_EA_RETURN_DATA          "External-Authentication-Return-Data-Capabilities:"
#define AR_DIR_LABEL_EA_RPC_SOCKET           "External-Authentication-RPC-Socket:"
#define AR_DIR_LABEL_EA_RPC_TIMEOUT          "External-Authentication-RPC-Timeout:"
#define AR_DIR_LABEL_EA_SYNC_TIMEOUT         "External-Authentication-Sync-Timeout:"
#define AR_DIR_LABEL_EA_IGNORE_EXCESS_GROUPS "External-Authentication-Ignore-Excess-Groups:"
#define AR_DIR_LABEL_EA_GROUP_MAPPING        "External-Authentication-Group-Mapping:"
#define AR_DIR_LABEL_EA_ATRIUM_SSO           "External-Authentication-Atrium-SSO:"
#define AR_DIR_LABEL_FS_SPEC_PORT            "Fast-Specific-Port:"
#define AR_DIR_LABEL_FORCE_PASSWORD_CHANGE   "Force-Password-Change:"
#define AR_DIR_LABEL_APPLICATION_FIELDID     "Field-Id:"
#define AR_DIR_LABEL_FILTER_API_RPC_TIMEOUT  "Filter-Api-Timeout:"
#define AR_DIR_LABEL_FILT_MAX_STACK          "Filter-Max-Stack:"
#define AR_DIR_LABEL_FILT_MAX_TOTAL          "Filter-Max-Total:"
#define AR_DIR_LABEL_FILTER_LOG_FILE         "Filter-Log-File:"
#define AR_DIR_LABEL_FLASH_DAEMON            "Flashboards-Daemon:"
#define AR_DIR_LABEL_FLASH_SPEC_PORT         "Flashboards-Specific-Port:"
#define AR_DIR_LABEL_FLUSH_LOG_LINES         "Flush-Log-Lines:"
#define AR_DIR_LABEL_FT_CASE_OPTION          "Full-Text-Case-Option:"
#define AR_DIR_LABEL_FT_COLLECTION_DIR       "Full-Text-Collection-Directory:"
#define AR_DIR_LABEL_FT_CONFIGURATION_DIR    "Full-Text-Configuration-Directory:"
#define AR_DIR_LABEL_FT_DISABLE_INDEXING     "Full-Text-Disable-Indexing:"
#define AR_DIR_LABEL_FT_DISABLE_SEARCHING    "Full-Text-Disable-Searching:"
#define AR_DIR_LABEL_FT_INDEXER_LOG_FILE     "Full-Text-Indexer-Log-File:"
#define AR_DIR_LABEL_FT_INDEXER_OPTIMIZE     "Full-Text-Indexer-Optimize-Threshold:"
#define AR_DIR_LABEL_FT_INDEXER_RECOVERY     "Full-Text-Indexer-Recovery-Interval:"
#define AR_DIR_LABEL_FT_INDEXER_SIGNAL_DELAY "Full-Text-Indexer-Signal-Delay:"
#define AR_DIR_LABEL_FT_LICENSE_TIMEOUT      "Full-Text-License-Timeout:"
#define AR_DIR_LABEL_FT_MATCH_OPTION         "Full-Text-Match-Option:"
#define AR_DIR_LABEL_FT_MAX_FIELD_LENGTH     "Full-Text-Max-Field-Data-Length:"
#define AR_DIR_LABEL_FT_LOCAL_MODE           "Full-Text-Mode:"
#define AR_DIR_LABEL_FT_THRESHOLD_HIGH       "Full-Text-Search-Threshold-High:"
#define AR_DIR_LABEL_FT_THRESHOLD_LOW        "Full-Text-Search-Threshold-Low:"
#define AR_DIR_LABEL_FT_SEARCH_THRESHOLD     "Full-Text-Search-Threshold:"
#define AR_DIR_LABEL_FT_2ARY_PLUGIN_PORT     "Full-Text-Secondary-Plugin-Port:"
#define AR_DIR_LABEL_FT_SERVER_NAME          "Full-Text-Server-Name:"
#define AR_DIR_LABEL_FT_SERVER_PORT          "Full-Text-Server-Port:"
#define AR_DIR_LABEL_FT_TEMP_DIR             "Full-Text-Temp-Directory:"
#define AR_DIR_LABEL_DATE_FORMAT             "GetListEntry-Server-Date-Format:"
#define AR_DIR_LABEL_GUEST_RESTRICT_READ     "Guest-Restricted-Read:"
#define AR_DIR_LABEL_GUID_PREFIX             "GUID-Prefix:"
#define AR_DIR_LABEL_HOMEPAGE_FORM           "Homepage-Form:"
#define AR_DIR_LABEL_INIT_FORM               "Init-Form:"
#define AR_DIR_LABEL_INFORMIX_DBN            "Informix-DBServer-Name:"
#define AR_DIR_LABEL_INFORMIX_RELAY_MOD      "Informix-Relay-Module:"
#define AR_DIR_LABEL_INFORMIX_TBC            "Informix-TBConfig:"
#define AR_DIR_LABEL_IP_NAME                 "IP-Name:"
#define AR_DIR_LABEL_USER_INFO_LISTS         "Internal-User-Info-Hash-Lists:"
#define AR_DIR_LABEL_USER_INST_TIMEOUT       "Internal-User-Instance-Timeout:"
#define AR_DIR_LABEL_LIC_TIMEOUT             "License-Timeout:"
#define AR_DIR_LABEL_LICENSE_TAG             "License-Tag:"
#define AR_DIR_LABEL_LS_SPEC_PORT            "List-Specific-Port:"
#define AR_DIR_LABEL_LOAD_SHARED_LIB         "Load-Shared-Library:"
#define AR_DIR_LABEL_LOAD_SHARED_LIB_PATH    "Load-Shared-Library-Path:"
#define AR_DIR_LABEL_LOCALE_LIST             "Locale-List:"
#define AR_DIR_LABEL_LOCALIZED_MSGS_CACHE    "Localized-Messages-To-Cache:"
#define AR_DIR_LABEL_LOCALIZED_SERVER        "Localized-Server:"
#define AR_DIR_LABEL_LOCKED_WFLW_LOG_MODE    "Locked-Workflow-Log-Mode:"
#define AR_DIR_LABEL_DSO_LOG_ERR_FORM        "Log-DSO-Errors-To-Form:"
#define AR_DIR_LABEL_DSO_LOG_FIELDS_VALUES   "Log-DSO-Field-Values:"
#define AR_DIR_LABEL_LOGFILE_APPEND          "Log-File-Append:"
#define AR_DIR_LABEL_LOGFORMSELECTED         "Log-Form-Selected:"
#define AR_DIR_LABEL_LOGTOFORM               "Log-To-Form:"
#define AR_DIR_LABEL_EMAIL_NOTIFY_DIR        "MailNotifyDir:"
#define AR_DIR_LABEL_MAP_IP_ADDR             "Map-IP-Address:"
#define AR_DIR_LABEL_MAX_AUDIT_LOG_FILE_SIZE "Max-Audit-Log-File-Size:"
#define AR_DIR_LABEL_MAX_ENTRIES_SEARCH_MENU "Max-Entries-Per-Search-Menu:"
#define AR_DIR_LABEL_MAX_ENTRIES             "Max-Entries-Per-Query:"
#define AR_DIR_LABEL_MAX_F_DAEMONS           "Max-Fast-Daemons:"
#define AR_DIR_LABEL_MAX_L_DAEMONS           "Max-List-Daemons:"
#define AR_DIR_LABEL_MAX_LOG_FILE_SIZE       "Max-Log-File-Size:"
#define AR_DIR_LABEL_MAX_HISTORY             "Max-Log-History:"
#define AR_DIR_LABEL_EMAIL_LINE_LEN          "Max-Notify-Mail-Line-Len:"
#define AR_DIR_LABEL_MAX_PASSWORD_ATTEMPTS   "Max-Password-Attempts:"
#define AR_DIR_LABEL_MAX_RECURSION_LEVEL     "Max-Recursion-Level:"
#define AR_DIR_LABEL_MAX_VENDOR_TEMP_TABLES  "Max-Vendor-Temp-Tables:"
#define AR_DIR_LABEL_MFS_ENVIRONMENT_FIELD_WEIGHT "MFS-Environment-Field-Weight:"
#define AR_DIR_LABEL_MFS_KEYWORDS_FIELD_WEIGHT "MFS-Keywords-Field-Weight:"
#define AR_DIR_LABEL_MFS_TITLE_FIELD_WEIGHT  "MFS-Title-Field-Weight:"
#define AR_DIR_LABEL_MID_TIER_PASSWD         "Mid-Tier-Service-Password:"
#define AR_DIR_LABEL_MINIMUM_API_VERSION     "Minimum-API-Version:"
#define AR_DIR_LABEL_MINIMUM_CMDB_API_VERSION "Minimum-CMDB-API-Version:"
#define AR_DIR_LABEL_MONITOR_DIR             "Monitor-directory:"
#define AR_DIR_LABEL_MULTIPLE_ARSERVER       "Multiple-ARSystem-Servers:"
#define AR_DIR_LABEL_MULT_ASSIGN_GROUPS      "Multiple-Assign-Groups:"
#define AR_DIR_LABEL_NEXT_ID_BLOCK_SIZE      "Next-ID-Block-Size:"
#define AR_DIR_LABEL_NEXT_ID_COMMIT          "Next-ID-Commit:"
#define AR_DIR_LABEL_NOTIFY_WEB_PATH         "Notification-Web-Path:"
#define AR_DIR_LABEL_ORACLE_CURSOR_SHARING   "Oracle-Cursor-Sharing:"
#define AR_DIR_LABEL_ORACLE_MULT_FACTOR      "Oracle-Colsize-Multiply:"
#define AR_DIR_LABEL_ORACLE_DBLINK_CHARSET   "Oracle-Dblink-Character-Set:"
#define AR_DIR_LABEL_ORACLE_SID              "Oracle-SID:"
#define AR_DIR_LABEL_ORACLE_TWO_T            "Oracle-Two-Task:"
#define AR_DIR_LABEL_ORACLE_QUERY_CLOB       "Oracle-Search-On-Clob:"
#define AR_DIR_LABEL_ORACLE_FETCH_COUNT      "Oracle-Bulk-Fetch-Count:"
#define AR_DIR_LABEL_ORACLE_CLOB_STORE_INROW "Oracle-Clob-Storage-In-Row:"
#define AR_DIR_LABEL_OVERLAY_MODE            "Overlay-mode:"
#define AR_DIR_LABEL_PER_THREAD_LOGS         "Per-Thread-Logging:"
#define AR_DIR_LABEL_PLUGIN_ARDBC_THREAD     "Plugin-ARDBC-Threads:"
#define AR_DIR_LABEL_PLUGIN_AREA_THREAD      "Plugin-AREA-Threads:"
#define AR_DIR_LABEL_PLUGIN_FILTERAPI_THREAD "Plugin-Filter-API-Threads:"
#define AR_DIR_LABEL_PLUGIN_DISABLE_REM      "Plugin-Disable-Remote:"
#define AR_DIR_LABEL_PLUGIN_LOAD             "Plugin:"
#define AR_DIR_LABEL_PLUGIN_LOG_FILE         "Plugin-Log-File:"
#define AR_DIR_LABEL_PLUGIN_LOG_LEVEL        "Plugin-Log-Level:"
#define AR_DIR_LABEL_PLUGIN_LOOPBACK_SOCKET  "Plugin-Loopback-RPC-Socket:"
#define AR_DIR_LABEL_PLUGIN_PASSWD           "Plugin-Password:"
#define AR_DIR_LABEL_PLUGIN_PATH             "Plugin-Path:"
#define AR_DIR_LABEL_PLUGIN_PORT             "Plugin-Port:"
#define AR_DIR_LABEL_PREFERENCE_PRIORITY     "Preference-Priority:"
#define AR_DIR_LABEL_PREF_SERVER_OPTION      "Preference-Server-Option:"
#define AR_DIR_LABEL_PRELOAD_NUM_THREADS     "Num-Preload-Threads:"
#define AR_DIR_LABEL_PRELOAD_NUM_SCHEMA_SEGS "Num-Preload-Schema-Segments:"
#define AR_DIR_LABEL_PRELOAD_THREAD_INIT_ONLY "Preload-At-Init-Only:"
#define AR_DIR_LABEL_PS_RPC_SOCKET           "Private-RPC-Socket:"
#define AR_DIR_LABEL_PS_SPEC_PORT            "Private-Specific-Port:"
#define AR_DIR_LABEL_PR_CATALOG_DIR          "PurchReq-Catalog-Dir:"
#define AR_DIR_LABEL_READ_ONLY_TRAN_OFF      "Read-Only-Tran-Off:"
#define AR_DIR_LABEL_RECORD_OBJECT_RELS      "Record-Object-Relationships:"
#define AR_DIR_LABEL_SVR_EVENT_LIST          "Record-Server-Events:"
#define AR_DIR_LABEL_REDUCE_CHCKPNT_UPD      "Reduce-Checkpoint-Updates:"
#define AR_DIR_LABEL_REGISTER_PORTMAPPER     "Register-With-Portmapper:"
#define AR_DIR_LABEL_REGISTRY_ADMIN_PASSWORD "Registry-Admin-Password:"
#define AR_DIR_LABEL_REGISTRY_ADMIN_USER     "Registry-Admin-User:"
#define AR_DIR_LABEL_REGISTRY_LOCATION       "Registry-Location:"
#define AR_DIR_LABEL_RE_LOG_DIR              "RE-Log-File-Location:"
#define AR_DIR_LABEL_REM_WKFLW_PASSWD        "Remote-Workflow-Password:"
#define AR_DIR_LABEL_REM_WKFLW_TARGET_PASSWD "Remote-Workflow-Target-Password:"
#define AR_DIR_LABEL_APP_SERVICE_PASSWD      "Remedy-App-Service-Password:"
#define AR_DIR_LABEL_REQ_FLD_IDENTIFIER      "Required-Field-Identifier:"
#define AR_DIR_LABEL_REQ_FLD_IDENTIFIER_LOCATION "Required-Field-Identifier-Location:"
#define AR_DIR_LABEL_RPC_CLIENT_XDR_LIMIT    "RPC-Client-XDR-Size-Limit:"
#define AR_DIR_LABEL_RPC_NON_BLOCKING_IO     "RPC-Non-Blocking-IO:"
#define AR_DIR_LABEL_SAVE_LOGIN              "Save-Login:"
#define AR_DIR_LABEL_SCC_CMNT_CHECKIN        "SCC-Comment-Checkin:"
#define AR_DIR_LABEL_SCC_CMNT_CHECKOUT       "SCC-Comment-Checkout:"
#define AR_DIR_LABEL_SCC_ENABLED             "SCC-Enabled:"
#define AR_DIR_LABEL_SCC_INT_MODE            "SCC-Integration-Mode:"
#define AR_DIR_LABEL_SCC_PROVIDER_NAME       "SCC-Provider-Name:"
#define AR_DIR_LABEL_SCC_TARGET_DIR          "SCC-Target-Dir:"
#define AR_DIR_LABEL_SELECT_QUERY_HINT       "Select-Query-Hint:"
#define AR_DIR_LABEL_SERVER_CONNECT_NAME     "Server-Connect-Name:"
#define AR_DIR_LABEL_SERVER_DIR              "Server-directory:"
#define AR_DIR_LABEL_SERVERGROUP_EMAIL_PORT  "Server-Group-Email-Admin-Port:"
#define AR_DIR_LABEL_SERVERGROUP_FLASH_PORT  "Server-Group-Flashboards-Admin-Port:"
#define AR_DIR_LABEL_SERVERGROUP_LOG_FILE    "Server-Group-Log-File:"
#define AR_DIR_LABEL_SERVERGROUP_MEMBER      "Server-Group-Member:"
#define AR_DIR_LABEL_SERVERGROUP_SIGNAL_OPT  "Server-Group-Signal-Option:"
#define AR_DIR_LABEL_SERVER_NAME             "Server-Name:"
#define AR_DIR_LABEL_SERVER_PLUGIN_ALIAS     "Server-Plugin-Alias:"
#define AR_DIR_LABEL_SERVER_PLUGIN_PASSWD    "Server-Plugin-Target-Password:"
#define AR_DIR_LABEL_SERVER_PLUGIN_TO        "Server-Plugin-Default-Timeout:"
#define AR_DIR_LABEL_SVR_STATS_REC_MODE      "Server-Stats-Rec-Mode:"
#define AR_DIR_LABEL_SVR_STATS_REC_INTERVAL  "Server-Stats-Rec-Interval:"
#define AR_DIR_LABEL_SET_PROC_TIME           "Set-Process-Timeout:"
#define AR_DIR_LABEL_CACHE_SEG_SIZE          "Shared-Cache-Segment-Size:"
#define AR_DIR_LABEL_SNMP_AGENT_ENABLED      "SNMP-agent-enabled:"
#define AR_DIR_LABEL_SQL_LOG_FILE            "SQL-Log-File:"
#define AR_DIR_LABEL_SQL_SECURE_CONNECT      "SQL-Secure-Connection:"
#define AR_DIR_LABEL_SQL_SERVER_SET_ANSI     "SQL-Server-Set-ANSI-Defaults:"
#define AR_DIR_LABEL_SSTABLE_CHUNK_SIZE      "Server-Side-Table-Chunk-Size:"
#define AR_DIR_LABEL_SUBMITTER_MODE          "Submitter-Mode:"
#define AR_DIR_LABEL_SUPPRESS_SERVER_DOMAIN  "Suppress-Server-Domain-In-URL:"
#define AR_DIR_LABEL_SUPPRESS_WARNINGS       "Suppress-warnings:"
#define AR_DIR_LABEL_SVR_SECURITY_CACHE      "Server-Security-Cache:"
#define AR_DIR_LABEL_SYBASE_CHARSET          "Sybase-Character-Set:"
#define AR_DIR_LABEL_SYBASE_SERV             "Sybase-Server-Name:"
#define AR_DIR_LABEL_SYSTEM_LOGGING_OPTIONS  "System-Logging-Options:"
#define AR_DIR_LABEL_SYSTEM_MESSAGES_DISPLAYED "System-Messages-Displayed:"
#define AR_DIR_LABEL_TS_SPEC_PORT            "TCD-Specific-Port:"
#define AR_DIR_LABEL_TS_SPEC_IP              "TCD-Specific-Bind:"
#define AR_DIR_LABEL_THREAD_LOG_FILE         "Thread-Log-File:"
#define AR_DIR_LABEL_TRACK_ADMIN_OP_PROGRESS "Track-Admin-Op-Progress:"
#define AR_DIR_LABEL_TWO_DIGIT_YEAR_CUTOFF   "Two-Digit-Year-Cutoff:"
#define AR_DIR_LABEL_USE_FTS_IN_WORKFLOW     "Use-FTS-In-Workflow:"
#define AR_DIR_LABEL_USE_PASSWD              "Use-Password-File:"
#define AR_DIR_LABEL_USE_CONNECT_NAME_STATS  "Use-Server-Connect-Name-In-Stats:"
#define AR_DIR_LABEL_USER_LOG_FILE           "User-Log-File:"
#define AR_DIR_LABEL_OBJ_MOD_LOG_MODE        "VersionControl-Object-Modification-Log-Mode:"
#define AR_DIR_LABEL_OBJ_MOD_LOG_SAVE_DEF    "VersionControl-Object-Modification-Log-Save-Definition-Files:"
#define AR_DIR_LABEL_OBJ_RESERVATION_MODE    "VersionControl-Object-Reservation-Mode:"
#define AR_DIR_LABEL_XML_VUI_EXP_LOCALIZED   "XML-VUI-Export-Default-Is-Localized:"
#define AR_DIR_LABEL_SUPPRESS_LOGOFF_SIGNAL  "Suppress-Logoff-Signals:"
#define AR_DIR_LABEL_UPGRADE_MODE            "Upgrade-Mode:"
#define AR_DIR_LABEL_UPGRADE_ADMIN_USER      "Upgrade-Admin-User:"
#define AR_DIR_LABEL_ATTACH_EXT_FILTER       "Attachment-Ext-Filter:" 
#define AR_DIR_LABEL_ATTACH_EXT_LIST         "Attachment-Ext-List:" 
#define AR_DIR_LABEL_ATTACH_EXCEPTION_LIST   "Attachment-Exception-List:" 
#define AR_DIR_LABEL_ATTACH_SYSTEM_EXCEPTION_LIST   "Attachment-System-Exception-List:" 
#define AR_DIR_LABEL_ATTACH_DISPLAY_FILTER   "Display-Filter:" 
#define AR_DIR_LABEL_ATTACH_DISPLAY_LIST     "Display-Ext-List:"
#define AR_DIR_LABEL_ATTACH_VALIDATION_PLUGIN_NAME  "Attach-Validation-Plugin-Name:"
#define AR_DIR_LABEL_SSO_CONFIRM_PASSWORD_PLUGIN_NAME  "SSO-Confirm-Password-Plugin-Name:"

#define AR_DIR_LABEL_WORKFLOW_ENCRYPT_ALGO   "Workflow-Encryption-Algorithm:"

#define ALT_DATA_FORM_SEPARATOR ";"          /* used to delineate list of data forms to be redirected */
                                             /* like so "Form1;Form2;Form3" */

/* Constants holding definitions for the database structure clause extensions */
#define AR_DIR_LABEL_CLAUSE              "Clause:"
#define AR_DIR_LABEL_FIELD               "Field {"
#define AR_DIR_LABEL_ID                  "Id:"
#define AR_DIR_LABEL_INDEX               "Index {"
#define AR_DIR_LABEL_SCHEMA              "Schema:"
#define AR_DIR_LABEL_FORM                "Form:"
#define AR_DIR_LABEL_INDEX_UPPER         "Oracle-Upper-Index"
#define AR_DIR_LABEL_INDEX_FUPPER        "Oracle-All-Upper-Index"

/* Constants holding definitions for the database options */
#define AR_DIR_LABEL_DB_OPTION            "DB-Options:"
#define AR_DIR_LABEL_DB_OPTION_NAME       "name:"
#define AR_DIR_LABEL_DB_OPTION_VALUE      "value:"
#define AR_DIR_LABEL_BEGIN_CLAUSE_NO_NL   "{"
#define AR_DIR_LABEL_END_CLAUSE_NO_NL     "}"

/* Constants holding definitions that have been deprecated */
#define AR_DIR_LABEL_THREAD_DEBUG_MODE       "Thread-Debug-mode:"

#define AR_TAG_TRUE               "T"
#define AR_TAG_FALSE              "F"

#define AR_FULL_TEXT_DEFAULT_THRESHOLD_LOW     200
#define AR_FULL_TEXT_MAX_THRESHOLD_LOW         250
#define AR_FULL_TEXT_DEFAULT_THRESHOLD_HIGH    1000000
#define AR_FULL_TEXT_SEARCH_DEFAULT_THRESHOLD  10000
                /* the following full text threshold definitions have been deprecated */
#define AR_DEFAULT_THRESHOLDLOW              AR_FULL_TEXT_DEFAULT_THRESHOLD_LOW
#define AR_DEFAULT_THRESHOLDHIGH             AR_FULL_TEXT_DEFAULT_THRESHOLD_HIGH

/* Constants holding definitions for alert message items */

#define AR_ALERT_MSG_TOTAL_LEN            1
#define AR_ALERT_MSG_SERVER_VERSION       2
#define AR_ALERT_MSG_TIMESTAMP            3
#define AR_ALERT_MSG_TYPE_CODE            4
#define AR_ALERT_MSG_PRIORITY             5
#define AR_ALERT_MSG_TEXT_LEN             6
#define AR_ALERT_MSG_TEXT                 7
#define AR_ALERT_MSG_SOURCE_LEN           8
#define AR_ALERT_MSG_SOURCE               9
#define AR_ALERT_MSG_SOURCE_SERVER_LEN   10
#define AR_ALERT_MSG_SOURCE_SERVER       11
#define AR_ALERT_MSG_SOURCE_FORM_LEN     12
#define AR_ALERT_MSG_SOURCE_FORM         13
#define AR_ALERT_MSG_SOURCE_OBJECT_LEN   14
#define AR_ALERT_MSG_SOURCE_OBJECT       15
#define AR_ALERT_MSG_SOURCE_SVR_ADDR_LEN 16
#define AR_ALERT_MSG_SOURCE_SVR_ADDR     17

#define AR_ALERT_MSG_ITEM_COUNT          17
#define AR_ALERT_MSG_ITEM_COUNT_V1       15

#define AR_ALERT_MSG_PROTOCOL_VERSION    2

/* Constants holding definitions for the contents of a mail template/message */

#define AR_MAIL_LABEL_SCHEMA   "Schema:"
#define AR_MAIL_LABEL_SERVER   "Server:"
#define AR_MAIL_LABEL_LOGIN    "Login:"
#define AR_MAIL_LABEL_PASSWORD "Password:"
#define AR_MAIL_LABEL_ACTION   "Action:"
#define AR_MAIL_LABEL_FORMAT   "Format:"

#define AR_MAIL_ACTION_SUBMIT  "Submit"
#define AR_MAIL_ACTION_QUERY   "Query"

#define AR_MAIL_FORMAT_SHORT   "Short"
#define AR_MAIL_FORMAT_FULL    "Full"

#define AR_MAIL_BEGIN          "AR-Message-Begin"
#define AR_MAIL_END            "AR-Message-End"

#define AR_MAIL_ID_DELIMITER   '!'

#define AR_MAIL_MAX_LINE_SIZE  1024 /* max size of mail message lines */

/* license format defines */
#define AR_LICENSE_FORMAT_REGULAR      1
#define AR_LICENSE_FORMAT_VENDOR       4
#define AR_LICENSE_FORMAT_APPLICATION  5

#define AR_APP_LICENSE_LABEL_DELIMITER ':'
#define AR_APP_LICENSE_SEPARATOR       ';'

#define AR_LICENSE_TYPE_USER_FIXED     "User Fixed"
#define AR_LICENSE_TYPE_USER_FLOATING  "User Floating"
#define AR_LICENSE_APPLICATION         "Application"
/* These are needed because the FTS licenses don't follow the license naming convention */
#define AR_LICENSE_TYPE_FTS_FIXED     "FTS Fixed"
#define AR_LICENSE_TYPE_FTS_FLOATING  "FTS Floating"
#define AR_LICENSE_TYPE_FTS_FIXED_ALT "Full Text Fixed"
#define AR_LICENSE_TYPE_FTS_FLOATING_ALT "Full Text Floating"

/* vendor application license types */
#define AR_APP_LICENSE_TYPE_APPLICATION   0   /* application license */
#define AR_APP_LICENSE_TYPE_USER_FIXED    1   /* application user fixed */
#define AR_APP_LICENSE_TYPE_USER_FLOATING 2   /* application user floating */

/* Constants holding license names */
#define AR_SERVER_LICENSE_TYPE          "AR Server"
#define AR_SERVER_LITE_LICENSE_TYPE     "AR System - Dedicated Server"
#define AR_USER_LICENSE_TYPE            "AR User"
#define AR_USER_FIXED_LICENSE_TYPE      "AR User Fixed"
#define AR_USER_FLOATING_LICENSE_TYPE   "AR User Floating"
#define AR_FULLTEXT_SERVER_LICENSE_TYPE "BMC Remedy Full Text Search"
/* These are deprecated full text licenses from 7.6 onwards, 
   adding the constants here for license upgrade purpose only */
#define AR_FULLTEXT_FIXED_LICENSE_TYPE  "BMC Remedy AR FTS Fixed"
#define AR_FULLTEXT_FLOAT_LICENSE_TYPE  "BMC Remedy AR FTS Floating"
/* */
#define AR_DISTRIBUTED_SERVER_TYPE      "AR Distributed Server"
#define AR_APPROVAL_SERVER_TYPE         "AR Approval Server"
#define AR_MIDTIER_LICENSE_TYPE         "AR Mid-Tier"
#define AR_ENCRYPT_STANDARD_TYPE        "AR Encryption - Standard Security"
#define AR_ENCRYPT_PERFORMANCE_TYPE     "AR Encryption - Performance Security"
#define AR_ENCRYPT_PREMIUM_TYPE         "AR Encryption - Premium Security"
#define AR_RESERVED1_SERVER_TYPE        "AR Reserved1 Server"
#define AR_RESERVED1_FIXED_TYPE         "AR Reserved1 Fixed"
#define AR_RESERVED1_FLOATING_TYPE      "AR Reserved1 Floating"
#define AR_RESERVED1_BUILDER_TYPE       "AR Reserved1 Builder"
#define FLASHBOARD_WEB_SERVER           "Flashboards Web Server"
#define AR_PAGER_LICENSE_TYPE           "AR Pager"
#define AR_WWW_LICENSE_TYPE             "AR Web Server"
#define AR_WIRELESS_LICENSE_TYPE        "AR Wireless Server"
#define AR_DISCOVERY_SMS                "Discovery Service for SMS"
#define AR_DISCOVERY_NETCENSUS          "Discovery Service for NetCensus"
#define AR_DISCOVERY_ORACLE             "Remedy Link for Oracle"
#define AR_DISCOVERY_SQL_SERVER         "Remedy Link for SQL Server"
#define AR_DISCOVERY_SAP                "Remedy Link for SAP R/3"
#define AR_DISCOVERY_LANDESK            "Discovery Service for LANDesk"
#define AR_SLA_FIXED_TYPE               "SLA User Fixed"
#define AR_ASSET_FIXED_TYPE             "Asset User Fixed"
#define AR_CHANGE_FIXED_TYPE            "Change User Fixed"
#define AR_HELPDESK_FIXED_TYPE          "Help Desk User Fixed"
#define AR_HELPDESK_FLOATING_TYPE       "Help Desk User Floating"
#define AR_PURCHASING_LICENSE_TYPE      "Purchasing@Work User"
#define AR_EXPENSABLE_LICENSE_TYPE      "ExpensAble@Work User"
#define AR_SETUPWORK_LICENSE_TYPE       "SetUp@Work User"
#define AR_SUPPORT_LICENSE_TYPE         "Support"
#define AR_QUALITY_LICENSE_TYPE         "Quality"
#define AR_CRMSERVER_LICENSE_TYPE       "CRM Server"
#define AR_CRMUSER_FIXED_TYPE           "CRM User Fixed"
#define AR_CRMUSER_FLOATING_TYPE        "CRM User Floating"
#define AR_CS_FIXED_TYPE                "Customer Support Fixed"
#define AR_CS_FLOATING_TYPE             "Customer Support Floating"
#define AR_ASSET_FLOATING_TYPE          "Asset User Floating"
#define AR_CHANGE_FLOATING_TYPE         "Change User Floating"
#define AR_ENTERPRISE_FLOATING_TYPE     "Enterprise Integration Engine"
#define AR_SALES_CONTINUUM_FIXED_TYPE   "Sales Continuum User Fixed"
#define AR_MIGRATOR_LICENSE_TYPE        "AR Migrator"
#define AR_PALM_LICENSE_TYPE            "AR Link for Palm User"
#define AR_PERSONALIZATION              "Remedy Personalization"
#define AR_APPLICATION_EXPLORER         "Remedy Application Explorer"
#define PROFILER_SERVER_TYPE            "Profiler Server"
#define PROFILER_USER_TYPE              "Profiler User"
#define DEMO_LICENSE_TYPE               "Demo"
#define PURGE_LICENSE_TYPE              "Purge"
#define LITE_LICENSE_TYPE               "Lite"
#define VENDOR_LICENSE                  "Vendor License"
#define AR_LOG_DECRYPTION_UTILITY_TYPE  "AR Log Decryption Utility"
#define AR_QUALITY_MGMT                 "Quality Management"
#define AR_QUALITY_MGMT_FIXED_TYPE      "Quality Management User Fixed"
#define AR_QUALITY_MGMT_FLOATING_TYPE   "Quality Management User Floating"
#define AR_RAD_SERVER                   "RAD/RCCS Server/integration license"
#define AR_ITSP_SUITE_FIXED_TYPE                "ITSP Suite User Fixed"
#define AR_ITSP_SUITE_FLOATING_TYPE             "ITSP Suite User Floating"
#define AR_ITSP_INCIDENT_USER_FIXED_TYPE        "ITSP Incident User Fixed"
#define AR_ITSP_INCIDENT_USER_FLOATING_TYPE     "ITSP Incident User Floating"
#define AR_ITSP_PROBLEM_USER_FIXED_TYPE         "ITSP Problem User Fixed"
#define AR_ITSP_PROBLEM_USER_FLOATING_TYPE      "ITSP Problem User Floating"
#define AR_ITSP_CHANGE_USER_FIXED_TYPE          "ITSP Change User Fixed"
#define AR_ITSP_CHANGE_USER_FLOATING_TYPE       "ITSP Change User Floating"
#define AR_ITSP_ASSET_USER_FIXED_TYPE           "ITSP Config/Asset User Fixed"
#define AR_ITSP_ASSET_USER_FLOATING_TYPE        "ITSP Config/Asset User Floating"
#define AR_ITSP_REQUEST_USER_FIXED_TYPE         "ITSP Request User Fixed"
#define AR_ITSP_REQUEST_USER_FLOATING_TYPE      "ITSP Request User Floating"
#define AR_ITSP_SLM_USER_FIXED_TYPE             "ITSP SLM User Fixed"
#define AR_ITSP_SLM_USER_FLOATING_TYPE          "ITSP SLM User Floating"
#define AR_ITSP_FOUNDATION_USER_FIXED_TYPE      "ITSP Foundation User Fixed"
#define AR_ITSP_FOUNDATION_USER_FLOATING_TYPE   "ITSP Foundation User Floating"
#define AR_ITSP_MASTER_ADMIN_FIXED_TYPE         "ITSP Master Admin Fixed"
#define AR_ITSP_MOBILITY_FIXED_TYPE             "ITSP Mobility Fixed"
#define AR_ENTERPRISE_INTEGRATION_TYPE          "BMC Atrium Integration Engine"
#define AR_CMDB_APPLICATION_TYPE                "BMC:Atrium CMDB Application"

/* Deprecated definitions for AR System client menu items */
/* that did not conform to established naming style       */
#define AR_RESERVE_MENU_MODIFYALL         AR_RESERV_MENU_MODIFYALL
#define AR_RESERVE_MENU_DELETE            AR_RESERV_MENU_DELETE
#define AR_RESERVE_MENU_PREFERENCES       AR_RESERV_MENU_PREFERENCES
#define AR_RESERVE_MENU_MENU              AR_RESERV_MENU_MENU
#define AR_RESERVE_MENU_TOOLBAR           AR_RESERV_MENU_TOOLBAR
#define AR_RESERVE_MENU_APPLY             AR_RESERV_MENU_APPLY
#define AR_RESERVE_MENU_POLLING           AR_RESERV_MENU_POLLING
#define AR_RESERVE_MENU_REPORTING         AR_RESERV_MENU_REPORTING
#define AR_RESERVE_MENU_PRINT             AR_RESERV_MENU_PRINT
#define AR_RESERVE_MENU_CLEARALL          AR_RESERV_MENU_CLEARALL
#define AR_RESERVE_MENU_SETDEFAULT        AR_RESERV_MENU_SETDEFAULT
#define AR_RESERVE_MENU_SEARCH            AR_RESERV_MENU_SEARCH
#define AR_RESERVE_MENU_NEW_SEARCH        AR_RESERV_MENU_NEW_SEARCH
#define AR_RESERVE_MENU_NEW_REQUEST       AR_RESERV_MENU_NEW_REQUEST
#define AR_RESERVE_MENU_SHOW_STAT_HIST    AR_RESERV_MENU_SHOW_STAT_HIST
#define AR_RESERVE_MENU_HOME              AR_RESERV_MENU_HOME
#define AR_RESERVE_MENU_HELP              AR_RESERV_MENU_HELP
#define AR_RESERVE_MENU_ADVANCED_SEARCH   AR_RESERV_MENU_ADVANCED_SEARCH

#endif  /* AR_STRUCT_DEFINED */
