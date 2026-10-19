/* { dg-do compile } */
/* { dg-options "-O2" } */

/* A variable shift sets SAR and then shifts.  When an earlier insn already
   left the same value in SAR, the setup is not repeated.  That includes a
   single normal predecessor.  A join of two predecessors keeps its setup.  */

int
sra2 (int a, int b, int s)
{
  return (a >> s) + (b >> s);
}

void
sra2_store (int *x, int *y, int val, int s)
{
  *x = val >> s;
  *y = (val + 1) >> s;
}

void
sll3 (int *p, int s)
{
  p[0] <<= s;
  p[1] <<= s;
  p[2] <<= s;
}

void
srl_rotr (unsigned int *p, int s)
{
  p[0] >>= s;
  p[1] = (p[1] >> s) | (p[1] << (32 - s));
}

void
ssa8 (unsigned int *p, int n)
{
  p[0] >>= n * 8;
  p[1] >>= n * 8;
}

void
ssa8b (unsigned int *p, int n)
{
  p[0] <<= n * 8;
  p[1] <<= n * 8;
}

void
rot_const (unsigned int *p)
{
  p[0] = (p[0] >> 7) | (p[0] << 25);
  p[1] = (p[1] >> 7) | (p[1] << 25);
}

/* SSR and SSL set SAR to different values.  */

int
sra_sll (int a, int s)
{
  return (a >> s) ^ (a << s);
}

/* The shift amount changes in between.  */

int
amount_changed (int a, int b, int s)
{
  int x = a >> s;
  s++;
  return x + (b >> s);
}

/* The first shift overwrites its own shift amount register.  */

int
amount_overwritten (int a, int b, int s)
{
  s = a >> s;
  return s + (b >> s);
}

/* SAR may be clobbered by a call or an asm.  */

extern void f (void);

void
across_call (volatile int *p, int s)
{
  p[0] >>= s;
  f ();
  p[1] >>= s;
}

void
across_asm (volatile int *p, int s)
{
  p[0] >>= s;
  __asm__ volatile ("nop");
  p[1] >>= s;
}

/* Same amount on the taken edge.  The second SSR goes away.  */

void
across_bb (volatile int *p, int s, int c)
{
  p[0] >>= s;
  if (c)
    p[1] >>= s;
}

/* Join of a path that set SAR and a path that did not.  Both SSRs stay.  */

void
across_join (volatile int *p, int s, int c)
{
  if (c)
    p[0] >>= s;
  else
    p[1] += 1;
  p[2] >>= s;
}

/* { dg-final { scan-assembler-times "\tssr\t" 15 } } */
/* { dg-final { scan-assembler-times "\tssl\t" 2 } } */
/* { dg-final { scan-assembler-times "\tssa8l\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssa8b\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssai\t" 1 } } */
