#!/bin/bash
#set -x

#check the required folder deps
if [ ! -d deps ]; 
then
    echo 'Please make sure the directory [deps] is exist'
    exit 0
fi

#unzip the required libraries
cd deps
if [ ! -d boost_1_63_0 ];
then
    tar -zxvf boost_1_63_0.tar.gz
fi

if [ ! -d blocklink_crosschain_privatekey ];
then
    tar -zxvf blocklink_crosschain_privatekey.tar.gz
fi

if [ ! -d eth_crosschain_privatekey ];
then
    tar -zxvf eth_crosschain_privatekey.tar.gz
fi
cd ..

#export some required environment
export BOOST_ROOT=`pwd`/deps/boost_1_63_0
export ETH_CROSSCHAIN_PROJECT=`pwd`/deps/eth_crosschain_privatekey
export CROSSCHAIN_PRIVATEKEY_PROJECT=`pwd`/deps/blocklink_crosschain_privatekey
export PATH=$BOOST_ROOT:$ETH_CROSSCHAIN_PROJECT:$CROSSCHAIN_PRIVATEKEY_PROJECT:$PATH

#compile whitecoin source code now
chmod +x libraries/fc/vendor/secp256k1-zkp/autogen.sh
cmake -DCMAKE_BUILD_TYPE=Release .
make

#check the compile is complete
rm -rf output/*
if [ ! -f programs/cli_wallet/cli_wallet ];
then
    echo 'Compile the xwc_cli is failed, please contract the developer or whitecoin'
    exit 0
fi

if [ ! -f programs/witness_node/witness_node ];
then
    echo 'Compile the xwc_node is failed, please contract the developer or whitecoin'
    exit 0
fi

cp programs/cli_wallet/cli_wallet output/xwc_cli
cp programs/witness_node/witness_node output/xwc_node
echo '#################################################################'
echo '#Success Pelease get the executable file from directory: output  '
echo '#################################################################'
