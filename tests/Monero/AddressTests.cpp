// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "PrivateKey.h"
#include "PublicKey.h"
#include "Monero/Address.h"

#include "../interface/TWTestUtilities.h"
#include <gtest/gtest.h>

using namespace TW::Monero;

TEST(MoneroAddress, FromPublicKey){

}

TEST(MoneroAddress, FromString){

}

TEST(MoneroAddress, FromBadPubKey){

}

TEST(MoneroAddress, FromBadString){

}

TEST(MoneroAddress, StealthAddressIsValid){
    ASSERT_TRUE(Address::isValid("439EMUy9kEZF2iBC85AvVGWoqbzf6A6cHHmiXME7KFYzZmJvxnqoqJgGSv5NFUgGFnMVKjXReSDGZZB3XA1jQj2wEhjc8eG"));
}

TEST(MoneroAddress, IntegratedAddressIsValid){
    ASSERT_TRUE(Address::isValid("4CquNHneMW5F2iBC85AvVGWoqbzf6A6cHHmiXME7KFYzZmJvxnqoqJgGSv5NFUgGFnMVKjXReSDGZZB3XA1jQj2wMLEoAsMWnGpMN6RfDF"));
}

TEST(MoneroAddress, FromPrivateKey){

}