
#include <memory>
#include "metalicensor/crypto/CryptoHelper.h"
#if defined(__APPLE__)
#include "metalicensor/crypto/CryptoHelperMac.h"
#elif defined(__unix__)
#include "metalicensor/crypto/CryptoHelperLinux.h"
#else
#include "metalicensor/crypto/CryptoHelperWindows.h"
#endif

using namespace std;

namespace license {

    unique_ptr<CryptoHelper> CryptoHelper::getInstance() {
    #if defined( __APPLE__ )
        unique_ptr<CryptoHelper> ptr((CryptoHelper*) new CryptoHelperMac());
    #elif defined( __unix__ )
        unique_ptr<CryptoHelper> ptr((CryptoHelper*) new CryptoHelperLinux());
    #else
        unique_ptr<CryptoHelper> ptr((CryptoHelper*) new CryptoHelperWindows());
    #endif
        return ptr;
    }

} //namespace license
