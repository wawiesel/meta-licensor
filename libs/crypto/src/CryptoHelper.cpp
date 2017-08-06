
#include <memory>
#include "metalicensor/crypto/CryptoHelper.h"
#ifdef __APPLE__
#include "metalicensor/crypto/CryptoHelperLinux.h"
#else
#include "metalicensor/crypto/CryptoHelperWindows.h"
#endif

using namespace std;

namespace license {

    unique_ptr<CryptoHelper> CryptoHelper::getInstance() {
    #ifdef __APPLE__
        unique_ptr<CryptoHelper> ptr((CryptoHelper*) new CryptoHelperLinux());
    #else
        unique_ptr<CryptoHelper> ptr((CryptoHelper*) new CryptoHelperWindows());
    #endif
        return ptr;
    }

} //namespace license
