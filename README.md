# link-list

# 基本类型:
list

# 关于返回值:
所有返回值为int类型的函数如果执行成功便返回1，失败返回0

# 关于此版本:
这个版本在所有链表操作的基础上增加了哈希表操作
可以给每个节点绑定一个key,之后可以直接通过这个key访问元素
API里面大多数函数都和C++里的list相类似,只要用过C++那么可以很快上手

# 在使用前你需要考虑两个宏
# LIST_TYPE
这个宏决定了链表操作的数据类型,比如可以: #define LIST_TYPE float

# LIST_SUPPORT_HASHMAP
这个宏决定是否要启用哈希表功能,为了效率程序默认关闭对哈希表的支持
只要定义这个宏就开启对哈希表的支持(可以使用哈希表的API)

# 更多细节:
此文件使用链表实现
list API基于单向链表
hashmap API则基于双向链表

# #####################详细说明#####################

list *list_init();
初始化，每个list类型的变量都要调用这个函数

LIST_TYPE list_var(list *nlist, int index);
返回第index的节点的值

int list_insert(list *nlist, LIST_TYPE iMem, int index);
在第index处插入元素iMem

int list_push_back(list *nlist, LIST_TYPE iMem);
在链表最前面插入元素iMem

int list_push_front(list *nlist, LIST_TYPE iMem);
在链表最后面插入元素iMem

int list_size(list *nlist);
返回链表大小

int list_erase(list *nlist, int size, int index);
从index处删除size个元素

int list_change(list *nlist, LIST_TYPE iNewMem, int index);
改变第index处的元素为iNewMem

int list_indexof(list *nlist, LIST_TYPE iMem);
返回iMem在这个链表中第一次出现的位置

int list_last_indexof(list *nlist, LIST_TYPE iMem);
返回iMem在这个链表中最后一次出现的位置

int list_equal(list *flist,list *slist);
比较两个链表是否相同(浮点数无法比较)

int *list_listtoarray(list *nlist);
把链表转换成数组类型返回

list *list_arraytolist(int *arr, int size);
把数组转换成链表类型返回

mlist *list_begin(list *nlist);
返回链表第一个节点的地址

mlist *list_end(list *nlist);
返回链表最后一个节点的地址

int *list_swap(list *xlist, list *ylist);
交换两个链表

int list_test(list *nlist, LIST_TYPE var, int index);
测试第index个元素是否是var

int list_clear(list *nlist);
清空链表(返回刚创建的状态)

int list_empty(list *nlist);
测试链表是否是空的

int list_delete(list *nlist);
删除链表(最后会把list变量置为NULL)

int list_hashlink(list *nlist, char* key, int index);
将链表第index个元素和key绑定

int list_hashindex(list *nlist, char* key);
返回与key绑定的元素index

char* list_hashstring(list *nlist, int index);
返回与index绑定的字符串

LIST_TYPE list_hashvar(list *nlist, char* key);
返回链表上绑定值为key的元素

int list_hashdel(list *nlist, char* key);
删除值为key的链表

int list_hashsize(list *nlist);
返回哈希表的大小

