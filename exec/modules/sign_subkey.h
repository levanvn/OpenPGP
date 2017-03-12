/*
sign_key.h
OpenPGP exectuable module

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __COMMAND_SIGN_SUBKEY__
#define __COMMAND_SIGN_SUBKEY__

#include "../../OpenPGP.h"
#include "module.h"

namespace module {

const Module sign_subkey(
    // name
    "sign-subkey",

    // positional arguments
    {
        "signer-key",
        "passphrase",
        "signee-key",
    },

    // optional arguments
    {
        std::make_pair("-o", std::make_pair("output file",                                        "")),
        std::make_pair("-c", std::make_pair("certification level (0x10 - 0x13 without '0x')",   "13")),
        std::make_pair("-h", std::make_pair("hash algorithm",                                 "SHA1")),
        std::make_pair("-u", std::make_pair("Signer's User Identifier",                           "")),
        std::make_pair("-v", std::make_pair("Signee's User Identifier",                           "")),
    },

    // optional flags
    {
        std::make_pair("-a", "armored"),
    },

    // function to run
    [](const std::map <std::string, std::string> & args,
       const std::map <std::string, bool>        & flags) -> int {
        std::ifstream signer_file(args.at("signer-key"), std::ios::binary);
        if (!signer_file){
            std::cerr << "IOError: File \"" + args.at("signer-key") + "\" not opened." << std::endl;
            return -1;
        }

        std::ifstream signee_file(args.at("signee-key"), std::ios::binary);
        if (!signee_file){
            std::cerr << "IOError: File \"" + args.at("signee-key") + "\" not opened." << std::endl;
            return -1;
        }

        if (Hash::NUMBER.find(args.at("-h")) == Hash::NUMBER.end()){
            std::cerr << "Error: Bad Hash Algorithm: " << args.at("-n") << std::endl;
            return -1;
        }

        const SignArgs signargs(PGPSecretKey(signer_file),
                                args.at("passphrase"),
                                4,
                                Hash::NUMBER.at(args.at("-h")));

        // std::string error;
        // PGPPublicKey key = ::sign_subkey(signargs, PGPPublicKey(signee_file), mpitoulong(hextompi(args.at("-c"))), error);

        // if (key.meaningful()){
            // output(key.write(flags.at("-a")?PGP::Armored::YES:PGP::Armored::NO), args.at("-o"));
        // }
        // else{
            // std::cerr << error << std::endl;
        // }

        return 0;
    }
);

}

#endif