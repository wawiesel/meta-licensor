#define BOOST_TEST_MODULE license_reader_test
//#define BOOST_TEST_MAIN
//#define BOOST_TEST_DYN_LINK
#include <stdlib.h>
#include <boost/test/unit_test.hpp>
#include "metalicensor/reader/LicenseReader.h"
#include "metalicensor/utils/build_properties.hpp"

using namespace license;

BOOST_AUTO_TEST_CASE( read_single_file ) {
	const char * licLocation = METALICENSOR_TEST_SRC_DIR "/test_reader.ini";
	const LicenseLocation location = { licLocation, NULL, false };
	LicenseReader licenseReader(location);
	vector<FullLicenseInfo> licenseInfos;
	EventRegistry registry = licenseReader.readLicenses("PrODUCT",
			licenseInfos);
	BOOST_CHECK(registry.isGood());
	BOOST_CHECK_EQUAL(1, licenseInfos.size());
}

BOOST_AUTO_TEST_CASE( product_not_licensed ) {
	const char * licLocation =
	METALICENSOR_TEST_SRC_DIR "/test_reader.ini";
	const LicenseLocation location = { licLocation, NULL, false };
	LicenseReader licenseReader(location);
	vector<FullLicenseInfo> licenseInfos;
	EventRegistry registry = licenseReader.readLicenses("PRODUCT-NOT",
			licenseInfos);
	BOOST_CHECK(!registry.isGood());
	BOOST_CHECK_EQUAL(0, licenseInfos.size());
	BOOST_ASSERT(registry.getLastFailure()!=NULL);
	BOOST_CHECK_EQUAL(PRODUCT_NOT_LICENSED,
			registry.getLastFailure()->event_type);
}

BOOST_AUTO_TEST_CASE( file_not_found ) {
	const char * licLocation = METALICENSOR_TEST_SRC_DIR "/not_found.ini";
	//const char * envName = "MYVAR";
	const LicenseLocation location = { licLocation, NULL, false };
	LicenseReader licenseReader(location);
	vector<FullLicenseInfo> licenseInfos;
	EventRegistry registry = licenseReader.readLicenses("PRODUCT",
			licenseInfos);
	BOOST_CHECK(!registry.isGood());
	BOOST_CHECK_EQUAL(0, licenseInfos.size());
	BOOST_ASSERT(registry.getLastFailure()!=NULL);
	BOOST_CHECK_EQUAL(LICENSE_FILE_NOT_FOUND,
			registry.getLastFailure()->event_type);
}

BOOST_AUTO_TEST_CASE( env_var_not_defined ) {
	const char * envName = "MYVAR";
	const LicenseLocation location = { NULL, envName, false };
	LicenseReader licenseReader(location);
	vector<FullLicenseInfo> licenseInfos;
	EventRegistry registry = licenseReader.readLicenses("PRODUCT",
			licenseInfos);
	BOOST_CHECK(!registry.isGood());
	BOOST_CHECK_EQUAL(0, licenseInfos.size());
	BOOST_ASSERT(registry.getLastFailure()!=NULL);
	BOOST_CHECK_EQUAL(ENVIRONMENT_VARIABLE_NOT_DEFINED,
			registry.getLastFailure()->event_type);
}

BOOST_AUTO_TEST_CASE( read_env_var ) {
	char str[MAX_PATH];
	strcpy(str,"LIC_VAR=" METALICENSOR_TEST_SRC_DIR "/test_reader.ini");
#ifdef __APPLE__
	putenv(str);
#else //windows
    _putenv(str);
#endif //windows
	const LicenseLocation location = { NULL, "LIC_VAR", false };
	LicenseReader licenseReader(location);
	vector<FullLicenseInfo> licenseInfos;
	EventRegistry registry = licenseReader.readLicenses("PrODUCT",licenseInfos);
	BOOST_CHECK(registry.isGood());
	BOOST_CHECK_EQUAL(1, licenseInfos.size());
}

