function initFilterTable() {
    if (filterList != null) { 
		var inputControl = 'filterFilter';
		fltListObj = new FilterableTable('filterList', inputControl, 'filterListFilterResultCount'); 
		fltListObj.onCreateHtmlRow(createFilterRowHtml);
		
		var checkboxes = $('#multiFilter input[type="checkbox"]');
		fltListObj.typeFilter = new Array();
		fltListObj.onHasTypeFilter(function() {
			var allTypeOn = true;
			var allTypeOff = true;
			for (i = 0; i < checkboxes.length; i++) {
				this.typeFilter[i] = (checkboxes[i].checked ? (checkboxes[i].value == "N" ? "N" : Number(checkboxes[i].value)) : 0);
				if (this.typeFilter[i]) { allTypeOff = false; }
				if (!this.typeFilter[i]) { allTypeOn = false; }
			}
			return !(allTypeOff || allTypeOn)			
		})
		.onCheckTypeFilterForRow(function(row) {
			for (i = 0; i < checkboxes.length; i++) { if (fltListObj.typeFilter[i] == "N" && 0 == row[9] || row[9] & fltListObj.typeFilter[i]) return true; }
			return false;
		});
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
    if (fltListObj != null) { fltListObj.filterTable(); }
}

function createFilterRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 5, 0, data[10]))
            .append($("<a>").attr("href", data[8]).text(data[0]))
        )
        .append($("<td>").text(AREnabled(data[1])))
        .append($("<td>").text(data[2]))
		.append($("<td>").text(data[3]))
		.append($("<td>").text(data[4]))
		.append($("<td>").text(data[5]))
		.append($("<td>").text(data[6]))
		.append($("<td>").text(data[7]))
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
        $("#filterFilter").val("^" + $(this).text());
        updateFilterTable();
        return false;
    });
});
