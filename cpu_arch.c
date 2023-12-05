//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>

 */

#include <string.h>
#include <stdio.h>

#include "cpu_arch.h"

void cpu_arch_print(struct cpu_arch *arch)
{
	printf("Vendor\t\t: %s\n", cpu_vendor_name(arch->vendor));
	printf("Architecture\t: %s\n", cpu_uarch_name(arch->uarch));
	printf("Model name\t: %s\n", arch->model_name);
	printf("Processors\t: %i\n", arch->processors);
	printf("Cores\t\t: %i\n", arch->cores);
}

__attribute__((weak)) void cpu_arch_get(struct cpu_arch *arch)
{
	arch->vendor = CPU_VENDOR_UNKNOWN;
	arch->uarch = CPU_UARCH_UNKNOWN;
	arch->processors = -1;
	arch->cores = -1;
	strcpy(arch->model_name, "Unknown");
}
