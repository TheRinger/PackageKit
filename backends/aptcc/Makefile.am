AM_CPPFLAGS = \
	-DDATADIR=\"$(datadir)\"		\
	-DG_LOG_DOMAIN=\"PackageKit-APTcc\"

plugindir = $(PK_PLUGIN_DIR)
plugin_LTLIBRARIES = libpk_backend_aptcc.la
libpk_backend_aptcc_la_SOURCES = pkg-list.cpp \
				 acqpkitstatus.cpp \
				 gst-matcher.cpp \
				 apt-messages.cpp \
				 apt-utils.cpp \
				 apt-sourceslist.cpp \
				 apt-cache-file.cpp \
				 apt-intf.cpp \
				 deb-file.cpp \
				 pk-backend-aptcc.cpp
libpk_backend_aptcc_la_LIBADD = -lcrypt \
				-lapt-pkg \
				-lapt-inst \
				-lutil \
				$(PK_PLUGIN_LIBS)
libpk_backend_aptcc_la_LDFLAGS = -module \
				-avoid-version \
				$(APTCC_LIBS) \
				$(APPSTREAM_LIBS) \
				$(GSTREAMER_LIBS)
libpk_backend_aptcc_la_CFLAGS = $(PK_PLUGIN_CFLAGS) \
				$(AM_CPPFLAGS) \
				$(APPSTREAM_CFLAGS)
libpk_backend_aptcc_la_CPPFLAGS = $(PK_PLUGIN_CFLAGS) \
				  $(APTCC_CFLAGS) \
				  $(APPSTREAM_CFLAGS) \
				  $(GSTREAMER_CFLAGS) \
				  $(AM_CPPFLAGS)

aptconfdir = ${SYSCONFDIR}/apt/apt.conf.d
aptconf_DATA = 20packagekit

EXTRA_DIST = 20packagekit \
	     get-distro-upgrade.py \
	     pkg-list.h \
	     apt-intf.h \
	     apt-utils.h \
	     apt-sourceslist.h \
	     apt-messages.h \
	     apt-cache-file.h \
	     gst-matcher.h \
	     deb-file.h \
	     acqpkitstatus.h

helperdir = $(datadir)/PackageKit/helpers/aptcc
dist_helper_DATA =					\
	pkconffile					\
	pkconffile.nodiff				\
	$(NULL)

install-data-hook:
	chmod +x $(DESTDIR)$(helperdir)/pkconffile

clean-local :
	rm -f *~
	rm -f *.pyc

-include $(top_srcdir)/git.mk
