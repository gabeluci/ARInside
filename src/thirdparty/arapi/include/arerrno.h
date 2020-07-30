/*  File:  arerrno.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef AR_ERRORNO_H
#define AR_ERRORNO_H

/* Codes for all the errors that can be returned from the AR Server */

/* error message catalog */
#define AR_CATALOG_FILENAME            "arsystem.cat"

/* set number in catalog for error msgs */
#define AR_ERROR_MSG_SET                            1

/* max error number that will be used by the AR system.  All "user" */
/*  errors should be above this value.                              */
#define AR_MAX_ERROR_NUMBER                        9999

/* object store API error message ranges */
#define OS_MIN_ERROR_NUMBER                        120000
#define OS_MAX_ERROR_NUMBER                        120999

#define OS_ERROR_MESSAGE_OFFSET                    119000
#define OS_ERROR_MSG_SET                           20

/* no error */
#define AR_ERROR_NONE                               0

/* error message for "can't find msg" */
#define AR_ERROR_NO_MESSAGE                         1

/* messages for the server */
#define AR_NOTE_SIGNAL_RECEIVED                    20
#define AR_NOTE_FATAL_EXIT                         21
#define AR_ERROR_LOG_FILE_FAILURE                  22
#define AR_NOTE_LOG_FILE_RESUME                    23
#define AR_ERROR_FILTER_PROCESS_FAIL               24
#define AR_ERROR_FILTER_FIELDS_MATCH               25
#define AR_ERROR_ADMIN_OPS_DISABLED                26
#define AR_NOTE_NO_SERVER_LICENSE                  27
#define AR_ERROR_DEMO_LICENSE_EXPIRED              28
#define AR_NOTE_DEMO_LICENSE_EXPIRE                29
#define AR_ERROR_USER_LICENSE_LIMIT                30
#define AR_NOTE_NEW_USER_LICENSE                   31
#define AR_NOTE_TERM_RECEIVED                      32
#define AR_ERROR_EXEC_PROCESS_FAIL                 33
#define AR_ERROR_LOCK_FILE_OPEN                    34
#define AR_ERROR_DUPLICATE_SERVER                  35
#define AR_ERROR_WRONG_DB_VERSION                  36
#define AR_ERROR_DEBUG_FILE_ERROR                  37
#define AR_ERROR_FILTER_PROCESS_ERROR              38
#define AR_ERROR_FILTER_PROCESS_TIME               39
#define AR_NOTE_SIGNAL_RECEIVED_PLUGIN_SERVER      40
#define AR_WARN_BAD_CMD_LINE_ARGUMENT              41
#define AR_WARN_MULTI_NOT_LICENSED                 42
#define AR_ERROR_BAD_MENU_MATCH                    43
#define AR_ERROR_SCHEMA_LICENSE_LIMIT              44
#define AR_NOTE_FATAL_EXIT_PLUGIN_SERVER           45
#define AR_ERROR_ESCALATION_MESSAGE                46
#define AR_WARN_EMAIL_NOTIFY_TIMEOUT               47

#define AR_ERROR_ESCALATION_PROCESS_FAIL           AR_ERROR_FILTER_PROCESS_FAIL
#define AR_ERROR_ESCALATION_FIELDS_MATCH           AR_ERROR_FILTER_FIELDS_MATCH
#define AR_ERROR_ESCALATION_PROCESS_ERROR          AR_ERROR_FILTER_PROCESS_ERROR
#define AR_ERROR_ESCALATION_PROCESS_TIME           AR_ERROR_FILTER_PROCESS_TIME

/* internal errors */
#define AR_ERROR_MAX_RESPONSE_BAD                  48
#define AR_ERROR_BAD_RESPONSE_ID                   49

/* warning messages */
#define AR_WARN_ADMIN_ONLY_ACCESS                  50
#define AR_WARN_ID_NOT_IN_SCHEMA                   51
#define AR_WARN_CORE_SUPPORT_FIELD                 52
#define AR_WARN_PERM_REQUIRES_ADMIN                53
#define AR_WARN_NOTHING_TO_SET                     54
#define AR_WARN_ITEM_NOT_IMPORTED                  55
#define AR_WARN_NO_SUCH_ENTRY                      56
#define AR_WARN_NULL_IN_STAT_OP                    57
#define AR_WARN_NO_SUCH_USER                       59
#define AR_WARN_NO_READ_ACCESS                     60
#define AR_WARN_NO_READ_ACCESS_IND                 61
#define AR_WARN_NO_ACCESS_TO_ENTRY                 62
#define AR_WARN_ACCESS_CONTROL_SKIP                63
#define AR_WARN_LOG_FILE_ACCESS                    64
#define AR_WARN_MULTI_SCHEMA_FILTER                65
#define AR_WARN_MAX_ENTRIES_RETRIEVED              66
#define AR_WARN_MENU_FILE_OPEN                     67
#define AR_WARN_BAD_RPC_ENV_VARIABLE               68
#define AR_WARN_VIEW_CREATE_FAILED                 69
#define AR_WARN_MISSING_MENUS                      70
#define AR_WARN_ADMIN_ONLY_ACCESS_AL               71
#define AR_WARN_MAX_ENTRIES_SERVER                 72
#define AR_WARN_PENDING_SUB_MODE_CHNG              73
#define AR_WARN_DUPLICATE_INDEX                    74
#define AR_WARN_NO_FREE_FLOATING                   75
#define AR_NOTE_UPGRADE_TO_FLOATING                76
#define AR_WARN_NO_FREE_FLOATING_FULL              77
#define AR_NOTE_UPGRADE_TO_FLOAT_FULL              78
#define AR_WARN_UNIQUE_SETTING_IGNORED             79
#define AR_WARN_SQL_DEL_COL_FAIL                   80
#define AR_WARN_DISTRIB_CORE_FIELD                 81
#define AR_WARN_LONG_OUT_OF_INDEX                  82
#define AR_WARN_LONG_OUT_OF_GET_LIST               83
#define AR_WARN_LONG_OUT_OF_SORT_LIST              84
#define AR_WARN_INDEX_IGNORED                      85

/* limits to support of features */
#define AR_WARN_NO_FLAT_FILE_INDEX                 86
#define AR_WARN_FLAT_FILE_DB_LIMIT                 87
#define AR_WARN_FLAT_FILE_NO_SQL                   88
#define AR_WARN_NO_FLAT_FILE_JOIN                  89

#define AR_WARN_MIN                                50
#define AR_WARN_MAX                                89

/* rpc errors */
#define AR_ERROR_CONNECT                           90
#define AR_ERROR_RPC_CALL                          91
#define AR_ERROR_RPC_TIMEOUT                       92
#define AR_ERROR_RPC_TIMEOUT_2                     93
#define AR_ERROR_RPC_TIMEOUT_3                     94

/* support and licensing errors */
#define AR_ERROR_RPC_INIT                          95
#define AR_WARN_CAP_UNSUP_BY_CLNT                  96
#define AR_ERROR_ONE_UNLIC_CONNECT                 97
#define AR_ERROR_NO_LONGER_SUPPORTED               98
#define AR_ERROR_DUP_REM_SERVER_ID                 99

/* parameter validation errors */
#define AR_ERROR_ENTRYID_EMPTY                    100
#define AR_ERROR_ENTRYID_TOO_LONG                 101
#define AR_ERROR_NAME_EMPTY                       102
#define AR_ERROR_NAME_TOO_LONG                    103
#define AR_ERROR_FIELD_VALUE_EMPTY                104
#define AR_ERROR_RESULT_LIST_NULL                 105
#define AR_ERROR_ENTRYID_LIST_EMPTY               106
#define AR_ERROR_STATS_LIST_EMPTY                 107
#define AR_ERROR_FIELD_DISPLAY_BAD                108
#define AR_ERROR_FILENAME_TOO_LONG                109
#define AR_ERROR_DATA_TYPE_BAD                    110
#define AR_ERROR_DEFAULT_VALUE_BAD                111
#define AR_ERROR_CHAR_MENU_EMPTY                  112
#define AR_ERROR_NAME_LIST_EMPTY                  113
#define AR_ERROR_NAME_LIST_ITEM                   114
#define AR_ERROR_OP_SET_BAD                       115
#define AR_ERROR_FILTER_ACTION_EMPTY              116
#define AR_ERROR_COMMAND_BAD                      117
#define AR_ERROR_FIELD_OPTION_BAD                 118
#define AR_ERROR_CREATE_MODE_BAD                  119
#define AR_ERROR_UNSUPP_DATATYPE                  120
#define AR_ERROR_ENTRYID_LIST_ITEM                121
#define AR_ERROR_SERVER_IREQ_EMPTY                122
#define AR_ERROR_SERVER_INFO_TAG_BAD              123
#define AR_ERROR_FIELD_VALUE_ITEM                 124
#define AR_ERROR_STATS_LIST_ITEM                  125
#define AR_ERROR_STATS_OP_BAD                     126
#define AR_ERROR_PERM_LIST_ITEM                   127
#define AR_ERROR_PERMISSIONS_BAD                  128
#define AR_ERROR_FIELD_LIMIT_BAD                  129
#define AR_ERROR_CHAR_MENU_ITEM                   130
#define AR_ERROR_CHAR_MENU_TYPE_BAD               131
#define AR_ERROR_STRUCT_ITEM_EMPTY                132
#define AR_ERROR_STRUCT_ITEM_BAD                  133
#define AR_ERROR_STRUCT_ITEM_ITEM                 134
#define AR_ERROR_FILTER_ACTION_BAD                135
#define AR_ERROR_NOTIFY_MECH_BAD                  136
#define AR_ERROR_MESSAGE_TYPE_BAD                 137
#define AR_ERROR_MESSAGE_NUM_BAD                  138
#define AR_ERROR_CORE_FIXED_OPTIONS               139
#define AR_ERROR_STATUS_REQ_DEFAULT               140
#define AR_ERROR_QUAL_NONE_NOT_TOP                141
#define AR_ERROR_QUAL_OPERATION_BAD               142
#define AR_ERROR_REL_OP_EMPTY                     143
#define AR_ERROR_REL_OP_BAD                       144
#define AR_ERROR_ARITH_OP_EMPTY                   145
#define AR_ERROR_ARITH_OP_BAD                     146
#define AR_ERROR_FVA_EMPTY                        147
#define AR_ERROR_FVA_TAG_BAD                      148
#define AR_ERROR_USER_MISSING                     149
#define AR_ERROR_SERVER_MISSING                   150
#define AR_ERROR_SCHEMA_MISSING                   151
#define AR_ERROR_SORT_LIST_ITEM                   152
#define AR_ERROR_SORT_OP_BAD                      153
#define AR_ERROR_MALLOC_CLIENT_FAIL               154
#define AR_ERROR_RETURN_BUFFER_BAD                155
#define AR_ERROR_INPUT_BUFFER_BAD                 156
#define AR_ERROR_FIELD_ID_CORE                    157
#define AR_ERROR_ENTID_DEF_TOO_LONG               158
#define AR_ERROR_SERVER_NAME_EMPTY                159
#define AR_ERROR_DECOMPRESSION_FAILURE            160
#define AR_ERROR_INVALID_SESSION_ID               161
#define AR_ERROR_NOTIFY_TEXT_BAD                  162
#define AR_ERROR_NOTIFY_FIELD_ID_BAD              163
#define AR_ERROR_ITEMS_BUT_NULL_PTR               165
#define AR_ERROR_DEFAULT_TYPE_ERROR               166
#define AR_ERROR_LIMIT_TYPE_ERROR                 167
#define AR_ERROR_FILTER_SET_ERROR                 168
#define AR_ERROR_ORDER_BAD                        169
#define AR_ERROR_STAT_HIST_TAG_BAD                170
#define AR_ERROR_STAT_HIST_ENUM_BAD               171
#define AR_ERROR_SERVICE_NOT_STARTED              172
#define AR_ERROR_LANGUAGE_BAD                     173
#define AR_ERROR_DISP_BAD_FOR_TYPE                174
#define AR_ERROR_DISP_PARM_BAD                    175
#define AR_ERROR_DUPLICATE_ENUM_VAL               176
#define AR_ERROR_CHANGE_IN_VIEW_GRP               177
#define AR_ERROR_FIELD_ID_NULL                    178
#define AR_ERROR_PATTERN_BAD                      179
#define AR_ERROR_DEFAULT_VALUE_LONG               180
#define AR_ERROR_FIELD_ID_RESERVED                181
#define AR_ERROR_TOO_MANY_ACTIONS                 182
#define AR_ERROR_DUP_ID_IN_PERM_LIST              183
#define AR_ERROR_QUOTE_IN_ENTRYID                 184
#define AR_ERROR_SYSTEM_NO_DEFAULT                185
#define AR_ERROR_CHAR_MENU_SYSTEM                 186
#define AR_ERROR_EXEC_MASK_BAD                    187
#define AR_ERROR_EXEC_MASK_REQ_FIELD              188
#define AR_ERROR_ACTLINK_ACTION_EMPTY             189
#define AR_ERROR_ACTLINK_ACTION_BAD               190
#define AR_ERROR_ASSIGN_TYPE_BAD                  191
#define AR_ERROR_FIELD_ASSIGN_EMPTY               192
#define AR_ERROR_FIELD_ASSIGN_ITEM                193
#define AR_ERROR_FIELD_TAG_BAD                    194
#define AR_ERROR_FIELD_EMPTY                      195
#define AR_ERROR_NO_MACRO_NAME_TEXT               196
#define AR_ERROR_KEYWORD_BAD                      197
#define AR_ERROR_NO_DEFAULT_KEYWORD               198
#define AR_ERROR_MISSING_PARM_NAME                199
#define AR_ERROR_MACRO_VALUE_TOO_BIG              200
#define AR_ERROR_BAD_FIELD_TAG                    201
#define AR_ERROR_NOTIFY_NAME_BAD                  202
#define AR_ERROR_VALUE_LIST_EMPTY                 203
#define AR_ERROR_NOTIFY_PRIORITY_BAD              204
#define AR_ERROR_CHAR_MENU_CLASS_BAD              206
#define AR_ERROR_MENU_REFRESH_BAD                 207
#define AR_ERROR_MENU_FILE_LOC_BAD                208
#define AR_ERROR_MENU_FILENAME_BAD                209
#define AR_ERROR_INDEX_LEN_TOO_LONG               210
#define AR_ERROR_NUM_INDEX_FIELDS_BAD             211
#define AR_ERROR_DISPLAY_LIST_EMPTY               212
#define AR_ERROR_QUALIFIER_NULL                   213
#define AR_ERROR_FIELD_LIST_BAD                   214
#define AR_ERROR_FIELD_LIST_TOO_LONG              215
#define AR_ERROR_SERVER_INFO_EMPTY                216
#define AR_ERROR_SERVER_INFO_SET_BAD              217
#define AR_ERROR_SERVER_INFO_GET_BAD              218
#define AR_ERROR_SERVER_INFO_TYPE                 219
#define AR_ERROR_LOCAL_VAR_NUM_BAD                220
#define AR_ERROR_QUERY_VALUE_EMPTY                221
#define AR_ERROR_QUERY_VALUE_ITEM                 222
#define AR_ERROR_QUERY_VAL_MULTI_BAD              223
#define AR_ERROR_CANNOT_INDEX_LONG                224
#define AR_ERROR_ONLY_REF_CURRENT                 225
#define AR_ERROR_QUAL_NOT_GET_LIST                226
#define AR_ERROR_FIELD_FOCUS_BAD                  227
#define AR_ERROR_FIELD_ACCESS_BAD                 228
#define AR_ERROR_FUNCTION_EMPTY                   229
#define AR_ERROR_FUNCTION_BAD                     230
#define AR_ERROR_PARAM_LIST_EMPTY                 231
#define AR_ERROR_VALUE_SET_TYPE_DIFF              232
#define AR_ERROR_FUNCTION_PARMS_BAD               233
#define AR_ERROR_SET_PROC_TIME_BAD                234
#define AR_ERROR_USER_LIST_TYPE_BAD               235
#define AR_ERROR_SET_LIC_TIME_BAD                 236
#define AR_ERROR_DDE_NAME_BAD                     237
#define AR_ERROR_DDE_ITEM_BAD                     238
#define AR_ERROR_DDE_ACTION_BAD                   239
#define AR_ERROR_CANNOT_SORT_LONG                 240
#define AR_ERROR_CANNOT_GETLIST_LONG              241
#define AR_ERROR_QUAL_FILTER_ONLY                 242
#define AR_ERROR_DDE_EMPTY                        243
#define AR_ERROR_DDE_PATH_BAD                     244
#define AR_ERROR_FIRETM_TYPE_BAD                  246
#define AR_ERROR_INTERVAL_BAD                     247
#define AR_ERROR_DAY_BAD                          248
#define AR_ERROR_HOUR_BAD                         249
#define AR_ERROR_MINUTE_BAD                       250
#define AR_ERROR_ENABLE_BAD                       251
#define AR_ERROR_SUBADMIN_BAD                     252
#define AR_WARN_SUBADMIN_BAD                      253
#define AR_ERROR_SUBJECT_TEXT_BAD                 254
#define AR_ERROR_SUBMITTER_MODE_BAD               255
#define AR_ERROR_SERVER_STAT_TAG_BAD              256
#define AR_ERROR_DUP_DISPLAY_TAG                  257
#define AR_ERROR_DS_RPC_SOCKET_BAD                258
#define AR_ERROR_NO_MATCH_BAD                     259
#define AR_ERROR_MULTI_MATCH_BAD                  260
#define AR_ERROR_SQL_COMMAND_EMPTY                261
#define AR_ERROR_CANNOT_GROUP_LONG                262
#define AR_ERROR_SAVE_LOGIN_BAD                   263
#define AR_ERROR_MENU_SERVER_BAD                  264
#define AR_ERROR_EMPTY_COMSCHEMA                  265
#define AR_ERROR_BAD_JOIN_MEMBER                  266
#define AR_ERROR_BAD_JOIN_QUERY                   267
#define AR_ERROR_BAD_VIEW_SCHEMA                  268
#define AR_ERROR_BAD_SCHEMA_TYPE                  269
#define AR_ERROR_EMPTY_FIELDMAP                   270
#define AR_ERROR_BAD_JOIN_MAP_INDEX               271
#define AR_ERROR_BAD_VIEW_MAP_NAME                272
#define AR_ERROR_BAD_MAPPING_TYPE                 273
#define AR_ERROR_BAD_COMSCHEMA_CHANGE             274
#define AR_ERROR_INDEX_NOT_ALLOWED                275
#define AR_ERROR_SCHEMA_DEPENDED                  276
#define AR_ERROR_FIELD_DEPENDED                   277
#define AR_ERROR_FIELD_IN_JOIN_QUAL               278
#define AR_ERROR_ENUM_NUM_TOO_LARGE               279
#define AR_ERROR_NO_SUPPORT_IN_FLAT               280
#define AR_ERROR_NO_MULTI_ACTLINK                 281
#define AR_ERROR_DEFAULT_VUI_EXISTS               282
#define AR_ERROR_NO_DATATYPE_ON_SERVER            283
#define AR_ERROR_ESCL_ACTION_EMPTY                284
#define AR_ERROR_NOT_ALLOWED_IN_QUAL              285
#define AR_ERROR_NO_DISPLAY_IN_QUERY              286
#define AR_ERROR_NO_STATUS_FIELD                  287
#define AR_ERROR_NOT_SUPPORTED_ON_SERVER          288
#define AR_ERROR_NO_NESTED_OUTER_JOIN             289
#define AR_ERROR_NO_JOIN_ACCESS                   290
#define AR_ERROR_MESSAGE_TEXT_BAD                 291
#define AR_ERROR_BAD_EXISTANCE_ARRAY              292
#define AR_ERROR_BAD_FIELDLIST_COLUMN             293
#define AR_ERROR_TOO_MANY_ENTRY                   294
#define AR_ERROR_FILE_POINTER_BAD                 295
#define AR_ERROR_BAD_SUP_FILE_TYPE                296
#define AR_ERROR_RELEASE_TOO_RECENT               297
#define AR_ERROR_FILTER_MAX_TOTAL                 298
#define AR_ERROR_FILTER_MAX_STACK                 299

/* runtime errors */
#define AR_ERROR_MALLOC_FAILED                    300
#define AR_ERROR_FILE_WRITE                       301
#define AR_ERROR_NO_SUCH_ENTRY                    302
#define AR_ERROR_NO_SUCH_SCHEMA                   303
#define AR_ERROR_MUST_BE_ADMIN                    304
#define AR_ERROR_ID_TOO_LONG                      305
#define AR_ERROR_VALUE_OUT_OF_LIMIT               306
#define AR_ERROR_REQ_VALUE_MISSING                307
#define AR_ERROR_DUPLICATE_FIELD                  308
#define AR_ERROR_MODIFIED_SINCE_GET               309
#define AR_ERROR_WRONG_DATA_TYPE                  310
#define AR_ERROR_ID_NOT_IN_SCHEMA                 311
#define AR_ERROR_BAD_ARITH_OP                     312
#define AR_ERROR_BAD_REL_OP                       313
#define AR_ERROR_NO_SUCH_FIELD                    314
#define AR_ERROR_ENTRIES_NO_DELETE                315
#define AR_ERROR_TEMP_FILE_FAILURE                316
#define AR_ERROR_DUPLICATE_SCHEMA                 317
#define AR_ERROR_NO_SUCH_GROUP                    318
#define AR_ERROR_CORE_LENGTH                      319
#define AR_ERROR_NO_SUCH_CHAR_MENU                320
#define AR_ERROR_CHAR_MENU_TOO_DEEP               321
#define AR_ERROR_INVALID_HIERARCHY                322
#define AR_ERROR_NO_SUCH_FILTER                   323
#define AR_ERROR_NO_SUCH_ADMIN_EXT                324
#define AR_ERROR_DUPLICATE_FILTER                 325
#define AR_ERROR_REQ_VALUE_NULL                   326
#define AR_ERROR_STAT_OP_BAD_TYPE                 327
#define AR_ERROR_DUPLICATE_ADMIN_EXT              328
#define AR_ERROR_PASSWORD_MISMATCH                329
#define AR_ERROR_NO_WRITE_ACCESS                  330
#define AR_ERROR_NO_WRITE_ACCESS_IND              331
#define AR_ERROR_NO_WRITE_ACCESS_CRE              332
#define AR_ERROR_NO_ACCESS_TO_FIELD               333
#define AR_ERROR_BAD_AR_RESERV_DEFN               334
#define AR_ERROR_RESERV_FIELD_FORMAT              335
#define AR_ERROR_ID_IN_GROUP_LIST                 336
#define AR_ERROR_NO_LICENSE_DB_LIMIT              337
#define AR_ERROR_MERGE_DUPLICATE_ID               338
#define AR_ERROR_DIARY_FORMAT                     339
#define AR_ERROR_STAT_HIST_FORMAT                 340
#define AR_ERROR_CANNOT_RUN_PROCESS               341
#define AR_ERROR_DIRECTORY_OPEN_FAIL              342
#define AR_ERROR_BAD_FILTER_DEFN                  343
#define AR_ERROR_GROUP_TYPE_CONFLICT              344
#define AR_ERROR_DUPLICATE_ACTLINK                345
#define AR_ERROR_NO_SUCH_ACTLINK                  346
#define AR_ERROR_NO_ACCESS_TO_ACTLINK             347
#define AR_ERROR_GROUP_CACHE_EMPTY                348
#define AR_ERROR_DELETE_CORE_FIELD                349
#define AR_ERROR_DIVIDE_BY_0                      350
#define AR_ERROR_PASSWORD_IN_QUALIFY              351
#define AR_ERROR_GROUP_NOTIFY_LOOP                352
#define AR_ERROR_NO_ACCESS_TO_SCHEMA              353
#define AR_ERROR_NO_ACCESS_TO_ADMEXT              354
#define AR_ERROR_NO_ACCESS_TO_FILTER              355
#define AR_ERROR_DUPLICATE_CHAR_MENU              356
#define AR_ERROR_CHAR_MENU_TOO_LONG               357
#define AR_ERROR_MENU_FILE_ACCESS                 358
#define AR_ERROR_BAD_RPC_FOR_OP                   359
#define AR_ERROR_MISSING_CONVERSION_RATIO         360
#define AR_ERROR_NO_UNQUAL_QUERY                  361
#define AR_ERROR_FLAT_FILE_DB_LIMIT               362
#define AR_ERROR_REQ_VALUE_BAD_DEF                363
#define AR_ERROR_DIARY_VALUE_NULL                 364
#define AR_ERROR_NO_SUCH_ESCALATION               366
#define AR_ERROR_DUPLICATE_ESCALATION             367
#define AR_ERROR_BAD_ESCALATION_DEFN              368
#define AR_ERROR_NO_ACCESS_TO_ESCALATION          369
#define AR_ERROR_NO_SCHEMAID                      370
#define AR_ERROR_SUBMITTER_LOCKED                 371
#define AR_ERROR_NOTIFICATION_ERROR               372
#define AR_ERROR_NO_ACCESS_TO_DIST_MAP            373
#define AR_ERROR_NO_SUCH_DIST_MAP                 374
#define AR_ERROR_DUPLICATE_DIST_MAP               375
#define AR_ERROR_DIST_NOT_MASTER                  376
#define AR_ERROR_MISSING_QUOTE_IN_DS              377
#define AR_ERROR_MUST_BE_DISTRIB                  378
#define AR_ERROR_IMPORT_DISTRIBUTED               379
#define AR_ERROR_FILTER_REF_NO_MATCH              380
#define AR_ERROR_FILTER_MULTI_MATCH               381
#define AR_ERROR_DUP_ON_UNIQUE_INDEX              382
#define AR_ERROR_FILE_MENU_TOO_LONG               383
#define AR_ERROR_INVALID_CHAR_IN_NAME             384
#define AR_ERROR_DUP_ID_IN_MULTIPLE               385
#define AR_ERROR_NESTED_EXCEPTION                 386
#define AR_ERROR_VIOLATE_INTEGRITY                387
#define AR_ERROR_NO_SUCH_VUI                      388
#define AR_ERROR_DUPLICATE_VUI                    389
#define AR_ERROR_DELETE_LAST_VUI                  390
#define AR_ERROR_CREATE_VUI                       391
#define AR_ERROR_DUPLICATE_DB_NAME                392
#define AR_ERROR_STATUS_HIS_IN_MENU               393
#define AR_ERROR_ADMIN_ONLY_MODE                  394
#define AR_ERROR_REMOTE_PROC_TIMEOUT              395
#define AR_ERROR_NO_SUCH_SUP_FILE                 396
#define AR_ERROR_GROUPLIST_LENGTH                 397
#define AR_ERROR_MALLOC_FAILED_FOR_CACHE          398
#define AR_ERROR_BAD_ACTLINK_DEFN                 399

/* definition file errors */
#define AR_ERROR_NOT_SCHEMA_DEFN                  400
#define AR_ERROR_WRONG_DEFINITION                 401
#define AR_ERROR_INCORRECT_FORMAT                 402
#define AR_ERROR_DEF_COUNT_MISMATCH               403
#define AR_ERROR_UNKNOWN_CORE_FIELD               404
#define AR_ERROR_BAD_CORE_DEFN                    405
#define AR_ERROR_MISSING_CORE_FIELD               406
#define AR_ERROR_DUPLICATE_FIELD_ID               407
#define AR_ERROR_ENUM_REQ_LIMITS                  408
#define AR_ERROR_NO_DEFN_IN_FILE                  409
#define AR_ERROR_NOT_FILTER_DEFN                  410
#define AR_ERROR_NOT_ADMIN_EXT_DEFN               411
#define AR_ERROR_BAD_IMPORT_FORMAT                412
#define AR_ERROR_NOT_ACTLINK_DEFN                 413
#define AR_ERROR_NOT_CHAR_MENU_DEFN               414
#define AR_ERROR_NOT_ESCALATION_DEFN              415
#define AR_ERROR_NOT_DIST_MAP_DEFN                416
#define AR_ERROR_RESERV_GROUP_LIST                417
#define AR_ERROR_INCORRECT_JOIN                   418
#define AR_ERROR_INCORRECT_VIEW                   419
#define AR_ERROR_INCORRECT_FIELD_TYPE             420
#define AR_ERROR_INCORRECT_FIELD_MAP              421
#define AR_ERROR_ESCL_ACTION_BAD                  422
#define AR_ERROR_NOT_CONTAINER_DEFN               423
#define AR_ERROR_PF_ONLY_REF_CURRENT              424
/* added for export distributed pool */
#define AR_ERROR_NO_ACCESS_TO_DIST_POOL           425
#define AR_ERROR_NOT_DIST_POOL_DEFN               426
#define AR_ERROR_NO_SUCH_DIST_POOL                427
#define AR_ERROR_DUPLICATE_DIST_POOL              428
#define AR_ERROR_NOT_VUI_DEFN                     429

#define AR_ERROR_FIELD_ID_TOO_LARGE               430
#define AR_ERROR_FIELD_NO_MULTI_COLUMN            431
#define AR_ERROR_TOO_MANY_FUNC_FOR_INDEXING       432
/* added for object locking support */
#define AR_ERROR_NOT_LOCK_BLOCK_DEFN              433
#define AR_ERROR_INVALID_LOCK_BLOCK               434
/* server information support */
#define AR_ERROR_SERVER_INFO_ADMIN_DISABLED       435
#define AR_ERROR_SERVER_INFO_INVALID_FORMAT       436
/* import error */
#define AR_ERROR_NOT_SCHEMA_DATA_DEFN             437
/* reload error */
#define AR_ERROR_RELOAD_FAILED                    438

#define AR_ERROR_FIELD_RESIZE_ERROR               439

/* generic errors */
#define AR_ERROR_BAD_FUNCTION_PARMS               440
#define AR_ERROR_INVALID_ARRAY_INDEX              441
#define AR_ERROR_REQUIRED_API_INPUT_NULL          442
#define AR_ERROR_NO_MORE_ENTRIES                  443
#define AR_ERROR_JNI_COULD_NOT_FIND_CLASS         444
#define AR_ERROR_JNI_COULD_NOT_FIND_METHOD        445
#define AR_ERROR_NO_CHANGE_FIELD_OPTION           446
#define AR_ERROR_SERVER_INFO_INVALID_VALUE        447
#define AR_ERROR_FILE_SIZE_EXCEEDS_LIMIT          448

/* external file errors */
#define AR_WARN_REP_FILE_OPEN_FAIL                450
#define AR_WARN_REP_FILE_LOAD_FAIL                451
#define AR_NOTE_TAG_FILE_NOT_FOUND                452

/* configuration file errors */
/* application license auditing message */
#define AR_ERROR_MISSING_APPL_AUDIT_INFO          460
#define AR_ERROR_LITE_LIC_WRONG_VERSION           461
#define AR_ERROR_LITE_LIC_FORM_NOT_SUPPORTED      462
#define AR_ERROR_LITE_LIC_NO_CREATE_FORM          463
#define AR_ERROR_LITE_LIC_NO_SET_FORM_NAME        464
#define AR_ERROR_LITE_LIC_NO_SET_FORM_MAP_CRITERIA 465
#define AR_ERROR_INVALID_LICENSE_FILE             466
#define AR_ERROR_INVALID_LICENSE_IMPORT_OPTION    467
#define AR_ERROR_LOADING_LICENSE_CACHE            468
#define AR_WARNING_BAD_SERVER_KEY                 469

/* arcache and arreload error messages */
#define AR_ERROR_USER_CACHE_UTILS_DISABLED        470

/* upgrade process errors */
#define AR_WARNING_EMPTY_LICENSE_FILE             474
#define AR_ERROR_TOO_FEW_UP_ARGS                  475
#define AR_ERROR_TOO_MANY_UP_ARGS                 476
#define AR_ERROR_ORCL80_NOT_SUPPORT               477
#define AR_ERROR_UNICODE_DB_NOT_UPGRADE_READY     478
#define AR_WARNING_DELETE_TEMP_COLUMN_FAILED      479

/* view schema errors */
#define AR_ERROR_UNSUPP_FIELD_ID                  480
#define AR_ERROR_NO_SUCH_TABLE                    481
#define AR_ERROR_VIEW_FORM_KEY_FIELD_NULL         482
#define AR_NOTE_SERVER_NEED_RESTART               483

/* multi-field error and warnings */
#define AR_ERROR_RESERVED_ID_OK_NULL              485
#define AR_ERROR_MULT_LIST_LENGTH_BAD             486
#define AR_ERROR_SET_FIELD_STATUS_LIST_NULL       487
#define AR_ERROR_CREATE_MULT_FIELD_POSITION       488
#define AR_WARN_SET_FIELD_FAILED                  489

/* Preference server errors */
#define AR_ERROR_PREF_SRV_OPTION_INVALID          490

/* flat-file database errors */                       
#define AR_ERROR_DB_OPEN_FAILED                   500
#define AR_ERROR_NOT_A_DB_FILE                    501
#define AR_ERROR_FILE_DB_FORMAT                   502
#define AR_ERROR_DB_WRITE                         503
#define AR_ERROR_NO_SCHEMA_DEFN                   504
#define AR_ERROR_SCHEMA_FILE_ERROR                505
#define AR_ERROR_DEFN_FILE_ERROR                  506
#define AR_ERROR_DB_FILE_ERROR                    507
#define AR_ERROR_FILTER_FILE_ERROR                508
#define AR_ERROR_ADMINEXT_FILE_ERROR              509
#define AR_ERROR_USER_FILE_ERROR                  510
#define AR_ERROR_GROUP_FILE_ERROR                 511
#define AR_ERROR_ACTLINK_FILE_ERROR               512
#define AR_ERROR_DB_RECORD_OVERFLOW               513
#define AR_ERROR_DB_STATHIST_INVALID              514
#define AR_ERROR_CHARMENU_FILE_ERROR              515
#define AR_ERROR_ESCALATION_FILE_ERROR            516
#define AR_ERROR_SUP_FILE_FILE_ERROR              517
#define AR_ERROR_SUP_FILE_ERROR                   518
#define AR_ERROR_ATTACH_FILE                      520
#define AR_ERROR_ATTACH_FILE_INDEX                521
#define AR_ERROR_NOTIFUSR_FILE_ERROR              522
#define AR_ERROR_NOTIFTIM_FILE_ERROR              523
#define AR_ERROR_UNBALANCED_DB_TRANSACTION        524
#define AR_ERROR_ATTACH_FILE_NOT_ALLOWED          525
#define AR_WARNING_ATTACH_FILE                    526

/* SQL database errors */
#define AR_ERROR_SQL_OPEN_FAILED                  550
#define AR_ERROR_SQL_INIT                         551
#define AR_ERROR_SQL_OP_FAILURE                   552
#define AR_ERROR_SQL_OP_TOO_LARGE                 553
#define AR_ERROR_SQL_MISSING_CONTROL              554
#define AR_ERROR_SQL_MISSING_ENUM                 555
#define AR_ERROR_SQL_MISSING_DATA                 556
#define AR_ERROR_SQL_TOO_MUCH_DATA                557
#define AR_ERROR_SQL_MISSING_SCHEMA               558
#define AR_ERROR_SQL_CHAR_STRING_LEN              559
#define AR_ERROR_SQL_BAD_ACTION_IND               560
#define AR_ERROR_SQL_QUALIFY_LONG                 561
#define AR_ERROR_SQL_MISSING_HELP                 562
#define AR_ERROR_SQL_NO_MODULO_OP                 563
#define AR_ERROR_SQL_BAD_LIKE                     564
#define AR_ERROR_SQL_NO_COL_IN_CMD                565
#define AR_ERROR_SQL_DEADLOCK                     566
#define AR_ERROR_SQL_CONNECTION_FAILURE           567
#define AR_ERROR_SQL_OCI_HANDLE_UNAVAILABLE       568
#define AR_ERROR_SQL_AFFECTED_COUNT_UNAVAILABLE   569
#define AR_ERROR_SQL_COMMAND_BAD_FORMAT           570

#define AR_NOTE_SQL_DB_UNAVAILABLE                590
#define AR_NOTE_SQL_DB_STILL_UNAVAIL              591
#define AR_NOTE_SQL_DB_AVAILABLE                  592

/* messages for noting performance issues in the exception log */
#define AR_NOTE_SQL_TIME_THRESHOLD_EXCEEDED       595
#define AR_NOTE_API_TIME_THRESHOLD_EXCEEDED       596
#define AR_NOTE_CLIENT_HAS_TIMED_OUT_API          597
#define AR_NOTE_CLIENT_HAS_TIMED_OUT_API_SQL      598

/* messages with user/group cache proc */
#define AR_ERROR_DIRECTORY_FILE                   600
#define AR_ERROR_BAD_CMD_LINE_OPTION              601
#define AR_ERROR_OPERATION_CONFLICT               602
#define AR_ERROR_MUST_GIVE_ONE                    603
#define AR_ERROR_MUST_GIVE_OPERATION              604
#define AR_ERROR_CMD_OPTION_CONFLICT              605
#define AR_ERROR_CMD_OPTION_MISSING               607
#define AR_ERROR_VALUE_EXPECTED                   608
#define AR_ERROR_CRE_DEL_TAG                      609
#define AR_ERROR_SERVER_FILE_ERROR                610
#define AR_ERROR_DYNAMIC_GROUP_NOT_PERMITTED      611
#define AR_ERROR_NO_SUCH_USER                     612
#define AR_ERROR_GROUP_TYPE_BAD                   613
#define AR_ERROR_LICENSE_TYPE_BAD                 614
#define AR_ERROR_CASE_MISMATCH_USER               615
#define AR_ERROR_GROUP_CATEGORY_BAD               616
#define AR_ERROR_COMPUTED_GROUP_CIRCULAR          617
#define AR_ERROR_INVALID_COMPUTED_GROUP_QUAL      618
#define AR_ERROR_INVALID_COMPUTED_GROUP_LIST      619

#define AR_ERROR_TWO_OPEN_WRITE_TAG               620
#define AR_ERROR_TAG_FILE_PROBLEM                 621
#define AR_ERROR_TAG_LIC_PROBLEM                  622
#define AR_ERROR_AUTHENTICATION_FAILED            623 
#define AR_ERROR_ACCOUNT_MARKED_INVALID           624

/* messages for business time */
#define AR_WARN_HOLIDAY_DATE_BAD                  625
#define AR_WARN_WORKDAY_TIME_BAD                  626 

#define AR_ERROR_2_HOLIDAY_SCHEMA                 635
#define AR_ERROR_NO_HOLIDAY_SCHEMA                636
#define AR_ERROR_NO_HOLIDAY_FOR_TAG               637
#define AR_ERROR_2_WORKDAY_SCHEMA                 638
#define AR_ERROR_NO_WORKDAY_SCHEMA                639
#define AR_ERROR_NO_WORKDAY_FOR_TAG               640
#define AR_ERROR_WORKDAY_NEVER_OPEN               641
#define AR_ERROR_2_BUS_TIME_ACTIVITY_SCHEMA       642
#define AR_ERROR_NO_BUS_TIME_ACTIVITY_SCHEMA      643
#define AR_ERROR_NO_BUS_ACTIVITY_FOR_TAG          644
#define ARAPP_ERROR_CMD_INVALID_LEVEL             645
#define AR_ERROR_2_BUS_TIME_ASSOC_SCHEMA          646
#define AR_ERROR_NO_BUS_TIME_ASSOC_SCHEMA         647
#define AR_ERROR_INCORRECT_LEVEL1_OR_2            648
#define AR_ERROR_INVALID_RECURRENCE_TIME          649

/* messages for full text search */
#define AR_ERROR_FULLTEXT_BEGIN                   650
#define AR_ERROR_FULLTEXT_INFO_EMPTY              651
#define AR_ERROR_FULLTEXT_INFO_TYPE               652
#define AR_ERROR_FULLTEXT_INFO_VALUE              653
#define AR_ERROR_FULLTEXT_INFO_TAG_BAD            654
#define AR_ERROR_FULLTEXT_IREQ_EMPTY              655
#define AR_ERROR_FULLTEXT_INIT_FAILED             656
#define AR_ERROR_FULLTEXT_OP_FAILURE              657
#define AR_ERROR_FULLTEXT_DOCREAD_FAILURE         658
#define AR_ERROR_FULLTEXT_STOPWORD_FILE_OPEN      659
#define AR_ERROR_FULLTEXT_SET_STOPWORD_FAIL       660
#define AR_ERROR_FULLTEXT_MOVECOLDIRFAIL          661
#define AR_ERROR_FULLTEXT_OP_TOO_LARGE            662
#define AR_ERROR_FULLTEXT_WRONG_DATA_TYPE         663
#define AR_ERROR_FULLTEXT_WRONG_VERSION           664
#define AR_ERROR_FULLTEXT_NOT_LICENSED            665
#define AR_ERROR_FULLTEXT_STATEOFF                666
#define AR_ERROR_FULLTEXT_STATEON                 667
#define AR_ERROR_FULLTEXT_BADQUERY                668
#define AR_ERROR_FULLTEXT_INDEXDIR_EXISTS         669
#define AR_WARN_FT_FIELD_PENDING_INDXNG           670
#define AR_ERROR_FT_INDEXER_NOT_EXISTS            671
#define AR_ERROR_FT_CANT_INDX_STATUS_HISTORY      672
#define AR_WARN_FT_UNSUPPORTED_FTS_QUERY          673
#define AR_ERROR_FULLTEXT_UNQUALIFIED_QUERY       674
#define AR_ERROR_FULLTEXT_INFO_SET_BAD            675
#define AR_ERROR_FULLTEXT_END                     676
#define AR_ERROR_WRITE_LICENSE_TYPE_BAD           677
#define AR_ERROR_FULLTEXT_INDEXING_OFF            678
#define AR_ERROR_FULLTEXT_NO_FORM_BASED_SEARCH    679
#define AR_ERROR_FULLTEXT_NO_LOAD_LIBRARY         680
#define AR_WARN_FULLTEXT_INDEX_REBUILD_STARTED    681
#define AR_WARN_SEARCH_SERVICE_NOT_AVAILABLE      682
#define AR_WARN_SEARCH_SERVICE_NOT_CONFIGURED     683
#define AR_ERROR_FULLTEXT_INVALID_DOCBOOST        684
#define AR_WARN_FULLTEXT_FTSPLUGIN_NOT_AVAILABLE  685
#define AR_WARN_FULLTEXT_NO_MODIFIED_DATE         686
#define AR_ERROR_TABLE_FIELD_NOT_INDEXABLE        687

/* Multi-Form FTS search errors */
#define AR_ERROR_MFSSEARCH_FORM_CREATE_DUP            688
#define AR_WARN_MFSEARCH_PENDING_INDEXING             689
#define AR_ERROR_MFSEARCH_SEARCH_STRING_NOT_SPECIFIED 690
#define AR_ERROR_MFSEARCH_FORM_FIELD_NOT_SPECIFIED    691
#define AR_ERROR_MFSEARCH_NO_LICENSE                  692
#define AR_ERROR_MFSEARCH_UPDATES_NOT_ALLOWED         693
#define AR_ERROR_MFSEARCH_OP_NOT_ALLOWED              694
#define AR_ERROR_MFSEARCH_CAT_BAD_FIELD_TYPE          695
#define AR_ERROR_MFSEARCH_FIELD_NOT_PUBLIC            696
#define AR_ERROR_MFSEARCH_FIELD_NOT_FTINDEXED         697
#define AR_ERROR_MFSEARCH_DUP_CAT_NAME                698
#define AR_ERROR_MFSEARCH_INVALID_PROPERTY            699

/*** The range 700 to 799 are reserved for NM daemon messages ***/

/* messages for multi-process control */
#define ARTC_NOTE_SIGNAL_RECEIVED                 800
#define ARTC_NOTE_FATAL_EXIT                      801
#define ARTC_NOTE_FAILURE_RELAUNCH                802
#define ARTC_NOTE_INHERIT_RELAUNCH                803
#define ARTC_NOTE_RELAUNCH                        804
#define ARTC_ERROR_LOCK_FILE_OPEN                 840
#define ARTC_ERROR_DUPLICATE_SERVER               841
#define ARTC_ERROR_MALLOC_FAILED                  842
#define ARTC_ERROR_FORK_PROCESS                   843
#define ARTC_ERROR_EXEC_PROCESS                   844
#define ARTC_ERROR_MULTI_FAILURE                  845
#define AR_ERROR_WAIT_FAILED                      847
#define AR_ERROR_NO_SERVERS_RUNNING               848
#define AR_ERROR_PIPE_CREATE                      849
#define AR_ERROR_PIPE_OPEN                        850
#define AR_ERROR_PIPE_READ                        851

/* messages for FTS daemon */                                        
#define AR_ERROR_FT_LOCKF_EXISTS                  855
#define AR_ERROR_FT_LOCKF_NOT_EXISTS              856
#define AR_ERROR_FT_PEND_FILE_OPEN_FAIL           857
#define AR_ERROR_FT_PEND_FILE_WRITE_FAIL          858
#define AR_ERROR_FT_RECORD_NOT_EXISTS             859
#define AR_ERROR_FT_TRUNCATE_ERROR                860
#define AR_ERROR_FULLTEXT_PURGE_PEND_FAIL         861
#define AR_ERROR_FT_TOO_FEW_ARGS                  862
#define AR_ERROR_FT_TOO_MANY_ARGS                 863
#define AR_ERROR_FT_INVALID_ACTION                864
#define AR_ERROR_FT_TERM_SIGNAL                   865
#define AR_ERROR_FT_DUPLICATE_SERVER              866
#define AR_ERROR_FULLTEXT_FIELDID_REQD            867
#define AR_ERROR_FULLTEXT_TOOMANYFOROPT           868
#define AR_ERROR_FULLTEXT_TOOMANYFORRETRY         869
#define AR_ERROR_FULLTEXT_NAMESPECIFIED           870
#define AR_ERROR_FULLTEXT_IDSPECIFIED             871
#define AR_ERROR_FULLTEXT_SCHEMANAMEBAD           872
#define AR_ERROR_FULLTEXT_BADDEBUGOPT             873
#define AR_ERROR_FULLTEXT_REQUIREDPARAMINVALID    874
#define AR_ERROR_FULLTEXT_INDEXINGSERVICEERROR    875
#define AR_ERROR_MFSEARCH_RELEVANCY_FIELD_UNINDEX 876
#define AR_ERROR_MFSEARCH_RELEVANCY_FIELD_NON_PUBLIC 877
#define AR_ERROR_MFSEARCH_RELEVANCY_FIELD_DELETE  878
#define AR_ERROR_FULLTEXT_INDEX_BUSY              879
#define AR_ERROR_FULLTEXT_FIELD_BUSY              880

/* messages for server image objects */
#define AR_ERROR_NOT_IMAGE_DEFN                   881
#define AR_ERROR_IMAGE_NOT_FOUND                  882
#define AR_ERROR_DUPLICATE_IMAGE                  883
#define AR_ERROR_NO_IMAGE_SUPPLIED                884
#define AR_ERROR_NO_IMAGE_TYPE_SUPPLIED           885

/* client managed transaction errors */
#define AR_ERROR_MAX_CLIENT_TRANASACTION_EXCEEDED 897
#define AR_ERROR_NO_SUCH_CLIENT_TRANSACTION       898
#define AR_ERROR_ALREADY_IN_CLIENT_TRANSACTION    899

/* range with 900-949 error codes is obsolete */

/* messages for mail interface */
#define AR_NOTE_MAIL_SUBJECT_ERROR                950
#define AR_ERROR_MAIL_NO_SCHEMA                   951
#define AR_ERROR_NO_MAIL_BODY                     952
#define AR_ERROR_MAIL_BODY_FORMAT                 953
#define AR_ERROR_MAIL_BAD_CMD_LINE                954
#define AR_ERROR_MAIL_PARM_VALUE                  955
#define AR_ERROR_MAIL_CONFIG_FILE                 956
#define AR_ERROR_MAIL_NOT_REQ_SCHEMA              957
#define AR_ERROR_MAIL_NOT_REQ_SERVER              958
#define AR_ERROR_MAIL_NOT_A_SERVER                959

#define AR_NOTE_MAIL_SUBJECT_OK                   960
#define AR_NOTE_MAIL_SUCCESS                      961
#define AR_NOTE_MAIL_QUERY_SUCCESS                962
#define AR_NOTE_MAIL_QUERY_SUBJECT_OK             963
#define AR_ERROR_MAIL_MAPI_LOGON_FAIL             964
#define AR_ERROR_MAIL_MAPI_RESOLVE_FAIL           965
#define AR_ERROR_MAIL_MAPI_READ_FAIL              966
#define AR_ERROR_MAIL_MAPI_LOGOFF_FAIL            967
#define AR_ERROR_MAIL_MAPI_SEND_FAIL              968
#define AR_NOTE_MAIL_QUERY_RESPONSE               969
#define AR_NOTE_MAIL_QUERY_MATCHES                970
#define AR_WARN_MAIL_MATCHES_LIMIT                971
#define AR_WARN_MAIL_MATCHES_NONE                 972
#define AR_WARN_MAIL_NO_FIELDS_IN_QL              973

/* messages for currency */
#define AR_ERROR_REQ_CURR_VALUE                   980
#define AR_ERROR_REQ_CURR_CODE                    981
#define AR_ERROR_BAD_CURR_VALUE                   982
#define AR_ERROR_NO_COMMON_FUNCTIONAL             983
#define AR_ERROR_NO_CURRENCY_CODES_SCHEMA         984
#define AR_ERROR_CURRENCY_CODE_NOT_ACTIVE         985
#define AR_ERROR_BAD_CURR_CODE_NOT_ALLOWED        986
#define AR_ERROR_CURR_NOT_ALLOWED_FOR_GROUPING    987
#define AR_ERROR_CURRENCY_PART_REQUIRED           988
#define AR_ERROR_FUNCTIONAL_CURRENCY_REQUIRED     989

/* messages for locking */
#define AR_ERROR_USER_LOCK_NOT_HELD               998
#define AR_ERROR_LOCK_NOT_HELD                    999

/* 1000 - 1999 BMC Remedy User tool errors */
/* 2000 - 2999 BMC Remedy Admin tool errors */

/* messages for distributed server */
#define ARDS_NOTE_SIGNAL_RECEIVED                3000
#define ARDS_NOTE_FATAL_EXIT                     3001
#define ARDS_NOTE_TIMEOUT                        3002
#define ARDS_NOTE_CANCELLED_ON_ERROR             3003
#define ARDS_NOTE_AR_SERVER_UNAVAILABLE          3004
#define ARDS_NOTE_AR_SERVER_AVAILABLE            3005

#define ARDS_ERROR_DIST_NOT_LICENSED             3100
#define ARDS_ERROR_LOCK_FILE_OPEN                3101
#define ARDS_ERROR_DUPLICATE_SERVER              3102
#define ARDS_ERROR_MALLOC_FAILED                 3103
#define ARDS_ERROR_SERVER_NOT_DISTRIB            3106
#define ARDS_ERROR_NO_MAPPING_SCHEMA             3107
#define ARDS_ERROR_2_MAPPING_SCHEMA              3108
#define ARDS_ERROR_NO_PENDING_SCHEMA             3109
#define ARDS_ERROR_2_PENDING_SCHEMA              3110
#define ARDS_ERROR_DIFF_FROM_SCHEMA              3111
#define ARDS_ERROR_DIFF_FROM_SERVER              3112
#define ARDS_ERROR_DIFF_TO_SCHEMA                3113
#define ARDS_ERROR_DIFF_TO_SERVER                3114
#define ARDS_ERROR_BAD_PENDING_TYPE              3115
#define ARDS_ERROR_NON_MASTER_TRANSFER           3116
#define ARDS_ERROR_NO_FROM_INFO                  3117
#define ARDS_ERROR_DISTRIB_FAIL                  3118
#define ARDS_ERROR_MAPPING_DISABLED              3119
#define ARDS_ERROR_BAD_PENDING_OTHER             3120
#define ARDS_ERROR_NEW_NEEDS_FROM_ID             3121
#define ARDS_ERROR_DISTRIB_ON_DELETE             3122
#define ARDS_ERROR_DS_ID_NOT_MAPPED              3123
#define ARDS_ERROR_OWNER_REQ_MASTER_TRG          3124
#define ARDS_ERROR_OWNER_REQ_FROM_SCHEMA         3125
#define ARDS_ERROR_OWNER_REQ_FROM_SERVER         3126
#define ARDS_ERROR_OWNER_REQ_MASTER_SRC          3127
#define ARDS_ERROR_2_DSOPOOL_SCHEMA              3128
#define ARDS_ERROR_NO_DSOPOOL_SCHEMA             3129
#define ARDS_ERROR_NO_DSOPENDING_ERR_SCHEMA      3130
#define ARDS_ERROR_2_PENDING_ERR_SCHEMA          3131
#define ARDS_ERROR_2_LOGICAL_MAP_SCHEMA          3132
#define ARDS_ERROR_NO_LOGICAL_MAP_SCHEMA         3133
#define ARDS_ERROR_NO_LOGICAL_NAME_FOUND         3134

#define ARDS_ERROR_MASTER_FLAG_BAD               3194
#define ARDS_ERROR_MISSING_ENTRY_ID              3195
#define ARDS_ERROR_MISSING_SCHEMA                3196
#define ARDS_ERROR_MISSING_SERVER                3197
#define ARDS_ERROR_DS_PARM_VALUE                 3198
#define ARDS_ERROR_BAD_DS_CMD_LINE               3199

/* messages for alert system */
#define AR_ERROR_BAD_DYNAMIC_INHERITANCE_PROP    3200
#define AR_ERROR_NO_DYNAMIC_INHERITANCE_PROP     3201
#define AR_ERROR_MISSING_DYNAMIC_INHERITANCE_FIELD 3202
#define AR_ERROR_PARSING_DYNAMIC_INHERITANCE_PROP 3203

/* Error for Allow Non-Admin to delete */
#define AR_ERROR_NO_NON_ADMIN_DELETE_FORM_PROP   3225

/* messages for alert system */
#define AR_ERROR_USER_ALREADY_REGISTERED         3226
#define AR_ERROR_INVALID_ALERT_PARAMS            3227
#define AR_ERROR_ALERT_INVALID_MERGE_OPTION      3228
#define AR_ERROR_NO_ALERT_EVENT_SCHEMA           3300
#define AR_ERROR_2_ALERT_EVENT_SCHEMA            3301
#define AR_ERROR_IMPORT_ALERT                    3302
#define AR_ERROR_MUST_BE_ALERT_USER              3303
#define AR_ERROR_ALERT_SOCKET                    3314
#define AR_ERROR_ALERT_SOCKET_TIMEOUT            3315
#define AR_ERROR_IMPORT_ALERT_ESCL               3316
#define AR_ERROR_INVALID_ALERT_MESSAGE           3317
#define AR_ERROR_ALERT_SOCKET_ADDR_IN_USE        3318
#define AR_ERROR_ALERT_SOCKET_PRE_CONNECT        3319

/* messages for server groups */
#define AR_ERROR_2_SG_OP_RANK_SCHEMAS            3320
#define AR_ERROR_NO_SG_OP_RANK_SCHEMA            3321
#define AR_ERROR_UNRECOGNIZED_SG_OPERATION       3322
#define AR_ERROR_IMPORT_SERVER_GROUP             3323
#define AR_ERROR_NOT_ALLOWED_IN_SERVER_GROUP     3324
#define AR_ERROR_SG_SIGNAL_FAILURE               3325
#define AR_ERROR_SG_NO_SERVER_ENTRY              3326
#define AR_WARN_SG_INTERVAL_BELOW_MINIMUM        3327
#define AR_ERROR_SG_AGENT_PROCESS_FAILURE        3328
#define AR_ERROR_SG_LICENSE_TAG_REQUIRED         3329
#define AR_ERROR_SG_LICENSE_TAG_NOT_ALLOWED      3330
#define AR_ERROR_SG_DIFFERENT_LICENSE_TAGS       3331
#define AR_WARN_SG_PENDING_MEMBER_CHNG           3332
#define AR_ERROR_INVAL_SG_OPERATION_DEFN         3333
#define AR_ERROR_INVAL_SG_LICENSE_ENTRY          3334
#define AR_WARN_SG_PENDING_INTERVAL_CHNG         3335
#define AR_WARN_SG_DUPLICATE_RANKING             3336
#define AR_WARN_SG_ACTION_POSTPONED              3337
#define AR_ERROR_SG_SOME_OPS_NO_FAILOVER         3338

/* messages for arsignald */
#define AR_ERROR_CANT_START_SIGNALD              3340
#define AR_ERROR_CANT_MAKE_SIGNALD_START_INFO    3341
#define AR_ERROR_CANT_WRITE_TO_SIGNALD           3342

/* messages for Report ARDBC Plug-in */
#define AR_ERROR_REPORT_NO_SCHEMA                3350
#define AR_ERROR_REPORT_TEMP_FILENAME            3351
#define AR_ERROR_REPORT_NO_CREATE_FILE           3352
#define AR_ERROR_REPORT_BAD_FIELD                3353
#define AR_ERROR_REPORT_BAD_SORT_FIELD           3354
#define AR_ERROR_REPORT_BAD_QUAL_FIELD           3355
#define AR_ERROR_REPORT_BAD_DEFN_FORMAT          3356
#define AR_ERROR_REPORT_MISSING_FIELD            3357

/* messages for the LDAP ARDBC Plug-in */
#define AR_ERROR_LDAP_CONNECT                    3375
#define AR_ERROR_LDAP_BAD_URL                    3376
#define AR_ERROR_LDAP_OP                         3377
#define AR_ERROR_LDAP_DN_NOT_CONFIGURED          3378
#define AR_ERROR_LDAP_DN_NO_VALUE                3379
#define AR_ERROR_LDAP_SEARCH_DN_TIMEDOUT         3380

/* messages for the BSM AREA Plug-in */
#define AR_ERROR_BMCAREA_NO_CONFIG_FILE          3400
#define AR_ERROR_BMCAREA_NO_ENDPOINT             3401
#define AR_ERROR_BMCAREA_UNABLE_TO_INIT          3402
#define AR_ERROR_BMCAREA_UNABLE_TO_TERM          3403

/* messages for application server */
#define ARAPP_NOTE_SIGNAL_RECEIVED               4500
#define ARAPP_NOTE_FATAL_EXIT                    4501
#define ARAPP_NOTE_CANCELLED_ON_ERROR            4502
#define ARAPP_NOTE_RELAUNCH                      4503
 
#define ARAPP_WARN_DUP_ROLE_FOUND                4510
#define ARAPP_WARN_NO_ADMIN_SCHEMA               4511
#define ARAPP_WARN_NO_NOTIFY_SCHEMA              4512
#define ARAPP_WARN_NO_FORM_SCHEMA                4513

#define ARAPP_ERROR_PASS_NOT_CONFIRMED           4549

#define ARAPP_ERROR_IMPORT_APPLICATION           4550
#define ARAPP_ERROR_MUST_BE_APPLIC               4551
#define ARAPP_ERROR_2_PENDING_SCHEMA             4552
#define ARAPP_ERROR_NO_PENDING_SCHEMA            4553
#define ARAPP_ERROR_APPLIC_FAIL                  4554
#define ARAPP_ERROR_CMD_NO_SCHEMA                4555
#define ARAPP_ERROR_CMD_BAD_SCHEMA               4556
#define ARAPP_ERROR_PARSE_TWO_SCHEMA             4557
#define ARAPP_ERROR_QUAL_LINE_BAD                4558
#define ARAPP_ERROR_ASSIGN_LINE_BAD              4559
#define ARAPP_ERROR_NO_DETAILS_SCHEMA            4560
#define ARAPP_ERROR_CMD_NO_FIELD                 4561
#define ARAPP_ERROR_CMD_BAD_FIELD                4562
#define ARAPP_ERROR_CMD_NO_ENTRY_ID              4563
#define ARAPP_ERROR_CMD_BAD_ENTRY_ID             4564
#define ARAPP_ERROR_NO_SIGNATURE_SCHEMA          4565
#define ARAPP_ERROR_NO_DETSIG_SCHEMA             4566
#define ARAPP_ERROR_NO_VALID_PARAM               4567
#define ARAPP_ERROR_CMD_INVALID_TIME             4568


#define ARAPP_ERROR_APPROVAL_NOT_LICENSED        4577
#define ARAPP_ERROR_2_LICENSE_TAGS               4578
#define ARAPP_ERROR_NO_LICENSE_TAGS              4579
#define ARAPP_ERROR_SCHEMA_NOT_LIC               4580
#define ARAPP_ERROR_MALLOC_FAILED                4581
#define ARAPP_ERROR_DUPLICATE_SERVER             4582
#define ARAPP_ERROR_LOCK_FILE_OPEN               4583
#define ARAPP_ERROR_2_DETAILS_SCHEMA             4584
#define ARAPP_ERROR_2_SIG_LINE_SCHEMA            4585
#define ARAPP_ERROR_NO_SIG_LINE_SCHEMA           4586
#define ARAPP_ERROR_2_PROCESS_SCHEMA             4587
#define ARAPP_ERROR_NO_PROCESS_SCHEMA            4588
#define ARAPP_ERROR_CMD_MISSING_DATA             4589
#define ARAPP_ERROR_2_RULE_SCHEMA                4590
#define ARAPP_ERROR_NO_RULE_SCHEMA               4591
#define ARAPP_ERROR_2_ALTERNATE_SCHEMA           4592
#define ARAPP_ERROR_NO_ALTERNATE_SCHEMA          4593
#define ARAPP_ERROR_2_MORE_INFO_SCHEMA           4594
#define ARAPP_ERROR_NO_MORE_INFO_SCHEMA          4595
#define ARAPP_ERROR_2_PROC_ADMIN_SCHEMA          4596
#define ARAPP_ERROR_NO_PROC_ADMIN_SCHEMA         4597
#define ARAPP_ERROR_2_ROLE_SCHEMA                4598
#define ARAPP_ERROR_NO_ROLE_SCHEMA               4599
#define ARAPP_ERROR_DETAIL_IS_ACTIVE             4600
#define ARAPP_ERROR_MULTI_NEXT_ERROR             4601
#define ARAPP_ERROR_SERVER_NOT_APPLIC            4602
#define ARAPP_ERROR_BAD_AD_HOC_FIELD             4603
#define ARAPP_ERROR_SIG_NEEDS_SIG                4604
#define ARAPP_ERROR_SIG_SAME_PROC                4605
#define ARAPP_ERROR_TWO_PROCESSES                4606
#define ARAPP_ERROR_ONLY_ONE_BUT_TWO             4607
#define ARAPP_ERROR_MI_NEEDS_MI                  4608
#define ARAPP_ERROR_NO_SUCH_PROCESS              4609
#define ARAPP_ERROR_NO_SCHEMA_PROCESS            4610
#define ARAPP_ERROR_NO_DETAIL_JOIN               4611
#define ARAPP_ERROR_NO_DETAIL_SIG_JOIN           4612
#define ARAPP_ERROR_CFG_MISSING_DATA             4613
#define ARAPP_ERROR_NAME_TO_ID_MAP_FAIL          4614
#define ARAPP_ERROR_GET_DETSIG_FAIL              4615
#define ARAPP_ERROR_2_ADMIN_SCHEMA               4616
#define ARAPP_ERROR_2_NOTIFY_SCHEMA              4617
#define ARAPP_ERROR_2_FORM_SCHEMA                4618
#define ARAPP_ERROR_2_PREVIEW_SIG_LINE_SCHEMA    4619
#define ARAPP_ERROR_NO_PREVIEW_SIG_LINE_SCHEMA   4620
#define ARAPP_ERROR_2_ADHOC_DET_SCHEMA           4622
#define ARAPP_ERROR_NO_ADHOC_DET_SCHEMA          4623


#define ARAPP_ERROR_NO_FIELD_ESCAPED             4650
#define ARAPP_ERROR_NO_FIELD_SCHEMA              4651
#define ARAPP_ERROR_NO_FIELD_ENTRY_ID            4652
#define ARAPP_ERROR_NO_FIELD_NEXT_APP            4653
#define ARAPP_ERROR_NO_FIELD_PROCESS             4654

/* messages for zero downtime install 4700-4799 */
#define AR_ERROR_ZDT_UPGRADE_INVALID_MODE        4700    /* Invalid install state requested, must be 0-6 */
#define AR_ERROR_ZDT_UPGRADE_INVALID_ADMIN_STATE 4701    /* Invalid install admin state requested, must be 0-2 */
#define AR_ERROR_ZDT_UPGRADE_BAD_NEW_MODE        4702    /* Can't set to new state from current state */
#define AR_ERROR_ZDT_UPGRADE_INVALID_ROLLBACK    4703    /* Can't rollback now (not in phase 3) */
#define AR_ERROR_ZDT_UPGRADE_BAD_INSTALL_SIG_REQ 4704    /* Unrecognized zero downtime installer signal */
#define AR_ERROR_ZDT_UPGRADE_WRONG_CACHE_MODE    4705    /* Must be in production cache mode */
#define AR_ERROR_ZDT_UPGRADE_OPS_RESTRICTED_NOW  4706    /* Admin operations restricted due to installation */
#define AR_ERROR_ZDT_UPGRADE_IN_PROCESS_OP_ONLY  4707    /* This operation can only be done during upgrade mode InProcess */
#define AR_ERROR_ZDT_UPGRADE_INSTALLER_REQUIRED  4708    /* Admin operations restricted to installer or special user */
#define AR_ERROR_ZDT_UPGRADE_MUST_BE_INST_HOST   4709    /* This operation can only be done by the install host */
#define AR_ERROR_ZDT_UPGRADE_SET_NOT_PERMITTED   4710    /* This form is read only during install */
#define AR_ERROR_ZDT_UPGRADE_IMPORT_OPT_CONFLICT 4711    /* Import options conflict (typically overwrite and create only) */
#define AR_ERROR_ZDT_UPGRADE_COPYING_METADATA    4720    /* Error copying metadata table */
#define AR_ERROR_ZDT_UPGRADE_DROPPING_METADATA   4721    /* Error dropping metadata table */
#define AR_ERROR_ZDT_UPGRADE_DEFERRED_DELETE_TAB 4725    /* Error creating deferred delete table */
#define AR_ERROR_ZDT_UPGRADE_DEFERRED_DELETE_ENT 4726    /* Error creating/deleting entry in deferred delete table */
#define AR_ERROR_ZDT_UPGRADE_ALT_DATA_FORM_TAB   4730    /* Error creating or dropping alt data form table in DB */
#define AR_ERROR_ZDT_UPGRADE_ALT_DATA_FORM_COPY  4731    /* Error creating alternate data tables in DB */
#define AR_ERROR_ZDT_UPGRADE_ALT_DATA_FORM_REST  4732    /* Error during restore or rollback of alt data tables in DB */
#define AR_ERROR_ZDT_UPGRADE_ALT_DATA_FORM_OP    4733    /* Error processing alt data form entry */
#define AR_ERROR_ZDT_UPGRADE_ALT_DATA_FORM_TYPE  4734    /* Warning, unsupported form type */
#define AR_ERROR_ZDT_UPGRADE_ARCHGID_TABLE       4735    /* Error creating or dropping ArChgId Restore table in DB */
#define AR_ERROR_ZDT_UPGRADE_ARCHGID_ENTRY       4736    /* Error retrieving/inserting entry in ArChgId Restore table */
#define AR_ERROR_ZDT_UPGRADE_ARCHGID_RENAME      4737    /* Error renaming table or column in ArChgId Restore table */
#define AR_ERROR_ZDT_UPGRADE_NO_ALT_TABLENAMES   4740    /* No alternate metadata table names table */
/* end of messages for zero downtime install 4700-4799 */

#define ARPR_WARN_DUP_CATEGORY_FOUND             4810
 
#define ARSUM_ERROR_MALLOC_FAILED                4820
#define ARSUM_ERROR_GROUP_MISSING                4821
 
#define ARAPS_ERROR_TWO_MATCHING_SCHEMA          4830
#define ARAPS_ERROR_NO_MATCHING_SCHEMA           4831
 
#define ARPR_ERROR_CMD_MISSING_DATA              4836
#define ARPR_ERROR_CAT_NEEDS_PARTS               4837
#define ARPR_ERROR_MALLOC_FAILED                 4838
#define ARPR_ERROR_PART_NO_PARENT                4839
#define ARPR_ERROR_NO_SUCH_CATEGORY              4840
#define ARPR_ERROR_CATALOG_FILE_ERROR            4841
#define ARPR_ERROR_PART_TYPE_BAD                 4842
#define ARPR_ERROR_PART_ROW_COUNT_BAD            4843
#define ARPR_ERROR_MAP_NEEDS_PURREQ              4844
#define ARPR_ERROR_2_LINE_MAP_SCHEMA             4845
#define ARPR_ERROR_SUPPLIER_NULL                 4846
#define ARPR_ERROR_MAPB_NEEDS_LINEITEM           4847
#define ARPR_ERROR_MAPBACK_NO_LINE               4848
#define ARPR_ERROR_MAPBACK_NO_ENTRY              4849
#define ARPR_ERROR_NO_PENDING_ID                 4850
#define ARPR_ERROR_LINE_MAP_FAILURE              4851
#define ARPR_ERROR_LINE_MAPBACK_FAILURE          4852
#define ARPR_ERROR_CMD_MISSING_DATA2             4853
#define ARPR_ERROR_CMD_MISSING_DATA3             4854
#define ARPR_ERROR_CMD_MISSING_DATA4             4855
#define ARPR_ERROR_NO_PR_LI_SCHEMA               4856
#define ARPR_ERROR_LINE_ITEM_BOUNDS_ERR          4857

/* Range 4900 - 4999 reserved for Email Engine messages */

/* Range 5000 - 5999 reserved for Dev Studio messages */

/* Range 6000 - 6499 reserved for ARS clients */

/* Range 6500 - 4599 reserved for Email Engine messages */

/* Range 6600 - 6699 reserved for the query widget */

/* Range 6700 - 6999 is currently free */

/* Range 7000 - 7999 reserved for AR Admin Messages */

/* Error Handling Errors and Other Filter errors */
#define AR_ERROR_NO_HANDLER                      8000
#define AR_ERROR_BAD_ERRORHANDLER_SIZE           8001
#define AR_ERROR_ERROR_HANDLER_MAX_STACK         8002
#define AR_ERROR_ERROR_HANDLER_NOT_FOUND         8003
#define AR_ERROR_SAME_ERRORHANDLER_NAME          8004
#define AR_ERROR_NO_FILTER_CONTEXT               8005

#define AR_ERROR_FILTER_ANY_MATCH                8029

/* additional warning messages */
#define AR_WARN_UNSUP_FIELD_OR_WORKFLOW          8031
#define AR_WARN_CONT_OWN_NO_ADMIN_GRP            8032
#define AR_WARN_FLOAT_TIMEOUT_PEND_CHNG          8033
#define AR_WARN_FULL_TIMEOUT_PEND_CHNG           8034
#define AR_WARN_EXPORT_MISSING_MENUS             8035
#define AR_WARN_EXTRA_TEXT_AFTER_PARSE           8036
#define AR_WARN_INDEX_LEN_TOO_LONG               8037
#define AR_WARN_MERGE_WORKFLOW_FIRING            8038
#define AR_WARN_SQL_UNSUPPORT_DB_CONFIG          8039

#define AR_WARN_MIN_2                            8031
#define AR_WARN_MAX_2                            8200

/* additional RPC error messages */
#define AR_ERROR_RPC_SOCKET_RANGE                8201
#define AR_ERROR_RPC_PORT_RANGE                  8202
#define AR_ERROR_RPC_BAD_SERVER_VERS             8203
#define AR_WARN_RPC_NON_BLOCKING_FAILURE         8204
/* Message for busy port */
#define AR_WARN_PORT_BUSY                        8205

/* messages for version control 8301 - 8407 */
#define AR_ERROR_VERCNTL_RESERVATION_CREATE_DUP  8301
#define AR_ERROR_VERCNTL_RESERVATION_MODE        8302
#define AR_ERROR_VERCNTL_OBJ_RESERVED_BY_OTHERS  8303
#define AR_ERROR_VERCNTL_FORM_RESERVED           8304
#define AR_ERROR_VERCNTL_FILTER_RESERVED         8305
#define AR_ERROR_VERCNTL_ACTIVE_LINK_RESERVED    8306
#define AR_ERROR_VERCNTL_CHAR_MENU_RESERVED      8307
#define AR_ERROR_VERCNTL_ESCALATION_RESERVED     8308
#define AR_ERROR_VERCNTL_CONTAINER_RESERVED      8309
#define AR_ERROR_VERCNTL_APP_RESERVED            8310
#define AR_ERROR_VERCNTL_IMAGE_RESERVED          8311
#define AR_ERROR_VERCNTL_DEPENDED_FORM_RESERVED          8312
#define AR_ERROR_VERCNTL_RELATED_FILTER_RESERVED         8313
#define AR_ERROR_VERCNTL_RELATED_ACTIVE_LINK_RESERVED    8314
#define AR_ERROR_VERCNTL_RELATED_ESCALATION_RESERVED     8315
#define AR_ERROR_VERCNTL_OWNER_CONTAINER_RESERVED        8316
#define AR_ERROR_VERCNTL_OWNER_APP_RESERVED              8317
#define AR_ERROR_VERCNTL_CANNOT_RESERVE_NONE_EXIST_OBJ   8318
#define AR_ERROR_VERCNTL_OBJ_MOD_LOG_MODE        8351
#define AR_ERROR_VERCNTL_TASK_CREATE_DUP         8352
#define AR_ERROR_VERCNTL_OBJ_MOD_LOG_CREATE_DUP  8353
#define AR_WARN_VERCNTL_OBJ_MOD_LOG_FAILED       8354
#define AR_ERROR_VERCNTL_OBJ_MOD_LOG_SAVE_DEF    8355
#define AR_ERROR_VERCNTL_LABEL_CREATE_DUP        8356
#define AR_ERROR_VERCNTL_LABELED_OBJ_CREATE_DUP  8357
#define AR_WARN_VERCNTL_LABEL                    8358
#define AR_WARN_VERCNTL_LABELED_OBJ              8359
#define AR_ERROR_VERCNTL_TASK_FORM_RESERVED                   8360
#define AR_ERROR_VERCNTL_TASK_FILTER_RESERVED                 8361
#define AR_ERROR_VERCNTL_TASK_ACTIVE_LINK_RESERVED            8362
#define AR_ERROR_VERCNTL_TASK_CHAR_MENU_RESERVED              8363
#define AR_ERROR_VERCNTL_TASK_ESCALATION_RESERVED             8364
#define AR_ERROR_VERCNTL_TASK_CONTAINER_RESERVED              8365
#define AR_ERROR_VERCNTL_TASK_APP_RESERVED                    8366
#define AR_ERROR_VERCNTL_TASK_IMAGE_RESERVED                  8367
#define AR_ERROR_VERCNTL_TASK_DEPENDED_FORM_RESERVED          8368
#define AR_ERROR_VERCNTL_TASK_RELATED_FILTER_RESERVED         8369
#define AR_ERROR_VERCNTL_TASK_RELATED_ACTIVE_LINK_RESERVED    8370
#define AR_ERROR_VERCNTL_TASK_RELATED_ESCALATION_RESERVED     8371
#define AR_ERROR_VERCNTL_TASK_OWNER_CONTAINER_RESERVED        8372
#define AR_ERROR_VERCNTL_TASK_OWNER_APP_RESERVED              8373

#define AR_ERROR_TASK_NOT_FOUND                  8400
#define AR_ERROR_DUPLICATE_TASK                  8401
#define AR_ERROR_TASK_CHECKPOINT_NOT_FOUND       8402
#define AR_ERROR_DUPLICATE_TASK_CHECKPOINT       8403
#define AR_ERROR_TASK_CREATIION                  8404
#define AR_ERROR_CHECKPOINT_CREATIION            8405
#define AR_ERROR_CANNOT_DELETE_OPEN_TASK         8406
#define AR_ERROR_NOT_TASK_OWNER                  8407

/* Available for server errors 8408 - 8600 */
#define AR_ERROR_JOIN_BASE_FIELD_MISMATCH        8408
#define AR_ERROR_EXISTING_AND_NEW_FIELD_DATATYPE_MISMATCH   8409

/* more param validation errors */
#define AR_ERROR_BAD_LOC_TYPE                    8700
#define AR_ERROR_BAD_LOC_BUF_SIZE                8701
#define AR_ERROR_BAD_LOC_BUF_PTR                 8702
#define AR_ERROR_BAD_BLOB_SIZE                   8703
#define AR_ERROR_AUTO_EMPTY                      8704
#define AR_ERROR_COM_METHODLIST_EMPTY            8705
#define AR_ERROR_COM_VALUE_BAD                   8706
#define AR_ERROR_COM_NAME_BAD                    8707
#define AR_ERROR_COM_ID_BAD                      8708
#define AR_ERROR_COM_METHOD_BAD                  8709
#define AR_ERROR_COM_METHOD_NAME_BAD             8710
#define AR_ERROR_COM_METHOD_EMPTY                8711
#define AR_ERROR_COM_PARMLIST_EMPTY              8712
#define AR_ERROR_COM_PARM_EMPTY                  8713
#define AR_ERROR_COM_PARM_BAD                    8714
#define AR_ERROR_AUTO_STRING_BAD                 8715
#define AR_ERROR_AP_RPC_SOCKET_BAD               8716
#define AR_ERROR_AP_DEFN_CHECK_BAD               8717
#define AR_WARN_BAD_SIGNAL                       8718

#define AR_WARN_GUIDEMODE_BAD                    8719
#define AR_ERROR_OPENDLG_EMPTY                   8720
#define AR_ERROR_CALLGUIDE_EMPTY                 8721
#define AR_ERROR_GUIDENAME_MISSING               8722
#define AR_ERROR_GOTOLABEL_BAD                   8723 
#define AR_ERROR_BAD_GOTOACTION_TAG              8724
#define AR_ERROR_CONTTITLE_BAD                   8725
#define AR_ERROR_GUIDE_CALL_ITSELF_DISALLOWED    8726
#define AR_ERROR_BAD_VENDOR_MAP_NAME             8727
#define AR_ERROR_BAD_VENDOR_SCHEMA               8728
#define AR_ERROR_NO_VENDOR_IN_JOIN               8729
#define AR_ERROR_NO_CHANGE_JOIN_FIELDMAP         8730
#define AR_ERROR_NO_CHANGE_FIELDMAP_TYPE         8731
#define AR_ERROR_BAD_CLIENT_TYPE                 8732
#define AR_ERROR_CURR_PART_TAG_BAD               8733
#define AR_ERROR_BAD_CURR_CODE_LEN               8734
#define AR_ERROR_BAD_DEC_VALUE                   8735
#define AR_ERROR_BAD_DEC_CALC                    8736
#define AR_ERROR_NOTIFY_HEADER_BAD               8737
#define AR_ERROR_NOTIFY_FOOTER_BAD               8738
#define AR_ERROR_NOTIFY_CONTENT_BAD              8739

/* messages related to thread management */
#define AR_ERROR_CREATE_THREAD_FAILED            8740
#define AR_ERROR_CREATE_MUTEX_FAILED             8741
#define AR_ERROR_CREATE_SEM_FAILED               8742
#define AR_ERROR_LOCK_MUTEX_FAILED               8743
#define AR_ERROR_SEM_OP_FAILED                   8744
#define AR_ERROR_CREATE_QUEUE_FAILED             8745
#define AR_ERROR_CREATE_TLS_FAILED               8746
#define AR_ERROR_ACCESS_TLS_FAILED               8747
#define AR_ERROR_SEM_TIMEOUT                     8748
#define AR_ERROR_NEAR_STACK_LIMIT                8749

/* messages related to plug-ins (e.g. ARDBC) */
#define AR_ERROR_ARDBC_NO_CREATE                 8750
#define AR_ERROR_ARDBC_NO_SET                    8751
#define AR_ERROR_ARDBC_NO_DELETE                 8752
#define AR_ERROR_IN_PLUGIN                       8753
#define AR_ERROR_ARDBC_NO_GETBLOB                8754
#define AR_ERROR_NO_PLUGIN                       8755
#define AR_ERROR_PLUGIN_LOAD                     8756
#define AR_ERROR_FILTER_API_DEF_BAD              8757
#define AR_ERROR_INVALID_PLUGIN_NAME             8758
#define AR_ERROR_NO_PLUGIN_IDENTIFY              8759
#define AR_ERROR_PLUGIN_CONNECT                  8760
#define AR_ERROR_PLUGIN_BAD_PASSWORD             8761
#define AR_ERROR_PLUGIN_HAD_FAILED_INIT          8762
#define AR_ERROR_PLUGIN_HAD_FAILED_SETPROP       8763
#define AR_ERROR_PLUGIN_NATIVE_PLUGINHOST_LOAD   8764
#define AR_ERROR_PLUGIN_JNI_TYPE_INIT            8765
#define AR_ERROR_PLUGIN_NATIVE_PLUGINHOST_CALL   8766
#define AR_ERROR_PLUGIN_JAVAWRAPPER_LOAD         8767
#define AR_ERROR_PLUGIN_CONFIG_LOAD              8768
#define AR_ERROR_PLUGIN_CONFIG                   8769
#define AR_ERROR_PLUGIN_LOOPBACK_RPC_SOCKET_BAD  8770
#define AR_ERROR_PLUGIN_DUPLICATE                8771
#define AR_ERROR_DUPLICATE_USER                  8780
#define AR_PLUGIN_INVLAID_CMD_LINE_ARGS          8781
#define AR_PLUGIN_INVALID_PORT_NUMBER            8782
#define AR_PLUGIN_UNKNOWN_HOSTNAME               8783
#define AR_ERROR_ENCRYPTION_FAILED               8784
#define AR_ERROR_DECRYPTION_FAILED               8785
#define AR_ERROR_PPKEYPAIR_CREATION              8786
#define AR_ERROR_GET_PRIVATEKEY                  8787
#define AR_ERROR_GET_PUBLICKEY                   8788
#define AR_ERROR_STRING_ENCODING                 8789
#define AR_PLUGIN_ERROR_UNKOWN                   8790
#define AR_PLUGIN_STARTUP_MESSAGE                8791
#define AR_PLUGIN_ERROR_NATIVE_LIBRARY_LOAD      8792 
#define AR_PLUGIN_ERROR_STARTUP                  8793
#define AR_PLUGIN_ERROR_TERMINATE                8794
#define AR_PLUGIN_ERROR_CREATEINSTANCE           8795
#define AR_PLUGIN_ERROR_DELETEINSTANCE           8796
#define AR_ERROR_BYTE_ENCODING                   8797
#define AR_ERROR_INVALID_PLUGIN_PORT             8798

/* param validation errors for container */
#define AR_ERROR_CON_OWNER_ITEM                  8800
#define AR_ERROR_REF_VALUE_EMPTY                 8801
#define AR_ERROR_REF_LABEL_EMPTY                 8802
#define AR_ERROR_REF_DESCR_EMPTY                 8803
#define AR_ERROR_NO_SUCH_CONTAINER               8804
#define AR_ERROR_NO_ACCESS_TO_CONTAINER          8805
#define AR_ERROR_CONTAINER_MISSING               8806
#define AR_ERROR_CTR_OPEN_FAILED                 8807
#define AR_ERROR_NOT_A_CTR_FILE                  8808
#define AR_ERROR_BAD_CONTAINER_TYPE              8809
#define AR_ERROR_DUPLICATE_CONTAINER             8810
#define AR_ERROR_NO_OWNER_NAME                   8811
#define AR_ERROR_ILLEGAL_OWNER_TYPE              8812
#define AR_ERROR_CONTAINER_FILE_ERROR            8813
#define AR_ERROR_NO_CONTAINERID                  8814
#define AR_ERROR_NO_CONTAINER_DEFN               8815
#define AR_ERROR_BAD_REFERENCE_TYPE              8816
#define AR_ERROR_REF_VALUE_BAD                   8817
#define AR_ERROR_CONTAINER_UNSUP_BY_SVR          8818
#define AR_WARN_APP_OWNER_MISMATCH               8819

/* object locking warnings and errors */
#define AR_NOTE_OBJ_LOCK_NOT_SUPPORTED           8830
#define AR_WARN_OBJ_LOCK_DECREASE_NOT_ALLOWED    8831
#define AR_ERROR_OBJ_LOCK_UNKNOWN_LOCKTYPE       8832
#define AR_WARN_OBJ_LOCK_KEY_CANNOT_CHANGE       8833
#define AR_ERROR_OBJ_LOCK_INFO_MISMATCH          8834
#define AR_ERROR_OBJ_LOCK_CACHE_LOAD_FAILED      8835
#define AR_ERROR_OBJ_LOCK_BLOCK_NOT_FOUND        8836
#define AR_NOTE_EOF_REACHED                      8837
#define AR_WARN_GET_HIDDEN_LOCKED_OBJ            8838
#define AR_ERROR_DELETE_LOCKED_OBJ               8839
#define AR_WARN_SET_LOCKED_OBJ                   8840
#define AR_ERROR_SAFEGUARD_MISMATCH_SCHEMA       8841 /* to be removed */
#define AR_ERROR_SAFEGUARD_MISMATCH_CONTAINER    8842 /* to be removed */
#define AR_ERROR_SAFEGUARD_MISMATCH_ACTLINK      8843 /* to be removed */
#define AR_ERROR_SAFEGUARD_MISMATCH_FILTER       8844 /* to be removed */
#define AR_ERROR_SAFEGUARD_MISMATCH_ESCALATION   8845 /* to be removed */
#define AR_ERROR_SAFEGUARD_MISMATCH_CHAR_MENU    8846 /* to be removed */
#define AR_ERROR_CREATEFIELD_ON_LOCKED_SCHEMA    8847
#define AR_ERROR_DELETEFIELD_ON_LOCKED_SCHEMA    8848
#define AR_WARN_SETTING_LOCK_PROP_DISALLOWED     8849
#define AR_ERROR_XML_DEF_MIXED_EXPORT_NOT_ALLOWED 8850

/* more param validation errors */
#define AR_WARN_SETTING_BSM_TAG_DISALLOWED                     8851
#define AR_ERROR_SVR_SETTING_OUT_OF_RANGE                      8852
#define AR_ERROR_INVALID_LOCALE                                8853
#define AR_WARN_CHILDREN_NOT_PROCESSED                         8854
#define AR_ERROR_SAFEGUARD_MISMATCH_IMAGE                      8855 /* to be removed */

/* Overlay related error messages */
#define AR_ERROR_OVERLAY_OF_OVERLAY_DISALLOWED                 8856
#define AR_ERROR_INVALID_OBJECT_FOR_OVERLAY                    8857
#define AR_ERROR_USING_RESERV_STRING_IN_NAME                   8858
#define AR_ERROR_OVERLAY_INVALID_OP                            8859
#define AR_ERROR_OVERLAY_INVALID_GROUP                         8860
#define AR_ERROR_OVERLAY_BASE_CUSTOM_TYPE_MISMATCH             8861
#define AR_ERROR_CUSTOM_SUFFIX_ERROR                           8862
#define AR_ERROR_FIELD_VUI_OVERLAY_ON_NONOVERLAY_SCHEMA        8863
#define AR_ERROR_OVERLAY_INVALID_OVERLAY_PROP                  8864
#define AR_ERROR_FIELD_VUI_OVERLAY_GROUP_MISMATCH_WITH_SCHEMA  8865
#define AR_ERROR_SHADOW_FORM_OVERLAY_GROUP_MISMATCH_WITH_SCHEMA 8866
#define AR_ERROR_OVERLAY_OBJ_DOES_NOT_EXIST                    8867
#define AR_ERROR_FIELD_OVERLAY_GROUP_MISMATCH_WITH_VUI         8868
#define AR_ERROR_OVERLAY_BASE_CUSTOM_FIELD_ID_MISMATCH         8869
#define AR_ERROR_OVERLAY_BASE_CUSTOM_SCHEMA_MISMATCH           8870
#define AR_ERROR_OVERLAY_INVALID_CUSTOM_FIELD                  8871
#define AR_ERROR_OVERLAID_OBJ_DOES_NOT_EXIST                   8872
#define AR_ERROR_RENAMING_OVERLAY_DISALLOWED                   8873
#define AR_ERROR_INVALID_OBJECT_FOR_BASE_CONVERSION            8874
#define AR_ERROR_INVALID_SHADOW_FORM_OVERLAY_PROP              8875
#define AR_ERROR_INVALID_OBJECT_FOR_CUSTOM_CONVERSION          8876
#define AR_ERROR_BASE_MODE_ACCESS_DENIED                       8877
#define AR_ERROR_OVERLAY_MODE_ACCESS_DENIED                    8878
#define AR_ERROR_SELF_OVERLAY_CONVERSION_DISALLOWED            8879
#define AR_ERROR_BASE_REFERENCE_TO_OVERLAY_OR_CUSTOM           8880
#define AR_ERROR_CONVERT_OVERLAY_NOTRESERVED_FIELD_ID          8881
#define AR_ERROR_BASE_REF_ADD_REMOVE_ON_CUSTOM_APP             8882
#define AR_ERROR_SHADOW_FORM_APP_OVERLAY_REQUIRED              8883
#define AR_ERROR_CUSTOM_FORM_APP_OVERLAY_REQUIRED              8884
#define AR_ERROR_BASE_OVERLAY_DEPAPP_DATA_FORM_QUAL_MISMATCH   8885
#define AR_ERROR_FLD_NOT_ON_OVERLAY_VUI_INVALID_DISPPROP       8886
#define AR_ERROR_DATA_OPERATIONS_DENIED_FOR_FULL_MODE          8887
#define AR_ERROR_INVALID_OVERLAY_VUI_CHANGED_FIELDLIST         8888

#define AR_ERROR_INVALID_OVERLAY_MASK            8890
#define AR_ERROR_INVALID_OVERLAY_APPEND_MASK     8891 /* to be removed */
#define AR_ERROR_INVALID_OVERLAY_EXTEND_MASK     8891
#define AR_ERROR_INVALID_OVERLAY_INHERIT_MASK    8892

#define AR_ERROR_SHADOW_FORM_APP_OVERLAY_OVERWRITE_REQUIRED    8893

#define AR_ERROR_GETLISTFIELDS_NOT_ALLOWED       8900 
#define AR_WARN_GETLISTFIELDS_IGNORED            8901
#define AR_ERROR_SORTLIST_NOT_ALLOWED            8902
#define AR_WARN_SORTLIST_IGNORED                 8903
#define AR_ERROR_FILTER_NOT_ALLOWED              8904
#define AR_ERROR_ESCALATION_NOT_ALLOWED          8905
#define AR_ERROR_CORE_FIELD_NOT_ALLOWED          8906
#define AR_ERROR_MUST_BE_DISPLAY_FIELD           8907
#define AR_ERROR_ILLEGAL_USER_OR_PWD             8908
#define AR_ERROR_NO_DIALOG_OR_PLACEHLDR_IN_JOIN  8909
#define AR_ERROR_FIELD_IN_TABLE_QUAL             8910
#define AR_WARN_FIELD_LIST_TRUNCATED             8911
#define AR_ERROR_GLEWF_UNSUP_BY_SVR              8912
#define AR_ERROR_SEMAPHORE                       8913
#define AR_NOTE_LOG_INFO                         8914
#define AR_WARN_WRITE_LOGFILE                    8915
#define AR_ERROR_UPDATE_NEXT_FIELD               8916
#define AR_ERROR_GET_NEXT_FIELD                  8917
#define AR_ERROR_UPDATE_NEXT_VUI                 8918
#define AR_ERROR_GET_NEXT_VUI                    8919
#define AR_ERROR_NO_SUCH_WORKFLOW                8920
#define AR_ERROR_NO_SCHEMALIST                   8921
#define AR_ERROR_CONNECT_TO_EXTAUTH              8922
#define AR_ERROR_BAD_CONN_TYPE                   8923
#define AR_ERROR_DUPLICATED_SCHEMA               8924
#define AR_ERROR_EA_RPC_SOCKET_BAD               8925
#define AR_NOTE_EA_MESSAGE                       8926
#define AR_ERROR_EA_MESSAGE                      8927
#define AR_ERROR_OPEN_APPL_AUDIT_LOG             8928
#define AR_ERROR_OPEN_APPL_VIOLATION_LOG         8929
#define AR_ERROR_SCHEMA_NOT_IN_CACHE             8930
#define AR_ERROR_EVENT_NAME                      8931
#define AR_ERROR_NO_WRITE_LICENSE                8932
#define AR_WARN_NO_VUIS_IMPORTED_INTO_SCHEMA     8933
#define AR_ERROR_NO_ARFORKD                      8934
#define AR_ERROR_UPGRD_INTERNAL_SCHEMA           8935
#define AR_ERROR_COMPRESSION_FAILURE             8936
#define AR_ERROR_CLIENT_OPERATION_DISABLED       8937
#define AR_ERROR_XML_INIT_FAILED                 8938
#define AR_ERROR_CONNECT_TO_PLUGIN_SERVER        8939
#define AR_ERROR_XML_DEFN_PARSING                8940
#define AR_ERROR_XML_UNKNOWN_ELEMENT_TAG         8941
#define AR_ERROR_XML_UNKNOWN_ATTRIBUTE_TAG       8942
#define AR_ERROR_XML_UNKNOWN_ENUMERATION_TAG     8943
#define AR_ERROR_XML_PARSING_DATA                8944
#define AR_ERROR_XML_NO_SUCH_OBJECT              8945
#define AR_ERROR_EXTERNAL_QUAL_REF               8946
#define AR_ERROR_INVALID_LICENSE_KEY             8947
#define AR_ERROR_INVALID_API_CONFIG_VAR          8948
#define AR_ERROR_ENUM_STYLE_BAD                  8949
#define AR_ERROR_ENUM_NUM_NOT_UNIQUE             8950
#define AR_ERROR_STATUS_NOT_ENUM_QUERY           8951
#define AR_ERROR_XML_INVALID_DOC_TYPE            8952
#define AR_ERROR_ARXML_LIB_LOAD_FAILED           8953
#define AR_ERROR_FILE_OPEN_FAILED                8954
#define AR_ERROR_XML_IMP_EXP_NOT_SUPPPORTED      8955
#define AR_ERROR_INVALID_DATEPARTS               8956
#define AR_ERROR_INVALID_DATE_FORMAT             8957
#define AR_ERROR_INVALID_DATE_VALUE              8958
#define AR_ERROR_UNSUPPORTED_XML_DATA_TYPE       8959
#define AR_ERROR_SERVER_INFO_FORMAT              8960
#define AR_ERROR_EXPECTED_XML_INPUT_ELEMENT      8961
#define AR_ERROR_UNEXPECTED_XML_INPUT_ELEMENT    8962
#define AR_ERROR_NUM_ENTRIES_EXCEEDS_XML_MAX     8963
#define AR_ERROR_NUM_ENTRIES_LESS_THAN_XML_MIN   8964
#define AR_ERROR_NO_DEFAULT_NOTIFICATION_FROM    8965
#define AR_ERROR_MISSING_XML_MAPPING_ELEMENT     8966
#define AR_ERROR_MISSING_XML_MAPPING_ATTRIBUTE   8967
#define AR_ERROR_ILLEGAL_PROCESS_STRING          8968
#define AR_ERROR_EXPECTED_XML_INPUT_ATTRIBUTE    8969
#define AR_ERROR_DISTINGUISH_KEY_NOT_UNIQUE      8970
#define AR_ERROR_DUP_USER_PREF_USER              8971
#define AR_ERROR_DUP_USER_PREF_ADMIN             8972
#define AR_ERROR_DUP_USER_PREF_FILE              8973
#define AR_ERROR_NOTIFY_FROM_BAD                 8974
#define AR_ERROR_NOTIFY_REPLYTO_BAD              8975
#define AR_ERROR_NOTIFY_CC_BAD                   8976
#define AR_ERROR_NOTIFY_BCC_BAD                  8977
#define AR_ERROR_NOTIFY_ORGANIZATION_BAD         8978
#define AR_ERROR_NOTIFY_MAILBOXNAME_BAD          8979
#define AR_ERROR_SYSTEM_DEFN_FILE_OPEN_FAILED    8980
#define AR_WARN_SETTING_APP_OWNER_DISALLOWED     8981
#define AR_ERROR_OBJ_ALREADY_OWNED               8982
#define AR_ERROR_NO_CHANGE_FIELD_DATA_TYPE       8983
#define AR_WARN_GROUP_PERMISSIONS_REMOVED        8984
#define AR_WARN_ROLE_PERMISSIONS_REMOVED         8985
#define AR_WARN_WEB_ALIAS_NOT_UNIQUE             8986
#define AR_ERROR_CHANGE_FIELD_OPTION_BAD         8987

/* archive warnings and errors */
#define AR_ERROR_UNABLE_TO_MODIFY_SHADOW_INFO    8988
#define AR_ERROR_CANNOT_DELETE_SHADOW_FIELD      8989
#define AR_ERROR_CANNOT_MODIFY_SHADOW_FIELD      8990
#define AR_ERROR_CANNOT_CREATE_SHADOW_FIELD      8991
#define AR_ERROR_UNABLE_TO_CREATE_SHADOW_FORM    8992
#define AR_ERROR_ARCHIVE_NAME_NOT_PRESENT        8993
#define AR_ERROR_SHADOW_FORM_NOT_IN_APP          8994
#define AR_ERROR_INVALID_ARCHIVE_TYPE            8995
#define AR_ERROR_ARCHIVE_NOT_ALLOWED             8996
#define AR_ERROR_CANNOT_DELETE_SHADOW            8997
#define AR_ERROR_CANNOT_MODIFY_SHADOW_FORM_DATA  8998
#define AR_ERROR_INVALID_SHADOW_FORM             8999

/* encryption errors */
#define AR_ERROR_ENCRYPTION_DISALLOWED           9000
#define AR_ERROR_ENCRYPTION_REQUIRED             9001
#define AR_ERROR_KEY_EXCHANGED_FAILED            9002
#define AR_ERROR_BAD_PUB_KEY_DECRYPTION          9003
#define AR_ERROR_BAD_DATA_DECRYPTION             9004
#define AR_ERROR_ENCRYPT_LIBRARY                 9005
#define AR_ERROR_UNSUPPORTED_PUBLIC_KEY_ALG      9006
#define AR_ERROR_UNSUPPORTED_DATA_ENC_KEY_ALG    9007
#define AR_ERROR_XDR_SIZEOF_INVALID_SIZE         9008
#define AR_ERROR_XDR_RES_FAILED                  9009
#define AR_ERROR_NO_ENCRYPTION_LIB               9010
#define AR_ERROR_ENCRYPTION_LIB_LOAD_FAILED      9011
#define AR_ERROR_NO_ENCRYPTION_LICENSE           9012
#define AR_ERROR_ENCRYPT_LICENSE_MISMATCH        9013
#define AR_ERROR_ENCRYPT_ARGUMENT_OUT_OF_BOUNDS  9014
#define AR_ERROR_ENCRYPT_NULL_INPUT_ARGUMENT     9015
#define AR_ERROR_DECRYPT_FUNC_INVALID_CRC        9016
#define AR_ERROR_ENCRYPT_FIPS_FAILURE            9017
#define AR_ERROR_ENCRYPT_FIPS_DUAL_MODE_FAIL     9018
#define AR_ERROR_ENCRYPT_FIPS_STRICT_MODE_FAIL   9019
#define AR_ERROR_FIPS_INVALID_SECURITY_POLICY    9020



/* messages for localization */
#define AR_ERROR_NO_MESSAGE_CAT_SCHEMA           9050
#define AR_ERROR_2_MESSAGE_CAT_SCHEMA            9051
#define AR_ERROR_VUI_NOT_UNIQUE                  9052
#define AR_WARN_DEFAULT_VUI_REDEFINED            9053
#define AR_WARN_NO_SUCH_FIELD                    9054
#define AR_ERROR_BAD_VUI_IMPORT_FORMAT           9055
#define AR_ERROR_SERVER_NOT_LOCALIZED            9056
#define AR_ERROR_LOCAL_TXT_RECURSION_NOT_ALLOWED 9057
#define AR_ERROR_UPDATE_LOC_AL_MENU_FAILED       9058
#define AR_ERROR_JOIN_FORM_CIRCULAR              9059

/* messages for Unicode */
#define AR_ERROR_CREATE_UNICODE_CONVERTER        9060
#define AR_ERROR_CONVERT_TO_UNICODE              9061
#define AR_ERROR_CONVERT_FROM_UNICODE            9062
#define AR_ERROR_UNICODE_CLIENTS_ONLY            9063

#define AR_ERROR_USER_FORM_CREATE_DUP            9070
#define AR_ERROR_GROUP_FORM_CREATE_DUP           9071
#define AR_ERROR_ROLE_FORM_CREATE_DUP            9072
/* messages for server schemas */
#define AR_ERROR_IMPORT_SVR_SCHEMA               9075
#define AR_ERROR_NO_SVR_EVENT_SCHEMA             9076
#define AR_ERROR_SVR_EVENT_CREATE_DUP            9077
#define AR_ERROR_NO_SVR_STATS_SCHEMA             9078
#define AR_ERROR_SVR_STATS_CREATE_DUP            9079
#define AR_ERROR_APP_STATS_CREATE_DUP            9080
#define AR_ERROR_NO_APP_STATS_SCHEMA             9081
#define AR_ERROR_APP_STATS_CONFIG_CREATE_DUP     9082
#define AR_ERROR_NO_APP_STATS_CONFIG_SCHEMA      9083
#define AR_ERROR_USER_HOST_IP_DIFFERENT          9084
#define AR_ERROR_USER_HOST_IP_NOT_FOUND          9085
#define AR_ERROR_APP_STATS_NOT_IN_MAP            9086
#define AR_ERROR_FORM_STATS_NOT_IN_MAP           9087
#define AR_ERROR_NOT_APP_DEFN                    9088
#define AR_ERROR_USER_DATA_CORRUPT               9089
#define AR_ERROR_MAX_FIXED_LIC_ASSIGN_EXCEEDED   9090
#define AR_ERROR_USER_DATA_CORRUPT_LIC_DELETED   9091
#define AR_ERROR_PENDING_FILE_CORRUPT            9092
#define AR_ERROR_USER_HOST_IP_OVERRIDE_OPTION    9093
#define AR_WARN_SUBADMIN_GROUP_PERMS_REMOVED     9094
#define AR_WARN_SUBADMIN_ROLE_PERMS_REMOVED      9095
#define AR_ERROR_SET_AUTH_CHAINING_MODE_BAD      9096
#define AR_ERROR_NO_LICENSE_SCHEMA               9097
#define AR_ERROR_SVR_LICENSE_CREATE_DUP          9098

/* execute */
#define AR_ERROR_NON_LOCAL_SERVER_EXECUTION      9100
#define AR_ERROR_NOT_SERVER_SIDE_PROCESS         9101
#define AR_ERROR_PROCESS_COMMAND_ERROR           9102

#define AR_ERROR_INVALID_HOST_ID                 9110

#define AR_ERROR_WEB_SERVICE_EXECUTION_ERROR     9130
#define AR_ERROR_XML_OUTPUT_MAPPING_NULL         9131
#define AR_ERROR_EXPECTED_XML_DEFAULT_MAPPING    9132
#define AR_ERROR_REGISTRY_LOCATION_NULL          9133
#define AR_ERROR_REGISTRY_PLUGIN_ERROR           9134
#define AR_ERROR_REGISTRY_INVALID_URL            9135
#define AR_ERROR_REGISTRY_BAD_SERVICE_KEY        9136
#define AR_WARN_REGISTRY_EP_NOT_IN_CACHE         9137

#define AR_ERROR_NO_SUCH_COLUMN                  9140
#define AR_ERROR_COULD_NOT_CONVERT_DATETIME      9141
#define AR_ERROR_COULD_NOT_CONVERT_TIMEOFDAY_STRING     9142
#define AR_ERROR_COULD_NOT_CONVERT_DATETIME_STRING      9143

#define AR_ERROR_SYSTEM_FORM_NOT_REQUIRED_VER    9144
#define AR_ERROR_SYSTEM_FORM_DEF_MISSING_FIELD   9145

/* armonitor errors */
#define ARMONITOR_ERROR_LOCK_FILE_OPEN           9150

/* Range 9200 - 9699 reserved for mid tier */

/* messages for currency ratio */
#define AR_ERROR_IMPORT_CURRENCY                 9701

/* messages for bulk entry operations */
#define AR_ERROR_BULK_ENTRY_TXN_IN_PROGRESS      9710
#define AR_ERROR_BULK_ENTRY_NO_TXN_IN_PROGRESS   9711
#define AR_ERROR_BULK_ENTRY_BAD_ACTION           9712
#define AR_ERROR_BULK_ENTRY_CALL_FAILED          9713

/* mergeEntry Error */
#define AR_ERROR_MERGE_ENTRY_MULTI_MATCH_ERROR   9719

/* messages for object relationships */
#define AR_ERROR_OBJECT_REL_UPDATES_NOT_ALLOWED  9720
#define AR_NOTE_OBJECT_REL_GENERATION_SKIPPED    9721
#define AR_NOTE_OBJECT_REL_CLEANUP_SKIPPED       9722

/* messages for metadata views */
#define AR_ERROR_METADATA_UPDATES_NOT_ALLOWED    9730

/* messages for full text form scan */
#define AR_ERROR_INVALID_FT_SCAN_INFO            9735

/* messages for server statistics longest operations */
#define AR_ERROR_LONGEST_OP_MODS_NOT_ALLOWED     9740

/* messages for api extention sharedlibs */
#define AR_ERROR_SHAREDLIB_LOAD                  9750
#define AR_ERROR_INVALID_SHAREDLIB_NAME          9751
#define AR_ERROR_NO_SHAREDLIB_IDENTIFY           9752
#define AR_ERROR_INVALID_SHAREDLIB               9753
#define AR_ERROR_SHAREDLIB_NORPCNUM              9754
#define AR_ERROR_SHAREDLIB_INIT                  9755
#define AR_ERROR_UNSUPPORTED_ARIAPI_VERSION      9756
#define AR_ERROR_CALL_FROM_FILTERPROCESSING      9757
#define AR_ERROR_CALL_NOT_FROM_FILTERPROCESSING  9758
#define AR_ERROR_ARIWF_NO_FILTER_CONTEXT         9759
#define AR_ERROR_ARIWF_CALL_FROM_IMPROPER_PHASE  9760
#define AR_ERROR_ARIWF_UNKNOWN_CALL              9761

/* messages for roles */
#define AR_ERROR_ROLE_MAP_NO_SUCH_APP            9780
#define AR_ERROR_ROLE_MAP_NO_SUCH_ROLE           9781
#define AR_ERROR_INCORRECT_ROLE_FORMAT           9782

/* messages for email */
#define AR_ERROR_IMPORT_EMAIL_SCHEMA             9800
#define AR_ERROR_NO_EMAIL_SCHEMA                 9801
#define AR_ERROR_EMAIL_ATTACHMENT_MAPPING_BAD    9802
#define AR_ERROR_EMAIL_NO_SUCH_MAILBOX           9803
#define AR_ERROR_EMAIL_REQUIRED_FORM_MISSING     9804

/* messages for license audit 9820 - 9849*/
#define AR_ERROR_OPENING_LICENCE_REPORT_FILE     9820
#define AR_ERROR_READING_LICENCE_REPORT_FILE     9821
#define AR_ERROR_WRITING_LICENCE_REPORT_FILE     9822
#define AR_ERROR_CORRUPT_LICENCE_REPORT_FILE     9823
#define AR_ERROR_LICENCE_REPORT_MUTEX_ERROR      9824

/* messages for application license */
#define AR_ERROR_NO_APPLICATION_WRITE_LICENSE    9850
#define AR_ERROR_NO_APPLICATION_FIXED_LICENSES   9851
#define AR_WARN_EXCEED_MAXIMUM_FIXED_LICENSES    9852
#define AR_NOTE_APP_FIXED_LICENSE_RETURNED       9853
#define AR_NOTE_APP_FIXED_LICENSE_GRANTED        9854
#define AR_NOTE_UPGRADE_TO_APPLICATION_FLOATING  9855
#define AR_ERROR_NO_SUCH_APP_USER_LICENSE        9856
#define AR_ERROR_ALREADY_LICENSABLE              9857 /*8983*/
#define AR_ERROR_APPLICATION_NOT_LICENSED        9858 /*8984*/
#define AR_ERROR_APP_LIC_MISMATCH                9859 /*8985*/
#define AR_ERROR_APPLICATION_LICENSE_FORMAT_BAD  9860 /*8987*/
#define AR_ERROR_MISSING_APP_LICENSE_INFO        9861 /*8988*/
#define AR_WARN_NO_FREE_APP_FLOATING             9862 /*8989*/
#define AR_WARN_SETTING_LIC_PROP_DISALLOWED      9863 /*8990*/
#define AR_ERROR_CANNOT_LICENSE                  9864 /*8991*/

/* messages for the workflow debugger  */
#define AR_ERROR_ESCL_NOT_DISABLED               9870
#define AR_ERROR_TERMINATED_BY_DEBUGGER          9871
#define AR_ERROR_WFD_BAD_FIELDVALUE_LIST         9872
#define AR_WARN_WFD_COMMAND_INVALID_NOW          9873
#define AR_WARN_WFD_NO_SUCH_BREAKPOINT           9874

/* messages for external logging */
#define AR_NOTE_EXTERNAL_LOGGING                 9900
#define AR_ERROR_EXTERNAL_LOGGING_FAILED         9901
#define AR_ERROR_EXTERNAL_LOGGING_NOT_HANDLED    9902

/* general error messages */
#define AR_ERROR_INTERNAL_API_CALL_FAILED        9905
#define AR_ERROR_RESULT_MEM_ALLOC_TOO_LARGE      9906
#define AR_ERROR_ILLEGAL_CMD_LINE_PARAM          9907
#define AR_ERROR_ILLEGAL_PLACEHOLDER_OPERATION   9908

#define AR_WARN_TOO_MANY_CACHES                  9910
#define AR_ERROR_TOO_MANY_CACHES                 9911

#define AR_ERROR_FIELD_COUNT_MISMATCH            9912
#define AR_ERROR_VUI_COUNT_MISMATCH              9913

/* lock block import export messages */
#define AR_ERROR_LOCK_BLOCK_IMPORT_NOT_SUPPORTED 9920;
#define AR_ERROR_LOCK_BLOCK_EXPORT_NOT_SUPPORTED 9921;

/* messages for audit */
#define AR_ERROR_AUDIT_NOT_ALLOWED               9922
#define AR_ERROR_CANNOT_CREATE_JOIN_SHADOW_FORM  9923
#define AR_ERROR_ONE_FIELD_PER_LOGKEY            9924
#define AR_ERROR_INCORRECT_NUM_SPECIAL_FIELDS    9925
#define AR_ERROR_SHADOW_FORM_IN_USE              9926
#define AR_ERROR_INCORRECT_NUM_DATA_FIELDS       9927
#define AR_ERROR_DATATYPE_MISMATCH               9928
#define AR_ERROR_SOURCE_FIELD_NOT_PRESENT        9929
#define AR_WARN_SHADOW_FORM_NOT_IMPORTED         9930
#define AR_ERROR_EXTERNAL_REF_NOT_ALLOWED        9931
#define AR_WARN_SHADOW_FORM_NOT_FOUND            9932
#define AR_ERROR_AUDIT_DISABLE_NOT_ALLOWED       9933
#define AR_ERROR_AUDIT_ENABLE_NOT_ALLOWED        9934
#define AR_ERROR_RESERVED_FOR_AUDIT              9935

#define AR_ERROR_TIMEOUT_FOR_PLUGIN_CALL         9940

/* messages for recurrence times */
#define AR_ERROR_RECURRENCE_BAD_INPUT            9950
#define AR_ERROR_RECURRENCE_BAD_DATE             9951
#define AR_ERROR_RECURRENCE_INVALID_TYPE         9952
#define AR_ERROR_RECURRENCE_INVALID_MOY          9953
#define AR_ERROR_RECURRENCE_INVALID_WOM          9954
#define AR_ERROR_RECURRENCE_INVALID_DOM          9955
#define AR_ERROR_RECURRENCE_BAD_HOURSOFDAY       9956
#define AR_ERROR_RECURRENCE_BAD_DAYSOFWEEK       9957
#define AR_ERROR_RECURRENCE_DATE_OUTOFRANGE      9958
#define AR_WARN_RECURRENCE_DATE_OF_MONTH_INVALID 9959
#define AR_ERROR_RECURRENCE_NO_DATES             9960
#define AR_ERROR_RECURRENCE_NONE_FOUND           9961


#define AR_ERROR_SHARE_APP_CONFIG_REG_CREATE_DUP      9970

/* messages for Log Schemas */
#define AR_ERROR_NO_LOG_SCHEMA                   9971
#define AR_ERROR_LOG_SCHEMA_CREATE_DUP           9972

/* Message for SHARE:Application_Properties and SHARE:Application_Interface */
#define AR_ERROR_SHARE_APP_PROPS_CREATE_DUP      9973
#define AR_ERROR_SHARE_APP_INTERFACE_CREATE_DUP  9974

/* Range 9975 - 9999 reserved for Dynamic Join/Recursive Query messages */
#define AR_ERROR_REC_QUERY_NO_RECURSE_QUAL       9975
#define AR_ERROR_REC_QUERY_WRONG_TYPE            9976
#define AR_ERROR_MORE_THAN_ONE_REC_QUERY         9977
#define AR_ERROR_REC_QUERY_ONLY_ONE_SCHEMA_FIELDS 9979
#define AR_ERROR_REC_QUERY_WRONG_REC_SCHEMA      9980
#define AR_ERROR_BAD_JOIN_TYPE                   9981
#define AR_ERROR_BAD_QUERY_FROM_TYPE             9982
#define AR_ERROR_BAD_QUERY_FROM_ALIAS            9983
#define AR_ERROR_REG_QUERY_EMPTY                 9984
#define AR_ERROR_FROM_LIST_EMPTY                 9985
#define AR_ERROR_MISSING_JOIN_SOURCE             9986
#define AR_ERROR_BAD_FIELD_INFO                  9987
#define AR_ERROR_REC_QUERY_NULL                  9988
#define AR_ERROR_BAD_GET_LIST                    9989
#define AR_ERROR_VALUE_SET_BAD_FROM_LIST         9990
#define AR_ERROR_BAD_JOIN_QUALIFIER              9991
#define AR_ERROR_DIALOG_IN_QUERY                 9992
#define AR_ERROR_JOIN_IN_FIRST_SOURCE            9993
#define AR_ERROR_DIARY_IN_JOIN                   9994
#define AR_ERROR_RPC_INVALID_SQL                 9995
#define AR_ERROR_BAD_FIELD_FUNC                  9996
#define AR_ERROR_ONE_JOIN_ONLY                   9997
#define AR_ERROR_FUNCTION_IN_GROUP_BY            9998
#define AR_ERROR_NOT_FUNCTION_FIELD              9999

/* default messages when we cannot get text from the catalog */
#define AR_ERROR_DEF_OPEN_CATALOG    "Cannot open catalog; Message number = "
#define AR_ERROR_DEF_NO_MESSAGE      "Message not in catalog; Message number = "

#endif   /* AR_ERRORNO_H */
