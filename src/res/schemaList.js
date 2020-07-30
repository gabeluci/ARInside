function initSchemaTable() {
	if (schemaList != null) {
		var inputControl = 'formFilter';
		schemaListObj = new FilterableTable('schemaList', inputControl, 'schemaListFilterResultCount');
		schemaListObj.typeFilter = new Array();
		schemaListObj.onHasTypeFilter(function() {
			var allTypeOn = true;
			var allTypeOff = true;
			for (l = 1; l < 8; l++) {
				if (l == 6) { i = 100; /* for special audit type support*/ }
				else if (l == 7) { i = 101; /* for special archive type support*/ }
				else { i = l; }
				this.typeFilter[i] = $('#listMultiFilter input[value="' + i + '"]').attr('checked');
				if (this.typeFilter[i]) { allTypeOff = false; }
				if (!this.typeFilter[i]) { allTypeOn = false; }
			}
			return !(allTypeOff || allTypeOn)
		})
		.onCheckTypeFilterForRow(function(row) {
			return schemaListObj.typeFilter[row[5]];
		})
		.setNameIndex(1)
		.onCreateHtmlRow(createSchemaRowHtml);
		$('#'+inputControl).focus();
	}
}

function updateSchemaTable() {
    if (schemaListObj != null) { schemaListObj.filterTable(); }
}

function createSchemaRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 1, data[5], data[9]))
            .append($("<a>").attr("href", data[8]).text(data[1]))
        )
        .append($("<td>").text(data[2]))
        .append($("<td>").text(data[3]))
		.append($("<td>").text(data[4]))
		.append($("<td>").text(ARSchemaType(data[5])))
		.append($("<td>").text(data[6]))
		.append($("<td>").text(data[7]))
    );
}

$('document').ready(function() {
    var checkBoxes = $('#listMultiFilter input[type="checkbox"]');

    $.address.change(function(event) {
		var hash = window.location.hash;
		var value = 0;
		if (hash === "#regular") { value = 1; }
		if (hash === "#join") { value = 2; }
		if (hash === "#view") { value = 3; }
		if (hash === "#dialog") { value = 4; }
		if (hash === "#vendor") { value = 5; }
		if (hash === "#audit") { value = 100; }
		if (hash === "#archive") { value = 101; }
		if (value>0) {
			checkBoxes.filter('[value="'+value+'"]').attr("checked","checked");
			updateSchemaTable();
		}
    });
    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateSchemaTable);
    });
    $("#typeFilterNone").click(function() {
        checkBoxes.each(function() {
            this.checked = false;
        });
		window.location.hash="";
        updateSchemaTable();
    });
    checkBoxes.change(function() {
		if (this.checked) {	window.location.hash="#" + ARSchemaType(Number(this.value)).toLowerCase(); }
		updateSchemaTable();
	});

    initSchemaTable();
	updateSchemaTable();

    $("#formLetterFilter a").click(function() {
        $("#formFilter").val("^" + $(this).text());
        updateSchemaTable();
        return false;
    });
});
