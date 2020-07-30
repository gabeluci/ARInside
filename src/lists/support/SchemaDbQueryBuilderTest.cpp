#include "ARInsideTest.h"
#include "SchemaDbQueryBuilder.h"

using namespace testing;

const int NO_MAX_RESULT_LIMIT = 0;

#define BASE_STATEMENT "select schemaId, name, viewName, shViewName from arschema"
#define BASE_QUERY(N) " where schemaId > " #N
#define BASE_ORDER " order by schemaId asc"

#define DEFAULT_SQL_STATEMENT_WITHOUT_QUERY      (BASE_STATEMENT BASE_ORDER)
#define DEFAULT_SQL_STATEMENT_WITH_QUERY         (BASE_STATEMENT BASE_QUERY(0) BASE_ORDER)

TEST(SchemaDbQueryBuilder, DefaultQueryIfNoMaxRetrieve)
{
	SchemaDbQueryBuilder queryBuilder;

	const char* sql = queryBuilder.GetNextQuery();

	ASSERT_STREQ(DEFAULT_SQL_STATEMENT_WITHOUT_QUERY, sql);
}

#define SECOND1000_SQL_STATEMENT_WITH_QUERY (BASE_STATEMENT BASE_QUERY(1122) BASE_ORDER)
TEST(SchemaDbQueryBuilder, QueryAfterSetMaxRetrieve)
{
	SchemaDbQueryBuilder queryBuilder;
	queryBuilder.GetNextQuery();
	// .. execute query and work on results, then start next chunk iteration
	queryBuilder.SetMaxRetrieve(1000);           // take the size of the first result (for the test we assume 1000 entries)
	queryBuilder.SetLastReceivedSchemaId(1122);

	const char* sql = queryBuilder.GetNextQuery();

	ASSERT_STREQ(SECOND1000_SQL_STATEMENT_WITH_QUERY, sql);
}

TEST(SchemaDbQueryBuilder, ValidateQueryColumCount)
{
	ASSERT_EQ(4, SchemaDbQueryBuilder::ExpectedColumnCount());
}

class SchemaDbQueryWithMax100Results : public Test
{
public:
	SchemaDbQueryBuilder *queryBuilder;

	const static unsigned int MAX_RESULT = 100;

	void SetUp() {
		queryBuilder = new SchemaDbQueryBuilder();
		queryBuilder->SetMaxRetrieve(MAX_RESULT);
	}
	void TearDown() {
		delete queryBuilder;
	}
};

TEST_F(SchemaDbQueryWithMax100Results, FirstQueryShouldStartAtZero)
{
	const char* sql = queryBuilder->GetNextQuery();
	ASSERT_STREQ(DEFAULT_SQL_STATEMENT_WITH_QUERY, sql);
}

#define SECOND100_SQL_STATEMENT_WITH_QUERY (BASE_STATEMENT BASE_QUERY(112) BASE_ORDER)
TEST_F(SchemaDbQueryWithMax100Results, SecondQueryShouldStartAtLastSchemaId)
{
	const char* sql;
	sql = queryBuilder->GetNextQuery(); // generate first query
	queryBuilder->SetLastReceivedSchemaId(112); // this is the last row (schemaId) we did get from previous query result
	
	sql = queryBuilder->GetNextQuery(); // generate second query
	ASSERT_STREQ(SECOND100_SQL_STATEMENT_WITH_QUERY, sql);
}

class SchemaDbQueryResultValidator : public Test
{
#define STRUCT_ITEM_COUNT 4
#define ROW_VALUE_SCHEMAID 123
#define ROW_VALUE_SCHEMANAME "TestSchema"
#define ROW_VALUE_SCHEMAVIEW ROW_VALUE_SCHEMANAME
#define ROW_VALUE_SCHEMASHVIEW ("SH_" ROW_VALUE_SCHEMANAME)
public:
	SchemaDbQueryBuilder *queryBuilder;

	ARValueList validRow;
	ARValueStruct values[STRUCT_ITEM_COUNT];

	void SetUp() {
		queryBuilder = new SchemaDbQueryBuilder();

		values[0].dataType = AR_DATA_TYPE_INTEGER;
		values[0].u.intVal = ROW_VALUE_SCHEMAID;

		values[1].dataType = AR_DATA_TYPE_CHAR;
		values[1].u.charVal = ROW_VALUE_SCHEMANAME;

		values[2].dataType = AR_DATA_TYPE_CHAR;
		values[2].u.charVal = ROW_VALUE_SCHEMAVIEW;

		values[3].dataType = AR_DATA_TYPE_CHAR;
		values[3].u.charVal = ROW_VALUE_SCHEMASHVIEW;

		validRow.numItems = STRUCT_ITEM_COUNT;
		validRow.valueList = values;
	}
};

TEST_F(SchemaDbQueryResultValidator, TryReadingAValidSchemaId)
{
	unsigned int schemaId = 0;  // just init it to a value, different to the expected result
	
	bool isValidRead = queryBuilder->TryReadSchemaId(validRow, schemaId);
	
	ASSERT_EQ(ROW_VALUE_SCHEMAID, schemaId);
	ASSERT_TRUE(isValidRead);
}

TEST_F(SchemaDbQueryResultValidator, TryReadingAValidSchemaView)
{
	ARNameType schemaView;
	bool isValidRead = queryBuilder->TryReadSchemaView(validRow, schemaView);

	ASSERT_STREQ(ROW_VALUE_SCHEMAVIEW, schemaView);
	ASSERT_TRUE(isValidRead);
}

TEST_F(SchemaDbQueryResultValidator, TryReadingAValidSchemaShView)
{
	ARNameType shViewName;
	bool isValidRead = queryBuilder->TryReadSchemaShView(validRow, shViewName);
	
	ASSERT_STREQ(ROW_VALUE_SCHEMASHVIEW, shViewName);
	ASSERT_TRUE(isValidRead);
}
