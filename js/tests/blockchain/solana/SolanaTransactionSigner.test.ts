import { expect } from 'chai';
import 'mocha';

import * as Long from 'long';

import { bufToHex } from '../../Utils';
import { TW, Base58, PrivateKey, SolanaSigner } from '../../../lib';

describe('SolanaSigner', () => {

    it('test Solana transaction signing', () => {
        const signingInput = TW.Solana.Proto.SigningInput.create({
            privateKey: Base58.decodeNoCheck('A7psj2GW7ZMdY4E5hJq14KMeYg7HFjULSsWSrTXZLvYr'),
            recipient: "EN2sCsJ1WDV8UFqsiTXHcUPUxQ4juE71eCknHYYMifkd",
            lamports: Long.fromString("42"),
            recentBlockhash: "11111111111111111111111111111111",
        });

        const output: TW.Solana.Proto.SigningOutput = SolanaSigner.sign(signingInput);
        const expectedOutput = Uint8Array.from([
            1,   253, 161, 200, 173, 136, 114, 217, 79,  126, 171, 82,  249, 195, 141, 199, 126, 16,
            97,  244, 137, 126, 61,  226, 184, 70,  158, 176, 153, 34,  105, 246, 250, 31,  23,  62,
            147, 219, 178, 218, 115, 138, 180, 232, 149, 159, 250, 80,  205, 8,   124, 223, 168, 137,
            243, 161, 184, 172, 221, 98,  85,  47,  124, 29,  7,   1,   0,   2,   3,   102, 194, 245,
            8,   201, 197, 85,  202, 204, 159, 178, 109, 136, 232, 141, 213, 78,  33,  11,  181, 168,
            188, 229, 104, 127, 96,  215, 231, 92,  76,  208, 127, 198, 139, 60,  137, 76,  120, 43,
            5,   169, 194, 127, 198, 198, 110, 177, 77,  78,  125, 49,  222, 144, 134, 171, 125, 33,
            41,  188, 176, 73,  58,  250, 2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
            0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
            0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
            0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,
            2,   2,   0,   1,   12,  2,   0,   0,   0,   42,  0,   0,   0,   0,   0,   0,   0]);

        expect(bufToHex(output.encoded)).to.equal('0x01fda1c8ad8872d94f7eab52f9c38dc77e1061f4897e3de2b8469eb0992269f6fa1f173e93dbb2da738ab4e8959ffa50cd087cdfa889f3a1b8acdd62552f7c1d070100020366c2f508c9c555cacc9fb26d88e88dd54e210bb5a8bce5687f60d7e75c4cd07fc68b3c894c782b05a9c27fc6c66eb14d4e7d31de9086ab7d2129bcb0493afa020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001020200010c020000002a00000000000000');
    });

});
