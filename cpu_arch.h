//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#ifndef CPU_ARCH_H
#define CPU_ARCH_H

#include <stdint.h>
#include "cpu_vendor.h"
#include "cpu_uarch.h"

struct cpu_arch {
	enum cpu_vendor vendor;
	enum cpu_uarch uarch;

	int processors;
	int cores;

	union {
		struct cpu_arch_x86 {
			uint8_t family;
			uint8_t model;
		} x86;
	};

	char model_name[128];
};

/**
 * @brief Parses and decodes CPU architecture.
 *
 * @arch A structure the architecture information is filled into.
 */
void cpu_arch_get(struct cpu_arch *arch);

/**
 * @brief Pretty prints the CPU architecture info.
 *
 * @arch Initialized cpu_arch structure.
 */
void cpu_arch_print(struct cpu_arch *arch);

#endif /* CPU_ARCH_H */
