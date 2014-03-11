#ifndef MY_UUID_H__
#define MY_UUID_H__

#include <string>
#include <uuid/uuid.h>

const int UUIDLEN = 36;

class MyUuid
{
public:
    MyUuid();
    MyUuid(uuid_t sUuid);
    MyUuid(const char *pString, unsigned iSize);

    MyUuid(const MyUuid &sOther);
    MyUuid &operator=(const MyUuid &sOther);
    MyUuid &operator=(const uuid_t &sOther);

    bool operator < (const MyUuid &sCmp) const;

    const uuid_t * const Uuid() const {
        return &m_dUuid;
    }

    const char *UuidString() const {
        return m_szUuidStr;
    }

    static const std::string& NewUuid();
protected:
    uuid_t m_dUuid;
    char m_szUuidStr[UUIDLEN + 1];
};

#endif // MY_UUID_H__
