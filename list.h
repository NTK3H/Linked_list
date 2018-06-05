/* Date:	2018/6/5
 * Author:	Truth <2568878009@qq.com>
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef __FN_LIST_H
#define __FN_LIST_H
#endif

#ifndef	LIST_TYPE
#define LIST_TYPE	int
#endif

#if LIST_TYPE==float || LIST_TYPE==double
#include <math.h>
#include <float.h>
#endif

#ifdef LIST_SUPPORT_HASHMAP
#include <string.h>
#endif

typedef struct _list_struct_mem{
	LIST_TYPE mem;
	struct _list_struct_mem *next;
}mlist;

#pragma pack(4)
#ifdef LIST_SUPPORT_HASHMAP
typedef struct _list_hash_map{
	int index;
	char *str;
	struct _list_hash_map *last;
	struct _list_hash_map *next;
}mhp;
#endif

typedef struct _list_struct_head{
	int size;
#ifdef LIST_SUPPORT_HASHMAP
	int hashsize;
	mhp *hashmap;
#endif
	mlist *first;
}list;
#pragma pop

list *list_init();
LIST_TYPE list_var(list *nlist, int index);
int list_insert(list *nlist, LIST_TYPE iMem, int index);
int list_push_back(list *nlist, LIST_TYPE iMem);
int list_push_front(list *nlist, LIST_TYPE iMem);
int list_size(list *nlist);
int list_erase(list *nlist, int size, int index);
int list_change(list *nlist, LIST_TYPE iNewMem, int index);
int list_indexof(list *nlist, LIST_TYPE iMem);
int list_last_indexof(list *nlist, LIST_TYPE iMem);
int list_equal(list *flist,list *slist);
int *list_listtoarray(list *nlist);
list *list_arraytolist(int *arr, int size);
mlist *list_begin(list *nlist);
mlist *list_end(list *nlist);
int *list_swap(list *xlist, list *ylist);
int list_test(list *nlist, LIST_TYPE var, int index);
int list_clear(list *nlist);
int list_empty(list *nlist);
int list_delete(list *nlist);

#ifdef LIST_SUPPORT_HASHMAP
int list_hashlink(list *nlist, char* key, int index);
int list_hashindex(list *nlist, char* key);
char* list_hashstring(list *nlist, int index);
LIST_TYPE list_hashvar(list *nlist, char* key);
int list_hashdel(list *nlist, char* key);
int list_hashsize(list *nlist);
#endif
