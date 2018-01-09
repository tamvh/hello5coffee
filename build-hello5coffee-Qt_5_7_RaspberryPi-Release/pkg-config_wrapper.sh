#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/opt/build/qt5pi/sysroot
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/opt/build/qt5pi/sysroot/usr/lib/pkgconfig:/opt/build/qt5pi/sysroot/usr/share/pkgconfig:/opt/build/qt5pi/sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
