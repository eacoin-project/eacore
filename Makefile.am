ACLOCAL_AMFLAGS = -I build-aux/m4
SUBDIRS = src
.PHONY: deploy FORCE

GZIP_ENV="-9n"

if BUILD_EACOIN_LIBS
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libeacoinconsensus.pc
endif

EACOIND_BIN=$(top_builddir)/src/eacoind$(EXEEXT)
EACOIN_QT_BIN=$(top_builddir)/src/qt/eacoin-qt$(EXEEXT)
EACOIN_CLI_BIN=$(top_builddir)/src/eacoin-cli$(EXEEXT)
WALLET_UTILITY_BIN=$(top_builddir)/src/wallet-utility$(EXEEXT)
EACOIN_WIN_INSTALLER=$(PACKAGE)-$(PACKAGE_VERSION)-win$(WINDOWS_BITS)-setup$(EXEEXT)

OSX_APP=EACoin-Qt.app
OSX_DMG=EACoin-Core.dmg
OSX_BACKGROUND_IMAGE=background.tiff
OSX_DEPLOY_SCRIPT=$(top_srcdir)/contrib/macdeploy/macdeployqtplus
OSX_FANCY_PLIST=$(top_srcdir)/contrib/macdeploy/fancy.plist
OSX_BASE_LPROJ_DIR=$(top_srcdir)/contrib/macdeploy/Base.lproj/InfoPlist.strings
OSX_INSTALLER_ICONS=$(top_srcdir)/src/qt/res/icons/eacoin.icns
OSX_PLIST=$(top_srcdir)/share/qt/Info.plist #not installed
OSX_QT_TRANSLATIONS = da,de,es,hu,ru,uk,zh_CN,zh_TW

DIST_DOCS = $(wildcard doc/*.md) $(wildcard doc/release-notes/*.md)

BIN_CHECKS=$(top_srcdir)/contrib/devtools/symbol-check.py \
           $(top_srcdir)/contrib/devtools/security-check.py

WINDOWS_PACKAGING = $(top_srcdir)/share/pixmaps/eacoin.ico \
  $(top_srcdir)/share/pixmaps/nsis-header.bmp \
  $(top_srcdir)/share/pixmaps/nsis-wizard.bmp \
  $(top_srcdir)/doc/README_windows.txt

OSX_PACKAGING = $(OSX_DEPLOY_SCRIPT) $(OSX_FANCY_PLIST) $(OSX_INSTALLER_ICONS) $(OSX_BASE_LPROJ_DIR) \
  $(top_srcdir)/contrib/macdeploy/$(OSX_BACKGROUND_IMAGE) \
  $(top_srcdir)/contrib/macdeploy/DS_Store \
  $(top_srcdir)/contrib/macdeploy/detached-sig-apply.sh \
  $(top_srcdir)/contrib/macdeploy/detached-sig-create.sh

COVERAGE_INFO = baseline_filtered_combined.info baseline.info block_test.info \
  leveldb_baseline.info test_eacoin_filtered.info total_coverage.info \
  baseline_filtered.info block_test_filtered.info rpc_test.info rpc_test_filtered.info \
  leveldb_baseline_filtered.info test_eacoin_coverage.info test_eacoin.info

dist-hook:
	-$(MAKE) -C $(top_distdir)/src/leveldb clean
	-$(MAKE) -C $(top_distdir)/src/secp256k1 distclean
	-$(GIT) archive --format=tar HEAD -- src/clientversion.cpp | $(AMTAR) -C $(top_distdir) -xf -

distcheck-hook:
	$(MKDIR_P) $(top_distdir)/_build/src/leveldb
	cp -rf $(top_srcdir)/src/leveldb/* $(top_distdir)/_build/src/leveldb/
	-$(MAKE) -C $(top_distdir)/_build/src/leveldb clean

distcleancheck:
	@:

$(EACOIN_WIN_INSTALLER): all-recursive
	$(MKDIR_P) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(EACOIND_BIN) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(EACOIN_QT_BIN) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(EACOIN_CLI_BIN) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(WALLET_UTILITY_BIN) $(top_builddir)/release
	@test -f $(MAKENSIS) && $(MAKENSIS) -V2 $(top_builddir)/share/setup.nsi || \
	  echo error: could not build $@
	@echo built $@

$(if $(findstring src/,$(MAKECMDGOALS)),$(MAKECMDGOALS), none): FORCE
	$(MAKE) -C src $(patsubst src/%,%,$@)

$(OSX_APP)/Contents/PkgInfo:
	$(MKDIR_P) $(@D)
	@echo "APPL????" > $@

$(OSX_APP)/Contents/Resources/empty.lproj:
	$(MKDIR_P) $(@D)
	@touch $@ 

$(OSX_APP)/Contents/Info.plist: $(OSX_PLIST)
	$(MKDIR_P) $(@D)
	$(INSTALL_DATA) $< $@

$(OSX_APP)/Contents/Resources/eacoin.icns: $(OSX_INSTALLER_ICONS)
	$(MKDIR_P) $(@D)
	$(INSTALL_DATA) $< $@

$(OSX_APP)/Contents/MacOS/EACoin-Qt: $(EACOIN_QT_BIN)
	$(MKDIR_P) $(@D)
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM)  $< $@

$(OSX_APP)/Contents/Resources/Base.lproj/InfoPlist.strings: $(OSX_BASE_LPROJ_DIR)
	$(MKDIR_P) $(@D)
	$(INSTALL_DATA) $< $@

OSX_APP_BUILT=$(OSX_APP)/Contents/PkgInfo $(OSX_APP)/Contents/Resources/empty.lproj \
  $(OSX_APP)/Contents/Resources/eacoin.icns $(OSX_APP)/Contents/Info.plist \
  $(OSX_APP)/Contents/MacOS/EACoin-Qt $(OSX_APP)/Contents/Resources/Base.lproj/InfoPlist.strings

if BUILD_DARWIN
$(OSX_DMG): $(OSX_APP_BUILT) $(OSX_PACKAGING)
	$(OSX_DEPLOY_SCRIPT) $(OSX_APP) -add-qt-tr $(OSX_QT_TRANSLATIONS) -translations-dir=$(QT_TRANSLATION_DIR) -dmg -fancy $(OSX_FANCY_PLIST) -verbose 2

deploydir: $(OSX_DMG)
else
APP_DIST_DIR=$(top_builddir)/dist
APP_DIST_EXTRAS=$(APP_DIST_DIR)/.background/$(OSX_BACKGROUND_IMAGE) $(APP_DIST_DIR)/.DS_Store $(APP_DIST_DIR)/Applications

$(APP_DIST_DIR)/Applications:
	@rm -f $@
	@cd $(@D); $(LN_S) /Applications $(@F)

$(APP_DIST_EXTRAS): $(APP_DIST_DIR)/$(OSX_APP)/Contents/MacOS/EACoin-Qt

$(OSX_DMG): $(APP_DIST_EXTRAS)
	$(GENISOIMAGE) -no-cache-inodes -D -l -probe -V "EACoin-Core" -no-pad -r -dir-mode 0755 -apple -o $@ dist

$(APP_DIST_DIR)/.background/$(OSX_BACKGROUND_IMAGE): contrib/macdeploy/$(OSX_BACKGROUND_IMAGE)
	$(MKDIR_P) $(@D)
	$(INSTALL) $< $@
$(APP_DIST_DIR)/.DS_Store: contrib/macdeploy/DS_Store
	$(INSTALL) $< $@

$(APP_DIST_DIR)/$(OSX_APP)/Contents/MacOS/EACoin-Qt: $(OSX_APP_BUILT) $(OSX_PACKAGING)
	INSTALLNAMETOOL=$(INSTALLNAMETOOL)  OTOOL=$(OTOOL) STRIP=$(STRIP) $(OSX_DEPLOY_SCRIPT) $(OSX_APP) -translations-dir=$(QT_TRANSLATION_DIR) -add-qt-tr $(OSX_QT_TRANSLATIONS) -verbose 2

deploydir: $(APP_DIST_EXTRAS)
endif

if TARGET_DARWIN
appbundle: $(OSX_APP_BUILT)
deploy: $(OSX_DMG)
endif
if TARGET_WINDOWS
deploy: $(EACOIN_WIN_INSTALLER)
endif

$(EACOIN_QT_BIN): FORCE
	$(MAKE) -C src qt/$(@F)

$(EACOIND_BIN): FORCE
	$(MAKE) -C src $(@F)

$(EACOIN_CLI_BIN): FORCE
	$(MAKE) -C src $(@F)

$(WALLET_UTILITY_BIN): FORCE
	$(MAKE) -C src $(@F)

if USE_LCOV

baseline.info:
	$(LCOV) -c -i -d $(abs_builddir)/src -o $@

baseline_filtered.info: baseline.info
	$(LCOV) -r $< "/usr/include/*" -o $@

leveldb_baseline.info: baseline_filtered.info
	$(LCOV) -c -i -d $(abs_builddir)/src/leveldb -b $(abs_builddir)/src/leveldb -o $@

leveldb_baseline_filtered.info: leveldb_baseline.info
	$(LCOV) -r $< "/usr/include/*" -o $@

baseline_filtered_combined.info: leveldb_baseline_filtered.info baseline_filtered.info
	$(LCOV) -a leveldb_baseline_filtered.info -a baseline_filtered.info -o $@

test_eacoin.info: baseline_filtered_combined.info
	$(MAKE) -C src/ check
	$(LCOV) -c -d $(abs_builddir)/src -t test_eacoin -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

test_eacoin_filtered.info: test_eacoin.info
	$(LCOV) -r $< "/usr/include/*" -o $@

block_test.info: test_eacoin_filtered.info
	$(MKDIR_P) qa/tmp
	-@TIMEOUT=15 qa/pull-tester/run-eacoind-for-test.sh $(JAVA) -jar $(JAVA_COMPARISON_TOOL) qa/tmp/compTool $(COMPARISON_TOOL_REORG_TESTS)
	$(LCOV) -c -d $(abs_builddir)/src --t EACoinJBlockTest -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

block_test_filtered.info: block_test.info
	$(LCOV) -r $< "/usr/include/*" -o $@

rpc_test.info: test_eacoin_filtered.info
	-@TIMEOUT=15 python qa/pull-tester/rpc-tests.py $(EXTENDED_RPC_TESTS)
	$(LCOV) -c -d $(abs_builddir)/src --t rpc-tests -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

rpc_test_filtered.info: rpc_test.info
	$(LCOV) -r $< "/usr/include/*" -o $@

test_eacoin_coverage.info: baseline_filtered_combined.info test_eacoin_filtered.info
	$(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_eacoin_filtered.info -o $@

total_coverage.info: baseline_filtered_combined.info test_eacoin_filtered.info block_test_filtered.info rpc_test_filtered.info
	$(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_eacoin_filtered.info -a block_test_filtered.info -a rpc_test_filtered.info -o $@ | $(GREP) "\%" | $(AWK) '{ print substr($$3,2,50) "/" $$5 }' > coverage_percent.txt

test_eacoin.coverage/.dirstamp:  test_eacoin_coverage.info
	$(GENHTML) -s $< -o $(@D)
	@touch $@

total.coverage/.dirstamp: total_coverage.info
	$(GENHTML) -s $< -o $(@D)
	@touch $@

cov: test_eacoin.coverage/.dirstamp total.coverage/.dirstamp

endif

if USE_COMPARISON_TOOL
check-local:
	$(MKDIR_P) qa/tmp
	@qa/pull-tester/run-eacoind-for-test.sh $(JAVA) -jar $(JAVA_COMPARISON_TOOL) qa/tmp/compTool $(COMPARISON_TOOL_REORG_TESTS) 2>&1
endif

dist_noinst_SCRIPTS = autogen.sh

EXTRA_DIST = $(top_srcdir)/share/genbuild.sh qa/pull-tester/rpc-tests.py qa/rpc-tests $(DIST_DOCS) $(WINDOWS_PACKAGING) $(OSX_PACKAGING) $(BIN_CHECKS)

CLEANFILES = $(OSX_DMG) $(EACOIN_WIN_INSTALLER)

.INTERMEDIATE: $(COVERAGE_INFO)

clean-local:
	rm -rf coverage_percent.txt test_eacoin.coverage/ total.coverage/ qa/tmp/ cache/ $(OSX_APP)
