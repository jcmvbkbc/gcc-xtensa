/* { dg-do compile } */
/* { dg-require-effective-target xtensa_loops } */
/* { dg-options "-O2" } */

/* When every SAR setup in a zero-overhead loop is the same and the shift
   amount does not change in the loop, SAR is set once before the LOOP
   instruction.  */

int
sra_sum (const int *d, int s, int n)
{
  int r = 0;
  for (int i = 0; i < n; i++)
    r += d[i] >> s;
  return r;
}

int
sll_sum (const int *d, int s, int n)
{
  int r = 0;
  for (int i = 0; i < n; i++)
    r += d[i] << s;
  return r;
}

int
sra_sum32 (const int *d, int s)
{
  int r = 0;
  for (int i = 0; i < 32; i++)
    r += d[i] >> s;
  return r;
}

void
sra_srl (int *d, unsigned int *e, int s, int n)
{
  for (int i = 0; i < n; i++)
    {
      d[i] >>= s;
      e[i] >>= s;
    }
}

void
rotr7 (unsigned int *d, int n)
{
  for (int i = 0; i < n; i++)
    d[i] = (d[i] >> 7) | (d[i] << 25);
}

void
bswap (unsigned int *d, int n)
{
  for (int i = 0; i < n; i++)
    d[i] = __builtin_bswap32 (d[i]);
}

/* Hoisted from a loop with multiple basic blocks.  */

void
srl_if_nonzero (unsigned int *d, int s, int n)
{
  for (int i = 0; i < n; i++)
    if (d[i])
      d[i] >>= s;
}

/* Not hoisted: SSR and SSL in one loop.  */

int
sra_sll_sum (const int *d, int s, int n)
{
  int r = 0;
  for (int i = 0; i < n; i++)
    r += (d[i] >> s) - (d[i] << s);
  return r;
}

/* Not hoisted: the shift amount varies.  */

void
sra_var (int *d, const int *s, int n)
{
  for (int i = 0; i < n; i++)
    d[i] >>= s[i];
}

/* { dg-final { scan-assembler-times "\tssr\ta\[0-9\]+\n\tloop\t" 4 } } */
/* { dg-final { scan-assembler-times "\tssl\ta\[0-9\]+\n\tloop\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssai\t\[78\]\n\tloop\t" 2 } } */
/* { dg-final { scan-assembler-times "\tssr\t" 6 } } */
/* { dg-final { scan-assembler-times "\tssl\t" 2 } } */
