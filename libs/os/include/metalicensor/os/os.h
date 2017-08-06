
#ifndef OS_DEPENDENT_HPP_
#define OS_DEPENDENT_HPP_

#include <stddef.h>
//definition of size_t
#include <stdlib.h>
#ifdef __APPLE__
#include <stdbool.h>
#endif
#include "metalicensor/base/base.h"

enum VIRTUALIZATION {
	NONE,
    VMWARE
};

enum IFACE_TYPE {
	IFACE_TYPE_ETHERNET,
    IFACE_TYPE_WIRELESS
};

struct OsAdapterInfo {
	int id;
	char description[1024];
	unsigned char mac_address[6];
	unsigned char ipv4_address[4];
	IFACE_TYPE type;
};

struct DiskInfo {
	int id;
	char device[255];
	unsigned char disk_sn[8];
	char label[255];
	bool preferred;
};

FUNCTION_RETURN getAdapterInfos(OsAdapterInfo * adapterInfos, size_t * adapter_info_size);
FUNCTION_RETURN getDiskInfos(DiskInfo * diskInfos, size_t * disk_info_size);
FUNCTION_RETURN getUserHomePath(char[MAX_PATH]);
FUNCTION_RETURN getModuleName(char buffer[MAX_PATH]);
FUNCTION_RETURN getCpuId(unsigned char identifier[6]);
FUNCTION_RETURN getMachineName(unsigned char identifier[6]);
/**
 * Get an identifier of the machine in an os specific way.
 * In Linux it uses:
 * http://stackoverflow.com/questions/328936/getting-a-unique-id-from-a-unix-like-system
 *
 * <ul>
 * <li>Dbus if available</li>
 * </ul>
 * Can be used as a fallback in case no other methods are available.
 * Windows:
 * HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\ CurrentVersion\ProductId
 * http://sowkot.blogspot.it/2008/08/generating-unique-keyfinger-print-for.html
 * http://stackoverflow.com/questions/2842116/reliable-way-of-generating-unique-hardware-id
 *
 *
 * @param identifier
 * @return
 */
FUNCTION_RETURN getOsSpecificIdentifier(unsigned char identifier[6]);
//VIRTUALIZATION getVirtualization();
void os_initialize();

FUNCTION_RETURN verifySignature(const char* stringToVerify, const char* signatureB64);

#endif /* OS_DEPENDENT_HPP_ */
