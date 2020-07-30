function ARFieldDataTypeToString(dataType) {
    switch (dataType) {
        case 0: return "Null";
        case 1: return "Keyword";
        case 2: return "Integer";
        case 3: return "Real";
        case 4: return "Character";
        case 5: return "Diary";
        case 6: return "Selection";
        case 7: return "Date/Time";
        case 8: return "Bitmask";
        case 9: return "Bytes";
        case 10: return "Decimal";
        case 11: return "Attach";
        case 12: return "Currency";
        case 13: return "Date";
        case 14: return "Time of Day";
        case 30: return "Join";
        case 31: return "Trim";
        case 32: return "Control";
        case 33: return "Table";
        case 34: return "Column";
        case 35: return "Page";
        case 36: return "Page Holder";
        case 37: return "Attach Pool";
        case 40: return "Long";
        case 41: return "Coords";
        case 42: return "View";
        case 43: return "Display";
        default: return "unknwon";
    };
};

function AREnabled(val) {
    if (val) return "Enabled";
    return "Disabled";
}

function ARObjectType(objType) {
    switch (objType) {
        case 5: return "Filter";
        case 6: return "Active Link";
        case 9: return "Escalation";
    }
}

function ARContainerType(cntType) {
    switch (cntType) {
        case 1: return "Active Link Guide";
        case 2: return "Application";
        case 3: return "Packing List";
        case 4: return "Filter Guide";
        case 5: return "Webservice";
    }
}

function StrAppend(str, val) {
    if (str.length > 0)
        return str + ", " + val;
    return val;
}

function RootPath(rootLevel) {
	var path = '';
    for (i = 0; i < rootLevel; i++) { path += "../"; }
	return path;
}

function ARActLinkExecuteOn(val) {
    var result = "";
    if (val & 1) { result = StrAppend(result, "Button/MenuField") }
    if (val & 2) { result = StrAppend(result, "Return"); }
    if (val & 4) { result = StrAppend(result, "Submit"); }
    if (val & 8) { result = StrAppend(result, "Modify"); }
    if (val & 16) { result = StrAppend(result, "Display"); }
    if (val & 128) { result = StrAppend(result, "Menu Choise"); }
    if (val & 256) { result = StrAppend(result, "Loose Focus"); }
    if (val & 512) { result = StrAppend(result, "Set Default"); }
    if (val & 1024) { result = StrAppend(result, "Search"); }
    if (val & 2048) { result = StrAppend(result, "After Modify"); }
    if (val & 4096) { result = StrAppend(result, "After Submit"); }
    if (val & 8192) { result = StrAppend(result, "Gain Focus"); }
    if (val & 16384) { result = StrAppend(result, "Window Open"); }
    if (val & 32768) { result = StrAppend(result, "Window Close"); }
    if (val & 65536) { result = StrAppend(result, "Un-Display"); }
    if (val & 131072) { result = StrAppend(result, "Copy To New"); }
    if (val & 262144) { result = StrAppend(result, "Window Loaded"); }
    if (result.length == 0) return "None";
    return result;
}

function ARFilterOperation(val) {
    var result = "";
    if (val & 1) { result = StrAppend(result, "Get"); }
    if (val & 2) { result = StrAppend(result, "Modify"); }
    if (val & 4) { result = StrAppend(result, "Submit"); }
    if (val & 8) { result = StrAppend(result, "Delete"); }
    if (val & 16) { result = StrAppend(result, "Merge"); }
    if (val & 64) { result = StrAppend(result, "Service"); }
    if (result.length == 0) return "None";
    return result;
}

function AREscalationTMType(val) {
    if (val == 1) { return "Interval"; }
    return "Time";
}

function ARSchemaType(schemaType) {
    switch (schemaType) {
        case 1: return "Regular";
        case 2: return "Join";
        case 3: return "View";
        case 4: return "Dialog";
        case 5: return "Vendor";
        case 100: return "Audit";
        case 101: return "Archive";
        default: return "unknown";
    }
}

function getIcon(rootLevel, type, subtype, overlay) {
    var alt = ""; var width=16; var height=16;
    switch (type) {
        case 1: switch (subtype) {
				case 2: alt="schema_join.gif"; break;
				case 3: alt="schema_view.gif"; break;
				case 4: alt="schema_display.gif"; break;
				case 5: alt="schema_vendor.gif"; break;
				default: alt = "schema.gif"; break;
			}; break;
        case 5: alt = "filter.gif"; break;
        case 6: alt = "active_link.gif"; break;
        case 8: alt = "menu.gif"; break;
        case 9: alt = "escalation.gif"; break;
        case 12: switch (subtype) {
                case 1: alt = "al_guide.gif"; break;
                case 2: alt = "application.gif"; break;
                case 3: alt = "packing_list.gif"; break;
                case 4: alt = "filter_guide.gif"; break;
                case 5: alt = "webservice.gif"; break;
            }; break;
        case 17: alt = "image.gif"; break;
		case 500: alt = "user.gif"; break;
		case 501: alt = "group.gif"; break;
		case 502: alt = "role.gif"; break;
        default: return "";
    };
    var src = "";
    src += RootPath(rootLevel) + "img/" + alt;

	var ovlIcon = '';
	var style;
	switch (overlay)
	{
		case 2: ovlIcon = 'overlay.gif'; break;
		case 4: ovlIcon = 'custom.gif'; break;
	}
	if (ovlIcon) {
		style = 'background:url('+src+')';
		src = RootPath(rootLevel) + "img/" + ovlIcon;
	}
	
	var image = $("<img>").attr("width", width).attr("height", height)/*.attr("alt", alt)*/.attr("src", src);
	if (style)
		image.attr('style',style);
    return image;
}

function ARPool(poolNum) {
	var n = Number(poolNum);	
	if (n !== "NaN" && poolNum > 0) { return n; }	
}

function ARMenuType(type) {
	switch (type) {
		case 1: return "Character";
		case 2: return "Search";
		case 3: return "File";
		case 4: return "SQL";
		case 6: return "Data Dictionary";
		default: return "";
	}
}

function ARMenuConnect(type) {
	switch (type) {
		case 1: return "On Connect";
		case 2: return "On Open";
		case 3: return "On 15-minute Interval";
		default: return "";
	}
}

function ARGroupType(type) {
	switch(type) {
		case 1: return "View";
		case 2: return "Change";
		default: return "None";
	}
}

function ARGroupCategory(cat) {
	switch(cat) {
		case 0: return "Regular";
		case 1: return "Dynamic";
		case 2: return "Computed";
		default: return "None";
	}
}
