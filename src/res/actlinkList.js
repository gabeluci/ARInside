function initActlinkTable() {
    if (alList != null) { 
		var inputControl = 'actlinkFilter';
		alListObj = new FilterableTable('alList', inputControl, 'actlinkListFilterResultCount'); 
		alListObj.onCreateHtmlRow(createActlinkRowHtml);
		$('#'+inputControl).focus();
	}
}

function updateActlinkTable() {
    if (alListObj != null) { alListObj.filterTable(); }
}

function createActlinkRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 6, 0, data[10]))
            .append($("<a>").attr("href", data[9]).text(data[0]))
        )
        .append($("<td>").text(AREnabled(data[1])))
        .append($("<td>").text(data[2]))
		.append($("<td>").text(data[3]))
		.append($("<td>").text(data[4]))
		.append($("<td>").text(data[5]))
		.append($("<td>").text(data[6]))
		.append($("<td>").text(data[7]))
		.append($("<td>").text(data[8]))
    );
}

$('document').ready(function() {
    //var checkBoxes = $('#multiFilter input[type="checkbox"]');

    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateActlinkTable);
    });
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

    initActlinkTable();
	updateActlinkTable();

    $("#formLetterFilter a").click(function() {
        $("#actlinkFilter").val("^" + $(this).text());
        updateActlinkTable();
        return false;
    });
});
