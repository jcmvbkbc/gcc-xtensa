/* { dg-do run } */
/* { dg-require-effective-target xtensa_mac16 } */
/* { dg-options "-O2" } */

/* Value checks for corners the assembler scans do not pin down:
   a shared result/addend/factor register, an unsigned 16x16 product
   with the sign bit set, and a negative high half.  */

__attribute__ ((noipa)) int
mac_same (int c, int b)
{
  return c + (short) c * (short) b;
}

__attribute__ ((noipa)) int
mas_same (int c, int b)
{
  return c - (short) c * (short) b;
}

__attribute__ ((noipa)) unsigned
mac_u (unsigned c, unsigned a, unsigned b)
{
  return c + (unsigned short) a * (unsigned short) b;
}

__attribute__ ((noipa)) unsigned
mas_u (unsigned c, unsigned a, unsigned b)
{
  return c - (unsigned short) a * (unsigned short) b;
}

__attribute__ ((noipa)) int
mul_hh (int a, int b)
{
  return (a >> 16) * (b >> 16);
}

__attribute__ ((noipa)) unsigned
umul_hh (unsigned a, unsigned b)
{
  return (a >> 16) * (b >> 16);
}

__attribute__ ((noipa)) int
mul_hl (int a, int b)
{
  return (a >> 16) * (short) b;
}

__attribute__ ((noipa)) unsigned
umul_hl (unsigned a, unsigned b)
{
  return (a >> 16) * (b & 0xffff);
}

__attribute__ ((noipa)) int
mul_lh (int a, int b)
{
  return (short) a * (b >> 16);
}

__attribute__ ((noipa)) int
mula_hh (int s, int a, int b)
{
  return s + (a >> 16) * (b >> 16);
}

__attribute__ ((noipa)) int
muls_hh (int s, int a, int b)
{
  return s - (a >> 16) * (b >> 16);
}

__attribute__ ((noipa)) unsigned
umula_hh (unsigned s, unsigned a, unsigned b)
{
  return s + (a >> 16) * (b >> 16);
}

__attribute__ ((noipa)) unsigned
umuls_hh (unsigned s, unsigned a, unsigned b)
{
  return s - (a >> 16) * (b >> 16);
}

int
main (void)
{
  int hi_neg = -2147483647 - 1;

  /* Clobbering the shared register yields 2 * product, or 0 for subtract.  */
  if (mac_same (3, 4) != 15)
    return 1;
  if (mac_same (-2, 5) != -12)
    return 2;
  if (mac_same (-32768, -1) != 0)
    return 3;
  if (mas_same (3, 4) != -9)
    return 4;
  if (mas_same (-2, 5) != 8)
    return 5;
  if (mas_same (-32768, 2) != 32768)
    return 6;

  /* 0xffff * 0xffff = 0xfffe0001, so bit 31 of the unsigned product is set.  */
  if (mac_u (0, 0xffff, 0xffff) != 0xfffe0001u)
    return 7;
  if (mas_u (100, 0xffff, 2) != 100u - 131070u)
    return 8;

  /* High half of INT_MIN is -32768 signed and 32768 unsigned.  */
  if (mul_hh (hi_neg, 3 << 16) != -98304)
    return 9;
  if (umul_hh (0x80000000u, 3u << 16) != 98304u)
    return 10;
  if (mul_hl (hi_neg, -2) != 65536)
    return 11;
  if (umul_hl (0x80000000u, 0xffffu) != 2147450880u)
    return 12;
  if (mul_lh (-2, hi_neg) != 65536)
    return 13;
  if (mula_hh (5, hi_neg, 1 << 16) != -32763)
    return 14;
  if (muls_hh (5, hi_neg, 1 << 16) != 32773)
    return 15;
  if (umula_hh (5, 0x80000000u, 1u << 16) != 32773u)
    return 16;
  if (umuls_hh (5, 0x80000000u, 1u << 16) != 5u - 32768u)
    return 17;

  return 0;
}
