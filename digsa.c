#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <openssl/sha.h>
#include <gmp.h>

mpz_t p, m, q, e0, e1, e2, d, r, s1, s2, p_minus_1_div_q, hm, ds1, v, s2_inv, e1_p, e2_p, r_inv, s_1;

void signing()
{
  /* Signing Algorithm */
  mpz_set_ui(p, 8081);

  mpz_set_ui(q, 101);
  mpz_set_ui(e0, 3);
  mpz_sub_ui(p_minus_1_div_q, p, 1);
  mpz_divexact(p_minus_1_div_q, p_minus_1_div_q, q);

  mpz_powm(e1, e0, p_minus_1_div_q, p);

  mpz_set_ui(d, 61);
  mpz_powm(e2, e1, d, p);

  mpz_set_ui(r, 61);
  mpz_powm(s1, e1, r, p);
  mpz_mod(s1, s1, q);

  gmp_printf("Enter a text(number) to sign:");
  gmp_scanf("%Zd", m);

  mpz_mul(ds1, d, s1);
  mpz_add(s2, ds1, m); // we take the message itself as the digest.
  mpz_invert(r_inv, r, q);
  mpz_mul(s2, s2, r_inv);
  mpz_mod(s2, s2, q);
  gmp_printf("sign s1: %Zd", s1);
  gmp_printf("\nsign s2: %Zd", s2);
}

void verifying()
{

  
  gmp_printf("verifying message %Zd with sign (s1,s2) (%Zd, %Zd)\n", m,s1,s2);
  /* Verifying */
  mpz_invert(s2_inv, s2, q);
  mpz_mul(e1_p, m, s2_inv);
  mpz_mod(e1_p, e1_p, q);
  mpz_pow_ui(e1_p, e1, mpz_get_ui(e1_p));

  mpz_mul(e2_p, s1, s2_inv);
  mpz_mod(e2_p, e2_p, q);
  mpz_pow_ui(e2_p, e2, mpz_get_ui(e2_p));
  mpz_mul(v, e1_p, e2_p);
  mpz_mod(v, v, p);
  mpz_mod(v, v, q);
  gmp_printf("v: %Zd\n", v);
  gmp_printf("s1: %Zd\n", s1);

  if(mpz_cmp(s1, v) == 0) {
    gmp_printf("\n Verification succeded...\n");
  } else
  {
    gmp_printf("\n Verification failed...\n");
  }

}

int main()
{
  mpz_inits(p, m, q, e0, e1, e2, d, r, s1, s2, p_minus_1_div_q, hm, ds1, v, s2_inv, e1_p, e2_p, r_inv, NULL);


      printf("\n ------------ Signing -------------\n");
      signing();

      printf("\n\n\n------------- Verifying -------------\n");
      verifying();


  mpz_clears(p, m, q, e0, e1, e2, d, r, s1, s2, p_minus_1_div_q, hm, ds1, v, s2_inv, e1_p, e2_p, r_inv, NULL);
  return 0;
}
