#!/bin/bash
#set -x

#check the required folder deps
if [ ! -d deps ]; 
then
    echo 'Please make sure the directory [deps] is exist'
    exit 0
fi


#########################################################################################################################
#check and comiple boost library
cd deps
if [ ! -d boost_1_63_0 ];
then
    if [ ! -f boost_1_63_0.tar.gz ]; 
    then
        wget -c https://boostorg.jfrog.io/artifactory/main/release/1.63.0/source/boost_1_63_0.tar.gz -O boost_1_63_0.tar.gz
    fi
    
    if [ ! -f boost_1_63_0.tar.gz ]; 
    then
        echo "can't found boost_1_63_0.tar.gz"
        exit 0
    fi
    
    tar -zxvf boost_1_63_0.tar.gz
    cd boost_1_63_0
    ./bootstrap.sh --prefix=`pwd`
    ./b2 install link=static
    rm -rf bin.v2
    cd ..
fi

export BOOST_ROOT=`pwd`/boost_1_63_0
export PATH=$BOOST_ROOT:$PATH

#########################################################################################################################
#check and compile the blocklink_crosschain_privatekey library
if [ ! -d blocklink_crosschain_privatekey ];
then
    if [ ! -f blocklink_crosschain_privatekey.tar.gz ]; 
    then
        echo "can't found blocklink_crosschain_privatekey.tar.gz"
        exit 0
    fi
    
    tar -zxvf blocklink_crosschain_privatekey.tar.gz
    cd blocklink_crosschain_privatekey
    cmake -DBOOST_ROOT=`pwd`/../boost_1_63_0 .
    make -j 4
    cd ..
fi

export CROSSCHAIN_PRIVATEKEY_PROJECT=`pwd`/blocklink_crosschain_privatekey
if [ ! -f ${CROSSCHAIN_PRIVATEKEY_PROJECT}/libblocklink_libbitcoin.a ];
then
    echo "The libblocklink_libbitcoin.a is not exist"
    exit 0
fi
export PATH=$CROSSCHAIN_PRIVATEKEY_PROJECT:$PATH

#########################################################################################################################
#check and compile the eth_crosschain_privatekey library
if [ ! -d eth_crosschain_privatekey ];
then
    if [ ! -f eth_crosschain_privatekey.tar.gz ]; 
    then
        echo "can't found eth_crosschain_privatekey.tar.gz"
        exit 0
    fi
    
    tar -zxvf eth_crosschain_privatekey.tar.gz
    cd eth_crosschain_privatekey/eth_sign
    cmake -DBOOST_ROOT=`pwd`/../../boost_1_63_0 .
    make -j 4
    
    cd cryptopp
    make -j 4
    cd ../../../
fi

export ETH_CROSSCHAIN_PROJECT=`pwd`/eth_crosschain_privatekey
if [ ! -f ${ETH_CROSSCHAIN_PROJECT}/eth_sign/libeth_sign.a ]; 
then
    echo "The libeth_sign.a is not exist"
    exit 0
fi
export PATH=$ETH_CROSSCHAIN_PROJECT:$PATH
cd ..
exit 0

#########################################################################################################################
#compile whitecoin source code now
chmod +x libraries/fc/vendor/secp256k1-zkp/autogen.sh
cmake -DCMAKE_BUILD_TYPE=Release .
make -j 20

#########################################################################################################################
#check the compile is complete
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

#copy files
rm -rf output
mkdir output

cp programs/cli_wallet/cli_wallet output/xwc_cli
strip output/xwc_cli

cp programs/witness_node/witness_node output/xwc_node
strip output/xwc_node
echo '#################################################################'
echo '#Success Pelease get the executable file from directory: output  '
echo '#################################################################'
