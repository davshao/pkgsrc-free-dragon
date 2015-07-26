$NetBSD$

--- src/radeon_kms.c.orig	2014-10-02 03:31:27.000000000 +0000
+++ src/radeon_kms.c
@@ -30,6 +30,12 @@
 
 #include <errno.h>
 #include <sys/ioctl.h>
+
+#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
+#include <sys/param.h>
+#include <sys/linker.h>
+#endif
+
 /* Driver data structures */
 #include "radeon.h"
 #include "radeon_reg.h"
@@ -280,7 +286,7 @@ static void
 radeon_dirty_update(ScreenPtr screen)
 {
 	RegionPtr region;
-	PixmapDirtyUpdatePtr ent;
+	PixmapDirtyUpdatePtr ent = NULL;
 
 	if (xorg_list_is_empty(&screen->pixmap_dirty_list))
 		return;
@@ -589,7 +595,11 @@ static int radeon_get_drm_master_fd(Scrn
 #endif
     struct pci_device *dev = info->PciInfo;
     char *busid;
+#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
+    int fd, err;
+#else
     int fd;
+#endif
 
 #ifdef XF86_PDEV_SERVER_FD
     if (pRADEONEnt->platform_dev) {
@@ -608,6 +618,17 @@ static int radeon_get_drm_master_fd(Scrn
 		      dev->domain, dev->bus, dev->dev, dev->func);
 #endif
 
+#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
+    err = kldload("radeonkms");
+    if (err == -1 && errno != EEXIST) {
+        xf86DrvMsg(pScrn->scrnIndex, X_ERROR,
+        	"[drm] Failed to load kernel module for %s: %s\n",
+        	busid, strerror(errno));
+        free(busid);
+        return -1;
+    }
+#endif
+
     fd = drmOpen(NULL, busid);
     if (fd == -1)
 	xf86DrvMsg(pScrn->scrnIndex, X_ERROR,
