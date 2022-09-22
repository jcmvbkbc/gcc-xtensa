/* Xtensa FDPIC ABI configuration.
   Copyright (C) 2024 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#undef	TARGET_FDPIC_CC1_SPEC
#define TARGET_FDPIC_CC1_SPEC "%{!mno-fdpic:-mfdpic}"

#undef	TARGET_FDPIC_ASM_SPEC
#define TARGET_FDPIC_ASM_SPEC "%{!mno-fdpic:--fdpic}"

#undef	TARGET_FDPIC_LINKER_EMULATION
#define TARGET_FDPIC_LINKER_EMULATION "%{!mno-fdpic:-m elf32xtensa_fdpic}"
