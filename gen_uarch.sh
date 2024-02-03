#!/bin/sh
#
# Generate cpu_uarch.h
#

echo "// Generated file, do not edit! run ./gen_uarch.sh > cpu_uarch.h"
echo ""
echo "#ifndef CPU_UARCH_H"
echo "#define CPU_UARCH_H"
echo

echo "enum cpu_uarch {"
for i in $(cat cpu_uarchs.txt); do
	cap=$(echo "cpu_uarch_$i" | tr [a-z] [A-Z] | tr  - _)
	echo "	$cap,"
done
echo "};"
echo
echo "static inline const char *cpu_uarch_name(enum cpu_uarch uarch)"
echo "{"
echo "	switch (uarch) {"
for i in $(cat cpu_uarchs.txt); do
	name=$(echo $i |sed "s/_/ /" | sed -e "s/\b\(.\)/\u\1/g")
	cap=$(echo "cpu_uarch_$i" | tr [a-z] [A-Z] | tr  - _)
	echo "	case $cap:"
	echo "		return \"$name\";"
done
echo "	}"
echo ""
echo "	return \"Fixme\";"
echo "}"
echo
echo "#endif /* CPU_UARCH_H */"
