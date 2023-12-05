LIB=sysinfo
LIB_SRCS=$(filter-out mem_info_test.c bat_info_test.c cpu_info_test.c,$(wildcard *.c))
LIB_HEADERS=$(wildcard *.h)
INCLUDEDIR=$(PREFIX)/include/sysinfo/

BIN=cpu_info_test bat_info_test mem_info_test
