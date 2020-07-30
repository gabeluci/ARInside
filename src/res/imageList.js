function initImageTable() {
    if (imageList != null) { 
		var inputControl = 'imageFilter';
		imgListObj = new FilterableTable('imageList', inputControl, 'imageListFilterResultCount'); 
		imgListObj.onCreateHtmlRow(createImageRowHtml);
		$('#'+inputControl).focus();
	}
}

function updateImageTable() {
    if (imgListObj != null) { try { imgListObj.filterTable(); } catch (e) { document.write(e); } }
}

function createImageRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 17, 0, data[5]))
            .append($("<a>").attr("href", data[4]).text(data[0]))
        )
        .append($("<td>").text(data[1]))
        .append($("<td>").text(data[2]))
		.append($("<td>").text(data[3]))
    );
}

$('document').ready(function() {
    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateImageTable);
    });

    initImageTable();
	updateImageTable();

    $("#formLetterFilter a").click(function() {
        $("#imageFilter").val("^" + $(this).text());
        updateImageTable();
        return false;
    });
});
