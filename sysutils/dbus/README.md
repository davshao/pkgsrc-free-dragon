DBUS
====

Necessity
---------

Optional since it appears security/policykit is sufficient to start
the Xfce4 desktop using startx and exec startxfce4 in .xinitrc.

Usage
-----

1. To be able to set the pid file name, apply mk/defaults/mk.conf.diff
2. Set the following in etc/mk.conf, for example:
* DBUS_USER=mydbus
* DBUS_GROUP=mydbus
* DBUS_SYSTEM_PID_FILE=dbus.pid
3. After installing, copy /usr/pkg/examples/share/rc.d/dbus to etc/rc.d
4. Set in rc.conf
* dbus_enable=YES

PR/50075 edited
---------------

I have found the following patches to be helpful for getting dbus to
work on DragonFly, FreeBSD, and possibly other OSes.
The functionality has been verified on DragonFly 4.3 DEVELOPMENT
and FreeBSD 10.1 release. 

That being said I acknowledge it is possible I have made an error
and broken working dbus on Darwin or in the smf code.

### mk/defaults/mk.conf.

1. The pid file for dbus in /var/run/dbus can have different names,
anything from messagebus.pid to dbus.pid on DragonFly and FreeBSD
to the default name of pid. 
DBUS_SYSTEM_PID_FILE allows the installer to customize this pid file name.

2. The new mk.conf also notes that in practice DBUS_USER and DBUS_GROUP
are the same value.

The script dbus that starts the dbus daemon is generated using FILE_SUBST
from files/dbus.sh and from smf/files/dbus.sh. 

3. For newer DragonFly and FreeBSD the rcvar name used to invoke dbus in
/etc/rc.conf has incorrect default of dbus, whereas it should be dbus_enable.
Therefore @DBUS_RCVAR@ is introduced to pass the correct name.  

4. The pid file name is passed through @DBUS_SYSTEM_PID_FILE_SH@.
I did not want to use FILE_SUBST directly on variables such as
DBUS_SYSTEM_PID_FILE because the source code for dbus seems to
originally have its own @DBUS_USER@ patterns.
Thus the _SH extension for DBUS_SYSTEM_PID_FILE_SH.

5. The original dbus.sh neither removes the pid file when dbus is
stopped nor checks if a stale one exists before it starts.
I added a check for both, including adding a dbus_poststop() command
similar to the one that DragonFly dports uses.

6. Older dbus install advise sometimes recommended the /var/run/dbus
directory to have ownership ${DBUS_USER}:${DBUS_GROUP}.  That is no longer
the case for current dbus that happily accepts defaults from /var/run
such as root:root or root:wheel on newer Linux, DragonFly, or FreeBSD.
I therefore commented out the code setting ownership and permissions for
/var/run/dbus but at least left it behind as a hint.

7. The code now checks for the existence of both /var/run/dbus
and /var/db/dbus and creates them if they do not exist. 

8. I added the _SH extension to the FILE_SUBST variables
in files/smf/dbus.sh for the new line:
@CHOWN@ @DBUS_USER_SH@:@DBUS_GROUP_SH@ $dir

### sysutils/dbus/Makefile

9. I added DBUS_USER, DBUS_GROUP, and DBUS_SYSTEM_PID_FILE
to BUILD_DEFS to at least give installers a hint what to set
in their etc/mk.conf if they want other than the defaults.
And as mentioned above, I changed the FILE_SUBST to variables
with a _SH extension so that there was no chance of a clash
with source code patterns of the same form.

10. I commented out the setting of a home directory for the DBUS_USER
as it is nonexistent on newer systems.
I also added a call to create DBUS_USER and DBUS_GROUP before configure,
but that may not have been necessary.

11. I got rid of a construct playing with CONFIGURE_ARGS.var
that grepping seemed to indicate exists nowhere else in pkgsrc.
Instead I rewrote everything to the usual format of
CONFIGURE_ARGS+=

### options.mk.

12. I added the option enable_in_rcvar so that dbus_enable
could be set as the correct rcvar in dbus.sh.  It is the suggested
option for newer DragonFly and FreeBSD, yet the flexibility is
there to choose otherwise for older versions.

13. I again removed the unique CONFIGURE_ARGS.var constructs. 
