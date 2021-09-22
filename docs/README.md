### Building
**BitShares requires an [OpenSSL](https://www.openssl.org/) version in the 1.0.x series. OpenSSL 1.1.0 and newer are NOT supported. If your system OpenSSL version is newer, then you will need to manually provide an older version of OpenSSL and specify it to CMake using `-DOPENSSL_INCLUDE_DIR`, `-DOPENSSL_SSL_LIBRARY`, and `-DOPENSSL_CRYPTO_LIBRARY`. Example:**
  
```
cmake -DOPENSSL_INCLUDE_DIR=/usr/include/openssl-1.0 -DOPENSSL_SSL_LIBRARY=/usr/lib/openssl-1.0/libssl.so -DOPENSSL_CRYPTO_LIBRARY=/usr/lib/openssl-1.0/libcrypto.so .
```

**BitShares requires a [Boost](http://www.boost.org/) version in the range [1.57, 1.60]. Versions earlier than 1.57 or newer than 1.60 are NOT supported. If your system Boost version is newer, then you will need to manually build an older version of Boost and specify it to CMake using `-DBOOST_ROOT`. Example:**

```
cmake -DBOOST_ROOT=~/boost160 .
```

* [Ubuntu Linux](build/BUILD_UBUNTU)
* [OS X](build/Building-on-OS-X)
* [Windows](build/BUILD_WIN32)
* [Web and light wallets](build/Web-and-light-wallets-release-procedure)

### Architecture
* [Blockchain Objects](dev/Blockchain-Objects)
* [Wallet / Full Nodes / Witness Nodes](wallet/Wallet_Full-Nodes_Witness-Nodes)
* [Stealth Transfers](dev/StealthTransfers)

### Wallet
* [CLI Wallet Cookbook](wallet/CLI-Wallet-Cookbook)
* [Wallet Login Protocol](wallet/Wallet_Login_Protocol)
* [Wallet Merchant Protocol](wallet/Wallet_Merchant_Protocol)
* [Wallet Argument Format](Wallet Argument Format)
* [Wallet 2-Factor Authentication Protocol](Wallet 2-Factor Authentication Protocol)

### Contributing
* [General API](API)
* [Websocket Subscriptions](Websocket Subscriptions)
* [Testing](Testing)

### Exchanges
* [Monitoring Accounts](Monitoring accounts)

### Witnesses
* [How to become an active witness in BitShares 2.0](How to become an active witness in BitShares 2.0)
* [How to setup your witness for test net (Ubuntu 14.04)](How to setup your witness for test net (Ubuntu 14.04))