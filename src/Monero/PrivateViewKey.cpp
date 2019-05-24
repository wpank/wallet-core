// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "PrivateKey.h"
#include "PublicKey.h"
#include "PrivateSpendKey.h"
#include "PrivateViewKey.h"
#include "PublicViewKey.h"
#include "PublicSpendKey.h"

#include <TrezorCrypto/ed25519-donna/ed25519-blake2b.h>



using namespace TW;

PublicViewKey PrivateViewKey::getPublicViewKey() const{
    Data result(PublicKey::ed25519Size);
    ed25519_publickey(bytes.data(), result.data());
    return PublicViewKey(result);
}

