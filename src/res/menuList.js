function initMenuTable() {
    if (menuList != null) { 
		var inputControl = 'menuFilter';
		menuListObj = new FilterableTable('menuList', inputControl, 'menuListFilterResultCount'); 
		menuListObj.onCreateHtmlRow(createMenuRowHtml);
		
		var checkboxes = $('#multiFilter input[type="checkbox"]');
		menuListObj.typeFilter = new Array();
		menuListObj.onHasTypeFilter(function() {
			var allTypeOn = true;
			var allTypeOff = true;
			for (i = 1; i < 7; i++) {
				this.typeFilter[i] = checkboxes.filter("[value="+i+"]").attr('checked');
				if (this.typeFilter[i]) { allTypeOff = false; }
				if (!this.typeFilter[i]) { allTypeOn = false; }
			}
			return !(allTypeOff || allTypeOn)			
		})
		.onCheckTypeFilterForRow(function(row) {
			return menuListObj.typeFilter[row[1]];
		});
		checkboxes.change(updateMenuTable);
		$("#typeFilterNone").click(function() {
			checkboxes.each(function() {
				this.checked = false;
			});
			updateMenuTable();
		});
		$('#'+inputControl).focus();
	}
}

function updateMenuTable() {
    if (menuListObj != null) { menuListObj.filterTable(); }
}

function createMenuRowHtml(data) {
    return ($("<tr>")
        .append($("<td>")
            .append(getIcon(rootLevel, 8, 0, data[6]))
            .append($("<a>").attr("href", data[5]).text(data[0]))
			.append((data[7]==0?" (<b>!</b>)":""))
        )
        .append($("<td>").text(ARMenuType(data[1])))
        .append($("<td>").text(ARMenuConnect(data[2])))
		.append($("<td>").text(data[3]))
		.append($("<td>").text(data[4]))
    );
}

$('document').ready(function() {
    $(".clearable").on('propertychange keyup input paste', 'input.data_field', function(e) {
        if (e.keyCode == 27 /*Escape-Key*/) { $(this).val(''); }
        $(this).stopTime().oneTime(300, updateMenuTable);
    });

    initMenuTable();
	updateMenuTable();

    $("#formLetterFilter a").click(function() {
        $("#menuFilter").val("^" + $(this).text());
        updateMenuTable();
        return false;
    });
});
