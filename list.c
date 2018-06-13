/* Date:	2018/6/5
 * Author:	Truth <2568878009@qq.com>
 */

#include "list.h"

list *list_init()
{
	list *init = (list*)malloc(sizeof(list));
	init->size = 0;
#ifdef LIST_SUPPORT_HASHMAP
	init->hashmap = NULL;
	init->hashsize = 0;
#endif
	init->first = NULL;
	return init;
}

#ifdef LIST_SUPPORT_HASHMAP
int list_hashlink(list *nlist, char* map, int index)
{
	mhp *thp = NULL;
	if(nlist->hashmap == NULL)
	{
		nlist->hashmap = (mhp*)malloc(sizeof(mhp));
		thp = nlist->hashmap;
		thp->index = index;
		thp->str = (char*)malloc(sizeof map);
		strcpy(thp->str,map);
		thp->next = NULL;
		thp->last = thp;
	}
	else
	{
		thp = nlist->hashmap;
		for(int i=1;i<nlist->hashsize;i++)
			thp = thp->next;
		thp->next = (mhp*)malloc(sizeof(mhp));
		thp->next->last = thp;
		thp = thp->next;
		thp->index = index;
		thp->str = (char*)malloc(sizeof map);
		strcpy(thp->str,map);
		thp->next = NULL;
	}
	nlist->hashsize++;
	return 1;
}

int list_hashindex(list *nlist, char* key)
{
	if(nlist->hashmap != NULL)
	{
		mhp *thp = nlist->hashmap;
		for(int i=0;i<nlist->hashsize;i++)
		{
			if(0 == strcmp(thp->str,key))
				return thp->index;
			thp = thp->next;
		}
	}
	return -1;
}

char* list_hashstring(list *nlist, int index)
{
	if(nlist->hashmap != NULL)
	{
		mhp *thp = nlist->hashmap;
		for(int i=0;i<nlist->hashsize;i++)
		{
			if(thp->index == index)
				return thp->str;
			thp = thp->next;
		}
	}
	return NULL;
}

int list_hashdel(list *nlist, char* key)
{
	if(nlist->hashmap != NULL)
	{
		mhp *thp = nlist->hashmap;
		for(int i=0;i<nlist->hashsize;i++)
		{
			if(0 == strcmp(thp->str,key))
			{
				if(thp->last == thp)
				{
					nlist->hashmap = thp->next;
					nlist->hashmap->last = nlist->hashmap;
				}
				else
				{
					thp->last->next = thp->next;
					if(thp->next != NULL) thp->next->last = thp->last;
				}
				nlist->hashsize--;
				free(thp);
				return 1;
			}
			thp = thp->next;
		}
	}
	return 0;
}

LIST_TYPE list_hashvar(list *nlist, char* key)
{
	return list_var(nlist, list_hashindex(nlist, key));
}

int list_hashsize(list *nlist)
{
	return nlist->hashsize;
}
#endif

LIST_TYPE list_var(list *nlist, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	for(int i=0;i<index;i++)
		m = m->next;
	return m->mem;
}

int list_insert(list *nlist, LIST_TYPE iMem, int index)
{
	if(index>nlist->size)return 0;
	if(nlist->size == 0)
	{
		nlist->first = (mlist*)malloc(sizeof(mlist));
		nlist->first->mem = iMem;
		nlist->size++;
		return 1;
	}
	if(index == 0)
	{
		mlist *m_bkf = nlist->first;
		nlist->first = (mlist*)malloc(sizeof(mlist));
		nlist->first->mem = iMem;
		nlist->first->next = m_bkf;
		nlist->size++;
		return 1;
	}
	mlist *m = nlist->first;
	for(int i=1;i<index;i++)
		m = m->next;
	mlist *m_bkf = m->next;
	m->next = (mlist*)malloc(sizeof(mlist));
	m = m->next;
	m->mem = iMem;
	m->next = m_bkf;
	nlist->size++;
	return 1;
}

int list_push_back(list *nlist, LIST_TYPE iMem)
{
	list_insert(nlist,iMem,nlist->size);
}

int list_push_front(list *nlist, LIST_TYPE iMem)
{
	list_insert(nlist,iMem,0);
}

int list_size(list *nlist)
{
	if(nlist == NULL)return 0;
	return nlist->size;
}

int list_erase(list *nlist, int size, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	if(index == 0)
	{
		for(int i=0;i<size;i++)
		{
			nlist->first = nlist->first->next;
			free(m);
			m = nlist->first;
		}
		nlist->size-=size;
		return 1;
	}
	for(int i=1;i<index;i++)
		m = m->next;
	mlist *m_bkf;
	for(int i=0;i<size;i++)
	{
		m_bkf = m->next;
		m->next = m_bkf->next;
		free(m_bkf);
	}
	nlist->size-=size;
}

int list_change(list *nlist, LIST_TYPE iNewMem, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	for(int i=0;i<index;i++)
		m = m->next;
	m->mem = iNewMem;
	return 1;
}

int list_indexof(list *nlist, LIST_TYPE iMem)
{
	int index = 0;
	int flag = -1;
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
	{
		if(m->mem == iMem)
		{
			flag++;
			break;
		}
		m = m->next;
		index++;
	}
	return flag == -1?flag:index;
}

int list_last_indexof(list *nlist, LIST_TYPE iMem)
{
	int index = 0;
	int flag = -1;
	int index_flag = 0;
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
	{
		if(m->mem == iMem)
		{
			flag++;
			index_flag=0;
		}
		else
			index_flag++;
		m = m->next;
		index++;
	}
	return flag == -1?flag:index-index_flag-1;
}

int list_equal(list *flist,list *slist)
{
	if(flist->size==slist->size)
	{
		mlist *fm = flist->first;
		mlist *sm = slist->first;
		for(int i=0;i<flist->size;i++)
		{
		//funcation list_equal is not support float or double
#if LIST_TYPE==float
			return 0;
			//if(fabs(fm->mem-sm->mem)<FLT_EPSILON)return 0;
#elif LIST_TYPE==double
			return 0;
			//if(fabs(fm->mem-sm->mem)<DBL_EPSILON)return 0;
#else
			if(fm->mem != sm->mem)return 0;
#endif
			fm = fm->next;
			sm = sm->next;
		}
		return 1;
	}
	return 0;
}

int *list_listtoarray(list *nlist)
{
	int *iArr = (int*)malloc(sizeof(int)*nlist->size);
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
	{
		iArr[i] = m->mem;
		m = m->next;
	}
	return iArr;
}

list *list_arraytolist(int *arr, int size)
{
	list *nlist = list_init();
	for(int i=0;i<size;i++)
		list_push_back(nlist,arr[i]);
	return nlist;
}

mlist *list_begin(list *nlist)
{
	return nlist->first;
}

mlist *list_end(list *nlist)
{
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
		m = m->next;
	return m;
}

int *list_swap(list *xlist, list *ylist)
{
	list *bkf = xlist;
	xlist = ylist;
	ylist = bkf;
}

int list_test(list *nlist, LIST_TYPE var, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	for(int i=0;i<index;i++)
		m = m->next;
	return var==m->mem;
}

int list_clear(list *nlist)
{
	list_erase(nlist,0,nlist->size);
	nlist->first = NULL;
}

int list_empty(list *nlist)
{
	if(nlist == NULL) return 0;
	return nlist->first == NULL;

}

int list_delete(list *nlist)
{
	list_clear(nlist);
	free(nlist);
	nlist = NULL;
}

