function FilterableTable(objTableId, objFilterId, objResultCountId) {
	this.tableId = objTableId;
	this.filterId = objFilterId;
	this.resultCountId = objResultCountId;
	this.maxMatches = 100;
	this.lastMatches = 0;
	this.lastIndex = 0;
	this.nameIndex = 0;
    this.table = $('#' + objTableId);
}

FilterableTable.prototype.hasTypeFilter = function() { return false; }
FilterableTable.prototype.checkTypeFilterForRow = function(row) { return false; }
FilterableTable.prototype.createHtmlRow = function(row) { return ""; }

FilterableTable.prototype.onHasTypeFilter = function(cb) { this.hasTypeFilter = cb; return this; }
FilterableTable.prototype.onCheckTypeFilterForRow = function(cb) { this.checkTypeFilterForRow = cb; return this; }
FilterableTable.prototype.onCreateHtmlRow = function(cb) { this.createHtmlRow = cb; return this; }

FilterableTable.prototype.setNameIndex = function(idx) { this.nameIndex = idx; return this; }

FilterableTable.prototype.createMoreResultsRow = function() {
	var ft = this;
    return $("<tfoot>").append($("<tr>")
    .append($("<td class='warn' colspan=99>").text("Result limit reached! ")
	    .append($("<a id=showNext href='javascript:void(0)'>Show Next " + ft.maxMatches + "</a>").click(function() {
	        $(this).parents('tfoot:first').remove();
	        ft.filterTable('next');
	    }))
	    .append(" &nbsp; ")
	    .append($("<a id=showAll href='javascript:void(0)'>Show All</a>").click(function() {
	        $(this).parents('tfoot:first').remove();
	        ft.filterTable('all');
	    }))
	));
}

FilterableTable.prototype.filterTable = function(appendNextChunk) {
    var table = this.table; //$('#' + tableId);
	var list = window[this.tableId];
    var search = $('#' + this.filterId).val().replace(/ +/g, " ").replace(/ /g, ".*");
    var numSearch = search.search("^-?\\d+$");
    var maxMatch = this.maxMatches;
    var lastMatches = 0;
    var matches = 0;
    var hasTypeFilter = this.hasTypeFilter();
    var hasFilter = (search != null && search.length > 0) || hasTypeFilter;
    var start = 0;
    var end = list.length;
    var showAllMatches = appendNextChunk == 'all';

    if (appendNextChunk) {
        start = this.lastIndex;
        lastMatches += this.lastMatches;
    }
    else {
        if (end > 0) table.find("tbody,tfoot").remove();
    }

        for (var i = start; i < end; i++) {
            var r = new RegExp(search, "i");
			var row = list[i];
            if ((!hasTypeFilter || hasTypeFilter && this.checkTypeFilterForRow(row)) && (row[this.nameIndex].match(r) || (numSearch == 0 && ("" + row[0]) == search))) {
                matches++;
                table.append(this.createHtmlRow(row));
            }
            if (!showAllMatches && matches >= maxMatch) {
                table.append(this.createMoreResultsRow());
                this.lastIndex = i + 1;
                this.lastMatches = lastMatches + matches;
                break;
            }
        };

    $('#' + this.resultCountId).text((hasFilter ? "showing " + (lastMatches + matches) + " out of " : ""));
}
