#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void sortarr(int* size, int* filestr, int count)
{
  int tmp;
  int tmp2;
  for(int i=0; i<count; i++)
  {
    for(int j=i+1; j<count; j++)
    {
      if(size[i] > size[j])
      {
        tmp = size[i];
        tmp2 = filestr[i];
        size[i] = size[j];
        filestr[i] = filestr[j];
        size[j] = tmp;
        filestr[j] = tmp2;
      }
    }
  }
}
int main()
{
  DIR *d;
  struct dirent *dir;
  struct stat st;
  int count=0;
  int isize=0;
  int *size;
  int *filestr;
  char** filename;
  d = opendir(".");
  if(d)
  {
    while((dir = readdir(d)) != NULL)
    {
      count++;
    }
    closedir(d);
  }
  size = (int*)malloc(count*sizeof(int));
  filestr = (int*)malloc(count*sizeof(int));
  filename = (char**)malloc(count*sizeof(char*));
  for(int i=0; i<count; i++)
  {
    filename[i] = (char*)malloc(1024*sizeof(char));
    filestr[i]=i;
  }
  d = opendir(".");
  if(d)
  {
    while((dir = readdir(d)) != NULL)
    {
      strcpy(filename[isize],dir->d_name);
      stat(dir->d_name,&st);
      size[isize]=st.st_size;
      isize++;
    }
    closedir(d);
  }
  sortarr(size,filestr,count);
  for(int i=0; i<count; i++)
  {
    printf("%s \t %d \n",filename[filestr[i]],size[i]);
  }
  return 0;
}
