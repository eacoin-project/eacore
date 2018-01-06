
Debian
====================
This directory contains files used to package eacoind/eacoin-qt
for Debian-based Linux systems. If you compile eacoind/eacoin-qt yourself, there are some useful files here.

## eacoin: URI support ##


eacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install eacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your eacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/eacoin128.png` to `/usr/share/pixmaps`

eacoin-qt.protocol (KDE)

