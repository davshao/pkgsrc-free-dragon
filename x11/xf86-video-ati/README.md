xf86-video-ati
==============

Necessity
---------

This patch is fairly essential for relatively recent Radeon graphics cards
on newer FreeBSD and DragonFly, unless one wants to figure out how to
pre-load the **radeonkms.ko** kernel module before starting Xorg.

PR/50067, edited
----------------

The following patch is from DragonFly dports master as of
commit 4f04bfe0ea83ce09 ..., 
file `x11-drivers/xf86-video-ati/files/patch-src__radeon_kms.c`

It has been tested on DragonFly 4.3-DEVELOPMENT,
FreeBSD 10.1 release amd64, and FreeBSD 10.2 beta2 using openbox
and Xfce4 and a patched xf86-input-mouse.  It also at least
compiled and built successfully on NetBSD 6.99.20 amd64 `X11_type=modular`,
and should have no affect on it.

Here is output from a resulting **/var/log/Xorg.0.log**
    [    45.299] (II) [KMS] Kernel modesetting enabled.
...
    [    45.318] (--) RADEON(0): Chipset: "ATI Radeon HD 4550" (ChipID = 0x9540)
    [    47.470] (II) Loading sub module "dri2"
...
    [    47.493] (II) RADEON(0): KMS Color Tiling: enabled
    [    47.493] (II) RADEON(0): KMS Color Tiling 2D: enabled
    [    47.493] (II) RADEON(0): KMS Pageflipping: enabled
...
    [    47.693] (II) RADEON(0): [DRI2] Setup complete
    [    47.693] (II) RADEON(0): [DRI2]   DRI driver: r600
    [    47.693] (II) RADEON(0): [DRI2]   VDPAU driver: r600
...
    [    47.712] (II) EXA(0): Driver allocated offscreen pixmaps
    [    47.712] (II) EXA(0): Driver registered support for the following operations:
...
    [    47.712] (II) RADEON(0): Acceleration enabled
    [    47.712] (==) RADEON(0): DPMS enabled
...
    [    48.090] (II) AIGLX: enabled GLX_MESA_copy_sub_buffer
    [    48.090] (II) AIGLX: enabled GLX_ARB_create_context
    [    48.090] (II) AIGLX: enabled GLX_ARB_create_context_profile
    [    48.090] (II) AIGLX: enabled GLX_EXT_create_context_es2_profile
    [    48.090] (II) AIGLX: enabled GLX_INTEL_swap_event
    [    48.090] (II) AIGLX: enabled GLX_SGI_swap_control and GLX_MESA_swap_control
    [    48.090] (II) AIGLX: enabled GLX_EXT_framebuffer_sRGB
    [    48.090] (II) AIGLX: enabled GLX_ARB_fbconfig_float
    [    48.090] (II) AIGLX: GLX_EXT_texture_from_pixmap backed by buffer objects
    [    48.092] (II) AIGLX: Loaded and initialized r600
    [    48.092] (II) GLX: Initialized DRI2 GL provider for screen 0
