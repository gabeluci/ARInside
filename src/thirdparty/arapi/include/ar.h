/*  File: ar.h  */

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef AR_SYSTEM_DEFINED
#define AR_SYSTEM_DEFINED

#include "artypes.h"

#define AR_SYSTEM_NAME           "Action Request System"

                                 /* directory containing config files */
#define AR_HOME_CONFIGDIR        "conf"

#ifdef _WIN32
                                 /* system server configuration filename */
#define AR_HOME_CONFIGFILE       "ar.cfg"
                                 /* database configuration filename */
#define AR_HOME_DB_CONFIGFILE    "ardb.cfg"
                                 /* audit configuration filename */
#define AR_HOME_AUDIT_CONFIGFILE "araudit.cfg"
                                 /* default home directory */
#define AR_HOME_DEFAULT          "c:\\arservdb"
                                 /* default ar monitor configuration filename */
#define AR_MONITOR_CONFIGFILE    "c:\\armonitor.cfg"

#else /* _WIN32 */
                                 /* system server configuration filename */
#define AR_HOME_CONFIGFILE       "ar.conf"
                                 /* database configuration filename */
#define AR_HOME_DB_CONFIGFILE    "ardb.conf"
                                 /* default home directory */
#define AR_HOME_DEFAULT          "/usr/ar"
                                 /* audit configuration filename */
#define AR_HOME_AUDIT_CONFIGFILE "araudit.conf"
                                 /* default ar monitor configuration filename */
#define AR_MONITOR_CONFIGFILE    "armonitor.conf"

#endif /* _WIN32 */
                                 /* environment variable for alt config dir */
#define AR_ENV_CONFIGDIR         "ARCONFIGDIR"
                                 /* environment variable for alt install dir */
#define AR_ENV_INSTALLDIR        "ARINSTALLDIR"
                                 /* environment variable for alt monitor */
                                 /*  config filename                     */
#define AR_ENV_MONITOR_CONFIG    "ARMCONFIGFILE"
                                 /* default server stop file */
#define AR_MONITOR_PID           "armonitor.pid"
                                 /* default filter log file */
#define AR_LOG_FILE              "ar.log"
                                 /* default server directory file */
#define AR_DIRECTORY_FILE        "ar"
                                 /* application audit file */
#define AR_APPL_AUDIT_FILE       "appl.aud"
                                 /* application audit violation file */
#define AR_APPL_VIOLATION_FILE   "appl.vio"
                                 /* tag for AR server */
#define AR_DIRECTORY_AR_TAG      "AR"

#define AR_MAX_ACTIONS            25/* max actions for 1 filter/active link */
#define AR_MAX_AL_MESSAGE_SIZE  4095/* max size of an active link message */
#define AR_MAX_AUTH_SIZE        2047/* max size of auth string */
#define AR_MAX_AUTOMATION_SIZE  2000/* max size of an auto item string */
#define AR_MAX_BUFFER_SIZE       352/* max size of a temporary buffer */
#define AR_MAX_CMENU_SIZE        255/* max size of a character menu value */
#define AR_MAX_COMMAND_SIZE      255/* max size of a user command string */
#define AR_MAX_COMMAND_SIZE_LONG 4096/* max size of a user commandLong string */
#define AR_MAX_FORMAT_SIZE        32/* max size of a custom date time format */
#define AR_MAX_DDE_ITEM        32767/* max size of a dde item string */
#define AR_MAX_DDE_NAME           64/* max size of a dde service/topic name */
#define AR_MAX_COM_NAME         1024/* max size of a COM name */
#define AR_MAX_COM_METHOD_NAME   128/* max size of a method string */
#define AR_MAX_COM_ID_SIZE       128/* max size of a COM clsId/methodIId */
#define AR_MAX_DEFAULT_SIZE      255/* max size of a character type default */
#define AR_MAX_EMAIL_ADDR        255/* max size of a notify email address */
#define AR_MAX_ENTRYID_SIZE       15/* max size of an entry id in the system */
#define AR_MAX_GOTOGUIDE_LABEL_SIZE  128/* max size of goto label string */
#define AR_MAX_GROUPLIST_SIZE    255/* max size of the group list field */
#define AR_MAX_GUID_SIZE          30/* max size for a GUID string */
#define AR_MAX_GUID_PREFIX_SIZE   2 /* max size for a GUID prefix */
#define AR_MAX_INDEX_BYTES       255/* max bytes in ALL columns in an index */
#define AR_MAX_INDEX_FIELDS       16/* max fields in an index */
#define AR_MAX_LANG_SIZE          15/* max size of a language name */
#define AR_MAX_LICENSE_NAME_SIZE  50/* max size of a license name */
#define AR_MAX_LICENSE_KEY_SIZE   30/* max size of a license key */
#define AR_MAX_LOCALE_SIZE        64/* max size of a locale */
#define AR_MAX_MACRO_VALUE       255/* max size of a macro value */
#define AR_MAX_MENU_ITEMS        199/* max menu items in any single menu for */
                                    /*   char field default sets             */
#define AR_MAX_MENU_LEVELS        15/* max menu levels for char field default */
                                    /*   sets                                 */
#define AR_MAX_LEVELS_DYNAMIC_MENU 5/* max levels for Dynamic Query and SQL menu */
#define AR_MAX_MESSAGE_SIZE      255/* max size of a status message */
#define AR_MAX_MULT_ENTRIES      100/* max entries that can be handled by a */
                                    /*   multiple entries call              */
#define AR_MAX_NAME_SIZE         254/* max size of a name in the system */
#define AR_MAX_ACCESS_NAME_SIZE  254/* max size of an user name type */
                                    /*   (user,group)        */
#define AR_MAX_ACCESS_NAME_SIZE_63 30/* max size of an access name type */
#define AR_MAX_PASSWORD_SIZE      30/* max size of a password type */
#define AR_MAX_HASH_SIZE          28 /* max size of hashed string */
#define AR_MAX_ENCRYPTED_PASSWORD_SIZE 120 /* max size of an encrypted password type */
#define AR_MAX_NAME_CHARACTERS    80/* max number of chars in an object name */
#define AR_MAX_NOTIFY_USER       255/* max size of a notify user line */
#define AR_MAX_PATTERN_SIZE      255/* max size of a character limit pattern */
#define AR_MAX_RELATED_SIZE      128/* max size of related to field */
#define AR_MAX_SCHEMAID_SIZE       5/* max size schemaid in flat file schema */
                                    /*   cache                               */
#define AR_MAX_SERVER_SIZE        64/* max size of a server name */
#define AR_MAX_LINE_LENGTH     2048/* max size of a server name */
#define AR_MAX_SDESC_SIZE        254/* max size of a short description */
#define AR_MAX_SUBJECT_SIZE      255/* max size of a notify subject line */
#define AR_MAX_HOSTID_SIZE       100/* max size of a host id */
#define AR_MAX_TARGET_STRING_SIZE 255/* max size of targetLocation string in */
                                     /* activeLink OpenDlg struct            */
#define AR_MAX_USER_GUID_SIZE    128 /* max size of user identifier */
#define AR_MAX_WAIT_CONT_TITLE_SIZE  64 /* max size of wait continue label */

                                /* filename limits; are restrictive so the */
#define AR_MAX_FILENAME_SIZE  12/*   names will be legal on any target     */
#define AR_MAX_FILENAME_BASE   8/*   system and these limits are smallest  */
#define AR_MAX_FULL_FILENAME 255

/* reserved overlay string for AR server */
#define AR_RESERV_OVERLAY_STRING          "__o"
#define AR_RESERV_OVERLAY_CUSTOM_STRING   "__c"

/* bitmask variables for generating the overlay property of objects */
#define AR_ORIGINAL_OBJECT      0    /* un-touched or out of the box object */
#define AR_OVERLAID_OBJECT      1    /* base object which is overlaid       */
#define AR_OVERLAY_OBJECT       2    /* overlay object                      */   
#define AR_CUSTOM_OBJECT        4    /* object created through cusomt mode client */
                                 /* max number of chars allowed in overlaid objects */
#define AR_MAX_CHAR_OVERLAID_OBJ_NAME  244

/* Constants for relation overlay group in Object Relationship table */
#define AR_OBJ_REL_OVERLAY_GROUP_BASE  "-1"
#define AR_OBJ_REL_OVERLAY_GROUP_OVERLAID  "0"

/*
 * Predefined values for the groupOverlay column in Group form and
 * group_cache table, and for the corresponding in-memory structures.
 * ~_TAG_BASE identifies the special overlay group 0 (a member of this
 * group can only modify and create base-mode objects).
 * ~_TAG_NULL represents the NULL db value in memory.
 * ~_TAG_INVALID warns the client that the server couldn't provide the
 * info accurately.
 */
#define AR_OVERLAY_GROUP_TAG_NULL ((unsigned int) -2)
#define AR_OVERLAY_GROUP_TAG_INVALID ((unsigned int) -1)
#define AR_OVERLAY_GROUP_TAG_BASE 0U
#define AR_OVERLAY_GROUP_TAG_OVERLAY 1U

/* Following three set of flags are reserved for the future for the client managed */
/* Transaction API */

/* new flags for the user for the client transaction */
#define AR_COMMIT_CLIENT_TRANSACTION 1
#define AR_ROLLBACK_CLIENT_TRANSACTION 2

/*max limit for the client transaction, time out is in seconds */
#define MAX_CLIENT_MANAGED_TRANSACTIONS_TIMEOUT       600  /* 10 minutes */
#define DEFAULT_CLIENT_MANAGED_TRANSACTIONS_TIMEOUT   60  /* 1 minute */

/* default number of concurrent client managed transactions */
#define MAX_CONCURRENT_CLIENT_MANAGED_TRANSACTIONS            100 /* max concurrent transactions */
#define DEFAULT_NUM_CONCURRENT_CLIENT_MANAGED_TRANSACTIONS    10  /* default transactions */


                                    /* table and column field size limits */
#define AR_MAX_COLFLD_COLLENGTH  255/* max data size displayed in a column */
#define AR_MAX_SVR_EVENT_DETAILS 255/* max len of details in svr event form */
#define AR_MAX_SVR_EVENT_LIST    255/* max len of a server event list string */
#define AR_MAX_TABLENAME_SIZE    2047/* maximum external table name size */
#define AR_MAX_TBLFLD_NUMCOLS    255/* max columns in a table field */
#define AR_MAX_TBLFLD_RETROWS   9999/* max rows returned in a refresh */

#if defined(_WIN32) || defined(LINUX) || defined(__APPLE__)
#define MAXHOSTNAMELEN           255/* maximum size of a server name -- same */
                                    /*  as MAXHOSTNAMELEN from <sys/param.h> */
#endif
                               /* maximum if using flatfile server */
#define AR_MAX_FLATFILE_LIMIT  10000000
#define AR_WARN_FLATFILE_LIMIT  9000000

                               /* maximum size of attachment BLOB */
#define AR_MAX_BLOB_SIZE       ARLONG32_MAX

                               /* maximum field ID */
#define AR_MAX_FIELD_ID        ARLONG32_MAX

                               /* maximum if the server doesn't have license */
#define AR_NO_LICENSE_DB_LIMIT 2000000 /* max bytes for flat file solution */
#define AR_NO_LICENSE_DB_COUNT  2000   /* max entries for SQL solution */

#define AR_LICENSE_TYPE_NONE                0   /* types of user licenses supported by */
#define AR_LICENSE_TYPE_FIXED               1   /*  the AR System                      */
#define AR_LICENSE_TYPE_FLOATING            2
#define AR_LICENSE_TYPE_RESTRICTED_READ     3   /*  Restricted Read License */

#define AR_LICENSE_POOL_NON_RESERVED_POOL   (ARInternalId) ((int) -1) /* -1 means non-reserved pool */

#define AR_LICENSE_IMPORT_APPEND      0   /* append the new licenses to the license file */
#define AR_LICENSE_IMPORT_OVERWRITE   1   /* overwrite the license file with the new licenses */

#define AR_DEFAULT_INTERVAL   300  /* default time interval for escalation */


#define AR_CURRENT_API_VERSION       20  /* current api version */
#define AR_MINIMUM_CMDB_API_VERSION   3  /* minimum cmdb api version supported by */
                                         /* current shared library implementation */
#define AR_CURRENT_CMDB_API_VERSION   4  /* current cmdb api version */

#define AR_NATIVE_ENCRYPTION        '0'
#define AR_UNICODE_ENCRYPTION       '1'

#define AR_ENCRYPTION_VERSION_1     '0'
#define AR_ENCRYPTION_VERSION_2     '1'
#define AR_ENCRYPTION_VERSION_3     '2'

#define AR_SERVER_MIN_AUDIT_LOG_FILE_SIZE 100000 /* Set minimum audit file */
                                                 /* size to 100 KB         */

#define AR_MAX_DECIMAL_SIZE               64
#define AR_MAX_DECIMAL_FIELD_VALUE_LIMIT  "99999999999999999999999999.99"
#define AR_MIN_DECIMAL_FIELD_VALUE_LIMIT  "-99999999999999999999999999.99"
#define AR_MAX_CURRENCY_FIELD_VALUE_LIMIT  "99999999999999999999999999.99"
#define AR_MIN_CURRENCY_FIELD_VALUE_LIMIT  "-99999999999999999999999999.99"
#define AR_MAX_CURRENCY_CODE_SIZE         3
#define AR_MAX_CURRENCY_RATIO_SIZE        64
#define AR_CURRENT_CURRENCY_RATIOS        0

#define AR_AUTH_CHAINING_MODE_DEFAULT       0 /* default and minimum value */
#define AR_AUTH_CHAINING_MODE_ARS_THEN_AREA 1 /* auth in ARS first, then AREA */
#define AR_AUTH_CHAINING_MODE_AREA_THEN_ARS 2 /* auth in AREA first, then ARS */
#define AR_AUTH_CHAINING_MODE_ARS_OS_AREA   3 /* auth in ARS first, then OS, then AREA */
#define AR_AUTH_CHAINING_MODE_ARS_AREA_OS   4 /* auth in ARS first, then AREA, then OS */
#define AR_AUTH_CHAINING_MODE_MAX           4 /* maximum value */
#ifdef __cplusplus
/* This is needed so C++ applications don't compile these structures as C++. */
extern "C" {
#endif
                               /* Name for the system constants for support */
                               /*   of ARBoolean type                       */
#ifndef FALSE
#define FALSE                0
#endif
#ifndef False
#define False                0
#endif
#ifndef TRUE
#define TRUE                 1
#endif
#ifndef True
#define True                 1
#endif

                               /* codes for return values from API routines */
#define AR_RETURN_OK         0 /*   successful; status may contain notes */
#define AR_RETURN_WARNING    1 /*   successful?; status contains details */
#define AR_RETURN_ERROR      2 /*   failure; status contains details */
#define AR_RETURN_FATAL      3 /*   failure; status may or may not contain */
                               /*            any details                   */
#define AR_RETURN_BAD_STATUS 4 /*   status structure is invalid */
#define AR_RETURN_PROMPT     5 /*   status for the active link action */
#define AR_RETURN_ACCESSIBLE 6 /*   status message for client accessibility */
#define AR_RETURN_TOOLTIP    7 /*   message type for ToolTips message action */

typedef unsigned char ARBoolean;   /* boolean flag set to TRUE or FALSE */

                                   /* structure to hold an entry id value */
typedef char          AREntryIdType[AR_MAX_ENTRYID_SIZE + 1];

typedef ARULong32     ARInternalId;/* structure to hold an internal id */
                                   /* structure to hold an object name */
typedef char          ARNameType[AR_MAX_NAME_SIZE + 1];
                                   /* structure to hold password */
typedef char          ARPasswordType[AR_MAX_PASSWORD_SIZE + 1];
                                  /* structure to hold an auth string */
typedef char          ARAuthType[AR_MAX_AUTH_SIZE + 1];
                                   /* structure to hold a file name */
typedef char          ARFileNameType[AR_MAX_FULL_FILENAME + 1];
                                   /* structure to hold an access name */
typedef char          ARAccessNameType[AR_MAX_ACCESS_NAME_SIZE + 1];
                                   /* structure to hold an encrypted password */
typedef char          AREncryptedPasswordType[AR_MAX_ENCRYPTED_PASSWORD_SIZE + 1];
                                   /* structure to hold a server name */
typedef char          ARServerNameType[AR_MAX_SERVER_SIZE + 1];
                                   /* timestamp; Unix style timestamp */
typedef ARLong32      ARTimestamp; /*  (seconds since Jan. 1, 1970)   */
#define ARTIMESTAMP_MAX ARLONG32_MAX
                                   /* structure to hold a license name */
typedef char          ARLicenseNameType[AR_MAX_LICENSE_NAME_SIZE + 1];
                                   /* structure to hold a license key */
typedef char          ARLicenseKeyType[AR_MAX_LICENSE_KEY_SIZE + 1];
                                   /* used to hold host id string */
typedef char          ARHostIDType[AR_MAX_HOSTID_SIZE + 1];
                                   /* structure to hold a locale string */
typedef char          ARLocaleType[AR_MAX_LOCALE_SIZE + 1];
                                   /* structure to hold a menu entry */
typedef char          ARCMenuType[AR_MAX_CMENU_SIZE + 1];
                                   /* structure to hold a table name */
typedef char          ARTableNameType[AR_MAX_TABLENAME_SIZE + 1];
typedef ARLong32      ARTime;      /*  (seconds since midnight 00.00.00)   */
typedef char          ARCurrencyCodeType[AR_MAX_CURRENCY_CODE_SIZE + 1];


typedef struct ARTextString
{
   unsigned int   length;
   char          *string;

}  ARTextString;              /* character string */


typedef struct AREntryIdList
{
   unsigned int    numItems;
   AREntryIdType  *entryIdList;

}  AREntryIdList;             /* list of 0 or more entry ids */


typedef struct ARInternalIdList
{
   unsigned int   numItems;
   ARInternalId  *internalIdList;

}  ARInternalIdList;          /* list of 0 or more internal ids */


typedef struct ARInternalIdListList
{
   unsigned int       numItems;
   ARInternalIdList  *internalIdListList;

}  ARInternalIdListList;      /* list of 0 or more internal id list */


typedef struct ARLocaleList
{
   unsigned int   numItems;
   ARLocaleType  *localeList;

}  ARLocaleList;              /* list of 0 or more entry ids */


typedef struct ARNameList
{
   unsigned int   numItems;
   ARNameType    *nameList;

}  ARNameList;                /* list of 0 or more object names */


typedef struct ARNamePtrList
{
   unsigned int   numItems;
   char         **namePtrList;

}  ARNamePtrList;             /* list of 0 or more object name pointers */

typedef struct ARFileNameList {
   unsigned int        numItems;
   ARFileNameType     *fileNameList;
} ARFileNameList;            /* list of 0 or more file names */

typedef struct ARAccessNameList
{
   unsigned int       numItems;
   ARAccessNameType  *nameList;

}  ARAccessNameList;          /* list of 0 or more access names */


typedef struct ARAccessNamePtrList
{
   unsigned int   numItems;
   char         **namePtrList;

}  ARAccessNamePtrList;       /* list of 0 or more access name pointers */

typedef struct ARPasswordList
{
   unsigned int     numItems;
   ARPasswordType  *nameList;
}  ARPasswordList;          /* list of 0 or more passwords or keys */

typedef struct ARServerNameList
{
   unsigned int       numItems;
   ARServerNameType  *nameList;

}  ARServerNameList;          /* list of 0 or more server names */


typedef struct ARTextStringList
{
   unsigned int   numItems;
   char         **stringList;

}  ARTextStringList;          /* list of 0 or more character strings */


typedef struct ARTimestampList
{
   unsigned int   numItems;
   ARTimestamp   *timestampList;

}  ARTimestampList;           /* list of 0 or more timestamps */


typedef struct ARUnsignedIntList
{
   unsigned int   numItems;
   unsigned int  *intList;

}  ARUnsignedIntList;         /* list of 0 or more unsigned integers */


typedef struct ARUnsignedIntPtrList
{
   unsigned int   numItems;
   unsigned int **intPtrList;

}  ARUnsignedIntPtrList;         /* list of 0 or more unsigned integer pointers */

#define AR_BYTE_LIST_SELF_DEFINED   0 /* byte list is self typed via the  */
                                      /*  first bytes; i.e. "GIF" at head */
#define AR_BYTE_LIST_WIN30_BITMAP   1 /* Windows 3.0 bitmap format */
#define AR_BYTE_LIST_JPEG           2
#define AR_BYTE_LIST_TIFF           3
#define AR_BYTE_LIST_TARGA          4
#define AR_BYTE_LIST_PCX            5
#define AR_BYTE_LIST_LOCALIZED_FILE 6
#define AR_BYTE_LIST_AUTH_STRING    7 /* Windows domain name / auth str */
#define AR_BYTE_LIST_FUNC_PTR       8 /* Byte list with a function ptr in it */
#define AR_BYTE_LIST_GIF            9 /* Image type GIF */
#define AR_BYTE_LIST_PNG           10 /* Image Type PNG */

typedef struct ARByteList
{
   ARULong32       type;      /* type of list */
   AR_XDR_STRUCT_PAD32(noval_)
   unsigned int    numItems;  /* length of bytes */
   unsigned char  *bytes;     /* not NULL terminated */

}  ARByteList;                /* byte stream */

typedef struct ARLocalizationInfo
{
   char locale[AR_MAX_LOCALE_SIZE + 1];
   char charSet[AR_MAX_LANG_SIZE + 1];
   char timeZone[AR_MAX_LOCALE_SIZE + 1];
   char customDateFormat[AR_MAX_FORMAT_SIZE + 1];
   char customTimeFormat[AR_MAX_FORMAT_SIZE + 1];
   char separators[AR_MAX_LANG_SIZE + 1];

}  ARLocalizationInfo ;

/* Control record containing information about the user and the environment.  */
/* An instance of this structure will be the first parameter of all the calls */
/* supported by the AR system.                                                */
/*  NOTE that server is listed last in the structure below as it is not passed*/
/*     in the RPC call.  It is not needed on the server (who already knows    */
/*     who he is).  By placing it last, there can still be a "clean" mapping  */
/*     of the first part of the record with the RPC structure.                */

typedef struct ARControlStruct
{                     /* id assigned and used by the system */
                      /*  for efficient cache access        */
   ARLong32           cacheId;
                      /* time at which the operation was    */
                      /* performed                          */
   ARTimestamp        operationTime;
                      /* username and password for access   */
                      /* control                            */
   ARAccessNameType   user;
   ARPasswordType     password;
                      /* locale information                 */
   ARLocalizationInfo localeInfo;
                      /* API session identifier             */
   ARUIntPtr          sessionId;
                      /* Windows domain                     */
   ARAuthType         authString;
                      /* server to access                   */
   char               server[AR_MAX_SERVER_SIZE + 1];

} ARControlStruct;


typedef struct ARStatusStruct
{
   unsigned int   messageType;
   ARLong32       messageNum;
   char          *messageText;
   char          *appendedText;

}  ARStatusStruct;            /* type of error (see return values) */


typedef struct ARStatusList
{
   unsigned int     numItems;
   ARStatusStruct  *statusList;

} ARStatusList;               /* list of 0 or more status messages */


typedef struct ARStatusListList
{
   unsigned int     numItems;
   ARStatusList    *statusListList;

} ARStatusListList;           /* list of 0 or more status lists */


typedef struct ARMessageStruct
{
   unsigned int   messageType;
   ARLong32       messageNum;
   char          *messageText;
   ARBoolean      usePromptingPane;

}  ARMessageStruct;


#define AR_DATA_TYPE_NULL           0 /* code for a NULL value */
#define AR_DATA_TYPE_KEYWORD        1 /* code indicating a keyword setting */
#define AR_DATA_TYPE_INTEGER        2 /* codes for the data type of a value */
#define AR_DATA_TYPE_REAL           3
#define AR_DATA_TYPE_CHAR           4
#define AR_DATA_TYPE_DIARY          5
#define AR_DATA_TYPE_ENUM           6
#define AR_DATA_TYPE_TIME           7
#define AR_DATA_TYPE_BITMASK        8
#define AR_DATA_TYPE_BYTES          9
#define AR_DATA_TYPE_DECIMAL       10
#define AR_DATA_TYPE_ATTACH        11
#define AR_DATA_TYPE_CURRENCY      12
#define AR_DATA_TYPE_DATE          13
#define AR_DATA_TYPE_TIME_OF_DAY   14

#define AR_MAX_STD_DATA_TYPE       14

#define AR_DATA_TYPE_JOIN          30
#define AR_DATA_TYPE_TRIM          31 /* visual trim field */
#define AR_DATA_TYPE_CONTROL       32 /* control (button/menu/icon) field */
#define AR_DATA_TYPE_TABLE         33 /* table field */
#define AR_DATA_TYPE_COLUMN        34 /* column field */
#define AR_DATA_TYPE_PAGE          35 /* page field */
#define AR_DATA_TYPE_PAGE_HOLDER   36 /* page holder field */
#define AR_DATA_TYPE_ATTACH_POOL   37 /* attachment pool */

#define AR_DATA_TYPE_ULONG         40
#define AR_DATA_TYPE_COORDS        41
#define AR_DATA_TYPE_VIEW          42 /* view field */
#define AR_DATA_TYPE_DISPLAY       43 /* display field (e.g., flashlets) */

#define AR_DATA_TYPE_MAX_TYPE      43

#define AR_FIELD_TYPE_DATA          1 /* per record stored data field type */
#define AR_FIELD_TYPE_TRIM          2 /* visual trim field type */
#define AR_FIELD_TYPE_CONTROL       4 /* GUI control field type */
#define AR_FIELD_TYPE_PAGE          8 /* page field type */
#define AR_FIELD_TYPE_PAGE_HOLDER  16 /* page holder field type */
#define AR_FIELD_TYPE_TABLE        32 /* table field type */
#define AR_FIELD_TYPE_COLUMN       64 /* column field type */
#define AR_FIELD_TYPE_ATTACH      128 /* attachment field type */
#define AR_FIELD_TYPE_ATTACH_POOL 256 /* attachment pool type */

#define AR_FIELD_TYPE_ALL   (AR_FIELD_TYPE_DATA | AR_FIELD_TYPE_TRIM | \
                             AR_FIELD_TYPE_CONTROL | AR_FIELD_TYPE_PAGE | \
                             AR_FIELD_TYPE_PAGE_HOLDER | AR_FIELD_TYPE_TABLE | \
                             AR_FIELD_TYPE_COLUMN | AR_FIELD_TYPE_ATTACH | \
                             AR_FIELD_TYPE_ATTACH_POOL)

#define AR_DEFAULT_VALUE_NONE       0 /* code used to indicate that there is */
                                      /*  no default value for this field    */

/* an additional AR_KEYWORD_NULL concept is mapped to AR_DATA_TYPE_NULL */

                                      /* codes for keywords supported */
#define AR_KEYWORD_DEFAULT          0 /* admin defined default for the field */
#define AR_KEYWORD_USER             1 /* login name of the current user */
#define AR_KEYWORD_TIMESTAMP        2 /* current date/time */
#define AR_KEYWORD_TIME_ONLY        3 /* current time (date defaults to */
                                      /*  today)                        */
#define AR_KEYWORD_DATE_ONLY        4 /* current date (time defaults to */
                                      /*  midnight)                     */
#define AR_KEYWORD_SCHEMA           5 /* schema currently being worked on */
#define AR_KEYWORD_SERVER           6 /* server currently being accessed */
#define AR_KEYWORD_WEEKDAY          7 /* current day of the week */
#define AR_KEYWORD_GROUPS           8 /* groups current user is member of */
#define AR_KEYWORD_OPERATION        9 /* operation being performed (see */
                                      /*  defines)                      */
#define AR_KEYWORD_HARDWARE        10 /* hardware operating on (see uname) */
#define AR_KEYWORD_OS              11 /* OS and release of OS (see uname) */
#define AR_KEYWORD_DATABASE        12 /* database and version of database */
#define AR_KEYWORD_LASTID          13 /* EntryID of most recently created */
                                      /*  entry                           */
#define AR_KEYWORD_LASTCOUNT       14 /* number of matches to most recent */
                                      /*  search                          */
#define AR_KEYWORD_VERSION         15 /* version of current environment */
#define AR_KEYWORD_VUI             16 /* current VUI (client only) */
#define AR_KEYWORD_GUIDETEXT       17 /* current Guide Text (client only) */
#define AR_KEYWORD_FIELDHELP       18 /* current Field Help (client only) */
#define AR_KEYWORD_GUIDE           19 /* current guide (client only) */
#define AR_KEYWORD_APPLICATION     20 /* current application (client only) */
#define AR_KEYWORD_LOCALE          21 /* user locale */
#define AR_KEYWORD_CLIENT_TYPE     22 /* client type of the api program */
#define AR_KEYWORD_SCHEMA_ALIAS    23 /* alias name for the current form */
#define AR_KEYWORD_ROWSELECTED     24 /* indicates if row in a table is */
                                      /*  selected (client only)        */
#define AR_KEYWORD_ROWCHANGED      25 /* table row status - loaded, modified, */
                                      /*  new or deleted (client only)        */
#define AR_KEYWORD_BROWSER         26 /* browser type (client only) */
#define AR_KEYWORD_VUI_TYPE        27 /* current VUI type */
#define AR_KEYWORD_TCPPORT         28 /* TCP/IP port of the local arserver */
#define AR_KEYWORD_HOMEURL         29 /* base location of mid-tier install */
#define AR_KEYWORD_ROLES           30 /* roles current use is member of */
#define AR_KEYWORD_EVENTTYPE       31 /* type, or name, of event received by */
                                      /*  window (client only)               */
#define AR_KEYWORD_EVENTSRCWINID   32 /* window id from which the event was */
                                      /*  sent (client only)                */
#define AR_KEYWORD_CURRENTWINID    33 /* returns the window id of the current */
                                      /*  window (client only)                */
#define AR_KEYWORD_LASTOPENEDWINID 34 /* ret window id from last open window */
                                      /*  action (client only)               */
#define AR_KEYWORD_INBULKTRANS     35 /* indicates if currently within a bulk */
                                      /*  entry transaction                   */
#define AR_KEYWORD_FIELDID         36 /* returns the field id for currently */
                                      /*  selected field (client only)      */
#define AR_KEYWORD_FIELDNAME       37 /* returns the field name for currently */
                                      /*  selected field (client only)        */
#define AR_KEYWORD_FIELDLABEL      38 /* returns the field label for currently */
                                      /*  selected field (client only)         */
#define AR_KEYWORD_SERVERTIMESTAMP 39 /* current date/time on the server (same */
                                      /*  (as AR_KEYWORD_TIMESTAMP on server)  */
#define AR_KEYWORD_GROUPIDS        40 /* group ids for groups current user */
                                      /*  is a member of                   */
#define AR_KEYWORD_EVENTDATA       41 /* data, of event received by */
                                      /*  window (client only)      */
#define AR_KEYWORD_ERRNO           42 /* errorcode of the current workflow action */
                                      /* Relevant both in filter/activelink error handler */
#define AR_KEYWORD_ERRMSG          43 /* error message of the current workflow action */
                                      /* Relevant both in filter/activelink error handler */
#define AR_KEYWORD_ERRAPPENDMSG    44 /* additional appended message(if any) of the error above */
#define AR_KEYWORD_INCLNTMANAGEDTRANS    45 /* Indicates if currently in client managed transaction */
#define AR_KEYWORD_DRAGSRCFIELDID  46 /* return field ID of source field for drag operation */
#define AR_KEYWORD_DROPTGTFIELDID  47 /* return field ID of destination field for drop operation */
#define AR_KEYWORD_SHIFT_KEY       48 /* Indicates if shift key was pressed while triggering a workflow */
#define AR_KEYWORD_CTRL_KEY        49 /* Indicates if control key was pressed while triggering a workflow */
#define AR_KEYWORD_ALT_KEY         50 /* Indicates if ALT key was pressed while triggering a workflow */        
#define AR_KEYWORD_AUTHSTRING      51 /* returns the authString */
#define AR_KEYWORD_ROWVISIBLE      52 /* indicates if row in a table is */
                                      /*  visible (client only)         */
#define AR_KEYWORD_NO              53 /* no more keywords !! Returns NO */
/*
 * NB AR system developers: when you add a keyword here, add it also
 * to arkeywords.h and to Keywords.java.
 */


#define AR_MAX_KEYWORD_USED        AR_KEYWORD_NO  /* set to code for "highest" keyword */

#define AR_KEY_OPERATION_CREATE  "CREATE"    /* User Tool - Submit */
#define AR_KEY_OPERATION_DELETE  "DELETE"    /* User Tool - Delete */
#define AR_KEY_OPERATION_GET     "GET"       /* User Tool - Display */
#define AR_KEY_OPERATION_GETLIST "GETLIST"   /* User Tool - Query List */
#define AR_KEY_OPERATION_MERGE   "MERGE"     /* User Tool - N/A */
#define AR_KEY_OPERATION_SET     "SET"       /* User Tool - Modify */
#define AR_KEY_OPERATION_SET_ALL "SET ALL"   /* User Tool - Modify All */
#define AR_KEY_OPERATION_QUERY   "QUERY"     /* User Tool - Query */
#define AR_KEY_OPERATION_GUIDE   "GUIDE"     /* User Tool - N/A */
#define AR_KEY_OPERATION_SERVICE "SERVICE"
#define AR_KEY_OPERATION_ERRHANDLE "ERROR-HANDLER" /* Server only - Filter Err Handling */

#define AR_PATTERN_KEY_DIGIT      101 /* codes for keyword in char patterns */
#define AR_PATTERN_KEY_ALPHA      102
#define AR_PATTERN_KEY_ALNUM      103
#define AR_PATTERN_KEY_PRINT      104
#define AR_PATTERN_KEY_UPPER      105
#define AR_PATTERN_KEY_LOWER      106
#define AR_PATTERN_KEY_MENU       107


typedef struct ARCoordStruct
{
   ARLong32 x;
   ARLong32 y;

}  ARCoordStruct;             /* in typographic points (i.e., pixels) */

typedef struct ARCoordList
{
   unsigned int    numItems;
   ARCoordStruct  *coords;

}  ARCoordList;               /* ordered list of 0 or more coordinates */


#define AR_LOC_NULL      0    /* RESERVED for future use */
#define AR_LOC_FILENAME  1    /* store and retrieve via filename */
#define AR_LOC_BUFFER    2    /* store and retrieve via memory buffer */


typedef struct ARBufStruct
{
   ARULong32      bufSize;
   unsigned char *buffer;

}  ARBufStruct;               /* A generic buffer */


typedef struct ARLocStruct
{
   ARULong32      locType;    /* AR_LOC_FILENAME | AR_LOC_BUFFER */
   union
   {
      char       *filename;   /* filename to open */
      ARBufStruct buf;        /* memory buffer */
   } u;

} ARLocStruct;                /* how to locate attachment */


typedef struct ARAttachStruct
{
   char         *name;        /* name of attachment */
   ARLong32      origSize;    /* pre-compression number of bytes */
   ARLong32      compSize;    /* post-compression number of bytes */
   ARLocStruct   loc;         /* how to locate attachment content */

}  ARAttachStruct;


typedef struct ARFuncCurrencyStruct
{
   char                *value;        /* numeric currency value */
   ARCurrencyCodeType   currencyCode; /* ISO currency code */

}  ARFuncCurrencyStruct;


typedef struct ARFuncCurrencyList
{
   unsigned int           numItems;
   ARFuncCurrencyStruct  *funcCurrencyList;

}  ARFuncCurrencyList;


typedef struct ARCurrencyStruct
{
   char                *value;           /* numeric value of currency      */
   ARCurrencyCodeType   currencyCode;    /* ISO currency code              */
   ARTimestamp          conversionDate;  /* timestamp of conversion        */
   ARFuncCurrencyList   funcList;        /* list of functional currencies  */

}  ARCurrencyStruct;

typedef struct ARCurrencyList
{
   unsigned int       numItems;
   ARCurrencyStruct  *currencyList;

}  ARCurrencyList;


                               /* Structure used to hold a value.  There is */
                               /*  one branch for each datatype/property    */
typedef struct ARValueStruct   /*  that is supported by the system.         */
{
   unsigned int   dataType;    /* AR_DATA_TYPE_xxx */
   union
   {
      /*
       * noval_ is big enough to initialize both integer and pointer
       * union members in declarations like
       *   ARValueStruct val = { 0, {0}};
       */
      size_t             noval_;
      unsigned int       keyNum;
      ARLong32           intVal;
      double             realVal;
      char              *charVal;
      char              *diaryVal;
      ARULong32          enumVal;
      ARTimestamp        timeVal;
      ARULong32          maskVal;
      ARTime             timeOfDayVal;
      ARByteList        *byteListVal;
      char              *decimalVal;
      ARAttachStruct    *attachVal;
      ARULong32          ulongVal;
      ARCoordList       *coordListVal;
      int                dateVal;
      ARCurrencyStruct  *currencyVal;
      /*
       * Placeholder for passing pointers through this data structure.
       * Can only be used locally - you can't XDR a pointer unless
       * you know the type of object being referenced.
       */
      void              *ptrVal;
   } u;

} ARValueStruct;


typedef struct ARValueList
{
   unsigned int    numItems;
   ARValueStruct  *valueList;

}  ARValueList;               /* list of 0 or more values */


typedef struct ARValuePtrList
{
   unsigned int    numItems;
   ARValueStruct **valuePtrList;

}  ARValuePtrList;            /* list of 0 or more value pointers */


typedef struct ARValueListList
{
   unsigned int   numItems;
   ARValueList   *valueListList;

}  ARValueListList;           /* list of 0 or more value lists */


#define AR_START_WITH_FIRST_ENTRY  0 /* code to indicate should retrieve from */
                                       /*  result set starting with first entry */

#define AR_NO_MAX_LIST_RETRIEVE    0 /* code to indicate no maximum limit for */
                                       /*  number of entries retrieved in list  */

#define AR_RETRIEVE_ALL_ENTRIES    999999999  /* retrieve all entries even if there is a limit on  */
                                              /* the number of entries that the server will return */

typedef struct AREntryListFieldStruct
{
   ARInternalId   fieldId;
   unsigned int   columnWidth;
   char           separator[10];

}  AREntryListFieldStruct;    /* definition for a field in the entry list */

typedef struct AREntryListFieldList
{
   unsigned int             numItems;
   AREntryListFieldStruct  *fieldsList;

}  AREntryListFieldList;      /* list of 0 or more fields in entrylist */


typedef struct AREntryListFieldListList
{
   unsigned int           numItems;
   AREntryListFieldList  *listFieldList;

}  AREntryListFieldListList;  /* list of 0 or more fields lists */


typedef struct AREntryListStruct
{
   AREntryIdList   entryId;
                  /* short description of the entry that    */
                  /*  contains data from selected fields of */
                  /*  the entry                             */
   char           *shortDesc;

}  AREntryListStruct;         /* key to an entry */

typedef struct AREntryFuncListStruct
{
   AREntryIdList   entryId;
   int             funcId;
                  /* short description of the entry that    */
                  /*  contains data from selected fields of */
                  /*  the entry                             */
   char           *shortDesc;

}  AREntryFuncListStruct;         /* key to an entry */

typedef struct AREntryListList
{
   unsigned int        numItems;
   AREntryListStruct  *entryList;

}  AREntryListList;           /* list of 0 or more entries */

typedef struct AREntryFuncListList
{
   unsigned int        numItems;
   AREntryFuncListStruct  *entryList;

}  AREntryFuncListList;           /* list of 0 or more entries */

typedef struct AREntryIdListList
{
   unsigned int    numItems;
   AREntryIdList  *entryIdList;

}  AREntryIdListList;         /* list of 0 or more entryIds */


typedef struct ARFieldValueStruct
{
   ARInternalId    fieldId;
   ARValueStruct   value;

}  ARFieldValueStruct;        /* id and value for a single field */


typedef struct ARFieldValueList
{
   unsigned int         numItems;
   ARFieldValueStruct  *fieldValueList;

}  ARFieldValueList;          /* list of 0 or more field/value pairs */


                              /* parallel entry list structures which are */
                              /* used to return entryList as a list of    */
                              /* entryId and entry as field/value pairs   */
typedef struct AREntryListFieldValueStruct
{
   AREntryIdList      entryId;
   ARFieldValueList  *entryValues;

}  AREntryListFieldValueStruct;


typedef struct AREntryListFieldValueList
{
   unsigned int                  numItems;
   AREntryListFieldValueStruct  *entryList;

}  AREntryListFieldValueList; /* list of 0 or more entries */

typedef struct ARFieldFuncValueStruct
{
   ARInternalId    fieldId;
   int             funcId;
   ARValueStruct   value;

}  ARFieldFuncValueStruct;        /* id and value for a single field */


typedef struct ARFieldFuncValueList
{
   unsigned int         numItems;
   ARFieldFuncValueStruct  *fieldValueList;

}  ARFieldFuncValueList;          /* list of 0 or more field/value pairs */

typedef struct AREntryListFieldFuncValueStruct
{
   AREntryIdList      entryId;
   ARFieldFuncValueList  *entryValues;

}  AREntryListFieldFuncValueStruct;


typedef struct AREntryListFieldFuncValueList
{
   unsigned int                  numItems;
   AREntryListFieldFuncValueStruct  *entryList;

}  AREntryListFieldFuncValueList; /* list of 0 or more entries */

typedef struct ARBooleanList
{
   unsigned int   numItems;
   ARBoolean     *booleanList;

}  ARBooleanList;             /* list of 0 or more ARBoolean */


typedef struct ARBooleanListList
{
   unsigned int    numItems;
   ARBooleanList  *booleanList;

}  ARBooleanListList;         /* list of 0 or more ARBooleanList */

typedef struct ARFieldValueListList
{
   unsigned int       numItems;
   ARFieldValueList  *valueListList;

}  ARFieldValueListList;      /* list of 0 or more ARFieldValueList */

typedef struct ARFieldFuncValueListList
{
   unsigned int       numItems;
   ARFieldFuncValueList  *valueListList;

}  ARFieldFuncValueListList;      /* list of 0 or more ARFieldValueList */

#define AR_MERGE_ENTRY_DUP_ERROR          1
#define AR_MERGE_ENTRY_DUP_NEW_ID         2
#define AR_MERGE_ENTRY_DUP_OVERWRITE      3
#define AR_MERGE_ENTRY_DUP_MERGE          4
#define AR_MERGE_ENTRY_GEN_NEW_ID         5

#define AR_MERGE_NO_REQUIRED_INCREMENT 1024 /* code added to above to "ignore */
                                            /*  required" during merge        */
#define AR_MERGE_NO_PATTERNS_INCREMENT 2048 /* code added to above to "ignore */
                                            /*  patterns" during merge        */
#define AR_MERGE_NO_WORKFLOW_FIRED     4096 /* code added to above to "ignore */
                                            /* filter processing" during merge*/
/* multimatch option */
#define AR_MERGE_ENTRY_MULT_MATCH_ERROR        0
#define AR_MERGE_ENTRY_MULT_MATCH_USE_FIRST    1


/* forward declaration */
struct ARQualifierStruct;

/* Structures used to specify qualifying criteria for a set of entries. */

#define AR_STAT_HISTORY_USER  1 /* tags to indicate user or time field */
#define AR_STAT_HISTORY_TIME  2

typedef struct ARStatHistoryValue
{
   ARULong32       enumVal;
   unsigned int    userOrTime;

}  ARStatHistoryValue;

#define AR_MAX_LOCAL_VARIABLES     10  /* maximum number of local variables */

#define AR_QUERY_VALUE_MULTI_ERROR  1  /* tags for what to do with multiple */
#define AR_QUERY_VALUE_MULTI_FIRST  2  /*  matches on a Query Value         */
#define AR_QUERY_VALUE_MULTI_SET    3

typedef struct ARQueryValueStruct
{
   ARNameType                 schema;
   char                       server[AR_MAX_SERVER_SIZE + 1];
   struct ARQualifierStruct  *qualifier;
   ARInternalId               valueField;
   unsigned int               multiMatchCode;

}  ARQueryValueStruct;

#define AR_CURRENCY_PART_FIELD        0  /* tags for currency field parts */
#define AR_CURRENCY_PART_VALUE        1
#define AR_CURRENCY_PART_TYPE         2
#define AR_CURRENCY_PART_DATE         3
#define AR_CURRENCY_PART_FUNCTIONAL   4

#define AR_CURRENCY_CODE_LEN          3

typedef struct ARCurrencyPartStruct
{
   ARInternalId         fieldId;
   unsigned int         partTag;
   ARCurrencyCodeType   currencyCode;

}  ARCurrencyPartStruct;


#define AR_FIELD                  1 /* tags to indicate field or value */
#define AR_VALUE                  2 /* general tags used for all instances */
#define AR_ARITHMETIC             3
#define AR_STAT_HISTORY           4
#define AR_VALUE_SET              5 /* set of values used for "IN" operator */
#define AR_CURRENCY_FLD           6

                                    /* options from here down are used only */
                                    /*  by filters and active links         */

#define AR_FIELD_TRAN            50 /* tags used for filters to indicate      */
#define AR_FIELD_DB              51 /*  value in transaction or database only,*/
                                    /*  use "CURRENT" if value in tran or if  */
                                    /*  not there in db (use fieldId branch   */
                                    /*  of the structure)                     */
#define AR_LOCAL_VARIABLE        52 /* local variable for filter/active link */
#define AR_QUERY                 53 /* query another schema for filter/active */
                                    /*  link                                  */
#define AR_CURRENCY_FLD_TRAN     54 /* for currency fields the tags that are */
#define AR_CURRENCY_FLD_DB       55 /* the equivalent of transaction,        */
#define AR_CURRENCY_FLD_CURRENT  56 /* database, or current fields           */

#define AR_FIELD_CURRENT         99 /* tag used for active links to indicate */
                                    /*  a field reference to the screen the  */
                                    /*  active link is being fired from and  */
                                    /*  for filters to indicate use of the   */
                                    /*  value in the transaction if present  */
                                    /*  and db if not (use fieldId branch of */
                                    /*  the structure)                       */

    /* When processing qualifier structures, it is useful to be able to  */
    /* record the type of fieldIds encountered.  This offset is added to */
    /* one of the datatype fields to indicate the type of the fieldId.   */
    /* The AR_FIELD tag is converted into a "typed" tag which is         */
    /* referenced during searches of the database.                       */
#define AR_FIELD_OFFSET       12

#define AR_TEXT_OVERFLOW      -3  /* code used to indicate overflow on a */
                                  /* text string being built             */

typedef struct ARFieldValueOrArithStruct
{
   unsigned int tag;
   union
   {
      /*
       * noval_ is big enough to initialize both integer and pointer
       * union members in declarations like
       *   ARFieldValueOrArithStruct val = { 0, {0}};
       */
      size_t                   noval_;
      ARInternalId             fieldId;
      ARValueStruct            value;
      struct ARArithOpStruct  *arithOp;
      ARStatHistoryValue       statHistory;
      ARValueList              valueSet;
      unsigned int             variable;
      ARQueryValueStruct      *queryValue;
      ARCurrencyPartStruct    *currencyField;
   } u;

} ARFieldValueOrArithStruct;

#define AR_ARITH_OP_ADD          1 /* tags for type of arithmetic operation */
#define AR_ARITH_OP_SUBTRACT     2
#define AR_ARITH_OP_MULTIPLY     3
#define AR_ARITH_OP_DIVIDE       4
#define AR_ARITH_OP_MODULO       5
#define AR_ARITH_OP_NEGATE       6 /* unary minus; operandLeft is unused */

typedef struct ARArithOpStruct
{
   unsigned int                operation;
   ARFieldValueOrArithStruct   operandLeft;
   ARFieldValueOrArithStruct   operandRight;

}  ARArithOpStruct;

#define AR_REL_OP_EQUAL          1 /* tags for type of relational operation */
#define AR_REL_OP_GREATER        2
#define AR_REL_OP_GREATER_EQUAL  3
#define AR_REL_OP_LESS           4
#define AR_REL_OP_LESS_EQUAL     5
#define AR_REL_OP_NOT_EQUAL      6
#define AR_REL_OP_LIKE           7
#define AR_REL_OP_IN             8
#define AR_REL_OP_NOT_IN         9

typedef struct ARRelOpStruct
{
   unsigned int                operation;
   ARFieldValueOrArithStruct   operandLeft;
   ARFieldValueOrArithStruct   operandRight;

}  ARRelOpStruct;

#define AR_COND_OP_NONE          0 /* indicates no qualifier */
#define AR_COND_OP_AND           1 /* tags for type of conditional operation */
#define AR_COND_OP_OR            2
#define AR_COND_OP_NOT           3
#define AR_COND_OP_REL_OP        4
#define AR_COND_OP_FROM_FIELD    5

typedef struct ARAndOrStruct 
{
   struct ARQualifierStruct *operandLeft;
   struct ARQualifierStruct *operandRight;
} ARAndOrStruct;
/* For compatibility with strict ANSI C compilation modes, use the         */
/* "notQual" data member name rather than "not", and define AR_STRICT_ANSI */
/* in your project  The words "and", "or", and "not" have become ANSI C    */
/* reserved keyword, and will eventually be phased out of the AR API.      */

typedef struct ARQualifierStruct
{
   unsigned int   operation;
   union
   {
      ARAndOrStruct                 andor;
      #ifndef AR_STRICT_ANSI
         struct ARQualifierStruct  *not;
      #else
         struct ARQualifierStruct  *notQual;
      #endif
      ARRelOpStruct             *relOp;
      ARInternalId               fieldId;
   } u;
}  ARQualifierStruct;


typedef struct ARQualifierList
{
   unsigned int        numItems;
   ARQualifierStruct  *qualifierList;

}  ARQualifierList;                 /* list of 0 or more qualifier structures */

#define AR_SORT_ASCENDING        1  /* tags for sort order */
#define AR_SORT_DESCENDING       2

typedef struct ARSortStruct
{
   ARInternalId   fieldId;
   unsigned int   sortOrder;

}  ARSortStruct;


typedef struct ARSortList
{
   unsigned int   numItems;
   ARSortStruct  *sortList;

}  ARSortList;                      /* list of 0 or more sort criteria */


typedef struct ARSortListList
{
   unsigned int   numItems;
   ARSortList    *sortListList;

}  ARSortListList;                  /* list of 0 or more sort lists */


#define AR_STAT_OP_COUNT         1  /* tags for type of statistical op */
#define AR_STAT_OP_SUM           2
#define AR_STAT_OP_AVERAGE       3
#define AR_STAT_OP_MINIMUM       4
#define AR_STAT_OP_MAXIMUM       5

typedef struct ARStatisticsResultStruct
{
   ARValueList     groupByValues;
   ARValueStruct   result;

}  ARStatisticsResultStruct;


typedef struct ARStatisticsResultList
{
   unsigned int               numItems;
   ARStatisticsResultStruct  *resultList;

}  ARStatisticsResultList;          /* list of 0 or more results from stat request */


typedef struct ARIndexStruct
{
   unsigned int   numFields;
   ARInternalId   fieldIds[AR_MAX_INDEX_FIELDS];
   ARBoolean      unique;
   ARNameType     indexName;
   unsigned int   dataMappingUsageCnt;

}  ARIndexStruct;                   /* field(s) to specify an index */


typedef struct ARIndexList
{
   unsigned int    numItems;
   ARIndexStruct  *indexList;

}  ARIndexList;                     /* list of 0 or more indexes */


typedef struct ARIndexListList
{
   unsigned int   numItems;
   ARIndexList   *indexListList;

}  ARIndexListList;                 /* list of 0 or more index lists */


/* ARDayStruct was declared before the escalation structures.  It    */
/* has been brought forward here since ARArchiveInfo struct uses it. */
/* The macros that should be used to set the month, week, and hour   */
/* are still defined in the original place.                          */
typedef struct ARDayStruct
{
   ARLong32       monthday;  /* day of month in bitmask */
   ARLong32       weekday;   /* day of week in bitmask  */
   ARLong32       hourmask;  /* hour bitmask of the day */
                             /*  one hour for all days  */
   unsigned int   minute;    /* 0-59 minute of the hour */
                             /*  one minute mark only   */
}  ARDayStruct;


typedef struct ARArchiveInfoStruct
{
   unsigned int        enable;
   unsigned int        archiveType; /* form, file, delete */
   union
   {
      ARNameType       formName;
      char            *dirPath;
   } u;
   ARDayStruct         archiveTime;
   ARQualifierStruct   query;
   ARNameType          archiveFrom;

}  ARArchiveInfoStruct;


typedef struct ARArchiveInfoList
{
   unsigned int          numItems;
   ARArchiveInfoStruct  *archiveInfoList;

}  ARArchiveInfoList;                  /* list of 0 or more archive info's */

#define AR_ARCHIVE_NONE            0   /* no archive */
#define AR_ARCHIVE_FORM            1   /* copy to form  */
#define AR_ARCHIVE_DELETE          2   /* delete from main form */
#define AR_ARCHIVE_FILE_XML        4   /* archive to file in XML format */
#define AR_ARCHIVE_FILE_ARX        8   /* archive to file in ARX format */
#define AR_ARCHIVE_NO_ATTACHMENTS 32   /* do not archive attachments */
#define AR_ARCHIVE_NO_DIARY       64   /* do not archive diary fields */

typedef struct ARAuditInfoStruct
{
   unsigned int      enable;
   unsigned int      style;      /* copy, log, none */
   ARNameType        formName;   /* if copy then shadow form, if log then log form name */
                                 /* if none then can be the name of the main form */
   ARQualifierStruct query;      /* query for Audit */
   unsigned int      auditMask;  /* This mask can have three values as Default/Yes/No*/
} ARAuditInfoStruct;

typedef struct ARAuditInfoList
{
   unsigned int       numItems;
   ARAuditInfoStruct *auditInfoList;
} ARAuditInfoList;

#define AR_AUDIT_NONE 0
#define AR_AUDIT_COPY 1
#define AR_AUDIT_LOG  2
#define AR_AUDIT_LOG_SHADOW 3 /* to indicate a log shadow form - internal use only */

#define AR_AUDIT_ONLY_CHNG_FLDS_DEFAULT 0
#define AR_AUDIT_ONLY_CHNG_FLDS_YES     1
#define AR_AUDIT_ONLY_CHNG_FLDS_NO      2

#define AR_FIELD_OPTION_REQUIRED   1   /* tags for field definition option */
#define AR_FIELD_OPTION_OPTIONAL   2
#define AR_FIELD_OPTION_SYSTEM     3   /* system field; read-only to ALL users */
                                       /*  NOTE that fields cannot be created  */
                                       /*   with nor set to this option        */
#define AR_FIELD_OPTION_DISPLAY    4   /* display-only field; no data will be */
                                       /*  stored for this field in the DB    */
#define AR_FIELD_OPTION_FORCE_SYSTEM 5 /* To allow placeholder schema. */

#define AR_FIELD_OPEN_AT_CREATE       1/* tags for field create mode */
#define AR_FIELD_PROTECTED_AT_CREATE  2

#define AR_FIELD_BITOPTION_NONE  0x0000     /* no bit option */
#define AR_FIELD_BITOPTION_AUDIT 0x0001     /* BIT 0 - bit option to audit */
#define AR_FIELD_BITOPTION_COPY  0x0002     /* BIT 1 - bit option to copy when some field is being audited */
                              /* 0x0003        BIT 0 & 1 - indicates AUDIT + COPY */
#define AR_FIELD_BITOPTION_LOG_KEY1 0x0004  /* BIT 2 - bit option to indicate this field is log key 1 */
#define AR_FIELD_BITOPTION_LOG_KEY2 0x0008  /* BIT 3 - bit option to indicate this field is log key 2 */
#define AR_FIELD_BITOPTION_LOG_KEY3 0x000c  /* BIT 2 & 3 - bit option to indicate this field is log key 3 */

#define AR_FIELD_BITOPTION_AUDIT_MASK 0x0003 /* mask to check if any audit option is set */
#define AR_FIELD_BITOPTION_AUDIT_LOG_KEY_MASK 0x000c /* mask to check if any audit log key is set */

/* Mask of all audit options that are set from base to overlay */
#define AR_FIELD_BITOPTION_AUDIT_TO_OVERLAY_MASK (AR_FIELD_BITOPTION_AUDIT_MASK | AR_FIELD_BITOPTION_AUDIT_LOG_KEY_MASK)

#define AR_DISPLAY_TAG_SQL   "SQL"     /* tag used to identify SQL view display */

typedef struct ARPropStruct
{
   ARULong32       prop;               /* AR_*PROP_*; property tag */
   ARValueStruct   value;

}  ARPropStruct;                       /* display/object property */


typedef struct ARPropList
{
   unsigned int   numItems;
   ARPropStruct  *props;

}  ARPropList;                         /* list of 0 or more display/object properties */


typedef struct ARPropListList
{
   unsigned int   numItems;
   ARPropList    *propsList;

}  ARPropListList;                     /* list of 0 or more display/object properties lists */


typedef struct ARDisplayInstanceStruct
{
   ARInternalId   vui;     /* VUI to which display belongs */
   ARPropList     props;   /* properties specific to the vui */

}  ARDisplayInstanceStruct;            /* display instance */


typedef struct ARDisplayInstanceList
{                          /* properties common across displays */
   ARPropList                commonProps;
                           /* properties specific to one display */
   /* ASSERT ALIGN(this.numItems) >= ALIGN_NEEDED_BY(this.dInstanceList) */
   unsigned int              numItems;
   ARDisplayInstanceStruct  *dInstanceList;

}  ARDisplayInstanceList;


typedef struct ARDisplayInstanceListList
{
   unsigned int            numItems;
   ARDisplayInstanceList  *dInstanceList;

}  ARDisplayInstanceListList;          /* list of 0 or more display instance lists */


typedef struct ARDisplayInstanceListPtrList
{
   unsigned int            numItems;
   ARDisplayInstanceList **dInstanceListPtrList;

}  ARDisplayInstanceListPtrList;       /* list of 0 or more display instance list pointers */

/* values for cache display properties setting AR_SERVER_INFO_CACHE_DISP_PROP */

/* AR_CACHE_DPROP_VUI and AR_CACHE_DPROP_FIELD are no longer supported by the */
/* server and the value is no longer a bit mask                               */
#define AR_CACHE_DPROP_NONE                    0   /* cache server-only props */
#define AR_CACHE_DPROP_VUI                     1   /* deprecated - same as ALL */
#define AR_CACHE_DPROP_FIELD                   2   /* deprecated - same as ALL */
#define AR_CACHE_DPROP_ALL                     3   /* cache all props */


/* Display property and value definitions.  [0..16K] reserved for AR System. */
/*                                                                       */
/*      NAME                    VALUE    TYPE; DEFAULT; COMMENT          */
/*                                                                       */
/*     *** ONLY PROPERTIES DOCUMENTED IN MANUAL ARE SUPPORTED ***        */
#define AR_DPROP_NONE               0 /* NULL; no property */

/* Types of trim fields */
#define AR_DPROP_TRIM_TYPE          1 /* ENUM; no trim */
#define   AR_DVAL_TRIM_NONE           0 /* unknown trim */
#define   AR_DVAL_TRIM_LINE           1 /* polyline */
#define   AR_DVAL_TRIM_SHAPE          2 /* polygon */
#define   AR_DVAL_TRIM_TEXT           3 /* multi-row text */
#define   AR_DVAL_TRIM_IMAGE          4 /* static image */

/* Types of control fields */
#define AR_DPROP_CNTL_TYPE          2 /* BITMASK; no control */
#define   AR_DVAL_CNTL_BUTTON         1 /* button on view */
#define   AR_DVAL_CNTL_MENU           2 /* menu item */
#define   AR_DVAL_CNTL_TOOLBAR        4 /* toolbar item */
#define   AR_DVAL_CNTL_TAB_SWITCH     8 /* tabbed dialog switch */
#define   AR_DVAL_CNTL_URL           16 /* URL type button */
#define   AR_DVAL_CNTL_CHART         32 /* Chart type */
#define   AR_DVAL_CNTL_METER         64 /* Meter type */
#define   AR_DVAL_CNTL_HORIZNAV     128 /* Horizontal Navigation */
#define   AR_DVAL_CNTL_VERTICALNAV  256 /* Vertical Navigation */
#define   AR_DVAL_CNTL_NAV_ITEM     512 /* Navigation Item*/

/* Generic visual properties and values */
#define AR_FIXED_POINT_PRECISION    100 /* Precision of coordinate values */

#define AR_DPROP_BBOX               3 /* COORDS (box); no data area; */
                                      /*   context dependent         */
#define AR_DPROP_VISIBLE            4 /* ENUM (bool); visible */
#define AR_DPROP_ENABLE             5 /* ENUM; enabled */
#define   AR_DVAL_ENABLE_DEFAULT      0  /* default - probably read-write */
#define   AR_DVAL_ENABLE_READ_ONLY    1  /* make field read-only */
#define   AR_DVAL_ENABLE_READ_WRITE   2  /* make field read-write */
#define   AR_DVAL_ENABLE_DISABLE      3  /* make field disabled */
#define AR_DPROP_HELP               6 /* CHAR; use field/vui help */
#define AR_DPROP_Z_ORDER            7 /* ULONG; create on top */
#define AR_DPROP_COLOR_FILL         8 /* CHAR (name); */
#define   AR_DVAL_COLOR_NONE          "none"    /* transparent */
#define   AR_DVAL_COLOR_BG            "bg"      /* background */
#define   AR_DVAL_COLOR_FG            "fg"      /* foreground */
#define   AR_DVAL_COLOR_EDIT_BG       "edit_bg" /* text edit background */
#define   AR_DVAL_COLOR_EDIT_FG       "edit_fg" /* text edit foreground */
#define   AR_DVAL_COLOR_FOCUS         "focus"   /* input focus highlight */
#define   AR_DVAL_COLOR_INSET1        "inset1"  /* 1st level group */
#define   AR_DVAL_COLOR_INSET2        "inset2"  /* 2nd level group */
                                      /* custom color is "#BBGGRR" style tag */
#define AR_DPROP_DEPTH_EFFECT       9 /* ENUM; depends on field type */
#define   AR_DVAL_DEPTH_EFFECT_FLAT         0
#define   AR_DVAL_DEPTH_EFFECT_RAISED       1
#define   AR_DVAL_DEPTH_EFFECT_SUNKEN       2
#define   AR_DVAL_DEPTH_EFFECT_FLOATING     3
#define   AR_DVAL_DEPTH_EFFECT_ETCHED       4
#define AR_DPROP_DEPTH_AMOUNT      10 /* ULONG; depends on field type */
#define AR_DPROP_COLOR_LINE        11 /* CHAR (name); context dependent; */
#define AR_DPROP_COLOR_TEXT        12 /* CHAR (name); context dependent; */
#define AR_DPROP_PROMPT            13 /* CHAR; no prompt; this form of help is*/
                                      /* displayed on status line in Windows  */
#define AR_DPROP_HIDE_WEBHELP      14 /* ENUM (bool); True - Display help link*/
                                      /* False - No help link                 */
                                      /* Applicable for fields in web views   */

/* Every field has a label display property */
#define AR_DPROP_LABEL             20 /* CHAR (name); no label;      */
                                      /*   field ID used if no label */
#define AR_DPROP_LABEL_BBOX        21 /* COORDS (box); no label */
#define AR_DPROP_LABEL_FONT_STYLE  22 /* CHAR (name); derive from field */
                                      /*   type/option                  */
#define AR_DPROP_LABEL_FONT_SIZE   23 /* ULONG; derive from field setting */
#define AR_DPROP_LABEL_COLOR_TEXT  24 /* CHAR (name)(AR_DVAL_COLOR_*); */
                                      /*   foreground; */
#define AR_DPROP_LABEL_JUSTIFY     25 /* ENUM; depends on field setting */
#define   AR_DVAL_JUSTIFY_DEFAULT     0 /* default based on situation */
#define   AR_DVAL_JUSTIFY_LEFT        1 /* left justified */
#define   AR_DVAL_JUSTIFY_CENTER      2 /* centered */
#define   AR_DVAL_JUSTIFY_FILL        3 /* fill to both sides */
#define   AR_DVAL_JUSTIFY_RIGHT       4 /* right justified */
#define   AR_DVAL_JUSTIFY_TILE        5 /* tile to fill both sides */
#define AR_DPROP_LABEL_ALIGN       26 /* ENUM; derive from field setting */
#define   AR_DVAL_ALIGN_DEFAULT       0 /* default based on situation */
#define   AR_DVAL_ALIGN_TOP           1 /* top aligned */
#define   AR_DVAL_ALIGN_MIDDLE        2 /* middle aligned */
#define   AR_DVAL_ALIGN_FILL          3 /* expand height to fill */
#define   AR_DVAL_ALIGN_BOTTOM        4 /* bottom aligned */
#define   AR_DVAL_ALIGN_TILE          5 /* tile to fill height */
#define AR_DPROP_LABEL_POS_SECTOR  27 /* BITMASK; depends on field setting */
#define   AR_DVAL_SECTOR_NONE         0 /* Label not auto positioned */
#define   AR_DVAL_SECTOR_CENTER       1 /* Inside field data area */
#define   AR_DVAL_SECTOR_NORTH        2 /* On top of field data area */
#define   AR_DVAL_SECTOR_EAST         4 /* To the right of field data area */
#define   AR_DVAL_SECTOR_SOUTH        8 /* Below field data area */
#define   AR_DVAL_SECTOR_WEST        16 /* To the left of field data area */
#define AR_DPROP_LABEL_POS_JUSTIFY 28 /* ENUM (AR_DVAL_JUSTIFY_*); not auto */
                                      /*  positioned                        */
#define AR_DPROP_LABEL_POS_ALIGN   29 /* ENUM (AR_DVAL_ALIGN_*); not auto */
                                      /*   positioned                     */
#define AR_DPROP_LABEL_COLOR_FILL  30 /* CHAR (name)(AR_DVAL_COLOR_*); */
                                      /* context dependent             */
#define AR_DPROP_LABEL_COLOR_LINE  31 /* CHAR (name)(AR_DVAL_COLOR_*); */
                                      /* context dependent             */

/* Shared between lines and shapes */
#define AR_DPROP_COORDS            40 /* COORDS; required shapes default to */
                                      /* non-zero winding number rule       */
#define AR_DPROP_LINE_WIDTH        41 /* ULONG; 3; points */
#define AR_DPROP_LINE_PATTERN      42 /* CHAR (name); NULL;              */
                                      /* -(dash), *(dot), =(double)      */
                                      /*   Can arrange to convey pattern */
                                      /*   single dash means solid */
#define AR_DPROP_JOINT_STYLE       43 /* ENUM; rounded */
#define   AR_DVAL_JOINT_EXTENDED      0 /* small angles with long point */
#define   AR_DVAL_JOINT_SHARP         1 /* angles w/ point, trunc small angles*/
#define   AR_DVAL_JOINT_ROUNDED       2 /* rounded corners */
#define   AR_DVAL_JOINT_SMOOTH        3 /* between ROUNDED and MAX_SMOOTH */
#define   AR_DVAL_JOINT_MAX_SMOOTH    4 /* all straight lines smoothed */

/* Line specific display properties */
#define AR_DPROP_ENDCAP_START      44 /* ENUM; rounded */
#define AR_DPROP_ENDCAP_END        45 /* ENUM; rounded */
#define   AR_DVAL_ENDCAP_ROUND        0 /* rounded */
#define   AR_DVAL_ENDCAP_FLUSH        1 /* flush */
#define   AR_DVAL_ENDCAP_EXTENDED     2 /* extended past coord */
#define   AR_DVAL_ENDCAP_ARROW1       3 /* arrow 1 style */

/* Field "dimension" semantic properties, not to be used for gfx positionning */
#define AR_DPROP_DATA_ROWS         60 /* ULONG; base on BBOX; legacy usage */
#define AR_DPROP_DATA_COLS         61 /* ULONG; base on BBOX; legacy usage */

/* Data field editing display properties */
#define AR_DPROP_DATA_SPIN         62 /* ENUM (bool); no spinner; */
                                      /*  part of data gfx        */
#define AR_DPROP_DATA_MENU         63 /* ENUM (bool); no menu; */
                                      /*  may be separate gfx  */
#define AR_DPROP_DATA_RADIO        64 /* ENUM; dropdown/radio/checkbox style */
#define   AR_DVAL_RADIO_DROPDOWN      0 /* dropdown */
#define   AR_DVAL_RADIO_RADIO         1 /* radio */
#define   AR_DVAL_RADIO_CHECKBOX      2 /* checkbox */

/* Location of subcomponents in data fields, relative to field's parent */
#define AR_DPROP_DATA_MENU_BBOX    65 /* COORDS (box); no menu accel */
#define AR_DPROP_DATA_EXPAND_BBOX  66 /* COORDS (box); no expanded editor */

/* Display type of character field */
#define AR_DPROP_CHARFIELD_DISPLAY_TYPE  67 /* ENUM; edit/dropdown */
#define   AR_DVAL_CHARFIELD_EDIT            0 /* edit */
#define   AR_DVAL_CHARFIELD_DROPDOWN        1 /* dropdown */
#define   AR_DVAL_CHARFIELD_MASKED          2 /* masked  */
#define   AR_DVAL_CHARFIELD_FILE            3 /* File System Widget  */
#define   AR_DVAL_CHARFIELD_RICH_TEXT       4 /* normal rich text field  */
#define   AR_DVAL_CHARFIELD_RICH_TEXT_ADV   5 /* rich text with support for editing  */

/* Display Properties for Auto Complete */
#define AR_DPROP_CHARFIELD_AUTO_COMPLETE              68 /* ENUM; auto-complete in the character field */
#define   AR_DVAL_AUTO_COMPLETE_NONE                  0  /* none */
#define   AR_DVAL_AUTO_COMPLETE_LEADING               1  /* leading */
#define   AR_DVAL_AUTO_COMPLETE_ANYWHERE              2  /* anywhere */

/* Control how Auto Complete matching works */
#define AR_DPROP_CHARFIELD_AUTO_COMPLETE_MATCH_BY     69 /* ENUM; auto-complete matching option */
#define   AR_DVAL_AUTO_COMPLETE_MATCH_BY_VALUE        0 /* show and insert values */
#define   AR_DVAL_AUTO_COMPLETE_MATCH_BY_LABEL        1 /* show label, insert value */

/* Option to automatically add "Clear" selection */
#define AR_DPROP_ENABLE_CLEAR                         70  /* ENUM; policy on adding "Clear" to menu */
#define   AR_DVAL_ENABLE_CLEAR_ALWAYS                 0 /* add clear for all modes (the default) */
#define   AR_DVAL_ENABLE_CLEAR_SEARCH_ONLY            1 /* add clear for search mode only */

/* Multi-row text specific display properties (which may have label, too) */
#define AR_DPROP_TEXT              80 /* CHAR; font style name */
#define AR_DPROP_TEXT_FONT_STYLE   81 /* CHAR (name); derive from field */
                                      /*  type/option                   */
#define AR_DPROP_TEXT_FONT_SIZE    82 /* ULONG; derive from field type/option */

/* HTML Properties */
#define AR_DPROP_HTML_TEXT         83 /* CHAR; HTML Text */
#define AR_DPROP_HTML_TEXT_COLOR   84 /* ULONG; RGB in ColorRef */

/* Shared between image and text trim fields */
#define AR_DPROP_JUSTIFY           90 /* ENUM (AR_DVAL_JUSTIFY_*); field */
                                      /*  type/option derived            */
#define AR_DPROP_ALIGN             91 /* ENUM (AR_DVAL_ALIGN_*); field */
                                      /*  type/option derived          */

/* Button, toolbar, image specific */
#define AR_DPROP_IMAGE                  100 /* BYTELIST or Image Reference */
                                            /* image for toolbar icons     */

#define AR_DPROP_PUSH_BUTTON_IMAGE      101 /* BYTELIST or Image Reference */
                                            /* push button field image     */

/* Button control */
#define AR_DPROP_BUTTON_TEXT            110 /* CHAR (name); use label */
#define AR_DPROP_BUTTON_2D              111 /* ENUM (bool); display button */
                                            /*  as 2D image                */
#define AR_DPROP_BUTTON_IMAGE_POSITION  112 /* ENUM */
#define   AR_DVAL_IMAGE_CENTER              0 /* no label visible */
#define   AR_DVAL_IMAGE_LEFT                1 /* image to the left of label */
#define   AR_DVAL_IMAGE_RIGHT               2 /* image to the right of label */
#define   AR_DVAL_IMAGE_ABOVE               3 /* image above the label */
#define   AR_DVAL_IMAGE_BELOW               4 /* image below the label */
#define AR_DPROP_BUTTON_SCALE_IMAGE     113 /* ENUM (bool); scale image to */
                                            /*  fit button                 */
#define AR_DPROP_BUTTON_MAINTAIN_RATIO  114 /* ENUM (bool); maintain ratio */
                                            /*  of image if scaled         */

/* Menu item control */
#define AR_DPROP_MENU_TEXT        120 /* CHAR (name); use label */
#define AR_DPROP_MENU_POS         121 /* ULONG; 0-not specified; top to */
                                      /*  bottom starting at 1          */
#define AR_DPROP_MENU_MODE        122 /* ENUM; leaf */
#define   AR_DVAL_CNTL_ITEM           0 /* leaf node */
#define   AR_DVAL_CNTL_ON             1 /* yes|on (checked,depressed) */
#define   AR_DVAL_CNTL_SEPARATOR      2 /* separator (-, blank space) */
#define   AR_DVAL_CNTL_CHOICE         3 /* chosen, 1 of many (dot,depressed) */
#define   AR_DVAL_CNTL_DIALOG         4 /* dialog will pop up */
#define   AR_DVAL_CNTL_A_MENU         5 /* top level or sub menu(>,down arrow)*/

#define AR_DPROP_MENU_PARENT      123 /* ULONG (ARInternalId); 0 os top level */
#define AR_DPROP_MENU_HELP        124 /* CHAR (name); use for menu help */

/* Toolbar control */
#define AR_DPROP_TOOLTIP          130 /* CHAR (name); use label */
#define AR_DPROP_TOOLBAR_POS      131 /* ULONG; 0-not specified; left to */
                                      /*  right starting at 1            */
#define AR_DPROP_TOOLBAR_MODE     132 /* ENUM (AR_DPROP_CNTL_*); */
                                      /*  AR_DPROP_MENU_MODE     */
#define AR_DPROP_TOOLBAR_TEXT     133 /* CHAR (name); nothing; over image */

/* Tab switch control */
#define AR_DPROP_TAB_MODE         140 /* ENUM (AR_DPROP_CNTL_*); */
                                      /*  AR_DPROP_MENU_MODE     */
#define AR_DPROP_TAB_COORD        141 /* COORDS (1); (0,0)-not specified; */
                                      /* x is horizontal (left to right   */
                                      /*                  starting at 1); */
                                      /* y is vertical (bottom to top     */
                                      /*                starting at 1);   */
#define AR_DPROP_TAB_TEXT         142 /* CHAR (name); use label */
#define AR_DPROP_TAB_ORDER        143 /* ULONG - number for tab order of */
                                      /*  the field on the view          */

#define AR_DPROP_DATETIME_POPUP   144 /* ENUM (AR_DVAL_DATETIME_*) */
#define   AR_DVAL_DATETIME_BOTH       0 /* default: both date & time oriented */
#define   AR_DVAL_DATETIME_TIME       1 /* time only */
#define   AR_DVAL_DATETIME_DATE       2 /* date only */

/* background mode of a field (i.e. trim box or text) */
#define AR_DPROP_BACKGROUND_MODE  145 /* ENUM (AR_DVAL_BKG_MODE_*) */
#define   AR_DVAL_BKG_MODE_OPAQUE      0 /* default: */
#define   AR_DVAL_BKG_MODE_TRANSPARENT 1 /* transparent */

/* Inter field keyboard relationships */
#define AR_DPROP_TAB_NEXT         150 /* ULONG (ARInternalId); x,y order; */
                                      /*  can include tab switch          */
#define AR_DPROP_DATA_BBOX        151 /* COORDS sub-bounding box for data area*/

/* VUI specific */
#define AR_DPROP_VIEW_GRID_BBOX   160 /* COORDS (box); (0,0),(25,25) to match */
                                      /*  2.* default; suggest (0,0),(2x,2x)  */
#define AR_DPROP_VUI_DEFAULT      161 /* ENUM (bool); 0;                */
                                      /*  1st VUI is default, otherwise */

#define AR_DPROP_PANE_LAYOUT      162 /* INTEGER: 1 through 8 for layout   */
                                      /*  option negative if locked layout */
#define AR_DPROP_DETAIL_PANE_VISIBILITY 163 /* INTEGER: detail pane visibility*/
#define   AR_DVAL_PANE_ALWAYS_HIDDEN  3     /* pane always hidden */
#define   AR_DVAL_PANE_HIDDEN         0     /* pane hidden but can be visible */
#define   AR_DVAL_PANE_VISIBLE        1     /* pane visible but can be hidden */
#define   AR_DVAL_PANE_ALWAYS_VISIBLE 2     /* pane always visible */

#define AR_DPROP_PROMPT_PANE_VISIBILITY 164 /* INTEGER: AR_DVAL_PANE_* */
#define AR_DPROP_RESULT_PANE_VISIBILITY 165 /* INTEGER: AR_DVAL_PANE_* */

/* See AR_DPROP_PANE_VISIBILITY_OPTION (214) below - this determines whether */
/*   the above 3 properties (detail pane, result pane, and prompt pane */
/*   visibility) are used or not. */

#define AR_DPROP_DETAIL_PANE_COLOR 166      /* CHAR: #BBGGRR custom color */
#define AR_DPROP_DETAIL_PANE_IMAGE 167      /* BYTELIST or Image Reference */
                                            /* image for view background   */
#define AR_DPROP_IMAGE_ALIGN       168      /* ULONG: alignment of image */
                                            /*        AR_DVAL_ALIGN_*    */
#define AR_DPROP_IMAGE_JUSTIFY     169      /* ULONG: justification of   */
                                            /*   image AR_DVAL_JUSTIFY_* */

/* Specific to fields that are children of another field */
#define AR_DPROP_DISPLAY_PARENT   170   /* ULONG (ARInternalId); FieldId of */
                                        /*  parent field                    */

/* Page Field Specific Properties */
#define AR_DPROP_PAGE_ORDER       180           /* ULONG; order of appearence of a page */

#define AR_DPROP_PAGE_FIELD_TYPE  181           /* enum; type of page field        */
#define   AR_DVAL_PAGE_FIELD_NONEDITABLE    0   /* User can not modify the contents*/
#define   AR_DVAL_PAGE_FIELD_EDITABLE       1   /* User can modify the contents    */

#define AR_DPROP_TABLE_PANEL_BBOX  182          /* COORDS (box); no data area; */
                                                /* context dependent           */

/* Page Holder Specific Properties */
#define AR_DPROP_PAGE_LABEL_DISPLAY  190  /* ENUM (bool); 0; Position on */
                                          /*  page holder where page     */
                                          /*  labels should appear       */
#define   AR_DVAL_PAGE_DISPLAY_TOP        0 /* top */
#define   AR_DVAL_PAGE_DISPLAY_BOTTOM     1 /* bottom */
#define   AR_DVAL_PAGE_DISPLAY_LEFT       2 /* left */
#define   AR_DVAL_PAGE_DISPLAY_RIGHT      3 /* right */
#define   AR_DVAL_PAGE_DISPLAY_NONE       4 /* only one page exposed without */
                                            /*  any label                    */

#define AR_DPROP_PAGE_ARRANGEMENT     191 /* ENUM (bool); 0; how pages should */
                                          /*  be displayed if pages cannot    */
                                          /*  fit in page holder              */
#define   AR_DVAL_PAGE_SCROLL             0 /* scroll to view the pages */
#define   AR_DVAL_PAGE_LAYER              1 /* view as layers of pages */

#define AR_DPROP_DEFAULT_PAGE         192 /* ULONG; FieldId of page field    */
                                          /*  1st page is default, otherwise */

/* More VUI specific properties */
#define AR_DPROP_TITLE_BAR_ICON_IMAGE 200
                                     /* BYTELIST or Image Object Reference    */
                                     /* image for icon in title bar           */
                                     /* size of image is determined by Win32  */
                                     /* SDK call GetSystemMetrics(SM_CXSMICON)*/
                                     /* and GetSystemMetrics(SM_CYICON)       */
#define AR_DPROP_DETAIL_PANE_WIDTH    201
                                     /* INTEGER: width in schema coordinates  */
                                     /* of the detail pane.  Negative numbers */
                                     /* reserved for future use */
#define AR_DPROP_DETAIL_PANE_HEIGHT   202   /* INTEGER: height of detail pane */
#define AR_DPROP_DETAIL_BANNER_VISIBILITY 203
                                     /* ULONG: boolean - detail banner visible*/
#define AR_DPROP_PROMPT_BANNER_VISIBILITY 204
                                     /* ULONG: boolean - prompt banner visible*/
#define AR_DPROP_RESULT_BANNER_VISIBILITY 205
                                     /* ULONG: boolean - result banner visible*/
#define AR_DPROP_ALIAS_SINGULAR 206  /* CHAR: alias for singular, ie "Child" */
#define AR_DPROP_ALIAS_PLURAL 207    /* CHAR: alias for plural, ie "Children" */
#define AR_DPROP_ALIAS_SHORT_SINGULAR 208 /* CHAR: alias for short singular,*/
                                          /*        i.e. "Kid"              */
#define AR_DPROP_ALIAS_SHORT_PLURAL 209   /* CHAR: alias for short plural,  */
                                          /*       i.e. "Kids"              */
#define AR_DPROP_ALIAS_ABBREV_SINGULAR 210/* CHAR: alias for short sing abbr */
#define AR_DPROP_ALIAS_ABBREV_PLURAL  211 /* CHAR: alias for short plural abbr*/
#define AR_DPROP_NAMED_SEARCHES       212 /* CHAR: predefined named searches. */
                                          /* format is count\length\name\     */
                                          /* length\description\qualification\*/
#define AR_DPROP_MENU_ACCESS          213
                         /* CHAR: encoded menu access, format is            */
                         /*  length\field-id\state\field-id\state\etc...    */
                         /* field-id is AR_RESERV_*, a reserved menu field  */
                         /* id from arstruct.h.  State is a bitmask where   */
                         /* the lowest-order bit is enabled/disabled (bool) */
                         /* and the bit above that (bit 1) specifies        */
                         /* whether the enabled/disabled bit (bit 0) is     */
                         /* used.  Higher order bits are reserved for future */
                         /* settings, and must be zero.                      */
/* Macro to decode menu access state from the 'state' encoding described for */
/* AR_DPROP_MENU_ACCESS.  This macro will return TRUE (enabled, the default) */
/* if the enabled flag (bit 1) isn't set, Otherwise it will return TRUE      */
/* (enabled) or FALSE (disabled) based on bit 0, the state bit               */
#define AR_GET_MENU_ACCESS_ENABLED(x)      (x & 0x2) ? (x & 0x1) : TRUE
/* Set menu access to enabled */
#define AR_SET_MENU_ACCESS_ENABLED(x)      (x |= 0x3)
/* Set menu access to disabled */
#define AR_SET_MENU_ACCESS_DISABLED(x)     (x = (x | 0x2) & ~0x1)

#define AR_DPROP_PANE_VISIBILITY_OPTION 214 /* ENUM (bool): determines whether*/
                                            /* pane visibility for view is    */
                                            /* determined by admin or by user */
#define   AR_DVAL_PANE_VISIBILITY_USER_CHOICE 0 /* default: user decides */
#define   AR_DVAL_PANE_VISIBILITY_ADMIN       1 /* admin defined */

#define AR_DPROP_REQUEST_IDENTIFIER      215/* ULONG: field id of field to use*/
                                            /* for 'id' of this ticket for    */
                                            /* display purposes               */
#define AR_DPROP_QUERY_LIST_COLOR        216/* CHAR: encoded: query list color*/
                                            /* by priority -- format is       */
                                            /* fieldid\numvalues\value\color\value\color... */
/* Note numbering gap 217 - 219 */
                                          /* table and column field specific */
#define AR_DPROP_COLUMN_WIDTH       220   /* INTEGER; col width in table field*/
#define AR_DPROP_COLUMN_ORDER       221   /* INTEGER; col order in table field*/
#define AR_DPROP_SORT_SEQ           222   /* INTEGER; col seq in sort order */

#define AR_DPROP_SORT_DIR           223   /* ENUM; sort direction - ascending */
                                          /*       or dec                     */
#define   AR_DVAL_SORT_DIR_ASCENDING    0 /* lowest to highest */
#define   AR_DVAL_SORT_DIR_DESCENDING   1 /* highest to lowest */

#define AR_DPROP_DRILL_DOWN         224   /* ULONG (bitmask); row drill down */
                                          /*                  for details    */
#define   AR_DVAL_DRILL_DOWN_NONE     0x0 /* DRILL_DOWN not allowed */
#define   AR_DVAL_DRILL_DOWN_ENABLE   0x1 /* DRILL_DOWN is enabled */

#define AR_DPROP_REFRESH            225   /* ENUM; table field refresh enabled*/
#define   AR_DVAL_REFRESH_NONE          0 /* No REFRESH of data               */
#define   AR_DVAL_REFRESH_TABLE_MAX     1 /* REFRESH according to max defined */
                                          /* for table field                  */
#define AR_DPROP_AUTO_REFRESH       226   /* ENUM; table field refresh enabled*/
#define   AR_DVAL_AUTO_REFRESH_NONE       0 /* No AUTO REFRESH of data        */
#define   AR_DVAL_AUTO_REFRESH_TABLE_MAX  1 /* AUTO REFRESH according to max  */
                                          /* defined for table field          */
#define AR_DPROP_AUTOFIT_COLUMNS    227   /* ENUM; Allow horizontal scrollbar */
                                          /* in table field                   */
#define   AR_DVAL_AUTOFIT_COLUMNS_NONE  0 /* No Scrollbar. User Tool will auto*/
                                          /* scale the column width           */
#define   AR_DVAL_AUTOFIT_COLUMNS_SET   1 /* Scrollbar will be enabled in the */
                                          /* Table Field                      */
                                          /* when displayed in User Tool      */
#define AR_DPROP_APPLY_DIRTY        228   /* ENUM; Apply to Dirty Bit         */
#define AR_DPROP_IMAGE_CACHE        229   /* ULONG: runtime cache of internal */
                                          /* image format, not a design time  */
                                          /* property, client specific format */
#define AR_DPROP_ENUM_LABELS        230   /* CHAR: display labels for         */
                                          /* localized selection fields.      */
#define AR_DPROP_MANAGE_EXPAND_BOX  231   /* ENUM; Control Over Presence of   */
                                          /*       Expand boxes               */
#define   AR_DVAL_EXPAND_BOX_DEFAULT   0  /* Default value */
#define   AR_DVAL_EXPAND_BOX_HIDE      1  /* HIDE the expand box */
#define   AR_DVAL_EXPAND_BOX_SHOW      2  /* show the expand box */

#define AR_DPROP_ATTACH_ADD_LABEL     232 /* char; label for the Add button   */
                                          /* for Attachment's Web View        */
#define AR_DPROP_ATTACH_DELETE_LABEL  233 /* char; label for the Delete       */
                                          /* button for Attachment's Web View */
#define AR_DPROP_ATTACH_DISPLAY_LABEL 234 /* char; label for the Display      */
                                          /* button for Attachment's Web View */
#define AR_DPROP_ATTACH_SAVE_LABEL    235 /* char;label for the Save button in*/
                                          /* Attachment's Web View            */
#define AR_DPROP_ATTACH_LABEL_TITLE   236 /* char;title of Attachment Pool's  */
                                          /* label column                     */
#define AR_DPROP_ATTACH_FILENAME_TITLE 237/* char;title of Attachment Pool's  */
                                          /* Filename column                  */
#define AR_DPROP_ATTACH_FILESIZE_TITLE 238/* char;title of Attachment Pool's  */
                                          /* File size column                 */
#define AR_DPROP_HIDE_PAGE_TABS_BORDERS 239/* boolean;0 is the default to show*/
                                          /* the borders and Tab and 1 to hide*/
#define AR_DPROP_DISPLAY_AS_TEXT_ONLY 240 /* boolean; To display the chars in */
                                          /*      any data field as text only.*/
#define AR_DPROP_AR_OBJECT_NAME       241 /* char; ar object name reference   */
#define AR_DPROP_DISPLAY_FIELD_APP    242 /* char; char string to indicate    */
                                          /* display field's application type */
#define AR_DPROP_ZERO_SIZE_WHEN_HIDDEN 243/* boolean; make field zero size    */
                                          /*      when hidden                 */
#define AR_DPROP_ACCESSIBLE_HINT      244 /* CHAR: store workflow hint for    */
                                          /*       accessibility              */
#define AR_DPROP_INITIAL_CURRENCY_TYPE 245/* char; initial type for currency  */
                                          /*       field                      */
#define AR_DPROP_AUTO_FIELD_COLPROP       246 /* integer; field size w.r.t columns*/

#define AR_DPROP_AUTO_FIELD_ROWNUM        247 /* integer; field's row*/

#define AR_DPROP_AUTO_FIELD_ROWPART       248 /* integer; field's column*/

#define AR_DPROP_AUTO_FIELD_ORDER         249 /* ULONG; field's order in view*/

#define AR_DPROP_AUTO_FIELD_TYPE          250 /* enum; field type */
#define   AR_DVAL_AUTO_FIELD_REGULAR          0 /* Regular Field */
#define   AR_DVAL_AUTO_FIELD_NAV              1 /* Navigation Field */
#define   AR_DVAL_AUTO_FIELD_ACTION           2 /* Action area Field */
#define   AR_DVAL_AUTO_FIELD_GROUPTITLE       3 /* Group Title Field */
#define   AR_DVAL_AUTO_FIELD_PAGETITLE        4 /* Page Title Field */
#define   AR_DVAL_AUTO_FIELD_APPTITLE         5 /* Application Title Field */

#define AR_DPROP_AUTO_LAYOUT              251 /* enum; Auto layout (vui prop) */
#define   AR_DVAL_AUTO_LAYOUT_OFF             0 /* Layout Off */
#define   AR_DVAL_AUTO_LAYOUT_ON              1 /* Layout On */

#define AR_DPROP_AUTO_LAYOUT_VUI_NAV      252 /* enum; navigation (vui prop) */
#define   AR_DVAL_AUTO_LAYOUT_VUI_NAV_OFF     0 /* Nav Off */
#define   AR_DVAL_AUTO_LAYOUT_VUI_NAV_ON      1 /* Nav On */

#define AR_DPROP_AUTO_LAYOUT_STYLE_SHEET  253 /* char; xml info of style sheet*/

#define AR_DPROP_AUTO_FIELD_NAVPROP       254 /* enum; nav level */
#define   AR_DVAL_AUTO_FIELD_LEVEL1           0 /* level 1 */
#define   AR_DVAL_AUTO_FIELD_LEVEL2           1 /* level 2 */
#define   AR_DVAL_AUTO_FIELD_LEVEL3           2 /* level 3 */

#define AR_DPROP_AUTO_FIELD_SPACER        255 /* enum; nav level */
#define   AR_DVAL_AUTO_FIELD_SPACER_OFF       0 /* Off */
#define   AR_DVAL_AUTO_FIELD_SPACER_ON        1 /* On */

#define AR_DPROP_FORMACTION_FIELDS        256 /* char; row order and list of */
                                              /*  form action fields         */

#define AR_DPROP_AUTO_SET_OVERLAP_FIELD   257 /* ULONG (ARInternalId); id of */
                                              /*  the overlapped field       */

#define AR_DPROP_AR_SERVER_NAME           258 /* char; ar server name */
                                              /*  reference in FB     */

#define AR_DPROP_AUTO_FIELD_ALIGN         259 /* enum; Align Field (Button) */
#define   AR_DVAL_AUTO_FIELD_ALIGN_LEFT       0 /* Align left */
#define   AR_DVAL_AUTO_FIELD_ALIGN_RIGHT      1 /* Align Right */

#define AR_DPROP_FORMACTION_PAGE_PROPERTIES     260 /* CHAR; page property */

#define AR_DPROP_FORMACTION_FLDS_EXCLUDE        261 /* enum; Exclude FormAction */
                                                    /*  flds (vui prop)         */
#define   AR_DVAL_FORMACTION_FLDS_EXCLUDE_OFF     0 /* Off */
#define   AR_DVAL_FORMACTION_FLDS_EXCLUDE_ON      1 /* On  */

#define AR_DPROP_AUTO_FIELD_NEW_COLUMN          262 /* enum; Adds field in a new column*/
#define   AR_DVAL_AUTO_FIELD_NEW_COLUMN_OFF       0 /* Off */
#define   AR_DVAL_AUTO_FIELD_NEW_COLUMN_ON        1 /* On  */

#define AR_DPROP_AUTO_FIELD_NEW_SECTION         263 /* enum; Adds field in a new row*/
#define   AR_DVAL_AUTO_FIELD_NEW_SECTION_OFF      0 /* Off */
#define   AR_DVAL_AUTO_FIELD_NEW_SECTION_ON       1 /* On  */

#define AR_DPROP_VUI_DEFAULT_PROCESS            264 /* ENUM (bool); 0; */
                                                    /*A default view for reports, set/push fields etc.*/
#define AR_DPROP_WEB_HEADER_CONTENT             265 /* Used to contain html snippets for */
#define AR_DPROP_WEB_FOOTER_CONTENT             266 /* web header and footer for form    */
                                                    /* absolute view.                    */
#define AR_DPROP_PATH_TO_BKG_IMAGE              267 /* CHAR: Allow path to the background image*/
                                                    /* to be specified. */
#define AR_DPROP_WEB_TOOLBAR_VISIBILITY         268 /* ULONG: Don't show web toolbar if admin disabled*/
                                                    /* this view property from Appearance tab */

#define AR_DPROP_AR_GRAPH_PLUGIN_NAME           269 /* Char: Name of the plugin to be attached*/
                                                    /* Graph Plug-n field */

#define AR_DPROP_EXPAND_COLLAPSE_TREE_LEVELS    270 /* Integer; expand or collapse tree levels */
#define   AR_DVAL_EXPAND_ALL_LEVELS               1 /* Expand All Levels */
#define   AR_DVAL_COLLAPSE_ALL_LEVELS             2 /* Collapse All Levels */
#define AR_DPROP_ATTACH_DESELECT_LABEL          271 /* char; label for the deselectall  */
                                                    /* button for Attachment's Web View */

/* display properties for panels */
#define AR_DPROP_LAYOUT_POLICY                        272 /*enum*/
#define   AR_DVAL_LAYOUT_XY                           0
#define   AR_DVAL_LAYOUT_FILL                         1
#define   AR_DVAL_LAYOUT_FLOW                         2

#define AR_DPROP_PAGEHOLDER_DISPLAY_TYPE              273 /*enum*/
#define   AR_DVAL_PAGEHOLDER_DISPLAY_TYPE_TABCTRL       0
#define   AR_DVAL_PAGEHOLDER_DISPLAY_TYPE_STACKEDVIEW   1
#define   AR_DVAL_PAGEHOLDER_DISPLAY_TYPE_SPLITTERVIEW  2
#define   AR_DVAL_PAGEHOLDER_DISPLAY_TYPE_ACCORDION     3

#define AR_DPROP_ORIENTATION                          274 /*enum*/
#define   AR_DVAL_ORIENTATION_HORIZONTAL              0   /*Horizontal Orientation*/
#define   AR_DVAL_ORIENTATION_VERTICAL                1   /*Vertical Orientation*/
#define   AR_DVAL_ORIENTATION_VERTICAL_UP             2   /*Vertical Reverse Orientation*/

#define AR_DPROP_PAGEHOLDER_MARGIN_LEFT               275 /*integer*/
#define AR_DPROP_PAGEHOLDER_MARGIN_TOP                276 /*integer*/
#define AR_DPROP_PAGEHOLDER_MARGIN_RIGHT              277 /*integer*/
#define AR_DPROP_PAGEHOLDER_MARGIN_BOTTOM             278 /*integer*/
#define AR_DPROP_PAGEHOLDER_SPACING                   279 /*integer*/
#define AR_DPROP_PAGEHOLDER_INIT_PAGE                 280 /*integer*/

#define AR_DPROP_PAGE_HEADER_STATE                    281 /*enum*/
#define   AR_DVAL_PAGE_HEADER_HIDDEN                  0
#define   AR_DVAL_PAGE_HEADER_VISIBLE                 1

#define AR_DPROP_PAGE_HEADER_COLOR                    282 /*char*/
#define AR_DPROP_PAGE_INITIAL_SIZE                    283 /*integer Can be width or height*/
#define AR_DPROP_PAGE_MIN_SIZE                        284 /*integer*/
#define AR_DPROP_PAGE_MAX_SIZE                        285 /*integer*/

#define AR_DPROP_PAGE_BODY_STATE                      286 /*enum*/
#define   AR_DVAL_PAGE_BODY_COLLAPSE                    0
#define   AR_DVAL_PAGE_BODY_EXPAND                      1

#define AR_DPROP_LOCALIZATION_REQUIRED                287 /* bool Property for view and fields*/
                                                          /* which need localization          */

/* Field effects display properties */  
#define AR_DPROP_FIELD_HIGHLIGHT                      288  /* boolean; */
#define   AR_DVAL_FIELD_HIGHLIGHT_DISABLE             0    /* Field Highlight disabled */
#define   AR_DVAL_FIELD_HIGHLIGHT_ENABLE              1    /* Field Highlight enabled */

#define AR_DPROP_FIELD_HIGHLIGHT_START_COLOR          289  /* it is a color property */
#define AR_DPROP_FIELD_HIGHLIGHT_END_COLOR            290  /* it is a color property */

/* Field display property for rounded corners */  
#define AR_DPROP_FIELD_ROUNDED                        291  /* boolean; */
#define   AR_DVAL_FIELD_ROUNDED_DISABLE               0    /* Field rounded disabled */
#define   AR_DVAL_FIELD_ROUNDED_ENABLE                1    /* Field rounded enabled */

/*****NEW PROPERTY FOR Fill layout*********/
#define AR_DPROP_FIELD_MIN_WIDTH                      292 /*integer*/
#define AR_DPROP_FIELD_MAX_WIDTH                      293 /*integer*/
#define AR_DPROP_FIELD_MIN_HEIGHT                     294 /*integer*/
#define AR_DPROP_FIELD_MAX_HEIGHT                     295 /*integer*/

#define AR_DPROP_COLOR_FILL_GRADIENT                  296 /* char */
#define AR_DPROP_COLOR_FILL_GRADIENT_EFFECT           297 /* enum */
#define   AR_DVAL_GRADIENT_EFFECT_NONE                   0
#define   AR_DVAL_GRADIENT_EFFECT_LINEAR_HORIZONTAL      1
#define   AR_DVAL_GRADIENT_EFFECT_LINEAR_VERTICAL        2
#define   AR_DVAL_GRADIENT_EFFECT_REFLECTED_HORIZONTAL   3
#define   AR_DVAL_GRADIENT_EFFECT_REFLECTED_VERTICAL     4

#define AR_DPROP_COLOR_FILL_OPACITY                   298 /* real ( 0.0 - 1.0) */

/* Some more field display properties for rounded corners */  
#define AR_DPROP_FIELD_ROUNDED_TOP_RIGHT_RADIUS       300 /* integer */
#define AR_DPROP_FIELD_ROUNDED_TOP_LEFT_RADIUS        301 /* integer */
#define AR_DPROP_FIELD_ROUNDED_BOTTOM_RIGHT_RADIUS    302 /* integer */
#define AR_DPROP_FIELD_ROUNDED_BOTTOM_LEFT_RADIUS     303 /* integer */

/* splitter panel holder property */
#define AR_DPROP_PANELHOLDER_SPLITTER                 304/* enum */
#define AR_DVAL_SPLITTER_HIDE                           0   /* HIDE SPLITTER*/
#define   AR_DVAL_SPLITTER_SHOW                       1   /* SHOW SPLITTER*/
#define AR_DVAL_SPLITTER_INVISIBLE                      2   /* Invisible splitter with resize capability */

/* Panel Header Gradient Color */

#define AR_DPROP_COLOR_GRADIENT_HEADER                         305  /* char */ 
#define AR_DPROP_COLOR_GRADIENT_EFFECT_HEADER                  306  /* enum */
#define   AR_DVAL_GRADIENT_EFFECT_HEADER_NONE                  0
#define   AR_DVAL_GRADIENT_EFFECT_HEADER_LINEAR_HORIZONTAL     1
#define   AR_DVAL_GRADIENT_EFFECT_HEADER_LINEAR_VERTICAL       2
#define   AR_DVAL_GRADIENT_EFFECT_HEADER_REFLECTED_HORIZONTAL  3
#define   AR_DVAL_GRADIENT_EFFECT_HEADER_REFLECTED_VERTICAL    4

/* Panel Holder borders */
#define AR_DPROP_HIDE_PANELHOLDER_BORDERS              307 /* Boolean */

#define AR_DPROP_PANEL_SLACK_ORDER      308 /* integer OBSOLETE, remove post-I2 */
#define AR_DPROP_PANEL_SLACK_DISTRIBUTION_ORDER  308 /* integer */
#define AR_DPROP_PANEL_AVOID_WHITESPACE 309 /* Boolean OBSOLETE, remove post-I2 */
#define AR_DPROP_PANEL_FIT_TO_CONTENT            309 /* Boolean */

#define AR_DPROP_ALIGNED                310 /* Enum */
#define   AR_DVAL_ALIGNED_LEFT          0   /* default */
#define   AR_DVAL_ALIGNED_RIGHT         1

#define AR_DPROP_RIGHT_BBOX             311 /* COORDS (Box) */

#define AR_DPROP_HEADER_HEIGHT          312 /*integer*/
#define AR_DPROP_NAV_ITEM_TEXT_COLOR    313 /*Char*/ 

/* Drag and Drop properties */
#define AR_DPROP_FIELD_DRAGGABLE        314  /* Boolean */
#define AR_DPROP_FIELD_DROPPABLE        315  /* Boolean */

/* Localize view */
#define AR_DPROP_LOCALIZE_VIEW          316  /* Enum */
#define   AR_DVAL_LOCALIZE_VIEW_SKIP      0
#define   AR_DVAL_LOCALIZE_VIEW_ALL       1
/* Localize field’s labels */
#define AR_DPROP_LOCALIZE_FIELD         317  /* Enum */
#define   AR_DVAL_LOCALIZE_FIELD_SKIP     0
#define   AR_DVAL_LOCALIZE_FIELD_ALL      1

#define AR_DPROP_FLOW_LAYOUT_VERT_SPACE 318 /* Int; Vertical spacing between fields */

#define AR_DPROP_PANEL_MARGIN_LEFT      319 /* integer */
#define AR_DPROP_PANEL_MARGIN_TOP       320 /* integer */
#define AR_DPROP_PANEL_MARGIN_RIGHT     321 /* integer */
#define AR_DPROP_PANEL_MARGIN_BOTTOM    322 /* integer */
#define AR_DPROP_AUTO_RESIZE            323 /* enum */
#define   AR_DVAL_RESIZE_NONE             0
#define   AR_DVAL_RESIZE_VERT             1
#define   AR_DVAL_RESIZE_HORZ             2
#define   AR_DVAL_RESIZE_BOTH             3

#define AR_DPROP_FIELD_FLOAT_STYLE      324 /* enum applies to panel holder or panel */
#define   AR_DVAL_FLOAT_STYLE_NONE      0
#define   AR_DVAL_FLOAT_STYLE_MODELESS  1
#define   AR_DVAL_FLOAT_STYLE_DIALOG    2
#define   AR_DVAL_FLOAT_STYLE_TOOLTIP   3

#define AR_DPROP_FIELD_FLOAT_EFFECT     325   /* enum applies to panel holder or panel */
#define   AR_DVAL_FLOAT_EFFECT_NONE             0
#define   AR_DVAL_FLOAT_EFFECT_APPEAR_DISAPPEAR 1
#define   AR_DVAL_FLOAT_EFFECT_GROW_SHRINK      2
#define   AR_DVAL_FLOAT_EFFECT_FADEIN_FADEOUT   3

#define AR_DPROP_PANELHOLDER_SHRINKTOFIT  326   /* Boolean */
#define AR_DPROP_PANEL_BORDER_THICKNESS   327   /* String */
#define AR_DPROP_AUTO_COMPLETE_AFTER_KEYSTROKES  328 /* integer */
#define AR_DPROP_AUTO_COMPLETE_HIDE_MENU_BUTTON  329 /* Boolean */

#define AR_DPROP_ROW_LABEL              330 /* String */
#define AR_DPROP_ROW_LABEL_PLURAL       331 /* String */


/** Table field column header and data alignment **/
#define AR_DPROP_TABLE_COLUMN_HEADER_ALIGNMENT   332 /* integer */
#define AR_DPROP_TABLE_COLUMN_DATA_ALIGNMENT     333 /* integer */
#define   AR_DVAL_TABLE_COLUMN_ALIGNMENT_RIGHT     0
#define   AR_DVAL_TABLE_COLUMN_ALIGNMENT_CENTER    1
#define   AR_DVAL_TABLE_COLUMN_ALIGNMENT_LEFT      2

#define AR_DPROP_MOUSEOVER_EFFECT                334 /* enum - mouseover effect */
#define   AR_DVAL_MOUSEOVER_EFFECT_NONE            0
#define   AR_DVAL_MOUSEOVER_EFFECT_CURSOR          1
#define   AR_DVAL_MOUSEOVER_EFFECT_HIGHLIGHT       2

#define AR_DPROP_DVF_INLINE                      335 /* Boolean */
#define AR_DPROP_EXTERNAL_LINK_BUTTON  336 /* Integer */

   /* ***Note numbering gap [337,899] */

/* char; properties to help regularize localization */
#define AR_DPROP_PREFIX_NEW             900
#define AR_DPROP_PREFIX_SEARCH          901
#define AR_DPROP_PREFIX_MODIFY          902
#define AR_DPROP_PREFIX_MODIFY_ALL      903
#define AR_DPROP_PREFIX_DISPLAY         904
#define AR_DPROP_PREFIX_MATCHING_REQ    905
#define AR_DPROP_PREFIX_NO_MATCHING_REQ 906

#define AR_DPROP_PREFIX_MINval          900
#define AR_DPROP_PREFIX_MAXval          906

    /* ***Note numbering gap [907,5000] */

/* Table field properties */
#define AR_DPROP_TABLE_DISPLAY_TYPE  5001 /* enum; type of table field */
#define   AR_DVAL_TABLE_DISPLAY_TABLE              0 /* regular table field */
#define   AR_DVAL_TABLE_DISPLAY_RESULTS_LIST       1 /* results list */
#define   AR_DVAL_TABLE_DISPLAY_NOTIFICATION       2 /* alert list */
#define   AR_DVAL_TABLE_DISPLAY_SINGLE_TABLE_TREE  3 /* Single Table Tree */
#define   AR_DVAL_TABLE_DISPLAY_MULTI_TABLE_TREE   4 /* Multiple Table Tree */
#define   AR_DVAL_TABLE_DISPLAY_PAGE_ARRAY         5 /* Table Page Array Field */

#define AR_DPROP_TABLE_SELINIT       5003 /* enum; initial selection within */
                                          /*  table field when it is loaded */
#define   AR_DVAL_TABLE_SELINIT_SELFIRE     0 /* select 1st, fire workflow */
#define   AR_DVAL_TABLE_SELINIT_SELNOFIRE   1 /* select 1st, no workflow */
#define   AR_DVAL_TABLE_SELINIT_NOSEL       2 /* no selection, no workflow */

#define AR_DPROP_TABLE_SELREFRESH    5004 /* enum; selection within table */
                                          /*  field after a refresh       */
#define   AR_DVAL_TABLE_SELREFRESH_RETFIRE     0 /* retain select, fire workflow*/
#define   AR_DVAL_TABLE_SELREFRESH_RETNOFIRE   1 /* retain select, no workflow */
#define   AR_DVAL_TABLE_SELREFRESH_FIRSTFIRE   2 /* select 1st, fire workflow */
#define   AR_DVAL_TABLE_SELREFRESH_FIRSTNOFIRE 3 /* select 1st, no workflow */
#define   AR_DVAL_TABLE_SELREFRESH_NOSEL       4 /* no selection, no workflow */

#define AR_DPROP_TABLE_CHUNK_SIZE    5005 /* integer; table chunk size */
#define AR_DPROP_TABLE_CHUNK_NEXT    5006 /* char; label for next chunk */
#define AR_DPROP_TABLE_CHUNK_PREV    5007 /* char; label for prev chunk */
#define AR_DPROP_TABLE_NOT_REFRESHED 5008 /* char; string to display when */
                                          /*  table is not loaded         */
#define AR_DPROP_TABLE_ENTRIES_RETURNED 5009/* char; string indicating number */
                                            /*  of table entries returned     */
#define AR_DPROP_TABLE_AUTOREFRESH   5010 /* char; auto refresh string */
#define AR_DPROP_TABLE_DRILL_COL     5011 /* integer; field ID of column to */
                                          /*  use as drill down column in   */
                                          /*  table field on the web        */
#define AR_DPROP_TABLE_SELROWS_DISABLE 5012/* enum; disable row selection */
#define   AR_DVAL_TABLE_SELROWS_MULTI_SELECT   0 /* multiple selection */
#define   AR_DVAL_TABLE_SELROWS_DISABLE_YES    1 /* selection disabled */
#define   AR_DVAL_TABLE_SELROWS_SINGLE_SELECT  2 /* single selection */
#define   AR_DVAL_TABLE_SELROWS_DISABLE_NO     AR_DVAL_TABLE_SELROWS_MULTI_SELECT /* obsolete */

#define AR_DPROP_TABLE_SELECT_ALL      5013 /* char; select all string */
#define AR_DPROP_TABLE_DESELECT_ALL    5014 /* char; deselect all string */
#define AR_DPROP_TABLE_REFRESH         5015 /* char; refresh button label */
#define AR_DPROP_TABLE_REPORT          5016 /* char; report button label */
#define AR_DPROP_TABLE_DELETE          5017 /* char; delete button label */
#define AR_DPROP_TABLE_READ            5018 /* char; alert, "read" label */
#define AR_DPROP_TABLE_UNREAD          5019 /* char; alert, "unread" button */
#define AR_DPROP_TABLE_SELECTIONCOLUMN_LABEL 5020 /* char; display the label */
                                                  /* of Selection column     */
#define AR_DPROP_TABLE_COL_DISPLAY_TYPE 5021/* enum; display type of column */
#define    AR_DVAL_TABLE_COL_DISPLAY_NONEDITABLE   0 /* not editable */
#define    AR_DVAL_TABLE_COL_DISPLAY_EDITABLE      1 /* allow editing */
#define    AR_DVAL_TABLE_COL_DISPLAY_HTML          2 /* display html in column*/
#define    AR_DVAL_TABLE_COL_DISPLAY_PAGE_DATA     3 /* Table Page Array Page Data Field*/
#define    AR_DVAL_TABLE_COL_DISPLAY_DROPDOWN_MENU 4 /* support drop down menu */

#define AR_DPROP_TABLE_COL_INITVAL      5022/* char; initial value for column */

#define AR_DPROP_FIXED_TABLE_HEADERS    5023/* boolean; fixed table header */
#define    AR_DVAL_FIXED_TABLE_HEADERS_DISABLE     0 /* header disabled */
#define    AR_DVAL_FIXED_TABLE_HEADERS_ENABLE      1 /* header enabled */

#define AR_DPROP_VIEWFIELD_SCROLLBARS     5024      /* view fields, hide/show scroll bars */
#define    AR_DVAL_VIEWFIELD_SCROLLBARS_AUTO    0   /* add scrollbars if necessary */
#define    AR_DVAL_VIEWFIELD_SCROLLBARS_ON      1   /* always show scrollbars */
#define    AR_DVAL_VIEWFIELD_SCROLLBARS_HIDDEN  2   /* content is clipped */

#define AR_DPROP_VIEWFIELD_BORDERS        5025      /* view fields, hide/show borders */
#define    AR_DVAL_VIEWFIELD_BORDERS_DEFAULT    0   /* for native(border on) and web (based on display) */
#define    AR_DVAL_VIEWFIELD_BORDERS_NONE       1   /* no border on view field */
#define    AR_DVAL_VIEWFIELD_BORDERS_ENABLE     2   /* border on view field */

#define AR_DPROP_ENTRYPOINT_LABEL_DEFAULT_NEW     5026 /* label for default new EP */
#define AR_DPROP_ENTRYPOINT_LABEL_DEFAULT_SEARCH  5027 /* label for default search EP */

#define AR_DPROP_TABLE_COL_WRAP_TEXT   5058         /* boolean, multi-line column */
#define    AR_DVAL_TABLE_COL_WRAP_TEXT_DISABLE   0  /* multi-line disabled */
#define    AR_DVAL_TABLE_COL_WRAP_TEXT_ENABLE    1  /* multi-line enabled */

#define AR_DPROP_TABLE_PREFERENCES   5060                /* char; preferences button label */

#define AR_DPROP_FIELD_CUSTOMSTYLE   5061                /* char; custom style information */

#define AR_DPROP_TABLE_TREE_CUSTOM_NULL_VALUE   5062     /* char; custom value for Tree NULL nodes */

#define AR_DPROP_NAVBAR_INITIAL_SELECTED_ITEM   5063     /* ULONG (ARInternalId); id of */
                                                         /*  the selected field       */

#define AR_DPROP_NAVBAR_WORKFLOW_ON_SELECTED_ITEM   5064 /* enum; fire or do not fire workflow */
                                                         /*  on already selected item          */
#define   AR_DVAL_NAVBAR_SELITEM_NOFIRE         0        /* do not fire workflow */
#define   AR_DVAL_NAVBAR_SELITEM_FIRE           1        /* fire workflow */

#define AR_DPROP_NAVBAR_SELECT_ITEM_ON_CLICK    5065  /* ULONG; select item on click */

#define AR_DPROP_BUTTON_ALT_TEXT                5066  /* char; Alternative text to be used */
                                                      /*  for image button for 508 user    */

#define AR_DPROP_TABLE_USE_LOCALE               5067  /* boolean; table refresh using */
                                                      /*  user's locale               */

#define AR_DPROP_QUERY_LIST_BKG_COLOR           5068  /* CHAR: encoded: query list background */
                                                      /*  color by priority -- format is      */
                                                      /*  fieldid\numvalues\value\color\value\color... */

#define AR_DPROP_AUTO_MAXIMIZE_WINDOW           5069  /* boolean; auto maximize a window on */
                                                      /*  open - defined per view           */
#define    AR_DVAL_AUTO_MAXIMIZE_WINDOW_DISABLE   0    /* auto maximize disabled */
#define    AR_DVAL_AUTO_MAXIMIZE_WINDOW_ENABLE    1    /* auto maximize enabled  */

#define AR_DPROP_VIEW_RTL                       5070  /* boolean; RightToLeft property of a view */
#define    AR_DVAL_VIEW_RTL_DISABLE                0  /* RightToLeft disabled */
#define    AR_DVAL_VIEW_RTL_ENABLE                 1  /* RightToLeft enabled  */

/* Table Page Array Display Properties */
/* Table Page Array Margin Properties */
#define AR_DPROP_TABLE_PAGE_ARRAY_LEFT_MARGIN   5100 /* Int; Left Margin to use */
#define AR_DPROP_TABLE_PAGE_ARRAY_RIGHT_MARGIN  5101 /* Int; Right Margin to use */
#define AR_DPROP_TABLE_PAGE_ARRAY_TOP_MARGIN    5102 /* Int; Top Margin to use */
#define AR_DPROP_TABLE_PAGE_ARRAY_BOTTOM_MARGIN 5103 /* Int; Bottom Margin to use*/

#define AR_DPROP_TABLE_PAGE_VISIBLE_COLUMNS     5104 /* Int; Number of Visible Columns to display */
                                                     /* in the Table Page Array Field, i.e. number*/
                                                     /* of panels across. */

/* Table Array Horizontal and Vertical Space size */
#define AR_DPROP_TABLE_PAGE_ARRAY_HOR_SPACE     5109 /* Int; Horizontal spacing between panels */
#define AR_DPROP_TABLE_PAGE_ARRAY_VER_SPACE     5110 /* Int; Vertical spacing between panels   */ 

/* Remedy VUI are not supposed to be modified by Customers. */ 
/* We dont restrict them but we issue warning in case if below */
/* display property is set. Form level property takes precedence. */
#define AR_DPROP_FORM_LOCK_ALLVUI               5111 /* boolean; Form level property that makes all vui lock/unlock */
#define AR_DPROP_VUI_LOCK_VUI                   5112 /* boolean; VUI level property; can be set individually at VUI level or */
                                                     /* can be set/unset by form level preference. */

/*
 * Properties for attaching images to table cells/tree nodes.
 * AR_DPROP_ROOT_NODE_IMAGE is a single string value containing a
 * reference to an image (specifically, the name of an image object
 * in the current server.)
 * AR_DPROP_TABLE_ROOT_NODE_ALT_TEXT is a single string value containing
 * alternative text for the image.
 * AR_DPROP_TABLE_COL_IMAGE_LIST is a list of integer enum ids,
 * image references, and alt-text strings, formatted as
 *
 * fieldid\#vals\enum-id1\image-ref1\alt-text1\enum-id2\imag-ref2\alt-text2\...
 *
 * In order to let '\' appear in image-ref and alt-text substrings,
 * we introduce an escape notation.  Interpret the sequence "`\" as a
 * '\' character; interpret the sequence "``" as a '`' character.
 *
 * We do not honor this escape notation when decoding the similarly-formatted
 * AR_DPROP_ENUM_LABELS property value: in that property, '\' cannot appear
 * in any of the substrings because it cannot be distinguished from use of
 * '\' as a syntax character.
 */
#define AR_DPROP_TABLE_ROOT_NODE_IMAGE    5113  /* char; image ref */
#define AR_DPROP_TABLE_ROOT_NODE_ALT_TEXT 5114  /* char; alt text for image */
#define AR_DPROP_TABLE_COL_IMAGE_LIST     5115  /* char; see above */

#define AR_DPROP_SHOWURL                  5116  /* Display property for Show URL*/   
#define AR_DPROP_NAVIGATION_MODE          5117  /* Mode prop for navigation bar. */

#define   AR_DVAL_NAV_EXPANDABLE            0 /* default - expandable */
#define   AR_DVAL_NAV_FLYOUT                 1 /* fly out navigation */

#define AR_DPROP_TABLE_CELL_BKG_COLOR     5118  /* Table cell background color*/
#define AR_DPROP_TABLE_COL_ENABLE_SORT    5119  /* int, 0/1 */
#define AR_DVAL_TABLE_COL_SORT_DISABLED 0
#define AR_DVAL_TABLE_COL_SORT_ENABLED  1

#define AR_DPROP_APPLIST_MODE             5120  /* Disp Prop for Application List field */
#define AR_DVAL_APP_TRADITIONAL              0  /* default - traditional */
#define AR_DVAL_APP_FLYOUT                   1  /* fly out navigation */

#define AR_DPROP_TABLE_COLUMN_CHECKBOX       5121 /* Disp Prop for Table column check box */
#define AR_DVAL_TABLE_COLUMN_CHECKBOX_DISABLE   0 /* default - disabled */
#define AR_DVAL_TABLE_COLUMN_CHECKBOX_ENABLE    1 /* enabled */

/* Note numbering gap 5122:5199 to leave room for DPROP_TABLE properties */


#define AR_DPROP_SKIN_STYLE               5200  /* char; skin name */
#define AR_DPROP_ATTACH_FIELD_IMAGE_CACHE 5201  /* char; RTF Field mapping  */

/* disp prop version of AR_OPROP_LOCALIZE_FIELD_DATA property for backward compatibility */

#define AR_DPROP_LOCALIZE_FIELD_DATA      5202 /* enum; Localize field’s data */

#define AR_DPROP_FIELD_PROCESS_ENTRY_MODE      5203 /* enum; Field required or not while running process. */
#define AR_DVAL_FIELD_PROCESS_NOT_REQUIRED        0 /* default - not required */
#define AR_DVAL_FIELD_PROCESS_REQUIRED            1 /* required for process   */

/* disp prop for sort group - value should be 0 when not to group based on column or 1 otherwise */
#define AR_DPROP_SORT_GROUP                    5204

/* disp prop for sort aggregation type                                            *
 * when not to display the count value should be 0 (AR_DVAL_SORT_AGGREGATION NONE *
 * 1 otherwise (AR_DVAL_SORT_AGGREGATION_COUNT)                                   */

#define AR_DPROP_SORT_AGGREGATION_TYPE         5205
#define AR_DVAL_SORT_AGGREGATION_NONE           0
#define AR_DVAL_SORT_AGGREGATION_COUNT          1

/* disp prop for header footer grad type */
#define AR_DPROP_TABLE_HDRFTR_GRADTYPE   5206

/* disp prop for column header text color */
#define AR_DPROP_TABLE_COLUMN_HEADER_TEXT_COLOR 5207

/* disp prop for Table Header footer grad color */
#define AR_DPROP_TABLE_HDRFTR_GRADCOLOR              5208

/* disp prop for Table Footer background color */
#define AR_DPROP_TABLE_HDRFTR_GRADBKGCOLOR              5209

/* disp prop for View Field border color */
#define AR_DPROP_VIEW_BORDER_COLOR              5210

/* disp prop for vertical navigation bar */
#define AR_DPROP_VERTNAV_SUBLEVELTWO_COLOR      5211

#define AR_DPROP_TABLE_CONTENT_CLIPPED          5212 /* enum; Table loop content is clipped. */
#define AR_DVAL_TABLE_CONTENT_NOT_CLIPPED          0 /* default - not clipped */
#define AR_DVAL_TABLE_CONTENT_CLIPPED              1 /* content is clipped   */

/* disp prop for column header background type */
#define AR_DPROP_COL_HEADBKG_GRADTYPE           5213

/* disp prop for column header background color */
#define AR_DPROP_COL_HEADBKG_GRADCOLOR          5214

/* disp prop for column header background grad color */
#define AR_DPROP_COL_HEADBKG_GRADBKGCOLOR         5215

/* disp prop for drop shadow on panel holders inside lightweight popups  */
#define AR_DPROP_DROP_SHADOW                     5216
#define AR_DVAL_DROP_SHADOW_NONE                   0 /* default - no shadow */
#define AR_DVAL_DROP_SHADOW_NORTH_WEST             1 /* Add drop shadow     */

/* disp prop for  footer color */
#define AR_DPROP_ATTACH_FTRGRAD_COLOR             5217

/* disp prop for footer grad background color */
#define AR_DPROP_ATTACH_FTRGRADBKG_COLOR           5218

/* disp prop for footer grad type */
#define AR_DPROP_ATTACH_FTRGRAD_TYPE               5219

/* disp prop for attachment column grad color */
#define AR_DPROP_ATTACH_COLGRAD_COLOR              5220

/* disp prop for attachment colum grad background color */
#define AR_DPROP_ATTACH_COLGRADBKG_COLOR           5221

/* disp prop for attachment column grad type */
#define AR_DPROP_ATTACH_COLGRAD_TYPE               5222

/* disp prop for column header text color */
#define AR_DPROP_ATTACH_COLHDRTXT_COLOR             5223

/* disp prop for menu box */
#define AR_DPROP_MENU_BOX                           5224

/* disp prop for char-field border */
#define AR_DPROP_CHARFIELD_BORDER                   5225

/* disp prop for specifying different images for the disabled state of a button */ 
#define AR_DPROP_DISABLED_IMAGE                     5226

/* disp prop for top level background color for application list */
#define AR_DPROP_APPLIST_TOP_BKG_COLOR              5227

/* disp prop for even sub-level menus in application list */
#define AR_DPROP_APPLIST_SUB_EVEN_LVL_BKG_COLOR     5228

/* disp prop for odd sub-level menus in application list */
#define AR_DPROP_APPLIST_SUB_ODD_LVL_BKG_COLOR      5229

/* disp prop for column's initial state (Initially displayed or not) - boolean value */
#define AR_DPROP_COLUMN_INITIAL_STATE               5230
#define AR_DVAL_COLUMN_INITIAL_STATE_REMOVED        0    /* disp prop cloumn initial state value: removed */
#define AR_DVAL_COLUMN_INITIAL_STATE_SHOWN          1    /* disp prop cloumn initial state value: shown   */


/* Object property and value definitions.                                */
/*   0..59999       reserved property numbers for display properties.    */
/*   60000..89999   reserved for object properties for AR System         */
/*   90000..119999  reserved for object properties for AR System         */
/*   120001..180000 available for object properties                      */
/*                                                                       */
/*      NAME                    VALUE    TYPE; DEFAULT; COMMENT          */
/*                                                                       */
/*     *** ONLY PROPERTIES DOCUMENTED IN MANUAL ARE SUPPORTED ***        */

#define AR_OPROP_RESERVED           60000 /* CHAR; Name of company that  */
                                          /*       produces the product  */
#define AR_OPROP_VENDOR_NAME        60001 /* CHAR; Name of company that  */
                                          /*       produces the product  */
#define AR_OPROP_VENDOR_PRODUCT     60002 /* CHAR; Name of product       */
#define AR_OPROP_VENDOR_VERSION     60003 /* CHAR; Version of product    */
#define AR_OPROP_GUID               60004 /* CHAR; unique identifier for */
                                          /*       this object           */
#define AR_OPROP_COPYRIGHT          60005 /* CHAR; Copyright information */
#define AR_OPROP_SCC_LOCKED_BY      60006 /* CHAR; User who has this     */
                                          /*       object locked in      */
                                          /*       source code control   */
                                          /*       (SCC)                 */
#define AR_OPROP_SCC_VERSION        60007 /* CHAR; SCC version number    */
#define AR_OPROP_SCC_TIMESTAMP      60008 /* TIME; SCC last mod timestamp*/
#define AR_OPROP_SCC_USER           60009 /* CHAR; SCC last mod by user  */
#define AR_OPROP_SCC_LOCATION       60010 /* CHAR; Location in SCC DB    */
#define AR_OPROP_SCC_DATA_LOCKED_BY 60011 /* CHAR; User who has this     */
                                          /*       data locked in        */
                                          /*       source code control   */
                                          /*       (SCC)                 */
#define AR_OPROP_SCC_DATA_VERSION   60012 /* CHAR; SCC version num (data)*/
#define AR_OPROP_SCC_DATA_TIMESTAMP 60013 /* TIME; SCC mod time (data)   */
#define AR_OPROP_SCC_DATA_USER      60014 /* CHAR; SCC mod by user (data)*/
#define AR_OPROP_SCC_DATA_LOCATION  60015 /* CHAR; Loc in SCC DB (data)  */
#define AR_OPROP_WINDOW_OPEN_IF_SAMPLE_SERVER_SCHEMA    60016
                                          /* CHAR; Sample Server and Schema */
                                          /*       name for IF Window open  */
                                          /*       action in Advanced Mode. */
#define AR_OPROP_WINDOW_OPEN_ELSE_SAMPLE_SERVER_SCHEMA  60017
                                          /* CHAR; Sample Server and Schema */
                                          /*       name for ELSE Window open*/
                                          /*       action in Advanced Mode. */
#define AR_OPROP_FORM_NAME_WEB_ALIAS  60018 /* CHAR; Unique Form Alias used */
                                            /*       while deploying JSP    */
                                            /*       page for the Web       */
                                            /*       Server. Unique in a    */
                                            /*       given Server.          */
#define AR_OPROP_VIEW_LABEL_WEB_ALIAS 60019 /* CHAR; Unique View Label Alias*/
                                            /*       used while deploying   */
                                            /*       JSP page for the Web   */
                                            /*       Server. Unique in a    */
                                            /*       given Form.            */
#define AR_OPROP_APP_WEB_ALIAS      60020 /* CHAR; Unique Application Alias */
                                          /*       used while deploying JSP */
                                          /*       page for the Web Server. */
                                          /*       Unique in a given Server.*/
#define AR_OPROP_INTERVAL_VALUE     60021 /* INT; Interval value            */
                                          /*      used to indicate the      */
                                          /*      time interval between     */
                                          /*      an active link's timed    */
                                          /*      executions                */
#define AR_OPROP_INTEGRITY_KEY      60022 /* CHAR; The integrity key for the*/
                                          /*       lite AR Server.          */

#define AR_OPROP_NEXT_ID_BLOCK_SIZE 60023 /* INT; Next ID block size        */
                                          /*     override, if doesn't exist */
                                          /*     use the global setting.    */

#define AR_OPROP_POOL_NUMBER        60024 /* INT; Pool number if object is  */
                                          /*     assigned to a pool         */

#define AR_OPROP_CORE_FIELDS_OPTION_MASK  60025 
                                          /* INT; Bit mask of core field    */
                                          /*     options for a form         */
/* Bit mask values for AR_OPROP_CORE_FIELDS_OPTION_MASK */
#define AR_CORE_FIELDS_OPTION_NONE                          0
#define AR_CORE_FIELDS_OPTION_DISABLE_STATUS_HISTORY   0x0001

#define AR_OPROP_FT_SCAN_TIME_MONTH_MASK      60030 /* INT; day of the month bitmask */
#define AR_OPROP_FT_SCAN_TIME_WEEKDAY_MASK    60031 /* INT; weekday bitmask */
#define AR_OPROP_FT_SCAN_TIME_HOUR_MASK       60032 /* INT; hour bitmask */
#define AR_OPROP_FT_SCAN_TIME_MINUTE          60033 /* INT; minute value (0-59) */
#define AR_OPROP_FT_SCAN_TIME_INTERVAL        60034 /* INT; interval value (in seconds) */

#define AR_OPROP_GUIDE_PARAMETERS   60035 /* CHAR; Parameterized Guides*/
                                          /*       The arguments to a  */
                                          /*       Param Guide.        */

#define AR_OPROP_CACHE_DISP_PROP    60036 /* INT; bit mask for cache VUI       */
                                          /*      and Field display properties */

#define AR_OPROP_TRANSACTION_HANDLE_ID    60037 /* CHAR; This is a GUID based unique */
                                                /* identifier for the client managed transaction API support */
                                                /* This is used for putting the GUID in the given object property */
/* Property used to indicate the maximum number of temp tables that will be created for a vendor form. */
#define AR_OPROP_MAX_VENDOR_TEMP_TABLES       60038 /* INT; max number of temp tables */
/* Property used to indicate that permission inheritnace is turned on for this object. */
#define AR_OPROP_STATIC_PERMISSION_INHERITED  60039 /* INT; value is not used         */
                                          /*     presence of the prop means */
                                          /*     use group inheritance.     */
/* Property used to indicate that permission inheritnace is turned on for this object. */
#define AR_OPROP_DYNAMIC_PERMISSION_INHERITED 60040 /* CHAR; value is fieldID pairs    */
                                          /*     of the form "XXX:YYY"      */
                                          /*     the server will update YYY */
                                          /*     based on contents of XXX   */

#define AR_OPROP_MFS_OPTION_MASK    60045 /* INT; Bit mask of multi-form search */
                                          /*     options for a form             */

/* Bit mask values for AR_OPROP_MFS_OPTION_MASK */
#define AR_MULTI_FORM_SEARCH_OPTION_NONE                    0
#define AR_MULTI_FORM_SEARCH_OPTION_EXCLUDE            0x0001

#define AR_OPROP_FORM_ALLOW_DELETE            60046 /* INT; 1 to allow */
#define AR_OPROP_TABLE_PERSIST_DIRTY_ROWS     60047

#define AR_OPROP_MFS_WEIGHTED_RELEVANCY_FIELDS  60048 /* CHAR; semicolon separated list of field ids
                                                        mapped to weighted relevancy fields of multi-form
                                                        fts search in the format as below:
                                                        <numtags>;<field tag>;<fieldid>;<fieldtag>;<fieldid>..
                                                        e.g. 3;1;536870913;2;536870914;3;536870915
                                                        */
#define AR_MFS_WEIGHTED_RELEVANCY_TITLE_FIELD_TAG        1
#define AR_MFS_WEIGHTED_RELEVANCY_ENVIRONMENT_FIELD_TAG  2
#define AR_MFS_WEIGHTED_RELEVANCY_KEYWORDS_FIELD_TAG     3

#define AR_OPROP_APP_INTEGRATION_WORKFLOW       60049 /* CHAR; value is fieldID pairs    */

#define AR_OPROP_LOCALIZE_FORM_VIEWS            60050 /* enum; Localize field’s Views */
#define AR_LOCALIZE_FORM_VIEWS_SKIP                 0
#define AR_LOCALIZE_FORM_VIEWS_ALL                  1
#define AR_LOCALIZE_FORM_VIEWS_ALIASES              2
#define AR_OPROP_LOCALIZE_FORM_DATA             60051 /* enum; Localize form’s data */
#define AR_LOCALIZE_FORM_DATA_SKIP                  0
#define AR_LOCALIZE_FORM_DATA_ALL                   1
#define AR_OPROP_LOCALIZE_FIELD_DATA            60052 /* enum; Localize field’s data */
#define AR_LOCALIZE_FIELD_DATA_SKIP                 0
#define AR_LOCALIZE_FIELD_DATA_ALL                  1

#define AR_OPROP_FT_MFS_CATEGORY_NAME          60055 /* CHAR; option for a field; 
                                                        Category name for the field when
                                                        used in Full Text Multi-form search */
#define AR_OPROP_FT_MFS_INDEX_TABLE_FIELD      60056 /* enum; 1 to index, 0 to not index */
#define AR_FT_MFS_INDEX_TABLE_FIELD_OPTION_NO      0
#define AR_FT_MFS_INDEX_TABLE_FIELD_OPTION_YES     1

#define AR_OPROP_OBJECT_MODE                   60057 /* enum; Object property to distinguish whether
                                                         the object has been created in Customize mode or
                                                         Full mode of Developer Studio
                                                      */
#define AR_CUSTOMIZE_MODE_OBJECT                   0
#define AR_FULL_MODE_OBJECT                        1

#define AR_OPROP_OVERLAY_GROUP                 60058  /* CHAR; run time Overlay Group id    */
#define AR_OPROP_OVERLAY_DESIGN_GROUP          60059  /* CHAR; design time Overlay Group id */
#define AR_OPROP_OVERLAY_PROP                  60060  /* int; overlay prop */

/* for overlay group, apart from actual group id, */
/* one can also set following values              */
#define AR_OVERLAY_CLIENT_MODE_BASE           "-1" /* operation on base object object */
#define AR_OVERLAY_CLIENT_MODE_FULL           "-2" /* all objects available, referred to by real name */

#define AR_OPROP_DRILL_DOWN_IN_WEB_REPORTS     60062 /* boolean, Chart drill down */
#define AR_PROHIBIT_DRILL_DOWN_IN_WEB_REPORTS      0 /* Drill down disabled */
#define AR_ALLOW_DRILL_DOWN_IN_WEB_REPORTS         1 /* Drill down enabled */

#define AR_OPROP_FT_STRIP_TAGS                 60063 /* enum; 1 to strip the tags,      */
                                                     /*       0 to not strip the tags   */
#define AR_FT_STRIP_TAGS_OPTION_NO                 0
#define AR_FT_STRIP_TAGS_OPTION_YES                1

/*
 * enum; 0 default (multiple instances OK),
 *       1 open form as single instance through open-window action
 */
#define AR_OPROP_DISPLAY_FORM_SINGLETON   60064
#define AR_OPEN_FORM_MULTIPLE 0
#define AR_OPEN_FORM_SINGLETON 1

#define AR_OPROP_FT_FILTER_SEARCH              60065 /* enum; 1 to use FT search (default), */
                                                     /*       0 to not use FT search        */
#define AR_FT_FILTER_SEARCH_OPTION_NO              0
#define AR_FT_FILTER_SEARCH_OPTION_YES             1

/**
* Form tag
*/
#define AR_OPROP_FORM_TAG_NAME                  60066

/* SetVui will have objProp specifying the list of fields whose */
/* display instance has changed for an overlay vui.             */
#define AR_OPROP_VUI_OVERLAY_CHANGED_FIELD_LIST 60067 /* CHAR; field list (fid1;fid2;..) */

#define AR_OPROP_GRANULAR_OVERLAY_MODE          60068 /* INT; Object property to determine whether the get of an overlay   */
                                                      /* returns the entire object definition or only the portion that     */
                                                      /* is defined in the overlay.  This applies to elements that can     */
                                                      /* be extended (all of which can also be overwritten) -- the get     */
                                                      /* call can return only one list so this property determines whether */
                                                      /* that list is the entire list for the object or only the list of   */
                                                      /* things set in the overlay.                                        */

#define AR_GRANULAR_OVERLAY_FULL_MODE               0 /* Return the final object definition, including both what is       */
                                                      /* defined in the base object and what is defined in the overlay.   */

#define AR_GRANULAR_OVERLAY_ONLY_MODE               1 /* Return only elements that are defined in the overlay itself;  */
                                                      /* the overwritten or extended elements.                         */


#define AR_OPROP_OVERLAY_EXTEND_MASK            60069 /* bitmask */

#define AR_OPROP_OVERLAY_INHERIT_MASK           60070 /* bitmask */

/* the following bits are defined for the AR_OPROP_OVERLAY_EXTEND_MASK and AR_OPROP_OVERLAY_INHERIT_MASK bit masks */
#define AR_GRANULAR_UNSET            0
#define AR_GRANULAR_PERMISSIONS      1
#define AR_GRANULAR_FORM_LIST        2
#define AR_GRANULAR_INDEX            4
#define AR_GRANULAR_OTHER            8

#define AR_GRANULAR_ACTLINK_SHELL    (AR_GRANULAR_PERMISSIONS | AR_GRANULAR_FORM_LIST | AR_GRANULAR_OTHER)
#define AR_GRANULAR_FIELD_SHELL      (AR_GRANULAR_PERMISSIONS | AR_GRANULAR_OTHER)
#define AR_GRANULAR_FILTER_SHELL     (AR_GRANULAR_FORM_LIST | AR_GRANULAR_OTHER)
#define AR_GRANULAR_ESCALATION_SHELL (AR_GRANULAR_FORM_LIST | AR_GRANULAR_OTHER)
#define AR_GRANULAR_SCHEMA_SHELL     (AR_GRANULAR_PERMISSIONS | AR_GRANULAR_INDEX | AR_GRANULAR_OTHER)

#define AR_GRANULAR_RESERVE1    (1 << 31)      /* reserved for internal use */
#define AR_GRANULAR_RESERVE2    (1 << 30)      /* reserved for internal use */

/* Server-managed Object properties (SMOPROP)                            */
/*   90000..119999  reserved for object properties for AR System         */
/*   These properties will be managed exclusively by the server          */
/*                                                                       */
/*      NAME                    VALUE    TYPE; DEFAULT; COMMENT          */
/*                                                                       */
/*     *** ONLY PROPERTIES DOCUMENTED IN MANUAL ARE SUPPORTED ***        */
#define AR_SMOPROP_MIN                          90000
#define AR_SMOPROP_MAX                         119999

#define AR_SMOPROP_NONE                         90000
#define AR_SMOPROP_OBJECT_VERSION               90001
#define AR_SMOPROP_APP_OWNER                    90002
#define AR_SMOPROP_OBJECT_LOCK_TYPE             90003 /* INT; object lock type   */
                                                      /*      AR_LOCK_*          */
#define AR_SMOPROP_OBJECT_LOCK_KEY              90004 /* CHAR; object lock key   */
#define AR_SMOPROP_ENTRYPOINT_DEFAULT_NEW_ORDER    90005 /* INT; entry point order    */
                                                         /*   within entry point list */
#define AR_SMOPROP_ENTRYPOINT_DEFAULT_SEARCH_ORDER 90006 /* INT; entry point order    */
                                                         /*   within entry point list */
#define AR_SMOPROP_NO_APP_STATS_LOGGING         90007 /* INT; does not participate in app stats */

/* Properties for Application Licensing */
#define AR_SMOPROP_APP_LIC_VERSION              90008
#define AR_SMOPROP_APP_LIC_DESCRIPTOR           90009
#define AR_SMOPROP_APP_LIC_USER_LICENSABLE      90010
#define AR_SMOPROP_APP_ACCESS_POINT             90011 /* INT; 0 = not application access point */
                                                      /*      1 = application access point */

/* Property for forms with BSM tag */
#define AR_SMOPROP_APP_BSM_TAG                  90012

/* Property used to get unique field combination on import of form data. */
/* This property will only be used for forms that are tagged as data definition forms */
/* i.e. has fields 61000(Group/Role field), 61001(Application field) and 112(Assignee group field) */
#define AR_SMOPROP_PRIMARY_FIELDSET             90013 /* CHAR; field list (fid1;fid2;..) */

/* Property for filters that should get data as the user that caused them to run */
#define AR_SMOPROP_FILTER_GET_DATA_AS_USER        90014 /* enum; get data using user permissions */
#define AR_FILTER_GET_DATA_AS_ADMIN                 0
#define AR_FILTER_GET_DATA_AS_USER                  1

/* Property of every object for overlay property */
#define AR_SMOPROP_OVERLAY_PROPERTY        90015 /* INT */
/* Property of every object for overlay group */
#define AR_SMOPROP_OVERLAY_GROUP        90016 /* CHAR */



/* see ARFieldValueOrArithStruct above for tag defines -- */
/*   AR_FIELD and AR_STAT_HISTORY                         */

#define AR_CURRENT_SERVER_TAG    "@" /* set server to this to indicate use */
                                     /*  "current" server (import/filter)  */
#define AR_CURRENT_SCHEMA_TAG    "@" /* set schema to this to indicate use */
                                     /*  "current" schema in db (filter)   */
#define AR_CURRENT_SCREEN_TAG    "*" /* set server and schema name to this */
#define AR_CURRENT_TRAN_TAG      "*" /*  tag to indicate get value from    */
                                     /*  "current working screen" not DB   */
#define AR_REP_SCHEMA_TAG        "&" /* set schema to this indicating real */
                                     /* schema name is from field          */
                                     /* AR_RESERV_SETFIELD_SCHEMA_NAME     */

#define AR_NO_MATCH_ERROR         1  /* codes for action if no match */
#define AR_NO_MATCH_SET_NULL      2  /* only if Set Fields action;  if set */
                                     /*    in Push Fields, ERROR           */
#define AR_NO_MATCH_NO_ACTION     3  /* only if Push Fields action; if set */
                                     /*    in Set Fields, ERROR            */
#define AR_NO_MATCH_SUBMIT        4  /* only if Push Fields action; if set */
                                     /*    in Set Fields, ERROR            */

#define AR_MULTI_MATCH_ERROR      1  /* codes for action if 2+ matches        */
#define AR_MULTI_MATCH_SET_NULL   2  /* only if Set Fields action; if set     */
                                     /*    in Push Fields, ERROR              */
#define AR_MULTI_MATCH_USE_FIRST  3
#define AR_MULTI_MATCH_PICKLIST   4  /* only if active link; if set in filter */
                                     /*  or escalation, USE_FIRST             */
#define AR_MULTI_MATCH_MODIFY_ALL 5  /* only if Push Fields action; if set    */
                                     /*    in Set Fields, ERROR               */
#define AR_MULTI_MATCH_NO_ACTION  6  /* only if Push Fields action; if set    */
                                     /*    in Set Fields, ERROR               */
#define AR_MULTI_MATCH_USE_LOCALE 7  /* Use First Matching Request based on   */
                                     /* Locale; if set in Push Fields, ERROR  */

   /* NOTE: When used with filters, the server setting MUST be one of the */
   /*   above settings.  The values for filters can only be pulled from   */
   /*   the current server or the current "screen" (current operation).   */

typedef struct ARAssignFieldStruct
{
   char               server[AR_MAX_SERVER_SIZE + 1];
   ARNameType         schema;
   ARQualifierStruct  qualifier;
   unsigned int       tag;  /* AR_FIELD, AR_STAT_HISTORY, etc */
   union
   {
      size_t                noval_;
      ARInternalId          fieldId;
      ARStatHistoryValue    statHistory;
      ARCurrencyPartStruct *currencyField;
   } u;
   unsigned int       noMatchOption;   /* action if no match */
   unsigned int       multiMatchOption;/* action if 2+ matches */

}  ARAssignFieldStruct;

#define AR_DDE_EXECUTE   1       /* first two used only with   */
#define AR_DDE_POKE      2       /*   ARActiveLinkActionStruct */
#define AR_DDE_REQUEST   3       /* used only with ARAssignStruct */

typedef struct ARDDEStruct
{
   char         *serviceName;
   char         *topic;
   char         *item;         /* NULL if EXECUTE */
   unsigned int  action;
   char         *pathToProgram;
   char         *command;      /* NULL if REQUEST */

}  ARDDEStruct;

typedef struct ARAssignSQLStruct
{
   char          server[AR_MAX_SERVER_SIZE + 1];
   char         *sqlCommand;      /* SQL command to execute */
   unsigned int  valueIndex;      /* index of value in sql cmd */
   unsigned int  noMatchOption;   /* action if no match */
   unsigned int  multiMatchOption;/* action if 2+ matches */

}  ARAssignSQLStruct;

                           /* For a parameter, it's simply a value */
#define AR_COM_PARM_NULL      0  /* invalid parameter value        */
#define AR_COM_PARM_FIELDID   1  /* a fieldId                      */
#define AR_COM_PARM_VALUE     2  /* value of ARValueStruct type    */
                                 /* Note that value is ALWAYS a string, */
                                 /* its true value type is specified in */
                                 /* parmType, a COM VARIANT type        */

                           /* For a method, it's a return value */
#define AR_COM_METHOD_NULL    0  /* invalid value               */
#define AR_COM_METHOD_FIELDID 1  /* value of fieldId            */

                           /* This ARCOMValueStruct applies for COM method/parm  */
typedef struct ARCOMValueStruct
{
   char                  *valueIId;
   ARInternalId           transId;
   AR_XDR_STRUCT_PAD32(noval_)
   unsigned int           valueType;
   union
   {
      ARInternalId        fieldId;
      ARValueStruct       value;
   } u;

}  ARCOMValueStruct;


typedef struct ARCOMMethodParmStruct
{
   char                  *parmName;      /* not null */
   unsigned int           parmType;
   ARCOMValueStruct       parmValue;

}  ARCOMMethodParmStruct;


typedef struct ARCOMMethodParmList
{
   unsigned int           numItems;
   ARCOMMethodParmStruct *parameterList;

}  ARCOMMethodParmList;       /* list of parameters in a COM method*/


typedef struct ARCOMMethodStruct
{
   char                  *methodName;
   char                  *methodIId;
   unsigned int           methodType;
   ARCOMValueStruct       methodValue;
   ARCOMMethodParmList    parameterList;

}  ARCOMMethodStruct;


typedef struct ARCOMMethodList
{
   unsigned int           numItems;
   ARCOMMethodStruct     *methodList;

}  ARCOMMethodList;           /* list of 0 or more methods */


typedef struct ARAutomationStruct
{
   char                  *autoServerName;
   char                  *clsId;
   char                  *action;
   ARBoolean              isVisible; /* showing auto. server? */
   ARCOMMethodList        methodList;

}  ARAutomationStruct;


#define AR_ASSIGN_SQL_SCHEMA_NAME   "_SQL_"   /* schema name used in AssignLoad... function */
                                              /* to indicate that the assignType is SQL.    */
#define AR_ASSIGN_TYPE_NONE       0
#define AR_ASSIGN_TYPE_VALUE      1  /* codes for the assign type to a field */
#define AR_ASSIGN_TYPE_FIELD      2
#define AR_ASSIGN_TYPE_PROCESS    3
#define AR_ASSIGN_TYPE_ARITH      4
#define AR_ASSIGN_TYPE_FUNCTION   5
#define AR_ASSIGN_TYPE_DDE        6  /* used only in active links */
#define AR_ASSIGN_TYPE_SQL        7
#define AR_ASSIGN_TYPE_FILTER_API 8  /* used only in filters/escalations */

typedef struct ARAssignStruct
{
   unsigned int assignType;
   union
   {
      size_t                            noval_;
      ARValueStruct                     value;
      ARAssignFieldStruct              *field;
      char                             *process;
      struct ARArithOpAssignStruct     *arithOp;
      struct ARFunctionAssignStruct    *function;
      ARDDEStruct                      *dde;
      ARAssignSQLStruct                *sql;
      struct ARAssignFilterApiStruct   *filterApi;
   } u;

}  ARAssignStruct;


typedef struct ARAssignFilterApiStruct
{
   ARNameType      serviceName;
   /* assert ALIGN(this.numItems)>=ALIGN_NEEDED_BY(ARAssignStruct *) */
   unsigned int    numItems;
   ARAssignStruct *inputValues;
   unsigned int    valueIndex; /* index of val in returned data*/

}  ARAssignFilterApiStruct;


typedef struct ARFieldAssignStruct
{               /* id and assignment for a single field */
   ARInternalId   fieldId;
   ARAssignStruct assignment;

}  ARFieldAssignStruct;


typedef struct ARFieldAssignList
{               /* list of 0 or more field/value assign pairs */
   unsigned int         numItems;
   ARFieldAssignStruct *fieldAssignList;

}  ARFieldAssignList;

/* see ARArithOpStruct above for the AR_ARITH_OP defines */
typedef struct ARArithOpAssignStruct
{
   unsigned int    operation;
   ARAssignStruct  operandLeft;
   ARAssignStruct  operandRight;

}  ARArithOpAssignStruct;

                                   /* Return   Parameters    Description      */
#define AR_FUNCTION_DATE       1   /* char date(timestamp)   Date part of time*/
#define AR_FUNCTION_TIME       2   /* char time(timestamp)   Time part of time*/
#define AR_FUNCTION_MONTH      3   /* long month(timestamp)  Month (1 to 12)  */
#define AR_FUNCTION_DAY        4   /* long day(timestamp)    Day (1 to 31)    */
#define AR_FUNCTION_YEAR       5   /* long year(timestamp)   Year             */
#define AR_FUNCTION_WEEKDAY    6   /* long weekday(timestamp)Weekday (1 to 7) */
#define AR_FUNCTION_HOUR       7   /* long hour(timestamp)   Hour (0 to 23)   */
#define AR_FUNCTION_MINUTE     8   /* long minute(timestamp) Minute (0 to 59) */
#define AR_FUNCTION_SECOND     9   /* long second(timestamp) Second (0 to 59) */
#define AR_FUNCTION_TRUNC     10   /* long trunc(real)       Truncate real    */
#define AR_FUNCTION_ROUND     11   /* long round(real)       Round real       */
#define AR_FUNCTION_CONVERT   12   /* char convert(???,long[,long])  Convert  */
                                   /*            ??? to type with code long1  */
                                   /*            with format qualifer long2   */
#define AR_FUNCTION_LENGTH    13   /* long length(char)      Length of string */
#define AR_FUNCTION_UPPER     14   /* char upper(char)       Upshift string   */
#define AR_FUNCTION_LOWER     15   /* char lower(char)       Downshift string */
#define AR_FUNCTION_SUBSTR    16   /* char substr(char,long[,long]) Substring */
                                   /*            in char starting at long1,   */
                                   /*            ending at long2, inclusive   */
#define AR_FUNCTION_LEFT      17   /* char left(char,long)   Leftmost x bytes */
#define AR_FUNCTION_RIGHT     18   /* char right(char,long)  Rightmost x bytes*/
#define AR_FUNCTION_LTRIM     19   /* char ltrim(char)       Trim blanks left */
#define AR_FUNCTION_RTRIM     20   /* char rtrim(char)       Trim blanks right*/
#define AR_FUNCTION_LPAD      21   /* char lpad(char,long,char)  Pad char1 on */
                                   /*            left with char2 to long      */
#define AR_FUNCTION_RPAD      22   /* char rpad(char,long,char)  Pad char1 on */
                                   /*            right with char2 to long     */
#define AR_FUNCTION_REPLACE   23   /* char replace(char,char,char)  Replace   */
                                   /*            char2 with char3 in char1    */
#define AR_FUNCTION_STRSTR    24   /* int  strstr(char,char)  Position of     */
                                   /*            char2 in char 1 (-1 not in)  */
#define AR_FUNCTION_MIN       25   /* ???  min(???,???[,???]...)  Min value   */
#define AR_FUNCTION_MAX       26   /* ???  max(???,???[,???]...)  Max value   */

#define AR_FUNCTION_COLSUM    27   /* ???  colsum(column) sum of values       */
#define AR_FUNCTION_COLCOUNT  28   /* int  colcount(column) number of non-null*/
                                   /*            values                       */
#define AR_FUNCTION_COLAVG    29   /* ???  colavg(column) average of non-null */
                                   /*            values                       */
#define AR_FUNCTION_COLMIN    30   /* ???  colmin(column) minimum value       */
#define AR_FUNCTION_COLMAX    31   /* ???  colmax(column) maximum value       */
#define AR_FUNCTION_DATEADD   32   /* date dateadd(char,int,date)             */
#define AR_FUNCTION_DATEDIFF  33   /* int  datediff(char,date,date)           */
#define AR_FUNCTION_DATENAME  34   /* char datename(char,date)                */
#define AR_FUNCTION_DATENUM   35   /* int  datenum(char,date)                 */
#define AR_FUNCTION_CURRCONVERT  36
#define AR_FUNCTION_CURRSETDATE  37
#define AR_FUNCTION_CURRSETTYPE  38
#define AR_FUNCTION_CURRSETVALUE 39
#define AR_FUNCTION_LENGTHC    40  /* long lengthc(char)      Length of string  - in Characters */
#define AR_FUNCTION_LEFTC      41  /* char leftc(char,long)   Leftmost x Characters */
#define AR_FUNCTION_RIGHTC     42  /* char rightc(char,long)  Rightmost x Characters */
#define AR_FUNCTION_LPADC      43  /* char lpadc(char,long,char)  Pad char1 on */
                                   /*            left with char2 to long      */
#define AR_FUNCTION_RPADC      44  /* char rpadc(char,long,char)  Pad char1 on*/
                                   /*            right with char2 to long     */
#define AR_FUNCTION_STRSTRC    45  /* int  strstrc(char,char)  Position of    */
                                   /*            char2 in char 1 (-1 not in)  */
#define AR_FUNCTION_SUBSTRC    46  /* char substrc(char,long[,long]) Substring*/
                                   /*            in char starting at long1,   */
                                   /*            ending at long2, inclusive   */

#define AR_FUNCTION_ENCRYPT    47  /* char encrypt(char, char) Encrypt string */
                                   /*            with password.               */

#define AR_FUNCTION_DECRYPT    48  /* char decrypt(char, char) Decrypt string */
                                   /*            with password.               */
#define AR_FUNCTION_HOVER      49  /* char hover(int/field)                   */
                                   /* input is column and returns char value. */
#define AR_FUNCTION_TEMPLATE   50  /* char template(char/field,value,value,...) */
                                   /* vararg:                                 */
                                   /* arg1: template name, char or field      */
                                   /* arg2*: param value mapping, value       */
#define AR_FUNCTION_SELECTEDROWCOUNT 51  /* int selectrowcount(field)         */
#define AR_FUNCTION_DROPPEDROWINDEX  52  /* int droppedrowindex(field)        */
#define AR_FUNCTION_DROPPEDCOLUMNINDEX  53  /* int droppedcolumnindex(field)        */
#define AR_FUNCTION_MAPGET     54  /* mapget(field,char)                      */
#define AR_FUNCTION_LISTGET    55  /* listget(field,int)                      */
#define AR_FUNCTION_LISTSIZE   56  /* listsize(field)                         */
#define AR_FUNCTION_STRIPHTML  57  /* char stripHtml(char)-strip HTML encoding */
#define AR_FUNCTION_VISIBLEROWS  58  /* VisibleRows(int)                      */
#define AR_MAX_FUNCTION_USED   58  /* set to code for "highest" function      */

typedef struct ARFunctionAssignStruct
{
   unsigned int    functionCode;
   AR_XDR_STRUCT_PAD32(noval_)
   unsigned int    numItems;
   ARAssignStruct *parameterList;

}  ARFunctionAssignStruct;


#define AR_ORDER_MAX          1000 /* max value allowed as filter/active link */
                                   /*  order value                            */

#define AR_OPERATION_NONE              0
#define AR_OPERATION_GET               1 /* tags for operations being performed  */
#define AR_OPERATION_SET               2 /*  ORed together to form mask for mask */
#define AR_OPERATION_CREATE            4 /*  of operations to apply filter on    */
#define AR_OPERATION_DELETE            8
#define AR_OPERATION_MERGE            16
#define AR_OPERATION_GUIDE            32
#define AR_OPERATION_SERVICE          64

#define AR_NOTIFY_BEHAVIOR_SEND_MULTIPLE        0

#define AR_NOTIFY_PERMISSION_DEFAULT            0

typedef struct ARFilterActionNotifyAdvanced
{
   char           *from;
   char           *replyTo;
   char           *cc;
   char           *bcc;
   char           *organization;
   char           *mailboxName;
   char           *headerTemplate;
   char           *footerTemplate;
   char           *contentTemplate;
   ARULong32       reserved1;
   ARULong32       reserved2;
   ARULong32       reserved3;

}  ARFilterActionNotifyAdvanced;

#define AR_NOTIFY_NONE           0
#define AR_NOTIFY_VIA_NOTIFIER   1 /* tags for notify mechanism */
#define AR_NOTIFY_VIA_EMAIL      2
#define AR_NOTIFY_VIA_DEFAULT    3

#define AR_NOTIFY_VIA_XREF      99 /* tag to indicate look at a specified    */
                                   /*  field cross-reference for notify mech */

#define AR_NOTIFY_PRIORITY_MAX  10 /* maximum notify priority */

#define AR_FILTER_FIELD_IDS_NONE    0
#define AR_FILTER_FIELD_IDS_ALL     1 /* tags for which field ids for notify */
#define AR_FILTER_FIELD_IDS_LIST    2
#define AR_FILTER_FIELD_IDS_CHANGED 3

typedef struct ARFilterActionNotify
{
   char              *user;
   char              *notifyText;
   unsigned int       notifyPriority;
   unsigned int       notifyMechanism;
   ARInternalId       notifyMechanismXRef;/*if AR_NOTIFY_VIA_XREF*/
   char              *subjectText;
   unsigned int       fieldIdListType;
   ARInternalIdList   fieldIdList; /* unused if NONE/ALL fields */
   unsigned int       notifyBehavior;
   unsigned int       notifyPermission;
   ARFilterActionNotifyAdvanced   *notifyAdvanced;

}  ARFilterActionNotify;


typedef struct ARFilterStatusStruct
{               /* type of error (see return values) */
   unsigned int  messageType;
   ARLong32      messageNum;
   char         *messageText;

}  ARFilterStatusStruct;


typedef struct ARPushFieldsStruct
{
   ARAssignFieldStruct   field;   /* target of push */
   ARAssignStruct        assign;  /* value assigned to target */

}  ARPushFieldsStruct;


typedef struct ARPushFieldsList
{           /* list of 0 or more push fields */
   unsigned int         numItems;
   ARPushFieldsStruct  *pushFieldsList;

}  ARPushFieldsList;


typedef struct ARPushFieldsActionStruct
{
   ARPushFieldsList   pushFieldsList;
   ARServerNameType   sampleServer;
   ARNameType         sampleSchema;

}  ARPushFieldsActionStruct;


typedef struct ARSetFieldsActionStruct
{
   ARFieldAssignList   fieldList;
   ARServerNameType    sampleServer;
   ARNameType          sampleSchema;

}  ARSetFieldsActionStruct;

typedef struct ARSQLStruct
{
   char   server[AR_MAX_SERVER_SIZE + 1];
   char  *command;

}  ARSQLStruct;

typedef struct AROverlaidStruct
{
   ARNameType     name;       /* name of overlaid object */               
   unsigned int   objType;    /* type of overlaid object ESCALATION, FILTER, VIEW etc. */
   ARNameType     schemaName; /* schema name of overlaid object. Applicable for Field, View */
   ARInternalId   id;         /* ID of overlaid object. Applicable for Field, View */
   unsigned int   inheritMask;
   unsigned int   extendMask;
}  AROverlaidStruct;


#define AR_GOTO_FIELD_XREF          1
#define AR_GOTO_ABSOLUTE_ORDER      2
#define AR_GOTO_OFFSET_FORWARD      3
#define AR_GOTO_OFFSET_BACKWARD     4

typedef struct ARGotoActionStruct
{
   unsigned int    tag;
   ARULong32       fieldIdOrValue;

}  ARGotoActionStruct;


typedef struct ARCallGuideStruct
{
   ARServerNameType    serverName;
   ARNameType          guideName;
   int                 guideMode;
   ARInternalId        guideTableId;
   ARFieldAssignList   inputValueFieldPairs;
   ARFieldAssignList   outputValueFieldPairs;
   ARServerNameType    sampleServer;
   ARNameType          sampleGuide;

}  ARCallGuideStruct;

#define AR_CALL_GUIDE_FORM_HIDDEN         1  /* mask for guideMode, form  */
                                             /*  will open in hidden mode */
#define AR_CALL_GUIDE_LOOP_SELECTED_ONLY  2  /* mask for guideMode, table */
                                             /*  loop guide will loop on  */
                                             /*  selected rows only       */
#define AR_CALL_GUIDE_LOOP_ALL_ROWS_VISIBLE  4  /* mask for guideMode, table */
                                             /*  loop guide will loop on  */
                                             /*  visible rows only        */
#define AR_CALL_GUIDE_MODE_MAX  7            /* 0<=valid value<=this */

typedef struct ARExitGuideStruct
{
   ARBoolean   closeAll;

}  ARExitGuideStruct;

typedef struct ARGotoGuideLabelStruct
{
   char  *label;

}  ARGotoGuideLabelStruct;

typedef struct ARSvcActionStruct
{
   ARServerNameType        serverName;
   ARNameType              serviceSchema;
   ARInternalId            requestIdMap;
   ARFieldAssignList       inputFieldMapping;
   ARFieldAssignList       outputFieldMapping;
   ARServerNameType        sampleServer;
   ARNameType              sampleSchema;
}  ARSvcActionStruct;

                                    /* tags for types of filter actions */
#define AR_FILTER_ACTION_NONE             0
#define AR_FILTER_ACTION_NOTIFY           1
#define AR_FILTER_ACTION_MESSAGE          2
#define AR_FILTER_ACTION_LOG              3
#define AR_FILTER_ACTION_FIELDS           4
#define AR_FILTER_ACTION_PROCESS          5
#define AR_FILTER_ACTION_FIELDP           6
#define AR_FILTER_ACTION_SQL              7
#define AR_FILTER_ACTION_GOTOACTION       8
#define AR_FILTER_ACTION_CALLGUIDE        9
#define AR_FILTER_ACTION_EXITGUIDE       10
#define AR_FILTER_ACTION_GOTOGUIDELABEL  11
#define AR_FILTER_ACTION_SERVICE         12
#define AR_FILTER_LAST_ACTION            AR_FILTER_ACTION_SERVICE

#define AR_ERRHANDLER_ENABLE 0x0001

typedef struct ARFilterActionStruct
{
   unsigned int  action;
   union
   {
      ARFilterActionNotify       notify;
      ARFilterStatusStruct       message;
      char                      *logFile;
      ARSetFieldsActionStruct    setFields;
      char                      *process;
      ARPushFieldsActionStruct   pushFields;
      ARSQLStruct                sqlCommand;
      ARGotoActionStruct         gotoAction;
      ARCallGuideStruct          callGuide;
      ARExitGuideStruct          exitGuide;
      ARGotoGuideLabelStruct     gotoGuide;
      ARSvcActionStruct          serviceAction;
   } u;

}  ARFilterActionStruct;

typedef struct ARFilterActionList
{               /* list of 0 or more filter actions */
   unsigned int           numItems;
   ARFilterActionStruct  *actionList;

}  ARFilterActionList;


typedef struct ARFilterActionListList
{               /* list of 0 or more filter actions */
   unsigned int         numItems;
   ARFilterActionList  *actionListList;

}  ARFilterActionListList;

/* Tags for when to execute an active link. These can be ORed together */
/* to form mask of conditions to execute active link on.               */
#define AR_EXECUTE_ON_NONE                   0
#define AR_EXECUTE_ON_BUTTON                 (1 << 0)
#define AR_EXECUTE_ON_RETURN                 (1 << 1)
#define AR_EXECUTE_ON_SUBMIT                 (1 << 2)
#define AR_EXECUTE_ON_MODIFY                 (1 << 3)
#define AR_EXECUTE_ON_DISPLAY                (1 << 4)
#define AR_EXECUTE_ON_MODIFY_ALL             (1 << 5)
#define AR_EXECUTE_ON_MENU_OPEN              (1 << 6)
#define AR_EXECUTE_ON_MENU_CHOICE            (1 << 7)
#define AR_EXECUTE_ON_LOSE_FOCUS             (1 << 8)
#define AR_EXECUTE_ON_SET_DEFAULT            (1 << 9)
#define AR_EXECUTE_ON_QUERY                  (1 << 10)
#define AR_EXECUTE_ON_AFTER_MODIFY           (1 << 11)
#define AR_EXECUTE_ON_AFTER_SUBMIT           (1 << 12)
#define AR_EXECUTE_ON_GAIN_FOCUS             (1 << 13)
#define AR_EXECUTE_ON_WINDOW_OPEN            (1 << 14)
#define AR_EXECUTE_ON_WINDOW_CLOSE           (1 << 15)
#define AR_EXECUTE_ON_UNDISPLAY              (1 << 16)
#define AR_EXECUTE_ON_COPY_SUBMIT            (1 << 17)
#define AR_EXECUTE_ON_LOADED                 (1 << 18)
#define AR_EXECUTE_ON_INTERVAL               (1 << 19)
#define AR_EXECUTE_ON_EVENT                  (1 << 20)
#define AR_EXECUTE_ON_MASK_EXP_V10           ((AR_EXECUTE_ON_EVENT * 2) - 1)

#define AR_EXECUTE_ON_TABLE_CONTENT_CHANGE   (1 << 21)
#define AR_EXECUTE_ON_HOVER_FIELD_LABEL      (1 << 22)
#define AR_EXECUTE_ON_HOVER_FIELD_DATA       (1 << 23)
#define AR_EXECUTE_ON_HOVER_FIELD            (1 << 24)
/*Event handlers used in workflow for page expand/collapse*/
#define AR_EXECUTE_ON_PAGE_EXPAND            (1 << 25)
#define AR_EXECUTE_ON_PAGE_COLLAPSE          (1 << 26)
#define AR_EXECUTE_ON_DRAG                   (1 << 27)
#define AR_EXECUTE_ON_DROP                   (1 << 28)

#define AR_EXECUTE_ON_MASK_MAX               ((AR_EXECUTE_ON_DROP * 2) - 1)

/* possible mask values for the focus field */
#define AR_EXECUTE_ON_MASK_FOCUS_FIELD       (AR_EXECUTE_ON_RETURN | AR_EXECUTE_ON_MENU_CHOICE | AR_EXECUTE_ON_MENU_OPEN | \
                                              AR_EXECUTE_ON_LOSE_FOCUS | AR_EXECUTE_ON_GAIN_FOCUS | AR_EXECUTE_ON_TABLE_CONTENT_CHANGE | \
                                              AR_EXECUTE_ON_HOVER_FIELD_LABEL | AR_EXECUTE_ON_HOVER_FIELD_DATA | AR_EXECUTE_ON_HOVER_FIELD | \
                                              AR_EXECUTE_ON_PAGE_EXPAND | AR_EXECUTE_ON_PAGE_COLLAPSE | \
                                              AR_EXECUTE_ON_DRAG | AR_EXECUTE_ON_DROP)



typedef struct ARMacroParmStruct
{
   ARNameType   name;
   char        *value;

}  ARMacroParmStruct;

typedef struct ARMacroParmList
{
   unsigned int        numItems;
   ARMacroParmStruct  *parms;

}  ARMacroParmList;

typedef struct ARActiveLinkMacroStruct
{
   ARNameType        macroName;
   char             *macroText;
   ARMacroParmList   macroParms;

}  ARActiveLinkMacroStruct;

typedef ARSvcActionStruct ARActiveLinkSvcActionStruct;


#define AR_FIELD_CHAR_OPTION_REFERENCE    1

#define AR_FOCUS_UNCHANGED          0
#define AR_FOCUS_SET_TO_FIELD       1

#define AR_ACCESS_OPTION_UNCHANGED  0
#define AR_ACCESS_OPTION_READ_ONLY  AR_DVAL_ENABLE_READ_ONLY
#define AR_ACCESS_OPTION_READ_WRITE AR_DVAL_ENABLE_READ_WRITE
#define AR_ACCESS_OPTION_DISABLE    AR_DVAL_ENABLE_DISABLE

typedef struct ARFieldCharacteristics
{
   unsigned int   option;
   ARInternalId   fieldId;
   char          *charMenu;
   ARPropList     props;
   unsigned int   focus;
   unsigned int   accessOption;

}  ARFieldCharacteristics;

typedef struct AROpenDlgStruct
{
   ARServerNameType     serverName;
   ARNameType           schemaName;
   ARNameType           vuiLabel;
   ARBoolean            closeBox;
   ARFieldAssignList    inputValueFieldPairs;
   ARFieldAssignList    outputValueFieldPairs;
   int                  windowMode;
   char                *targetLocation;
   ARQualifierStruct    query;
   ARBoolean            noMatchContinue;
   ARBoolean            suppressEmptyLst;
   ARMessageStruct      msg;
   ARULong32            pollinginterval;
   char                *reportString;
   ARSortList           sortOrderList;
}  AROpenDlgStruct;

typedef struct ARCommitChangesStruct
{
   ARNameType   schemaName;

}  ARCommitChangesStruct;

typedef struct ARCloseWndStruct
{
   ARBoolean   closeAll;

}  ARCloseWndStruct;

typedef struct ARWaitStruct
{
   char  *continueButtonTitle;

}  ARWaitStruct;

                                    /* tags for types of active link actions */
#define AR_ACTIVE_LINK_ACTION_NONE            0
#define AR_ACTIVE_LINK_ACTION_MACRO           1
#define AR_ACTIVE_LINK_ACTION_FIELDS          2
#define AR_ACTIVE_LINK_ACTION_PROCESS         3
#define AR_ACTIVE_LINK_ACTION_MESSAGE         4
#define AR_ACTIVE_LINK_ACTION_SET_CHAR        5
#define AR_ACTIVE_LINK_ACTION_DDE             6
#define AR_ACTIVE_LINK_ACTION_FIELDP          7
#define AR_ACTIVE_LINK_ACTION_SQL             8
#define AR_ACTIVE_LINK_ACTION_AUTO            9
#define AR_ACTIVE_LINK_ACTION_OPENDLG        10
#define AR_ACTIVE_LINK_ACTION_COMMITC        11
#define AR_ACTIVE_LINK_ACTION_CLOSEWND       12
#define AR_ACTIVE_LINK_ACTION_CALLGUIDE      13
#define AR_ACTIVE_LINK_ACTION_EXITGUIDE      14
#define AR_ACTIVE_LINK_ACTION_GOTOGUIDELABEL 15
#define AR_ACTIVE_LINK_ACTION_WAIT           16
#define AR_ACTIVE_LINK_ACTION_GOTOACTION     17
#define AR_ACTIVE_LINK_ACTION_SERVICE        18

#define AR_ACTIVE_LINK_ACTION_OPEN_DLG                  0
#define AR_ACTIVE_LINK_ACTION_OPEN_SEARCH               1
#define AR_ACTIVE_LINK_ACTION_OPEN_SUBMIT               2
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_LST           3
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_DETAIL        4
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_SPLIT         5
#define AR_ACTIVE_LINK_ACTION_OPEN_DSPLY_LST            6
#define AR_ACTIVE_LINK_ACTION_OPEN_DSPLY_DETAIL         7
#define AR_ACTIVE_LINK_ACTION_OPEN_DSPLY_SPLIT          8
#define AR_ACTIVE_LINK_ACTION_OPEN_REPORT               9
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY               10
#define AR_ACTIVE_LINK_ACTION_OPEN_DSPLY                11
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_DIRECT        12  /*Active link Open Window*/
                                                       /*action open window in modify mode*/
                                                       /*skipping all workflows except for*/
                                                       /*window open and window display workflow.*/
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_DIRECT_LST    13
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_DIRECT_DETAIL 14
#define AR_ACTIVE_LINK_ACTION_OPEN_MODIFY_DIRECT_SPLIT  15

#define AR_ACTIVE_LINK_ACTION_OPEN_DISPLAY_DIRECT        16
#define AR_ACTIVE_LINK_ACTION_OPEN_DISPLAY_DIRECT_LST    17
#define AR_ACTIVE_LINK_ACTION_OPEN_DISPLAY_DIRECT_DETAIL 18
#define AR_ACTIVE_LINK_ACTION_OPEN_DISPLAY_DIRECT_SPLIT  19
#define AR_ACTIVE_LINK_ACTION_OPEN_POPUP                 20

                                    /* Tags for ActiveLink OpenWindow's  */
                                    /* reportString or macro's macroText.*/
                                    /* ARL(x) in <artypes.h> */
#define AR_REPORT_ATTR_LAYOUT           ARL(1) /* report layout (record/col...*/
#define AR_REPORT_ATTR_IDLIST           ARL(2) /* field IDs included in report*/
#define AR_REPORT_ATTR_NAME             ARL(3)  /* name of the report */
#define AR_REPORT_ATTR_TITLE            ARL(4)  /* title on first page */
#define AR_REPORT_ATTR_HEADER           ARL(5)  /* header on every page */
#define AR_REPORT_ATTR_FOOTER           ARL(6)  /* footer on every page */
#define AR_REPORT_ATTR_LINES            ARL(7)  /* lines per page */
#define AR_REPORT_ATTR_TOP              ARL(8)  /* lines in top margin */
#define AR_REPORT_ATTR_BOTTOM           ARL(9)  /* lines in bottom margin */
#define AR_REPORT_ATTR_CHARS            ARL(10) /* characters per line */
#define AR_REPORT_ATTR_LEFT             ARL(11) /* characters in left margin */
#define AR_REPORT_ATTR_RIGHT            ARL(12) /* characters in right margin */
#define AR_REPORT_ATTR_COL_SEP          ARL(13) /* column separator string */
#define AR_REPORT_ATTR_ONE_REC_PER_PAGE ARL(14) /*PC 1.1.5 -- page breaks per */
#define AR_REPORT_ATTR_COMPRESSED       ARL(15) /*compresses text format type */
#define AR_REPORT_ATTR_TITLE_SEP_CHAR   ARL(16) /* column title separator */
#define AR_REPORT_REC_SEP               ARL(17) /* record separator */
#define AR_REPORT_LONG_FIELD_FORMAT     ARL(18) /*long fieldformat(wrap/trunc)*/
#define AR_REPORT_COL_TITLE_PER         ARL(19) /* column titles per */
#define AR_REPORT_ATTR_PAGE_BREAKS      ARL(20) /* page breaks per */
#define AR_REPORT_ATTR_TYPE             ARL(21) /* type of report */
#define AR_REPORT_ATTR_FILENAME         ARL(22) /*filename for external report*/
#define AR_REPORT_ATTR_PRINT_ORIENT     ARL(23) /* print orientation */
#define AR_REPORT_ATTR_SCHEMANAME       ARL(24) /* schema report is against */
#define AR_REPORT_ATTR_SERVERNAME       ARL(25) /* server schema is on */
#define AR_REPORT_ATTR_QUERY            ARL(26) /* backup query */
#define AR_REPORT_ATTR_ENTRYIDS         ARL(27)
#define AR_REPORT_ATTR_QUERY_OVERRIDE   ARL(28) /* allow query override? */
#define AR_REPORT_ATTR_OPERATION        ARL(29)
#define AR_REPORT_ATTR_LOCATION         ARL(30) /* location of report definition*/
#define AR_REPORT_ATTR_CHAR_ENCODING    ARL(31) /* character encoding */
#define AR_REPORT_ATTR_INLINE_FORM      ARL(32) /* rendering mode - inline */

#define AR_REPORT_LOCATION_EMBEDDED          0    /* stored on AR Server */
#define AR_REPORT_LOCATION_LOCAL             1    /* stored on local disc */
#define AR_REPORT_LOCATION_REPORTING_FORM    2    /* stored in reporting form */
#define AR_REPORT_LOCATION_FIELD             3    /* stored in a field on form*/

typedef struct ARActiveLinkActionStruct
{
   unsigned int  action;
   union
   {
      ARActiveLinkMacroStruct  macro;
      ARSetFieldsActionStruct  setFields;
      char                    *process;
      ARMessageStruct          message;
      ARFieldCharacteristics   characteristics;
      ARDDEStruct              dde;
      ARPushFieldsActionStruct pushFields;
      ARSQLStruct              sqlCommand;
      ARAutomationStruct       automation;
      AROpenDlgStruct          openDlg;
      ARCommitChangesStruct    commitChanges;
      ARCloseWndStruct         closeWnd;
      ARCallGuideStruct        callGuide;
      ARExitGuideStruct        exitGuide;
      ARGotoGuideLabelStruct   gotoGuide;
      ARWaitStruct             waitAction;
      ARGotoActionStruct       gotoAction;
      ARActiveLinkSvcActionStruct service;
   } u;

}  ARActiveLinkActionStruct;

typedef struct ARActiveLinkActionList
{               /* list of 0 or more active link actions */
   unsigned int               numItems;
   ARActiveLinkActionStruct  *actionList;

}  ARActiveLinkActionList;


typedef struct ARActiveLinkActionListList
{               /* list of 0 or more active link action list */
   unsigned int             numItems;
   ARActiveLinkActionList  *actionListList;

}  ARActiveLinkActionListList;

#define AR_PERMISSIONS_NONE      0 /* tags for permissions allowed to group */

#define AR_PERMISSIONS_VISIBLE   1 /* tags for schema level permissions */
#define AR_PERMISSIONS_HIDDEN    2

#define AR_PERMISSIONS_VIEW      1 /* tags for field level permissions */
#define AR_PERMISSIONS_CHANGE    2 /* note that change includes view */

typedef struct ARPermissionStruct
{               /* a group and the permissions defined */
   ARInternalId   groupId;
   unsigned int   permissions;

}  ARPermissionStruct;

typedef struct ARPermissionList
{               /* list of 0 or more permission entries */
   unsigned int         numItems;
   ARPermissionStruct  *permissionList;

}  ARPermissionList;

typedef struct ARPermissionListList
{               /* list of 0 or more permission lists */
   unsigned int       numItems;
   ARPermissionList  *permissionList;

}  ARPermissionListList;

typedef struct ARPermissionListPtrList
{               /* list of 0 or more permission list pointers */
   unsigned int       numItems;
   ARPermissionList **permissionListPtrList;

}  ARPermissionListPtrList;

#define AR_GROUP_TYPE_NONE           0 /* tag for no group type --> needed in mid-tier */
#define AR_GROUP_TYPE_VIEW           1 /* tags for types of groups */
#define AR_GROUP_TYPE_CHANGE         2

#define AR_GROUP_CATEGORY_REGULAR    0 /* tags for group categories */
#define AR_GROUP_CATEGORY_DYNAMIC    1
#define AR_GROUP_CATEGORY_COMPUTED   2

#define AR_GROUP_PARENT_NONE         0 /* this group has no parent */

                               /* holds information about groups used with */
                               /*  field permissions                       */
typedef struct ARGroupInfoStruct
{
   ARInternalId       groupId;
   unsigned int       groupType;
   ARAccessNameList   groupName;
   unsigned int       groupCategory;
   ARInternalId       groupParent;     /* parent of this group (may be none) */
   unsigned int       groupOverlay;    /* see AR_OVERLAY_GROUP_TAG_NULL &c. */
} ARGroupInfoStruct;

typedef struct ARGroupInfoList
{               /* list of 0 or more groups */
   unsigned int        numItems;
   ARGroupInfoStruct  *groupList;

}  ARGroupInfoList;


typedef struct ARRoleInfoStruct
{
   int          roleId;
   ARNameType   roleName;
   int          roleType;

}  ARRoleInfoStruct;


typedef struct ARRoleInfoList
{               /* list of 0 or more groups */
   unsigned int       numItems;
   ARRoleInfoStruct  *roleList;

}  ARRoleInfoList;

#define AR_LICENSE_TAG_WRITE       1  /* codes for licenses that could be */
#define AR_LICENSE_TAG_FULL_TEXT   2  /*  held by a user                  */
#define AR_LICENSE_TAG_RESERVED1   3
#define AR_LICENSE_TAG_APP         4

#define AR_LICENSE_TAG_WRITE_INDEX  0
#define AR_LICENSE_TAG_RESV_INDEX   1
#define AR_LICENSE_TAG_NUM_INDEXES  2

typedef struct ARUserLicenseStruct
{               /* holds information about user's licenses */
   unsigned int        licenseTag;
   unsigned int        licenseType;
   unsigned int        currentLicenseType;
   ARInternalId        licensePool;
   ARLicenseNameType   appLicenseDescriptor;
   ARTimestamp         lastAccess;
}  ARUserLicenseStruct;


typedef struct ARUserLicenseList
{               /* list of 0 or more users */
   unsigned int          numItems;
   ARUserLicenseStruct  *licenseList;

}  ARUserLicenseList;

typedef ARUserLicenseStruct   ARAppLicensePoolStruct;
typedef struct ARAppLicensePoolList
{               /* list of 0 or more users */
   unsigned int          numItems;
   ARAppLicensePoolStruct   *appLicenseList;

}  ARAppLicensePoolList;

typedef struct ARLicenseNameList
{               /* list of 0 or more license names */
   unsigned int        numItems;
   ARLicenseNameType  *nameList;

}  ARLicenseNameList;


typedef struct ARLicenseDateStruct
{               /* date structure to use with licensing */
   int   month; /* 0 to 11 with 0 meaning January */
   int   day;   /* 1 to 31 with 0 meaning 1st */
   int   year;  /* This is the year - 1900. Value is >=  70 */
                /* Jan-01-70 (0-1-70) is the default time.  */
}  ARLicenseDateStruct;


typedef struct ARLicenseInfoStruct
{               /* structure holding details for a license */
   ARLicenseKeyType      licKey;     /* license key */
   ARLicenseNameType     licType;    /* the type of license */
   ARLicenseNameType     licSubtype; /* sub-type of license */
   ARLicenseDateStruct   issuedDate; /* date license issued */
   ARLicenseDateStruct   expireDate; /* date license expires */
   char                 *siteName;   /* Site name. */
   char                 *hostId;     /* host id */
   int                   numLicenses;/* number of licenses */
   char                 *tokenList;  /* more data for the lic */
   char                 *comment;    /* comments */

}  ARLicenseInfoStruct;


typedef struct ARLicenseInfoList
{               /* list of 0 or more license detail items */
   unsigned int          numItems;
   ARLicenseInfoStruct  *licenseInfoList;

}  ARLicenseInfoList;


typedef struct ARLicenseValidStruct
{               /* validation information for a license */
   int                   numLicenses;/* # of active license    */
   ARBoolean             isDemo;     /* True if a demo license */
   ARLicenseDateStruct   expireDate; /* Expiration date */
   char                 *tokenList;

}  ARLicenseValidStruct;


typedef struct ARLicenseValidList
{               /* list of 0 or more license validations */
   unsigned int           numItems;
   ARLicenseValidStruct  *licenseValidateInfoList;

}  ARLicenseValidList;


typedef struct ARHostIDTypeList
{               /* list of 0 or more host id string */
   unsigned int   numItems;
   ARHostIDType  *idList;

}  ARHostIDTypeList;

#define AR_USER_LIST_MYSELF      0 /* tags for type of user list wanted */
#define AR_USER_LIST_REGISTERED  1
#define AR_USER_LIST_CURRENT     2
#define AR_USER_LIST_INVALID     3
#define AR_USER_LIST_APPLICATION 4

typedef struct ARUserInfoStruct
{               /* holds information about users in the system */
   ARAccessNameType    userName;
   ARUserLicenseList   licenseInfo;
   ARTimestamp         connectTime;
   ARTimestamp         lastAccess;
   unsigned int        defaultNotifyMech;
   char               *emailAddr;

}  ARUserInfoStruct;

typedef struct ARUserInfoList
{               /* list of 0 or more users */
   unsigned int       numItems;
   ARUserInfoStruct  *userList;

}  ARUserInfoList;

/* Flag indicates the workflow lock type */

typedef struct ARWorkflowLockStruct
{
   int                lockType; /* bitmask indicating the type of lock */
   ARPasswordType     lockKey;  /* the lock key for the object */

}  ARWorkflowLockStruct;

#define AR_LOCK_TYPE_NONE          0 /* object lock flag is OFF */
#define AR_LOCK_TYPE_READONLY      1 /* flag for locking objects in such a way that */
                                     /*    they can be read but not modified */
#define AR_LOCK_TYPE_HIDDEN        2 /* flag for locking objects in such a way that */
                                     /*    they can neither be read nor modified */
#define AR_LOCK_TYPE_MIN           0 /* minimum for lock level range */
#define AR_LOCK_TYPE_MAX           2 /* maximum for lock level range */

typedef struct ARIntegerLimitsStruct
{
   ARLong32 rangeLow;
   ARLong32 rangeHigh;

}  ARIntegerLimitsStruct;

#define AR_PRECISION_NONE    -1  /* code for no precision setting */

typedef struct ARRealLimitsStruct
{
   double   rangeLow;
   double   rangeHigh;
   int      precision;

}  ARRealLimitsStruct;

#define AR_MENU_APPEND         1 /* code indicating append/overwrite */
#define AR_MENU_OVERWRITE      2 /*  new items dropped from menu     */

                                 /* operation to perform on QBE screen */
#define AR_QBE_MATCH_ANYWHERE  1 /* LIKE "%value%" */
#define AR_QBE_MATCH_LEADING   2 /* LIKE "value%"  */
#define AR_QBE_MATCH_EQUAL     3 /* = "value"      */

                                 /* Full text options */
#define AR_FULLTEXT_OPTIONS_NONE                  0x0  /* No full text options */
#define AR_FULLTEXT_OPTIONS_INDEXED               0x1  /* Field is full text indexed */
#define AR_FULLTEXT_OPTIONS_LITERAL               0x2  /* Literal search option */
#define AR_FULLTEXT_OPTIONS_EXCLUDE_FIELD_BASED   0x4  /* Exclude from field based search */

#define AR_COREFIELD_LENGTH_FACTOR 4 /* always use 4 as length factor for core field */

#define AR_LENGTH_UNIT_BYTE   0x0 /* field length measured in byte */
#define AR_LENGTH_UNIT_CHAR   0x1 /* field length mesuared in char */

#define AR_STORE_OPT_DEF      0x0 /* CLOB Storage Option - Default    */
#define AR_STORE_OPT_INROW    0x1 /* CLOB Storage Option - In-Row     */
#define AR_STORE_OPT_OUTROW   0x2 /* CLOB Storage Option - Out-of-Row */

typedef struct ARCharLimitsStruct
{                                /* 0 for maxLength means unlimited length */
   unsigned int   maxLength;
                                 /* append or overwrite with new menu selections */
   unsigned int   menuStyle;
                                 /* operation to use from QBE type operation */
   unsigned int   qbeMatchOperation;
                                 /* name of character menu associated to field */
   ARNameType     charMenu;
                                 /* pattern, incl wildcards, value must match */
   char          *pattern;
                                 /* Full Text options */
   unsigned int   fullTextOptions;
                                 /* 0 for in-byte, 1 for in-char */   
   unsigned int   lengthUnits;
                                 /* 0 for Default, 1 for In-Row and 2 for Out-of-Row */
   unsigned int   storageOptionForCLOB;
}  ARCharLimitsStruct;

typedef struct ARDiaryLimitsStruct
{
   unsigned int   fullTextOptions;

}  ARDiaryLimitsStruct;

#define AR_ENUM_STYLE_REGULAR  1 /* list auto-indexed starting at 0 */
#define AR_ENUM_STYLE_CUSTOM   2 /* list indexed manually, gaps in numbers OK */
#define AR_ENUM_STYLE_QUERY    3 /* search performed to find name/number pairs*/

typedef struct AREnumItemStruct
{
   ARNameType      itemName;
   ARULong32       itemNumber;

}  AREnumItemStruct;

typedef struct AREnumItemList
{
   unsigned int       numItems;
   AREnumItemStruct  *enumItemList;

}  AREnumItemList;

typedef struct AREnumQueryStruct
{
   ARNameType          schema;
   char                server[AR_MAX_SERVER_SIZE + 1];
   ARQualifierStruct   qualifier;
   ARInternalId        nameField;
   ARInternalId        numberField;

}  AREnumQueryStruct;

typedef struct AREnumLimitsStruct
{
   unsigned int listStyle;
   union
   {
      ARNameList          regularList;
      AREnumItemList      customList;
      AREnumQueryStruct   queryList;
   } u;

}  AREnumLimitsStruct;

#define AR_ATTACH_FIELD_TYPE_EMBED    0x1   /* embedded type; file is stored */
#define AR_ATTACH_FIELD_TYPE_LINK     0x2   /* RESERVED for future use */

typedef struct ARAttachLimitsStruct
{
   ARULong32       maxSize;     /* 0 means unlimited */
   unsigned int    attachType;
   unsigned int    fullTextOptions;

}  ARAttachLimitsStruct;

typedef struct ARTableLimitsStruct
{
                                      /* number of columns in table field */
   unsigned int        numColumns;
                                      /* qualification for table field */
   ARQualifierStruct   qualifier;
                                      /* max rows to retrieve */
   unsigned int        maxRetrieve;
                                      /* data fields belong to this schema */
   ARNameType          schema;
                                      /* that schema is in this server */
   ARServerNameType    server;
   ARNameType          sampleSchema;
   ARServerNameType    sampleServer;

}  ARTableLimitsStruct;

                                    /* data source for the column limits */
#define COLUMN_LIMIT_DATASOURCE_DATA_FIELD         0  /* regular dataField      */
#define COLUMN_LIMIT_DATASOURCE_DISPLAY_FIELD      1  /* display-only dataField */
#define COLUMN_LIMIT_DATASOURCE_CONTROL_FIELD      2  /* local control field e.g. button */
#define COLUMN_LIMIT_DATASOURCE_TRIM_FIELD         3  /* local trim field */
#define COLUMN_LIMIT_DATASOURCE_VIEW_FIELD         4  /* local view field */
#define COLUMN_LIMIT_DATASOURCE_MAX                4  

typedef struct ARColumnLimitsStruct
{
   ARInternalId   parent;
                                    /* parent field column field belongs to */
   ARInternalId   dataField;
                                    /* remote fieldId form which data comes */
   unsigned int   dataSource;
                                    /* data source for the above dataField */
   unsigned int   colLength;
                                    /* column length to display - char fields */
}  ARColumnLimitsStruct;

typedef struct ARDecimalLimitsStruct
{
   char  *rangeLow;
   char  *rangeHigh;
   int    precision; /* number of places to right of dec point */

}  ARDecimalLimitsStruct;

typedef struct ARViewLimits
{
   unsigned int   maxLength;   /* 0 means unlimited length */

}  ARViewLimits;

typedef struct ARDisplayLimits
{
   unsigned int   maxLength;   /* 0 means unlimited length */
   unsigned int   lengthUnits; /* 0 for in-byte, 1 for in-char */   
}  ARDisplayLimits;

typedef struct ARDateLimitsStruct
{
   int   minDate;  /* minimum date value, in julian days */
   int   maxDate;  /* maximum date value, in julian days */

}  ARDateLimitsStruct;

#define AR_MAX_FUNC_CURRENCY_LIMIT_TEXT_SIZE 20      /* this is used when I stringify */
                                                     /* a FuncCurrencyLimit           */

typedef struct ARCurrencyDetailStruct
{
   ARCurrencyCodeType   currencyCode;  /* currency type */
   int                  precision;     /* number of places to right of dec point */

}  ARCurrencyDetailStruct;


typedef struct ARCurrencyDetailList
{
   unsigned int             numItems;
   ARCurrencyDetailStruct  *currencyDetailList;

}  ARCurrencyDetailList;

typedef struct ARCurrencyLimitsStruct
{
   char                  *rangeLow;
   char                  *rangeHigh;
   int                    precision;  /* number of places to */
                                      /*  right of dec point */
   ARCurrencyDetailList   functionalCurrencies;
   ARCurrencyDetailList   allowableCurrencies;

}  ARCurrencyLimitsStruct;

#define AR_FIELD_LIMIT_NONE    0 /* code for no limits for this field */

typedef struct ARFieldLimitStruct
{
   unsigned int dataType;
   union
   {
      ARIntegerLimitsStruct    intLimits;
      ARRealLimitsStruct       realLimits;
      ARCharLimitsStruct       charLimits;
      ARDiaryLimitsStruct      diaryLimits;
      AREnumLimitsStruct       enumLimits;
      /* time has no external limits */
      AREnumLimitsStruct       maskLimits;
      /* bytes has no external limits */
      ARAttachLimitsStruct     attachLimits;
      ARTableLimitsStruct      tableLimits;
      ARColumnLimitsStruct     columnLimits;
      ARDecimalLimitsStruct    decimalLimits;
      ARViewLimits             viewLimits;
      ARDisplayLimits          displayLimits;
      ARDateLimitsStruct       dateLimits;
      ARCurrencyLimitsStruct   currencyLimits;
   } u;
}  ARFieldLimitStruct;

typedef struct ARFieldLimitList
{                   /* list of 0 or more FieldLimitStructs */
   unsigned int         numItems;
   ARFieldLimitStruct  *fieldLimitList;
}  ARFieldLimitList;

typedef struct ARFieldLimitPtrList
{                   /* list of 0 or more FieldLimitStruct pointers */
   unsigned int         numItems;
   ARFieldLimitStruct **fieldLimitPtrList;
}  ARFieldLimitPtrList;


#define AR_MENU_REFRESH_CONNECT   1 /* codes for when to refresh menu */
#define AR_MENU_REFRESH_OPEN      2
#define AR_MENU_REFRESH_INTERVAL  3

#define AR_MENU_TYPE_NONE         0
#define AR_MENU_TYPE_VALUE        1 /* tags for type of char menu item */
#define AR_MENU_TYPE_MENU         2

typedef struct ARCharMenuItemStruct
{               /* defines a label and value or child menu */
   ARNameType     menuLabel;
   unsigned int   menuType;
   union
   {                           /* actual default value to load */
      char                     *menuValue;
                               /* pointer to a child menu */
      struct ARCharMenuStruct  *childMenu;
   } u;
}  ARCharMenuItemStruct;


typedef struct ARCharMenuQueryStruct
{               /* menu built using a query to the AR System */
   ARNameType          schema;
   char                server[AR_MAX_SERVER_SIZE + 1];
   ARQualifierStruct   qualifier;
   ARInternalId        labelField[AR_MAX_LEVELS_DYNAMIC_MENU];
   ARInternalId        valueField;
   ARBoolean           sortOnLabel;
   ARNameType          sampleSchema;
   ARServerNameType    sampleServer;

}  ARCharMenuQueryStruct;

#define AR_MENU_FILE_SERVER   1 /* tags for location of menu file */
#define AR_MENU_FILE_CLIENT   2

typedef struct ARCharMenuFileStruct
{               /* menu built using contents of a file */
   unsigned int   fileLocation;
   char          *filename;
}  ARCharMenuFileStruct;


typedef struct ARCharMenuSQLStruct
{               /* menu built using a direct SQL command */
   char   server[AR_MAX_SERVER_SIZE + 1];
   char  *sqlCommand;
   int    labelIndex[AR_MAX_LEVELS_DYNAMIC_MENU];
   int    valueIndex;
}  ARCharMenuSQLStruct;


typedef struct ARCharMenuList
{               /* list of 0 or more char menu entries */
   unsigned int           numItems;
   ARCharMenuItemStruct  *charMenuList;
}  ARCharMenuList;


typedef struct ARCharMenuSSStruct
{               /* server-side menu*/
   ARNameType         menuName;
   ARFieldValueList   keywordList;
   ARFieldValueList   parameterList;
   ARQualifierList    externList;
   char              *server;
   char              *schema;
}  ARCharMenuSSStruct;

#define AR_CHAR_MENU_DD_NONE    0
#define AR_CHAR_MENU_DD_FORM    1   /* tags for MenuDD struct type */
#define AR_CHAR_MENU_DD_FIELD   2

typedef struct ARCharMenuDDFormStruct
{
   unsigned int   schemaType;
   ARBoolean      includeHidden;

}  ARCharMenuDDFormStruct;

typedef struct ARCharMenuDDFieldStruct
{
   unsigned int   fieldType;
   ARNameType     schema;

}  ARCharMenuDDFieldStruct;

                                            /* tags for Menu DD name type */
#define AR_CHAR_MENU_DD_DB_NAME         0   /* Unique DB name for item */
#define AR_CHAR_MENU_DD_LOCAL_NAME      1   /* Localized label/alias for item */
#define AR_CHAR_MENU_DD_ID              2   /* ID for the item */

                                            /* tags for Menu DD value format */
#define AR_CHAR_MENU_DD_FORMAT_NONE     0
#define AR_CHAR_MENU_DD_FORMAT_ID       1   /* ID only */
#define AR_CHAR_MENU_DD_FORMAT_NAME     2   /* name only */
#define AR_CHAR_MENU_DD_FORMAT_QUOTES   3   /* name with quotes */
#define AR_CHAR_MENU_DD_FORMAT_DOLLARS  4   /* name with dollar signs */
#define AR_CHAR_MENU_DD_FORMAT_ID_NAME  5   /* id;name */
#define AR_CHAR_MENU_DD_FORMAT_NAMEL    6   /* local only */
#define AR_CHAR_MENU_DD_FORMAT_QUOTESL  7   /* local with quotes */
#define AR_CHAR_MENU_DD_FORMAT_DOLLARSL 8   /* local with dollar signs */
#define AR_CHAR_MENU_DD_FORMAT_ID_L     9   /* id;local */
#define AR_CHAR_MENU_DD_FORMAT_NAME_L  10   /* ;name;local (first & sep match)*/
#define AR_CHAR_MENU_DD_FORMAT_L_NAME  11   /* ;local;name (first * sep match)*/

typedef struct ARCharMenuDDStruct
{
   char           server[AR_MAX_SERVER_SIZE + 1];
   unsigned int   nameType;
   unsigned int   valueFormat;
   unsigned int   structType;
   union
   {
      ARCharMenuDDFormStruct    formDefn;
      ARCharMenuDDFieldStruct   fieldDefn;
   } u;

}  ARCharMenuDDStruct;

#define AR_CHAR_MENU_NONE             0
#define AR_CHAR_MENU_LIST             1 /* tags for type of character menu */
#define AR_CHAR_MENU_QUERY            2
#define AR_CHAR_MENU_FILE             3
#define AR_CHAR_MENU_SQL              4
#define AR_CHAR_MENU_SS               5
#define AR_CHAR_MENU_DATA_DICTIONARY  6

typedef struct ARCharMenuStruct
{
   unsigned int   menuType;
   union
   {
      ARCharMenuList          menuList;
      ARCharMenuQueryStruct   menuQuery;
      ARCharMenuFileStruct    menuFile;
      ARCharMenuSQLStruct     menuSQL;
      ARCharMenuSSStruct      menuSS;
      ARCharMenuDDStruct      menuDD;
   } u;

}  ARCharMenuStruct;

/* poor planning: ARCharMenuList already taken for something else */
typedef struct ARCharMenuStructList {
   unsigned int numItems;
   ARCharMenuStruct *list;
} ARCharMenuStructList;

                                       /* High order tags ORed with other tags */
#define AR_STRUCT_XML_OFFSET             (1 << 30) /* highest positive bit of the integer  */
#define AR_STRUCT_SUPPRESS_NONSTRUCTURAL_CHANGE_TAG (1 << 29) /* Export timestamps as zero */
                                                              /* and last modified as      */
                                                              /* empty string              */

#define AR_EXPORT_FORMAT_AR_DEF           1
#define AR_EXPORT_FORMAT_XML              2

#define AR_STRUCT_ITEM_SCHEMA             1 /* tags for structure item types */
#define AR_STRUCT_ITEM_SCHEMA_DEFN        2
#define AR_STRUCT_ITEM_SCHEMA_VIEW        3
#define AR_STRUCT_ITEM_SCHEMA_MAIL        4
#define AR_STRUCT_ITEM_FILTER             5
#define AR_STRUCT_ITEM_ACTIVE_LINK        6
#define AR_STRUCT_ITEM_ADMIN_EXT          7
#define AR_STRUCT_ITEM_CHAR_MENU          8
#define AR_STRUCT_ITEM_ESCALATION         9
#define AR_STRUCT_ITEM_DIST_MAP          10
#define AR_STRUCT_ITEM_SCHEMA_VIEW_MIN   11
#define AR_STRUCT_ITEM_CONTAINER         12
#define AR_STRUCT_ITEM_DIST_POOL         13
#define AR_STRUCT_ITEM_VUI               14
#define AR_STRUCT_ITEM_FIELD             15
#define AR_STRUCT_ITEM_APP               16
#define AR_STRUCT_ITEM_IMAGE             17
#define AR_STRUCT_ITEM_LOCALE_VUI        18 /* export vui's based on locale */
#define AR_STRUCT_ITEM_TASK              19

#define AR_STRUCT_ITEM_SCHEMA_DATA       30
#define AR_STRUCT_ITEM_LOCK_BLOCK        31 /* only for internal use in xml api */

                              /* special tag for ALL VUIs instead of just one */
#define AR_STRUCT_ITEM_SCHEMA_VIEW_2    103
                              /* special tag for one locale for VUIs and data */
#define AR_STRUCT_ITEM_LOCALE_VUI_DATA  104
#define AR_STRUCT_ITEM_LOCALE_APP_DATA  105
#define AR_STRUCT_ITEM_PLACEHOLDER      106

/* Source Control Object Reservation selection types */
#define AR_VERCNTL_OBJ_TYPE_NONE                    0
#define AR_VERCNTL_OBJ_TYPE_ACTIVE_LINK             10
#define AR_VERCNTL_OBJ_TYPE_MENU                    20
#define AR_VERCNTL_OBJ_TYPE_CONTAINER               30
#define AR_VERCNTL_OBJ_TYPE_ESCALATION              40
#define AR_VERCNTL_OBJ_TYPE_FILTER                  50
#define AR_VERCNTL_OBJ_TYPE_FORM                    60
#define AR_VERCNTL_OBJ_TYPE_IMAGE                   70

/* Version Control Object Reservation selection object subtypes */
#define AR_VERCNTL_OBJ_SUBTYPE_NONE                          0
#define AR_VERCNTL_OBJ_SUBTYPE_CONTAINER_ACTIVELINK_GUIDE    10
#define AR_VERCNTL_OBJ_SUBTYPE_CONTAINER_APPLICATION         20
#define AR_VERCNTL_OBJ_SUBTYPE_CONTAINER_FILTER_GUIDE        30
#define AR_VERCNTL_OBJ_SUBTYPE_CONTAINER_PACKINGLIST         40
#define AR_VERCNTL_OBJ_SUBTYPE_CONTAINER_WEBSERVICE          50

/* VERCNTL_OBJ_RESERVATION_MODE defines */
#define AR_VERCNTL_OBJ_RESERVATION_MODE_DISABLED     0
#define AR_VERCNTL_OBJ_RESERVATION_MODE_ENFORCED    10
#define AR_VERCNTL_OBJ_RESERVATION_MODE_DEFAULT     AR_VERCNTL_OBJ_RESERVATION_MODE_DISABLED

/* VERCNTL_OBJ_MOD_LOG_MODE defines */
#define AR_VERCNTL_OBJ_MOD_LOG_MODE_DISABLED     0
#define AR_VERCNTL_OBJ_MOD_LOG_MODE_ENABLED      10
#define AR_VERCNTL_OBJ_MOD_LOG_MODE_DEFAULT     AR_VERCNTL_OBJ_MOD_LOG_MODE_DISABLED

/* VERCNTL_OBJ_MOD_LOG_DEFINITION_FILES defines */
#define AR_VERCNTL_OBJ_MOD_LOG_DEFINITION_FILES_SAVE            0
#define AR_VERCNTL_OBJ_MOD_LOG_DEFINITION_FILES_DONOT_SAVE      10
#define AR_VERCNTL_OBJ_MOD_LOG_DEFINITION_FILES_DEFAULT         AR_VERCNTL_OBJ_MOD_LOG_DEFINITION_FILES_SAVE

/* definitions for XML */

#define AR_STRUCT_ITEM_XML_NONE           0
#define AR_STRUCT_ITEM_XML_SCHEMA         (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_SCHEMA)
#define AR_STRUCT_ITEM_XML_FILTER         (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_FILTER)
#define AR_STRUCT_ITEM_XML_ACTIVE_LINK    (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_ACTIVE_LINK)
#define AR_STRUCT_ITEM_XML_CHAR_MENU      (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_CHAR_MENU)
#define AR_STRUCT_ITEM_XML_ESCALATION     (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_ESCALATION)
#define AR_STRUCT_ITEM_XML_DIST_MAP       (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_DIST_MAP)
#define AR_STRUCT_ITEM_XML_CONTAINER      (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_CONTAINER)
#define AR_STRUCT_ITEM_XML_DIST_POOL      (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_DIST_POOL)
#define AR_STRUCT_ITEM_XML_VUI            (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_VUI)
#define AR_STRUCT_ITEM_XML_FIELD          (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_FIELD)
#define AR_STRUCT_ITEM_XML_APP            (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_APP)
#define AR_STRUCT_ITEM_XML_SCHEMA_DATA    (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_SCHEMA_DATA)
#define AR_STRUCT_ITEM_XML_LOCK_BLOCK     (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_LOCK_BLOCK)
#define AR_STRUCT_ITEM_XML_IMAGE          (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_IMAGE)
#define AR_STRUCT_ITEM_XML_LOCALE_VUI     (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_LOCALE_VUI)
#define AR_STRUCT_ITEM_XML_TASK           (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_TASK)
#define AR_STRUCT_ITEM_XML_LOCALE_VUI_DATA (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_LOCALE_VUI_DATA)
#define AR_STRUCT_ITEM_XML_LOCALE_APP_DATA (AR_STRUCT_XML_OFFSET | AR_STRUCT_ITEM_LOCALE_APP_DATA)

/* Cache Event Ids that we support as valid events for API ARGetCacheEvent */
#define AR_CACHE_ADMINONLYCREATE_EVENT    1
#define AR_CACHE_ADMINONLYPUBLIC_EVENT    2
#define AR_CACHE_FREE_EVENT               3
#define AR_CACHE_GROUPCHANGEPUBLIC_EVENT  4

#define AR_CACHE_EVENT_MAX                4

/*Option that indicated when to return GCE API, either immediate or after the next event occurs.*/
#define AR_GCE_OPTION_NONE 0  /* default - returns immediately.*/
#define AR_GCE_OPTION_NEXT 1  /* wait for the event only if the event is not present currently, i.e. it is yet to happen.  */
/* For eg: If api is waiting for admin cache public and there is no admin cache then the event for which they're waiting   */
/*          is already present and we just return.  If there is an admin cache then only return when it becomes public.    */
/*         If api is waiting for admin cache creation and there is an admin cache then return immediately.  If there is    */
/*          no admin cache then only return when one is created.                                                           */


#define EXPORT_OPTION_NONE         0 /* additional option to Export call */
#define EXPORT_VUI_MINIMUM         1 /* basic vui - w/o bitmaps, etc */

#define AR_OPT_NO_IMPORT          -1 /* 0xFFFFFFFF not an import op */
                                     /* importOptions for ARImport() */

                                     /* There are two sets of import options. The first set   */
                                     /* is basic options, which are CREATE and OVERWRITE. The */
                                     /* second set is advanced options, which enables further */
                                     /* configuration to ARImport functionality. The advanced */
                                     /* options are stored using bit mask. This is because    */
                                     /* that the advanced options should be set along with    */
                                     /* one of the basic options, and multiple advanced       */
                                     /* options can be turned on at the same time.            */

#define AR_IMPORT_OPT_CREATE       0 /* 0x00000000 create; error if item already exists */
#define AR_IMPORT_OPT_OVERWRITE    1 /* 0x00000001 overwrite if item exists             */

                                     /* Two bits are reserved for HANDLE_CONFLICT option. */
                                     /* The user should pick only ONE of HANDLE_CONFLICT  */
                                     /* value for the conflict handling option.           */
                                     /* We get 4 from the formula 2^4 = 16, where 16 is   */
                                     /* the starting point of the OPT_HANDLE_CONFLICT.    */
#define AR_IMPORT_OPT_HANDLE_CONFLICT_ERROR           16    /* 0x00000010 (1 << 4) */
#define AR_IMPORT_OPT_HANDLE_CONFLICT_OVERWRITE       32    /* 0x00000020 (2 << 4) */
#define AR_IMPORT_OPT_HANDLE_CONFLICT_NO_ACTION       48    /* 0x00000030 (3 << 4) */
                                                            /* == (AR_IMPORT_OPT_HANDLE_CONFLICT_ERROR | AR_IMPORT_OPT_HANDLE_CONFLICT_OVERWRITE) */
#define AR_IMPORT_OPT_NOT_DELETE_FIELD                64    /* 0x00000040 do not delete excess field */
#define AR_IMPORT_OPT_DATA_REJECT_FOR_DUP             128   /* 0x00000080 reject duplicate entries */
#define AR_IMPORT_OPT_DATA_NEWID_FOR_DUP              256   /* 0x00000100 generate new id for duplicates */
#define AR_IMPORT_OPT_DATA_OVERWRITE_FOR_DUP          512   /* 0x00000200 overwrite existing entry */
#define AR_IMPORT_OPT_DATA_MERGE_FOR_DUP              1024  /* 0x00000400 merge with existing entry */
#define AR_IMPORT_OPT_DATA_NEWID_FOR_ALL              2048  /* 0x00000800 generate new id for all entries*/
#define AR_IMPORT_OPT_NOT_DELETE_VUI                  4096  /* 0x00001000 do not delete excess VUI */
#define AR_IMPORT_OPT_NOT_OVERWRITE_PERMISSION        8192  /* 0x00002000 do not overwrite permission */
#define AR_IMPORT_OPT_WORKFLOW_PRESERVE_DEFN          16384 /* 0x00004000 (1 << 14) Preserve all workflow attributes */
                                                            /* EXCEPT workflow attachment list as workflow*/
                                                            /* attachment list is handled separately      */      
#define AR_IMPORT_OPT_WORKFLOW_MERGE_ATTACHLIST       32768 /* 0x00008000 (1 << 15) Merge workflow attachment list   */
#define AR_IMPORT_OPT_PRESERVE_HISTORY                65536 /* 0x00010000 (1 << 16) Do not overwrite change history  */
#define AR_IMPORT_OPT_PRESERVE_INDEX                 131072 /* 0x00020000 (1 << 17) Do not delete excess indexes */
#define AR_IMPORT_OPT_PRESERVE_VUI_NAMESPACE         262144 /* 0x00040000 (1 << 18) Do not override label, locale and vuitype */ 
                                                            /* of vui getting imported. */
#define AR_IMPORT_OPT_PRESERVE_EXTRA_APP_FORMS       524288 /* 0x00080000 (1 << 19) Do not delete excess forms of deployable application  */
#define AR_IMPORT_OPT_WITH_APP_OWNER                1048576 /* 0x00100000 (1 << 20) Update App Owner if form already exist when importing */
                                                             /* individual forms of deployable application                      */
#define AR_IMPORT_OPT_WORKFLOW_PRESERVE_ATTACHLIST  2097152 /* 0x00200000 (1 << 21) Overwrite the workflow definiton and preserve the     */
                                                             /* attach list*/
#define AR_IMPORT_OPT_WORKFLOW_REMOVE_ATTACHLIST    4194304 /* 0x00400000 (1 << 22)remove the form names specified in the import file */
                                                             /* from the attachment list */
#define AR_IMPORT_OPT_OVERWRITE_FULL_TEXT_OPTION    8388608 /* 0x00800000 (1 << 23) Overwrite full text option on existing field */
#define AR_IMPORT_OPT_OVERWRITE_DISP_PROPS         16777216 /* 0x01000000 (1 << 24) Overwrite field Display Properties */
#define AR_IMPORT_OPT_CREATE_NEW_ONLY              33554432 /* 0x02000000 (1 << 25) Skip existing objects */

#define AR_IMPORT_OPT_BASIC_MASK             15 /* 0x0000000F The mask to extract the value of the basic */
                                                /* import option. It is also the maxium value */
                                                /* for a Basic Import Option.                 */
                                                /* == (AR_IMPORT_OPT_HANDLE_CONFLICT_ERROR | AR_IMPORT_OPT_HANDLE_CONFLICT_OVERWRITE) */
#define AR_IMPORT_OPT_HANDLE_CONFLICT_MASK   48 /* 0x00000030 The mask used to extract the bit setting */
                                                /* for the conflict handling option. The    */
                                                /* value of the mask is 3 << 4.             */
                                                /* == (AR_IMPORT_OPT_OVERWRITE | ??? | ??? | ???) */

#define AR_DISABLE_KEYWORD_VALIDATION   (1 << 0)
#define AR_DISABLE_PATTERN_MATCHING     (1 << 1)

#define AR_EXPORT_DEFAULT                    0
#define AR_EXPORT_SHARED_WORKFLOW            (1<<0)
#define AR_EXPORT_DEFAULT_LOCALE             (1<<1)
#define AR_EXPORT_SELECTED_LOCALES           (1<<2)
#define AR_EXPORT_APP_INTEGRATION_WORKFLOW   (1<<3)
#define AR_EXPORT_LOCALE_ONLY                (1<<4)
#define AR_EXPORT_APPLICATION                (1<<5)
#define AR_EXPORT_OVERLAY                    (1<<6)

/* Flags for the setFieldOptions argument of ARSetField(): */
   /*
    * Pass this flag OR'd into setFieldOptions to get the following behavior:
    * - Server replaces its display instance items for this field
    *   that are present in the ARDisplayInstanceList *argument to ARSetField().
    * - Server does not modify or replace display instance items for this
    *   field that are not present in the list.
    * If this flag is clear, retain the 6.3 behavior (server replaces all
    * display instance items for this field with the ones in the passed-in
    * list).
    */
#define AR_SETFIELD_OPT_PRESERVE_UNLISTED_DISPLAY_INSTANCES 1
   /*
    * Pass this flag OR'd into setFieldOptions to get the following behavior:
    * - Server deletes the display instance items for this field
    *   present in the ARDisplayInstanceList *arguments to ARSetField().
    * - Server does not modify, replace, or delete any other display
    *   instance item.
    * If this flag is clear, retain the 6.3 behavior (server replaces all
    * display instance items for this field with the ones in the passed-in
    * list).
    */
#define AR_SETFIELD_OPT_DELETE_LISTED_DISPLAY_INSTANCES 2
   /*
    * If both of these bits are set, it is an error.
    */
#define AR_SETFIELD_OPT_PRESERVE_DELETE_BITS 3

typedef struct ARStructItemStruct
{               /* type and name of a structure item */
   unsigned int   type;
   ARNameType     name;
   ARNameList     selectedElements;

}  ARStructItemStruct;

typedef struct ARStructItemList
{               /* list of 0 or more struct item entries */
   unsigned int         numItems;
   ARStructItemStruct  *structItemList;

}  ARStructItemList;

                               /* tags for server info operations */
#define AR_SERVER_INFO_DB_TYPE          1/*   char - type of DB used by server*/
#define AR_SERVER_INFO_SERVER_LICENSE   2/*   char - type of server license   */
#define AR_SERVER_INFO_FIXED_LICENSE    3/*   int  - number of fixed user lic */
#define AR_SERVER_INFO_VERSION          4/*   char - version string for server*/
#define AR_SERVER_INFO_ALLOW_GUESTS     5/*   int  - allow guest users (0/1)  */
#define AR_SERVER_INFO_USE_ETC_PASSWD   6/*   int  - ref passwd file (0/1)    */
#define AR_SERVER_INFO_XREF_PASSWORDS   7/*   int  - ref passwd for blank     */
                                         /*          passwords (0/1)          */
#define AR_SERVER_INFO_DEBUG_MODE       8/*   int  - bitmask for debug type   */
#define AR_SERVER_INFO_DB_NAME          9/*   char - name of the underlying DB*/
#define AR_SERVER_INFO_DB_PASSWORD     10/*   char - password for underlying  */
#define AR_SERVER_INFO_HARDWARE        11/*   char - server hardware platform */
#define AR_SERVER_INFO_OS              12/*   char - server OS (incl version) */
#define AR_SERVER_INFO_SERVER_DIR      13/*   char - server directory         */
#define AR_SERVER_INFO_DBHOME_DIR      14/*   char - SQL DB home directory    */
#define AR_SERVER_INFO_SET_PROC_TIME   15/*   int  - set fields proc timeout  */
                                         /*          1 to 20                  */
#define AR_SERVER_INFO_EMAIL_FROM      16/*   char - user email notifies from */
#define AR_SERVER_INFO_SQL_LOG_FILE    17/*   char - file used for SQL log    */
#define AR_SERVER_INFO_FLOAT_LICENSE   18/*   int  - number of float user lic */
#define AR_SERVER_INFO_FLOAT_TIMEOUT   19/*   int  - hours without access     */
                                         /*          before license times out */
#define AR_SERVER_INFO_UNQUAL_QUERIES  20/*   int  - allow unqual queries(0/1)*/
#define AR_SERVER_INFO_FILTER_LOG_FILE 21/*   char - file used for filter log */
#define AR_SERVER_INFO_USER_LOG_FILE   22/*   char - file used for user log   */
#define AR_SERVER_INFO_REM_SERV_ID     23/*   char - AR System server id string  */
#define AR_SERVER_INFO_MULTI_SERVER    24/*   int  - 0 if single; 1 if multi  */
#define AR_SERVER_INFO_EMBEDDED_SQL    25/*   int  - 0 if not; 1 if embedded  */
#define AR_SERVER_INFO_MAX_SCHEMAS     26/*   int  - 0 if no max; else maximum*/
                                         /*          number allowed on server */
#define AR_SERVER_INFO_DB_VERSION      27/*   char - version string for DB    */
#define AR_SERVER_INFO_MAX_ENTRIES     28/*   int  - max entries return in    */
                                         /*          getlistentry; 0=unlimited*/
#define AR_SERVER_INFO_MAX_F_DAEMONS   29/*   int  - max number of fast AR    */
                                         /*          server daemons allowed   */
#define AR_SERVER_INFO_MAX_L_DAEMONS   30/*   int  - max number of list AR    */
                                         /*          server daemons allowed   */
#define AR_SERVER_INFO_ESCALATION_LOG_FILE 31
                                         /*   char - file used for esc log    */
#define AR_SERVER_INFO_ESCL_DAEMON     32/*   int  - have escal server (0/1)  */
#define AR_SERVER_INFO_SUBMITTER_MODE  33/*   int  - submitter mode for system*/
#define AR_SERVER_INFO_API_LOG_FILE    34/*   char - file used for API log    */
#define AR_SERVER_INFO_FTEXT_FIXED     35/*   int  - number of fixed ftext lic*/
#define AR_SERVER_INFO_FTEXT_FLOAT     36/*   int  - number of float ftext lic*/
#define AR_SERVER_INFO_FTEXT_TIMEOUT   37/*   int  - hours without access     */
                                         /*          before license times out */
#define AR_SERVER_INFO_RESERV1_A       38/*   int  - number of fixed reserv li*/
#define AR_SERVER_INFO_RESERV1_B       39/*   int  - number of float reserv li*/
#define AR_SERVER_INFO_RESERV1_C       40/*   int  - number of admin reserv li*/
#define AR_SERVER_INFO_SERVER_IDENT    41/*   char - unique identifier of the */
                                         /*          machine running server   */
#define AR_SERVER_INFO_DS_SVR_LICENSE  42/*   char - type of DS server license*/
#define AR_SERVER_INFO_DS_MAPPING      43/*   char - name of schema holding   */
                                         /*          distributed mappings     */
#define AR_SERVER_INFO_DS_PENDING      44/*   char - name of schema holding   */
                                         /*          distributed pending items*/
#define AR_SERVER_INFO_DS_RPC_SOCKET   45/*   int  - RPC socket for DS server */
#define AR_SERVER_INFO_DS_LOG_FILE     46/*   char - file used for DS log     */
#define AR_SERVER_INFO_SUPPRESS_WARN   47/*   char - list of note/warning msg */
                                         /*          numbers to be suppressed */
#define AR_SERVER_INFO_HOSTNAME        48/*   char - hostname of server       */
#define AR_SERVER_INFO_FULL_HOSTNAME   49/*   char - DNS hostname of server   */
#define AR_SERVER_INFO_SAVE_LOGIN      50/*   int  - admin override for saving*/
                                         /*          login info on client     */
#define AR_SERVER_INFO_U_CACHE_CHANGE  51/*   int  - last user cache change   */
#define AR_SERVER_INFO_G_CACHE_CHANGE  52/*   int  - last group cache change  */
#define AR_SERVER_INFO_STRUCT_CHANGE   53/*   int  - last structure change    */
                                         /*          (for this run of server) */
#define AR_SERVER_INFO_CASE_SENSITIVE  54/*   int  - case sensitivity of DB   */
#define AR_SERVER_INFO_SERVER_LANG     55/*   char - server language setting  */
#define AR_SERVER_INFO_ADMIN_ONLY      56/*   int  - Admin Only Mode (0/1)    */
#define AR_SERVER_INFO_CACHE_LOG_FILE  57/*   char - file used for cache log  */
#define AR_SERVER_INFO_FLASH_DAEMON    58/*   int  - have flash server (0/1)  */
#define AR_SERVER_INFO_THREAD_LOG_FILE 59/*   char - file used for thread log */
#define AR_SERVER_INFO_ADMIN_TCP_PORT  60/*   int  - TCP port for Admin thread*/
#define AR_SERVER_INFO_ESCL_TCP_PORT   61/*   int  - TCP port for Escl thread */
#define AR_SERVER_INFO_FAST_TCP_PORT   62/*   int  - TCP port for Fast threads*/
#define AR_SERVER_INFO_LIST_TCP_PORT   63/*   int  - TCP port for List threads*/
#define AR_SERVER_INFO_FLASH_TCP_PORT  64/*   int  - TCP port for Flash thread*/
#define AR_SERVER_INFO_TCD_TCP_PORT    65/*   int  - TCP port for TCD thread  */
#define AR_SERVER_INFO_DSO_DEST_PORT   66/*   int  - TCP port DSO uses to talk*/
#define AR_SERVER_INFO_INFORMIX_DBN    67/*   char - Informix DB server name  */
#define AR_SERVER_INFO_INFORMIX_TBC    68/*   char - Informix TBConfig        */
#define AR_SERVER_INFO_INGRES_VNODE    69/*   char - Ingres VNode setting     */
#define AR_SERVER_INFO_ORACLE_SID      70/*   char - Oracle SID               */
#define AR_SERVER_INFO_ORACLE_TWO_T    71/*   char - Oracle Two Task setting  */
#define AR_SERVER_INFO_SYBASE_CHARSET  72/*   char - Sybase character set     */
#define AR_SERVER_INFO_SYBASE_SERV     73/*   char - Sybase server name       */
#define AR_SERVER_INFO_SHARED_MEM      74/*   int  - 0 - disabled; 1 - enabled*/
#define AR_SERVER_INFO_SHARED_CACHE    75/*   int  - 0 - disabled; 1 - enabled*/
#define AR_SERVER_INFO_CACHE_SEG_SIZE  76/*   int  - cache seg size (UNIX)    */
#define AR_SERVER_INFO_DB_USER         77/*   char - user to access DB as     */
#define AR_SERVER_INFO_NFY_TCP_PORT    78/*   int  - TCP port for Notifier Svr*/
#define AR_SERVER_INFO_FILT_MAX_TOTAL  79/*   int  - max filters for an op    */
#define AR_SERVER_INFO_FILT_MAX_STACK  80/*   int  - max stack of filters     */
#define AR_SERVER_INFO_DEFAULT_ORDER_BY 81/*  int  - 0 - None   ; 1 - EntryID */
#define AR_SERVER_INFO_DELAYED_CACHE   82/*   int  - 0 -delay on; 1 -delay off*/
#define AR_SERVER_INFO_DSO_MERGE_STYLE 83/*   int  - 0 - merge; 1 - overwrite */
#define AR_SERVER_INFO_EMAIL_LINE_LEN  84/*   int  - line length of e-mail    */
#define AR_SERVER_INFO_EMAIL_SYSTEM    85/*   char - e-mail system (UNIX)     */
#define AR_SERVER_INFO_INFORMIX_RELAY_MOD 86/*char - informix relay module    */
#define AR_SERVER_INFO_PS_RPC_SOCKET   87/*   char - privSvr socket/port pairs*/
#define AR_SERVER_INFO_REGISTER_PORTMAPPER 88/*int  - 0 - not reg;1 - register*/
#define AR_SERVER_INFO_SERVER_NAME     89/*   char - name of the server       */
#define AR_SERVER_INFO_DBCONF          90/*   char - dbconf file content      */
#define AR_SERVER_INFO_APPL_PENDING    91/*   char - name of schema holding   */
                                         /*          application pending items*/
#define AR_SERVER_INFO_AP_RPC_SOCKET   92/*   int  - RPC socket for AP server */
#define AR_SERVER_INFO_AP_LOG_FILE     93/*   char - file used for AP log     */
#define AR_SERVER_INFO_AP_DEFN_CHECK   94/*   int  - interval between checks  */
                                         /*          for changed defns in appl*/
#define AR_SERVER_INFO_MAX_LOG_FILE_SIZE 95/* int  - 0 - no limit             */
#define AR_SERVER_INFO_CLUSTERED_INDEX 96/*   int  - - 0 - non-clustered;     */
                                         /*            1 - clustered          */
#define AR_SERVER_INFO_ACTLINK_DIR     97/*   char - actlink run process      */
                                         /*          directory                */
#define AR_SERVER_INFO_ACTLINK_SHELL   98/*   char - shell for actlink run    */
                                         /*          processes                */
#define AR_SERVER_INFO_USER_CACHE_UTILS 99/*  int  - 1 - allow arcache,       */
                                          /*            arreload API calls    */
#define AR_SERVER_INFO_EMAIL_TIMEOUT  100/*   int  - email timeout (UNIX)     */
#define AR_SERVER_INFO_EXPORT_VERSION 101/*   int  - server's export version  */
#define AR_SERVER_INFO_ENCRYPT_AL_SQL 102/*   int  - encrypt AL direct SQL    */
                                         /*          exports                  */
#define AR_SERVER_INFO_SCC_ENABLED    103/*   int  - 0 - not enabled          */
#define AR_SERVER_INFO_SCC_PROVIDER_NAME 104/* char - name of SCC provider    */
#define AR_SERVER_INFO_SCC_TARGET_DIR 105/*   char - target dir for SCC       */
#define AR_SERVER_INFO_SCC_COMMENT_CHECKIN 106/*int- comments required at     */
                                              /*     checkin time (0/1)       */
#define AR_SERVER_INFO_SCC_COMMENT_CHECKOUT 107/*int-comments required at     */
                                               /*     checkout time (0/1)     */
#define AR_SERVER_INFO_SCC_INTEGRATION_MODE 108/*int-level of SCC             */
                                               /*    integration (0/1)        */
#define AR_SERVER_INFO_EA_RPC_SOCKET  109/*   int  - RPC socket for external  */
                                         /*          authentication server    */
#define AR_SERVER_INFO_EA_RPC_TIMEOUT 110/*   int  - Timeout associated with  */
                                         /*       calls to an external        */
                                         /*       authentication server       */
#define AR_SERVER_INFO_USER_INFO_LISTS 111/*  int  - Number of User/NotifyUser*/
                                          /*         hash Lists.              */
#define AR_SERVER_INFO_USER_INST_TIMEOUT 112/*int  - Timeout interval to flush*/
                                          /*         user instances in User   */
                                          /*         Cache hash lists.        */
#define AR_SERVER_INFO_DEBUG_GROUPID  113/*   int  - id of the group          */
                                         /*          whose members are allowed*/
                                         /*          to retrieve server       */
                                         /*          logging information      */
#define AR_SERVER_INFO_APPLICATION_AUDIT 114/*char - application license audit*/
                                            /*       line                     */
#define AR_SERVER_INFO_EA_SYNC_TIMEOUT 115/*  int  - Timeout associated with  */
                                          /*         calls to an external     */
                                          /*         authentication server    */
#define AR_SERVER_INFO_SERVER_TIME    116/*   int  - server's current time    */
#define AR_SERVER_INFO_SVR_SEC_CACHE  117/*   int  - tie security cache to    */
                                         /*          specific server name(0/1)*/
#define AR_SERVER_INFO_LOGFILE_APPEND 118/*   int  - - 0 - create bak file    */
                                         /*            1 - append to existing */
#define AR_SERVER_INFO_MINIMUM_API_VER 119/*  int  - specifies the oldest API */
                                         /*          version with which server*/
                                         /*          will communicate         */
#define AR_SERVER_INFO_MAX_AUDIT_LOG_FILE_SIZE 120/*int - max audit file size */
                                                  /*      0 -  no limit       */
#define AR_SERVER_INFO_CANCEL_QUERY   121/*   int  - 0 - inactive; 1 - active */
#define AR_SERVER_INFO_MULT_ASSIGN_GROUPS 122/*int - 0 - not allowed          */
#define AR_SERVER_INFO_ARFORK_LOG_FILE 123/* char  - name of fork log file    */
#define AR_SERVER_INFO_DSO_PLACEHOLDER_MODE 124/* int  - remote run DSO dummy */
                                               /*         run mode            */
#define AR_SERVER_INFO_DSO_POLLING_INTERVAL 125/* int  - 15-3600              */
#define AR_SERVER_INFO_DSO_SOURCE_SERVER    126/* char - source server for DSO*/
#define AR_SERVER_INFO_DS_POOL              127/* char - name of schema for   */
                                               /*        distributed pools    */
#define AR_SERVER_INFO_DSO_TIMEOUT_NORMAL   128/* int  - number of seconds for*/
                                               /*     the timeout DSO uses for*/
                                               /*     making API calls        */
#define AR_SERVER_INFO_ENC_PUB_KEY          129/* char - server public key    */
#define AR_SERVER_INFO_ENC_PUB_KEY_EXP      130/* int  - time (secs) until the*/
                                               /*   server's public/private   */
                                               /*   keys expire               */
#define AR_SERVER_INFO_ENC_DATA_KEY_EXP     131/* int  - time until encrypted */
                                               /*    api session key expires  */
#define AR_SERVER_INFO_ENC_DATA_ENCR_ALG    132/* int  - API Data encryption  */
                                               /*    algorithm                */
#define AR_SERVER_INFO_ENC_SEC_POLICY       133/* int  - security policy      */
#define AR_SERVER_INFO_ENC_SESS_H_ENTRIES   134/* int  - number of session    */
                                               /*    hash entries             */
#define AR_SERVER_INFO_DSO_TARGET_CONNECTION 135/* char - String of AR server */
                                                /*   name, RPC and port #     */
#define AR_SERVER_INFO_PREFERENCE_PRIORITY  136/* int  - Priority number for  */
                                               /*    preference server        */
#define AR_SERVER_INFO_ORACLE_QUERY_ON_CLOB 137/* int  - 1 - support search on*/
                                               /*    clob field               */
#define AR_SERVER_INFO_MESSAGE_CAT_SCHEMA   138/* char - name of schema for   */
                                               /*    message catalog          */
#define AR_SERVER_INFO_ALERT_SCHEMA         139/* char - name of schema for   */
                                               /*    alert events             */
#define AR_SERVER_INFO_LOCALIZED_SERVER     140/* int  - 0 - not localized    */
                                               /*        1 - localized        */
#define AR_SERVER_INFO_SVR_EVENT_LIST       141/* char - list of server events*/
                                               /*    to track                 */
#define AR_SERVER_INFO_DISABLE_ADMIN_OPERATIONS 142/* int - 0 - enabled       */
                                               /*           1 - not enabled   */
#define AR_SERVER_INFO_DISABLE_ESCALATIONS  143/* int  - 0 - enabled          */
                                               /*        1 - not enabled      */
#define AR_SERVER_INFO_ALERT_LOG_FILE       144/* char - file used for alert  */
                                               /*    log                      */
#define AR_SERVER_INFO_DISABLE_ALERTS       145/* int  - 0 - enabled          */
                                               /*        1 - not enabled      */
#define AR_SERVER_INFO_CHECK_ALERT_USERS    146/* int  - 0 - no check         */
                                               /*        1 - check            */
#define AR_SERVER_INFO_ALERT_SEND_TIMEOUT   147/* int  - number of seconds    */
                                               /*    allowed sending alert    */
#define AR_SERVER_INFO_ALERT_OUTBOUND_PORT  148/* int  - alert outbound port  */
#define AR_SERVER_INFO_ALERT_SOURCE_AR      149/* char - AR System source tag */
#define AR_SERVER_INFO_ALERT_SOURCE_FB      150/* char - Flashboard source tag*/
#define AR_SERVER_INFO_DSO_USER_PASSWD      151/* char - DSO User Password    */
#define AR_SERVER_INFO_DSO_TARGET_PASSWD    152/* char - DSO Target Password  */
#define AR_SERVER_INFO_APP_SERVICE_PASSWD   153/* char - Remedy Application   */
                                               /*    Service password         */
#define AR_SERVER_INFO_MID_TIER_PASSWD      154/* char - Mid Tier password    */
#define AR_SERVER_INFO_PLUGIN_LOG_FILE      155/* char - log file name for    */
                                               /*    arplugin                 */
#define AR_SERVER_INFO_SVR_STATS_REC_MODE   156/* int  - recording mode for   */
                                               /*    server stats             */
#define AR_SERVER_INFO_SVR_STATS_REC_INTERVAL 157/* int- interval (secs) for  */
                                                 /*  server stats recording   */
#define AR_SERVER_INFO_DEFAULT_WEB_PATH     158/* char - default path for web */
                                               /*    access                   */
#define AR_SERVER_INFO_FILTER_API_RPC_TIMEOUT 159/* int - Timeout for calls   */
                                                 /*  to the filter Api        */
#define AR_SERVER_INFO_DISABLED_CLIENT      160/* char - types of clients that*/
                                               /*   are denied server access  */
#define AR_SERVER_INFO_PLUGIN_PASSWD        161/* char - Plug-in server passwd*/
#define AR_SERVER_INFO_PLUGIN_ALIAS         162/* char - List of plug-in alias*/
#define AR_SERVER_INFO_PLUGIN_TARGET_PASSWD 163/* char - Password used by     */
                                               /*    plug-in server clients   */
#define AR_SERVER_INFO_REM_WKFLW_PASSWD     164/* char -Remote workflow passwd*/
#define AR_SERVER_INFO_REM_WKFLW_TARGET_PASSWD 165/* char - Remote workflow   */
                                                  /* passwds for other servers*/
#define AR_SERVER_INFO_EXPORT_SVR_OPS       166/* int  - Export Server-side   */
                                               /*    operations               */
#define AR_SERVER_INFO_INIT_FORM            167/* char - "Initial Form" to be */
                                               /*    loaded on Login          */
#define AR_SERVER_INFO_ENC_PUB_KEY_ALG      168/* int  - Public key encryption*/
                                               /*    algorithm                */
#define AR_SERVER_INFO_IP_NAMES             169/* char - IP names that are    */
                                               /*    accepted as current svr  */
#define AR_SERVER_INFO_DSO_CACHE_CHK_INTERVAL 170/* int- Interval (sec) for   */
                                                 /*  checking cache schema    */
#define AR_SERVER_INFO_DSO_MARK_PENDING_RETRY 171/* int- Indicates to mark the*/
                                                 /*  pending items for retry  */
#define AR_SERVER_INFO_DSO_RPCPROG_NUM       172 /* int - RPC number for the   */
                                                 /*   local ARServer for DSO   */
#define AR_SERVER_INFO_DELAY_RECACHE_TIME    173 /* int -  seconds before      */
                                                 /* sending a delayed signal to*/
                                                 /* move servers to shared cache*/
#define AR_SERVER_INFO_DFLT_ALLOW_CURRENCIES 174 /* char - default list of      */
                                                 /*  allowable currencies       */
#define AR_SERVER_INFO_CURRENCY_INTERVAL     175 /* int  - currency ratio client*/
                                                 /*    refresh interval(minutes)*/
#define AR_SERVER_INFO_ORACLE_CURSOR_SHARE   176 /* char - The value of Oracle  */
                                                 /*    parameter cursor_sharing.*/
#define AR_SERVER_INFO_DB2_DB_ALIAS          177 /* char - DB2 database alias   */
#define AR_SERVER_INFO_DB2_SERVER            178 /* char - DB2 server name      */
#define AR_SERVER_INFO_DFLT_FUNC_CURRENCIES  179 /* char - default list of      */
                                                 /*  functional currencies      */
#define AR_SERVER_INFO_EMAIL_IMPORT_FORM     180 /* int - 0 by default          */
                                                 /* 0 - don't import email forms*/
                                                 /* 1 - import email forms      */
#define AR_SERVER_INFO_EMAIL_AIX_USE_OLD_EMAIL 181 /* int(AIX) 0 - use new email*/
                                                   /*          1 - use old email*/
#define AR_SERVER_INFO_TWO_DIGIT_YEAR_CUTOFF 182 /* int - two digit year cutoff */
#define AR_SERVER_INFO_ALLOW_BACKQUOTE_IN_PROCESS 183/* int  - 0 - no backquotes */
                                                     /*        1 - allowed       */
#define AR_SERVER_INFO_DB_CONNECTION_RETRIES 184 /* int - no retries for DB conn */
#define AR_SERVER_INFO_DB_CHAR_SET           185 /* char - the character set of */
                                                 /*        AR System database.  */
#define AR_SERVER_INFO_CURR_PART_VALUE_STR   186 /* char - currency "VALUE" string */
#define AR_SERVER_INFO_CURR_PART_TYPE_STR    187 /* char - currency "TYPE" string */
#define AR_SERVER_INFO_CURR_PART_DATE_STR    188 /* char - currency "DATE" string */
#define AR_SERVER_INFO_HOMEPAGE_FORM         189 /* char - homepage form        */
#define AR_SERVER_INFO_DISABLE_FTS_INDEXER   190 /* int  - 0 - enabled          */
                                                 /*        1 - not enabled      */
#define AR_SERVER_INFO_DISABLE_ARCHIVE       191 /* int  - 0 - enabled          */
                                                 /*        1 - not enabled      */
#define AR_SERVER_INFO_SERVERGROUP_MEMBER    192 /* int  - 0 - not a SG member  */
                                                 /*        1 - a SG member      */
#define AR_SERVER_INFO_SERVERGROUP_LOG_FILE  193 /* char - file used for server */
                                                 /*  group log                  */
#define AR_SERVER_INFO_FLUSH_LOG_LINES       194 /* int - 0 - no flush          */
                                                 /*       1 - flush each line   */
#define AR_SERVER_INFO_SERVERGROUP_INTERVAL  195 /* int  - interval (secs) for  */
                                                 /*  server group checking      */
#define AR_SERVER_INFO_JAVA_VM_OPTIONS       196 /* char - java vm options */
#define AR_SERVER_INFO_PER_THREAD_LOGS       197 /* int - 0 - use common log    */
                                                 /*       1 - per-thread log    */
#define AR_SERVER_INFO_CONFIG_FILE           198 /* char - path to ar.conf  */
#define AR_SERVER_INFO_SSTABLE_CHUNK_SIZE    199 /* int - max sstable chunk */
                                                 /*    (0==unlimited)       */
#define AR_SERVER_INFO_SG_EMAIL_STATE        200 /* int  - 0 - no server group  */
                                                 /*            or not managed   */
                                                 /*        1 - suspended        */
                                                 /*        2 - resumed          */
#define AR_SERVER_INFO_SG_FLASHBOARDS_STATE  201 /* int  - 0 - no server group  */
                                                 /*            or not managed   */
                                                 /*        1 - suspended        */
                                                 /*        2 - resumed          */
#define AR_SERVER_INFO_SERVERGROUP_NAME      202 /* char - name to identify     */
                                                 /*  server group               */
#define AR_SERVER_INFO_SG_ADMIN_SERVER_NAME  203 /* char - name of server with  */
                                                 /*  Administration operation   */
#define AR_SERVER_INFO_LOCKED_WKFLW_LOG_MODE 204 /* int  - what to log while    */
                                                 /* executing locked workflow   */
                                                 /*  0 - names only             */
                                                 /*  1 - encrypted workflow log */
#define AR_SERVER_INFO_ROLE_CHANGE           205 /* int  - last role change     */
#define AR_SERVER_INFO_SG_ADMIN_SERVER_PORT  206 /* int  - port of server with  */
                                                 /*  Administration operation   */
#define AR_SERVER_INFO_PLUGIN_LOOPBACK_RPC   207 /* int  - RPC socket number for*/
                                                 /*        plugin loopback      */
#define AR_SERVER_INFO_CACHE_MODE            208 /* int 0 - production, 1 - dev */
#define AR_SERVER_INFO_DB_FREESPACE          209 /* int - amount of free        */
                                                 /*       database space in KB  */
#define AR_SERVER_INFO_GENERAL_AUTH_ERR      210 /* int 0 - detailed auth error */
                                                 /* int 1 - general auth error  */
#define AR_SERVER_INFO_AUTH_CHAINING_MODE    211 /* int 0 - default             */
                                                 /* int 1 - 1st ARS, then AREA  */
                                                 /* int 2 - 1st AREA, then ARS  */
                                                 /* int 3 - ARS, OS, then AREA  */
                                                 /* int 4 - ARS, AREA, then OS  */
#define AR_SERVER_INFO_RPC_NON_BLOCKING_IO   212 /* int 0 - blocking (default)  */
                                                 /* int 1 - non-blocking        */
#define AR_SERVER_INFO_SYS_LOGGING_OPTIONS   213 /* int  - bitmask              */
                                                 /*  bit 1 - no system logging  */
#define AR_SERVER_INFO_EXT_AUTH_CAPABILITIES 214 /* int  - bitmask              */
                                                 /*  bit 1 - no email address   */
                                                 /*  bit 2 - no notify mech     */
                                                 /*  bit 3 - no group ids       */
                                                 /*  bit 4 - no license info    */
#define AR_SERVER_INFO_DSO_ERROR_RETRY       215 /* int 0 - standard (default)  */
                                                 /* int 1 - retry nothing       */
                                                 /* int 2 - retry everything    */
                                                 /* int 3 - standard + db error */
#define AR_SERVER_INFO_PREF_SERVER_OPTION    216 /* int 1 - user defined (dflt) */
                                                 /* int 2 - use this server     */
                                                 /* int 3 - don't use this srv  */
#define AR_SERVER_INFO_FTINDEXER_LOG_FILE    217 /* char - file used for full   */
                                                 /*    text indexer log         */
#define AR_SERVER_INFO_EXCEPTION_OPTION      218 /* int 0 - include stack trace */
                                                 /* in the exception output     */
                                                 /* int 1 - exclude stack trace */
#define AR_SERVER_INFO_ERROR_EXCEPTION_LIST  219 /* char - a ";" delimited      */
                                                 /* string of integer values    */
#define AR_SERVER_INFO_DSO_MAX_QUERY_SIZE    220 /* int - maximum number of     */
                                                 /*  pending records per query  */
#define AR_SERVER_INFO_ADMIN_OP_TRACKING     221 /* int - admin op (such as import) */
                                                 /* should provide progress info */
                                                 /*     0 - No (default)        */
                                                 /*     1 - Yes                 */
#define AR_SERVER_INFO_ADMIN_OP_PROGRESS     222 /* char - admin op (such as import)*/
                                                 /* progress indicator string   */
                                                 /* Non-empty value when import */
                                                 /* operation is in progress;   */
                                                 /* Otherwise NULL              */
#define AR_SERVER_INFO_PLUGIN_DEFAULT_TIMEOUT 223 /* int - Default timeout for  */
                                                  /* plugin server              */
#define AR_SERVER_INFO_EA_IGNORE_EXCESS_GROUPS 224 /* int - Ignore Excess Groups  */
                                                   /* for external authentication */
                                                 /*     0 - No (default)        */
                                                 /*     1 - Yes                 */
#define AR_SERVER_INFO_EA_GROUP_MAPPING      225 /*   char - ExtAuth            */
                                                 /* ldapGroupName/ARGroupName pairs*/
#define AR_SERVER_INFO_PLUGIN_LOG_LEVEL      226 /* int - default 1000          */
                                                 /* values between 100 - 1000   */
#define AR_SERVER_INFO_FT_THRESHOLD_LOW      227 /* int  - full text search     */
                                                 /*  low threshold              */
#define AR_SERVER_INFO_FT_THRESHOLD_HIGH     228 /* int  - full text search     */
                                                 /*  high threshold             */
#define AR_SERVER_INFO_NOTIFY_WEB_PATH       229 /* char - email notification   */
                                                 /*  web path                   */
#define AR_SERVER_INFO_DISABLE_NON_UNICODE_CLIENTS 230   /* int */
#define AR_SERVER_INFO_FT_COLLECTION_DIR     231 /* char - full text collection */
                                                 /*  directory                  */
#define AR_SERVER_INFO_FT_CONFIGURATION_DIR  232 /* char - full text config     */
                                                 /*  directory                  */
#define AR_SERVER_INFO_FT_TEMP_DIR           233 /* deprecated - scheduled for  */
                                                 /*  removal in future release  */
#define AR_SERVER_INFO_FT_REINDEX            234 /* int 1 - initiate a reindex  */
                                                 /*  of all full text indexes   */
#define AR_SERVER_INFO_FT_DISABLE_SEARCH     235 /* int 0 - enable full text    */
                                                 /*  search                     */
                                                 /* int 1 - disable full text   */
                                                 /*  search                     */
#define AR_SERVER_INFO_FT_CASE_SENSITIVITY   236 /* int 0 - full text search is */
                                                 /*  is case sensitive          */
                                                 /* int 1 - full text search is */
                                                 /*  case insensitive           */
#define AR_SERVER_INFO_FT_SEARCH_MATCH_OP    237 /* int 0 - force leading and   */
                                                 /*  trailing wildcard          */
                                                 /* int 1 - force trailing wild */
                                                 /* int 2 - ignore leading wild */
                                                 /* int 3 - remove wildcards    */
                                                 /* int 4 - unchanged           */
#define AR_SERVER_INFO_FT_STOP_WORDS         238 /* char - semicolon delimited  */
                                                 /*  full text stop words       */
#define AR_SERVER_INFO_FT_RECOVERY_INTERVAL  239 /* int - minimum # of minutes  */
                                                 /*  between indexing failure   */
                                                 /*  recovery attempts          */
#define AR_SERVER_INFO_FT_OPTIMIZE_THRESHOLD 240 /* int - index changes before  */
                                                 /*  optimization (not used in  */
                                                 /*  version 7.6 and later)     */
#define AR_SERVER_INFO_MAX_PASSWORD_ATTEMPTS 241 /* int - maximum number of     */
                                                 /*  login attempts allowed(due */
                                                 /*  to bad password)           */
#define AR_SERVER_INFO_GUESTS_RESTRICT_READ  242 /* int - Restricted Read       */
                                                 /*       to guest user         */
                                                 /* 0 - No (default)            */
                                                 /* 1 - Yes                     */
#define AR_SERVER_INFO_ORACLE_CLOB_STORE_INROW 243 /* int - Oracle Clob use IN  */
                                                   /*   ROW storage             */
                                                   /* 0 - No                    */
                                                   /* 1 - Yes (default)         */
#define AR_SERVER_INFO_NEXT_ID_BLOCK_SIZE    244 /* int - size of nextId block  */
#define AR_SERVER_INFO_NEXT_ID_COMMIT        245 /* int 0 - Don't commit nextID */
                                                 /* int 1 - Do commit nextID    */
#define AR_SERVER_INFO_RPC_CLIENT_XDR_LIMIT  246 /* int - size limit of RPC     */
                                                 /*  data sent to the server    */
#define AR_SERVER_INFO_CACHE_DISP_PROP       247 /* int 0 - only cache server display props */
                                                 /*     1 - deprecated (same as 3)          */
                                                 /*     2 - deprecated (same as 3)          */
                                                 /*     3 - cache all display props         */
                                                 /*     4 - only cache server display props */
                                                 /*          and maintain in database       */
#define AR_SERVER_INFO_USE_CON_NAME_IN_STATS 248 /* int 0 - use default server  */
                                                 /*  name in statistics entries */
                                                 /* int 1 - use server connect  */
                                                 /*  name in statistics entries */
#define AR_SERVER_INFO_DB_MAX_ATTACH_SIZE    249 /* The maximum size (in bytes) allowed for attachments */
                                                 /* in Oracle. Please see AR_MAX_ATTACH_SIZE. It overrides this. */
#define AR_SERVER_INFO_DB_MAX_TEXT_SIZE      250 /* The maximum size (in bytes) allowed for long character text   */
                                                 /* data in Oracle, SQL Server, and Sybase databases.             */
                                                 /* For Oracle databases, this value is also used for memory      */
                                                 /* allocation during the processing of long text data; therefore,*/
                                                 /* it must be used conservatively. The default for an Oracle     */
                                                 /* database is 1 MB.                                             */ 
                                                 /* For SQL Server and Sybase, the default is 2,147,483,647 bytes.*/
                                                 /* The max value allowed for either DB is 2,147,483,647 bytes.   */
#define AR_SERVER_INFO_GUID_PREFIX           251 /* The character string used as a prefix for GUID strings that   */
                                                 /* are generated by filters.                                     */
#define AR_SERVER_INFO_MULTIPLE_ARSYSTEM_SERVERS   252 /* int 0 - not running multiple    */
                                                       /*  servers on same host (default) */
                                                       /* int 1 - running multiple        */
                                                       /*  servers on same host           */
#define AR_SERVER_INFO_ORACLE_BULK_FETCH_COUNT     253 /* int - number of the rows of data fetched at a time from */
                                                       /* the result set when querying an Oracle database.  The   */
                                                       /* minimum is 1, the maximum is 100, and the default is 50.*/
#define AR_SERVER_INFO_MINIMUM_CMDB_API_VER  254 /* int - specifies the oldest CMDB API */
                                                 /*  version with which server will     */
                                                 /*  communicate                        */
#define AR_SERVER_INFO_PLUGIN_PORT           255 /* int - Plug-in server port           */
#define AR_SERVER_INFO_PLUGIN_LIST           256 /* char - a ";" delimited string       */
                                                 /* of plugins found in ar.cfg          */
#define AR_SERVER_INFO_PLUGIN_PATH_LIST      257 /* char - a ";" delimited string       */
                                                 /* of plugin paths found in ar.cfg     */
#define AR_SERVER_INFO_SHARED_LIB            258 /* char - the name of the cmdb shared  */
                                                 /* library to be loaded by the server  */
#define AR_SERVER_INFO_SHARED_LIB_PATH       259 /* char - additional path environment  */
                                                 /* settings for cmdb shared library    */
#define AR_SERVER_INFO_CMDB_INSTALL_DIR      260 /* char - cmdb install location        */
                                                 /* (used only by cmdb installers)      */
#define AR_SERVER_INFO_RE_LOG_DIR            261 /* char - reconciliation engine log    */
                                                 /* file directory (used only by cmdb)  */
#define AR_SERVER_INFO_LOG_TO_FORM           262 /* int - bit mask value each logtype to enable logging to form */

#define AR_SERVER_INFO_SQL_LOG_FORM          263 /* char - form name for logging sql */
#define AR_SERVER_INFO_API_LOG_FORM          264 /* char - form name for logging api */
#define AR_SERVER_INFO_ESCL_LOG_FORM         265 /* char - form name for logging esclation */
#define AR_SERVER_INFO_FILTER_LOG_FORM       266 /* char - form name for logging filter */
#define AR_SERVER_INFO_USER_LOG_FORM         267 /* char - form name for logging user */
#define AR_SERVER_INFO_ALERT_LOG_FORM        268 /* char - form name for logging alert */
#define AR_SERVER_INFO_SVRGRP_LOG_FORM       269 /* char - form name for logging server group */
#define AR_SERVER_INFO_FTINDX_LOG_FORM       270 /* char - form name for logging full text index */
#define AR_SERVER_INFO_THREAD_LOG_FORM       271 /* char - form name for logging thread */

#define AR_SERVER_INFO_FIPS_SERVER_MODE      272 /* char - FIPS Server Mode */ 
#define AR_SERVER_INFO_FIPS_CLIENT_MODE      273 /* char - FIPS Client Mode */
#define AR_SERVER_INFO_FIPS_STATUS           274 /* char - FIPS Status */ 
#define AR_SERVER_INFO_ENC_LEVEL             275 /* char - Encryption Level (Standard/Perf/Premium) */ 
#define AR_SERVER_INFO_ENC_ALGORITHM         276 /* char - Encryption Algorithm (DES/RC4/AES) */ 
#define AR_SERVER_INFO_FIPS_MODE_INDEX       277 /* int - FIPS Server Mode index value */ 
#define AR_SERVER_INFO_FIPS_DUAL_MODE_INDEX  278 /* int - FIPS Dual Mode index value */
#define AR_SERVER_INFO_ENC_LEVEL_INDEX       279 /* int - Encryption Level index value */
#define AR_SERVER_INFO_DSO_MAIN_POLL_INTERVAL 280/* int - Interval(sec) for DSO main polling */
#define AR_SERVER_INFO_RECORD_OBJECT_RELS    281 /* int 0 - do not record object        */
                                                 /*  relationships                      */
                                                 /* int 1 - record object relationships */
#define AR_SERVER_INFO_LICENSE_USAGE         282 /* 0 = disabled, 1 = write licenses, 2 = all licenses */

#define AR_SERVER_INFO_COMMON_LOG_FORM       283 /* char - common log form name */
#define AR_SERVER_INFO_LOG_FORM_SELECTED     284 /* int - bit mask to indicate form selected - default or common form. */
                                                 /* If bit is set for respective type, log should go to common form */

#define AR_SERVER_INFO_MAX_CLIENT_MANAGED_TRANSACTIONS     285 /* Maximum number of concurrent client managed transactions */ 
#define AR_SERVER_INFO_CLIENT_MANAGED_TRANSACTION_TIMEOUT  286 /* Maximum allowed time to hold a transaction before timeout happens */
                                                               /* and transaction gets rolled back                                  */

#define AR_SERVER_INFO_OBJ_RESERVATION_MODE      287 /* int  - 0 - not disabled, 10 enforced */
#define AR_SERVER_INFO_NEW_ENC_PUB_KEY_EXP       288 /* int  - updated value for time (secs) until Public Key expires */
#define AR_SERVER_INFO_NEW_ENC_DATA_KEY_EXP      289 /* int  - updated value for time (secs) until encrypted api session key expires */
#define AR_SERVER_INFO_NEW_ENC_DATA_ALG          290 /* int  - updated Data Key Algorithm enumerated value */
#define AR_SERVER_INFO_NEW_ENC_SEC_POLICY        291 /* int  - updated Encryption security policy value */
#define AR_SERVER_INFO_NEW_FIPS_SERVER_MODE      292 /* char - updated FIPS mode */ 
#define AR_SERVER_INFO_NEW_ENC_LEVEL             293 /* char - updated Encryption Level (Standard/Perf/Premium) */ 
#define AR_SERVER_INFO_NEW_ENC_ALGORITHM         294 /* char - updated Data Encryption Algorithm (DES/RC4/AES) */ 
#define AR_SERVER_INFO_NEW_FIPS_MODE_INDEX       295 /* int  - updated FIPS Server Mode (true/false) */ 
#define AR_SERVER_INFO_NEW_ENC_LEVEL_INDEX       296 /* int  - updated Encryption AlgorithmLevel (Low/Medium/High) */
#define AR_SERVER_INFO_NEW_ENC_PUB_KEY           297 /* char - updated Public Key Algorithm value */
#define AR_SERVER_INFO_CUR_ENC_PUB_KEY           298 /* char - Active Public Key Algorithm value */
#define AR_SERVER_INFO_NEW_ENC_PUB_KEY_INDEX     299 /* int  - updated Public Key enumerated value */
                                                     /*        0=RSA 512-bit, 1=RSA 1024-bit, 2=RSA 2048-bit */
#define AR_SERVER_INFO_CURRENT_ENC_SEC_POLICY    300 /* char - Active Encryption Security Policy value */
#define AR_SERVER_INFO_ENC_LIBRARY_LEVEL         301 /* int  - Encryption Library Level (0=Standard/1=Performance/2=Premium) */
#define AR_SERVER_INFO_NEW_FIPS_ALG              302 /* int  - updated FIPS Premium Data Encryption Algorithm value */
#define AR_SERVER_INFO_FIPS_ALG                  303 /* char - updated FIPS Performance Data Encryption Algorithm value */
#define AR_SERVER_INFO_FIPS_PUB_KEY              304 /* char - updated FIPS Performance Public Key Algorithm value */
#define AR_SERVER_INFO_WFD_QUEUES                305 /* int  - list of debug queues */
#define AR_SERVER_INFO_VERCNTL_OBJ_MOD_LOG_MODE  306 /* int  - 0 - not disabled, 10 enabled */
#define AR_SERVER_INFO_MAX_RECURSION_LEVEL       307 /* int  - max depth for the hierarchical query */
#define AR_SERVER_INFO_FT_SERVER_NAME            308 /* char - hostname for FT search server */
#define AR_SERVER_INFO_FT_SERVER_PORT            309 /* int  - TCP PORT for FT search server */
#define AR_SERVER_INFO_DISABLE_AUDIT_ONLY_CHANGED_FIELDS  310 /* int 0 - Audit only records having changed field values */
                                                              /*     1 - Audit all records */ 
#define AR_SERVER_INFO_VERCNTL_OBJ_MOD_LOG_SAVE_DEF       311 /* int  - 0 - invalid, 10 - save definition files, 20 - do not save definition files */
#define AR_SERVER_INFO_SG_AIE_STATE              312 /* int  - 0 - no server group  */
                                                     /*            or not managed   */
                                                     /*        1 - suspended        */
                                                     /*        2 - resumed          */
#define AR_SERVER_INFO_MAX_VENDOR_TEMP_TABLES    313 /* int - default value for the maximum number of */
                                                     /*  temp tables to be created for a vendor form. */
#define AR_SERVER_INFO_DSO_LOG_LEVEL             314 /* int - DSO log level */
#define AR_SERVER_INFO_DS_PENDING_ERR            315 /* char - name of DSO pending error schema */
#define AR_SERVER_INFO_REGISTRY_LOCATION         316 /* char - location of registry */
#define AR_SERVER_INFO_REGISTRY_USER             317 /* char - registry admin user  */
#define AR_SERVER_INFO_REGISTRY_PASSWORD         318 /* char - registry admin password */
#define AR_SERVER_INFO_DSO_LOG_ERR_FORM          319 /* int  - 0 - do not log errors to DSO Pending Errors form */
                                                     /*        1 - log errors        */
#define AR_SERVER_INFO_ARSIGNALD_LOG_FILE        320 /* char  - name of arsignald log file    */
#define AR_SERVER_INFO_FIRE_ESCALATIONS          321 /* char - informs the server admin plugin to fire registry update escalations */
#define AR_SERVER_INFO_PRELOAD_NUM_THREADS       322 /* int - no. preload threads to run */
#define AR_SERVER_INFO_PRELOAD_NUM_SCHEMA_SEGS   323 /* int - no. schema segments to share among preload threads */
#define AR_SERVER_INFO_PRELOAD_THREAD_INIT_ONLY  324 /* int - 0 run preload threads on every InitializeServerCache */
                                                     /*       1 run preload threads only during init */
#define AR_SERVER_INFO_REG_ENDPOINT_CACHE_FLUSH  325 /* int - 0 do not flush              */
                                                     /*       1 flush endpoint URL cache. */
#define AR_SERVER_INFO_CREATE_WKFLW_PLACEHOLDER  326 /* int 0 - don't create placeholders when importing shared  */
                                                     /*         workflow */
                                                     /* int 1 - create placeholder when importing shared workflow */
                                                     /*         when form is missing */

/* Relevancy Weights for the three predefined fields used in multiform FTS Search 
   Their values could be floats between 0-2. 
     * Range of 1-2 for boosting e.g. 1.5, 1.2 etc 
     * and 0-1 for decreasing boost e.g .1
*/
#define AR_SERVER_INFO_MFS_TITLE_FIELD_WEIGHT         327
#define AR_SERVER_INFO_MFS_ENVIRONMENT_FIELD_WEIGHT   328
#define AR_SERVER_INFO_MFS_KEYWORDS_FIELD_WEIGHT      329
#define AR_SERVER_INFO_COPY_CACHE_LOGGING        330  /* int; log copycache to thread log */
#define AR_SERVER_INFO_DSO_SUPPRESS_NO_SUCH_ENTRY_FOR_DELETE  331 /* int - Suppresses no such entry */
                                                                  /*  warning on DSO delete        */
#define AR_SERVER_INFO_USE_FTS_IN_WORKFLOW       332 /* int 0 - do not use FTS in   */
                                                     /*  workflow                   */
                                                     /* int 1 - use FTS in workflow */
                                                     /*  (default)                  */
#define AR_SERVER_INFO_MAX_ATTACH_SIZE           333 /* The maximum size (in bytes) allowed for attachments for any */
                                                     /* database.*/
#define AR_SERVER_INFO_DISABLE_ARSIGNALS         334 /* int  - 0 - not disabled, else enforced */
#define AR_SERVER_INFO_FT_SEARCH_THRESHOLD       335 /* int  - full text search maximum number of */
                                                     /*  results returned by search engine        */

#define AR_SERVER_INFO_REQ_FIELD_IDENTIFIER           336 /* char - any ascii char like '*' which marks the field as required */
#define AR_SERVER_INFO_REQ_FIELD_IDENTIFIER_LOCATION  337 /* int - 0 front of label */
                                                          /*     - 1 back of label  */
#define AR_SERVER_INFO_FT_SIGNAL_DELAY           338 /* int - number of seconds before */
                                                     /*  sending ft indexing needed    */
                                                     /*  signal in a server group      */
#define AR_SERVER_INFO_ATRIUM_SSO_AUTHENTICATION 339 /* authenticate users with atrium sso(TRUE/FALSE) */
                                                     /* Default is FALSE            */
#define AR_SERVER_INFO_OVERLAY_MODE              340
#define AR_SERVER_INFO_FT_FORM_REINDEX           341 /* char - names of forms to reindex on input and names  */
                                                     /*        of forms pending indexing on output separated */
                                                     /*        by AR_FULL_TEXT_FORM_REINDEX_SEPARATOR        */
#define AR_SERVER_INFO_DS_LOGICAL_MAPPING        342 /* char - name of DSO logical mapping schema */
#define AR_SERVER_INFO_DB_CONNECTION_TIMEOUT     343 /* int - SQL Server DB conn timeout in Seconds */
#define AR_SERVER_INFO_ATRIUMSSO_LOCATION        344 /* char - location of Atrium SSO Server */
#define AR_SERVER_INFO_ATRIUMSSO_USER            345 /* char - Atrium SSO admin user */
#define AR_SERVER_INFO_ATRIUMSSO_PASSWORD        346 /* char - Atrium SSO admin password */
#define AR_SERVER_INFO_SUPPRESS_DOMAIN_IN_URL    347 /* int - 1 == suppress else don't, defaults to 0 */
#define AR_SERVER_INFO_RESTART_PLUGIN            348 /* int - used to signal plugin server forced restart */
#define AR_SERVER_INFO_USE_PROMPT_BAR_FOR        349 /* int - used to update "System Messages Displayed" */
#define AR_SERVER_INFO_ATRIUMSSO_KEYSTORE_PATH   350 /* char - location of the Atrium SSO keystore */
#define AR_SERVER_INFO_ATRIUMSSO_KEYSTORE_PASSWORD  351 /* char - Atrium SSO keystore password */
#define AR_SERVER_INFO_MAX_LOG_HISTORY           352 /* int - Number of log instances */
#define AR_SERVER_INFO_SUPRESS_LOGOFF_SIGNALS    353 /* int - 0 - disabled, else suppressed */
#define AR_SERVER_INFO_DB_FUNCTIONAL_INDEX       354 /* int - 0 -  don't create functional index (default) */
                                                     /*       1 -  create functional index                 */
                                                     /* NOTE: Only valid for oracle database               */
#define AR_SERVER_INFO_UPGRADE_MODE              355 /* int - Set upgrade mode */
#define AR_SERVER_INFO_UPGRADE_RESERVED          356 /* int - RESERVED for future use */
#define AR_SERVER_INFO_UPGRADE_ADMIN_USER        357 /* char - Secondary install admin user */
#define AR_SERVER_INFO_UPGRADE_DUAL_DATA_FORMS   358 /* char - Upgrade Data Form list */


/* Server Info Constants 358-379 have been defined in Boulder */
#define AR_SERVER_INFO_API_MONITORING_UPDATE_INTERVAL    380      /* int - Update Interval for API Monitoring */
#define  AR_SERVER_INFO_API_RECORDING_CLIENT_TYPE        381      /* String - API Recording on for specific Client Type */
#define  AR_SERVER_INFO_API_RECORDING_ENABLE             382      /* int - Enable Flag would be set to T or F */

/* Server Info Constants for collab app defined in Boulder */
#define AR_SERVER_INFO_OBJ_RESERVATION_REPOSITORY_TYPE 383 /* int Object reservation repository type - 0  ARS      */
                                                           /*                                        - 10 External */

/* Server Info Constants for API and SQL timing statistics */
#define AR_SERVER_INFO_STATS_APISQL_CONTROL      384 /* bitmask  Controls API and SQL recording */
#define AR_SERVER_INFO_STATS_APISQL_MAX_SAVED    386 /* int  Capacity for saving longest operations in memory */
#define AR_SERVER_INFO_STATS_APISQL_INTERVAL     387 /* int  Frequency of stats flush - in minutes (zero means no flush) */
#define AR_SERVER_INFO_STATS_APISQL_MIN_TIME     388 /* int  Minimum elapsed time to qualify for recording (mSec) */
#define AR_SERVER_INFO_STATS_GET_INCOMPLETE_API  389 /* char  Retrieves contents of incomplete API table */
#define AR_SERVER_INFO_STATS_GET_LONGEST_API     390 /* char  Retrieves contents of longest API table */
#define AR_SERVER_INFO_STATS_GET_INCOMPLETE_SQL  391 /* char  Retrieves contents of incomplete SQL table */
#define AR_SERVER_INFO_STATS_GET_LONGEST_SQL     392 /* char  Retrieves contents of longest SQL table */
/* Server Info Constants for Attachment Security */
#define AR_SERVER_INFO_ATTACH_EXT_FILTER         393 /* int  Attachment extension filter */
#define AR_SERVER_INFO_ATTACH_EXT_LIST           394 /* char List of extensions for attachment filter defined in above */
#define AR_SERVER_INFO_ATTACH_EXCEPTION_LIST     395 /* char List of form-field pairs for which attachment validation is exempt */
#define AR_SERVER_INFO_ATTACH_DISPLAY_FILTER     396 /* int  Display filter */
#define AR_SERVER_INFO_ATTACH_DISPLAY_LIST       397 /* char List of extensions for display filter defined in above */
#define AR_SERVER_INFO_ATTACH_VALIDATION_PLUGIN_NAME 398 /* char Name of custom attachment validation plugin */
#define AR_SERVER_INFO_ATTACH_SYSTEM_EXCEPTION_LIST     401 /* char List of system form-field pairs for which attachment validation is exempt */
#define AR_SERVER_INFO_SSO_CONFIRM_PASSWORD_PLUGIN_NAME 402 /* char name of filterapi plugin for SSO password confirmation */

#define AR_MAX_SERVER_INFO_USED                  402 /* set "highest" server info */ 

/* Values for license tracking var */
#define TRACK_LICENSE_USAGE_DISABLED         0     /* Disabled */
#define TRACK_LICENSE_USAGE_WRITE            1     /* Write licenses only (float and fixed) */
#define TRACK_LICENSE_USAGE_ALL              2     /* All licenses (including READ and READ_RESTRICTED) */

/* Typical values that can be set to upgrade mode (AR_SERVER_INFO_UPGRADE_MODE) during app upgrade */
#define NORMAL_TO_INPROCESS_UPGRADE_MODE     5     /* Switch from Normal (production) mode to InProcess */
#define INPROCESS_TO_COMPLETE_UPGRADE_MODE   6     /* Switch from InProcess to Complete */
#define COMPLETE_TO_NORMAL_UPGRADE_MODE      3     /* Switch from Complete to Normal */
/* If something goes wrong during InProcess, set this value to roll back */
#define ROLLBACK_INPROCESS_TO_NORMAL_UPGRADE_MODE 4 /* Rollback from InProcess to Normal */
/* Internally generated values that can not be set, but can be read */
#define UPGRADE_MODE_NORMAL_OPERATION        0     /* Normal or production mode */
#define UPGRADE_MODE_INPROCESS               1     /* Change to "Upgrade InProcess" mode is in progress */
#define UPGRADE_MODE_COMPLETED               2     /* Change from InProcess to Complete mode is in progress */

#define AR_DEBUG_SERVER_NONE            0 /* debug flag is OFF */
#define AR_DEBUG_SERVER_SQL             1 /* debug flag for SQL debugging */
#define AR_DEBUG_SERVER_FILTER     (1<<1) /* debug flag for filter debugging */
#define AR_DEBUG_SERVER_USER       (1<<2) /* debug flag for user debugging */
#define AR_DEBUG_SERVER_ESCALATION (1<<3) /* debug flag for escalation debugging */
#define AR_DEBUG_SERVER_API        (1<<4) /* debug flag for api debugging */
#define AR_DEBUG_THREAD            (1<<5) /* debug flag for thread debugging */
#define AR_DEBUG_SERVER_ALERT      (1<<6) /* debug flag for alert debugging */
#define AR_DEBUG_SERVER_ARFORK     (1<<7) /* debug flag for arforkd debugging */
#define AR_DEBUG_SERVER_SERVGROUP  (1<<8) /* debug flag for server group debugging */
#define AR_DEBUG_SERVER_FTINDEXER  (1<<9) /* debug flag for FT indexer debugging */
#define AR_DEBUG_SERVER_DISTRIB   (1<<15) /* debug flag for distrib server debugging */
#define AR_DEBUG_SERVER_APPROVAL  (1<<16) /* debug flag for approval server debugging */
#define AR_DEBUG_SERVER_PLUGIN    (1<<17) /* debug flag for plug-in server debugging */
#define AR_DEBUG_SERVER_EXTLOG    (1<<18) /* debug flag for enabling external logging */
#define AR_DEBUG_SERVER_CHECKDB   (1<<19) /* debug flag for db consistency checker */
#define AR_DEBUG_SERVER_ARSIGNALD (1<<20) /* debug flag for arsignal daemon */

#define NUM_DEBUG_FLAGS                15 /* total number of debug flags,        */
 
                                          /* should be updated for any new flag  */

                                          /* Debug types for files written by the AR  */
                                          /* as opposed to those written by companion */
                                          /* servers. Used to initialize an array of  */
                                          /* server debug types.                      */
#define AR_SERVER_DEBUG_TYPES    AR_DEBUG_SERVER_SQL, \
                                 AR_DEBUG_SERVER_FILTER, \
                                 AR_DEBUG_SERVER_USER, \
                                 AR_DEBUG_SERVER_ESCALATION, \
                                 AR_DEBUG_SERVER_API, \
                                 AR_DEBUG_THREAD, \
                                 AR_DEBUG_SERVER_ALERT, \
                                 AR_DEBUG_SERVER_SERVGROUP, \
                                 AR_DEBUG_SERVER_FTINDEXER

#define NUM_SERVER_DEBUG_TYPES         9  /* Number of types above */

                                          /* Types of files for which each thread can */
                                          /* log to its own file.                     */
#define PER_THREAD_LOG_TYPES (AR_DEBUG_SERVER_SQL | \
                              AR_DEBUG_SERVER_FILTER | \
                              AR_DEBUG_SERVER_USER | \
                              AR_DEBUG_SERVER_ESCALATION | \
                              AR_DEBUG_SERVER_API | \
                              AR_DEBUG_SERVER_ALERT | \
                              AR_DEBUG_SERVER_FTINDEXER )

/* flag to log in forms */
#define AR_LOG_TO_FORM_NONE            0 /* flag is OFF; implies log everything to file. */
#define AR_LOG_TO_FORM_SQL             1 /* flag for SQL logging to form */
#define AR_LOG_TO_FORM_FILTER     (1<<1) /* flag for filter logging to form */
#define AR_LOG_TO_FORM_USER       (1<<2) /* flag for user logging to form */
#define AR_LOG_TO_FORM_ESCALATION (1<<3) /* flag for escalation logging to form */
#define AR_LOG_TO_FORM_API        (1<<4) /* flag for api logging to form */
#define AR_LOG_TO_FORM_THREAD     (1<<5) /* flag for thread logging to form */
#define AR_LOG_TO_FORM_ALERT      (1<<6) /* flag for alert logging to form */
#define AR_LOG_TO_FORM_SERVGROUP  (1<<8) /* flag for server group logging to form */
#define AR_LOG_TO_FORM_FTINDEXER  (1<<9) /* flag for FT indexer logging to form */


/* Log level for plug-in logging */
#define AR_PLUGIN_LOG_OFF       10000
#define AR_PLUGIN_LOG_SEVERE    1000
#define AR_PLUGIN_LOG_WARNING   900
#define AR_PLUGIN_LOG_INFO      800
#define AR_PLUGIN_LOG_CONFIG    700
#define AR_PLUGIN_LOG_FINE      600
#define AR_PLUGIN_LOG_FINER     500
#define AR_PLUGIN_LOG_FINEST    400
#define AR_PLUGIN_LOG_ALL       100

#define AR_SUBMITTER_MODE_LOCKED      1 /* submitter locked at create */
#define AR_SUBMITTER_MODE_CHANGEABLE  2 /* submitter changeable after create */

#define AR_SAVE_LOGIN_USER_OPTION     0 /* let user define whether to save */
#define AR_SAVE_LOGIN_ADMIN_SAVE      1 /* admin override, force saving */
#define AR_SAVE_LOGIN_ADMIN_NO_SAVE   2 /* admin override, force NO saving */

#define AR_SYS_MSG_DISP_NOTE_AND_WARN 0 /* display only note and warning in prompt-bar*/
#define AR_SYS_MSG_DISP_ALL           1 /* display all messages in prompt-bar */
#define AR_SYS_MSG_DISP_NONE          2 /* no messages displayed in prompt-bar, every message as pop-up */

#define AR_CASE_SENSITIVE_UNKNOWN    -1 /* DB case sensitivity is unknown */
#define AR_CASE_SENSITIVE_YES         0 /* DB is case sensitive */
#define AR_CASE_SENSITIVE_NO          1 /* DB is case INsensitive */

                                        /* tags for preference server options */
#define AR_PREF_SERVER_USER_OPTION           1  /* default - use of preference server is determined by user */
#define AR_PREF_SERVER_USE_THIS_SERVER       2  /* Use of pref server is required and this server is available */
#define AR_PREF_SERVER_USE_NOT_THIS_SERVER   3  /* Use of pref server is required and this server is NOT available */

                                        /* tags for server stats operations */
/* NOTE: All of the integer values that are counts or total numbers start at */
/*       0 and increase during the running of the server.  They are all      */
/*       long values.  If they hit the maximum allowed in a long, they will  */
/*       wrap around to 0 again.                                             */
/* NOTE: All time values are in 1/100ths of a second                         */
#define AR_SERVER_STAT_START_TIME      1/*    long - start time of the server */
#define AR_SERVER_STAT_BAD_PASSWORD    2/*    long - num logins w/ bad passwd */
#define AR_SERVER_STAT_NO_WRITE_TOKEN  3/*    long - num logins where was no  */
                                        /*           free floating write token*/
#define AR_SERVER_STAT_NO_FULL_TOKEN   4/*    long - num logins where was no  */
                                        /*           free floating write token*/
#define AR_SERVER_STAT_CURRENT_USERS   5/*    long - num current users        */
#define AR_SERVER_STAT_WRITE_FIXED     6/*    long - num write fixed users    */
#define AR_SERVER_STAT_WRITE_FLOATING  7/*    long - num write floating users */
#define AR_SERVER_STAT_WRITE_READ      8/*    long - num write read-only users*/
#define AR_SERVER_STAT_FULL_FIXED      9/*    long - num fulltext fixed users */
#define AR_SERVER_STAT_FULL_FLOATING  10/*    long - num fulltext float users */
#define AR_SERVER_STAT_FULL_NONE      11/*    long - num fulltext none users  */
#define AR_SERVER_STAT_API_REQUESTS   12/*    long - num API requests         */
#define AR_SERVER_STAT_API_TIME       13/*    long - time in API calls        */
#define AR_SERVER_STAT_ENTRY_TIME     14/*    long - time in "entry" calls    */
#define AR_SERVER_STAT_RESTRUCT_TIME  15/*    long - time in "restructure"    */
#define AR_SERVER_STAT_OTHER_TIME     16/*    long - time in calls that       */
                                        /*           aren't entry/restructure */
#define AR_SERVER_STAT_CACHE_TIME     17/*    long - time loading/reloading   */
                                        /*           the server process cache */
#define AR_SERVER_STAT_GET_E_COUNT    18/*    long - num calls ARGetEntry     */
#define AR_SERVER_STAT_GET_E_TIME     19/*    long - time in ARGetEntry       */
#define AR_SERVER_STAT_SET_E_COUNT    20/*    long - num calls ARSetEntry     */
#define AR_SERVER_STAT_SET_E_TIME     21/*    long - time in ARSetEntry       */
#define AR_SERVER_STAT_CREATE_E_COUNT 22/*    long - num calls ARCreateEntry  */
#define AR_SERVER_STAT_CREATE_E_TIME  23/*    long - time in ARCreateEntry    */
#define AR_SERVER_STAT_DELETE_E_COUNT 24/*    long - num calls ARDeleteEntry  */
#define AR_SERVER_STAT_DELETE_E_TIME  25/*    long - time in ARDeleteEntry    */
#define AR_SERVER_STAT_MERGE_E_COUNT  26/*    long - num calls ARMergeEntry   */
#define AR_SERVER_STAT_MERGE_E_TIME   27/*    long - time in ARMergeEntry     */
#define AR_SERVER_STAT_GETLIST_E_COUNT 28/*   long - num calls ARGetListEntry */
#define AR_SERVER_STAT_GETLIST_E_TIME 29/*    long - time in ARGetListEntry   */
#define AR_SERVER_STAT_E_STATS_COUNT  30/*    long - num calls AREntryStatisti*/
#define AR_SERVER_STAT_E_STATS_TIME   31/*    long - time in AREntryStatistics*/
#define AR_SERVER_STAT_FILTER_PASSED  32/*    long - num filters executed     */
#define AR_SERVER_STAT_FILTER_FAILED  33/*    long - num filters where qualify*/
                                        /*           check failed             */
#define AR_SERVER_STAT_FILTER_DISABLE 34/*    long - num filters checked that */
                                        /*           were marked disabled     */
#define AR_SERVER_STAT_FILTER_NOTIFY  35/*    long - num filters notify action*/
#define AR_SERVER_STAT_FILTER_MESSAGE 36/*    long - num filters message actio*/
#define AR_SERVER_STAT_FILTER_LOG     37/*    long - num filters log action   */
#define AR_SERVER_STAT_FILTER_FIELDS  38/*    long - num filters set fields action*/
#define AR_SERVER_STAT_FILTER_PROCESS 39/*    long - num filters process actio*/
#define AR_SERVER_STAT_FILTER_TIME    40/*    long - time spent during        */
                                        /*           filter processing        */
#define AR_SERVER_STAT_ESCL_PASSED    41/*    long - num escls executed       */
#define AR_SERVER_STAT_ESCL_FAILED    42/*    long - num escls where qualify  */
                                        /*           check failed             */
#define AR_SERVER_STAT_ESCL_DISABLE   43/*    long - num escls checked that   */
                                        /*           were marked disabled     */
#define AR_SERVER_STAT_ESCL_NOTIFY    44/*    long - num escls notify action  */
#define AR_SERVER_STAT_ESCL_LOG       45/*    long - num escls log action     */
#define AR_SERVER_STAT_ESCL_FIELDS    46/*    long - num escls fields action  */
#define AR_SERVER_STAT_ESCL_PROCESS   47/*    long - num escls process action */
#define AR_SERVER_STAT_ESCL_TIME      48/*    long - time spent during        */
                                        /*           escalation processing    */
#define AR_SERVER_STAT_TIMES_BLOCKED  49/*    long - number of times a request*/
                                        /*           was temporarily blocked  */
#define AR_SERVER_STAT_NUMBER_BLOCKED 50/*    long - number of items that were*/
                                        /*           blocked at end of a call */
#define AR_SERVER_STAT_CPU            51/*    long - total CPU time used by   */
                                        /*           the server process       */
#define AR_SERVER_STAT_SQL_DB_COUNT   52/*    long - num DB commands issued   */
#define AR_SERVER_STAT_SQL_DB_TIME    53/*    long - time spend DB operations */
#define AR_SERVER_STAT_FTS_SRCH_COUNT 54/*    long - num FTS search operations*/
#define AR_SERVER_STAT_FTS_SRCH_TIME  55/*    long - time spent in FTS search */
#define AR_SERVER_STAT_SINCE_START    56/*    long - time from start time     */
#define AR_SERVER_STAT_IDLE_TIME      57/*    long - idle time between calls  */
#define AR_SERVER_STAT_NET_RESP_TIME  58/*    long - time spent on network    */
                                        /*           sending resp. to API call*/
#define AR_SERVER_STAT_FILTER_FIELDP  59/*    long - num filters push actions */
#define AR_SERVER_STAT_ESCL_FIELDP    60/*    long - num escls push actions   */
#define AR_SERVER_STAT_FILTER_SQL     61/*    long - num filters sql actions  */
#define AR_SERVER_STAT_ESCL_SQL       62/*    long - num escls sql actions    */
#define AR_SERVER_STAT_NUM_THREADS    63/*    long - num threads in queue     */
#define AR_SERVER_STAT_FILTER_GOTO_ACTION 64/*long - num filter goto actions  */
#define AR_SERVER_STAT_FILTER_CALL_GUIDE  65/*long - num filter call guide act*/
#define AR_SERVER_STAT_FILTER_EXIT_GUIDE  66/*long - num filter exit actions  */
#define AR_SERVER_STAT_FILTER_GOTO_GUIDE_LB 67/*long-num filter goto guide    */
                                              /*     label actions            */
#define AR_SERVER_STAT_FILTER_FIELDS_SQL  68/*long - num filter set fields -  */
                                            /*       sql actions              */
#define AR_SERVER_STAT_FILTER_FIELDS_PROCESS 69/*long - num filter set fields */
                                               /*     - process actions       */
#define AR_SERVER_STAT_FILTER_FIELDS_FLTAPI 70/*long - num filter set fields  */
                                              /*     - filter api actions     */
#define AR_SERVER_STAT_ESCL_FIELDS_SQL    71/*long - num escl set fields -    */
                                            /*       sql actions              */
#define AR_SERVER_STAT_ESCL_FIELDS_PROCESS 72/*long- num escl set fields -    */
                                             /*      process actions          */
#define AR_SERVER_STAT_ESCL_FIELDS_FLTAPI 73/*long - num escl set fields -    */
                                            /*       filter api actions       */
#define AR_SERVER_STAT_WRITE_RESTRICTED_READ 74/*long - num write restricted  */
                                               /*       read users            */
#define AR_SERVER_STAT_NUM_CACHES     75/*    long - active caches            */
#define AR_SERVER_STAT_MAX_CACHES     76/*    long - max active caches        */

#define AR_MAX_SERVER_STAT_USED           76/* set to code for "highest" serv stat*/

typedef struct ARServerInfoRequestList
{               /* list of server info to get */
   unsigned int   numItems;
   unsigned int  *requestList;

}  ARServerInfoRequestList;

typedef struct ARServerInfoStruct
{               /* operation type and data */
   unsigned int    operation;
   ARValueStruct   value;

}  ARServerInfoStruct;

typedef struct ARServerInfoList
{               /* list of 0 or more server info item entries */
   unsigned int         numItems;
   ARServerInfoStruct  *serverInfoList;

}  ARServerInfoList;

/* full text declarations */

#define AR_FULLTEXT_REINDEX        1  /* If reindexing set the valuestruct to */
                                      /* this value.  When doing a get, a 1   */
                                      /* will be returned for this info type  */
                                      /* if a reindex is in progress,         */
                                      /* otherwise a 0 will be returned.      */

#define AR_FULL_TEXT_SEARCH_CASE_SENSITIVE   0
#define AR_FULL_TEXT_SEARCH_CASE_INSENSITIVE 1

#define AR_FULL_TEXT_DISABLE_SEARCHING       0  /* turn full text searching off */
#define AR_FULL_TEXT_ENABLE_SEARCHING        1  /* turn full text searching on */

#define AR_FULLTEXT_FTS_MATCH_FORCE_L_T_WILD 0 /* force leading & trailing */
                                               /*  wildcards               */
#define AR_FULLTEXT_FTS_MATCH_FORCE_T_WILD   1 /* force trailing wildcards */
#define AR_FULLTEXT_FTS_MATCH_IGNORE_L_WILD  2 /* ignore leading wildcards */
#define AR_FULLTEXT_FTS_MATCH_REMOVE_WILD    3 /* remove all wildcards */
#define AR_FULLTEXT_FTS_MATCH_UNCHANGED      4 /* query unchanged */

#define AR_FULL_TEXT_FORM_REINDEX_SEPARATOR  '\f' /* separator in form reindex list for */
                                                  /* AR_SERVER_INFO_FT_FORM_REINDEX     */

                /* the following full text info definitions have been deprecated */
                                               /* tags for full text requests */
#define AR_FULLTEXTINFO_COLLECTION_DIR       1 /* Indexing collection directory */
#define AR_FULLTEXTINFO_STOPWORD             2 /* Stop words */
#define AR_FULLTEXTINFO_REINDEX              3 /* Reindex the collection */
#define AR_FULLTEXTINFO_CASE_SENSITIVE_SRCH  4 /* Case-sensitivity option */
#define AR_FULLTEXTINFO_STATE                5 /* Searching enabled or disabled */
#define AR_FULLTEXTINFO_FTS_MATCH_OP         6 /* Search match option */
#define AR_FULLTEXTINFO_HOMEDIR              7 /* Obsolete */
#define AR_FULLTEXTINFO_DEBUG                8 /* Obsolete */
#define AR_FULLTEXTINFO_TEMP_DIR             9 /* Indexing temp directory */

#define AR_MAX_FULLTEXT_INFO_USED            9 /* Code for "highest" FT info */

                /* the following full text case definitions have been deprecated */
#define AR_CASE_SENSITIVE_SEARCH             AR_FULL_TEXT_SEARCH_CASE_SENSITIVE
#define AR_CASE_INSENSITIVE_SEARCH           AR_FULL_TEXT_SEARCH_CASE_INSENSITIVE

                /* the following full text state definitions have been deprecated */
#define AR_FULLTEXT_STATE_OFF                AR_FULL_TEXT_DISABLE_SEARCHING
#define AR_FULLTEXT_STATE_ON                 AR_FULL_TEXT_ENABLE_SEARCHING

                /* the following full text structure definitions have been deprecated */
typedef struct ARFullTextInfoRequestList
{               /* list of full text info to get */
   unsigned int   numItems;
   unsigned int  *requestList;

}  ARFullTextInfoRequestList;

typedef struct ARFullTextInfoStruct
{               /* info type and data */
   unsigned int  infoType;
   union
   {
      ARValueList     valueList;  /* list of stop words */
      ARValueStruct   value;      /* collection dir, case srch, */
                                  /*  reindex, ft state, match  */
                                  /*  option, temp dir          */
   } u;

}  ARFullTextInfoStruct;

typedef struct ARFullTextInfoList
{               /* list of full text info item entries */
   unsigned int           numItems;
   ARFullTextInfoStruct  *fullTextInfoList;

}  ARFullTextInfoList;


/* Structures used in the Decode operations to convert the internal form */
/* of structured character strings into structures that are more easily  */
/* managed by the caller.                                                */

typedef struct ARStatusHistoryStruct
{               /* label of state and user/time of last set */
   ARAccessNameType   user;
   ARTimestamp        timeVal;

}  ARStatusHistoryStruct;

typedef struct ARStatusHistoryList
{               /* decoded status history */
   unsigned int            numItems;
   ARStatusHistoryStruct  *statHistList;

}  ARStatusHistoryList;

typedef struct ARDiaryStruct
{               /* user/time/text of entry */
   ARAccessNameType   user;
   ARTimestamp        timeVal;
   char              *value;

}  ARDiaryStruct;

typedef struct ARDiaryList
{               /* decoded diary text */
   unsigned int    numItems;
   ARDiaryStruct  *diaryList;

}  ARDiaryList;

/* Structure used in defining escalation firing time */
/* Bit 0 to 30 of 'monthday' represents day 1 to 31 of a month.       */
/* Bit 0 to  6 of 'weekday'  represents sunday to saturday of a week. */
/* Bit 0 to 23 of 'hourmask' represents hour 0 to 23 of a day.        */

#define AR_DAY(x, y)              (((x) >> (y)) & 0x1)
#define AR_HOUR(x, y)             (((x) >> (y)) & 0x1)
#define AR_SETDAY(x)              (1 << x)
#define AR_SETHOUR(x)             (1 << x)
#define AR_HOUR_A_DAY             24
#define AR_TIMEMARK_ALL           -1
#define AR_TIMEMARK_NOTFOUND      -1
#define AR_TIMEMARK_END_OF_MONTH  31


#define AR_ESCALATION_TYPE_INTERVAL   1 /* codes for types of escalation time */
#define AR_ESCALATION_TYPE_TIMEMARK   2

typedef struct AREscalationTmStruct
{
   unsigned int   escalationTmType;   /* interval or timemark */
   union
   {
      ARLong32      interval;   /* time in seconds */
      ARDayStruct   date;       /* escalation fire date */
   } u;

}  AREscalationTmStruct;

typedef struct AREscalationTmList
{               /* list of 0 or more escalation times */
   unsigned int           numItems;
   AREscalationTmStruct  *escalationTmList;

}  AREscalationTmList;


#define AR_LONGVALUE_TYPE_HELPTEXT    1  /* help text */
#define AR_LONGVALUE_TYPE_CHANGEDIARY 2  /* change diary */


#define AR_FIELD_NONE         0  /* null field */
#define AR_FIELD_REGULAR      1  /* field of regular schema */
#define AR_FIELD_JOIN         2  /* field of join schema */
#define AR_FIELD_VIEW         3  /* field of view schema */
#define AR_FIELD_VENDOR       4  /* field of vendor schema */
#define AR_FIELD_INHERITANCE  5  /* field of inheritance type */

#define AR_FIELD_CLEAN_DELETE 0  /* default field delete option */
                                 /* delete field only when there is no */
                                 /* dependency and there is no data */
#define AR_FIELD_DATA_DELETE  1  /* delete field even there is data */
                                 /* only applicable for regular schema */
#define AR_FIELD_FORCE_DELETE 2  /* delete field cascade */
                                 /* delete all invalid delete fields and */
                                 /* schemas, override DATA_DELETE */

#define AR_FIELD_MAPPING_PRIMARY   0  /* primary join member schema */
#define AR_FIELD_MAPPING_SECONDARY 1  /* secondary join member schema */

typedef struct ARJoinMappingStruct
{
   unsigned int   schemaIndex;   /* 0 - primary, 1 - secondary */
   ARInternalId   realId;        /* field id of member schema */

}  ARJoinMappingStruct;

typedef struct ARViewMappingStruct
{
   ARNameType   fieldName;       /* field name of external table */

}  ARViewMappingStruct;

typedef struct ARVendorMappingStruct
{
   ARNameType   fieldName;       /* field name in external table */

}  ARVendorMappingStruct;

typedef struct ARInheritanceMappingStruct
{
   ARNameType     srcSchema;     /* NULL means this is not a */
                                 /*  reference field         */
   unsigned int   referenceMask; /* a bitmask indicates which */
                                 /*  field characteristics    */
                                 /*  are inherited. For each  */
                                 /*  bit, 1 means it is       */
                                 /*  inherited, 0 means it is */
                                 /*  overwritten.  This only  */
                                 /*  has meaning if srcSchema */
                                 /*  is not an empty string   */
   unsigned int   dataMappingId; /* 0 means field doesn't */
                                 /*  reference DATA       */
}  ARInheritanceMappingStruct;


typedef struct ARFieldMappingStruct
{
   unsigned int   fieldType;
   union
   {
      ARJoinMappingStruct          join;
      ARViewMappingStruct          view;
      ARVendorMappingStruct        vendor;
      ARInheritanceMappingStruct   inheritance;
   } u;

}  ARFieldMappingStruct;

typedef struct ARFieldMappingList
{               /* list of 0 or more field mappings */
   unsigned int           numItems;
   ARFieldMappingStruct  *mappingList;

}  ARFieldMappingList;

typedef struct ARFieldMappingPtrList
{               /* list of 0 or more field mapping pointers */
   unsigned int           numItems;
   ARFieldMappingStruct **mappingPtrList;

}  ARFieldMappingPtrList;

#define AR_SCHEMA_NONE       0  /* null schema */
#define AR_SCHEMA_REGULAR    1  /* regular schema */
#define AR_SCHEMA_JOIN       2  /* join schema, has two member schemas */
#define AR_SCHEMA_VIEW       3  /* view schema, has one base schema */
#define AR_SCHEMA_DIALOG     4  /* dialog schema, only display-only fields */
#define AR_SCHEMA_VENDOR     5  /* vendor schema */
#define AR_SCHEMA_PLACEHOLDER    6  /* placeholder schema */
#define AR_SCHEMA_MAX_SCHEMA_TYPE   6  /* list the max type of schema */

#define AR_LIST_SCHEMA_ALL                  0  /* get list of all schemas */
#define AR_LIST_SCHEMA_REGULAR              1  /* get list of all regular schemas */
#define AR_LIST_SCHEMA_JOIN                 2  /* get list of all join schemas */
#define AR_LIST_SCHEMA_VIEW                 3  /* get list of all view schemas */
#define AR_LIST_SCHEMA_UPLINK               4  /* get list of all schemas depending */
                                               /*  on given schema                  */
#define AR_LIST_SCHEMA_DOWNLINK             5  /* get list of all schemas the given */
                                               /*  schema bases on                  */
#define AR_LIST_SCHEMA_DIALOG               6  /* get list of all dialog schemas */
#define AR_LIST_SCHEMA_ALL_WITH_DATA        7  /* get list of all schemas with */
                                               /* database fields              */
#define AR_LIST_SCHEMA_VENDOR               8  /* get list of all vendor schemas */
#define AR_LIST_SCHEMA_ALLOWED_IN_MFSEARCH  9  /* get list of all schemas allowed */
                                               /*  in multi-form searches         */

#define AR_HIDDEN_INCREMENT   1024  /* code added to above to "include hidden */
                                    /*  schemas" in the list returned         */

#define AR_JOIN_LEVEL_ORDER   2048  /* indicates when returning uplink joins that   */
                                    /* the schemas should be ordered by join level */

#define AR_ATTRIB_NONE          0   /* no attribute and visible attribute */
                                    /* for ARS objects                    */
#define AR_ATTRIB_VISIBLE       AR_ATTRIB_NONE
#define AR_ATTRIB_HIDDEN        1   /* hidden attribute for ARS objects */

                                   /* join schema definition option */
#define AR_JOIN_OPTION_NONE     0  /* no join option */
#define AR_JOIN_OPTION_OUTER    1  /* define the join as outer join */

                                   /* SetEntry option */
#define AR_JOIN_SETOPTION_NONE  0  /* don't enforce join referential */
                                   /* integrity */
#define AR_JOIN_SETOPTION_REF   1  /* enforce join referential integrity */
                                   /* For internal API workflow */
#define ARI_WF_DEFERRED_CREATE_MODE 1  /* bit to modify filter phasing to */
                                       /* enable/disable bulk insert for  */
                                       /* create entries                  */
#define ARI_WF_SETOPTION_OW      1024  /* Overwrite diary field instead   */
                                       /* of appending mode               */

                                   /* DeleteEntry option */
#define AR_JOIN_DELOPTION_NONE  0  /* individual entries will be deleted */
                                   /* only when the entry can be retrieved */
                                   /* through the join schema */
#define AR_JOIN_DELOPTION_FORCE 1  /* delete individual entries even when */
                                   /* the entry cannot be retrieved from */
                                   /* the join schema. Error will be ignored */
                                   /* for those entry pieces that are no */
                                   /* longer existing. */

#define AR_DEFAULT_DELETE_OPTION 0 /* server object default delete option */
                                   /* For locked objects, fails the delete attempt */
                                   /* For schemas, same as AR_SCHEMA_CLEAN_DELETE  */
#define AR_SCHEMA_CLEAN_DELETE   0 /* default schema delete option */
                                   /* delete schema only when there is no */
                                   /* dependency and there is no data in the */
                                   /* schema.(ignored in the case of join */
                                   /* schema) */
#define AR_SCHEMA_DATA_DELETE    1 /* delete schema even there is data */
                                   /* only applicable for regular schema */
#define AR_SCHEMA_FORCE_DELETE   2 /* delete schema even there is dependency */
                                   /* all the invalid schemas will be deleted */
                                   /* this option overrides DATA_DELETE */
#define AR_LOCK_BLOCK_DELETE     4 /* delete the given object and all objects */
                                   /* that are locked with same key */
                                   /* only applicable for locked objects */
#define AR_SCHEMA_SHADOW_DELETE 8  /* delete archive/audit form even if it is enabled */
                                   /* or part of a lock object */


#define AR_SCHEMA_SET_NONE                         0 /* default schema set */
                                                     /*  option            */
#define AR_SCHEMA_SET_DELETE_FIELDS_WITH_MAPPING   1 /* dependant fields should  */
                                                     /*  be removed during field */
                                                     /*  deletion caused by      */
                                                     /*  mapping removal         */
#define AR_SCHEMA_SET_DELETE_CONFLICTING_FIELDS    2 /* indicates if fields with */
                                                     /*  conflicting ids should  */
                                                     /*  be deleted when         */
                                                     /*  establishing schema     */
                                                     /*  inheritance             */

typedef struct ARJoinSchema
{                                   /* join schema specific info */
   ARNameType          memberA;     /* name of member schema A */
   ARNameType          memberB;     /* name of member schema B */
   ARQualifierStruct   joinQual;    /* join qualification */
   unsigned int        option;      /* join option bit mask */

}  ARJoinSchema;

typedef struct ARViewSchema
{                                   /* straight view to an external table*/
   char         tableName[AR_MAX_TABLENAME_SIZE + 1];
   ARNameType   keyField;           /* primary field entryId(C1) maps to */
}  ARViewSchema;

typedef struct ARVendorSchema
{                                   /* external table */
   ARNameType   vendorName;         /* name of vendor */
   char         tableName[AR_MAX_TABLENAME_SIZE + 1];
                                    /* name of "table" in vendor's */
                                    /*    namespace                */
}  ARVendorSchema;

typedef struct ARCompoundSchema
{
   unsigned int      schemaType;
   union
   {
      ARJoinSchema     join;
      ARViewSchema     view;
      ARVendorSchema   vendor;
   } u;

}  ARCompoundSchema;

typedef struct ARCompoundSchemaList
{
   unsigned int       numItems;
   ARCompoundSchema  *compoundSchema;

}  ARCompoundSchemaList;

typedef struct ARDataMappingInfoStruct
{
   unsigned int       id;
   ARNameType         name;
   ARNameType         primaryKeyIndexName;
   ARInternalIdList   foreignKeyFieldIdList;
   unsigned int       opMask;
   unsigned int       readOrder;
   unsigned int       writeOrder;

}  ARDataMappingInfoStruct;

typedef struct ARDataMappingInfoList
{
   unsigned int              numItems;
   ARDataMappingInfoStruct  *dataMappingInfoList;

}  ARDataMappingInfoList;

typedef struct ARSchemaInheritanceStruct
{
   ARNameType              srcSchema;
   ARBoolean               inheritAll;
   unsigned int            dataMappingId;
   ARDataMappingInfoList   dataMappingInfoList;

}  ARSchemaInheritanceStruct;

typedef struct ARSchemaInheritanceList
{
   unsigned int                numItems;
   ARSchemaInheritanceStruct  *schemaInheritanceList;

}  ARSchemaInheritanceList;

typedef struct ARSchemaInheritanceListList
{
   unsigned int              numItems;
   ARSchemaInheritanceList  *schemaInheritanceListList;

}  ARSchemaInheritanceListList;

                                    /* tags for types of support files */
#define AR_SUPPORT_FILE_NONE              0
#define AR_SUPPORT_FILE_EXTERNAL_REPORT   1

typedef struct ARSupportFileInfoStruct
{
   unsigned int   fileType;
   ARInternalId   fileId;
   ARTimestamp    timestamp;
   char          *content;
   unsigned int   contentLen;

}  ARSupportFileInfoStruct;

typedef struct ARSupportFileInfoList
{
   unsigned int              numItems;
   ARSupportFileInfoStruct  *sfList;

}  ARSupportFileInfoList;

    /* The next two Statistics structures are present for backward          */
    /* compatibility only.  They should not be used in any new development. */
    /* OBSOLETE; Backward compatibility only */
typedef struct ARStatisticsStruct
{
   unsigned int                operation;
   ARFieldValueOrArithStruct   field;
}  ARStatisticsStruct;

typedef struct ARStatisticsList
{                       /* OBSOLETE; Backward compatibility only */
                        /* list of 0 or more statistics requests */
   unsigned int         numItems;
   ARStatisticsStruct  *statisticsList;
}  ARStatisticsList;

   /* The following Display type define and structure definitions are */
   /* present for backward compatibility only.  They should not be    */
   /* used for any new development.                                   */

#define AR_DISPLAY_TYPE_NONE       0
#define AR_DISPLAY_TYPE_TEXT       1 /* tags for field display types */
#define AR_DISPLAY_TYPE_NUMTEXT    2
#define AR_DISPLAY_TYPE_CHECKBOX   4
#define AR_DISPLAY_TYPE_CHOICE     5
#define AR_DISPLAY_TYPE_BUTTON     6
#define AR_DISPLAY_TYPE_TRIM       7

#define AR_DISPLAY_OPT_VISIBLE     1 /* tags for field display options */
#define AR_DISPLAY_OPT_HIDDEN      2

#ifndef ASCII  /* Added ifndef to avoid multiple defines of the following */
#define AR_DISPLAY_LABEL_LEFT      1 /* tags for where to display the label */
#define AR_DISPLAY_LABEL_TOP       2
#endif /* ASCII */


typedef struct ARDisplayStruct
{
   ARNameType     displayTag;
   ARNameType     label;
   unsigned int   labelLocation;
   unsigned int   type;
   unsigned int   length;
   unsigned int   numRows;
   unsigned int   option;
   int            x;
   int            y;

}  ARDisplayStruct;

typedef struct ARDisplayList
{               /* list of 1 or more display structures */
   unsigned int      numItems;
   ARDisplayStruct  *displayList;

}  ARDisplayList;


/* Container types */
#define ARCON_ALL                   0  /* all container types */
#define ARCON_GUIDE                 1  /* guide container */
#define ARCON_APP                   2  /* application container */
#define ARCON_PACK                  3  /* packing list container */
#define ARCON_FILTER_GUIDE          4  /* filter guide container */
#define ARCON_WEBSERVICE            5  /* web service container */
#define ARCON_LAST_RESERVED     65535  /* last AR System reserved container type */

/* Reference types */
#define ARREF_NONE                  0  /* no references */
#define ARREF_ALL                   1  /* all reference types */
#define ARREF_SCHEMA                2  /* reference to a schema */
#define ARREF_FILTER                3  /* reference to a filter */
#define ARREF_ESCALATION            4  /* reference to an escalation */
#define ARREF_ACTLINK               5  /* reference to an active link */
#define ARREF_CONTAINER             6  /* reference to a container */
#define ARREF_CHAR_MENU             7  /* reference to a character menu */
#define ARREF_IMAGE                 8  /* reference to an image */
#define ARREF_TASK                  9  /* reference to an task */
#define ARREF_LAST_SERVER_OBJ   32767  /* last server object reference type */

/* AR System defined external references from here down */

#define ARREF_ICON              32768 /* reference to an icon             */
#define ARREF_SMALL_ICON        32769 /* reference to a small icon        */
#define ARREF_MAXIMIZE_FORMS    32770 /* for applications - int (boolean) */
                                      /* can be value: maximize forms?    */
#define ARREF_APPLICATION_FORMS 32771 /* for applications - forms used in */
                                      /* the application tag that next    */
                                      /* reference is a form can be       */
                                      /* repeated multiple times          */
#define ARREF_ABOUT_BOX_IMAGE   32772 /* about box image - bytelist value */
#define ARREF_ABOUT_BOX_FORM    32773 /* tag that about box form is next  */
                                      /* reference                        */
#define ARREF_NULL_STRING       32774 /* used for null strings ie. labels */
#define ARREF_APPLICATION_HELP_EXT 32775 /* CHAR - used for Application   */
                                      /*  object help file extension      */
#define ARREF_APPLICATION_HELP_FILE 32776 /* BYTELIST - used for Application*/
                                      /* object help file                 */
#define ARREF_APPLICATION_PRIMARY_FORM 32777 /* tag that next reference is*/
                                      /* primary form                     */
#define ARREF_APPLICATION_FORM_VUI 32778 /* ulong; vui-id of previous form*/
                                     /* reference                         */
#define ARREF_APPLICATION_DISABLE_BEGIN_TASK 32779 /* int (boolean) - TRUE if*/
                                     /* begin a task should be disabled. */
                                     /* Default is FALSE                 */
#define ARREF_APPLICATION_HELP_INDEX_EXT  32780 /* CHAR - used for Application*/
                                                /*  object help file's index */
                                                /*  file extension           */
#define ARREF_APPLICATION_HELP_INDEX_FILE 32781 /* BYTELIST - for Application*/
                                                /*  object help file's index */
                                                /*  file                     */
#define ARREF_APPLICATION_HELP_FILE_NAME  32782 /* CHAR - for Application    */
                                                /*  object help file's name, */
                                                /*  w/o the extension        */
#define ARREF_PACKINGLIST_GUIDE 32783 /* CHAR - for Packing Lists            */
                                      /*  reference to a Guide               */
#define ARREF_PACKINGLIST_APP   32784 /* CHAR - for Packing Lists            */
                                      /*  reference to an Application        */
#define ARREF_PACKINGLIST_PACK  32785 /* CHAR -  for Packing Lists           */
                                      /*  reference to a Packing List        */
#define ARREF_GROUP_DATA        32786 /* CHAR -  for Packing Lists           */
                                      /*  reference to data in the Group     */
                                      /*  schema                             */
#define ARREF_DISTMAPPING_DATA  32787 /* CHAR -  for Packing Lists           */
                                      /*  reference to data in the           */
                                      /*  Distributed Mapping schema         */
#define ARREF_APPLICATION_HAS_EXT_HELP  32788 /* INT -  for applications     */
                                      /*  use external help or not (bool)    */
#define ARREF_APPLICATION_SUPPORT_FILES 32789 /* BYTELIST - for Application  */
                                      /*  object support file's contents     */
#define ARREF_PACKINGLIST_DSOPOOL 32792 /* CHAR -  for Packing Lists         */
                                      /*  reference to data in the           */
                                      /*  Distributed Pool schema            */
#define ARREF_PACKINGLIST_FILTER_GUIDE 32793 /* CHAR - for Packing Lists     */
                                      /*  reference to a Filter Guide        */
#define ARREF_FLASH_BOARD_DEF        32794 /* Flashboard definition           */
#define ARREF_FLASH_DATA_SOURCE_DEF  32795 /* Flashboard Data Source def.     */
#define ARREF_FLASH_VARIABLE_DEF     32796 /* Flashboard Variable definition  */
#define ARREF_WS_PROPERTIES          32797 /* XML string that refers to misc  */
                                           /* properties of webservice.       */
#define ARREF_WS_OPERATION           32798 /* Web service operation info      */
                                           /* (xml string consisting of name, */
                                           /* type, mapping names, etc.)      */
#define ARREF_WS_ARXML_MAPPING       32799 /* Mapping xml document that       */
                                           /* describes relation between AR   */
                                           /* model and xml schema.           */
#define ARREF_WS_WSDL                32800 /* WSDL for web service.           */
#define ARREF_PACKINGLIST_WEBSERVICE 32801 /* CHAR - for Packing Lists       */
                                           /*  reference to a webservice     */
#define ARREF_WS_PUBLISHING_LOC      32802 /* CHAR - saved URL(s) for        */
                                           /*  publishing a web service      */
#define ARREF_APPLICATION_HELP_FILE_NAME2  32803 /* CHAR - for Application    */
                                                 /*  object help file's name, */
                                                 /*  w/o the extension        */
#define ARREF_APPLICATION_HELP_EXT2        32804 /* CHAR - used for Application */
                                                 /*  object help file extension */
#define ARREF_APPLICATION_HELP_FILE2       32805 /* BYTELIST - used for Application */
                                                 /* object help file                */
#define ARREF_APPLICATION_HELP_INDEX_EXT2  32806 /* CHAR - used for Application*/
                                                 /*  object help file's index */
                                                 /*  file extension           */
#define ARREF_APPLICATION_HELP_INDEX_FILE2 32807 /* BYTELIST - for Application*/
                                                 /*  object help file's index */
                                                 /*  file                     */
#define ARREF_APPLICATION_HELP_FILE_NAME3  32808 /* CHAR - for Application    */
                                                 /*  object help file's name, */
                                                 /*  w/o the extension        */
#define ARREF_APPLICATION_HELP_EXT3        32809 /* CHAR - used for Application */
                                                 /*  object help file extension */
#define ARREF_APPLICATION_HELP_FILE3       32810 /* BYTELIST - used for Application */
                                                 /* object help file                */
#define ARREF_APPLICATION_HELP_INDEX_EXT3  32811 /* CHAR - used for Application*/
                                                 /*  object help file's index */
                                                 /*  file extension           */
#define ARREF_APPLICATION_HELP_INDEX_FILE3 32812 /* BYTELIST - for Application*/
                                                 /*  object help file's index */
                                                 /*  file                     */
#define ARREF_APPLICATION_HELP_FILE_NAME4  32813 /* CHAR - for Application    */
                                                 /*  object help file's name, */
                                                 /*  w/o the extension        */
#define ARREF_APPLICATION_HELP_EXT4        32814 /* CHAR - used for Application */
                                                 /*  object help file extension */
#define ARREF_APPLICATION_HELP_FILE4       32815 /* BYTELIST - used for Application */
                                                 /* object help file                */
#define ARREF_APPLICATION_HELP_INDEX_EXT4  32816 /* CHAR - used for Application*/
                                                 /*  object help file's index */
                                                 /*  file extension           */
#define ARREF_APPLICATION_HELP_INDEX_FILE4 32817 /* BYTELIST - for Application*/
                                                 /*  object help file's index */
                                                 /*  file                     */
#define ARREF_APPLICATION_HELP_FILE_NAME5  32818 /* CHAR - for Application    */
                                                 /*  object help file's name, */
                                                 /*  w/o the extension        */
#define ARREF_APPLICATION_HELP_EXT5        32819 /* CHAR - used for Application */
                                                 /*  object help file extension */
#define ARREF_APPLICATION_HELP_FILE5       32820 /* BYTELIST - used for Application */
                                                 /* object help file                */
#define ARREF_APPLICATION_HELP_INDEX_EXT5  32821 /* CHAR - used for Application */
                                                 /*  object help file's index   */
                                                 /*  file extension             */
#define ARREF_APPLICATION_HELP_INDEX_FILE5 32822 /* BYTELIST - for Application  */
                                                 /*  object help file's index   */
                                                 /*  file                       */
#define ARREF_APPLICATION_HELP_LABEL       32823 /* CHAR - used for Application */
                                                 /*  object help file's label   */
#define ARREF_APPLICATION_HELP_LABEL2      32824 /* CHAR - used for Application */
                                                 /*  object help file's label   */
#define ARREF_APPLICATION_HELP_LABEL3      32825 /* CHAR - used for Application */
                                                 /*  object help file's label   */
#define ARREF_APPLICATION_HELP_LABEL4      32826 /* CHAR - used for Application */
                                                 /*  object help file's label   */
#define ARREF_APPLICATION_HELP_LABEL5      32827 /* CHAR - used for Application */
                                                 /*  object help file's label   */
#define ARREF_WS_XML_SCHEMA_LOC            32828 /* CHAR - xml schema location  */
                                                 /*  for a web service          */
#define ARREF_ENTRYPOINT_ORDER             32829 /* INT - listing order of the  */
                                                 /*   entry point               */
#define ARREF_ENTRYPOINT_START_ACTLINK     32830 /* CHAR - starting AL for the  */
                                                 /*   entry point               */
#define ARREF_APP_AUTOLAYOUT_SS            32831 /* CHAR - Style sheet info for AUT*/

#define ARREF_APP_FORMACTION_FIELDS        32832 /* CHAR - Form action fields*/
#define ARREF_ENCAPSULATED_APP_DATA        32833 /* CHAR - application data   */
                                                 /*        identifier         */
#define ARREF_APP_DEFAULT_OBJ_PERMS        32835 /* CHAR - default application */
                                                 /*   object permissions       */
#define ARREF_APP_ADD_FORMACTION_FIELDS                  32836/* enum; add form action fields */
#define ARREF_APP_FORMACTION_RESULTS_LIST_FIXED_HEADER   32837/* enum; fixed header property */
#define ARREF_APP_FORMACTION_PAGE_PROPERTIES             32838/* CHAR; page property */
#define ARREF_APP_OBJECT_VERSION           32839 /* INT - application object version */
#define ARREF_APP_PACKING_LISTS            32840 /* packing lists in the app */
#define ARREF_APP_DATA_MERGE_IMP_QUAL      32841 /* CHAR - list of field Ids for */
                                                 /*   merge qual on import */
#define ARREF_APP_DATA_MERGE_IMP_OPTION    32842 /* INT- data import option for */
                                                 /*   merge on app import       */

#define ARREF_LAST_RESERVED      65535 /* last AR System reserved reference type */

/* customer defined external references from here down */

/* Reference data types */
#define ARREF_DATA_ARSREF            0  /* AR System reference data */
#define ARREF_DATA_EXTREF            1  /* external reference data */

/* Types of container owning objects */
#define ARCONOWNER_NONE              0  /* global container (unowned) */
#define ARCONOWNER_ALL               1  /* all container, owned and unowned */
#define ARCONOWNER_SCHEMA            2  /* container owned by a schema */

/* API and server enforced limits on lengths of byte list structures */
/* in a container or reference                                       */
#define ARMAX_CON_LABEL_LEN        255  /* max chars in a label */
#define ARMAX_CON_DESCRIPTION_LEN 2000  /* max chars in a description */
#define ARMAX_CON_TASK_NAME_LEN   1024  /* max chars in a task name */
#define ARMAX_CON_OML_LABEL_LEN   1024  /* max chars in a objectModificationLogLabel */

/* Structures describing objects that own a container. */
typedef struct ARContainerOwnerObj
{
   unsigned int   type;
   ARNameType     ownerName;

}  ARContainerOwnerObj;

typedef struct ARContainerOwnerObjList
{
   unsigned int          numItems;
   ARContainerOwnerObj  *ownerObjList;

}  ARContainerOwnerObjList;

typedef struct ARContainerOwnerObjListList
{
   unsigned int              numItems;
   ARContainerOwnerObjList  *ownerObjListList;

}  ARContainerOwnerObjListList;

typedef struct ARContainerOwnerObjId
{
   unsigned int   type;
   unsigned int   ownerId;

}  ARContainerOwnerObjId;

typedef struct ARContainerOwnerObjIdList
{
   unsigned int            numItems;
   ARContainerOwnerObjId  *ownerObjIdList;

}  ARContainerOwnerObjIdList;

/* A structure to hold references to non-AR System server objects.  Each */
/* external reference has a list of groups that are permitted to use the */
/* reference.                                                            */
typedef struct ARExtReferenceStruct
{
   ARInternalIdList   permittedGroups;
   ARValueStruct      value;

}  ARExtReferenceStruct;

/* Reference structure.  This structure can point at server objects including */
/* schemas, filters, escalations, active links, menus, and containers. It can */
/* also hold other information like URLs and filenames as external references.*/
typedef struct ARReferenceUnion
{
   unsigned int   dataType;         /* ARREF_DATA_... */
   union
   {
      ARNameType             name;  /* AR System server object */
      ARExtReferenceStruct   extRef;/* non-AR System object    */
   } u;

}  ARReferenceUnion;

typedef struct ARReferenceStruct
{
   char              *label;        /* max 255 chars */
   char              *description;  /* max 2000 chars */
   unsigned int       type;         /* ARREF_... */
   ARReferenceUnion   reference;

}  ARReferenceStruct;

typedef struct ARReferenceList
{
   unsigned int        numItems;
   ARReferenceStruct  *referenceList;

}  ARReferenceList;

typedef struct ARReferenceListList
{
   unsigned int      numItems;
   ARReferenceList  *referenceListList;

}  ARReferenceListList;

typedef struct ARReferenceTypeList
{
   unsigned int   numItems;
   int           *refType;

}  ARReferenceTypeList;

/* A structure to contain the results of an ARGetListContainer call */
typedef struct ARContainerInfo
{
   ARNameType                name;
   unsigned int              type;
   ARContainerOwnerObjList   ownerList;

}  ARContainerInfo;

typedef struct ARContainerInfoList
{
   unsigned int      numItems;
   ARContainerInfo  *conInfoList;

}  ARContainerInfoList;

typedef struct ARContainerTypeList
{
   unsigned int   numItems;
   int           *type;

}  ARContainerTypeList;

                                 /* ARSignal types */
#define AR_SIGNAL_CONFIG_CHANGED           1  /* reload configuration file */
#define AR_SIGNAL_GROUP_CACHE_CHANGED      2  /* reload group info */
#define AR_SIGNAL_LICENSE_CHANGED          3  /* reload license information */
#define AR_SIGNAL_ALERT_USER_CHANGED       4  /* update alert user info */
#define AR_SIGNAL_DSO_SIGNAL               5  /* dso signal - info */
#define AR_SIGNAL_USER_CACHE_CHANGED       6  /* reload user info */
#define AR_SIGNAL_APPLICATION_SIGNAL       7  /* application process signal - info */
#define AR_SIGNAL_ARCHIVE_CHANGED          8  /* recache and reload archive definitions */
#define AR_SIGNAL_ESCALATION_CHANGED       9  /* recache and reload escalation fire times */
#define AR_SIGNAL_RECACHE                 10  /* recache definitions from database */
#define AR_SIGNAL_COMPUTED_GROUP_CHANGED  11  /* reload computed group info */
#define AR_SIGNAL_DYNAMIC_PERM_CHANGED    12  /* reload row level security info */
#define AR_SIGNAL_FULL_TEXT_PENDING       13  /* full text indexing pending */
#define AR_SIGNAL_INSTALL_SIGNAL          14  /* install signal - see sigArgument for details */
#define AR_SIGNAL_SRVSTAT_SIGNAL          15  /* flush API/SQL statistics */
#define AR_SIGNAL_FULL_TEXT_REINDEXING_SYNC 16  /* Sync FTS re-indexing tasks to FTS plugin */

typedef struct ARSignalStruct
{
   int    signalType;
   char  *sigArgument;

}  ARSignalStruct;

typedef struct ARSignalList
{
   unsigned int     numItems;
   ARSignalStruct  *signalList;

}  ARSignalList;

/* flag indicates whether logging information should be written to */
/* a file, and/or just returned via the status list */
#define AR_WRITE_TO_FILE                1
#define AR_WRITE_TO_STATUS_LIST         2

#define AR_WORKFLOW_CONN_NONE           0
#define AR_WORKFLOW_CONN_SCHEMA_LIST    1 /* assoc with a list of schemas */

typedef struct ARWorkflowConnectStruct
{
   unsigned int   type;
   union
   {
      ARNameList  *schemaList;
   } u;

}  ARWorkflowConnectStruct;

typedef struct ARWorkflowConnectList
{
   unsigned int              numItems;
   ARWorkflowConnectStruct  *workflowConnectList;

}  ARWorkflowConnectList;

typedef struct ARLocalizedRequestStruct
{
   ARNameType     name;
   unsigned int   messageType;
   union
   {
      struct
      {
         unsigned int   ifElse;
         unsigned int   action;
      } workflow;

      ARInternalId   fieldId;
   } u;

}  ARLocalizedRequestStruct;

typedef struct ARLocalizedRequestList
{
   unsigned int               numItems;
   ARLocalizedRequestStruct  *localizedRequestList;

}  ARLocalizedRequestList;

/* Default encryption policies. */
#define AR_ENC_SEC_POLICY_ENCRYPT_ALLOWED         0
#define AR_ENC_SEC_POLICY_ENCRYPT_REQUIRED        1
#define AR_ENC_SEC_POLICY_ENCRYPT_DISALLOWED      2

                                     /* codes for types of localized text */
#define AR_LOCAL_TEXT_SYSTEM_MESSAGE         0
#define AR_LOCAL_TEXT_ACT_LINK_MESSAGE       1
#define AR_LOCAL_TEXT_FILTER_MESSAGE         2
#define AR_LOCAL_TEXT_ACT_LINK_HELP          3
#define AR_LOCAL_TEXT_FORM_HELP              4
#define AR_LOCAL_TEXT_FIELD_HELP             5
#define AR_LOCAL_TEXT_CONTAIN_DESC           6
#define AR_LOCAL_TEXT_LIST_MENU_DEFN         7
#define AR_LOCAL_TEXT_EXTERN_REPORT          8    /* binary */
#define AR_LOCAL_TEXT_CONTAINER_LABEL        9
#define AR_LOCAL_TEXT_CONTAINER_HELP         10
#define AR_LOCAL_TEXT_APPLICATION_HELP       11   /* binary */
#define AR_LOCAL_TEXT_APPLICATION_ABOUT      12   /* binary */
#define AR_LOCAL_TEXT_APPLICATION_HELP_INDEX 13   /* binary */
#define AR_LOCAL_TEXT_FLASHBRD_MESSAGE       14
#define AR_LOCAL_TEXT_FLASHBRD_LABEL         15

#define AR_LOCAL_TEXT_ACTIVE_MESSAGE         0
#define AR_LOCAL_TEXT_INACTIVE_MESSAGE       1

#define AR_LOCAL_TEXT_RETURN_TYPE_MSG_TEXT   0
#define AR_LOCAL_TEXT_RETURN_TYPE_BIN_ATTACH 1

#define IFELSE_IF       0
#define IFELSE_ELSE     1

/* Alert event source types */
#define AR_ALERT_SOURCE_GP      1    /* General purpose source */
#define AR_ALERT_SOURCE_AR      2    /* AR System is the source */
#define AR_ALERT_SOURCE_FIRST   3    /* Generic first contact indicator */
#define AR_ALERT_SOURCE_CHECK   4    /* Generic accessibility check */
#define AR_ALERT_SOURCE_FB      5    /* Flashboards is the source */

#define AR_ALERT_ACK                 "ack" /* ack used in socket communication*/
#define AR_ALERT_USER_BROADCAST        "*" /* user to indicate send to all */
                                           /*  currently registered users  */
#define AR_ALERT_STRING_SEP           '\\' /* separator used in alert string */

/* Server Event Types */
#define AR_SVR_EVENT_CHG_SCHEMA        1
#define AR_SVR_EVENT_CHG_FIELD         2
#define AR_SVR_EVENT_CHG_CHARMENU      3
#define AR_SVR_EVENT_CHG_FILTER        4
#define AR_SVR_EVENT_CHG_IMPORT        5
#define AR_SVR_EVENT_CHG_ACTLINK       6
#define AR_SVR_EVENT_CHG_ESCAL         7
#define AR_SVR_EVENT_CHG_VUI           8
#define AR_SVR_EVENT_CHG_CONTAINER     9
#define AR_SVR_EVENT_CHG_USERS         10
#define AR_SVR_EVENT_CHG_GROUPS        11
#define AR_SVR_EVENT_CHG_SVR_SETTINGS  12
#define AR_SVR_EVENT_CHG_ALERT_USERS   13
#define AR_SVR_EVENT_ARCHIVE_DONE      14
#define AR_SVR_EVENT_SERVGROUP_ACTION  15
#define AR_SVR_EVENT_CHG_LICENSES      16
#define AR_SVR_EVENT_DYNAMIC_PERM      17
#define AR_SVR_EVENT_CHG_IMAGE         18
#define AR_SVR_EVENT_CLIENT_TIMEOUT    19

#define AR_MAX_SVR_EVENT_USED          19

/* Max length of one numeric event type string (with semi-colon). */
#define AR_MAX_SVR_EVENT_TYPE_STR      4

/* User Schema Server Event Causes */
#define AR_SVR_EVENT_USER_ADDED        0
#define AR_SVR_EVENT_USER_MODIFIED     1
#define AR_SVR_EVENT_USER_DELETED      2

/* Group Schema Server Event Causes */
#define AR_SVR_EVENT_GROUP_ADDED          0
#define AR_SVR_EVENT_GROUP_MODIFIED       1
#define AR_SVR_EVENT_GROUP_DELETED        2
#define AR_SVR_EVENT_COMPGROUP_ADDED      3
#define AR_SVR_EVENT_COMPGROUP_MODIFIED   4
#define AR_SVR_EVENT_COMPGROUP_DELETED    5
#define AR_SVR_EVENT_APPLICATION_ADDED    6
#define AR_SVR_EVENT_APPLICATION_MODIFIED 7
#define AR_SVR_EVENT_APPLICATION_DELETED  8
#define AR_SVR_EVENT_ROLE_ADDED           9
#define AR_SVR_EVENT_ROLE_MODIFIED        10
#define AR_SVR_EVENT_ROLE_DELETED         11

/* Archive Server Event Causes */
#define AR_SVR_EVENT_ARCHIVE_FORM         1
#define AR_SVR_EVENT_ARCHIVE_DELETE       2
#define AR_SVR_EVENT_ARCHIVE_FORM_DELETE  3
#define AR_SVR_EVENT_ARCHIVE_XML          4
#define AR_SVR_EVENT_ARCHIVE_ARX          5

/* Server Group Event Causes */
#define AR_SVR_EVENT_SERVGROUP_FAILOVER   1
#define AR_SVR_EVENT_SERVGROUP_RELINQUISH 2
#define AR_SVR_EVENT_SERVGROUP_TAKEOVER   3

/* Object import events      */
/* These apply to:           */
/* - Forms                   */
/* - Fields                  */ 
/* - Views                   */
/* - Filters                 */
/* - Active Links            */
/* - Escalations             */
/* - Containers              */
/* - Menus                   */
/* - Images                  */
#define AR_SVR_EVENT_IMPORT_SET_OBJECT     0
#define AR_SVR_EVENT_IMPORT_CREATE_OBJECT  1

/* Dynamic Permission Event Causes */
#define AR_SVR_EVENT_DYN_PERMISSION_START 1
#define AR_SVR_EVENT_DYN_PERMISSION_END   2


typedef struct ARConfigSvrEvents
{
   ARBoolean events[AR_MAX_SVR_EVENT_USED];
}  ARConfigSvrEvents;


typedef struct ARFieldInfoStruct
{
   ARInternalId            fieldId;
   ARNameType              fieldName;
   ARTimestamp             timestamp;
   ARFieldMappingStruct    fieldMap;
   unsigned int            dataType;
   unsigned int            option;
   unsigned int            createMode;
   unsigned int            fieldOption;
   ARValueStruct           defaultVal;
   ARPermissionList        permList;
   ARFieldLimitStruct      limit;
   ARDisplayInstanceList   dInstanceList;
   ARAccessNameType        owner;
   ARAccessNameType        lastChanged;
   char                   *helpText;
   char                   *changeDiary;
   ARPropList              objPropList;

}  ARFieldInfoStruct;

typedef struct ARFieldInfoList
{
   unsigned int        numItems;
   ARFieldInfoStruct  *fieldList;

}  ARFieldInfoList;

/* This includes structures used to exchange information between the */
/* server and the XMLUtil library.                                   */

typedef struct ARExportFieldInfoStruct
{
   ARInternalId            fieldId;
   ARNameType              fieldName;
   ARTimestamp             timestamp;
   ARFieldMappingStruct    fieldMap;
   unsigned int            dataType;
   unsigned int            option;
   unsigned int            createMode;
   unsigned int            fieldOption;
   ARValueStruct           defaultVal;
   ARPermissionList        permList;
   ARPermissionList        addPermList;
   ARFieldLimitStruct      limit;
   ARDisplayInstanceList   dInstanceList;
   ARAccessNameType        owner;
   ARAccessNameType        lastChanged;
   char                   *helpText;
   char                   *changeDiary;
   ARPropList              objPropList;

}  ARExportFieldInfoStruct;

typedef struct ARExportFieldInfoList
{
   unsigned int        numItems;
   ARExportFieldInfoStruct  *fieldList;

}  ARExportFieldInfoList;


typedef struct ARVuiInfoStruct
{
   ARInternalId       vuiId;
   ARNameType         vuiName;
   ARTimestamp        timestamp;
   ARPropList         props;      /* properties of this Vui */
   ARAccessNameType   owner;
   ARLocaleType       locale;
   unsigned int       vuiType;
   ARAccessNameType   lastChanged;
   char              *helpText;
   char              *changeDiary;
   ARPropList         smObjProp;  /* SM properties of this Vui */
}  ARVuiInfoStruct;

typedef struct ARVuiInfoList
{
   unsigned int      numItems;
   ARVuiInfoStruct  *vuiList;

}  ARVuiInfoList;


/* server statistics recording modes */
#define AR_SVR_STATS_RECMODE_OFF          0 /* no server stats recording */
#define AR_SVR_STATS_RECMODE_CUMUL_ONLY   1 /* cumulative queue stats only */
#define AR_SVR_STATS_RECMODE_CUMUL_QUEUE  2 /* cumulative & individual queue */
                                            /*  stats                        */

/* server dso setting options */
#define AR_DSO_UPDATE_IMMEDIATELY        0
#define AR_DSO_UPDATE_HOURLY             1
#define AR_DSO_UPDATE_DAILY              2
#define AR_DSO_UPDATE_ON_RETURN          3
#define AR_DSO_UPDATE_NO_UPDATE          4

#define AR_DSO_TRANSFER_DATA_ONLY        0
#define AR_DSO_TRANSFER_OWNERSHIP        1
#define AR_DSO_TRANSFER_COPY             2
#define AR_DSO_TRANSFER_COPY_DELETE      3

#define AR_DSO_TRANSFER_DUP_ERROR        0
#define AR_DSO_TRANSFER_DUP_OVERWRITE    1
#define AR_DSO_TRANSFER_DUP_CREATE_NEW   2

#define AR_DSO_MAP_BY_FIELD_IDS          0
#define AR_DSO_MAP_BY_CUSTOM             1
#define AR_DSO_MAP_BY_FIELD_NAMES        2

#define AR_DSO_ERROR_RETRY_STANDARD      0
#define AR_DSO_ERROR_RETRY_NO_RETRY      1
#define AR_DSO_ERROR_RETRY_ALL_RETRY     2
#define AR_DSO_ERROR_RETRY_STANDARD_DB   3

/* VUI-Type Definition */
#define AR_VUI_TYPE_NONE                 0
#define AR_VUI_TYPE_WINDOWS              1
#define AR_VUI_TYPE_STANDARD             1
#define AR_VUI_TYPE_WEB                  2
#define AR_VUI_TYPE_WEB_ABS_POS          3
#define AR_VUI_TYPE_WIRELESS             4
#define AR_VUI_TYPE_WEB_AUTOGEN          5
#define AR_VUI_TYPE_WEB_ABS_POS_AUTOGEN  6
#define AR_VUI_TYPE_DEFAULT              7
#define AR_VUI_TYPE_SELECT               8

/* client Id for an API program */
#define AR_CLIENT_TYPE_UNKNOWN                 0
#define AR_CLIENT_TYPE_PRE_50                  1  /* Pre 5.0 ar client tools */
#define AR_CLIENT_TYPE_WAT                     2  /* Windows admin tool */
#define AR_CLIENT_TYPE_WUT                     3  /* Windows user tool */
#define AR_CLIENT_TYPE_WIP                     4  /* Windows import tool */
#define AR_CLIENT_TYPE_DSO                     5  /* Distributed server */
#define AR_CLIENT_TYPE_ODBC                    6  /* ARODBC */
#define AR_CLIENT_TYPE_APPROVAL                7  /* Approval server */
#define AR_CLIENT_TYPE_WEB_SERVER              8  /* AR web server, waserver */
#define AR_CLIENT_TYPE_MID_TIER                9  /* Mid-tier 5.0 and later */
#define AR_CLIENT_TYPE_PALM_PILOT             10  /* Palm pilot */
#define AR_CLIENT_TYPE_FLASHBOARDS            11  /* Flashboards */
#define AR_CLIENT_TYPE_FLASHBOARDS_MID_TIER   12  /* Flashboards mid-tier */
#define AR_CLIENT_TYPE_EIE                    13  /* Enterprise Integration */
                                                  /*  Engine                */
#define AR_CLIENT_TYPE_RELOAD                 14  /* arreload */
#define AR_CLIENT_TYPE_CACHE                  15  /* arcache */
#define AR_CLIENT_TYPE_DIST                   16  /* ardist */
#define AR_CLIENT_TYPE_RUN_MACRO              17  /* runmacro */
#define AR_CLIENT_TYPE_MAIL                   18  /* armaild/armailex */
#define AR_CLIENT_TYPE_IMPORT_CMD             19  /* arimportcmd */
#define AR_CLIENT_TYPE_REPORT_PLUGIN          20  /* Report creator plugin */
#define AR_CLIENT_TYPE_ALERT                  21  /* Alert tool */
#define AR_CLIENT_TYPE_MAIL_DAEMON            22  /* New AR Mail Daemon, not armaild */
#define AR_CLIENT_TYPE_SIGNAL                 23  /* arsignal */
#define AR_CLIENT_TYPE_DEBUGGER               24  /* debugger */
#define AR_CLIENT_TYPE_OBJSTR                 25  /* object store API */
#define AR_CLIENT_TYPE_OBJSTR_SYNC            26  /* object store sync utility */
#define AR_CLIENT_TYPE_SERVER_ADMIN_PLUGIN    27  /* Server Admin plugin */
#define AR_CLIENT_TYPE_SIM_PUBLISHING_SERVER  28  /* bmc sim publishing server */
#define AR_CLIENT_TYPE_SIM_SME                29  /* bmc sim service model editor */
#define AR_CLIENT_TYPE_CMDB_ENGINE            30  /* cmdb engine */
#define AR_CLIENT_TYPE_CMDB_DRIVER            31  /* cmdb driver */
#define AR_CLIENT_TYPE_RECON_ENGINE           32  /* cmdb reconciliation engine */
#define AR_CLIENT_TYPE_ASSIGNMENT_ENGINE      33  /* Assignment Engine */
#define AR_CLIENT_TYPE_WEBSERVICE             34  /* Webservice */
#define AR_CLIENT_TYPE_NORMALIZATION_ENGINE   35  /* Normalization Engine */
#define AR_CLIENT_TYPE_DEVELOPER_STUDIO       36  /* Developer Studio */
#define AR_CLIENT_TYPE_FT_TEXT_READER         37  /* FT Text Reader */
#define AR_CLIENT_TYPE_ATRIUMSSO              38  /* Atrium SSO Server */
#define AR_CLIENT_TYPE_MIGRATOR               39  /* AR Migrator */
#define AR_CLIENT_TYPE_UDM                    40  /* AR UDM Adapter */
#define AR_CLIENT_TYPE_RKM_OPERATIONS         41  /* RKM Operations plugin */
#define AR_CLIENT_TYPE_RKM_FORM_PERMISSIONS   42  /* RKM Form Permissions plugin */
#define AR_CLIENT_TYPE_RKM_DOCUMENT_MIGRATOR  43  /* RKM Document Migrator plugin */
#define AR_CLIENT_TYPE_RKM_FILE_SYSTEM        44  /* RKM File System plugin */
#define AR_CLIENT_TYPE_RKM_FILE_SYSTEM_SYNC   45  /* RKM File System Sync plugin */
#define AR_CLIENT_TYPE_RKM_GROUP              46  /* RKM Group plugin */
#define AR_CLIENT_TYPE_RKM_REGISTRATION       47  /* RKM Registration plugin */
#define AR_CLIENT_TYPE_ASSET_SWLM_RULE_ENGINE 48  /* Asset SWLM Rule Engine plugin */
#define AR_CLIENT_TYPE_ASSET_SOFTWARE_USAGE   49  /* Asset Software Usage plugin */
#define AR_CLIENT_TYPE_ASSET_RLE_CONFIG       50  /* Asset RLE Configuration plugin */
#define AR_CLIENT_TYPE_ASSET_CHARGE_BACK      51  /* Asset Charge Back plugin */
#define AR_CLIENT_TYPE_ITSM_COMMON            52  /* ITSM Common plugin */
#define AR_CLIENT_TYPE_ITSM_CAI               53  /* ITSM CAI plugin */
#define AR_CLIENT_TYPE_ITSM_UTILITY           54  /* ITSM Utility plugin */
#define AR_CLIENT_TYPE_ITSM_APPQUERY          55  /* ITSM AppQuery plugin */
#define AR_CLIENT_TYPE_ITSM_NEXT_ID           56  /* ITSM Next ID plugin */
#define AR_CLIENT_TYPE_ATRIUM_INTEGRATOR      57  /* Atrium Integrator */
#define AR_CLIENT_TYPE_ADDM                   58  /* ADDM */
#define AR_CLIENT_TYPE_BPPM                   59  /* BPPM */
#define AR_CLIENT_TYPE_ODA                    60  /* ARODA */
#define AR_CLIENT_TYPE_MYIT                   61  /* MyIT */

#define AR_CLIENT_TYPE_END_OF_PRODUCT       3999

#define AR_CLIENT_TYPE_UNPRODUCTIZED_START  4000
#define AR_CLIENT_TYPE_DRIVER               4000  /* Driver: sample program */
#define AR_CLIENT_TYPE_DISPATCHER           4001  /* distributor of appl. */
                                                  /*  command signals     */
#define AR_CLIENT_TYPE_HELP                 4002  /* arhelp */
#define AR_CLIENT_TYPE_JANITOR              4003  /* arjanitor */
#define AR_CLIENT_TYPE_MENU                 4004  /* armenu */
#define AR_CLIENT_TYPE_STRUCT               4005  /* arstruct */
#define AR_CLIENT_TYPE_TEXT                 4006  /* artext */
#define AR_CLIENT_TYPE_SQLED                4007  /* arsqled */
#define AR_CLIENT_TYPE_CHANGE_SEL           4008  /* archgsel */
#define AR_CLIENT_TYPE_CHANGE_ID            4009  /* archgid */
#define AR_CLIENT_TYPE_LABEL                4010  /* arlabel */
#define AR_CLIENT_TYPE_INSTALLER            4011  /* AR System Installer */
#define AR_CLIENT_TYPE_RIK                  4012  /* Remedy Install Kit (RIK) */

#define AR_CLIENT_TYPE_END_OF_RESERVED_RANGE  5000

/* Values for the API Session Configuration parameters */
#define AR_SESS_CHUNK_RESPONSE_SIZE    1 /* max size of a single resp */
#define AR_SESS_TIMEOUT_NORMAL         2 /* timeout for normal ops */
#define AR_SESS_TIMEOUT_LONG           3 /* timeout for long ops */
#define AR_SESS_TIMEOUT_XLONG          4 /* timeout for extra long ops */
#define AR_SESS_LOCK_TO_SOCKET_NUMBER  5 /* socket number to lock to */
#define AR_SESS_POOLED                 6 /* indicates if session is pooled */
#define AR_SESS_CLIENT_TYPE            7 /* client type of the api program */
#define AR_SESS_VUI_TYPE               8 /* vui type of the vui */
#define AR_SESS_OVERRIDE_PREV_IP       9 /* flag indicates if caller would like to    */
                                         /* override the session from the previous IP */
#define AR_SESS_API_CMD_LOG           10 /* name of API command log */
#define AR_SESS_API_RES_LOG           11 /* name of API result log */

#define AR_SESS_CONTROL_PROP_DESIGN_OVERLAYGROUP  12 /* This property is to be set if     */
                                                     /* caller wants to set overlay group */
                                                         /* for design time operations  */
#define AR_SESS_CONTROL_PROP_API_OVERLAYGROUP     13 /* This property is to be set if     */
                                                     /* caller wants to set overlay group */
                                                         /* for runtime(get) operations  */

#define AR_SESS_CONTROL_PROP_GRANULAR_OVERLAY_RETRIEVE_MODE  14 /* This property is to be set if caller ONLY  */
                                                                /* wants to see extended/overwritten granular */
                                                                /* overlay attributes at design time          */
/* XML API Input/Output Document */
#define AR_XML_DOC_CHAR_STR       1 /* character string */
#define AR_XML_DOC_FILE_NAME      2 /* file name */
#define AR_XML_DOC_URL            3 /* URL */
#define AR_XML_DOC_FILE_HANDLE    4 /* file handle */

typedef struct ARXMLInputDoc
{
   unsigned int   docType; /* AR_XML_DOC_XX */
   union
   {
      char  *charBuffer;
      char  *fileName;
      char  *url;
   } u;

}  ARXMLInputDoc;

typedef struct ARXMLOutputDoc
{
   unsigned int   docType; /* AR_XML_DOC_XX */
   union
   {
      char          *charBuffer;
      char          *fileName;
      unsigned int   fileHandle;
   } u;

}  ARXMLOutputDoc;

typedef struct ARXMLParsedStream
{
   void   *xmlStream;

}  ARXMLParsedStream;

typedef struct ARXMLParserHandle
{
   void  *handle;

}  ARXMLParserHandle;


/* public key encryption algorithms */
#define AR_ENC_ECC_163             1  /* OBSOLETED; do not reuse this value */
#define AR_ENC_ECC_239             2  /* OBSOLETED; do not reuse this value */
#define AR_ENC_ECC_571             3  /* OBSOLETED; do not reuse this value */
#define AR_ENC_RMOD_512            4  /* RSA encryption, modulus 512 bits */
#define AR_ENC_RMOD_1024           5  /* RSA encryption, modulus 1024 bits */
#define AR_ENC_RMOD_2048           6  /* RSA encryption, modulus 2048 bits */


/* data encrpytion algorithms */
#define AR_ENC_DES_SINGLE_KEY_CBC  1  /* Single DES, Cipher Block Chaining mode */
#define AR_ENC_RC4_KEY_LEN_128     2  /* RC4 encryption, key length of 128 bits */
#define AR_ENC_RC4_KEY_LEN_2048    3  /* RC4 encryption, key length of 2048 bits */
#define AR_ENC_RC4_KEY_LEN_64      4  /* RC4 encryption, key length of 64 bits */
#define AR_ENC_RC4_KEY_LEN_56      5  /* RC4 encryption, key length of 56 bits */

#define AR_ENC_AES_KEY_LEN_128       6  /* AES encryption, key length of 128 bits */
#define AR_ENC_AES_KEY_LEN_256       7  /* AES encryption, key length of 256 bits  */
#define AR_ENC_AES_FIPS_KEY_LEN_128  8  /* AES encryption, key length of 128 bits (FIPS) */
#define AR_ENC_AES_FIPS_KEY_LEN_256  9  /* AES encryption, key length of 256 bits (FIPS) */

/* BitMask values for setting encryption options */
#define ENABLE_FIPS_MODE           1
#define ENABLE_FIPS_DUAL_MODE      2

#define FIPS_SERVER_MODE         1
#define FIPS_CLIENT_MODE         2
#define FIPS_STATUS              3
#define DATA_ENCRYPTION          4
#define DATA_ALGORITHM           5
#define FIPS_DUAL_MODE           6
#define SECURITY_POLICY          7
#define DATAKEY_INTERVAL         8
#define PUBLIC_KEY_ALGORITHM     9
#define PUBLIC_KEY_INTERVAL      10
#define NEW_FIPS_SERVER_MODE     11
#define NEW_DATA_ENCRYPTION      12
#define NEW_DATA_ALGORITHM       13
#define NEW_SECURITY_POLICY      14
#define NEW_DATAKEY_INTERVAL     15
#define NEW_PUBLIC_KEY_ALGORITHM 16
#define NEW_PUBLIC_KEY_INTERVAL  17
#define DATA_ENCRYPTION_LEVEL    18
#define LIBRARY_ENCRYPTION_LEVEL 19
#define NEW_FIPS_DATA_ALGORITHM  20


typedef struct ARDateStruct
{
   int   year;      /* range: -4912 to 9999 */
   int   month;     /* range: 1 to 12       */
   int   day;       /* range: 1 to 31       */

}  ARDateStruct;

#define AR_DATEPARTS_YEAR     1
#define AR_DATEPARTS_MONTH    2
#define AR_DATEPARTS_DAY      3
#define AR_DATEPARTS_WEEK     4
#define AR_DATEPARTS_WEEKDAY  5


/* When using a rolling 100 year span for two digit */
/* years, this increment is added to the current    */
/* year to calculate the two digit year cutoff      */
/* (e.g., year=2002, increment=29 ==> cutoff=2031). */
#define AR_TWO_DIGIT_YEAR_CUTOFF_INCREMENT   29


/* display properties that are localizable */
#define AR_LOCALIZABLE_DISPLAY_PROPS \
   AR_DPROP_LABEL, \
   AR_DPROP_TEXT, \
   AR_DPROP_HTML_TEXT, \
   AR_DPROP_BUTTON_TEXT, \
   AR_DPROP_MENU_TEXT, \
   AR_DPROP_MENU_HELP, \
   AR_DPROP_TOOLTIP, \
   AR_DPROP_ALIAS_SINGULAR, \
   AR_DPROP_ALIAS_PLURAL, \
   AR_DPROP_ALIAS_SHORT_SINGULAR, \
   AR_DPROP_ALIAS_SHORT_PLURAL, \
   AR_DPROP_ENUM_LABELS, \
   AR_DPROP_ATTACH_ADD_LABEL, \
   AR_DPROP_ATTACH_DELETE_LABEL, \
   AR_DPROP_ATTACH_DISPLAY_LABEL, \
   AR_DPROP_ATTACH_SAVE_LABEL, \
   AR_DPROP_ATTACH_LABEL_TITLE, \
   AR_DPROP_ATTACH_FILENAME_TITLE, \
   AR_DPROP_ATTACH_FILESIZE_TITLE, \
   AR_DPROP_TABLE_CHUNK_NEXT, \
   AR_DPROP_TABLE_CHUNK_PREV, \
   AR_DPROP_TABLE_NOT_REFRESHED, \
   AR_DPROP_TABLE_ENTRIES_RETURNED, \
   AR_DPROP_TABLE_AUTOREFRESH, \
   AR_DPROP_TABLE_SELECT_ALL, \
   AR_DPROP_TABLE_DESELECT_ALL, \
   AR_DPROP_TABLE_REFRESH, \
   AR_DPROP_TABLE_REPORT, \
   AR_DPROP_TABLE_DELETE, \
   AR_DPROP_TABLE_READ, \
   AR_DPROP_TABLE_UNREAD, \
   AR_DPROP_TABLE_ROOT_NODE_IMAGE, \
   AR_DPROP_TABLE_ROOT_NODE_ALT_TEXT, \
   AR_DPROP_TABLE_COL_IMAGE_LIST, \
   AR_OPROP_VIEW_LABEL_WEB_ALIAS


/* browser types for entry points */
#define AR_ENTRYPOINT_BROWSER_TYPE_IE       1
#define AR_ENTRYPOINT_BROWSER_TYPE_NN4      2
#define AR_ENTRYPOINT_BROWSER_TYPE_NN6      3
#define AR_ENTRYPOINT_BROWSER_TYPE_NN7      4

/* entry point types */
#define AR_ENTRYPOINT_TYPE_AL_GUIDE         1
#define AR_ENTRYPOINT_TYPE_DEFAULT_SEARCH   2
#define AR_ENTRYPOINT_TYPE_DEFAULT_NEW      3


#define AR_XML_FORM_MAP_TYPE_EMBEDDED       1
#define AR_XML_FORM_MAP_TYPE_REFERENCE      2

#define AR_XML_VALINFO_USERNAME             1
#define AR_XML_VALINFO_PASSWORD             2
#define AR_XML_VALINFO_UT_PASSWORD_TYPE     3

/* forward declarations */
struct ARComplexEntryGetIn;
struct ARComplexEntryGetOut;
struct ARComplexEntryCreate;
struct ARComplexEntrySet;
struct ARComplexEntryService;
struct ARComplexEntryServiceOut;

typedef struct ARComplexEntryGetInList
{
   unsigned int                 numItems;
   struct ARComplexEntryGetIn  *list;

}  ARComplexEntryGetInList;


typedef struct ARComplexEntryGetIn
{
   ARQualifierStruct         qualifier;
   ARNameType                docMappingName;
   ARNameType                portName;
   ARNameType                operationName;
   ARNameType                inputMappingName;
   ARNameType                outputMappingName;
   ARNameType                formName;
   int                       mapType;      /* AR_XML_FORM_MAP_TYPE_<> */
   ARInternalId              primaryKeyId;
   ARInternalId              distinguishingKeyId;
   ARInternalId              foreignKeyId;
   ARInternalIdList          fieldIdList;
   ARComplexEntryGetInList   complexChildren;

}  ARComplexEntryGetIn;



typedef struct ARComplexEntryGetOutList
{
   unsigned int                  numItems;
   struct ARComplexEntryGetOut  *list;

}  ARComplexEntryGetOutList;


typedef struct ARComplexEntryGetOut
{
   AREntryIdList              entryId;
   ARFieldValueList           fieldValueList;
   unsigned int               numLists;
   ARComplexEntryGetOutList  *complexChildrenLists;

}  ARComplexEntryGetOut;


typedef struct ARComplexEntryCreateList
{
   unsigned int                  numItems;
   struct ARComplexEntryCreate  *list;

}  ARComplexEntryCreateList;

typedef struct ARComplexEntryCreate
{
   ARNameType                    formName;           /* IN */
   ARServerNameType              serverName;         /* IN */
   ARInternalId                  foreignKeyFieldId;  /* IN */
   struct ARComplexEntryCreate  *parent;             /* IN */
   ARComplexEntryCreateList      children;           /* IN */
   ARFieldValueList              fieldValueList;     /* IN */
   ARFieldValueStruct            primaryKey;         /* IN/OUT */
   ARFieldValueStruct            distinguishingKey;  /* IN/OUT */
   AREntryIdType                 entryId;            /* OUT */

}  ARComplexEntryCreate;


typedef struct ARComplexEntrySetList
{
   int                        numItems;
   struct ARComplexEntrySet  *list;

}  ARComplexEntrySetList;

typedef struct ARComplexEntrySet
{
   ARNameType                 formName;           /* IN */
   ARServerNameType           serverName;         /* IN */
   ARFieldValueStruct         primaryKey;         /* IN */
   ARFieldValueStruct         distinguishingKey;  /* IN */
   ARInternalId               foreignKeyFieldId;  /* IN */
   struct ARComplexEntrySet  *parent;             /* IN */
   ARComplexEntrySetList      children;           /* IN */
   ARFieldValueList           fieldValueList;     /* IN */

}  ARComplexEntrySet;

typedef struct ARComplexEntryOptions
{
   int                getEntries;      /* IN (0 or a positive number): 0: get all */
   int                startAt;         /* IN (0 or a positive number) */
   int                setEntries;      /* IN (1 or 2): 1: set all, 2: set first */
   int                setFullDocument; /* IN (1 or 2) full document or partial document */
   int                mergeOption;     /* IN (AR_IMPORT_OPT_DATA_<>) */
   ARInternalIdList   mergeQualifier;  /* IN field Id list for the merge qualifier */

}  ARComplexEntryOptions;

typedef struct ARComplexEntryServiceList
{
   unsigned int                  numItems;
   struct ARComplexEntryService  *list;
} ARComplexEntryServiceList;

typedef struct ARComplexEntryService
{
   ARNameType                    formName;           /* IN */
   ARServerNameType              serverName;         /* IN */
   ARFieldValueStruct            primaryKey;         /* IN */
   ARFieldValueStruct            distinguishingKey;  /* IN */
   ARInternalId                  foreignKeyFieldId;  /* IN */
   struct ARComplexEntryService  *parent;            /* IN */
   ARComplexEntryServiceList     children;           /* IN */
   ARFieldValueList              fieldValueList;     /* IN */
}  ARComplexEntryService;

typedef struct ARComplexEntryServiceOutList
{
   unsigned int                     numItems;
   struct ARComplexEntryServiceOut  *list;
} ARComplexEntryServiceOutList;

typedef struct ARComplexEntryServiceOut
{
   AREntryIdList                 entryId;
   ARFieldValueList              fieldValueList;
   unsigned int                  numLists;
   ARComplexEntryServiceOutList  *complexChildrenList;
}  ARComplexEntryServiceOut;

typedef struct ARXMLValueInfoStruct
{
   int             infoType;
   ARValueStruct   value;

}  ARXMLValueInfoStruct;

typedef struct ARXMLValueInfoList
{
   int                           numItems;
   struct ARXMLValueInfoStruct  *infoList;

}  ARXMLValueInfoList;

/* Structures used in the definition file parsing related operations. It is */
/* often useful to identify list of objects present within a definition     */
/* file. Following structures provide necessary data structures to classify */
/* any of the found objects as appropriate.                                 */

/* forward declaration */
struct ARObjectInfoStruct;

typedef struct ARObjectInfoList
{              /* list of 0 or more server object information entries */
   unsigned int                numItems;
   struct ARObjectInfoStruct  *objectInfoList;

}  ARObjectInfoList;

typedef struct ARObjectInfoStruct
{              /* type information about a server object */
   unsigned int                type;              /* AR_STRUCT_ITEM_... */
   unsigned int                subType;           /* subType to further classify this object */
                                                  /* (Currently applies to containers only, */
                                                  /*        so ARCON_... )*/
   ARNameType                  name;              /* name of the object */
   ARNameType                  appBlockName;      /* name of the app, the current object is in */
   struct ARObjectInfoList     objectInfoList;    /* objects nested within the current object */
                                                  /*  (applies to lock blocks only) */

}  ARObjectInfoStruct;


#define AR_APP_TYPE_LOCAL                 1
#define AR_APP_TYPE_DISTRIBUTABLE         2

/* declarations for bulk entry operations */

#define AR_BULK_ENTRY_CREATE              1
#define AR_BULK_ENTRY_SET                 2
#define AR_BULK_ENTRY_DELETE              3
#define AR_BULK_ENTRY_MERGE               4
#define AR_BULK_ENTRY_XMLCREATE           5
#define AR_BULK_ENTRY_XMLSET              6
#define AR_BULK_ENTRY_XMLDELETE           7

#define AR_BULK_ENTRY_ACTION_SEND         1
#define AR_BULK_ENTRY_ACTION_CANCEL       2

typedef struct AREntryReturn
{
   AREntryIdType   entryId;
   ARStatusList    status;
} AREntryReturn;

typedef struct ARXMLEntryReturn
{
   char          *outputDoc;
   ARStatusList   status;
} ARXMLEntryReturn;

typedef struct ARBulkEntryReturn
{
   unsigned int   entryCallType;
   union
   {
      AREntryReturn      createEntryReturn;
      ARStatusList       setEntryReturn;
      ARStatusList       deleteEntryReturn;
      AREntryReturn      mergeEntryReturn;
      ARXMLEntryReturn   xmlCreateEntryReturn;
      ARXMLEntryReturn   xmlSetEntryReturn;
      ARStatusList       xmlDeleteEntryReturn;
   } u;
} ARBulkEntryReturn;

typedef struct ARBulkEntryReturnList
{
   unsigned int        numItems;
   ARBulkEntryReturn  *entryReturnList;
} ARBulkEntryReturnList;

/* declarations for entry block operations */

typedef struct AREntryBlockStruct {
   unsigned int    blockSize;
   unsigned char  *entryBlock;
} AREntryBlockStruct;

typedef struct AREntryBlockList {
   unsigned int         numItems;
   AREntryBlockStruct  *entryBlockList;
} AREntryBlockList;

/* declarations for system logging options */

#define AR_SYSTEM_LOGGING_OPTION_NONE     0x0001

/* declarations for external authentication return data capabilities */

#define AR_EXT_AUTH_DATA_NO_EMAIL_ADDR        0x0001
#define AR_EXT_AUTH_DATA_NO_NOTIFY_MECH       0x0002
#define AR_EXT_AUTH_DATA_NO_GROUP_IDS         0x0004
#define AR_EXT_AUTH_DATA_NO_LICENSE_INFO      0x0008
#define AR_EXT_AUTH_DATA_NO_NOTIF_VALIDATION  0x0010

/* exception diagnostic options */

#define AR_EXCEPTION_DIAG_INCLUDE_ALL         0
#define AR_EXCEPTION_DIAG_EXCLUDE_STACK       1

/* Bit mask for audit set option */
#define AR_AUDIT_FORCE_DISABLE                0x0001  /* Forcfully disable the audit on the base form */
                                                      /* though the audit on the dependent form is enabled */
#define AR_AUDIT_ALLOW_MOVE                   0x0002  /* Allow audit form to change App owner when importing */
                                                      /* both audit form and base form                       */
#define AR_AUDIT_UPDATE_ONLY                  0x0004  /* Force Audit and Archive changes only */


/* declarations for image objects */
typedef struct ARImageDataStruct
{
   unsigned int    numItems;      /* number of bytes in image */
   unsigned char  *bytes;         /* not NULL terminated      */
} ARImageDataStruct;

typedef struct ARImageDataList
{
   unsigned int       numItems;
   ARImageDataStruct *imageList;

} ARImageDataList;    /* list of 0 or more image data structs */

typedef struct ARObjectChangeTimestamps
{
   unsigned int objectType;
   ARTimestamp  createTime;
   ARTimestamp  changeTime;
   ARTimestamp  deleteTime;
} ARObjectChangeTimestamps;

typedef struct ARObjectChangeTimestampList
{
   unsigned int    numItems;
   ARObjectChangeTimestamps *objectChanges;
} ARObjectChangeTimestampList;

/* A set of defines for the WFD stage, used in CurrentLoc struct */
#define  WFD_IDLE             0
#define  WFD_RUNNING          1
#define  WFD_BEFORE_API       2
#define  WFD_BEFORE_QUAL      3
#define  WFD_PHASE_1          4
#define  WFD_PHASE_2          5
#define  WFD_PHASE_3          6
#define  WFD_ESCL             7
#define  WFD_BEFORE_CMDB      8
#define  WFD_AFTER_API        9

/* defines for the WFD execution mode, used in CurrentLoc struct */
#define  WFD_EXECUTE_STEP   0
#define  WFD_EXECUTE_RUN    1
#define  WFD_EXECUTE_RESV_1 2
#define  WFD_EXECUTE_RESV_2 3

/* defines for the WFD execute command result */
#define  WFD_EXEC_NOTHING     0
#define  WFD_EXEC_STEPPED     1
#define  WFD_EXEC_BRK_POINT   2
#define  WFD_EXEC_USER_BRK    3
#define  WFD_EXEC_CONTINUE    4
#define  WFD_EXEC_QUERY       5

typedef struct ARWfdCurrentLocation
{
   /* These fields mirror the fields in the RPC structures */
   char                 *ApiCall;      /* name of the API call */
   char                 *SchemaName;   /* schema name */
   AREntryIdList        Entrys;        /* list of entrys */
   char                 *Filter;       /* Name of the filter */
   unsigned int         Stage;         /* start, qual, phase1,1,3 etc. */
   ARBoolean            ElsePath;        /* True if doing if actions, false if else */
   unsigned int         ActionNo;      /* Action index */
   char                 *ActionStr;    /* Extra text associated with action */
   ARBoolean            ActionDeferred;   /* True if this action deferred to later phase */
   /* Fields below here are used for other things, like building stacks, etc. */
   struct ARFilterContextStruct  *filtContext;  /* filter context for this location */
   struct ARSchemaContextStruct  *schemaContext; /* schema context for this location */
   struct ARWfdCurrentLocation   *next;         /* link for use creating stack */
} ARWfdCurrentLocation;

typedef struct ARWfdRmtBreakpoint {
   unsigned int         id;                     /* BP identifier */
   ARBoolean            disable;                /* disabled if TRUE */
   unsigned int         passcount;              /* passcount */
   struct ARQualifierStruct    *bpQualifier;    /* BP qualifier */
   ARNameType           *filter;                /* filter name */
   ARNameType           *schema;                /* schema name or any (*) */
   unsigned int         stage;                  /* workflow execution stage p1,2 etc. */
   unsigned int         actioNo;                /* action index */
   ARBoolean            elsePath;               /* must be on else path if true */
} ARWfdRmtBreakpoint;

typedef struct ARWfdRmtBreakpointList
{
   unsigned int               numItems;
   struct ARWfdRmtBreakpoint  *bpList;
}  ARWfdRmtBreakpointList;             /* array list of 0 or more breakpoints */

typedef struct ARWfdBreakpointLink
{
   /* A few fields for managing breakpoints */
   struct ARWfdBreakpointLink       *next;
   unsigned int                     timesPassed;
   /* and the bp, itself */
   ARWfdRmtBreakpoint               bp;
}  ARWfdBreakpointLink;                /* linked list of breakpoints */

typedef struct ARWfdUserContext {
   ARAccessNameType           user;
   unsigned int               notifyMech;
   struct ARUserLicenseList   licenseList;
   unsigned int               licenseType;
   unsigned int               currentLicenseType;
   ARBoolean                  doWorkflowFTS;
   struct ARInternalIdList    groupList;
   ARBoolean                  adminFlag;
   ARBoolean                  subadminFlag;
} ARWfdUserContext;

/* declarations for db consistency check for assignShortLong */
/* propShortLong and queryShortLong */
#define  AR_CHECKDB_TYPE_NONE          0
#define  AR_CHECKDB_ASSIGN_SHORT_LONG  1
#define  AR_CHECKDB_PROP_SHORT_LONG    2
#define  AR_CHECKDB_QUERY_SHORT_LONG   3

#define AR_REC_QRY_PARENT_ALIAS  "parent"
#define AR_SQL_MS_ALIAS_PREFIX  'J' /* character prefix to column names */

/* The structures are for multi schema fields */
typedef struct ARMultiSchemaFieldIdStruct {
   ARNameType   queryFromAlias; 
   ARInternalId fieldId;
} ARMultiSchemaFieldIdStruct; 

/* possible values for the ARMultiSchemaFieldFuncStruct "funcId" member */
#define AR_MULTI_SCHEMA_FUNC_NONE             0
#define AR_MULTI_SCHEMA_FUNC_COUNT            1
#define AR_MULTI_SCHEMA_FUNC_SUM              2
#define AR_MULTI_SCHEMA_FUNC_AVG              3
#define AR_MULTI_SCHEMA_FUNC_MIN              4
#define AR_MULTI_SCHEMA_FUNC_MAX              5
#define AR_MULTI_SCHEMA_FUNC_LAST             5  /* last valid function */

typedef struct ARMultiSchemaFieldFuncStruct {
   ARNameType   queryFromAlias; 
   ARInternalId fieldId;
   int funcId;
} ARMultiSchemaFieldFuncStruct;

typedef struct ARMultiSchemaFieldIdList {
   unsigned int               numItems;
   ARMultiSchemaFieldIdStruct *listPtr; 
} ARMultiSchemaFieldIdList;

typedef struct ARMultiSchemaFieldFuncList {
   unsigned int               numItems;
   ARMultiSchemaFieldFuncStruct *listPtr;
} ARMultiSchemaFieldFuncList;

typedef struct ARMultiSchemaFuncCurrencyPartStruct {
   ARMultiSchemaFieldFuncStruct fieldFunc;
   unsigned int               partTag;
   ARCurrencyCodeType         currencyCode;
} ARMultiSchemaFuncCurrencyPartStruct;

typedef struct ARMultiSchemaStatHistoryValue   {
   ARNameType    queryFromAlias; /* which schema's status history */
   unsigned long enumVal;
   unsigned int  userOrTime;    
} ARMultiSchemaStatHistoryValue;

typedef struct ARMultiSchemaFuncStatHistoryValue   {
   ARNameType    queryFromAlias; /* which schema's status history */
   unsigned long enumVal;
   unsigned int  userOrTime;  
   int funcId;
} ARMultiSchemaFuncStatHistoryValue;

#define AR_VALUE_SET_QUERY  7 /* subquery used for "IN" or "EXISTS" operator */

/*
 * This version used in WHERE clauses (e.g., WHERE x < y)
 */
typedef struct ARMultiSchemaFieldValueOrArithStruct {
   unsigned int tag;
   union {
      size_t                                    noval_;
      ARMultiSchemaFieldIdStruct                fieldId;
      ARValueStruct                             value;
      struct ARMultiSchemaArithOpStruct         *arithOp;
      ARMultiSchemaFuncStatHistoryValue             statHistory;
      ARValueList                               valueSet;
      ARMultiSchemaFuncCurrencyPartStruct           *currencyField;
         /* now a ~Func~ since subqueries can include funcs: */
      struct ARMultiSchemaValueSetFuncQueryStruct *valueSetQuery;
   } u;
} ARMultiSchemaFieldValueOrArithStruct;

/*
 * This version used in HAVING clauses (e.g., HAVING MIN(x) < y)
 */
typedef struct ARMultiSchemaFieldFuncValueOrArithStruct {
   unsigned int tag;
   union {
      size_t                                    noval_;
      ARMultiSchemaFieldFuncStruct              fieldFunc;
      ARValueStruct                             value;
      struct ARMultiSchemaFuncArithOpStruct     *arithOp;
      ARMultiSchemaFuncStatHistoryValue             statHistory;
      ARValueList                               valueSet;
      ARMultiSchemaFuncCurrencyPartStruct           *currencyField;
      struct ARMultiSchemaValueSetFuncQueryStruct   *valueSetQuery;
   } u;
} ARMultiSchemaFieldFuncValueOrArithStruct;


typedef struct ARMultiSchemaAndOrStruct 
{
   struct ARMultiSchemaQualifierStruct *operandLeft;
   struct ARMultiSchemaQualifierStruct *operandRight;
} ARMultiSchemaAndOrStruct;

typedef struct ARMultiSchemaFuncAndOrStruct
{
   struct ARMultiSchemaFuncQualifierStruct *operandLeft;
   struct ARMultiSchemaFuncQualifierStruct *operandRight;
} ARMultiSchemaFuncAndOrStruct;

typedef struct ARMultiSchemaArithOpStruct {
   unsigned int                           operation;
   ARMultiSchemaFieldValueOrArithStruct   operandLeft;
   ARMultiSchemaFieldValueOrArithStruct   operandRight;
} ARMultiSchemaArithOpStruct;

typedef struct ARMultiSchemaFuncArithOpStruct {
   unsigned int                           operation;
   ARMultiSchemaFieldFuncValueOrArithStruct   operandLeft;
   ARMultiSchemaFieldFuncValueOrArithStruct   operandRight;
} ARMultiSchemaFuncArithOpStruct;

typedef struct ARMultiSchemaRelOpStruct {
   unsigned int                           operation;
   ARMultiSchemaFieldValueOrArithStruct   operandLeft;
   ARMultiSchemaFieldValueOrArithStruct   operandRight;
} ARMultiSchemaRelOpStruct;

typedef struct ARMultiSchemaFuncRelOpStruct {
   unsigned int                           operation;
   ARMultiSchemaFieldFuncValueOrArithStruct   operandLeft;
   ARMultiSchemaFieldFuncValueOrArithStruct   operandRight;
} ARMultiSchemaFuncRelOpStruct;

typedef struct ARMultiSchemaQualifierStruct {
   unsigned int operation;
   union {
     ARMultiSchemaAndOrStruct             andor;
     struct ARMultiSchemaQualifierStruct  *notQual;
     struct ARMultiSchemaRelOpStruct      *relOp;
     ARMultiSchemaFieldIdStruct           fieldId;
   } u;
} ARMultiSchemaQualifierStruct;

typedef struct ARMultiSchemaFuncQualifierStruct {
   unsigned int operation;
   union {
     ARMultiSchemaFuncAndOrStruct             andor;
     struct ARMultiSchemaFuncQualifierStruct  *notQual;
     struct ARMultiSchemaFuncRelOpStruct      *relOp;
     ARMultiSchemaFieldFuncStruct          fieldFunc;
   } u;
} ARMultiSchemaFuncQualifierStruct;

/* possible values for the ARMultiSchema{,Func}QueryFromStruct "type" member */
#define AR_MULTI_SCHEMA_SCHEMA_NAME             0
#define AR_MULTI_SCHEMA_NESTED_QUERY            1
#define AR_MULTI_SCHEMA_RECURSIVE_QUERY         2

/* possible values for the ARMultiSchema{,Func}QueryFromStruct "joinType" member */
#define AR_MULTI_SCHEMA_JOIN_INNER              0
#define AR_MULTI_SCHEMA_JOIN_LEFT               1
#define AR_MULTI_SCHEMA_JOIN_RIGHT              2

typedef struct ARMultiSchemaQueryFromStruct {  /* XXX obsolete */
   unsigned int                                 type;
   union {
      ARNameType                                schemaName;
      struct ARMultiSchemaNestedQueryStruct     *nestedQuery;
      struct ARMultiSchemaRecursiveQueryStruct  *recursiveQuery;      
   } u;

   ARNameType                                   queryFromAlias;
   unsigned int                                 joinType;
   struct ARMultiSchemaQualifierStruct          *joinQual; 
} ARMultiSchemaQueryFromStruct;

typedef struct ARMultiSchemaFuncQueryFromStruct {
   unsigned int                                 type;
   union {
      ARNameType                                schemaName;
      struct ARMultiSchemaNestedFuncQueryStruct     *nestedQuery;
      struct ARMultiSchemaRecursiveFuncQueryStruct  *recursiveQuery;      
   } u;

   ARNameType                                   queryFromAlias;
   unsigned int                                 joinType;
   struct ARMultiSchemaQualifierStruct          *joinQual; 
} ARMultiSchemaFuncQueryFromStruct;

typedef struct ARMultiSchemaQueryFromList  {  /* XXX obsolete */
   unsigned int                  numItems;
   ARMultiSchemaQueryFromStruct  *listPtr;
} ARMultiSchemaQueryFromList;

typedef struct ARMultiSchemaFuncQueryFromList  {
   unsigned int                  numItems;
   ARMultiSchemaFuncQueryFromStruct  *listPtr;
} ARMultiSchemaFuncQueryFromList;

/* Default value for max depth for hierarchical query */
#define AR_MAX_RECURSION_LEVEL_DEFAULT                    25

/* Default value for the number of vendor temp tables. */
#define AR_MAX_VENDOR_TEMP_TABLES_DEFAULT                 1

typedef struct ARMultiSchemaRecursiveQueryStruct { /* XXX obsolete */
   ARNameType                       recursiveSchemaAlias;
   ARMultiSchemaQueryFromList       queryFromList;
   ARMultiSchemaFieldIdList         getListFields;
   ARMultiSchemaQualifierStruct     *startQual;
   ARMultiSchemaQualifierStruct     *recursionQual;
   int                              levelsToRetrieve;
} ARMultiSchemaRecursiveQueryStruct;

typedef struct ARMultiSchemaRecursiveFuncQueryStruct {
   ARNameType                       recursiveSchemaAlias;
   ARMultiSchemaFuncQueryFromList   queryFromList;
   ARMultiSchemaFieldFuncList       getListFuncs;
   ARMultiSchemaQualifierStruct     *startQual;
   ARMultiSchemaQualifierStruct     *recursionQual;
   int                              levelsToRetrieve;
   ARMultiSchemaFieldIdList         groupBy;
   ARMultiSchemaFuncQualifierStruct *having;
} ARMultiSchemaRecursiveFuncQueryStruct;

typedef struct ARMultiSchemaNestedQueryStruct {   /* XXX obsolete */
   ARMultiSchemaQueryFromList       queryFromList;
   ARMultiSchemaFieldIdList         getListFields;
   ARMultiSchemaQualifierStruct     *qualifier;
} ARMultiSchemaNestedQueryStruct;

typedef struct ARMultiSchemaNestedFuncQueryStruct {   
   ARMultiSchemaFuncQueryFromList   queryFromList;
   ARMultiSchemaFieldFuncList       getListFuncs;
   ARMultiSchemaQualifierStruct     *qualifier;
   ARMultiSchemaFieldIdList         groupBy;
   ARMultiSchemaFuncQualifierStruct *having;
} ARMultiSchemaNestedFuncQueryStruct;

typedef struct ARMultiSchemaValueSetQueryStruct {   /* XXX obsolete */
   ARMultiSchemaQueryFromList       queryFromList;
   ARMultiSchemaFieldIdStruct       fieldId;
   ARMultiSchemaQualifierStruct     *qualifier;
} ARMultiSchemaValueSetQueryStruct;

typedef struct ARMultiSchemaValueSetFuncQueryStruct {   
   ARMultiSchemaFuncQueryFromList   queryFromList;
   ARMultiSchemaFieldIdStruct       fieldId;
   ARMultiSchemaQualifierStruct     *qualifier;
   ARMultiSchemaFieldIdList         groupBy;
   ARMultiSchemaFuncQualifierStruct *having;
} ARMultiSchemaValueSetFuncQueryStruct;

typedef struct ARMultiSchemaSortStruct {
   ARMultiSchemaFieldIdStruct fieldId;
   unsigned int               sortOrder;
} ARMultiSchemaSortStruct;

typedef struct ARMultiSchemaSortList {
   int                     numItems;
   ARMultiSchemaSortStruct *listPtr;
} ARMultiSchemaSortList;

typedef struct ARMultiSchemaFieldValueStruct {
   ARMultiSchemaFieldIdStruct fieldId;
   ARValueStruct              value;
} ARMultiSchemaFieldValueStruct;

typedef struct ARMultiSchemaFieldValueList
{
   unsigned int                   numItems;
   ARMultiSchemaFieldValueStruct  *listPtr;

} ARMultiSchemaFieldValueList;          /* list of 0 or more multi schema field/value pairs */

typedef struct ARMultiSchemaFieldValueListList {
   unsigned int                 numItems;
   ARMultiSchemaFieldValueList *listPtr;
} ARMultiSchemaFieldValueListList;

typedef struct ARMultiSchemaFieldFuncValueStruct {
   ARMultiSchemaFieldFuncStruct fieldId;
   ARValueStruct              value;
} ARMultiSchemaFieldFuncValueStruct;

typedef struct ARMultiSchemaFieldFuncValueList {
   unsigned int                   numItems;
   ARMultiSchemaFieldFuncValueStruct  *listPtr;
} ARMultiSchemaFieldFuncValueList;          /* list of 0 or more multi schema field/value pairs */

typedef struct ARMultiSchemaFieldFuncValueListList {
   unsigned int                 numItems;
   ARMultiSchemaFieldFuncValueList *listPtr;
} ARMultiSchemaFieldFuncValueListList;

/* A set of defines for the version control task, used in task related structs */
#define  AR_TASK_STATE_NONE             0x00000000
#define  AR_TASK_STATE_OPEN             0x00000001  /* 0x00000002 reserved for current or default*/
#define  AR_TASK_STATE_COMMIT           0x00000004
#define  AR_TASK_STATE_ROllEDBACK       0x00000008
#define  AR_TASK_STATE_OPEN_MASK        AR_TASK_STATE_OPEN
#define  AR_TASK_STATE_COMPLETE_MASK    (AR_TASK_STATE_COMMIT | AR_TASK_STATE_ROllEDBACK)

#define  AR_TASK_NODE_OP_NONE           0x00000000
#define  AR_TASK_NODE_OP_CHANGE         0x00000001
#define  AR_TASK_NODE_OP_ADD            0x00000002
#define  AR_TASK_NODE_OP_REMOVE         0x00000004
#define  AR_TASK_OBJ_OP_NONE            0x00000000
#define  AR_TASK_OBJ_OP_CHANGE          0x00000001
#define  AR_TASK_OBJ_OP_ADD             0x00000002
#define  AR_TASK_OBJ_OP_REMOVE          0x00000004

typedef struct ARTaskCheckpointObj {
   ARInternalId         taskId;               /* task identifier, the foreign key for this checkpoint associates the task */
   ARInternalId         checkpointId;         /* checkpoint identifier, the foreign key for this checkpoint associates a check point. task->checkpointList->checkpoint */
   ARNameType           objName;              /* object name in this node from OML form */
   int                  objType;              /* object type in this node from OML form */
   char                *objOmlVersionGUID;    /* object version GUID for this node in OML form */
} ARTaskCheckpointObj;                        /* identify a particular version of an object in OML form */

typedef struct ARTaskCheckpointObjList
{
   unsigned int           numItems;
   ARTaskCheckpointObj   *listPtr;
}  ARTaskCheckpointObjList;                   /* array list of 0 or more object nodes */

typedef struct ARTaskCheckpoint {
   ARInternalId         taskId;               /* task identifier, the foreign key for this checkpoint associates the task */
   ARInternalId         checkpointId;         /* checkpoint identifier */
   ARNameType           checkpointName;       /* name of the checkpoint */
   ARTimestamp          timestamp;            /* last modified time any aspect of this task last changed  */
   ARTextString         description;          /* optional description a CLOB field */
   ARPropList           objPropList;          /* regular object properties */
   ARTaskCheckpointObjList cpObjNodeList;    /* pointer to link cache entries for checkpoint's object node list */
} ARTaskCheckpoint;

typedef struct ARTaskCheckpointList
{
   unsigned int           numItems;
   ARTaskCheckpoint      *listPtr;
}  ARTaskCheckpointList;                      /* array list of 0 or more checkpoints */

typedef struct ARTask {/* task this struct contains info about */
   ARInternalId           taskId;             /* task identifier */
   ARNameType             taskName;           /* task name */
   ARTextString           description;        /* optional description a CLOB field */
   ARAccessNameType       owner;              /* owner of the task */
   ARAccessNameType       lastChanged;        /* user who last changed the task */
   int                    state;              /* current state of the task, i.e. open, complete, etc.*/
   ARTimestamp            timestamp;          /* last modified time any aspect of this task last changed  */
   ARPropList             objPropList;        /* regular object properties */
   ARTaskCheckpoint       baseline;           /* pointer to baseline, which has checkpointId=0, for objects this task all associated */
   ARTaskCheckpointList   checkpointList;     /* pointer to link cache entries for checkpoint list */
} ARTask;

typedef struct ARTaskList
{
   unsigned int   numItems;
   ARTask        *listPtr;
}  ARTaskList;                                /* array list of 0 or more tasks */

/* following for API and RPC use */
typedef struct ARVercntlObject {
   ARNameType           objName;              /* object name */
   int                  objType;              /* object type */
} ARVercntlObject;                          

typedef struct ARVercntlObjectList
{
   unsigned int      numItems;
   ARVercntlObject  *listPtr;

}  ARVercntlObjectList;                       /* list of 0 or more objects */

typedef struct ARTaskInfo {/* taskInfo this struct contains info about. It does not contain baseline and checkpoints */
   ARInternalId           taskId;             /* task identifier */
   ARNameType             taskName;           /* task name */
   ARTextString           description;        /* optional description a CLOB field */
   ARAccessNameType       owner;              /* owner of the task */
   ARAccessNameType       lastChanged;        /* user who last changed the task */
   int                    state;              /* current state of the task, i.e. open, complete, etc.*/
   ARTimestamp            timestamp;          /* last modified time any aspect of this task last changed  */
   ARPropList             objPropList;        /* regular object properties */
} ARTaskInfo;

typedef struct ARTaskInfoList
{
   unsigned int   numItems;
   ARTaskInfo    *listPtr;

}  ARTaskInfoList;                           /* list of 0 or more objects */

#ifdef __cplusplus
/* This closes the 'extern "C" {' statement started at the top of this      */
/* file.  This is needed so C++ applications don't compile these structures */
/* as C++, which creates name-mangling and structure padding problems.      */
}
#endif

#endif

/* preserve this trailing newline for UNIX compilers */

