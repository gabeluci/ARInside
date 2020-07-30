#include "ARInsideTest.h"
#include "ARParseField.h"

bool isField(const ARParseField& field, int fieldId)
{
	return (field.tag == AR_FIELD && field.u.fieldId == fieldId);
}

bool isStatusHistory(const ARParseField& field, unsigned int usrOrTime, ARULong32 enumValue)
{
	return (field.tag == AR_STAT_HISTORY &&
		field.u.statHistory.userOrTime == usrOrTime &&
		field.u.statHistory.enumVal == enumValue);
}

bool isCurrencyField(const ARParseField& field, int fieldId, int currencyPartType, const char* partCode)
{
	return (field.tag == AR_CURRENCY_FLD &&
		field.u.currencyField->fieldId == fieldId &&
		field.u.currencyField->partTag == currencyPartType &&
		strcmp(field.u.currencyField->currencyCode, partCode) == 0);
}

bool isCurrencyField(const ARParseField& field, int fieldId, int currencyPartType)
{
	return (field.tag == AR_CURRENCY_FLD &&
		field.u.currencyField->fieldId == fieldId &&
		field.u.currencyField->partTag == currencyPartType &&
		field.u.currencyField->partTag != AR_CURRENCY_PART_FUNCTIONAL &&
		strcmp(field.u.currencyField->currencyCode, "") == 0);
}

TEST(ARParseFieldTests, InvalidFieldExample1)
{
	CARParseField parseField("1234abc");
	const ARParseField &result = parseField.getField();

	ASSERT_EQ(0, result.tag);
}

TEST(ARParseFieldTests, InvalidFieldExample2)
{
	CARParseField parseField("1234$");
	const ARParseField &result = parseField.getField();

	ASSERT_EQ(0, result.tag);
}

TEST(ARParseFieldTests, BasicField)
{
	CARParseField parseField("536870920");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isField(result, 536870920));
}

TEST(ARParseFieldTests, StatusHistory_User)
{
	CARParseField parseField("15.3.1");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isStatusHistory(result, AR_STAT_HISTORY_USER, 3));
}

TEST(ARParseFieldTests, StatusHistory_Time)
{
	CARParseField parseField("15.0.2");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isStatusHistory(result, AR_STAT_HISTORY_TIME, 0));
}

TEST(ARParseFieldTests, InvalidStatusHistory)
{
	CARParseField parseField("15.4.3");
	const ARParseField &result = parseField.getField();

	ASSERT_EQ(0, result.tag);
}

TEST(ARParseFieldTests, Keyword)
{
	CARParseField parseField("-6");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isField(result, -6));
}

TEST(ARParseFieldTests, InvalidKeyword)
{
	CARParseField parseField("-15.1.3");
	const ARParseField &result = parseField.getField();

	ASSERT_EQ(0, result.tag);
}

TEST(ARParseFieldTests, CurrencyFieldFunctional)
{
	CARParseField parseField("536870987.1.USD");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isCurrencyField(result, 536870987, AR_CURRENCY_PART_VALUE, "USD"));
}

TEST(ARParseFieldTests, CurrencyFieldSimple)
{
	CARParseField parseField("536870987.3");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isCurrencyField(result, 536870987, AR_CURRENCY_PART_DATE));
}

TEST(ARParseFieldTests, CurrencySupportForFieldPartType)
{
	CARParseField parseField("536870987.0");
	const ARParseField &result = parseField.getField();

	ASSERT_TRUE(isCurrencyField(result, 536870987, AR_CURRENCY_PART_FIELD));
}
