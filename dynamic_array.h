#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE (INT_MAX - 8)
typedef int ElemType;

typedef struct vector *Vector;
typedef ElemType *Vecarr;

Vector vecini(void);
Vector vecmeg(Vector, Vector);
int vecser(Vector, ElemType);
void vecinv(Vector);
void vecins(Vector, int, ElemType);
void vecapd(Vector, ElemType);
ElemType lstdel(Vector, int);

struct vector {
  int sz;     /* size */
  int cap;    /* capacity */
  Vecarr arr; /* array */
};

/* print error message and quit */
void perror(const char *str) {
  fprintf(stderr, "%s", str);
  exit(EXIT_FAILURE);
}

/* auxiliary function, swap two elem */
void swap(ElemType *e, ElemType *f) {
  ElemType tmp;

  tmp = *e;
  *e = *f;
  *f = tmp;
}
int min(int m, int n) { return m < n ? m : n; }
int max(int m, int n) { return m > n ? m : n; }

Vector vecini(void) {
  Vector vec;

  vec = (Vector)malloc(sizeof(struct vector));
  vec->sz = 0;
  vec->cap = 0;
  vec->arr = NULL;

  return vec;
}

void vececap(Vector vec, int mincap) {
  /* Overflow-conscious code */
  /* ref: openjdk ensureCapacity() */
  int ocap;
  int ncap;
  Vecarr oarr;
  Vecarr narr;
  int i;

  ocap = vec->cap;
  if (!(mincap - ocap > 0))
    return;
  ncap = ocap + (ocap >> 1); /* multiplex 1.5 */
  if (ncap - mincap < 0)
    ncap = mincap;
  if (ncap - MAX_ARRAY_SIZE > 0) {
    if (mincap < 0) /* overflow */
      perror("vececap: cap invalid");
    ncap = (mincap > MAX_ARRAY_SIZE) ? INT_MAX : MAX_ARRAY_SIZE;
  }

  /* copy array */
  vec->cap = ncap;
  oarr = vec->arr;
  narr = (Vecarr)calloc((size_t)vec->cap, sizeof(ElemType));
  for (i = 0; i < vec->sz; i++) {
    narr[i] = oarr[i];
  }
  vec->arr = narr;
  free(oarr);
}

/* typedef enum direct{ */
/*   left = -1, */
/*   right = 1 */
/* } Direct; */

/* vector round */
ElemType vecround(Vector vec, int from, int to) {
  Vecarr array;
  int i;

  if (min(from, to) < 1 || max(from, to) > vec->sz)
    perror("vecshf: invalid low and high");

  array = vec->arr;
  if (to - from > 0) /* left to right */
    for (i = to; i > from; i--) {
      swap(array + i - 1, array + i - 1 - 1);
    }
  else if (to - from < 0)
    for (i = to; i < from; i++) { /* right to left */
      swap(array + i - 1, array + i - 1 + 1);
    }
  return array[from - 1];
}

/* insert elem at 1-based index */
void vecins(Vector vec, int idx, ElemType elem) {
  int nsize; /* new size */

  nsize = max(vec->sz + 1, idx);
  vececap(vec, nsize); /* change cap */
  vec->sz = nsize;     /* change size */
  vecround(vec, idx, nsize);
  vec->arr[idx - 1] = elem; /* change arr */
}

void vecapd(Vector vec, ElemType elem) { vecins(vec, vec->sz + 1, elem); }

ElemType vecdel(Vector vec, int idx) {
  ElemType delem; /* deleted element */

  if ((idx > vec->sz) || (idx < 1))
    perror("vecdel: invalid index");

  delem = vecround(vec, vec->sz, idx);
  vec->sz -= 1;
  return delem;
}

/* search the rank of elem */
int vecser(Vector vec, ElemType elem) {
  int i;

  for (i = 0; i < vec->sz - 1; i++) {
    if (vec->arr[i] == elem)
      return i + 1;
  }
  return 0;
}

void vecinv(Vector vec) {
  int i;

  for (i = 1; i < vec->sz; i++) {
    vecround(vec, i, vec->sz);
  }
}

Vector vecmeg(Vector v, Vector w) {
  int i; /* v index */
  int j; /* w index */
  Vector nvec;

  nvec = vecini();

  i = j = 0;
  /* compare v and w, choose the smaller one */
  while (i < v->sz && j < w->sz) {
    vecapd(nvec, min(v->arr[i], w->arr[j]));
    v->arr[i] < w->arr[j] ? i++ : j++;
  }

  /* if v left some max num */
  while (i < v->sz) {
    vecapd(nvec, v->arr[i++]);
  }

  /* if w left some max num */
  while (j < w->sz) {
    vecapd(nvec, w->arr[j++]);
  }

  free(v->arr);
  free(v);
  free(w->arr);
  free(w);
  return nvec;
}

void vecprt(Vector vec) {
  int i;
  int size;
  Vecarr array;

  size = vec->sz;
  array = vec->arr;
  for (i = 0; i < size - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[size - 1]); /* last one should careful deal with */
}

#endif /* DYNAMIC_ARRAY_H */
