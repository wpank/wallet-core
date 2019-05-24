// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "PrivateKey.h"

#include "PrivateSpendKey.h"
#include "PublicSpendKey.h"
#include <TrezorCrypto/ed25519-donna/ed25519-blake2b.h>
#include "HexCoding.h"



using namespace TW;

    PublicSpendKey PrivateSpendKey::getPublicSpendKey() const {
        Data result(PublicKey::ed25519Size);
        ed25519_publickey(bytes.data(), result.data());
        return PublicSpendKey(result);
    }

    PrivateViewKey PrivateSpendKey::getPrivateViewKey() const {
        Data svkHash = Hash::keccak256(bytes);
    }

