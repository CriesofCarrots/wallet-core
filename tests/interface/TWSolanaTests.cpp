// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Base58.h"
#include "HexCoding.h"
#include "TWTestUtilities.h"
#include "proto/Solana.pb.h"

#include <TrustWalletCore/TWHDWallet.h>
#include <TrustWalletCore/TWSolanaAddress.h>
#include <TrustWalletCore/TWSolanaProto.h>
#include <TrustWalletCore/TWSolanaSigner.h>

#include <gtest/gtest.h>

using namespace TW;

TEST(TWSolanaSigner, SignTransfer) {
    auto privateKey = Base58::bitcoin.decode("A7psj2GW7ZMdY4E5hJq14KMeYg7HFjULSsWSrTXZLvYr");
    auto input = Solana::Proto::SigningInput();

    auto &message = *input.mutable_transfer_transaction();
    message.set_private_key(privateKey.data(), privateKey.size());
    message.set_recipient("EN2sCsJ1WDV8UFqsiTXHcUPUxQ4juE71eCknHYYMifkd");
    message.set_value((uint64_t)42L);
    input.set_recent_blockhash("11111111111111111111111111111111");

    auto inputData = input.SerializeAsString();
    auto inputTWData = TWDataCreateWithBytes((const byte *)inputData.data(), inputData.size());
    auto outputTWData = TWSolanaSignerSign(inputTWData);
    auto output = Solana::Proto::SigningOutput();
    output.ParseFromArray(TWDataBytes(outputTWData), TWDataSize(outputTWData));

    auto expectedHex =
        "01fda1c8ad8872d94f7eab52f9c38dc77e1061f4897e3de2b8469eb0992269f6fa1f173e93dbb2da738ab4e895"
        "9ffa50cd087cdfa889f3a1b8acdd62552f7c1d070100020366c2f508c9c555cacc9fb26d88e88dd54e210bb5a8"
        "bce5687f60d7e75c4cd07fc68b3c894c782b05a9c27fc6c66eb14d4e7d31de9086ab7d2129bcb0493afa020000"
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000001020200010c020000002a00000000000000";
    ASSERT_EQ(hex(output.encoded()), expectedHex);
}

TEST(TWSolanaSigner, SignDelegateStakeTransaction) {
    auto privateKey = Base58::bitcoin.decode("AevJ4EWcvQ6dptBDvF2Ri5pU6QSBjkzSGHMfbLFKa746");
    auto input = Solana::Proto::SigningInput();

    auto &message = *input.mutable_stake_transaction();
    message.set_private_key(privateKey.data(), privateKey.size());
    message.set_validator_pubkey("4jpwTqt1qZoR7u6u639z2AngYFGN3nakvKhowcnRZDEC");
    message.set_value((uint64_t)42L);
    input.set_recent_blockhash("11111111111111111111111111111111");

    auto inputData = input.SerializeAsString();
    auto inputTWData = TWDataCreateWithBytes((const byte *)inputData.data(), inputData.size());
    auto outputTWData = TWSolanaSignerSign(inputTWData);
    auto output = Solana::Proto::SigningOutput();
    output.ParseFromArray(TWDataBytes(outputTWData), TWDataSize(outputTWData));

    auto expectedHex =
        "018efed47208bf63df029951cea09600a6fa697c1a8b715a24347e4b43750694af40d870dbaad894d7b5a8d45c"
        "cd9eeaa366a1c3d5ccca93d5c707f8221f9d5904010005080eba44e56f060007284dc037275a15094c1d6c0697"
        "ddb28b2be661dfb0f4bab8e26f634c7f6a8f05eea8b1e74a93d6aaee9a07c907e9a825931fe678b26c5f3206a7"
        "d517192c5c51218cc94c3d4af17f58daee089ba1fd44e3dbd98a00000000378ba8d9f9881e9be69cf1d70ee0a9"
        "3ed0378b83203f42fa29f9df5c887f1c0d06a7d51718c774c928566398691d5eb68b5eb8a39b4b6d5c73555b21"
        "0000000006a1d817a502050b680791e6ce6db88e1e5b7150f61fc6790a4eb4d100000000000000000000000000"
        "000000000000000000000000000000000000000000000006a1d8179137542a983437bdfe2a7ab2557f535c8a78"
        "722b68a49dc0000000000000000000000000000000000000000000000000000000000000000000000000030602"
        "000134000000002a00000000000000d80600000000000006a1d8179137542a983437bdfe2a7ab2557f535c8a78"
        "722b68a49dc000000000070201026c000000000eba44e56f060007284dc037275a15094c1d6c0697ddb28b2be6"
        "61dfb0f4bab80eba44e56f060007284dc037275a15094c1d6c0697ddb28b2be661dfb0f4bab800000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000007050103040500040200000"
        "0";
    ASSERT_EQ(hex(output.encoded()), expectedHex);
}

TEST(TWSolanaSigner, SignDeactivateStakeTransaction) {
    auto privateKey = Base58::bitcoin.decode("AevJ4EWcvQ6dptBDvF2Ri5pU6QSBjkzSGHMfbLFKa746");
    auto input = Solana::Proto::SigningInput();

    auto &message = *input.mutable_deactivate_stake_transaction();
    message.set_private_key(privateKey.data(), privateKey.size());
    message.set_validator_pubkey("4jpwTqt1qZoR7u6u639z2AngYFGN3nakvKhowcnRZDEC");
    input.set_recent_blockhash("11111111111111111111111111111111");

    auto inputData = input.SerializeAsString();
    auto inputTWData = TWDataCreateWithBytes((const byte *)inputData.data(), inputData.size());
    auto outputTWData = TWSolanaSignerSign(inputTWData);
    auto output = Solana::Proto::SigningOutput();
    output.ParseFromArray(TWDataBytes(outputTWData), TWDataSize(outputTWData));

    auto expectedHex =
        "010edc9131bbfd79536d9e7fc403f5a0fcb36095c1fd2561147f1086173104d028dbe0ff228d11d2e5ea03752e"
        "2ef0c66d2a8d232387cf7bf311068e992566e40f010002040eba44e56f060007284dc037275a15094c1d6c0697"
        "ddb28b2be661dfb0f4bab8e26f634c7f6a8f05eea8b1e74a93d6aaee9a07c907e9a825931fe678b26c5f3206a7"
        "d51718c774c928566398691d5eb68b5eb8a39b4b6d5c73555b210000000006a1d8179137542a983437bdfe2a7a"
        "b2557f535c8a78722b68a49dc00000000000000000000000000000000000000000000000000000000000000000"
        "000000000103030102000405000000";
    ASSERT_EQ(hex(output.encoded()), expectedHex);
}

TEST(TWSolanaSigner, SignWithdrawStakeTransaction) {
    auto stakePrivateKey = Base58::bitcoin.decode("AevJ4EWcvQ6dptBDvF2Ri5pU6QSBjkzSGHMfbLFKa746");
    auto input = Solana::Proto::SigningInput();

    auto &message = *input.mutable_withdraw_transaction();
    message.set_private_key(stakePrivateKey.data(), stakePrivateKey.size());
    message.set_validator_pubkey("4jpwTqt1qZoR7u6u639z2AngYFGN3nakvKhowcnRZDEC");
    message.set_value((uint64_t)42L);
    input.set_recent_blockhash("11111111111111111111111111111111");

    auto inputData = input.SerializeAsString();
    auto inputTWData = TWDataCreateWithBytes((const byte *)inputData.data(), inputData.size());
    auto outputTWData = TWSolanaSignerSign(inputTWData);
    auto output = Solana::Proto::SigningOutput();
    output.ParseFromArray(TWDataBytes(outputTWData), TWDataSize(outputTWData));

    auto expectedHex =
        "015095806889455cdef7ff520bf8e7ed4cf67e3d04559c806400995273f4d88a20d85203e9aa15012dd3210224"
        "20dc6c9ae6a6776fb81496819b1fd9756b20bf0f010003050eba44e56f060007284dc037275a15094c1d6c0697"
        "ddb28b2be661dfb0f4bab8e26f634c7f6a8f05eea8b1e74a93d6aaee9a07c907e9a825931fe678b26c5f3206a7"
        "d51718c774c928566398691d5eb68b5eb8a39b4b6d5c73555b210000000006a7d517193584d0feed9bb3431d13"
        "206be544281b57b8566cc5375ff400000006a1d8179137542a983437bdfe2a7ab2557f535c8a78722b68a49dc0"
        "000000000000000000000000000000000000000000000000000000000000000000000000010404010002030c04"
        "0000002a00000000000000";
    ASSERT_EQ(hex(output.encoded()), expectedHex);
}

TEST(TWSolanaAddress, HDWallet) {
    auto mnemonic =
        "shoot island position soft burden budget tooth cruel issue economy destroy above";
    auto passphrase = "";

    auto wallet = WRAP(
        TWHDWallet, TWHDWalletCreateWithMnemonic(STRING(mnemonic).get(), STRING(passphrase).get()));

    auto privateKey = TWHDWalletGetKey(wallet.get(), TWCoinTypeDerivationPath(TWCoinTypeSolana));
    auto publicKey = TWPrivateKeyGetPublicKeyEd25519(privateKey);
    auto address = TWSolanaAddressCreateWithPublicKey(publicKey);
    auto addressStr = WRAPS(TWSolanaAddressDescription(address));

    assertStringsEqual(addressStr, "2bUBiBNZyD29gP1oV6de7nxowMLoDBtopMMTGgMvjG5m");
}
