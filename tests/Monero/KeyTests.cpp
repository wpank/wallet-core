// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../interface/TWTestUtilities.h"
#include "HexCoding.h"
#include "PrivateKey.h"
#include "PublicKey.h"
#include "Monero/Address.h"
#include "Monero/PrivateViewKey.h"
#include "Monero/PrivateSpendKey.h"
#include "Monero/PublicViewKey.h"
#include "Monero/PublicSpendKey.h"

#include <TrustWalletCore/TWHash.h>
#include <TrustWalletCore/TWPrivateKey.h>
#include <TrustWalletCore/TWPublicKey.h>

#include <gtest/gtest.h>


using namespace TW::Monero;

// PrivateSpendKey
// PublicSpendKey
// PrivateViewKey
// PublicViewKey
TEST(MoneroKeyTests, PrivateSpendKeyFromString) {
//
//    uint8_t bytes[] = {0xd1, 0x7f, 0x7e, 0xe3, 0x7f, 0xc9, 0x04, 0xcd, 0x04, 0x69, 0x2a, 0x0d, 0xb2, 0xa8, 0xaa, 0x00, 0x30, 0x08, 0xde, 0x68, 0x65, 0xd7, 0xb0, 0xed, 0x7c, 0x15, 0x15, 0xb9, 0x89, 0x2c, 0xca, 0x03};
//    auto privateSpendKeyData = WRAPD(TWDataCreateWithBytes(bytes, 32));
//    auto privateSpendKey = WRAP(TWPrivateKey, TWPrivateKeyCreateWithData(privateSpendKeyData.get()));
//
//    const char *message = "Hello";
//    auto messageData = WRAPD(TWDataCreateWithBytes((const uint8_t *)message, strlen(message)));
//    auto digest = WRAPD(TWHashKeccak256(messageData.get()));
//
//    auto signature = WRAPD(TWPrivateKeySign(privateKey.get(), digest.get(), TWCurveSECP256k1));
//
//    auto publicKey = TWPrivateKeyGetPublicKeySecp256k1(privateSpendKey.get(), false);
//    ASSERT_TRUE(TWPublicKeyVerify(publicKey, signature.get(), digest.get()));
}