#!/bin/sh
#
# Generate cpu_vendor.h
#

echo "// Generated file, do not edit! run ./gen_vendor.sh > cpu_vendor.h"
echo ""
echo "#ifndef CPU_VENDOR_H"
echo "#define CPU_VENDOR_H"
echo

echo "enum cpu_vendor {"
for i in $(cat cpu_vendors.txt); do
	cap=$(echo "cpu_vendor_$i" | tr [a-z] [A-Z] | tr '[&]' [_])
	echo "	$cap,"
done
echo "};"
echo
echo "static inline const char *cpu_vendor_name(enum cpu_vendor vendor)"
echo "{"
echo "	switch (vendor) {"
for i in $(cat cpu_vendors.txt); do
	name=$(echo $i |sed "s/_/ /" | sed -e "s/\b\(.\)/\u\1/g")
	cap=$(echo "cpu_vendor_$i" | tr [a-z] [A-Z] | tr '[&]' [_])
	echo "	case $cap:"
	echo "		return \"$name\";"
done
echo "	}"
echo ""
echo "	return \"Fixme\";"
echo "}"
echo
echo "#endif /* CPU_VENDOR_H */"
