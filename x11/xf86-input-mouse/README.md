xf86-input-mouse
===============

Necessity
---------

I find this useful for USB mice.

DragonFly for now has a workaround if one enables moused
from /etc/rc.conf, but I have not figured out how to do the
same from FreeBSD.

Usage
-----

The default for DragonFly in etc/mk.conf is
    PKG_OPTIONS.xf86-input-mouse = dflyu4b
and for FreeBSD 
    PKG_OPTIONS.xf86-input-mouse = fbsdusb

For an older DragonFly before the u4b USB stack from FreeBSD
was ported, one can try, but I have not verified,
    PKG_OPTIONS.xf86-input-mouse = dflyusb

PR/50068, edited
----------------

Patches from DragonFly dports to x11/xf86-input-mouse are needed
for DragonFly and FreeBSD to use a USB mouse in newer Xorg.
(There is a workaround for DragonFly using moused called
from /etc/rc.conf, but I can't get that workaround to succeed
on FreeBSD 10.1.  Also the DragonFly rc.conf invocation of moused
has been unreliable for me for use with pkgsrc in the past.)

There are some complications.  A new options.mk file seems
to require 3 new options just to distinguish between three possible
include paths for the usb header file depending on the OS.
(This problem applies to other ports.  It is fortunate
that sysutils/hal is being phased out.)  Unfortunately older DragonFly,
newer DragonFly, and FreeBSD have three different possible paths.
Also one of the patches is gigantic.  Apart from trying to understand such
a large patch, it is quite possible I have made mistakes merging the
patch from dports.

I have tried to enclose all of the new code in ifdefs on symbol
    FREEBSD_USB, and supplanted code in !defined(FREEBSD_USB) blocks.
The functionality should be completely unaffected on non-DragonFly
and non-FreeBSD platforms.

The patch itself ask why some of the logic for detecting OS
and OS version isn't performed by patching configure scripts.
