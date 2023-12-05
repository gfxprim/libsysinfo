// Generated file, do not edit! run ./gen_vendor.sh > cpu_vendor.h

#ifndef CPU_VENDOR_H
#define CPU_VENDOR_H

enum cpu_vendor {
	CPU_VENDOR_UNKNOWN,
	CPU_VENDOR_INTEL,
	CPU_VENDOR_AMD,
	CPU_VENDOR_ARM,
	CPU_VENDOR_QUALCOMM,
	CPU_VENDOR_APPLE,
	CPU_VENDOR_SAMSUNG,
	CPU_VENDOR_NVIDIA,
	CPU_VENDOR_MIPS,
	CPU_VENDOR_IBM,
	CPU_VENDOR_INGENIC,
	CPU_VENDOR_VIA,
	CPU_VENDOR_CAVIUM,
	CPU_VENDOR_BROADCOM,
	CPU_VENDOR_APM,
	CPU_VENDOR_HUAWEI,
	CPU_VENDOR_HYGON,
	CPU_VENDOR_TI,
	CPU_VENDOR_MARVELL,
	CPU_VENDOR_RDC,
	CPU_VENDOR_DM_P,
	CPU_VENDOR_MOTOROLA,
	CPU_VENDOR_TRANSMETA,
	CPU_VENDOR_CYRIX,
	CPU_VENDOR_NSC,
	CPU_VENDOR_UMC,
	CPU_VENDOR_DEC,
	CPU_VENDOR_ZHAOXIN,
	CPU_VENDOR_VORTEX,
};

static inline const char *cpu_vendor_name(enum cpu_vendor vendor)
{
	switch (vendor) {
	case CPU_VENDOR_UNKNOWN:
		return "Unknown";
	case CPU_VENDOR_INTEL:
		return "Intel";
	case CPU_VENDOR_AMD:
		return "AMD";
	case CPU_VENDOR_ARM:
		return "Arm";
	case CPU_VENDOR_QUALCOMM:
		return "Qualcomm";
	case CPU_VENDOR_APPLE:
		return "Apple";
	case CPU_VENDOR_SAMSUNG:
		return "Samsung";
	case CPU_VENDOR_NVIDIA:
		return "Nvidia";
	case CPU_VENDOR_MIPS:
		return "MIPS";
	case CPU_VENDOR_IBM:
		return "IBM";
	case CPU_VENDOR_INGENIC:
		return "Ingenic";
	case CPU_VENDOR_VIA:
		return "VIA";
	case CPU_VENDOR_CAVIUM:
		return "Cavium";
	case CPU_VENDOR_BROADCOM:
		return "Broadcom";
	case CPU_VENDOR_APM:
		return "APM";
	case CPU_VENDOR_HUAWEI:
		return "Huawei";
	case CPU_VENDOR_HYGON:
		return "Hygon";
	case CPU_VENDOR_TI:
		return "TI";
	case CPU_VENDOR_MARVELL:
		return "Marvell";
	case CPU_VENDOR_RDC:
		return "RDC";
	case CPU_VENDOR_DM_P:
		return "DM&P";
	case CPU_VENDOR_MOTOROLA:
		return "Motorola";
	case CPU_VENDOR_TRANSMETA:
		return "Transmeta";
	case CPU_VENDOR_CYRIX:
		return "Cyrix";
	case CPU_VENDOR_NSC:
		return "NSC";
	case CPU_VENDOR_UMC:
		return "UMC";
	case CPU_VENDOR_DEC:
		return "DEC";
	case CPU_VENDOR_ZHAOXIN:
		return "Zhaoxin";
	case CPU_VENDOR_VORTEX:
		return "Vortex";
	}

	return "Fixme";
}

#endif /* CPU_VENDOR_H */
