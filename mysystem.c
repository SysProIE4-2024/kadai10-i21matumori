/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース
char *execpath = "/bin/sh";
// system関数のクローン
int mysystem(char *command) {
  pid_t pid;
  if (command == NULL) {
    return 1;
  } else if ((pid = fork()) < 0) {
    perror(command);
    return -1;
  }
  if (pid != 0) {
    int status;
    while (wait(&status) != pid)
    ;
    return status;
  } else {
    execl(execpath,"sh","-c",command,NULL);
    perror(execpath);
    exit(127);
  }
  return 0
}

/* 実行例
 % ./mysysmain                             <-- 引数がない場合
使い方 : ./mysysmain コマンド文字列            <-- Usageメッセージ表示
% ls -l                                    <-- コマンドラインで実行した結果
total 616
-rw-r--r--  1 matsumoriyuna  staff     143  7  4 09:42 Makefile
-rw-r--r--  1 matsumoriyuna  staff    2795  7  4 09:42 README.md
-rw-r--r--  1 matsumoriyuna  staff  238232  7  4 09:42 README.pdf
-rwxr-xr-x  1 matsumoriyuna  staff   50392  7  8 12:34 mysysmain
-rw-r--r--  1 matsumoriyuna  staff     925  7  4 09:42 mysysmain.c
-rw-r--r--  1 matsumoriyuna  staff     719  7  8 12:34 mysystem.c
-rw-r--r--  1 matsumoriyuna  staff      90  7  4 09:42 mysystem.h
% ./mysysmain "ls -l"
mysystem:                                  <-- ここからmysystemの結果
total 616
-rw-r--r--  1 matsumoriyuna  staff     143  7  4 09:42 Makefile
-rw-r--r--  1 matsumoriyuna  staff    2795  7  4 09:42 README.md
-rw-r--r--  1 matsumoriyuna  staff  238232  7  4 09:42 README.pdf
-rwxr-xr-x  1 matsumoriyuna  staff   50392  7  8 12:39 mysysmain
-rw-r--r--  1 matsumoriyuna  staff     925  7  4 09:42 mysysmain.c
-rw-r--r--  1 matsumoriyuna  staff    1435  7  8 12:39 mysystem.c
-rw-r--r--  1 matsumoriyuna  staff      90  7  4 09:42 mysystem.h
retval = 00000000
system:                                     <-- ここからsystemの結果
total 616
-rw-r--r--  1 matsumoriyuna  staff     143  7  4 09:42 Makefile
-rw-r--r--  1 matsumoriyuna  staff    2795  7  4 09:42 README.md
-rw-r--r--  1 matsumoriyuna  staff  238232  7  4 09:42 README.pdf
-rwxr-xr-x  1 matsumoriyuna  staff   50392  7  8 12:39 mysysmain
-rw-r--r--  1 matsumoriyuna  staff     925  7  4 09:42 mysysmain.c
-rw-r--r--  1 matsumoriyuna  staff    1435  7  8 12:39 mysystem.c
-rw-r--r--  1 matsumoriyuna  staff      90  7  4 09:42 mysystem.h
retval = 00000000

ここに実行例を書く

*/
