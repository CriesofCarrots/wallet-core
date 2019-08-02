import { expect } from 'chai';
import 'mocha';

import { bufToHex, fromHexString } from '../../Utils';
import { Base58, PrivateKey, SolanaAddress, PublicKey, PublicKeyType } from '../../../lib';

describe('SolanaAddress', () => {

    it('test address from PrivateKey', () => {
        const key = PrivateKey.createWithData(Base58.decodeNoCheck('A7psj2GW7ZMdY4E5hJq14KMeYg7HFjULSsWSrTXZLvYr'));
        const pubkey = key.getPublicKeyEd25519();
        const address = SolanaAddress.createWithPublicKey(pubkey);

        expect(Base58.encodeNoCheck(pubkey.data())).to.equal('7v91N7iZ9mNicL8WfG6cgSCKyRXydQjLh6UYBWwm6y1Q');
        expect(address.description()).to.equal('7v91N7iZ9mNicL8WfG6cgSCKyRXydQjLh6UYBWwm6y1Q');
    });

    it('test address from PublicKey', () => {
        const pubkey = PublicKey.createWithData(Base58.decodeNoCheck('7v91N7iZ9mNicL8WfG6cgSCKyRXydQjLh6UYBWwm6y1Q'), PublicKeyType.ED25519);
        const addressPubkey = SolanaAddress.createWithPublicKey(pubkey);
        const addressString = SolanaAddress.createWithString('7v91N7iZ9mNicL8WfG6cgSCKyRXydQjLh6UYBWwm6y1Q');

        // expect(addressPubkey.description()).to.equal('7v91N7iZ9mNicL8WfG6cgSCKyRXydQjLh6UYBWwm6y1Q');
        expect(addressString.description()).to.equal('7v91N7iZ9mNicL8WfG6cgSCKyRXydQjLh6UYBWwm6y1Q');
    });

});
