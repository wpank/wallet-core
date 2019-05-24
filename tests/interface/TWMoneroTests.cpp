// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "TWTestUtilities.h"
#include "proto/Monero.pb.h"
#include "Monero/Address.h"
#include "Monero/crypto_ops.h"

#include "Monero/base58.h"

#include <TrezorCrypto/ecdsa.h>

#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <TrustWalletCore/TWMoneroAddress.h>
#include <TrustWalletCore/TWMoneroSigner.h>
#include <TrustWalletCore/TWMoneroProto.h>
#include <TrustWalletCore/TWHDWallet.h>

#include <gtest/gtest.h>
#include <PrivateKey.h>
#include <Monero/PrivateViewKey.h>
#include <TrezorCrypto/monero/xmr.h>
#include <TrezorCrypto/ed25519.h>

using namespace TW;
using namespace TW::Monero;

TEST(TWMoneroSigner, Sign){

}

TEST(TWMoneroAddress, HDWallet){
    auto mnemonic = "dummy system reunion ointment null hope memoir auctions brunt input pelican perfect laptop "
                    "vehicle giving custom leisure inexact oust betting sword unveil waffle when reunion";
    auto passphrase = "reunion";
    auto wallet = WRAP(TWHDWallet, TWHDWalletCreateWithMnemonic(
            STRING(mnemonic).get(),
            STRING(passphrase).get()
    ));

    auto privateKey = TWHDWalletGetKey(wallet.get(), TWCoinTypeDerivationPath(TWCoinTypeMonero));
//    auto privateKeyHex = parse_hex(privateKey.bytes);
    std::cout<< privateKey;
//    std::cout<<sizeof(privateKey);

}

TEST(TWMoneroAddress, PrivateViewKeyFromPrivateSpendKey) {
    PrivateKey privateSpendKey = PrivateKey(
            parse_hex("d17f7ee37fc904cd04692a0db2a8aa003008de6865d7b0ed7c1515b9892cca03"));
    auto pskHash = Hash::keccak256(privateSpendKey.bytes);
    sc_reduce32(pskHash.data());
    ASSERT_EQ(TW::hex(pskHash), "33c71dd92b22bfb25e8adfa25e2a7efb4565cbda457a2e0bc1aba021484d5f05");
}

TEST(TWMoneroAddress, PublicViewKeyFromPrivateViewKey) {
    Data privateKey = parse_hex("33c71dd92b22bfb25e8adfa25e2a7efb4565cbda457a2e0bc1aba021484d5f05");
    ge_p3 ge_p3_point;
    Data publicKey = Data(32);
    ge_scalarmult_base(&ge_p3_point, privateKey.data());
    ge_p3_tobytes(publicKey.data(), &ge_p3_point);
    ASSERT_EQ(TW::hex(publicKey), "e203501c6ffb515c59b7620e81bc3d7a7de06eecdf07eec059cc4324f0dfd079");
}

TEST(TWMoneroAddress, PublicSpendKeyFromPrivateSpendKey){
    Data privateKey = parse_hex("d17f7ee37fc904cd04692a0db2a8aa003008de6865d7b0ed7c1515b9892cca03");
    ge_p3 ge_p3_point;
    Data publicKey = Data(32);
    ge_scalarmult_base(&ge_p3_point, privateKey.data());
    ge_p3_tobytes(publicKey.data(), &ge_p3_point);
    ASSERT_EQ(TW::hex(publicKey), "2817dc38531a3e53e07546584c3ea3b2352c4719eb456a64445cf0a1f61687c3");
}

TEST(TWMoneroAddress, AddressFromPublicKeys){
    Data publicSpendKey = parse_hex("2817dc38531a3e53e07546584c3ea3b2352c4719eb456a64445cf0a1f61687c3");
    Data publicViewKey = parse_hex("e203501c6ffb515c59b7620e81bc3d7a7de06eecdf07eec059cc4324f0dfd079");
    Data prefix = parse_hex("0x12");

    std::string keys =  hex(prefix) + hex(publicSpendKey) + hex(publicViewKey);

    auto checksum_hash = Hash::keccak256(parse_hex(keys));

    std::cout<<"checksum hash: "<<hex(checksum_hash)<<std::endl;

    std::string checksum_hash_end = hex(checksum_hash.begin(), checksum_hash.begin()+4);
    std::string pre_58 = keys + checksum_hash_end;
    std::cout<<"checksum end: "<<checksum_hash_end<<std::endl;
    std::cout<<"pre 58: "<<pre_58<<std::endl;

    std::cout<<"size: "<<parse_hex(pre_58).size()<<std::endl;
    std::string address = tools::base58::encode(pre_58.data());
    std::cout<<"Address: "<<address<<std::endl;

    auto x = parse_hex(address);
    std::cout<<"hex sieze; "<<publicSpendKey.size()<<std::endl;
    std::cout<<"size of address: "<< parse_hex(pre_58).size()<<std::endl;
    ASSERT_EQ(address, "439EMUy9kEZF2iBC85AvVGWoqbzf6A6cHHmiXME7KFYzZmJvxnqoqJgGSv5NFUgGFnMVKjXReSDGZZB3XA1jQj2wEhjc8eG");

   std::string o;
    auto k = tools::base58::decode(address, o);
    std::cout<<"decoded string: "<<hex(o)<<std::endl;
    std::cout<<"decode: "<<hex(o).size()<<std::endl;
}