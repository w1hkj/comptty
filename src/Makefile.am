# Copyright (c) 2013 Dave Freese, W1HKJ (w1hkj AT w1hkj DOT com)

bin_PROGRAMS = comptty

comptty_cxxFLAGS = @comptty_BUILD_cxxFLAGS@
comptty_CXXFLAGS = @comptty_BUILD_CXXFLAGS@
comptty_CFLAGS = $(comptty_CXXFLAGS)
comptty_LDFLAGS = @comptty_BUILD_LDFLAGS@
comptty_LDADD = @comptty_BUILD_LDADD@

MINGW32_SRC = \
	comptty.rc \
	include/compttyrc.h

# We distribute these but do not always compile them
EXTRA_comptty_SOURCES = $(comptty_WIN32_RES_SRC) $(MINGW32_SRC)

comptty_SOURCES =

if MINGW32
if HAVE_WINDRES
  comptty_SOURCES += $(MINGW32_SRC)
endif
endif

########################################################################


comptty_VERSION_MAJOR = @comptty_VERSION_MAJOR@
comptty_VERSION_MINOR = @comptty_VERSION_MINOR@
comptty_VERSION_PATCH = @comptty_VERSION_PATCH@
comptty_VERSION = @comptty_VERSION@

.EXPORT_ALL_VARIABLES: nsisinst appbundle

# Sources that are generated,
BUILT_SOURCES =
# not distributed,
nodist_comptty_SOURCES = $(BUILT_SOURCES)
# and deleted by the clean targets
CLEANFILES = $(BUILT_SOURCES)
CLEAN_LOCAL =

if MINGW32
if HAVE_WINDRES
.rc.o:
	$(WINDRES) -I$(srcdir)/include -I$(srcdir)/../data/win32 $< -O coff $@
endif
endif

install-data-local:
	if test -f $(srcdir)/../data/comptty.xpm; then \
	    $(mkinstalldirs) $(DESTDIR)/$(datadir)/pixmaps; \
	    $(INSTALL_DATA) $(srcdir)/../data/comptty.xpm $(DESTDIR)/$(datadir)/pixmaps; \
	fi
	if test -f $(srcdir)/../data/comptty.desktop; then \
	    $(mkinstalldirs) $(DESTDIR)/$(datadir)/applications; \
	    $(INSTALL_DATA) $(srcdir)/../data/comptty.desktop $(DESTDIR)/$(datadir)/applications; \
	fi

uninstall-local:
	rm -f $(DESTDIR)/$(datadir)/pixmaps/comptty.xpm
	rm -f $(DESTDIR)/$(datadir)/applications/comptty.desktop

FL_SRC = comp_ui.fl

if HAVE_FLUID
flgen: $(FL_SRC)
	(cd $(srcdir)/include; \
	for f in $(FL_SRC); do \
	    c=$${f%.fl}.cxx; \
		h=$${f%.fl}.h; \
		h=$${h##*/}; \
	    $(FLUID) -c -o ../$$c -h $$h ../$$f; \
	done)
endif


INSTALLER_FILE = comptty-$(comptty_VERSION)_setup.exe
APPBUNDLE=comptty-$(comptty_VERSION)
APPBUNDLE_NOLIBS=$(APPBUNDLE)-nolibs

if HAVE_NSIS
nsisinst: $(bin_PROGRAMS)
	sh $(srcdir)/../scripts/mknsisinst.sh "$(srcdir)/../data" .
    CLEANFILES += $(INSTALLER_FILE)
endif

if DARWIN
appbundle: $(bin_PROGRAMS)
	sh $(srcdir)/../scripts/mkappbundle.sh "$(srcdir)/../data" .
    CLEAN_LOCAL += $(APPBUNDLE_NOLIBS) $(APPBUNDLE) $(APPBUNDLE)*.dmg
endif

clean-local:
	-rm -rf $(CLEAN_LOCAL)

# Sources that we build. It is OK to have headers here.
comptty_SOURCES += \
	main.cxx \
	comp_tty.cxx \
	comp_ui.cxx \
	include/comp_tty.h  \
	include/comp_ui.h

# Additional source files that are distributed
EXTRA_DIST = \
	comptty.rc \
	comp_ui.fl \
	comptty_icon.cxx \
	include/compttyrc.h

# Additional non-source files that are distributed
# Additional source files that support non-Linux cross compilation
EXTRA_DIST += \
	$(srcdir)/../data/comptty.desktop \
	$(srcdir)/../data/comptty.xpm \
	$(srcdir)/../data/win32/fl_app.nsi \
	$(srcdir)/../data/win32/comptty.ico \
	$(srcdir)/../scripts/mknsisinst.sh \
	$(srcdir)/../scripts/build4mingw.sh \
	$(srcdir)/../data/mac/Info.plist.in \
	$(srcdir)/../data/mac/comptty.icns \
	$(srcdir)/../scripts/mkappbundle.sh \
	$(comptty_WIN32_SRC) \
	$(comptty_FL_SRC)
