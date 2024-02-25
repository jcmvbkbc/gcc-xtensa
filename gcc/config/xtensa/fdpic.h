#undef	TARGET_FDPIC_CC1_SPEC
#define TARGET_FDPIC_CC1_SPEC "%{!mno-fdpic:-mfdpic}"

#undef	TARGET_FDPIC_ASM_SPEC
#define TARGET_FDPIC_ASM_SPEC "%{!mno-fdpic:--fdpic}"

#undef	TARGET_FDPIC_LINKER_EMULATION
#define TARGET_FDPIC_LINKER_EMULATION "%{!mno-fdpic:-m elf32xtensa_fdpic}"
