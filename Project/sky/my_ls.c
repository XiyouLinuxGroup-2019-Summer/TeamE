#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "/usr/include/linux/limits.h"
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <error.h>
#include "List.h"
#define PARAM_NONE 0 //无参数
#define PARAM_A 1 //-a显示所有文件
#define PARAM_L 2 //-l一行只显示一个文件的信息
#define PARAM_R 4 //展示所有子目录中的文件
#define PARAM_r 8//逆序输出
#define PARAM_f 16//不排序
#define MAXROWLEN 150 //一行显示的最多字符数

int g_leave_len = MAXROWLEN;//一行剩余长度
int g_maxlen; //最长文件名字的长度
typedef struct 
{
    char name[NAME_MAX+1];
}name_t;//实体struct结构体
typedef struct name_node
{
    name_t data;
    struct name_node *prev;
    struct name_node *next;
}name_node_t;
typedef name_node_t *name_list_t;
void display_single(char *namei,struct stat *buf);
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
void  SortList(name_list_t list) {
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
//获取文件属性并且打印
void display_attribute(struct stat buf,char *name)
{
    char buf_time[32];
    struct passwd *psd;//文件所有者的用户名
    struct group *grp;//文件所有者所属组

    //获取并且打印文件类型
    if(S_ISLNK(buf.st_mode)) printf("l");
    else if(S_ISREG(buf.st_mode)) printf("-");
    else if(S_ISDIR(buf.st_mode)) printf("d");
    else if(S_ISCHR(buf.st_mode)) printf("c");
    else if(S_ISBLK(buf.st_mode)) printf("b");
    else if(S_ISFIFO(buf.st_mode)) printf("f");
    else if(S_ISSOCK(buf.st_mode)) printf("s");

    //打印文件所有者的权限
    if(buf.st_mode & S_IRUSR) printf("r");
    else printf("-");
    if(buf.st_mode & S_IWUSR) printf("w");
    else printf("-");
    if(buf.st_mode & S_IXUSR) printf("x");
    else printf("-");

    //同组用户对文件的权限
    if(buf.st_mode & S_IRGRP) printf("r");
    else printf("-");
    if(buf.st_mode & S_IWGRP) printf("w");
    else printf("-");
    if(buf.st_mode & S_IXGRP) printf("x");
    else printf("-");

    //其他用户
    if(buf.st_mode & S_IROTH) printf("r");
    else printf("-");
    if(buf.st_mode & S_IWOTH) printf("w");
    else printf("-");
    if(buf.st_mode & S_IXOTH) printf("x");
    else printf("-");

    //根据uid和gid获取文件所有者的用户名和组名
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4d ",(int)buf.st_nlink);//打印文件链接数
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);

    printf("%6d",(int)buf.st_size);//打印文件大小
    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time) - 1] = '\0';
    printf(" %s",buf_time); //打印文件的时间信息
    return ;
}
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
}

void display(int flag,char *pathname,name_list_t list)
{
    int i,j;
    struct stat buf;
    char name[NAME_MAX+1];

    //从路径中解析出文件名字
    for(i = 0,j = 0;i < (int) strlen(pathname);i++)
    {
        if(pathname[i] ==  '/')
        {
            j = 0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j] = '\0';


    //用lstat而不是stat方便链接文件
    if(lstat(pathname,&buf) == -1) my_err("stat",__LINE__);

    switch(flag)
    {
        //没有参数
        case PARAM_NONE:
            if(name[0] != '.') display_single(name,&buf);
            break;

        case PARAM_A:
            display_single(name,&buf);
            break;

        case PARAM_L:
            if(name[0] != '.')
            {
                display_attribute(buf,name);
                printf(" %-s\n",name);
            }
            break;
        case PARAM_L + PARAM_A:
            //if(name[0] != '.')
            {
                display_attribute(buf,name);
                printf(" %-s\n",name);
            }
            break;
        case PARAM_R:
            if(name[0] != '.') 
                display_single(name,&buf);
            if(S_ISDIR(buf.st_mode))
            {
                //printf("yes\n");
                name_node_t *node =  (name_list_t)malloc(sizeof(name_node_t));
                strcpy(node->data.name,pathname);
                node->data.name[strlen(pathname)] = '/';
                node->data.name[strlen(pathname)+1] = '\0';
                List_AddTail(list,node);
            }
            break;
       case PARAM_R + PARAM_A:
            //if(name[0] != '.') 
                display_single(name,&buf);
            if(S_ISDIR(buf.st_mode) && name[0] != '.')
            {
                //printf("yes\n");
                name_node_t *node =  (name_list_t)malloc(sizeof(name_node_t));
                strcpy(node->data.name,pathname);
                node->data.name[strlen(pathname)] = '/';
                node->data.name[strlen(pathname)+1] = '\0';
                List_AddTail(list,node);
            }
            break;
       case PARAM_R + PARAM_L:
            if(name[0] != '.')
            {
                display_attribute(buf,name);
                printf(" %-s\n",name);
            }

            if(S_ISDIR(buf.st_mode))
            {
                //printf("yes\n");
                name_node_t *node =  (name_list_t)malloc(sizeof(name_node_t));
                strcpy(node->data.name,pathname);
                node->data.name[strlen(pathname)] = '/';
                node->data.name[strlen(pathname)+1] = '\0';
                List_AddTail(list,node);
            }
            break;
        case PARAM_r:
            if(name[0] != '.') display_single(name,&buf);
            break;
        case PARAM_f:
            if(name[0] != '.') display_single(name,&buf);
            break;



            
        default:
            break;
    }
}
void display_single(char *name,struct stat *buf)
{
    int i,len;

    //如果本行不足以打印一个文件名则换行
    if(g_leave_len < g_maxlen)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }

    len = strlen(name);
    len = g_maxlen - len;
    if(S_ISDIR(buf->st_mode))
    printf("\033[41;36m%-s\033[0m",name);
    else
    printf("%-s",name);
    for(i = 0;i<len;i++)    printf(" ");
    printf("  ");
    //2表示空两格
    g_leave_len -= (g_maxlen+2);
}
void display_dir(int flag_param,char *path)
{
    g_maxlen = -1;
    name_list_t list;
    name_list_t cur_list;
    List_Init(cur_list,name_node_t);
    List_Init(list,name_node_t);
    DIR *dir;
    struct dirent *ptr;
    int count = 0;
    /* char file_names[256][PATH_MAX+1],temp[PATH_MAX+1]; *///此处改为在堆区开辟空间


    //获取该目录下目录总数和最长文件名字
    dir = opendir(path);
    if(dir == NULL)
    {
        my_err("openir",__LINE__);
    }
    while((ptr = readdir(dir)) != NULL)
    {
        if((flag_param & 1) && ptr->d_name[0] == '.') count++;
        else if(ptr->d_name[0] != '.') count++;
        if(g_maxlen < (int)strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
    }
    closedir(dir);
    
    printf("文件总数:%d\n",count);
   /* if(count > 256)//有什么用处  未知 */
   /* { */
   /*     my_err("该目录下的文件太多！",__LINE__); */
   /* } */

    int i,j,len = strlen(path);
   //获取该目录下的所有文件名字
   dir = opendir(path);
   for(i = 0;i < count ;i++)
   {
       ptr = readdir(dir);
       if(!(flag_param&1) && ptr->d_name[0] == '.')
       {
           i--;
           continue;
       }
       if(ptr == NULL) my_err("readdir",__LINE__);
        else{
        name_node_t *node = (name_list_t)malloc(sizeof(name_node_t));
       strncpy(node->data.name,path,len);
       node->data.name[len] = '\0';
       strcat(node->data.name,ptr->d_name);
       node->data.name[len + (int)strlen(ptr->d_name)] = '\0';
       List_AddTail(cur_list,node);
    }
   }

   //使用冒泡法对文件名进行排序
   /* for(i = 0;i<count - 1;i++) */
   /*     for(j = i+1;j<count - 1;j++) */
   /*     { */
   /*         if(strcmp(file_names[i],file_names[j]) > 0 ) */
   /*         { */
   /*             strcpy(temp,file_names[i]); */
   /*             strcpy(file_names[i],file_names[j]); */
   /*             strcpy(file_names[j],temp); */
   /*         } */
   /*     } */

   /* for(i = 0;i<count;i++)//单个打印文件 */
       /* display(flag_param,file_names[i],list,i,count-1); */
   if(!(flag_param&16))
    SortList(cur_list);
    name_list_t p;
    if((flag_param&8))
    List_ForEach2(cur_list,p)
    {
        display(flag_param,p->data.name,list);
    }
    else 
    List_ForEach(cur_list,p)
    {
        display(flag_param,p->data.name,list);
    }
   closedir(dir);
    /* if(cur == count) */
            {
                //printf("yes\n");
                name_list_t p;
                printf("\n");
                List_ForEach(list,p)
                {
                    printf("\n%s\n",p->data.name);
                    display_dir(flag_param,p->data.name);
                }
            }
        

   //如果命令中没有-l 打印一个换行符
   if((flag_param & PARAM_L) == 0)  printf("\n");
   return ;
}
int main(int argc,char ** argv)
{
    int i,j,k,num;
    char path[PATH_MAX+1];
    char param[32]; //保存命令行参数,目标文件和命令行不在此列。
    int flag_param = PARAM_NONE;//参数种类即是否有-a -l选项
    struct stat buf;
    
    //命令行参数解析，分析-l -a -al -la 选项
    j = 0;num = 0;
    for(i = 0;i<argc;i++)
    {
        if(argv[i][0] == '-')
        {
            for(k = 1;k<(int)strlen(argv[i]);k++,j++)
            {
                param[j] = argv[i][k]; //获取-后面的参数保存到数组param中
            }
        num++; //保存-的个数
        }
    }

    //只支持参数-a -l 其他报错
    for(i = 0;i<j;i++)
    {
        if(param[i] == 'a')    flag_param |= PARAM_A;
        
        else if(param[i] == 'l')     flag_param |= PARAM_L; 
   
        else if(param[i] == 'R')     flag_param |= PARAM_R;
        
        else if(param[i] == 'r')     flag_param |= PARAM_r;
        
        else if(param[i] == 'f')     flag_param |= PARAM_f; 
        else
        {
            printf("my_ls:invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    param[j] = '\0';

    //如果没有输入文件名就显示当前目录
    if(num + 1 == argc)
    {
        strcpy(path,"./");
        path[2] = '\0';
        display_dir(flag_param,path);
        return 0;
    }
    
    i = 1;
    do
    {
        //如果不是目标文件或目录，解析下一个命令参数
        if(argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else
        {
            strcpy(path,argv[i]);
            //如果目标文件或者目录不存在，报错退出程序
            if(stat(path,&buf) == -1)
            {
                my_err("stat",__LINE__);
            }


            if(S_ISDIR(buf.st_mode))
            {//grgv[i]是一个目录
            //如果目录最后一个字符不是/ , 就加上/
            if(path[(int)strlen(argv[i])-1] != '/')
            {
                path[(int)strlen(argv[i])] = '/';
                path[(int)strlen(argv[i])+1] = '\0';
            }
            else path[(int)strlen(argv[i])] = '\0';
            display_dir(flag_param,path);
            i++;
            
            }
        }
    }while(i<argc);
    return 0;
}

