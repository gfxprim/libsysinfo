//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2024 Cyril Hrubis <metan@ucw.cz>

 */

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "cpuinfo_parser.h"
#include "cpu_vendor.h"
#include "cpu_arch.h"
#include "cpu_uarch.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))

#if defined(__aarch64__) || defined(__arm__)

static struct cpuinfo_entry entries[] = {
	{.name = "CPU implementer", .type = CPUINFO_UINT},
	{.name = "CPU part", .type = CPUINFO_UINT},
	{.name = "Hardware", .type = CPUINFO_STR},
	{.name = "processor", .type = CPUINFO_UINT_MAX},
};

static enum cpu_uarch match_uarch_arm(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x810:
		return CPU_UARCH_ARM8;
	case 0x920:
	case 0x922:
	case 0x926:
	case 0x940:
	case 0x966:
		return CPU_UARCH_ARM9;
	case 0xa20:
	case 0xa22:
	case 0xa26:
		return CPU_UARCH_ARM10;
	case 0xb02:
	case 0xb36:
	case 0xb56:
	case 0xb76:
		return CPU_UARCH_ARM11;
	case 0xc05:
		return CPU_UARCH_CORTEX_A5;
	case 0xc07:
		return CPU_UARCH_CORTEX_A7;
	case 0xc08:
		return CPU_UARCH_CORTEX_A8;
	case 0xc09:
		return CPU_UARCH_CORTEX_A9;
	case 0xc0d:
		return CPU_UARCH_CORTEX_A12;
	case 0xc0f:
		return CPU_UARCH_CORTEX_A15;
	case 0xc0e:
		return CPU_UARCH_CORTEX_A17;
	case 0xd01:
		return CPU_UARCH_CORTEX_A32;
	case 0xd03:
		return CPU_UARCH_CORTEX_A53;
	case 0xd04:
		return CPU_UARCH_CORTEX_A35;
	case 0xd05:
		return CPU_UARCH_CORTEX_A55;
	case 0xd07:
		return CPU_UARCH_CORTEX_A57;
	case 0xd08:
		return CPU_UARCH_CORTEX_A72;
	case 0xd09:
		return CPU_UARCH_CORTEX_A73;
	case 0xd0a:
		return CPU_UARCH_CORTEX_A75;
	case 0xd0b:
		return CPU_UARCH_CORTEX_A76;
	case 0xd0d:
		return CPU_UARCH_CORTEX_A77;
	case 0xd41:
		return CPU_UARCH_CORTEX_A78;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_broadcom(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x0f:
		return CPU_UARCH_BRAHMA_B15;
	case 0x100:
		return CPU_UARCH_BRAHMA_B53;
	case 0x516:
		return CPU_UARCH_THUNDERX2;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_dec(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0xa10:
		return CPU_UARCH_SA110;
	case 0xa11:
		return CPU_UARCH_SA1100;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_samsung(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x001:
		return CPU_UARCH_EXYNOS_M1;
	case 0x002:
		return CPU_UARCH_EXYNOS_M3;
	case 0x003:
		return CPU_UARCH_EXYNOS_M4;
	case 0x004:
		return CPU_UARCH_EXYNOS_M5;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_qualcomm(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x00f:
	case 0x02d:
		return CPU_UARCH_SCORPION;
	case 0x06f:
	case 0x04d:
		return CPU_UARCH_KRAIT;
	case 0x201:
	case 0x205:
	case 0x211:
	case 0x800 ... 0x805:
		return CPU_UARCH_KRYO;
	case 0xc00:
		return CPU_UARCH_FALKOR;
	case 0xc01:
		return CPU_UARCH_SAPHIRA;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_cavium(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x0a0 ... 0x0a3:
		return CPU_UARCH_THUNDERX;
	case 0x0af:
		return CPU_UARCH_THUNDERX2;
	case 0x0b0 ... 0xb6:
		return CPU_UARCH_OCTEONTX2;
	case 0x0b8:
		return CPU_UARCH_THUNDERX3;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_nvidia(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x000:
		return CPU_UARCH_DENVER;
	case 0x003:
		return CPU_UARCH_DENVER2;
	case 0x004:
		return CPU_UARCH_CARMEL;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_apm(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x004:
		return CPU_UARCH_XGENE;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_marvel(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x131:
		return CPU_UARCH_FEROCEON;
	case 0x581:
	case 0x584:
		return CPU_UARCH_PJ4;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static enum cpu_uarch match_uarch_intel(unsigned int cpu_part)
{
	switch (cpu_part) {
	case 0x41c:
	case 0x41d:
	case 0x41f:
		return CPU_UARCH_IPX425;
	case 0x682:
		return CPU_UARCH_PXA32X;
	case 0x683:
		return CPU_UARCH_PXA93X;
	case 0x688:
		return CPU_UARCH_PXA30X;
	case 0x689:
		return CPU_UARCH_PXA31X;
	case 0xb11:
		return CPU_UARCH_SA1110;
	case 0xc12:
		return CPU_UARCH_IPX1200;
	default:
		return CPU_UARCH_UNKNOWN;
	}
}

static struct vendor_id_map {
	unsigned int implementer_id;
	enum cpu_vendor vendor_id;
	enum cpu_uarch (*match_uarch)(unsigned int cpu_part);
} vendor_id_map[] = {
	{0x41, CPU_VENDOR_ARM, match_uarch_arm},
	{0x42, CPU_VENDOR_BROADCOM, match_uarch_broadcom},
	{0x43, CPU_VENDOR_CAVIUM, match_uarch_cavium},
	{0x44, CPU_VENDOR_DEC, match_uarch_dec},
	{0x4e, CPU_VENDOR_NVIDIA, match_uarch_nvidia},
	{0x50, CPU_VENDOR_APM, match_uarch_apm},
	{0x51, CPU_VENDOR_QUALCOMM, match_uarch_qualcomm},
	{0x53, CPU_VENDOR_SAMSUNG, match_uarch_samsung},
	{0x56, CPU_VENDOR_MARVELL, match_uarch_marvel},
	{0x69, CPU_VENDOR_INTEL, match_uarch_intel},
};

static void match_vendor_uarch(struct cpu_arch *arch, struct cpuinfo_entry *implementer, struct cpuinfo_entry *cpu_part)
{
	size_t i;

	arch->vendor = CPU_VENDOR_UNKNOWN;
	arch->uarch = CPU_UARCH_UNKNOWN;

	if (!implementer->found)
		return;

	for (i = 0; i < ARRAY_SIZE(vendor_id_map); i++) {
		if (vendor_id_map[i].implementer_id == implementer->val.uint) {
			arch->vendor = vendor_id_map[i].vendor_id;

			if (cpu_part->found && vendor_id_map[i].match_uarch)
				arch->uarch = vendor_id_map[i].match_uarch(cpu_part->val.uint);

			return;
		}
	}
}

void cpu_arch_get(struct cpu_arch *arch)
{
	cpuinfo_parse(entries, ARRAY_SIZE(entries));

	match_vendor_uarch(arch, &entries[0], &entries[1]);

	arch->cores = entries[3].found ? (int)entries[3].val.uint + 1 : -1;
	/* TODO: does arm have hyperthreading? */
	arch->processors = arch->cores;

	if (entries[2].found) {
		strncpy(arch->model_name, entries[2].val.str, sizeof(arch->model_name));
		arch->model_name[sizeof(arch->model_name)-1] = 0;
	}

	cpuinfo_free(entries, ARRAY_SIZE(entries));
}

#endif /* defined(__aarch64__) || defined(__arm__) */
