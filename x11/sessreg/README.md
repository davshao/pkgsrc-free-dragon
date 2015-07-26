sessreg
=======

Necessity
---------

This patch is only required for DragonFly with gcc5+ as its
base compiler.

PR/50083, edited
----------------

Due to DragonFly 4.3-DEVELOPMENT now using the gcc 5.x series
as the base compiler:

`$ gcc --version
gcc 5.2.1 [DragonFly] Release/2015-07-18`

x11/sessreg needs a patch to Makefile.
The DragonFly dports version of the patch is

    CPP+=  -P

That didn't seem to work for pkgsrc, so I converted it to the
following patch that does work.  Without the patch on
DragonFly 4.3 one gets an error such as:

`/usr/pkg/bin/bmake  all-recursive
Making all in man
  GEN      filenames.sed
  GEN      sessreg.1
sed: 3: filenames.sed: unescaped newline inside substitute pattern`

Here is an example link
[explaining the problem](http://www.linuxfromscratch.org/blfs/view/svn/x/x7app.html)

As was suggested on the pkgsrc-bugs mailing list, it is possibly
preferable to use **tradcpp**, but I can't test that option on
other platforms.
