#include <stdio.h>
#include <string.h>
#include "List.h"
#define List_ForEach2(list, curPos)\
	 for (   curPos = (list)->prev;  	\
		  	  	  curPos != list;       \
		  	  	  curPos=curPos->prev	\
	    )
typedef struct 
{
    int age;
    char name[64];
}name_t;
typedef struct name_node
{
    name_t data;
    struct name_node  *prev;
    struct name_node *next;
}name_node_t;
typedef name_node_t *name_list_t;
void AddToSortedList(name_list_t list,name_node_t *p)
{
    name_node_t *cur;
    if(!list) {List_AddTail(list,p);}
    else{
              cur = list->next;
              while(cur != list){
                  if(strcmp(p->data.name,cur->data.name) < 0) break;
                  cur = cur->next;
              }
              List_InsertBefore(cur,p);
    }
    return;
}
void  SortByNum(name_list_t list) {
    int flag = 1;
    name_list_t listLeft;
    List_Init(listLeft,name_node_t);
   if(!list)    flag = 0;
    if(flag){
   list->prev->next     =   NULL;//将循环链表最后一个节点断开
   listLeft     =   list->next;  //listleft指向第一个数据节点
   list->next   =     list->prev = list;//将list链表置为空
   while(listLeft != NULL){
       name_list_t p;
       p = listLeft;
       listLeft = listLeft->next;
       AddToSortedList(list,p);
   }}
}
int main()
{
   
    name_list_t list;
    List_Init(list,name_node_t);
    for(int i = 0;i<5;i++)
    {
        name_list_t pnode = (name_list_t)malloc(sizeof(name_node_t));
        printf("请输入姓名:");
        scanf("%s",pnode->data.name);
        setbuf(stdin,NULL);
        printf("请输入年龄:");
        scanf("%d",&pnode->data.age);
        List_AddTail(list,pnode);
    }

    name_list_t p;
    printf("\n排序前:\n");
    List_ForEach(list,p)
    {
        printf("名字:%s 年龄:%d\n",p->data.name,p->data.age);
    }
    //SortByNum(list);
    printf("\n按年龄排序后:\n");
    List_ForEach2(list,p)
    {
        printf("名字:%s 年龄:%d\n",p->data.name,p->data.age);
    }

    List_Destroy(list,name_node_t);
    return 0;
}
