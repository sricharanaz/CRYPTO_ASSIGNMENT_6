# CRYPTO_ASSIGNMENT_6
CRYPTO_ASSIGNMENT_6

COMPILE:
-------
  sudo apt-get install libgmp3-dev
  gcc -o dsa digsa.c -lgmp -lcrypto
  
  
  EXECUTION:
  ---------
  
   ./dsa

 ------------ Signing -------------
Enter a text(number) to sign:5
sign s1: 18
sign s2: 81


------------- Verifying -------------
verifying message 5 with sign (s1,s2) (18, 81)
v: 18
s1: 18

 Verification succeded...
