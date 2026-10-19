/* { dg-do compile } */
/* { dg-options "-O2" } */

/* count is 8 on this path, and the funnel shift also wants SAR = 8.
   ssai must stay an immediate.  A register is not a valid %R operand.  */

void
ssai_keeps_immediate (unsigned char *out, unsigned long long block,
		      unsigned count)
{
  if (count == 8)
    {
      out[0] = block >> 32;
      out[1] = block >> 24;
      out[2] = block >> 16;
      out[3] = block >> 8;
      out[4] = block;
    }
}

/* { dg-final { scan-assembler "ssai\t8" } } */
