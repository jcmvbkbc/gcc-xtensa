/* { dg-do compile } */
/* { dg-options "-O -mforce-l32" } */

void foo(int i);

void test_sc(signed char *p)
{
	foo(p[0]);
	foo(p[1]);
	foo(p[5]);
}

void test_uc(unsigned char *p)
{
	foo(p[0]);
	foo(p[1]);
	foo(p[5]);
}

void test_ss(signed short *p)
{
	foo(p[0]);
	foo(p[1]);
	foo(p[5]);
}

void test_us(unsigned short *p)
{
	foo(p[0]);
	foo(p[1]);
	foo(p[5]);
}

/* { dg-final { scan-assembler-not "l8ui" } } */
/* { dg-final { scan-assembler-not "l16ui" } } */
/* { dg-final { scan-assembler-not "l16si" } } */
