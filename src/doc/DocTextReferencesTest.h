#pragma once

#include "DocTextReferences.h"

class CDocTextReferencesTest : public CDocTextReferences
{
public:
	CDocTextReferencesTest(const std::string& inText, const std::string &fieldSeparator, int schemaInsideId, int rootLevel, bool findKeywords, const CRefItem *refItem)
		: CDocTextReferences(inText, fieldSeparator, schemaInsideId, rootLevel, findKeywords, refItem) { callReal_refFieldId = false; }

	void CallReal_refFieldId(bool value) { callReal_refFieldId = value; }

protected:
	virtual string refFieldID(int iFieldId) 
	{
		if (callReal_refFieldId)
			return CDocTextReferences::refFieldID(iFieldId);

		stringstream tmp;	
		tmp << "<a href='Test'>" 
		    << iFieldId 
		    << "</a>"; 
		return tmp.str(); 
	}
	virtual bool isInvalidSchemaId() { return true; }

private:
	bool callReal_refFieldId;
};
