#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node Node;
typedef Node *Link;
typedef Link List;

List lstini(void);
List lstmeg(List, List);
int lstser(List, ElemType);
int lstsize(List);
void lstinv(List);
void lstins(List, int, ElemType);
ElemType *lsttra(List);
ElemType lstdel(List, int);

struct node {
  ElemType elem;
  Link next;
};

/* print error message ant quit */
void perror(const char *str) {
  fprintf(stderr, "%s", str);
  exit(EXIT_FAILURE);
}

/* list create */
List lstini(void) {
  List list;

  list = (List)malloc(sizeof(Node));
  list->next = NULL;

  return list;
}

/* get list size */
int lstsize(List lst) {
  int size;
  Link cnode;

  size = 0;
  cnode = lst->next;
  while ((cnode)) {
    size++;
    cnode = cnode->next;
  }
  return size;
}

/* auxiliary function: check 1 based index is valid */
void lstichk(List lst, int idx, int tweak) {
  if ((idx < 1) || (idx > lstsize(lst) + tweak))
    perror("lstins: invalid index");
}

/* auxiliary function: get a link point to index-1 node, 1 based index*/
Link lstfidx(List lst, int idx) {
  Link cnode; /* current pointed node */

  cnode = lst;
  while (--idx) { /* make cnode point to node at index-1 */
    cnode = cnode->next;
  }
  return cnode;
}

/* insert element to list at 1 based index */
void lstins(List lst, int idx, ElemType elem) {
  Link pnode; /* pre node of index */
  Link nnode; /* created new node */

  lstichk(lst, idx, 1); /* check index */

  pnode = lstfidx(lst, idx);

  nnode = (Link)malloc(sizeof(Node));
  nnode->next = pnode->next;
  pnode->next = nnode;

  nnode->elem = elem;
}

/* delete the node at 1-based index */
ElemType lstdel(List lst, int idx) {
  ElemType elem;
  Link pnode;
  Link dnode; /* the node to be delete */

  lstichk(lst, idx, 0);

  pnode = lstfidx(lst, idx);
  dnode = pnode->next;
  pnode->next = dnode->next;

  elem = dnode->elem;
  free(dnode);

  return elem;
}

/* return the 1-based index of elem in lst */
/* return 0 if not find */
int lstser(List lst, ElemType elem) {
  int idx;
  int size;
  Link cnode;

  if (lst->next)
    cnode = lst->next;
  else
    return 0;

  size = lstsize(lst);
  for (idx = 1; idx <= size; ++idx) {
    if (cnode->elem == elem)
      return idx;
    else
      cnode = cnode->next;
  }
  return 0;
}

/* list traverse, return an array on heap, be careful */
/* do not forget free */
/* on heap instead of stack because array size only be known at run time */
ElemType *lsttra(List lst) {
  ElemType *earray; /* element array to store elements of list */
  Link cnode;
  int i; /* elem array index */
  int size;

  size = lstsize(lst);
  earray = (ElemType *)calloc((size_t)size, sizeof(ElemType));
  cnode = lst->next;
  for (i = 0; i < size; i++) {
    earray[i] = cnode->elem;
    cnode = cnode->next;
  }

  return earray;
}

/* inverse list */
void lstinv(List lst) {
  Link fnode; /* initial first node, not change */
  Link snode; /* awayls the second node of current list, change while loop */

  fnode = lst->next;
  if (fnode == NULL) /* if lst is NULL, no need to reverse */
    return;

  /* if fnode is the last node, inverse is down */
  while ((snode = fnode->next)) {
    fnode->next = snode->next; /* fnode right move */
    snode->next = lst->next;   /* snode link to prior first node */
    lst->next = snode; /* list point to snode, snode become the first node */
  }
}

/* merge two list */
/* just append lt to ls */
List lstmeg(List l, List r) {
  Link lnode; /* destination node */
  Link rnode; /* node be appended */
  Link tmpn;  /* tmp node */

  lnode = l;
  rnode = r->next;
  free(r);

  while (rnode && lnode->next) {
    if ((rnode->elem) >= (lnode->next->elem)) {
      lnode = lnode->next;
    } else {
      tmpn = rnode->next;
      rnode->next = lnode->next;
      lnode->next = rnode;
      rnode = tmpn;
    }
  }

  if (rnode) {
    lnode->next = rnode;
  }

  return l;
}

void lstprt(List lst) {
  ElemType *array;
  int i;

  array = lsttra(lst);
  printf("%d", array[0]);
  for (i = 1; i < lstsize(lst); i++)
    printf(" %d", array[i]);
  printf("\n");
  free(array);
}

#endif /* SINGLE_LIST_H */
