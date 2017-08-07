#ifndef LICENSEPP_H_
#define LICENSEPP_H_

#if defined(__APPLE__)

#define DllExport

#ifndef MAX_PATH
#    define MAX_PATH 1024
#endif

#elif defined(__unix__)

#define DllExport

#ifndef MAX_PATH
#    define MAX_PATH 1024
#endif

#else

#include <windows.h>
#define DllExport  __declspec( dllexport )

#endif

#include "metalicensor/api/datatypes.h"

/*
 * Method used to convert the LicenseInfo into a human readable
 * representation.
 */
DllExport void print_error(char out_buffer[256], LicenseInfo* licenseInfo);

/**
 * This method calculate the pc identifier. The string has to be shown
 * to the user in order to calculate the license.
 */
DllExport void identify_pc(IDENTIFICATION_STRATEGY pc_id_method,
		char chbuffer[PC_IDENTIFIER_SIZE + 1]);
/*
 * The optional parameter License contains the information the program that uses the library
 * should display:
 *
 * @return true if successful. False if there are errors.
 * @param licenseLocation[in] licenseLocation, either the name of the file
 * 								or the name of the environment variable should be !='\0'
 * @param license[out] optional, can be NULL.
 */

DllExport EVENT_TYPE acquire_license(const char * productName,
		LicenseLocation licenseLocation, LicenseInfo* license);

/**
 * Do nothing for now, useful for network licenses.
 * Should be called from time to time to confirm we're still using the
 * slicense.
 */
DllExport EVENT_TYPE confirm_license(char * productName,
		LicenseLocation licenseLocation);
/**
 * Do nothing for now, useful for network licenses.
 */
DllExport EVENT_TYPE release_license(char * productName,
		LicenseLocation licenseLocation);

#endif
