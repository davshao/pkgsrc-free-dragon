firefox and firefox38
=====================

Necessity
---------

This is only useful for DragonFly and has only been tested for
DragonFly 4.3-DEVELOPMENT.

Usage
-----

If it is desired to turn off --enable-shared-js, this is
automatically done for DragonFly and can be done through
    PKG_OPTIONS.firefox= -shared-js

PR/50089
--------

Neither www/firefox nor www/firefox38 build on DragonFly 4.3-DEVELOPMENT with

    CONFIGURE_ARGS+= --enable-shared-js

Similar apparently to DragonFly dports, both successfully build
on Dragonfly 4.3 when the above line in mozilla-common.mk is commented out.
Unfortunately the PLIST also needs to be modified to omit the now
non-built shared library libmozjs.so.

1. The following set of patches adds a new option shared-js for firefox,
and by extension firefox38, that would be suggested by default
for every OS other than DragonFly.

2. I move to options.mk
        CONFIGURE_ARGS+= --enable-shared-js

3. I add to options.mk, so that the non-built shared libarry can be omitted,
    PLIST_VAR libmozjs.

This problem is apparently
[not unknown on other platforms](https://bugzilla.mozilla.org/show_bug.cgi?id=1112945)

