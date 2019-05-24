// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Hash.h"
#include "../PublicKey.h"

#include <string>
#include <array>
#include <vector>

namespace TW{

    class PublicViewKey : public PublicKey{
    public:
        /// The number of bytes in a private spend key
        static const size_t size = 32;
        const enum TWPublicKeyType type = TWPublicKeyTypeED25519;


        /// Initializes a public view key with a collection of bytes.
        ///
        /// @throws std::invalid_argument if the data is not a valid public key.
        template <typename T>
        explicit PublicViewKey(const T& data): PublicKey(data, type){
            if (!isValid(data, type)) {
                throw std::invalid_argument("Invalid public key data");
            }
            bytes.reserve(ed25519Size);
            if (data.size() == ed25519Size + 1) {
                std::copy(std::begin(data) + 1, std::end(data), std::back_inserter(bytes));
            } else {
                std::copy(std::begin(data), std::end(data), std::back_inserter(bytes));
            }
        }


    };

} // namespace TW

/// Wrapper for C interface.
struct TWPublicViewKey {
    TW::PublicViewKey impl;
};

namespace TW{

}

