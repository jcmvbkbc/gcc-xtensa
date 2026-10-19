/* { dg-do compile } */
/* { dg-require-effective-target xtensa_loops } */
/* { dg-options "-O2 -fno-tree-pre -fno-gcse -fno-tree-loop-im -fno-move-loop-invariants" } */

/* Keep the byte-scaled shift amount in the shift expression so that
   SSA8L and SSA8B, rather than SSR and SSL, are tested.  */

void
srl8 (unsigned int *d, int s, int n)
{
  for (int i = 0; i < n; i++)
    d[i] >>= s * 8;
}

void
sll8 (unsigned int *d, int s, int n)
{
  for (int i = 0; i < n; i++)
    d[i] <<= s * 8;
}

/* { dg-final { scan-assembler-times "\tssa8l\ta\[0-9\]+\n\tloop\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssa8b\ta\[0-9\]+\n\tloop\t" 1 } } */
/* { dg-final { scan-assembler-not "\tssr\t" } } */
/* { dg-final { scan-assembler-not "\tssl\t" } } */
