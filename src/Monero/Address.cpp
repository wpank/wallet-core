// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <iostream>
#include "Address.h"
#include "stdint.h"
#include "../Hash.h"
#include "../HexCoding.h"
#include "base58.h"

using namespace TW::Monero;

bool Address::isValid(const std::string &string){
    if (string.size() != 95 && string.size() != 106){
        std::cout<<"String size: "<<(string.size() == 106)<<std::endl;
        return false;
    }
    std::string decodedAddress;
    tools::base58::decode(string, decodedAddress);
    std::cout<<"what";
    return Address::isValid(parse_hex(decodedAddress));
}

Address::Address(const std::string &string){
    if (!isValid(string)){
        throw std::invalid_argument("Invalid address data");
    }
    const auto data = parse_hex(string);
    std::copy(data.begin(), data.end(), bytes.begin());
}

Address::Address(const PublicKey &publicKey){
    if (publicKey.type != TWPublicKeyTypeED25519){
        throw std::invalid_argument("Monero::Adress needs ED25519 public key");
    }
    const auto data = TWX509EncodeED25519PublicKey(TWDataCreateWithBytes(
            reinterpret_cast<const uint8_t *>(publicKey.bytes.data()), publicKey.bytes.size()));
    const auto h256 = Hash::blake2b(*reinterpret_cast<const std::vector<uint8_t> *>(data), 32);
    const auto h160 = Hash::ripemd(h256);
    std::copy(h160.begin(), h160.end(), this->bytes.begin());
}

std::string Address::string() const {
    return hex(bytes);
}

