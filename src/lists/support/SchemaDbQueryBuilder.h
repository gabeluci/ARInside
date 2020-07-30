//Copyright (C) 2014 John Luthgers | jls17
//
//This file is part of ARInside.
//
//    ARInside is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 2 of the License.
//
//    ARInside is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

class SchemaDbQueryBuilder
{
public:
	SchemaDbQueryBuilder();
	~SchemaDbQueryBuilder(void);

	static unsigned int ExpectedColumnCount();
	const char* GetNextQuery();
	void SetLastReceivedSchemaId(int schemaId);
	void SetMaxRetrieve(unsigned int maxRetrieve);

	static bool TryReadSchemaId(ARValueList &row, unsigned int &schemaId);
	static bool TryReadSchemaView(ARValueList &row, ARNameType &schemaView);
	static bool TryReadSchemaShView(ARValueList &row, ARNameType &shSchemaView);

private:
	void AppendStatement(std::ostream &strm);
	void AppendWhereCondition(std::ostream &strm);
	void AppendOrdering(std::ostream &strm);

	void BuildWhereCondition(std::ostream &strm);

private:
	unsigned int maxRetrieve;
	int lastReceivedSchemaId;
	std::string query;
};
