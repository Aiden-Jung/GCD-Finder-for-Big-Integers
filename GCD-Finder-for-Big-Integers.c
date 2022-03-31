// C libraries
#include <stdio.h>
#include <gmp.h>

/* The function for this algorithm
 * The description is below the main function
 */
void extended_euclid(mpz_t a, mpz_t b, mpz_t *result);

//The main function
int main () {

  //Declare and initialize variables to store the three given numbers
  mpz_t a, b, c;
  mpz_init_set_str(a,"237860119462919774697968259", 10);
  mpz_init_set_str(b,"272314462066588884618061856", 10);
  mpz_init_set_str(c,"164705119724434", 10);

  //Declare and initialize variables to store the quotient and the remainder of c/gcd(a,b)
  mpz_t q, r;
  mpz_init(q);
  mpz_init(r);
  
  //Declare and initialize an array to store the result of extended_euclid
  mpz_t result[3];
  mpz_init(result[0]);
  mpz_init(result[1]);
  mpz_init(result[2]);

  //Pass the two given numbers and an array pointer to store the result
  extended_euclid(a, b, result);

  //Print gcd(a,b)
  gmp_printf("The greatest common divisor of %Zd and %Zd is %Zd\n\n", a, b, result[0]);

  /* By Theorem 31.2 on the textbook, c can be expressed as a linear combination of a and b
   * if c is a multiple of gcd(a,b)
   */

  //Find the quotient and the remainder of c/gcd(a,b)
  mpz_fdiv_qr(q, r, c, result[0]);

  //If the remainder of c/gcd(a,b) is 0, c can be expressed as a linear combination of a and b
  if(mpz_sgn(r)==0){

    printf("%Zd can be expressed as a linear combination of %Zd and %Zd\n\n", c, a, b);

    //We can find x and y such that c=ax+by by multiplying x' and y' such that gcd(a,b)=ax'+by' by c/gcd(a,b)
    mpz_mul(result[1], result[1], q);
    mpz_mul(result[2], result[2], q);
    gmp_printf("%Zd = %Zd * %Zd + %Zd * %Zd\n\n", c, result[1], a, result[2], b);

    //Check whether ax+by is equal to c
    mpz_mul(result[1], result[1], a);
    mpz_mul(result[2], result[2], b);
    mpz_add(result[1], result[1], result[2]);

    if(mpz_cmp(result[1],c)==0){
      printf("The linear combination is correct.\n");
    }else{
      printf("The linear combination is incorrect.\n");
    }

    //If the remainder of z/gcd(x,y) is not 0, z cannot be expressed as a linear combination of x and y
  }else{
    printf("The number cannot be expressed as a linear combination of the other two numbers\n");
  }
  
  //End the program
  return 0;
  
}

/* @Name   extended_euclid
 * @brief  Find the greatest common divisor of the given two numbers
 * @param  a, a mpz_t number
 *         b, a mpz_t number
 *         result, a mpz_t array pointer to store the result
 * @pre    a and b are nonegative integers
 *         result is a mpz_t array whose size is greater than or equal to 3
 * @post   result[0], result[1], and result[2] store d,x, and y such that d=gcd(a,b)=ax+by, respectively. 
 */
void extended_euclid(mpz_t a, mpz_t b, mpz_t *result){

  //Declare and initialize variables to store a quotient and a remainder of a/b
  mpz_t q, r;
  mpz_init(q);
  mpz_init(r);
  
  //Declare and initialize a temp array to store d,x, and y such that d=gcd(a,b)=ax+by in each loop
  mpz_t temp[3];
  mpz_init(temp[0]);
  mpz_init(temp[1]);
  mpz_init(temp[2]);

  //EXTENDED-EUCLID algorithm based on the pseudocode in the textbook
  if(mpz_sgn(b)==0){
    mpz_set(result[0], a);
    mpz_set_ui(result[1],(unsigned long int)1);
    mpz_set_ui(result[2],(unsigned long int)0);
  }else{
    mpz_fdiv_qr(q,r,a,b);
    extended_euclid(b,r,temp);
    mpz_set(result[0], temp[0]);
    mpz_set(result[1], temp[2]);
    mpz_set(result[2], temp[1]);
    mpz_submul(result[2],q,temp[2]);
  }
}
