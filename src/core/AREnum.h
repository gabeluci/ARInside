//Copyright (C) 2009 Stefan Nerlich | stefan.nerlich@hotmail.com
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
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include "../ARApi.h"
#define EnumDefault "Unknown"

class CAREnum
{
public:
	static string TrimType(int nType);
	static string ControlType(int bMaskIn);
	static string Operand(int nType);
	static unsigned int OperandPrecedence(int nType);
	static string Function(int nType);
	static string FieldPropertiesLabel(int nType);
	static string FieldPropertiesValue(int nProp, int nVal);
	static string ContainerRefType(int nType);
	static string SchemaType(int nType);
	static const char* SchemaTypeImage(int nType);
	static const char* JoinType(int nType);
	static string ContainerType(int nType);
	static string ContainerImage(int nType);
	static string ContainerDir(int nType);
	static string GroupType(int nType);
	static string GroupCategory(int nType);
	static string ObjectEnable(int nType);
	static string MenuDDLabelFormat(int nType);
	static string MenuDDValueFormat(int nType);
	static string MenuItemType(int nType);
	static string MenuFileLocation(int nType);
	static string MenuType(int nType);
	static string MenuRefresh(int nType);
	static string DataType(int nType);
	static string FieldType(int nType);
	static string VuiType(int nType);
	static string SchemaSortOrder(int nType);
	static string ObjectPermission(int nType);
	static string FieldPermission(int nType);
	static string UserGetLicType(int nType);
	static string UserGetFTLicType(int nType);
	static string UserGetDefNotify(int nType);
	static string ActiveLinkAction(int nType);
	static string ActiveLinkMessageType(int nType);
	static string Keyword(int nType);
	static int OpenWindowModeMapped(int nType);
	static string OpenWindowMode(int nType);
	static string OpenWindowDisplayType(int nType);
	static string FilterAction(int nType);
	static string MessageType(int nType);
	static string NotifyMechanism(int nType);
	static string NotifyFieldList(int nType);
	static string FieldOption(int nType);
	static string FieldCreateMode(int nType);
	static string FieldQbeMatch(int nType);
	static string FieldFTOption(int nType);
	static string EnumStyle(int nType);
	static string AssignType(int nType);
	static string NoMatchRequest(int nType);
	static string MultiMatchRequest(int nType);
	static string XmlStructItem(int nType);
	static string DDEAction(int nType);
	static string SetCharFieldAccess(int nType);
	static string SetCharFieldVisibility(int nType);
	static string ServerInfoApiCall(int nType);
	static string AuditStyle(int nType);
#if AR_CURRENT_API_VERSION > 13 // Version 7.5 and higher
	static string AuditChangedFields(int nType);
#endif
	static const char* ReportLocation(int nType);
	static const char* ReportOperation(int nType);
	static const char* FieldMappingType(int nType);
	static const char* ColumnDataSourceType(int nType);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	static const char* StorageOptionForCLOB(int nOpt);
#endif
	static const char* GetOverlayTypeString(int overlayType);
	static const char* GetOverlayType(int overlayType);
	static const char* CallGuideMode(int mode);
	static const char* WeightedRelevancyFieldType(int nType);
	static const char* WeekDayName(int day);
	static const char* CurrencyPart(int currencyPartType);
	static const char* StatHistoryTag(int usrOrTime);
};
