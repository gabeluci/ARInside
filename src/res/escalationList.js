function initEscalationTable() {
    if (escalationList != null) { 
		var inputControl = 'escalationFilter';
		escalListObj = new FilterableTable('escalationList', inputControl, 'escalationListFilterResultCount'); 
		escalListObj.onCreateHtmlRow(createEscalationRowHtml);
		escalListObj.hasPoolColumn = (escalListObj.table[0].rows[0].cells[2].textContent == "Pool");
		$('#'+inputControl).focus();
	}
}

function updateEscalationTable() {
    if (escalListObj != null) { escalListObj.filterTable(); }
}

function createEscalationRowHtml(data) {	
    var result = $("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 9, 0, data[9]))
            .append($("<a>").attr("href", data[7]).text(data[0]))
        )
        .append($("<td>").text(AREnabled(data[1])));
	if (this.hasPoolColumn) {
		result.append($("<td>").text(ARPool(data[8])));
	}
	result.append($("<td>").text(data[2]))		
		.append($("<td>").text(data[3]))
		.append($("<td>").text(data[4]))
		.append($("<td>").text(data[5]))
		.append($("<td>").text(data[6]));
    return result;
}

$('document').ready(function() {
    //var checkBoxes = $('#multiFilter input[type="checkbox"]');

    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateEscalationTable);
    });
    $("#execescalationFilter").click(updateEscalationTable);
	/*
    $("#typeFilterAll").click(function() {
        $('#multiFilter input[type="checkbox"]').each(function() {
            this.checked = true;
        });
        $("#execFormFilter").click();
    });
    $("#typeFilterNone").click(function() {
        checkBoxes.each(function() {
            this.checked = false;
        });
        $("#execFormFilter").click();
    });
    $("#typeFilterInvert").click(function() {
        checkBoxes.each(function() {
            this.checked = !this.checked;
        });
        $("#execFormFilter").click();
    });
    checkBoxes.change(function() {
        $("#execFormFilter").click();
    });
	*/

    initEscalationTable();
	updateEscalationTable();

    $("#formLetterFilter a").click(function() {
        $("#escalationFilter").val("^" + this.text);
        updateEscalationTable();
        return false;
    });
});
