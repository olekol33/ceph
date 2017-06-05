# lrc plugin
set(jerasure_srcs
  ../jerasure/jerasure/src/galois.c
  ../jerasure/jerasure/src/jerasure.c
  ../jerasure/jerasure/src/liberation.c
  ../jerasure/jerasure/src/reed_sol.c
  ../jerasure/gf-complete/src/gf_wgen.c
  ../jerasure/gf-complete/src/gf_method.c
  ../jerasure/gf-complete/src/gf_w16.c
  ../jerasure/gf-complete/src/gf.c
  ../jerasure/gf-complete/src/gf_w32.c
  ../jerasure/gf-complete/src/gf_w64.c
  ../jerasure/gf-complete/src/gf_w128.c
  ../jerasure/gf-complete/src/gf_general.c
  ../jerasure/gf-complete/src/gf_w4.c
  ../jerasure/gf-complete/src/gf_rand.c
  ../jerasure/gf-complete/src/gf_w8.c)
 add_library(jerasure_generic OBJECT ${jerasure_srcs})

set(optlrc_srcs
  ErasureCodeOptLrc.cc
  $<TARGET_OBJECTS:erasure_code_objs>
  ${CMAKE_SOURCE_DIR}/src/common/str_map.cc
)

add_library(ec_optlrc SHARED ${optlrc_srcs})
add_dependencies(ec_optlrc ${CMAKE_SOURCE_DIR}/src/ceph_ver.h)
target_link_libraries(ec_optlrc crush json_spirit)
set_target_properties(ec_optlrc PROPERTIES VERSION 1.0.0 SOVERSION 1)
install(TARGETS ec_optlrc DESTINATION lib/erasure-code)
