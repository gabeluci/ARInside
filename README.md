# ARInside: BMC Remedy Documentation Generator

ARInside is a command-line application that generates static HTML pages to document BMC Remedy ARSystem workflow. The program can be run in online mode connecting to an ARSystem server or in file mode using an XML server definition export file. In advance a Packing List with all ARSystem server objects to exclude from documentation can be specified in the application configuration.

ARInside was initially designed by Stefan Nerlich, who made the source code public in mid 2009. Since then it had been maintained by a few developers and released under the "General Public License Version 2" (GPLv2). Those contributors have moved on. It's no longer actively maintained and the original website is no longer up. With that being said, it's still the best free method available to document your AR System.

Few changes have been made since moving to GitHub in August 2020. See the [release notes](src/RELEASE_NOTES.txt) for more details.

## Getting Started

A simple example of running ARInside would look like this:

```
arinside –i settings.ini –l Demo –p pass –s localhost
```

After that ARInside connects to your server and starts documenting all forms, fields and workflow. The `-i` argument specifies the configuration file. ARInside comes with a default configuration file named `settings.ini`. The `-l` switch defines the login name and `-p` the password ARInside will use to connect to the server specified by the `-s` switch. Depending on the size of your application it can take several hours to finish. Please be patient. If its finished, you'll find the generated documentation in the `TargetFolder` specified in `settings.ini`. Open `index.htm` with a web browser to begin browsing.

## Requirements

On Windows, the [Microsoft Visual C++ Redistributable for Visual Studio 2015, 2017 and 2019](https://support.microsoft.com/en-ca/help/2977003/the-latest-supported-visual-c-downloads) must be installed.

On all platforms, make sure the following requirements are fulfilled:

*   The specified username should have administrator rights. Otherwise the documentation will be incomplete.
*   ARInside supports AR-server version 7.1 and higher. It might also work with older versions. However testing focuses mainly on the specified versions.

## Command Line Arguments

The following table describes all the available command line options.

| Argument | Type | Description |
|----------|------|-------------|
| -i <string> | required | File Name of the configuration file |
| -s <string> | optional | ARSystem server name to connect |
| -l <string> | optional | Login Name used to connect to the ARSystem server |
| -p <string> | optional | Password |
| -t <integer> | optional | The port number that the program will use to communicate with the AR System server. If you do not specify this parameter or provide 0 for the port number, your program will use the port number supplied by the portmapper. This parameter is overridden by the ARTCPPORT environment variable. |
| -r <integer> | optional | The RPC port number of the server. Specify `390600` to use the admin server, a number from `390621` to `390634` or `390636` to `390669` or `390680` to `390694` to use a private server, or `0` (default) to use the fast or list server queue. This setting is overridden by the `ARRPC` environment variable. |
| -o <string> | optional | The output directory of the documentation. |
| --slow | optional | Disables fast object loading |
| -v | optional | If specified it enables verbose program output. |
| -h | optional | Shows more detailed command line usage information. |

### Examples

```
arinside.exe -s servername -l Demo -i settings.ini

arinside.exe -l Demo -s servername -p mypassword -i settings.ini

arinside.exe -p "my&password" -i settings.ini -s servername -l Demo

arinside.exe -s servername -l Demo -i "my settings.ini"

arinside.exe -s servername -l Demo -i "my settings.ini" -t 1044 -r 390621
```

### Notes

*   The order of the parameters is irrelevant
*   Parameters with special characters (for example empty spaces) can be surrounded by quotation marks

## Configuration File

The ARInside application settings can be configured using a simple text-file. ARInside comes with a [sample configuration file](src/settings.ini) you will need to change. The settings are grouped into four categories described below.

Starting with ARInside 3.0.1 you can save the connection information within the ini file. Some settings can be set on the command line too. If you do this, the command-line arguments take precedence over the ini-file settings.

#### Server Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| ServerName | String | <EMPTY> | The server name ARInside should connect to. |
| Username | String | <EMPTY> | Login name used to connect to the ARSystem server. |
| Password | String | <EMPTY> | Password used to connect to the ARSystem server. |
| TCPPort | Integer | `0` | The port number that the program will use to communicate with the AR System server. If you do not specify this setting or provide `0` for the port number, your program will use the port number supplied by the portmapper. This setting is overridden by the `ARTCPPORT` environment variable. |
| RPCPort | Integer | `0` | The RPC program number of the server. Specify `390600` to use the admin server, a number from `390621` to `390634` or `390636` to `390669` or `390680` to `390694` to use a private server, or `0` (default) to use the fast or list server queue. This setting is overridden by the `ARRPC` environment variable. |
| APITimeout | Integer | `0` | If you have a big amount of workflow on your server, it's possible that ARInside fails to load objects like e.g. Active Links. In this case you should increase the api-timeout. |
#### Application Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| TargetFolder | String | <EMPTY> | Relative or absolute path to the output directory where the documentation is saved. This setting could be overridden by the `-o` command line argument. |
| FileMode | Boolean | `FALSE` | Specify if the application will connect to an ARSystem server (`FileMode=FALSE`) or load information from a file specified by `ObjListXML` setting (`FileMode=TRUE`). |
| ObjListXML | String | <EMPTY> | An ARSystem Administrator server definition file in XML format. The parameter specifies the filename and is only used when `FileMode` is set to `TRUE`. Refer to the ARSystem Administrator Guide how to export server definitions in XML format. |
| UTF-8 | Boolean | `FALSE` | Refer to your ARSystem Database configuration if UTF-8 encoding is required. |
| BlackList | String | <EMPTY> | Name of an ARSystem PackingList with a list of ARSystem objects which should be excluded from the documentation. Refer to the ARSystem Administrator Guide about how to create a PackingList and add/remove objects to the list. |
| LoadServerInfoList | Boolean | `TRUE` | Load extended server informations. |
| CompactFolder | Boolean | `FALSE` | Use NTFS file system compression to save some disk space. The application uses the Windows [`compact`](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/compact) command. |
| DeleteExistingFiles | Boolean | `FALSE` | Delete all existing files in target folder. |
| OldNaming | Boolean | `FALSE` | Since ARInside 3.0.1 the file and folder names in the output directory are generated using the object name (i.e. the schema name). On previous versions a consecutive number was used. If you set this parameter to `TRUE`, the old file naming convention will be used. This option exists for backward compatibility. |
| GZCompression | Boolean | `FALSE` | With version 3.0.2 ARInside supports gzip-compressed html files. In combination with an Apache server you can access the compressed documentation. ARInside generates the needed `.htaccess` file as well. |
| OverlayMode | Boolean | `TRUE` | If this option is set to `TRUE` and the server's version is 7.6.04 and higher, ARInside will document additional details of the overlay-feature. |
#### Data Retrieval

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| LoadUserList | Boolean | `TRUE` | Load user data. Requires the following fields in the form:  RequestId (1), LoginName (101), Email (103), GroupList (104), FullName (8), DefNotify (108), LicType (109), FtLicType (110), CreatedBy (2), Created (3), ModifiedBy (5), Modified (6). If this parameter is set to `FALSE` no user data will be loaded. |
| UserForm | String | `User` | Name of the ARSystem user form. |
| UserQuery | String | `'1'!=$NULL$` | Query to restrict the number of users returned from the server. |
| LoadGroupList | Boolean | `TRUE` | Load group data. Requires the following fields in the form:  RequestId (1), GroupName (105), GroupId (106), GroupType (107), LongGroupName (8), CreatedBy (2), Created (3), ModifiedBy (5), Modified (6), Category (120), Computed Group Definition (121). If this parameter is set to `FALSE` no group data will be loaded. |
| GroupForm | String | `Group` | Name of the ARSystem group form. |
| GroupQuery | String | `'1'!=$NULL$` | Query to restrict the number of groups returned from the server. |
| LoadRoleList | Boolean | `TRUE` | Load role. Requires the following fields in the form:  RequestId (1), ApplicationName (1700), RoleName (1701), RoleID (1702), GroupName Test (2001), GroupName Production (2002), CreatedBy (2), Created (3), ModifiedBy (5), Modified (6). If this parameter is set to `FALSE` no role data will be loaded. |
| RoleForm | String | `Roles` | Name of the ARSystem role form. |
| RoleQuery | String | `'1'!=$NULL$` | Query to restrict the number of roles returned from the server. |
| MaxRetrieve | Integer | `0` | The maximum number of entries to retrieve. Use this parameter to limit the amount of data returned if the qualification does not sufficiently narrow the list. Specify `0` to assign no maximum. |

#### Layout

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| CompanyName | String | `yourcompanyname` | Your company name displayed in the documentation. |
| CompanyUrl | String | `http://example.com` | Html link to the specified company (CompanyName) |
| RunNotes | String | <EMPTY> | Additional notes that will display on the main page. |

### Recommended Configuration

1.  Target Folder

    The output folder should be changed to a more appropriate name and location. For example:

    ```
    TargetFolder = D:\arinside\_doc\<servername>
    ```

2.  User List

    If you have a lot of users it could increase the duration of a run significantly. At the same time you don't get much functionality, just some details like license type and such, and a direct link between an AR-system object and the user. For most customers this isn't important at all. In this case, you can limit it to only those users with write licenses:

    ```
    # Data Retrieval
    LoadUserList = TRUE
    UserQuery    = 'License Type'="Fixed" OR 'License Type'="Floating"
    ```
    
    Or disable loading of users altogether:
    
    ```
    # Data Retrieval
    LoadUserList = FALSE
    ```

## Security

ARInside uses the following ARSystem API calls to load objects from server / file.

Online Mode

- ARInitialzation
- ARTermination
- ARGetList(...)
- ARGet(...)
- FreeAR

File Mode

- ARInitialzation
- ARGet(...)FromXML
- FreeAR

Security Comments

- ARInside doesn't use any of the ARSet(...) or ARExecuteProcess API calls.

## Known Errors

Here are some known problems and possible workarounds listed.

### Loading of encryption library failed

In some cases the program prints out the following text right after the start:

```
Connecting to server sample.server.name...
Initilization of ARAPI returned: 2 (Error)
[ARERR 9011] Loading of encryption library failed
```

After the error message, the program crashes. From what is known this is an issue of ARAPI 7.5, if it finds another api file within the path. The workaround is to clear the PATH variable before you run ARInside.

```
set PATH=
```

### Page not rendered by Internet Explorer

It looks like "Internet Explorer" has some trouble rendering bigger html files. A user has had some trouble with a 60 MB html file. In such a case we can only recommend using another browser. Firefox and Chrome will work very well in such a case.

### Unicode Support

While there is an option named "UTF-8" within the `settings.ini` file, the functionality isn't finished yet. Currently, the setting doesn't have any impact. Unicode support will be added in the future.

### Communication with older server versions

The current release of ARInside uses a rather ARAPI 8.1.2. If you connect to a server which has an older version, usually the API handles the backward compatibility. But we have observed some cases where the newer api-version couldn't handle the data transfer correctly. That's mostly because ARInside uses some of the newer ARGetMultiple(...) api-calls which aren't supported on AR Servers below version 6.3. Starting with ARInside 3.1.1 the slower object loading is automatically activated if you connect to a server below version 6.3. If ARInside causes crashes on newer server versions (6.3 and above) and prints some ARERR90 and ARERR91 during loading of objects like activelinks, filters, escalations, menus and so on, just use the "--slow" command line option. If this setting is specified, ARInside will load objects via calls like ARGetActiveLink (instead of ARGetMultipleActiveLinks) which provides a better backwards compatibility but is much slower.

## Troubleshooting

In case you observe some error during execution of ARInside (e.g. a crash) you should activate the detailed logging and redirect the output to a log file like this:

```
arinside.exe [...] –v >arinside.log 2>&1
```

The `[...]` is just a placeholder for other options (like `–i`) you want to specify on the command line. In this example the output is redirected to the file `arinside.log`.
