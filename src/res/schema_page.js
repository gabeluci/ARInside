$(function() {
    $("#MainObjectTabCtrl").tabs();
    $('#MainObjectTabCtrl div[id^="tab"]').addClass("inner-tab");
});

$.fn.appendText = function(text) {
    this.each(function() {
        var textNode = document.createTextNode(text);
        $(this).append(textNode);
    });
};

var schemaFieldManager = {
    view_vendor_RFR: function(row) {
        return (schemaFieldList[row].length > 7 ? schemaFieldList[row][7] : "");
    },
    join_left: null,
    join_right: null,
    join_RFR: function(row) {
        var pos = 7;
        var div = $("<div>");
        var first = 0;
        for (pos; pos + 2 <= schemaFieldList[row].length; pos += 2) {
            if (first > 0) { div.append($("<br/>")); }

            if (schemaFieldList[row][pos+1]==="")
              div.append($("<span>").addClass('fieldNotFound').text(schemaFieldList[row][pos]));
            else
              div.append($("<a>").attr("href", schemaFieldList[row][pos + 1]).text(schemaFieldList[row][pos]));
            div.appendText("\u00a0 -> \u00a0");

						var joinSchema = schemaFieldList[row][9];
						if (schemaFieldList[row].length == 10 && (joinSchema == '0' || joinSchema == '1')) {
							var joinLink = (joinSchema == '0' ? this.join_left : this.join_right);
							div.append($("<span>").append(joinLink.clone()));
							pos++;
						}
						else if (schemaFieldList[row].length == 11) {
							var joinLink = (first?this.join_right:this.join_left);
							div.append($("<span>").append(joinLink.clone()));
						}

            first++;
        }
        if (first > 0) return div;
        return (schemaFieldList[row].length > 7 ? schemaFieldList[row][7] : "");
    },
    renderRealField: function(row) {
        if (this.realFieldRenderer == null) { return ""; }
        return this.realFieldRenderer(row);
    },
    realFieldRenderer: null,
    setRenderer: function(type) {
        if (type === "view" || type === "vendor")
            this.realFieldRenderer = this.view_vendor_RFR;
        if (type === "join") {
            this.join_left = $('#join-left');
            this.join_right = $('#join-right');
            this.realFieldRenderer = this.join_RFR;
        }
    }
};

function getEnabled(row) {
    if (row[0] == 12) return "";
    return AREnabled(row[2]);
}

function getObjType(row) {
    if (row[0] == 12) return ARContainerType(row[2]);
    return ARObjectType(row[0]);
}

function createReferenceRow(row) {
//	var table_name = 'referenceList';
//	var table = $("#" + table_name);
//	if (schemaWorkflowList.length > 0) { $("#" + table_name + " tbody").remove(); }
//	$.each(schemaWorkflowList, function(i) {
	var executeOn = function() { return ""; }
	var objType = row[0];
	if (objType == 6)      { executeOn = function(val) { return ARActLinkExecuteOn(val);};}
	else if (objType == 5) { executeOn = function(val) { return ARFilterOperation(val);};}
	else if (objType == 9) { executeOn = function(val) { return AREscalationTMType(val);};}

	return ($("<tr>")
		.append($("<td>")
			.append(getIcon(rootLevel, row[0], row[2]))
			.append($("<a>").attr("href", row[9]).text(row[1]))
		)
		.append($("<td>").text(getEnabled(row)))
		.append($("<td>").text(row[3]))
		.append($("<td>").text(executeOn(row[4])))
		.append($("<td>").text(row[5]))
		.append($("<td>").text(row[6]))
		.append($("<td>").text(row[7]))
		.append($("<td>").text(row[8]))
	);
}

function initWorkflowList() {
	$('#workflowReferenceCount').text(referenceList.length);
	referenceListObj = new FilterableTable('referenceList', 'workflowFilter', 'workflowFilterResult');
	referenceListObj.typeFilterMapping = {6:1,5:2,9:3};
	referenceListObj.typeFilterContainer = { 1:4, 4:5, 2:6, 3:7, 5:8 };
	referenceListObj.typeFilter = new Array();
	referenceListObj
		.onHasTypeFilter(function() { 
			var allTypeOn = true;
			var allTypeOff = true;
			for (i = 1; i < 9; i++) {
				this.typeFilter[i] = $('#referenceMultiFilter input[value="' + i + '"]').attr('checked');
				if (this.typeFilter[i]) { allTypeOff = false; }
				if (!this.typeFilter[i]) { allTypeOn = false; }
			}
			return !(allTypeOff || allTypeOn)
		})
		.onCheckTypeFilterForRow(function(row) {
			var type;
			if (row[0]==12) {
				type = referenceListObj.typeFilterContainer[row[2]];
			}
			else {
				type = referenceListObj.typeFilterMapping[row[0]];
			}
			return referenceListObj.typeFilter[type];
		})
		.setNameIndex(1)
		.onCreateHtmlRow(createReferenceRow);
	referenceListObj.filterTable();
	schemaWFLInit = true;
	return;
}

function updateReferenceTable() {
    if (referenceListObj != null) { referenceListObj.filterTable(); }
}

$('document').ready(function() {
	$.address.change(function(event) {
		var hash = window.location.hash;
		$("#MainObjectTabCtrl").tabs("select", hash);
		if (hash === '#tab-2') { $("#fieldNameFilter").focus(); }
		if (hash === '#tab-4' && !schemaWFLInit) { initWorkflowList(); }
	});
	$("#MainObjectTabCtrl").bind("tabsselect", function(event, ui) {
		window.location.hash = ui.tab.hash;
		if (ui.tab.hash === '#tab-4' && !schemaWFLInit) { initWorkflowList(); }
	});
	$("#tab-2 .clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
		if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
		$(this).stopTime().oneTime(300, function() {
				$("#execFieldFilter").click();
		});
	});
	$("#schemaProperties").accordion({ heightStyle: "content", collapsible: true, active: false, animate: false });
	$("#schemaPermissions").accordion({ heightStyle: "content", collapsible: true, active: false, animate: false });

	$("#execFieldFilter").click(function() {
		if (schemaFieldList != null) {
			var table_name = 'fieldListAll';
			var table = $('#' + table_name);
			var search = $("#fieldNameFilter").val().replace(" +", " ").replace(" ", ".*");
			var numSearch = search.search("^\\d+$");
			var matches = 0;
			var hasRealFieldColumn = ($('#' + table_name + ' thead tr:eq(0) th:eq(3)').text().lastIndexOf("Real Field", 0) === 0);

			$('#' + table_name + ' tbody').remove();

			$.each(schemaFieldList, function(i) {
				var r = new RegExp(search, "i");
				if (schemaFieldList[i][1].match(r) || (numSearch == 0 && ("" + schemaFieldList[i][0]).match(search))) {
					matches++;
					var row = ($("<tr>")
						.append($("<td>")
							.append($("<a>").attr("href", schemaFieldList[i][6]).text(schemaFieldList[i][1]))
						)
						.append($("<td>").text(schemaFieldList[i][0]))
						.append($("<td>").text(ARFieldDataTypeToString(schemaFieldList[i][2])))
					);
					if (hasRealFieldColumn)
						row.append($("<td>").append(schemaFieldManager.renderRealField(i)));

					row.append($("<td>").text(schemaFieldList[i][3]))
						.append($("<td>").text(schemaFieldList[i][4]))
						.append($("<td>").text(schemaFieldList[i][5]));

					table.append(row);
				}
			});
			$('#fieldListFilterResultCount').text((search != null && search.length > 0 ? "showing " + matches + " out of " : ""));
		}
	});
	if ($("#fieldNameFilter").val() != "") {
		$("#execFieldFilter").click();
	}
  $("#tab-4 .clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
		if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
		$(this).stopTime().oneTime(300, updateReferenceTable);
	})

	var checkBoxes = $('#referenceMultiFilter input[type="checkbox"]');
	checkBoxes.change(function() {
		if (this.checked) {	/*window.location.hash="#" + ARSchemaType(Number(this.value)).toLowerCase(); */ }
		updateReferenceTable();
	});
	$("#typeFilterNone").click(function() {
		checkBoxes.each(function() {
			this.checked = false;
		});
		window.location.hash="";
		updateReferenceTable();
	});
});
