/* { dg-do compile } */
/* { dg-options "-O2" } */

typedef unsigned int u32;

u32
shld_reg (u32 a, u32 b, int s)
{
  return (a << (s & 31)) | (b >> (-s & 31));
}

u32
shrd_reg (u32 a, u32 b, int s)
{
  return (a >> (s & 31)) | (b << (-s & 31));
}

u32
shld_const (u32 a, u32 b)
{
  return (a << 7) | (b >> 25);
}

u32
shrd_const (u32 a, u32 b)
{
  return (a >> 7) | (b << 25);
}

u32
shld_byte (u32 a, u32 b, int s)
{
  int c = (s * 8) & 31;
  return (a << c) | (b >> (-c & 31));
}

u32
shrd_byte (u32 a, u32 b, int s)
{
  int c = (s * 8) & 31;
  return (a >> c) | (b << (-c & 31));
}

/* { dg-final { scan-assembler-times "\tsrc\t" 6 } } */
/* { dg-final { scan-assembler-times "\tssl\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssr\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssai\t" 2 } } */
/* { dg-final { scan-assembler-times "\tssa8b\t" 1 } } */
/* { dg-final { scan-assembler-times "\tssa8l\t" 1 } } */
