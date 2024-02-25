#undef	STARTFILE_SPEC
#define STARTFILE_SPEC "%{!mno-fdpic:%{!shared:crtreloc.o%s}} " \
  GNU_USER_TARGET_STARTFILE_SPEC
