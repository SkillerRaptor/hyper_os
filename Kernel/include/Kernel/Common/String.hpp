/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

namespace Kernel
{
	extern "C"
	{
		int strncmp(const char* string1, const char* string2, size_t num);
	}
} // namespace Kernel