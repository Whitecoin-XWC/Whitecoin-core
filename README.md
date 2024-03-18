<p align="center">
  <img alt="logo" src="assets/logo.png" height="128" />
  <h3 align="center"><a href="https://">WhiteCoin</a></h3>
  <p align="center">Command line toolchain for <a href=https:/>WhiteCoin blockchain</a>.</p>
  <p align="center">
    <a href="https://gitter.im/"><img alt="Join the chat at https://gitter.im/" src="https://img.shields.io/gitter/room/badges/shields.svg?style=flat-square"></a>
    <a href="https://circleci.com/gh/"><img alt="CircleCI" src="https://img.shields.io/circleci/project/github/master.svg?style=flat-square"></a>
    <a href="https://travis-ci.org/"><img alt="Travis" src="https://img.shields.io/travis/"></a>
    <a href="https://ci.appveyor.com/project"><img alt="AppVeyor" src="https://img.shields.io/appveyor/ci/"></a>
    <a href="https://codecov.io/gh"><img alt="Coverage Status" src="https://img.shields.io/codecov/c/"></a>
    <a href="https://github.com/"><img alt="Release" src="https://img.shields.io/github/release/e"></a>
    <a href="http://godoc.org/github.com/"><img alt="Go Doc" src="https://img.shields.io/badge/godoc-reference-blue.svg?style=flat-square"></a>
    <a href="LICENSE"><img alt="Software License" src="https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat-square"></a>
  </p>
</p>


## Licence

[MIT](LICENSE)

## Whitecoin-core

[Whitecoin](https://whitecoin.info/) is first to adopt Multi Tunnel Blockchain Communication Protocol (MTBCP), making the inter-blockchain communication protocol a reality.



## How to compile

#### ubuntu-18.04

Compile the whitecoin-xwc at ubuntu-18.04, please refer blow command line:

* update your compile machine

  ```shell
  $> sudo apt-get -f install
  $> sudo apt-get update
  ```

* install some required library

  ```shell
  $> sudo apt-get install cmake make libbz2-dev libdb++-dev libdb-dev libssl-dev openssl autoconf libtool
  $> sudo apt-get install libreadline-dev --fix-missing
  $> sudo apt-get install g++
  ```

* build whitecoin-xwc now

  ```shell
  $> git clone --recursive git@github.com:Whitecoin-XWC/Whitecoin-core.git
  $> cd Whitecoin-core
  $> git checkout master
  $> chmod +x build.sh
  $> ./build.sh
  
  #Please wait the compile....
  ```

* executable file `xwc_cli & xwc_node`

  > If the compile is success, you can found the executable files `xwc_cli & xwc_node` under the folder output.



# Object

This is a special blockchain network which aims to link all valued blockchain network together. Crypto-currencies can be exchanged / transfered within Whitecoin network.


