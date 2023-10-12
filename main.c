#include "single_list.h"
#include <stdio.h>

int main(void) {
  int c; /* count of number */
  int n; /* inserted number */
  List list;
  List lt;                      /* list for merge */
  int i;
  int x;

  /* list initial */
  list = lstini();
  i = 0;
  /* down order */
  /* printf("\tinput the number of elements: "); */
  scanf("%d", &c);
  /* printf("\tinput element(s): "); */
  while (++i <= c) {
    scanf("%d", &n);
    lstins(list, i, n);
  }

  /* list insert */
  /* printf("\tinput insert value: "); */
  scanf("%d", &x);
  /* printf("\tinput insert index: "); */
  scanf("%d", &i);
  lstins(list, i, x);
  lstprt(list);

  /* list delete */
  /* printf("\tinput delete index: "); */
  scanf("%d", &i);
  lstdel(list, i);
  lstprt(list);

  /* list search */
  /* printf("\tinput search value: "); */
  scanf("%d", &x);
  i = lstser(list, x);
  if (i) {
    printf("%d\n", i);
  } else {
    printf("Not found\n");
  }

  /* list inverse */
  lstinv(list);
  /* printf("\tinversed list: \n"); */
  lstprt(list);

  /* a new list, prepare for merge */
  lt = lstini();
  i = 0;
  /* up order */
  /* printf("\tinput the number of elements: "); */
  scanf("%d", &c);
  /* printf("\tinput element(s): "); */
  while (++i <= c) {
    scanf("%d", &n);
    lstins(lt, i, n);
  }

  /* merge two list */
  /* printf("\tmerged two list: "); */
  lstmeg(list, lt);
  lstprt(list);
}
