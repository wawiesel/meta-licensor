/*
 * CryptpHelperMac.h
 *
 *  Created on: Sep 14, 2014
 *
 */

#ifndef CRYPTPHELPERMac_H_
#define CRYPTPHELPERMac_H_
#include <openssl/rsa.h>
#include <cstddef>
#include <string>
#include "metalicensor/crypto/CryptoHelper.h"

namespace license {
using namespace std;

class CryptoHelperMac : public CryptoHelper {
private:
	static const int kBits = 1024;
	static const int kExp = 65537;
	RSA * rsa;
	const string Opensslb64Encode(size_t slen, unsigned char* signature) const;
public:
	CryptoHelperMac();

	virtual void generateKeyPair();
	virtual const string exportPrivateKey() const;
	virtual const string exportPublicKey() const;

	virtual const string signString(const void* privateKey, size_t pklen, const string& license) const;
	virtual ~CryptoHelperMac();
};

} /* namespace license */

#endif /* CRYPTPHELPERMac_H_ */
