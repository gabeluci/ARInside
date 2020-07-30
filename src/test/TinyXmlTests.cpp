#include "ARInsideTest.h"
#include <tinyxml/tinyxml.h>

/* 
 The following test parses a correct UTF-8 encoded xml document returned by ARAPI for example
 in the SetFields-Webservice-Call. 
 
 The encoding of the data provided by the ARAPI does depend on the localeInfo.charset variable
 in the ARControlStruct. (On linux the LANG env-var has impact on the locale identification of 
 the client as well!) 

 If the client connects as a UTF8 client, all data (all strings, e.g. object names and so on)
 send to the client is encoded in UTF-8. But if the client connects to the server as a none-
 unicode client, string-data is converted in a client-specific codepage (e.g. win1252). So 
 even if there is a UTF-8 encoded XML-Document stored in a filter-api-setfields-action (like 
 a webservice-call does), the data retrieved by the client is not UTF-8 encoded! The data is
 converted. If such a incorrect encoded xml is passed to TiXmlDocument, of course the parsing
 fails. 
 And it could get more complicated: the xml-document stored in the filter-api setfields can
 be encoded in other codepages too (e.g. the Sample:GetWeather is win1252 encoded). 
 I'm not sure how this was created, but I assume the old admin-tool did create webservice
 calls using then encoding of the client OS (e.g. win1252).

 First test  .. correct encoded UTF-8 document.
*/

TEST(TinyXmlUTF8, DecodeIfCorrectUTF8String_Ticket141)
{
	const char* xmlDoc = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		"<arDocMapping arDocVersion=\"11\" externalSchema=\"\"\n"
		"    generateXsiType=\"false\" name=\"UpdateTMTicket\" schemaSource=\"imported\">\n"
		"		<element dataType=\"string\" default=\"\" enumValues=\"Kyll\xc3\xa4\" form=\"qualified\" />\n"
		"</arDocMapping>";

	TiXmlDocument inputXML;
	inputXML.Parse(xmlDoc, 0, TIXML_DEFAULT_ENCODING);

	ASSERT_FALSE(inputXML.Error());

	TiXmlHandle inputHandle(&inputXML);
	TiXmlElement *element = inputHandle.FirstChild("arDocMapping").FirstChild("element").ToElement();
	const char* attr = element->Attribute("form");

	ASSERT_STREQ("qualified", attr);
}

/*
 Second test .. xml-doc with UTF-8 encoding in header but data in win1252. We need to pass
                TIXML_ENCODING_LEGACY to the TiXmlDocument to get a successful parse.
*/

TEST(TinyXmlUTF8, DecodeIfCorrectWin1252String_Ticket141)
{
	const char* xmlDoc = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		"<arDocMapping arDocVersion=\"11\" externalSchema=\"\"\n"
		"    generateXsiType=\"false\" name=\"UpdateTMTicket\" schemaSource=\"imported\">\n"
		"		<element dataType=\"string\" default=\"\" enumValues=\"Kyll\xe4\" form=\"qualified\" />\n"
		"</arDocMapping>";

	TiXmlDocument inputXML;

	// parsing the first time fails!
	inputXML.Parse(xmlDoc, 0, TIXML_DEFAULT_ENCODING);
	ASSERT_TRUE(inputXML.Error());

	// parsing in legacy mode doesn't fail, but ....
	inputXML.Parse(xmlDoc, 0, TIXML_ENCODING_LEGACY);
	ASSERT_FALSE(inputXML.Error());

	// ... the document isn't parsed correctly. We can't read the 'form' attribute!
	TiXmlHandle inputHandle(&inputXML);
	TiXmlElement *element = inputHandle.FirstChild("arDocMapping").FirstChild("element").ToElement();
	const char* attr = element->Attribute("form");

	ASSERT_EQ(NULL, attr);
}
