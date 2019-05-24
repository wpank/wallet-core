// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Hash.h"
#include "../PrivateKey.h"
#include "PublicViewKey.h"

namespace TW {
    class PrivateViewKey : public PrivateKey {
    public:

        /// Initializes a private view key with a collection of bytes.
        template <typename T>
        explicit PrivateViewKey(const T& data) : PrivateKey(data) {
            if (!isValid(data)) {
                throw std::invalid_argument("Invalid private key data");
            }
            std::copy(std::begin(data), std::end(data), std::begin(bytes));
        }

        /// Returns the public key for this private key.
        PublicViewKey getPublicViewKey() const;
    };
}

/// Wrapper for C interface.
struct TWPrivateViewKey {
    TW::PrivateViewKey impl;
};


