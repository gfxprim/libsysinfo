// Generated file, do not edit! run ./gen_uarch.sh > cpu_uarch.h

#ifndef CPU_UARCH_H
#define CPU_UARCH_H

enum cpu_uarch {
	CPU_UARCH_UNKNOWN,
	CPU_UARCH_P5,
	CPU_UARCH_QUARK,
	CPU_UARCH_P6,
	CPU_UARCH_PENTIUM_M,
	CPU_UARCH_MODIFIED_PENTIUM_M,
	CPU_UARCH_CORE,
	CPU_UARCH_PENRYN,
	CPU_UARCH_NEHALEM,
	CPU_UARCH_SANDY_BRIDGE,
	CPU_UARCH_IVY_BRIDGE,
	CPU_UARCH_HASWELL,
	CPU_UARCH_BROADWELL,
	CPU_UARCH_SKY_LAKE,
	CPU_UARCH_CANNON_LAKE,
	CPU_UARCH_ICE_LAKE,
	CPU_UARCH_NETBURST,
	CPU_UARCH_BONNELL,
	CPU_UARCH_SALTWELL,
	CPU_UARCH_SILVERMONT,
	CPU_UARCH_AIRMONT,
	CPU_UARCH_GOLDMONT,
	CPU_UARCH_GOLDMONT_PLUS,
	CPU_UARCH_KNIGHTS_FERRY,
	CPU_UARCH_KNIGHTS_CORNER,
	CPU_UARCH_KNIGHTS_LANDING,
	CPU_UARCH_KNIGHTS_HILL,
	CPU_UARCH_KNIGHTS_MILL,
	CPU_UARCH_XSCALE,
	CPU_UARCH_K5,
	CPU_UARCH_K6,
	CPU_UARCH_K7,
	CPU_UARCH_K8,
	CPU_UARCH_K10,
	CPU_UARCH_BULLDOZER,
	CPU_UARCH_PILEDRIVER,
	CPU_UARCH_STEAMROLLER,
	CPU_UARCH_EXCAVATOR,
	CPU_UARCH_ZEN,
	CPU_UARCH_ZEN2,
	CPU_UARCH_ZEN3,
	CPU_UARCH_ZEN4,
	CPU_UARCH_GEODE,
	CPU_UARCH_BOBCAT,
	CPU_UARCH_JAGUAR,
	CPU_UARCH_PUMA,
	CPU_UARCH_ARM8,
	CPU_UARCH_ARM9,
	CPU_UARCH_ARM10,
	CPU_UARCH_ARM11,
	CPU_UARCH_SA110,
	CPU_UARCH_SA1100,
	CPU_UARCH_IPX425,
	CPU_UARCH_PXA93X,
	CPU_UARCH_PXA30X,
	CPU_UARCH_PXA31X,
	CPU_UARCH_PXA32X,
	CPU_UARCH_SA1110,
	CPU_UARCH_IPX1200,
	CPU_UARCH_CORTEX_A5,
	CPU_UARCH_CORTEX_A7,
	CPU_UARCH_CORTEX_A8,
	CPU_UARCH_CORTEX_A9,
	CPU_UARCH_CORTEX_A12,
	CPU_UARCH_CORTEX_A15,
	CPU_UARCH_CORTEX_A17,
	CPU_UARCH_CORTEX_A32,
	CPU_UARCH_CORTEX_A35,
	CPU_UARCH_CORTEX_A53,
	CPU_UARCH_CORTEX_A55R0,
	CPU_UARCH_CORTEX_A55,
	CPU_UARCH_CORTEX_A57,
	CPU_UARCH_CORTEX_A65,
	CPU_UARCH_CORTEX_A72,
	CPU_UARCH_CORTEX_A73,
	CPU_UARCH_CORTEX_A75,
	CPU_UARCH_CORTEX_A76,
	CPU_UARCH_CORTEX_A77,
	CPU_UARCH_CORTEX_A78,
	CPU_UARCH_NEOVERSE_N1,
	CPU_UARCH_NEOVERSE_E1,
	CPU_UARCH_NEOVERSE_V1,
	CPU_UARCH_NEOVERSE_N2,
	CPU_UARCH_CORTEX_X1,
	CPU_UARCH_CORTEX_X2,
	CPU_UARCH_CORTEX_A510,
	CPU_UARCH_CORTEX_A710,
	CPU_UARCH_SCORPION,
	CPU_UARCH_KRAIT,
	CPU_UARCH_KRYO,
	CPU_UARCH_FALKOR,
	CPU_UARCH_SAPHIRA,
	CPU_UARCH_DENVER,
	CPU_UARCH_DENVER2,
	CPU_UARCH_CARMEL,
	CPU_UARCH_EXYNOS_M1,
	CPU_UARCH_EXYNOS_M2,
	CPU_UARCH_EXYNOS_M3,
	CPU_UARCH_EXYNOS_M4,
	CPU_UARCH_EXYNOS_M5,
	CPU_UARCH_SWIFT,
	CPU_UARCH_CYCLONE,
	CPU_UARCH_TYPHOON,
	CPU_UARCH_TWISTER,
	CPU_UARCH_HURRICANE,
	CPU_UARCH_MONSOON,
	CPU_UARCH_MISTRAL,
	CPU_UARCH_VORTEX,
	CPU_UARCH_TEMPEST,
	CPU_UARCH_LIGHTNING,
	CPU_UARCH_THUNDER,
	CPU_UARCH_FIRESTORM,
	CPU_UARCH_ICESTORM,
	CPU_UARCH_AVALANCHE,
	CPU_UARCH_BLIZZARD,
	CPU_UARCH_SAWTOOTH,
	CPU_UARCH_EVEREST,
	CPU_UARCH_THUNDERX,
	CPU_UARCH_THUNDERX2,
	CPU_UARCH_OCTEONTX2,
	CPU_UARCH_THUNDERX3,
	CPU_UARCH_FEROCEON,
	CPU_UARCH_PJ4,
	CPU_UARCH_BRAHMA_B15,
	CPU_UARCH_BRAHMA_B53,
	CPU_UARCH_XGENE,
	CPU_UARCH_TAISHAN_V110,
	CPU_UARCH_TAISHAN_V120,
	CPU_UARCH_A64FX,
	CPU_UARCH_FA526,
	CPU_UARCH_FA626,
	CPU_UARCH_AMPERE_1,
	CPU_UARCH_AMPERE_1A,
};

static inline const char *cpu_uarch_name(enum cpu_uarch uarch)
{
	switch (uarch) {
	case CPU_UARCH_UNKNOWN:
		return "Unknown";
	case CPU_UARCH_P5:
		return "P5";
	case CPU_UARCH_QUARK:
		return "Quark";
	case CPU_UARCH_P6:
		return "P6";
	case CPU_UARCH_PENTIUM_M:
		return "Pentium M";
	case CPU_UARCH_MODIFIED_PENTIUM_M:
		return "Modified Pentium_m";
	case CPU_UARCH_CORE:
		return "Core";
	case CPU_UARCH_PENRYN:
		return "Penryn";
	case CPU_UARCH_NEHALEM:
		return "Nehalem";
	case CPU_UARCH_SANDY_BRIDGE:
		return "Sandy Bridge";
	case CPU_UARCH_IVY_BRIDGE:
		return "Ivy Bridge";
	case CPU_UARCH_HASWELL:
		return "Haswell";
	case CPU_UARCH_BROADWELL:
		return "Broadwell";
	case CPU_UARCH_SKY_LAKE:
		return "Sky Lake";
	case CPU_UARCH_CANNON_LAKE:
		return "Cannon Lake";
	case CPU_UARCH_ICE_LAKE:
		return "Ice Lake";
	case CPU_UARCH_NETBURST:
		return "Netburst";
	case CPU_UARCH_BONNELL:
		return "Bonnell";
	case CPU_UARCH_SALTWELL:
		return "Saltwell";
	case CPU_UARCH_SILVERMONT:
		return "Silvermont";
	case CPU_UARCH_AIRMONT:
		return "Airmont";
	case CPU_UARCH_GOLDMONT:
		return "Goldmont";
	case CPU_UARCH_GOLDMONT_PLUS:
		return "Goldmont Plus";
	case CPU_UARCH_KNIGHTS_FERRY:
		return "Knights Ferry";
	case CPU_UARCH_KNIGHTS_CORNER:
		return "Knights Corner";
	case CPU_UARCH_KNIGHTS_LANDING:
		return "Knights Landing";
	case CPU_UARCH_KNIGHTS_HILL:
		return "Knights Hill";
	case CPU_UARCH_KNIGHTS_MILL:
		return "Knights Mill";
	case CPU_UARCH_XSCALE:
		return "Xscale";
	case CPU_UARCH_K5:
		return "K5";
	case CPU_UARCH_K6:
		return "K6";
	case CPU_UARCH_K7:
		return "K7";
	case CPU_UARCH_K8:
		return "K8";
	case CPU_UARCH_K10:
		return "K10";
	case CPU_UARCH_BULLDOZER:
		return "Bulldozer";
	case CPU_UARCH_PILEDRIVER:
		return "Piledriver";
	case CPU_UARCH_STEAMROLLER:
		return "Steamroller";
	case CPU_UARCH_EXCAVATOR:
		return "Excavator";
	case CPU_UARCH_ZEN:
		return "Zen";
	case CPU_UARCH_ZEN2:
		return "Zen2";
	case CPU_UARCH_ZEN3:
		return "Zen3";
	case CPU_UARCH_ZEN4:
		return "Zen4";
	case CPU_UARCH_GEODE:
		return "Geode";
	case CPU_UARCH_BOBCAT:
		return "Bobcat";
	case CPU_UARCH_JAGUAR:
		return "Jaguar";
	case CPU_UARCH_PUMA:
		return "Puma";
	case CPU_UARCH_ARM8:
		return "Arm8";
	case CPU_UARCH_ARM9:
		return "Arm9";
	case CPU_UARCH_ARM10:
		return "Arm10";
	case CPU_UARCH_ARM11:
		return "Arm11";
	case CPU_UARCH_SA110:
		return "SA110";
	case CPU_UARCH_SA1100:
		return "SA1100";
	case CPU_UARCH_IPX425:
		return "IPX425";
	case CPU_UARCH_PXA93X:
		return "PXA93x";
	case CPU_UARCH_PXA30X:
		return "PXA30x";
	case CPU_UARCH_PXA31X:
		return "PXA31x";
	case CPU_UARCH_PXA32X:
		return "PXA32x";
	case CPU_UARCH_SA1110:
		return "SA1110";
	case CPU_UARCH_IPX1200:
		return "IPX1200";
	case CPU_UARCH_CORTEX_A5:
		return "Cortex A5";
	case CPU_UARCH_CORTEX_A7:
		return "Cortex A7";
	case CPU_UARCH_CORTEX_A8:
		return "Cortex A8";
	case CPU_UARCH_CORTEX_A9:
		return "Cortex A9";
	case CPU_UARCH_CORTEX_A12:
		return "Cortex A12";
	case CPU_UARCH_CORTEX_A15:
		return "Cortex A15";
	case CPU_UARCH_CORTEX_A17:
		return "Cortex A17";
	case CPU_UARCH_CORTEX_A32:
		return "Cortex A32";
	case CPU_UARCH_CORTEX_A35:
		return "Cortex A35";
	case CPU_UARCH_CORTEX_A53:
		return "Cortex A53";
	case CPU_UARCH_CORTEX_A55R0:
		return "Cortex A55r0";
	case CPU_UARCH_CORTEX_A55:
		return "Cortex A55";
	case CPU_UARCH_CORTEX_A57:
		return "Cortex A57";
	case CPU_UARCH_CORTEX_A65:
		return "Cortex A65";
	case CPU_UARCH_CORTEX_A72:
		return "Cortex A72";
	case CPU_UARCH_CORTEX_A73:
		return "Cortex A73";
	case CPU_UARCH_CORTEX_A75:
		return "Cortex A75";
	case CPU_UARCH_CORTEX_A76:
		return "Cortex A76";
	case CPU_UARCH_CORTEX_A77:
		return "Cortex A77";
	case CPU_UARCH_CORTEX_A78:
		return "Cortex A78";
	case CPU_UARCH_NEOVERSE_N1:
		return "Neoverse N1";
	case CPU_UARCH_NEOVERSE_E1:
		return "Neoverse E1";
	case CPU_UARCH_NEOVERSE_V1:
		return "Neoverse V1";
	case CPU_UARCH_NEOVERSE_N2:
		return "Neoverse N2";
	case CPU_UARCH_CORTEX_X1:
		return "Cortex X1";
	case CPU_UARCH_CORTEX_X2:
		return "Cortex X2";
	case CPU_UARCH_CORTEX_A510:
		return "Cortex A510";
	case CPU_UARCH_CORTEX_A710:
		return "Cortex A710";
	case CPU_UARCH_SCORPION:
		return "Scorpion";
	case CPU_UARCH_KRAIT:
		return "Krait";
	case CPU_UARCH_KRYO:
		return "Kryo";
	case CPU_UARCH_FALKOR:
		return "Falkor";
	case CPU_UARCH_SAPHIRA:
		return "Saphira";
	case CPU_UARCH_DENVER:
		return "Denver";
	case CPU_UARCH_DENVER2:
		return "Denver2";
	case CPU_UARCH_CARMEL:
		return "Carmel";
	case CPU_UARCH_EXYNOS_M1:
		return "Exynos M1";
	case CPU_UARCH_EXYNOS_M2:
		return "Exynos M2";
	case CPU_UARCH_EXYNOS_M3:
		return "Exynos M3";
	case CPU_UARCH_EXYNOS_M4:
		return "Exynos M4";
	case CPU_UARCH_EXYNOS_M5:
		return "Exynos M5";
	case CPU_UARCH_SWIFT:
		return "Swift";
	case CPU_UARCH_CYCLONE:
		return "Cyclone";
	case CPU_UARCH_TYPHOON:
		return "Typhoon";
	case CPU_UARCH_TWISTER:
		return "Twister";
	case CPU_UARCH_HURRICANE:
		return "Hurricane";
	case CPU_UARCH_MONSOON:
		return "Monsoon";
	case CPU_UARCH_MISTRAL:
		return "Mistral";
	case CPU_UARCH_VORTEX:
		return "Vortex";
	case CPU_UARCH_TEMPEST:
		return "Tempest";
	case CPU_UARCH_LIGHTNING:
		return "Lightning";
	case CPU_UARCH_THUNDER:
		return "Thunder";
	case CPU_UARCH_FIRESTORM:
		return "Firestorm";
	case CPU_UARCH_ICESTORM:
		return "Icestorm";
	case CPU_UARCH_AVALANCHE:
		return "Avalanche";
	case CPU_UARCH_BLIZZARD:
		return "Blizzard";
	case CPU_UARCH_SAWTOOTH:
		return "Sawtooth";
	case CPU_UARCH_EVEREST:
		return "Everest";
	case CPU_UARCH_THUNDERX:
		return "ThunderX";
	case CPU_UARCH_THUNDERX2:
		return "ThunderX2";
	case CPU_UARCH_OCTEONTX2:
		return "OcteonTX2";
	case CPU_UARCH_THUNDERX3:
		return "ThunderX3";
	case CPU_UARCH_FEROCEON:
		return "Feroceon";
	case CPU_UARCH_PJ4:
		return "PJ4";
	case CPU_UARCH_BRAHMA_B15:
		return "Brahma B15";
	case CPU_UARCH_BRAHMA_B53:
		return "Brahma B53";
	case CPU_UARCH_XGENE:
		return "Xgene";
	case CPU_UARCH_TAISHAN_V110:
		return "TaiShan V110";
	case CPU_UARCH_TAISHAN_V120:
		return "TaiShan V120";
	case CPU_UARCH_A64FX:
		return "A64FX";
	case CPU_UARCH_FA526:
		return "FA526";
	case CPU_UARCH_FA626:
		return "FA626";
	case CPU_UARCH_AMPERE_1:
		return "Ampere-1";
	case CPU_UARCH_AMPERE_1A:
		return "Ampere-1A";
	}

	return "Fixme";
}

#endif /* CPU_UARCH_H */
