SUBDIRS=$(LIBMOWGLI) include modules src
CLEANDIRS = ${SUBDIRS}
DISTCLEAN = extra.mk buildsys.mk config.log config.status valkyrie-ircd.pc

-include extra.mk
-include buildsys.mk

# explicit dependencies need to be expressed to ensure parallel builds don't die
modules: include $(LIBMOWGLI)
src: include $(LIBMOWGLI)

install-extra:
	@echo "----------------------------------------------------------------"
	@echo ">>> Remember to cd to ${prefix} and edit your config file.";
	@echo "----------------------------------------------------------------"

dist:
	@if [ ! -d .hg ]; then \
		echo "make dist only works from a mercurial tree"; \
		false; \
	fi
	hg parent --template '#define SERNO "{rev}:{node|short}"\n' >include/serno.h
	@echo "Creating $(DISTNAME).tar.gz"
	$(RM) -f $(DISTNAME)
	$(LN) -s . $(DISTNAME)
	hg manifest | awk '{ print "$(DISTNAME)/"$$1; } END { print "$(DISTNAME)/configure"; print "$(DISTNAME)/aclocal.m4"; print "$(DISTNAME)/include/sysconf.h.in"; print "$(DISTNAME)/include/serno.h"; }' | $(TAR) -chnzf $(DISTNAME).tar.gz -T /dev/stdin
	$(RM) $(DISTNAME)

buildsys.mk:
	@echo "Run ./configure first you idiot."
	@exit 1
