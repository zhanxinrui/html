#include"stdafx.h"
#include<windows.h>
#include<stdio.h>
HANDLE FindFirstFile(
	LPCTSTR lpFileName,//文件名  欲搜索的文件名，可包括通配符，并可包含一个路径和相对路径名
	LPWIN32_FIND_DATA lpFindFileData//数据缓冲区  输出参数，他只想一个WIN32_FIND_DATA结构，更改结构可以用于装载于找到文件有关的信息，也可用于后续的搜索
	)；
typedef struct _WIN32_FIND_DATA{
	DWORD dwFileAttributes;//文件属性
	FILETIME ftcreationTime;  //文件创建的时间
	FILETIME ftLastAccessTime；//文件最后一次访问时间
	FILETIME ftLastWriteTime; //文件最后一次修改的时间
	DWORD nFileSizeHigh;//文件长度高32位
	DWORD nFileSizeLow;//文件长度低32位
	DWORD dwReserved0;  //系统保留
	DWORD dwReserved1;   //系统保留
	TCHAR cFileName[ MAX_PATH]; //长文件名
	TCHAR cAlternateFileName[14];    //8.3格式文件名

}WIN32_FIND_DATA,*PWIN32_FIND_DATA;


struct DirList{

	char table[256];//文件夹名
	DirList *pNext;
}
DirList *first ,*newlist ,*last;

void AddList(char *list)//加入文件夹链表
{
	newlist = new DirList;
	strcpy (newlist->table ,list);//strcpy是后cpy到前
	newlist->pNext=NULL;
	if(first == NULL){//假如文件链表为空，则第一个和最后一个结点都指向新结点
	 first=newlist;
	 last = newlist;
	}
	else {
		last->pNext = newlist;
		last = newlist;//不为空则原来最后一个结点指向新结点
	}
}

void FindFile(char *pRoad,char *pFile){//查找文件并把找到的文件夹加入文件夹链表 pRoad是文件夹名 pfile是文件名
	char FileRoad[256]={0};//去找的文件夹
	char DirRoad[256]={0};//去找的文件
	char FindedFile[256]={0};//找到的文件
	char FindedDir[256] = {0};//找到的文件夹
	strcpy(FileRoad,pRoad);    
	strcpy(DirRoad,pRoad);
	strcat(DirRoad,"\\*.*");//匹配文件夹下所有的？
	WIN32_FIND_DATA findData;
	HANDLE hFindFile;
	hFindFile = FindFirstFile(DirRoad,&findData);//文件夹，传回相应的finddata数据
	if(hFindFile!=INVALID_HANDLE_VALUE)
	{
		do{
			if(findData.cFileName[0]=='.')
				continue;
			if(findData.dwFileAttributes&&FILE_ATTRIBUTE_DIRECTORY)//假如是文件夹，则假如文件夹列表
			{
				strcpy(FindedDir,pRoad);
				strcat(FindedDir,"\\");
				strcat(FindedDir,fi  ndData.cFileName);
				
				AddList(FindedDir);//加入文件夹列表                                                                   go addlist(搜索到文件夹)，放到链表最后，以后再搜
				memset(FindedDir,0x00,256);  //再吧findeddir置空，为了下一次循环
			}
		}
		while(FindNextFile(hFindFile,&findData));
	}
	WIN32_FIND_DATA findData;
	strcat(FileRoad,"\\");   
	strcat(FileRoad,pFile);
	hFindFile= FindFirstFile(FileRoad,&findData);//查找要查找的文件
	if(hFindFile!= INVALID_HANDLE_VALUE){
		do{
			strcpy(FindedFile,pRoad);
			strcat(FindedFile,"\\");
			strcat(FindedFile,findData.cFileName);//输出查找的文件
			printf("%s\n",FindedFile);
			memset(FindedFile,0x00,256);
		}while(FindNextFile(hFindFile,&findData));

	}

}

int SearchFile(char *Directory,char *SearchFile){//directory是文件夹，searchfile是所搜寻的文件
	DirList NewList;
	strcpy(NewList.table,Directory);//把文件夹放进去
	NewList.pNext = NULL;//初始化第一个和最后一个结点
	last= &NewList;
	first = &NewList;
	while(true){
		DirList *Find;
		if(first != NULL)//链表不为空，提取链表中的第一个结点，并把第一个结点指向第二个
		{
			Find = First;//提取结点
			first = first->pNext;//并把第一个结点指向原来第二个,一个文件夹在被读取之后就被抛弃，first指向下一个                     go Find File(文件夹结点的文件夹名字，和输入的文件名)
			FindFile (Find->table,SearchFile);//再提取的结点的目录下查找文件

		}
		else //为空则停止查找
		{

			printf("文件搜索完毕\n");
			return 0;
		}

	}
	return 0;
}



int main(int argc,char* argv[]){

	SearchFile(argv[1],argv[2]);//一是文件夹，二是文件                                                                           go SearchFile(输入文件夹，输入文件)
	return 0;
}