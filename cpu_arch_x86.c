//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "cpuinfo_parser.h"
#include "cpu_vendor.h"
#include "cpu_arch.h"
#include "cpu_uarch.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))

#if defined(__x86_64__) || defined(__i386__)

static struct cpuinfo_entry entries[] = {
	{.name = "cpu cores", .type = CPUINFO_UINT},
	{.name = "cpu family", .type = CPUINFO_UINT},
	{.name = "model", .type = CPUINFO_UINT},
	{.name = "model name", .type = CPUINFO_STR},
	{.name = "processor", .type = CPUINFO_UINT_MAX},
	{.name = "vendor_id", .type = CPUINFO_STR},
};

/* grep for c_ident in linux/arch/x86/kernel/cpu/ */
static struct vendor_id_map {
	const char *name;
	enum cpu_vendor vendor_id;
} vendor_id_map[] = {
	{"GenuineIntel", CPU_VENDOR_INTEL},
	{"AuthenticAMD", CPU_VENDOR_AMD},
	{"CentaurHauls", CPU_VENDOR_VIA},
	{"HygonGenuine", CPU_VENDOR_HYGON},
	{"GenuineTMx86", CPU_VENDOR_TRANSMETA},
	{"TransmetaCPU", CPU_VENDOR_TRANSMETA},
	{"CyrixInstead", CPU_VENDOR_CYRIX},
	{"Geode by NSC", CPU_VENDOR_NSC},
	{"Vortex86 SOC", CPU_VENDOR_VORTEX},
	{"  Shanghai  ", CPU_VENDOR_ZHAOXIN},
	{"UMC UMC UMC", CPU_VENDOR_UMC},
};

static enum cpu_vendor match_vendor(struct cpuinfo_entry *vendor)
{
	size_t i;

	if (!vendor->found)
		return CPU_VENDOR_UNKNOWN;

	for (i = 0; i < ARRAY_SIZE(vendor_id_map); i++) {
		if (!strcmp(vendor->val.str, vendor_id_map[i].name))
			return vendor_id_map[i].vendor_id;
	}

	return CPU_VENDOR_UNKNOWN;
}

static enum cpu_uarch parse_intel_uarch(unsigned int family, unsigned int model)
{
	switch (family) {
	case 0x05:
		switch (model) {
		case 0x01 ... 0x04:
			return CPU_UARCH_P5;
		case 0x05:
			return CPU_UARCH_QUARK;
		}
	break;
	case 0x06:
		switch (model) {
		case 0x01:
		case 0x03:
		case 0x05 ... 0x08:
		case 0x0B:
			return CPU_UARCH_P6;
		case 0x09:
		case 0x0D:
		case 0x15:
			return CPU_UARCH_PENTIUM_M;
		case 0x0E:
			return CPU_UARCH_MODIFIED_PENTIUM_M;
		case 0x0F:
		case 0x16:
			return CPU_UARCH_CORE;
		case 0x17:
		case 0x1D:
			return CPU_UARCH_PENRYN;
		case 0x1A:
		case 0x1E:
		case 0x1F:
		case 0x2E:
		case 0x25:
		case 0x2C:
		case 0x2F:
			return CPU_UARCH_NEHALEM;
		case 0x2A:
		case 0x2D:
			return CPU_UARCH_SANDY_BRIDGE;
		case 0x3A:
		case 0x3E:
			return CPU_UARCH_IVY_BRIDGE;
		case 0x3C:
		case 0x3F:
		case 0x45:
		case 0x46:
			return CPU_UARCH_HASWELL;
		case 0x3D:
		case 0x47:
		case 0x4F:
		case 0x56:
			return CPU_UARCH_BROADWELL;
		case 0x4E:
		case 0x55:
		case 0x5E:
		case 0x8E:
		case 0x9E:
		case 0xA5:
		case 0xA6:
			return CPU_UARCH_SKY_LAKE;
		case 0x66:
			return CPU_UARCH_CANNON_LAKE;
		case 0x6A:
		case 0x6C:
		case 0x7D:
		case 0x7E:
			return CPU_UARCH_ICE_LAKE;
		case 0x1C:
		case 0x26:
			return CPU_UARCH_BONNELL;
		case 0x27:
		case 0x35:
		case 0x36:
			return CPU_UARCH_SALTWELL;
		case 0x37:
		case 0x4A:
		case 0x4D:
		case 0x5A:
		case 0x5D:
			return CPU_UARCH_SILVERMONT;
		case 0x4C:
			return CPU_UARCH_AIRMONT;
		case 0x5C:
		case 0x5F:
			return CPU_UARCH_GOLDMONT;
		case 0x7A:
			return CPU_UARCH_GOLDMONT_PLUS;
		case 0x57:
			return CPU_UARCH_KNIGHTS_LANDING;
		case 0x85:
			return CPU_UARCH_KNIGHTS_MILL;
		}
	break;
	case 0x0B:
		switch (model) {
		case 0x00:
			return CPU_UARCH_KNIGHTS_FERRY;
		case 0x01:
			return CPU_UARCH_KNIGHTS_CORNER;
		}
	break;
	case 0x0F:
		switch (model) {
		case 0x01 ... 0x06:
			return CPU_UARCH_NETBURST;
		}
	break;
	default:
	break;
	}

	return CPU_UARCH_UNKNOWN;
}

static enum cpu_uarch parse_amd_uarch(unsigned int family, unsigned int model)
{
	switch (family) {
	case 0x05:
		switch (model) {
		case 0x00 ... 0x02:
			return CPU_UARCH_K5;
		case 0x06 ... 0x09:
		case 0x0D:
			return CPU_UARCH_K6;
		case 0x0A:
			return CPU_UARCH_GEODE;
		}
	break;
	case 0x06:
		return CPU_UARCH_K7;
	case 0x0f:
	case 0x11:
		return CPU_UARCH_K8;
	case 0x10:
	case 0x12:
		return CPU_UARCH_K10;
	case 0x14:
		return CPU_UARCH_BOBCAT;
	case 0x15:
		switch (model) {
		case 0x01:
			return CPU_UARCH_BULLDOZER;
		case 0x02:
		case 0x10:
		case 0x13:
			return CPU_UARCH_PILEDRIVER;
		case 0x30:
		case 0x38:
			return CPU_UARCH_STEAMROLLER;
		case 0x60:
		case 0x65:
		case 0x70:
			return CPU_UARCH_EXCAVATOR;
		}
	break;
	case 0x16:
		switch (model) {
		case 0x00 ... 0x03:
			return CPU_UARCH_JAGUAR;
		default:
			return CPU_UARCH_PUMA;
		}
	break;
	case 0x17:
		switch (model & 0xf0) {
		case 0x00:
		case 0x10:
		case 0x20:
			return CPU_UARCH_ZEN;
		default:
			return CPU_UARCH_ZEN2;
		}
	break;
	/* 0x18 is AMD + Hygon cooperation */
	case 0x19:
		switch (model & 0xf0) {
		case 0x00:
		case 0x20:
		case 0x30:
		case 0x40:
		case 0x50:
			return CPU_UARCH_ZEN3;
		case 0x10:
		case 0x60:
		case 0x70:
		case 0xa0:
			return CPU_UARCH_ZEN4;
		}
	break;
	default:
	break;
	}

	return CPU_UARCH_UNKNOWN;
}

static enum cpu_uarch parse_hygon_uarch(unsigned int family)
{
	if (family == 0x00)
		return CPU_UARCH_ZEN;

	return CPU_UARCH_UNKNOWN;
}

static void parse_uarch(struct cpu_arch *arch,
                        struct cpuinfo_entry *cpu_family,
                        struct cpuinfo_entry *cpu_model)
{
	arch->uarch = CPU_UARCH_UNKNOWN;

	if (!cpu_family->found || !cpu_model->found)
		return;

	arch->x86.family = cpu_family->val.uint;
	arch->x86.model = cpu_model->val.uint;

	switch (arch->vendor) {
	case CPU_VENDOR_INTEL:
		arch->uarch = parse_intel_uarch(cpu_family->val.uint, cpu_model->val.uint);
	break;
	case CPU_VENDOR_AMD:
		arch->uarch = parse_amd_uarch(cpu_family->val.uint, cpu_model->val.uint);
	break;
	case CPU_VENDOR_HYGON:
		arch->uarch = parse_hygon_uarch(cpu_family->val.uint);
	break;
	default:
		arch->uarch = CPU_UARCH_UNKNOWN;
	}
}

static char *remove_prefix(char *str, char *needle)
{
	char *ret = strstr(str, needle);

	if (!ret)
		return str;

	return ret + strlen(needle);
}

static void remove_suffix(char *str, char *suf_start)
{
	char *term = strstr(str, suf_start);

	if (term)
		term[0] = 0;
}

static void parse_model_name(struct cpu_arch *arch, struct cpuinfo_entry *entry)
{
	if (!entry->found) {
		strcpy(arch->model_name, "Unknown");
		return;
	}

	char *model_name = entry->val.str;

	if (arch->vendor == CPU_VENDOR_INTEL) {
		model_name = remove_prefix(model_name, "Core(TM)");
		model_name = remove_prefix(model_name, "Xeon(R) CPU");
		model_name = remove_prefix(model_name, "Pentium(R) CPU");
		model_name = remove_prefix(model_name, "Core(TM)");
		model_name = remove_prefix(model_name, "2 Duo CPU");
		model_name = remove_prefix(model_name, "Atom(TM) CPU");
		model_name = remove_prefix(model_name, "Celeron(R) CPU");
		model_name = remove_prefix(model_name, "Intel(R)");

		remove_suffix(model_name, "CPU @ ");
		remove_suffix(model_name, "processor ");
		remove_suffix(model_name, "@ ");
	}

	if (arch->vendor == CPU_VENDOR_AMD) {
		model_name = remove_prefix(model_name, "AMD-");
		model_name = remove_prefix(model_name, "AMD ");

		remove_suffix(model_name, "with ");
		remove_suffix(model_name, "Integrated");
		remove_suffix(model_name, "Processor");
		remove_suffix(model_name, "Dual Core");
		remove_suffix(model_name, "Eight-");
		remove_suffix(model_name, "2-");
		remove_suffix(model_name, "4-");
		remove_suffix(model_name, "6-");
		remove_suffix(model_name, "8-");
		remove_suffix(model_name, "10-");
		remove_suffix(model_name, "12-");
		remove_suffix(model_name, "14-");
		remove_suffix(model_name, "16-");
		remove_suffix(model_name, "18-");
		remove_suffix(model_name, "20-");
		remove_suffix(model_name, "22-");
		remove_suffix(model_name, "24-");
		remove_suffix(model_name, "26-");
		remove_suffix(model_name, "28-");
		remove_suffix(model_name, "30-");
		remove_suffix(model_name, "32-");
		remove_suffix(model_name, ", ");
	}

	while (isspace(*model_name))
		model_name++;

	strncpy(arch->model_name, model_name, sizeof(arch->model_name));
	arch->model_name[sizeof(arch->model_name)-1] = 0;
}

void cpu_arch_get(struct cpu_arch *arch)
{
	cpuinfo_parse(entries, ARRAY_SIZE(entries));

	arch->vendor = match_vendor(&entries[5]);

	parse_uarch(arch, &entries[1], &entries[2]);

	arch->processors = entries[0].found ? (int)entries[0].val.uint : -1;
	arch->cores = entries[4].found ? (int)entries[4].val.uint + 1 : -1;

	parse_model_name(arch, &entries[3]);

	cpuinfo_free(entries, ARRAY_SIZE(entries));
}

#endif /* defined(__X86_64__) || defined(__i386__) */
