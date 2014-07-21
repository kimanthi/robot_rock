#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <posapi.h>
#include <posapi_all.h>

// posix
//#include <stdio.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <fcntl.h>
/*
int create_file_posix(void)
{
  unsigned char dat={0x00};
  int fd=0, iRet=0;

  fd = open("test", O_CREAT);
  //fd = creat("test", O_RDWR);
  printf("\nCreate file %d", fd);
  if (fd > 0)
  {
    printf("\nWrite file %d", write(fd, "1234567890", 10));
    printf("\nClose file %d", close(fd));
  }

  fd = open("test", O_RDWR);
  printf("\nOpen file %d", fd);
  if (fd > 0)
  {
    iRet = read(fd, dat, 10);
    printf("\nRead file %d - %s", iRet, dat);
    printf("\nClose file %d", close(fd));
  }

  return 0;
}
*/

// Stat file posix
//int test_stat(char *file_name)
//{
  //struct stat fileStat;
  //int iRet=0;

  //printf("\nstat %d", iRet = stat(file_name,&fileStat));

  //if(iRet < 0)
    //return 1;

  //printf("Information for %s\n",file_name);
  //printf("---------------------------\n");
  //printf("File Size: \t\t%d bytes\n",fileStat.st_size);
  //printf("Number of Links: \t%d\n",fileStat.st_nlink);
  //printf("File inode: \t\t%d\n",fileStat.st_ino);

  //printf("File Permissions: \t");
  //printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  //printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
  //printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
  //printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
  //printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
  //printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
  //printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
  //printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
  //printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
  //printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
  //printf("\n\n");

  //printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

  //return 0;
//}

// create file and directory
int create_file_and_directory(void)
{
  uchar dat[20];
  int fd=0, iRet=0;
  int fd_dir;

  memset(dat, 0, sizeof(dat));

  DelayMs(2000);
  fd_dir = FsOpen("dir1", FS_ATTR_D);
  printf("\nCreate dir %d", fd_dir);
  DelayMs(2000);
  printf("\nClose dir %d", FsClose(fd_dir));

  DelayMs(2000);
  fd = open("dir1/test3", O_CREATE);
  printf("\nCreate file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    printf("\nWrite file %d", write(fd, "1234567890", 10));
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  DelayMs(2000);
  fd = open("dir1/test3", O_RDWR);
  //fd = FsOpen("test3", FS_ATTR_R);
  printf("\nOpen file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    iRet = read(fd, dat, 10);
    printf("\nRead file %d - %s", iRet, dat);
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  return 0;
}

// pax stat
void print_info(FS_INODE_INFO fs_inode)
{
  printf("n %s ns %d attr %d nf %d si %d sp %d", fs_inode.name, fs_inode.name_size, fs_inode.attr, fs_inode.name_fmt, fs_inode.size, fs_inode.space);
  printf("\nwr s %lu m %lu h %lu d %lu M %lu y %lu ", fs_inode.wrtime.seconds, fs_inode.wrtime.minute, fs_inode.wrtime.hour, fs_inode.wrtime.day, fs_inode.wrtime.month, fs_inode.wrtime.year);
  printf("\ncr s %lu m %lu h %lu d %lu M %lu y %lu ", fs_inode.crtime.seconds, fs_inode.crtime.minute, fs_inode.crtime.hour, fs_inode.crtime.day, fs_inode.crtime.month, fs_inode.crtime.year);
}

int stat_info(void)
{
  FS_INODE_INFO fs_inode;
  int fd_dir;

  memset(&fs_inode, 0, sizeof(fs_inode));

  fd_dir = FsOpen("dir1", FS_ATTR_D);
  printf("\nOpen dir %d", fd_dir);

  printf("\nprint dir read %d", FsDirRead(fd_dir, &fs_inode, 1));
  DelayMs(2000);
  print_info(fs_inode);

  DelayMs(2000);
  printf("\nClose dir %d", FsClose(fd_dir));
}

int stat_info2(void)
{
  FS_W_STR name;

  memset(&name, 0, sizeof(name));

  DelayMs(2000);
  printf("\nGet Work dir %d            ", FsGetWorkDir(&name));
  DelayMs(2000);
  printf("\nWork dir %s - s %d - f %d ", name.str, name.size, name.fmt);
}

int stat_info3(void)
{
  FS_DISK_INFO ds;

  DelayMs(2000);
  memset(&ds, 0, sizeof(ds));
  printf("\nDisk Info 0 %d", FsGetDiskInfo(0, &ds));
  DelayMs(2000);
  printf("ver %d - fs %d, - us %d", ds.ver, ds.free_space, ds.used_space);

  DelayMs(2000);
  memset(&ds, 0, sizeof(ds));
  printf("\nDisk Info 1 %d", FsGetDiskInfo(1, &ds));
  DelayMs(2000);
  printf("ver %d - fs %d, - us %d", ds.ver, ds.free_space, ds.used_space);
}

//void print_info2(FILE_INFO *info)
//{
  //printf("fd %d - at %d - t %d - %s, %d", info.fid, info.attr, info.type, info.name, info.length);
//}

int stat_info4(void)
{
  FILE_INFO *info;
  FILE_INFO *info_ptr;

  info = malloc(sizeof(FILE_INFO)*256);

  printf("\nFile Info: %d", GetFileInfo(info));

  info_ptr = info;

  do {
    printf("\nfd %d - %s - %d", info->fid, info->name, info->length);
    DelayMs(500);
    info++;
  } while(info->fid);

  free(info_ptr);
  printf("\n GetLastError %d", GetLastError());

  //info = (info >> sizeof(FILE_INFO));
  //info = *((&info)++);

  //printf("\nsizeof %d", sizeof(FILE_INFO));
  //info2+=30;
  //printf("\nfd %d - %s", info2->fid, info2->name);
  //printf("\nfd %d - at %d - t %d - %s, %d", info2->fid, info2->attr, info2->type, info2->name, info2->length)
  //printf("\nfd %d - at %d - t %d - %s, %d", info.fid, info.attr, info.type, info.name, info.length);
  //printf("\nfd %d - at %d - t %d - %s, %d", info->fid, info->attr, info->type, info->name, info->length);

  //info = (info >> sizeof(FILE_INFO));
  //info = *((&info)++);

  //info2+=30;
  //printf("\nfd %d - %s", info2->fid, info2->name);
  //printf("\nfd %d - at %d - t %d - %s, %d", info2->fid, info2->attr, info2->type, info2->name, info2->length);
  //printf("\nfd %d - at %d - t %d - %s, %d", info.fid, info.attr, info.type, info.name, info.length);
  //printf("\nfd %d - at %d - t %d - %s, %d", info->fid, info->attr, info->type, info->name, info->length);
  //

  DelayMs(2000);
}

int stat_info5(FILE_INFO *st)
{
  FILE_INFO *info;
  FILE_INFO *info_ptr;
  int i=1;

  info = malloc(sizeof(FILE_INFO)*256);

  printf("\nFile Info: %d", GetFileInfo(info));

  info_ptr = info;

  do {
    printf("\nfd %d - %s - %d", info->fid, info->name, info->length);
    DelayMs(500);
    info++;
    i++;
    if (i == 3) {
      memcpy(st, info, sizeof(FILE_INFO));
    }
  } while(info->fid);

  free(info_ptr);
  printf("\n GetLastError %d", GetLastError());

  DelayMs(2000);
}

int stat_info6(void)
{
  FILE_INFO *info;
  int ret;

  info = malloc(sizeof(FILE_INFO));

  stat_info5(info);
  printf("\nfile %d %s", info->fid, info->name);
  DelayMs(4000);
}

//basename
int file_basename(void)
{
  uchar dat[20];
  int fd=0, iRet=0;

  memset(dat, 0, sizeof(dat));

  DelayMs(2000);
  fd = open("./dir2/test3", O_CREATE);
  printf("\nCreate file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    printf("\nWrite file %d", write(fd, "1234567899", 10));
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  DelayMs(2000);
  fd = open("./dir2/test3", O_RDWR);
  printf("\nOpen file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    iRet = read(fd, dat, 10);
    printf("\nRead file %d - %s", iRet, dat);
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  return 0;
}

//file exists
int file_exists(void)
{
  uchar dat[20];
  int fd=0, iRet=0;

  memset(dat, 0, sizeof(dat));

  DelayMs(2000);
  // -1
  printf("\nFile exist %d", fexist("test3"));

  DelayMs(2000);
  fd = open("test3", O_CREATE);
  printf("\nCreate file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    printf("\nWrite file %d", write(fd, "1234567899", 10));
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  //return file descriptor
  DelayMs(2000);
  printf("\nFile exist %d", fd = fexist("test3"));

  DelayMs(2000);
  printf("\nFile exist with tell %d", tell(fd));

  return 0;
}

//file size
int file_size(void)
{
  uchar dat[20];
  int fd=0, iRet=0;

  memset(dat, 0, sizeof(dat));

  DelayMs(2000);
  // -1
  printf("\nFile exist %d", fexist("test3"));

  DelayMs(2000);
  fd = open("test3", O_CREATE);
  printf("\nCreate file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    printf("\nWrite file %d", write(fd, "1234567899", 10));
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  DelayMs(2000);
  printf("\nFile size %d", filesize("test3"));

  return 0;
}

//file rename
int file_rename(void)
{
  uchar dat[20];
  int fd=0, iRet=0;

  memset(dat, 0, sizeof(dat));

  DelayMs(2000);
  // -1
  printf("\nFile exist %d", fexist("test3"));

  DelayMs(2000);
  fd = open("test3", O_CREATE);
  printf("\nCreate file %d", fd);
  if (fd > 0)
  {
    DelayMs(2000);
    printf("\nWrite file %d", write(fd, "1234567899", 10));
    DelayMs(2000);
    printf("\nClose file %d", close(fd));
  }

  DelayMs(2000);
  printf("\nFile rename %d", rename("test3", "test3_renamed"));

  return 0;
}

//getkey
int get_pax_key(void)
{
  int key;
  int i=0;

  while((i++) <= 10){
    key = getkey();
    printf("\n%d", key);
  }
  return 0;
}

//getstring
int get_pax_string(void)
{
  unsigned char str[20];
  int i=0;

  memset(str, 0, sizeof(str));

  printf("\nGetString %02X", GetString(&str, 0x26, 0, 10));

  printf("\nString %s", str);

  return 0;
}

//gethzstring
int get_pax_hz_string(void)
{
  unsigned char str[20];
  int i=0;

  memset(str, 0, sizeof(str));

  printf("\nGetHzString %02X", GetHzString(&str, 10, 30));
  printf("\nGetHzString %s", str);

  return 0;
}

//ScrPrint
int scr_print2(void)
{
  ScrGotoxy(0, 0);
  ScrCls();
  ScrFontSet(ASCII);
  ScrPrint(0, 0, 0, "Print!!");
  printf("\nBefore");
  ScrPrint(5, 3, 0, "Print!!");
  printf("\n\nAfter");
  DelayMs(10000);
}

int scr_print(void)
{
  ScrGotoxy(0, 1);
  printf("AAAAAAAAA");
  ScrGotoxy(1, 2);
  printf("AAAAAAAAA");
  ScrGotoxy(2, 3);
  printf("AAAAAAAAA");
  ScrGotoxy(3, 4);
  printf("AAAAAAAAA");
  ScrGotoxy(4, 5);
  printf("AAAAAAAAA");

  DelayMs(10000);
}

void test_print1(void)
{
  ST_FONT *Fonts;
  int num_fonts;

  ScrCls();
  printf("Before\n");
  Lcdprintf("Pax Technology Ltd.");
  //ScrFontSet(ASCII);
  ScrSelectFont(NULL, NULL);
  Lcdprintf(" PAX Computer Technology company \nAugust 2001\n");
  __ScrPrint(0, 0, 1, "Test ASCII %d   ", ASCII);
  __ScrPrint(2, 2, 1, "Test CFONT %d   ", CFONT);
  __ScrPrint(4, 4, 1, "Test 1\n");
  __ScrPrint(6, 6, 1, "Test 1\n");
  __ScrPrint(8, 8, 1, "Test 1\n");
  __ScrPrint(10, 10, 1, "Test 1\n");
  __ScrPrint(12, 12, 1, "Test 1\n");
  __ScrPrint(14, 14, 1, "Test 1\n");
  printf("After %d", EnumBaseFont(&Fonts, &num_fonts));
  printf("\n %d", num_fonts);
  //__ScrClrLine(2, 3);

}

void test_print2(void)
{
  ScrCls();
  ScrFontSet(ASCII);
  Lcdprintf("Pax Technology Ltd.");
  ScrPrint(4, 4, 0, "Test 1\n");
  ScrGotoxy(0, 5);
  ScrFontSet(CFONT);
  Lcdprintf(" PAX Computer Technology company \nAugust 2001\n");
}

