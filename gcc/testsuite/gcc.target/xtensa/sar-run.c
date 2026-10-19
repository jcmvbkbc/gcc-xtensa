/* { dg-do run } */
/* { dg-require-effective-target xtensa_loops } */
/* { dg-options "-O2" } */

#define N 33

typedef unsigned int u32;

static u32 input[N];
static u32 input2[N];
static u32 result[N];
static u32 expected[N];

__attribute__ ((noipa)) static void
shift_right (u32 *out, const u32 *in, int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = in[i] >> s;
}

__attribute__ ((noipa)) static void
shift_left (u32 *out, const u32 *in, int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = in[i] << s;
}

__attribute__ ((noipa)) static void
rotate_right_7 (u32 *out, const u32 *in, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = (in[i] >> 7) | (in[i] << 25);
}

__attribute__ ((noipa)) static void
byte_swap (u32 *out, const u32 *in, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = __builtin_bswap32 (in[i]);
}

__attribute__ ((noipa)) static void
byte_shift_right_2 (u32 *out, const u32 *in, int s)
{
  out[0] = in[0] >> (s * 8);
  out[1] = in[1] >> (s * 8);
}

__attribute__ ((noipa)) static void
byte_shift_left_2 (u32 *out, const u32 *in, int s)
{
  out[0] = in[0] << (s * 8);
  out[1] = in[1] << (s * 8);
}

__attribute__ ((noipa)) static u32
funnel_right_value (u32 a, u32 b, int s)
{
  return (a >> (s & 31)) | (b << (-s & 31));
}

__attribute__ ((noipa)) static u32
funnel_left_value (u32 a, u32 b, int s)
{
  return (a << (s & 31)) | (b >> (-s & 31));
}

__attribute__ ((noipa)) static u32
funnel_right_7_value (u32 a, u32 b)
{
  return (a >> 7) | (b << 25);
}

__attribute__ ((noipa)) static u32
funnel_left_7_value (u32 a, u32 b)
{
  return (a << 7) | (b >> 25);
}

__attribute__ ((noipa)) static u32
byte_funnel_right_value (u32 a, u32 b, int s)
{
  int c = (s * 8) & 31;
  return (a >> c) | (b << (-c & 31));
}

__attribute__ ((noipa)) static u32
byte_funnel_left_value (u32 a, u32 b, int s)
{
  int c = (s * 8) & 31;
  return (a << c) | (b >> (-c & 31));
}

__attribute__ ((noipa)) static void
funnel_right (u32 *out, const u32 *a, const u32 *b, int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = funnel_right_value (a[i], b[i], s);
}

__attribute__ ((noipa)) static void
funnel_left (u32 *out, const u32 *a, const u32 *b, int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = funnel_left_value (a[i], b[i], s);
}

__attribute__ ((noipa)) static void
funnel_right_7 (u32 *out, const u32 *a, const u32 *b, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = funnel_right_7_value (a[i], b[i]);
}

__attribute__ ((noipa)) static void
funnel_left_7 (u32 *out, const u32 *a, const u32 *b, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = funnel_left_7_value (a[i], b[i]);
}

__attribute__ ((noipa)) static void
byte_funnel_right_2 (u32 *out, const u32 *a, const u32 *b, int s)
{
  out[0] = byte_funnel_right_value (a[0], b[0], s);
  out[1] = byte_funnel_right_value (a[1], b[1], s);
}

__attribute__ ((noipa)) static void
byte_funnel_left_2 (u32 *out, const u32 *a, const u32 *b, int s)
{
  out[0] = byte_funnel_left_value (a[0], b[0], s);
  out[1] = byte_funnel_left_value (a[1], b[1], s);
}

__attribute__ ((noipa)) static void
shift_nonzero (u32 *out, const u32 *in, int s, int n)
{
  for (int i = 0; i < n; ++i)
    if (in[i])
      out[i] = in[i] >> s;
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_right (u32 *out, const u32 *in, int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = in[i] >> s;
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_left (u32 *out, const u32 *in, int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = in[i] << s;
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_rotate_right_7 (u32 *out, const u32 *in, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = (in[i] >> 7) | (in[i] << 25);
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_byte_swap (u32 *out, const u32 *in, int n)
{
  for (int i = 0; i < n; ++i)
    {
      u32 x = in[i];
      out[i] = ((x & 0x000000ffU) << 24)
	       | ((x & 0x0000ff00U) << 8)
	       | ((x & 0x00ff0000U) >> 8)
	       | ((x & 0xff000000U) >> 24);
    }
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_byte_shift_right_2 (u32 *out, const u32 *in, int s)
{
  out[0] = in[0] >> (s * 8);
  out[1] = in[1] >> (s * 8);
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_byte_shift_left_2 (u32 *out, const u32 *in, int s)
{
  out[0] = in[0] << (s * 8);
  out[1] = in[1] << (s * 8);
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_funnel_right (u32 *out, const u32 *a, const u32 *b,
			int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = (a[i] >> s) | (b[i] << (32 - s));
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_funnel_left (u32 *out, const u32 *a, const u32 *b,
		       int s, int n)
{
  for (int i = 0; i < n; ++i)
    out[i] = (a[i] << s) | (b[i] >> (32 - s));
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_byte_funnel_right_2 (u32 *out, const u32 *a, const u32 *b,
			       int s)
{
  out[0] = (a[0] >> (s * 8)) | (b[0] << (32 - s * 8));
  out[1] = (a[1] >> (s * 8)) | (b[1] << (32 - s * 8));
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_byte_funnel_left_2 (u32 *out, const u32 *a, const u32 *b,
			      int s)
{
  out[0] = (a[0] << (s * 8)) | (b[0] >> (32 - s * 8));
  out[1] = (a[1] << (s * 8)) | (b[1] >> (32 - s * 8));
}

__attribute__ ((noipa, optimize ("O0"))) static void
reference_shift_nonzero (u32 *out, const u32 *in, int s, int n)
{
  for (int i = 0; i < n; ++i)
    if (in[i])
      out[i] = in[i] >> s;
}

static int
different (int n)
{
  for (int i = 0; i < n; ++i)
    if (result[i] != expected[i])
      return 1;
  return 0;
}

static void
clear_outputs (void)
{
  for (int i = 0; i < N; ++i)
    result[i] = expected[i] = 0xdeadbeefU;
}

int
main (void)
{
  u32 state = 0x6d2b79f5U;

  for (int i = 0; i < N; ++i)
    {
      state ^= state << 13;
      state ^= state >> 17;
      state ^= state << 5;
      input[i] = state;
      input2[i] = state ^ 0xa5a5a5a5U;
    }
  input[0] = 0;
  input[1] = 0xffffffffU;
  input[2] = 0x80000000U;
  input[3] = 1;

  for (int n = 0; n <= N; ++n)
    for (int s = 0; s < 32; ++s)
      {
	clear_outputs ();
	shift_right (result, input, s, n);
	reference_right (expected, input, s, n);
	if (different (N))
	  return 1;

	clear_outputs ();
	shift_left (result, input, s, n);
	reference_left (expected, input, s, n);
	if (different (N))
	  return 2;

	clear_outputs ();
	shift_nonzero (result, input, s, n);
	reference_shift_nonzero (expected, input, s, n);
	if (different (N))
	  return 3;

	if (s != 0)
	  {
	    clear_outputs ();
	    funnel_right (result, input, input2, s, n);
	    reference_funnel_right (expected, input, input2, s, n);
	    if (different (N))
	      return 8;

	    clear_outputs ();
	    funnel_left (result, input, input2, s, n);
	    reference_funnel_left (expected, input, input2, s, n);
	    if (different (N))
	      return 9;
	  }
      }

  for (int n = 0; n <= N; ++n)
    {
      clear_outputs ();
      rotate_right_7 (result, input, n);
      reference_rotate_right_7 (expected, input, n);
      if (different (N))
	return 4;

      clear_outputs ();
      funnel_right_7 (result, input, input2, n);
      reference_funnel_right (expected, input, input2, 7, n);
      if (different (N))
	return 12;

      clear_outputs ();
      funnel_left_7 (result, input, input2, n);
      reference_funnel_left (expected, input, input2, 7, n);
      if (different (N))
	return 13;

      clear_outputs ();
      byte_swap (result, input, n);
      reference_byte_swap (expected, input, n);
      if (different (N))
	return 5;
    }

  for (int s = 0; s < 4; ++s)
    {
      clear_outputs ();
      byte_shift_right_2 (result, input, s);
      reference_byte_shift_right_2 (expected, input, s);
      if (different (N))
	return 6;

      clear_outputs ();
      byte_shift_left_2 (result, input, s);
      reference_byte_shift_left_2 (expected, input, s);
      if (different (N))
	return 7;

      if (s != 0)
	{
	  clear_outputs ();
	  byte_funnel_right_2 (result, input, input2, s);
	  reference_byte_funnel_right_2 (expected, input, input2, s);
	  if (different (N))
	    return 10;

	  clear_outputs ();
	  byte_funnel_left_2 (result, input, input2, s);
	  reference_byte_funnel_left_2 (expected, input, input2, s);
	  if (different (N))
	    return 11;
	}
    }

  return 0;
}
