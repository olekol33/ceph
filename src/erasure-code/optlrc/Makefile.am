# lrc plugin
noinst_HEADERS += \
  erasure-code/optlrc/ErasureCodeOptLrc.h

lrc_sources = \
  erasure-code/ErasureCode.cc \
  erasure-code/optlrc/ErasureCodePluginOptLrc.cc \
  erasure-code/optlrc/ErasureCodeOptLrc.cc

erasure-code/optlrc/ErasureCodePluginOptLrc.cc: ./ceph_ver.h

libec_optlrc_la_SOURCES = ${optlrc_sources} common/str_map.cc
libec_optlrc_la_CFLAGS = ${AM_CFLAGS}
libec_optlrc_la_CXXFLAGS= ${AM_CXXFLAGS}
libec_optlrc_la_LIBADD = $(LIBCRUSH) $(PTHREAD_LIBS) $(LIBJSON_SPIRIT)
libec_optlrc_la_LDFLAGS = ${AM_LDFLAGS} -module -avoid-version -shared
if LINUX
libec_optlrc_la_LDFLAGS += -export-symbols-regex '.*__erasure_code_.*'
endif

erasure_codelib_LTLIBRARIES += libec_optlrc.la
