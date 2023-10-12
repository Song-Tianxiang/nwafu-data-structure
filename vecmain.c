#include "dynamic_array.h"

#include <stdio.h>

int main(void) {
  int n;
  int val;
  int i;
  int x;
  Vector vec;
  Vector wec;

  vec = vecini();
  /* printf("input n of values: "); */
  scanf("%d", &n);
  /* printf("input values: "); */
  while (n--) {
    scanf("%d", &val);
    vecapd(vec, val);
  }

  /* printf("input down\n"); */
  vecprt(vec);

  /* printf("input value: "); */
  scanf("%d", &x);
  /* printf("input index: "); */
  scanf("%d", &i);
  vecins(vec, i, x);
  vecprt(vec);

  /* printf("input delete index: "); */
  scanf("%d", &i);
  /* printf("deleted elem is: %d\n",vecdel(vec, i)); */
  vecprt(vec);

  vecinv(vec);
  /* printf("\tinversed: \t"); */
  vecprt(vec);

  wec = vecini();
  /* printf("input n of values: "); */
  scanf("%d", &n);
  /* printf("input values: "); */
  while (n--) {
    scanf("%d", &val);
    vecapd(wec, val);
  }

  /* printf("input down\n"); */
  /* printf("merged array is: \n"); */
  vecprt(vecmeg(vec, wec));
}
