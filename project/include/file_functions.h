#ifndef _FILEFUNCTIONS_H_
#define _FILEFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include<time.h>
#include <ctype.h>


#define MAX_FILENAME_LENGTH 1000
#define MAX_COMMIT_MESSAGE_LENGTH 2000
#define MAX_ARRAY 1000
#define MAX_MESSAGE_LENGTH 1000
#define debug(x) printf("%s", x);
#define __USE_GNU
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void print_command(int argc, char * const argv[]);
int check_neogit();
int init(int argc,char * const argv[]);
int config_user(char user[]);
int config_global_user(char user[]);
int config_email(char email[]);
int config_global_email(char email[]);
int make_alias(char * command);
char * search_for_alias(char []);
int add_file(char []);
int srearch_for_add(char[]);
void copy_file(char[],char[]);
char * branch_where();
char *cat_branch(char *);
void remove_directory(const char *path);
void copy_dir(const char *srcDirPath, const char *dstDirPath);
int get_file_for_check_staging();
int check_for_staging(char* name);
int search_for_reset(char  name[]);
int run_reset(char * file_path);
int run_status();
int check_in_staging_for_status(char []);
int check_AM_for_status(char [],char []);
int compareFiles(FILE *file1, FILE *file2);
int check_d_for_status(char path_dir[]);
int set_massage(char *,char*);
int replace_massage(char*,char*);
int remove_massage(char *);
int find_message(char * );
char *user_name_commit();
int id_commit(char []);
int id_commit_without_ezafe(char[]);
int id_currnent(char username[]);
int copy_file_in_commit(char [],int );
int creat_commit_for_log(char *,int,char []);
int run_commit(char *);
int run_log();
int run_log_n(int);
int run_log_branch(char []);
int run_log_name(char []);
int run_log_message(char []);
int run_log_time(char*,int);
int make_branch(char []);
int show_branch();
int checkout_branch(char []);
int checkout_id(int );
int checkout_head();
char * message_revert(int id);
int be_revert_past(char [],int ,int ,int,char[]);
int run_revert(char message[],int id,int check);
int run_tag(char name[],char message[],int id,int check);
int tag_show(char name_tag[]);
int tag_sort();
int run_diff_whithout_line(char filename_1[],char filename_2[],char filepath_1[],char filepath_2[]);
int run_diff_line(char filename_1[],char filename_2[],int start_1,int end_1,int start_2,int end_2);
int run_diff_c(char id_1[],char id_2[]);
int run_merge(char branch_1[],char branch_2[]);
// handel nashodan trak dar checkout
/// alias kar dare



#endif