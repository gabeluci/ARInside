function initFilterTable() {
    if (groupList != null) { 
		var inputControl = 'groupFilter';
		grpListObj = new FilterableTable('groupList', inputControl, 'groupListFilterResultCount'); 
		grpListObj.onCreateHtmlRow(createGroupRowHtml);
		
		var checkboxes = $('#multiFilter input[type="checkbox"]');
		grpListObj.typeFilter = new Array();
		grpListObj.onHasTypeFilter(function() {
			var allTypeOn = true;
			var allTypeOff = true;
			for (i = 0; i < checkboxes.length; i++) {
				this.typeFilter[i] = checkboxes[i].checked;
				if (this.typeFilter[i]) { allTypeOff = false; }
				if (!this.typeFilter[i]) { allTypeOn = false; }
			}
			return !(allTypeOff || allTypeOn)			
		})
		.onCheckTypeFilterForRow(function(row) {
			for (i = 0; i < checkboxes.length; i++) { if (grpListObj.typeFilter[i] && row[3] == i) return true; }
			return false;
		})
		.setNameIndex(1);
		checkboxes.change(updateFilterTable);
		$("#typeFilterNone").click(function() {
			checkboxes.each(function() {
				this.checked = false;
			});
			updateFilterTable();
		});
		$('#'+inputControl).focus();
	}
}

function updateFilterTable() {
    if (grpListObj != null) { grpListObj.filterTable(); }
}

function createGroupRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 501))
            .append($("<a>").attr("href", data[6]).text(data[1]))
        )
		.append($("<td>").text(data[0]))
        .append($("<td>").text(ARGroupType(data[2])))
        .append($("<td>").text(ARGroupCategory(data[3])))
		.append($("<td>").text(data[4]))
		.append($("<td>").text(data[5]))
    );
}

$('document').ready(function() {
    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateFilterTable);
    });

    initFilterTable();
	updateFilterTable();

    $("#formLetterFilter a").click(function() {
        $("#groupFilter").val("^" + $(this).text());
        updateFilterTable();
        return false;
    });
});
