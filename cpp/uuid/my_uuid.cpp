#include "my_uuid.h"

#include <iostream>
#include <string.h>
#include <assert.h>

MyUuid::MyUuid()
{
	memset(m_szUuidStr, '\0', UUIDLEN + 1);
	uuid_generate(m_dUuid);
	uuid_unparse(m_dUuid, m_szUuidStr);
}

MyUuid::MyUuid(uuid_t sUuid)
{
	uuid_copy(m_dUuid, sUuid);
	memset(m_szUuidStr, '\0', UUIDLEN + 1);
	uuid_unparse(m_dUuid, m_szUuidStr);
}

MyUuid::MyUuid(const char *pString, unsigned iSize)
{
	assert(iSize == UUIDLEN);
	memset(m_szUuidStr, '\0', UUIDLEN + 1);
	strncpy(m_szUuidStr, pString, UUIDLEN);
	uuid_parse(m_szUuidStr, m_dUuid);
}

MyUuid::MyUuid(const MyUuid &sOther)
{
	uuid_copy(m_dUuid, sOther.m_dUuid);
	memset(m_szUuidStr, '\0', UUIDLEN + 1);
	uuid_parse(m_szUuidStr, m_dUuid);
}

MyUuid& MyUuid::operator=(const MyUuid &sOther)
{
	if (this == &sOther)
		return *this;

	uuid_copy(m_dUuid, sOther.m_dUuid);
	memset(m_szUuidStr, '\0', UUIDLEN + 1);
	uuid_parse(m_szUuidStr, m_dUuid);
}

bool MyUuid::operator < (const MyUuid &sCmp) const
{
	if (uuid_compare(m_dUuid, sCmp.m_dUuid) < 0)
		return true;
	return false;
}

const std::string& MyUuid::NewUuid()
{
	uuid_t	tmp_uuid;
	uuid_generate(tmp_uuid);
	char	tmp_struuid[UUIDLEN + 1];
	memset(tmp_struuid, '\0', UUIDLEN + 1);
	uuid_unparse(tmp_uuid, tmp_struuid);
	static std::string sUuid(tmp_struuid);
	return sUuid;
}
