function initFilterTable() {
    if (roleList != null) {
		var inputControl = 'roleFilter';
		roleListObj = new FilterableTable('roleList', inputControl, 'roleListFilterResultCount'); 
		roleListObj.onCreateHtmlRow(createRoleRowHtml);
		
		var checkboxes = $('#multiFilter input[type="checkbox"]');
		roleListObj.typeFilter = new Array();
		roleListObj.onHasTypeFilter(function() {
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
			for (i = 0; i < checkboxes.length; i++) { if (roleListObj.typeFilter[i] && row[3] == i) return true; }
			return false;
		})
		.setNameIndex(1);
		checkboxes.change(updateRoleTable);
		$("#typeFilterNone").click(function() {
			checkboxes.each(function() {
				this.checked = false;
			});
			updateRoleTable();
		});
		$('#'+inputControl).focus();
	}
}

function updateRoleTable() {
    if (roleListObj != null) { roleListObj.filterTable(); }
}

function createRoleRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 502))
            .append($("<a>").attr("href", data[5]).text(data[1]))
        )
		.append($("<td>").text(data[0]))
        .append($("<td>")
			.append(getIcon(rootLevel,12,2))
			.append((data[6] ? $("<a>").attr("href", data[6]).text(data[2]) : data[2] ))
		)
        .append($("<td>").text(data[3]))
		.append($("<td>").text(data[4]))
    );
}

$('document').ready(function() {
    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateRoleTable);
    });

    initFilterTable();
	updateRoleTable();

    $("#formLetterFilter a").click(function() {
        $("#roleFilter").val("^" + $(this).text());
        updateRoleTable();
        return false;
    });
});
