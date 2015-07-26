$NetBSD$

--- src/intel_device.c.orig	2015-07-23 00:34:18.755727000 +0000
+++ src/intel_device.c
@@ -398,8 +398,13 @@ static int __intel_open_device__legacy(c
 		 pci->domain, pci->bus, pci->dev, pci->func);
 
 	ret = drmCheckModesettingSupported(id);
+#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
+	if (ret || 1) {
+		if (xf86LoadKernelModule("i915kms"))
+#else
 	if (ret) {
 		if (xf86LoadKernelModule("i915"))
+#endif
 			ret = drmCheckModesettingSupported(id);
 		if (ret)
 			return -1;
