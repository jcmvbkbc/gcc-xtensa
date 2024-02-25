#undef MUSL_DYNAMIC_LINKER
#define MUSL_DYNAMIC_LINKER \
  "/lib/ld-musl-xtensa%{!mno-fdpic:-fdpic}.so.1"
