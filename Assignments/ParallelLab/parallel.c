//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Brandon Truong
 * UCLA ID : 
 * Email : brandonztruong@g.ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;

  //my declarations
  const int dim_sq = DIM * DIM;
  const int bsize=4;
  const int limit = DIM - 1;
  int ii=0,jj=0,kk=0,addy=0,tempaddy=0;
  long holder=0;
  long x0=histogrammy[0],x1=histogrammy[1],x2=histogrammy[2],x3=histogrammy[3],x4=histogrammy[4],x5=histogrammy[5],x6=histogrammy[6],x7=histogrammy[7],x8=histogrammy[8],x9=histogrammy[9];
  //leave first part alone, minor change to speed
  for(i=0; i<limit;i++)
  {
    super[i] += simple[i];
  }
  for(i=0; i<limit;i++)
  {
    dot_product += super[i]*simple[i];
    
    moving_average = 0;
    for(ton=i;ton<limit-WINDOW_SIZE;ton++)
    {
      moving_average += simple[ton];
    }
  }
  int a_secret = 5;
  fibonacci[0] = 1;
  fibonacci[1] = 1;
  for(i=2; i<limit;i++)
  {
    fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
    if(i==3)
    {
      printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
    }
  }
  step = 1.0 / NUM_STEPS;
  for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 
  
  //Take out r*r, doesn't change
  double r_sq = r*r;
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= r_sq) {
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

//pragma for separating into threads
#pragma omp parallel for private(j, k, ii, jj, kk, u, v, w, compute_it, addy, tempaddy) reduction (+:aggregate) reduction (+:holder) reduction (+:x0, x1, x2, x3, x4, x5, x6, x7, x8, x9)
//change code here
  for (i=1; i<limit; i+=bsize) {
    for (j=1; j<limit; j+=bsize) {
      for (k=1; k<limit; k+=bsize) {
        //Blocked matrix
        for (ii = i; ii < i + bsize && ii < limit; ii++) {
				  for (jj = j; jj < j + bsize && jj < limit; jj++) {
            for(kk = k; kk < k + bsize && kk < limit; kk++) {
              addy = ii*dim_sq+jj*DIM+kk;
              compute_it = old[addy] * we_need_the_func();
              aggregate += compute_it / gimmie_the_func();
              //use var holder instead of new[addy] to avoid time wasted finding address and accessing
              holder = 0;
              for(v=-1;v<=1;v++) {
                //reduce multiplication and use of for loops
                switch(v) {
                  case -1: tempaddy = addy - dim_sq; break;
                  case 0: tempaddy = addy; break;
                  case 1: tempaddy = addy + dim_sq; break;
                }
                //-1
                tempaddy -= DIM;
                holder += old[tempaddy-1];
                holder += old[tempaddy];
                holder += old[tempaddy+1];
                //+0
                tempaddy += DIM;
                holder += old[tempaddy-1];
                holder += old[tempaddy];
                holder += old[tempaddy+1];
                //+1
                tempaddy += DIM;
                holder += old[tempaddy-1];
                holder += old[tempaddy];
                holder += old[tempaddy+1];
              }

              holder/=27;
              new[addy] = holder;
              u=(holder/100);

              if (u<=0) u=0;
              if (u>=9) u=9;
              //use variables to avoid computing address of histogrammy, optimize should use registers to store, then place in address after done.
              switch(u) {
                case 0: x0++;
                break;
                case 1: x1++;
                break;
                case 2: x2++;
                break;
                case 3: x3++;
                break;
                case 4: x4++;
                break;
                case 5: x5++;
                break;
                case 6: x6++;
                break;
                case 7: x7++;
                break;
                case 8: x8++;
                break;
                case 9: x9++;
                break;
                default: break;
              }
            }
          }
        }
      }
    }
  }
  //store variables into designated addresses, quicker than continuously accessing and computing the addresses.
  histogrammy[0] = x0;
  histogrammy[1] = x1;
  histogrammy[2] = x2;
  histogrammy[3] = x3;
  histogrammy[4] = x4;
  histogrammy[5] = x5;
  histogrammy[6] = x6;
  histogrammy[7] = x7;
  histogrammy[8] = x8;
  histogrammy[9] = x9;
  printf("AGGR:%ld\n",aggregate);
  return (double) (dot_product+moving_average+pi+pi2);


}
