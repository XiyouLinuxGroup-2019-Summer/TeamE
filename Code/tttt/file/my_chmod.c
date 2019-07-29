#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char **argv)
{
	int mode;     //权限
	int mode_u;   //所有者权限
	int mode_g;   //所属组
	int mode_o;   //其他用户权限
	int flag = 0;
	char *path;
	struct stat buf;
	if(lstat(argv[2],&buf) == -1)
	{
		printf( "stat error\n");
		return 0;
	}

	if(argc < 3)
	{
		printf( "%s <mode num> <target file> \n",argv[0]);
		exit(0);
	}
	int i;
	int chmod_num = 0;
	for(i = 0;i < strlen(argv[1]);i++)
	{
		if(argv[1][i] == '+')  flag = 1;
		else if(argv[1][i] == '-')  flag = -1;
	}
	if(flag != 0)
	{
		if(buf.st_mode & S_IRUSR) 	chmod_num += (4*100);
		if(buf.st_mode & S_IWUSR) 	chmod_num += (2*100);
		if(buf.st_mode & S_IXUSR) 	chmod_num += 100;
		if(buf.st_mode & S_IRGRP)       chmod_num += (4*10);
		if(buf.st_mode & S_IWGRP)       chmod_num += (2*10);
		if(buf.st_mode & S_IXGRP)       chmod_num += (10);
		if(buf.st_mode & S_IROTH)       chmod_num += 4;
		if(buf.st_mode & S_IWOTH)       chmod_num += 2;
		if(buf.st_mode & S_IXOTH)       chmod_num += 1;
	
		if(flag == 1)
		{
			if(argv[1][0] == 'u')
			{
				if(argv[1][2] == 'r')  chmod_num += (4*100);
				if(argv[1][2] == 'w')  chmod_num += (2*100);
				if(argv[1][2] == 'x')  chmod_num += (100);
			}
			else if(argv[1][0] == 'g')
			{
				if(argv[1][2] == 'r')  chmod_num += (4*10);
				if(argv[1][2] == 'w')  chmod_num += (2*10);
				if(argv[1][2] == 'x')  chmod_num += (10);
			}
			else if(argv[1][0] == 'o')
			{
				if(argv[1][2] == 'r')  chmod_num += (4);
				if(argv[1][2] == 'w')  chmod_num += 2;
				if(argv[1][2] == 'x')  chmod_num += 1;
			}
		}
		else
		{
			if(argv[1][0] == 'u')
			{
				if(argv[1][2] == 'r')  chmod_num -= (4*100);
				if(argv[1][2] == 'w')  chmod_num -= (2*100);
				if(argv[1][2] == 'x')  chmod_num -= (100);
			}
			else if(argv[1][0] == 'g')
			{
				if(argv[1][2] == 'r')  chmod_num -= (4*10);
				if(argv[1][2] == 'w')  chmod_num -= (2*10);
				if(argv[1][2] == 'x')  chmod_num -= (10);
			}
			else if(argv[1][0] == 'o')
			{
				if(argv[1][2] == 'r')  chmod_num -= (4);
				if(argv[1][2] == 'w')  chmod_num -= 2;
				if(argv[1][2] == 'x')  chmod_num -= 1;
			}
		}


		mode = chmod_num;
	}
	else
		mode = atoi(argv[1]);    //atoi 将字符串转化为整型

	if(mode > 777 || mode < 0)
	{
		printf( "mode num error!\n");
		exit(0);
	}

	mode_u = mode/100;
	mode_g = (mode - (mode_u *100))/10;
	mode_o = mode - (mode_u * 100) - (mode_g * 10);
	mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;
	
//	printf( "mode = %d",mode);
	
	path = argv[2];

	if(chmod(path,mode) == -1)
	{
		perror("chmod errpr");
		exit(1);
	}


	return 0;
}
