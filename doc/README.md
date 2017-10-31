EACoin Core 0.12.1
=====================

Setup
---------------------
[EACoin Core](https://eacoin.org) is the original EACoin client and it builds the backbone of the network. However, it downloads and stores the entire history of EACoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run EACoin on your native platform.

### Unix

You need the Qt4 run-time libraries to run EACoin-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/eacoin-qt (GUI, 32-bit) or bin/32/eacoind (headless, 32-bit)
- bin/64/eacoin-qt (GUI, 64-bit) or bin/64/eacoind (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run eacoin-qt.exe.

### OS X

Drag EACoin-Core to your applications folder, and then run EACoin-Core.

### Need Help?

* See the documentation at the [EACoin Wiki](https://eacoin.io)
for help and more information.
* Ask for help on [#eacoin](#) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=eacoin).
* Ask for help on the [EACoin in BitcoinTalk](https://bitcointalk.org/index.php?topic=2288072) forums, in the [Technical Support board](https://bitcointalk.org/index.php?topic=2288072).

Building
---------------------
The following are developer notes on how to build EACoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The EACoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](#)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [EACoin in BitcoinTalk](https://bitcointalk.org/index.php?topic=2288072) forums, in the [Development & Technical Discussion board](https://bitcointalk.org/index.php?topic=2288072).
* Discuss project-specific development on #eacoin-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=eacoin-core-dev).
* Discuss general EACoin development on #eacoin-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=eacoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
