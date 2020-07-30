function initFilterTable() {
    if (containerList != null) { 
		var inputControl = 'containerFilter';
		cntListObj = new FilterableTable('containerList', inputControl, 'containerListResultCount'); 
		cntListObj.onCreateHtmlRow(createContainerRowHtml);		
		$('#'+inputControl).focus();
	}
}

function updateFilterTable() {
    if (cntListObj != null) { cntListObj.filterTable(); }
}

function createContainerRowHtml(data) {
    return ($("<tr>")
			.append($("<td>")
					.append(getIcon(rootLevel, 12, containerType, data[4]))
					.append($("<a>").attr("href", data[3]).text(data[0]))
					.append((data.length>5 && data[5]==0?" (<b>!</b>)":""))
			)
			.append($("<td>").text(data[1]))
			.append($("<td>").text(data[2]))
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
        $("#containerFilter").val("^" + $(this).text());
        updateFilterTable();
        return false;
    });
});
