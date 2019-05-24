// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../PrivateKey.h"
#include "PublicSpendKey.h"
#include "PrivateViewKey.h"

namespace TW{

    class PrivateSpendKey : public PrivateKey{
    public:

        /// Initializes a private Spend key with a collection of bytes.
        template <typename T>
        explicit PrivateSpendKey(const T& data) : PrivateKey(data) {
            if (!isValid(data)) {
                throw std::invalid_argument("Invalid private key data");
            }
            std::copy(std::begin(data), std::end(data), std::begin(bytes));
        }

        /// Returns the public key for this private key.
        PublicSpendKey getPublicSpendKey() const;

        /// Returns a derived private view key
        PrivateViewKey getPrivateViewKey() const;

    };

} // namespace TW

/// Wrapper for C interface.
struct TWPrivateSpendKey {
    TW::PrivateSpendKey impl;
};
