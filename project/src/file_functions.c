#include "file_functions.h"
void print_command(int argc, char * const argv[]) {
    for (int i = 0; i < argc; i++) {
        fprintf(stdout, "%s ", argv[i]);
    }
    fprintf(stdout, "\n");
}
int check_neogit(){
	char cwd[MAX_ARRAY];
if (getcwd(cwd,sizeof(cwd))==NULL) return 1;
char cur_cwd[MAX_ARRAY];
DIR * d;
struct dirent * empty;
int file_exist=0;
do
{
d=opendir(".");
if (d){
	while ((empty=readdir(d))!=NULL)
	{
     if ( (strcmp(empty->d_name,".neogit")==0))
	 file_exist=1;
	}}
	closedir(d);
if (getcwd(cur_cwd,sizeof(cur_cwd))==NULL)return 1;
if (strcmp(cur_cwd,"/")!=0){
	if (chdir("..")!=0)return 1;
}
} while (strcmp(cur_cwd,"/")!=0);
chdir(cwd);
if (file_exist)return 1;
perror("the neogit is not fined\n");
return 0;
}

int init(int argc,char * const argv[]){
char cwd[MAX_ARRAY];
if (getcwd(cwd,sizeof(cwd))==NULL) return 1;
char cur_cwd[MAX_ARRAY];
DIR * d;
struct dirent * empty;
int file_exist=0;
do
{
d=opendir(".");
if (d){
	while ((empty=readdir(d))!=NULL)
	{
     if ( (strcmp(empty->d_name,"./neogit")==0))
	 file_exist=1;
	}}
	closedir(d);
if (getcwd(cur_cwd,sizeof(cur_cwd))==NULL)return 1;
if (strcmp(cur_cwd,"/")!=0){
	if (chdir("..")!=0)return 1;
}
} while (strcmp(cur_cwd,"/")!=0);
chdir(cwd);
if (file_exist){
	perror("neogit is exsists alredy!!!\n");
}
else {
	int status;
    status = mkdir("/mnt/c/project/.neogit",0755);
	if(status == -1) {
        perror("Error creating directory\n");
        return 1;}
	printf("please enter your email and user with git config\n");
	int status_4;
    status_4 = mkdir("/mnt/c/project/.neogit/master",0755);
	if(status_4 == -1) {
        perror("Error creating directory\n");
        return 1;}
	 FILE *file;
	   int status_2;
    status_2 = mkdir("/mnt/c/project/.neogit/master/files",0755);
	if(status_2 == -1) {
        perror("Error creating directory\n");
        return 1;}
	int status_3;
    status_3 = mkdir("/mnt/c/project/.neogit/master/commits",0755);
	if(status_3 == -1) {
        perror("Error creating directory\n");
        return 1;}
       int status_5;
    status_5 = mkdir("/mnt/c/project/.neogit/master/copy_for_staging",0755);
	if(status_5 == -1) {
        perror("Error creating directory\n");
        return 1;}
		int status_6;
    status_6= mkdir("/mnt/c/project/.neogit/all_commits",0755);
	if(status_6 == -1) {
        perror("Error creating directory\n");
        return 1;}
		int status_7= mkdir("/mnt/c/project/.neogit/master/last_commit_files",0755);
	if(status_7 == -1) {
        perror("Error creating directory\n");
        return 1;}
		mkdir("/mnt/c/project/.neogit/master/all_commits_files",0755);
	   file=fopen("/mnt/c/project/.neogit/master/staging.txt","w");
	   if (file==NULL)return 1;
	   fclose(file);

	   file=fopen("/mnt/c/project/.neogit/alias.txt","w");
	   if (file==NULL)return 1;
	   fclose(file);
	   file=fopen("/mnt/c/project/.neogit/branch.txt","w");
	   fprintf(file,"master :*\n");
	   file=fopen("/mnt/c/project/.neogit/master/trak.txt","w");
	   if (file==NULL)return 1;
	   mkdir("/mnt/c/project/.neogit/tag",0755);

}}
int config_user(char user[]){
      FILE *file;
    file = fopen("/mnt/c/project/.neogit/config.txt","a");
    if (file == NULL) {
        perror("Error opening file");
        return(1);}
	   fprintf(file, "%s last_commit_ID: %d\n",user,0);
       fprintf(file, "current_commit_ID: %d\n", 0);
	   fprintf(file,"name:%s\n",user);
       fclose(file);
}
int config_global_user(char user[]){
	  FILE *file;
    file = fopen("/mnt/c/project/.neogit/config_global.txt","a");
    if (file == NULL) {
        perror("Error opening file");
        return(1);}
	   fprintf(file, "%s last_commit_ID: %d\n",user,0);
       fprintf(file, "current_commit_ID: %d\n", 0);
	   fprintf(file,"name:%s\n",user);
       fclose(file);
	   return 0;

}
int config_email(char email[]){
    FILE *file;
    file = fopen("/mnt/c/project/.neogit/config_email.txt","a");
    if (file == NULL) {
        perror("Error opening file");
        return(1);}
		fprintf(file,"email: %s",email);
		return 0;
}
int config_global_email(char email[]){
    FILE *file;
    file = fopen("/mnt/c/project/.neogit/config_email_global.txt","a");
    if (file == NULL) {
        perror("Error opening file");
        return(1);}
		fprintf(file,"email: %s",email);
		return 0;
}
int make_alias(char *command){
	FILE *fp;
	fp=fopen("/mnt/c/project/.neogit/alias.txt","a");
	if (fp==NULL){
		perror("EROR CRATING FILE\n");
		return 1;
	}
    fputs(command,fp);
	return 0;
}
char * search_for_alias(char alias[]){
	FILE *fp;
	fp=fopen("/mnt/c/project/.neogit/alias.txt","r");
	char line[MAX_ARRAY];
	char * where;
	while (fgets(line,MAX_ARRAY,fp)!=NULL)
	{ 
		char copy[MAX_ARRAY];
		strcpy(copy,line);
        char *token=strtok(copy," ");
		token=strtok(NULL," ");
		if(strcmp(token,alias)==0){
		where=strstr(line,alias);
		return where+strlen(alias)+1;}
	   }
	
	return NULL;

}

///  function for find branch
char * branch_where(){
	FILE *file;
	file=fopen("/mnt/c/project/.neogit/branch.txt","r");
	char line[MAX_ARRAY];
	char* branch=malloc(MAX_ARRAY);
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		if (strstr(line,"*")!=NULL){
           sscanf(line,"%s",branch);
		   return branch;
		}
	}
}
///function for copy file
void copy_file(char  file_read[],char file_write[]){
FILE * fp_read,*fp_write;
fp_read=fopen(file_read,"r");
fp_write=fopen(file_write,"w");
char line[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,fp_read)!=NULL){
	fputs(line,fp_write);
}
fclose(fp_read);
fclose(fp_write);
}
////finction ezafe kardan beranch
char *cat_branch(char * namefile){
	char *path=malloc(MAX_ARRAY);
	strcpy(path,"/mnt/c/project/.neogit/");
	strcat(path,branch_where());
	strcat(path,"/");
	strcat(path,namefile);
	return path;

} 
/////del directory

void remove_directory(const char *path) {
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;

    if (d) {
        struct dirent *p;
        r = 0;
        while (!r && (p=readdir(d))) {
            int r2 = -1;
            char *buf;
            size_t len;

            /* Skip the names "." and ".." as we don't want to recurse on them. */
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                continue;

            len = path_len + strlen(p->d_name) + 2; 
            buf = malloc(len);
            if (buf) {
                struct stat statbuf;

                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode))
                        remove_directory(buf);
                    else
                        unlink(buf);
                }
                free(buf);
            }
        }
        closedir(d);
    }

    if (!r)
        rmdir(path);
}
void copy_dir(const char *srcDirPath, const char *dstDirPath) {
    DIR *srcDir;
    struct dirent *entry;
    struct stat srcStat;
    char srcFilePath[1024], dstFilePath[1024];

    srcDir = opendir(srcDirPath);
    if (srcDir == NULL) {
        perror("Error opening source directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(srcDir)) != NULL) {
        snprintf(srcFilePath, sizeof(srcFilePath), "%s/%s", srcDirPath, entry->d_name);
        stat(srcFilePath, &srcStat);

        if (S_ISREG(srcStat.st_mode)) { // If it's a regular file
            snprintf(dstFilePath, sizeof(dstFilePath), "%s/%s", dstDirPath, entry->d_name);

            if (access(dstFilePath, F_OK) == 0) { // If the file already exists in the destination directory
                continue; // Skip copying this file
            }

            // Otherwise, copy the file to the destination directory
            FILE *srcFile = fopen(srcFilePath, "rb");
            FILE *dstFile = fopen(dstFilePath, "wb");

            if (srcFile == NULL || dstFile == NULL) {
                perror("Error opening files");
                fclose(srcFile);
                fclose(dstFile);
                closedir(srcDir);
                exit(EXIT_FAILURE);
            }

            char buffer[1024];
            size_t bytesRead;
            while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
                fwrite(buffer, 1, bytesRead, dstFile);
            }

            fclose(srcFile);
            fclose(dstFile);
        }
    }

    closedir(srcDir);
}

////add and family
int srearch_for_add(char name[]){
char cwd[MAX_ARRAY];
getcwd(cwd,MAX_ARRAY);
DIR * d;
struct dirent * including;
d=opendir(".");
if (d){
	while((including=readdir(d))!=NULL){
		if (strcmp(including->d_name,name)==0 && opendir(including->d_name)){
				DIR * dir;
				dir=opendir(including->d_name);
				chdir(including->d_name);
				while((including = readdir(dir))!=NULL){
					if (!opendir(including) && (strcmp(including->d_name,".")!=0) && (strcmp(including->d_name,"..")!=0)){
						add_file(including->d_name);
					}
				}
				chdir(cwd);
			return 0;
		}
		else if (strcmp(including->d_name,name)==0){
                   return add_file(including->d_name);
			
		}
	}
	closedir(d);
	printf("the file or directory is not found\n");
}

}

int add_file(char name_of_file[]){
	
char * path =realpath(name_of_file,NULL);
FILE * fp;
char  branch[MAX_ARRAY];
fp=fopen("/mnt/c/project/.neogit/branch.txt","r");

char line[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,fp)!=NULL){
if (strstr(line,"*")!=NULL){
sscanf(line,"%s",branch);
}
}
char path_staging[MAX_ARRAY];
strcpy(path_staging,"/mnt/c/project/.neogit/");
strcat(path_staging,branch);
strcat(path_staging,"/staging.txt");
fp=fopen(path_staging,"a+");

char file_path_copy[MAX_ARRAY];
strcpy(file_path_copy,"/mnt/c/project/.neogit/");
strcat(file_path_copy,branch);
strcat(file_path_copy,"/copy_for_staging/");
strcat(file_path_copy,name_of_file);
char line_2[MAX_ARRAY];
while(fgets(line_2,MAX_ARRAY,fp)!=NULL){
	if(line_2[strlen(line_2)-1]=='\n')line_2[strlen(line_2)-1]='\0';
      if (strcmp(path,line_2)==0){
		       copy_file(path,file_path_copy);
			   printf("this file alredy is in staging erea\n");
			   return 0;
	  }}
	  
            copy_file(path,file_path_copy);
			fprintf(fp,"%s\n",path);
			printf("staging %s is successful\n",name_of_file);
			return 0;

}

int get_file_for_check_staging() {
	char * path;
	DIR * d;
    struct dirent * including;
    d=opendir(".");
	char cwd[MAX_ARRAY];
	getcwd(cwd,MAX_ARRAY);
	
if (d){
	while((including=readdir(d))!=NULL){
		if (opendir(including->d_name) && strstr(including->d_name,".")==NULL ){
           DIR * dir;
           struct dirent * entry;
           dir=opendir(including->d_name);
		   chdir(including->d_name);
		   while((entry=readdir(dir))!=NULL){
			if (!(opendir(entry->d_name))){
				path=realpath(entry->d_name,NULL);
                check_for_staging(path);
			}
		   }
		   chdir(cwd);
		}
		else if ((strcmp(including->d_name,".")!=0) && (strcmp(including->d_name,"..")!=0) && !opendir(including->d_name)) {
			path=realpath(including->d_name,NULL);
		 check_for_staging(path);}
}closedir(d);
}}
int check_for_staging(char* name){
	         FILE * fp;
            char  branch[MAX_ARRAY];
            fp=fopen("/mnt/c/project/.neogit/branch.txt","r");
            char line[MAX_ARRAY];
        while(fgets(line,MAX_ARRAY,fp)!=NULL){
           if (strstr(line,"*")!=NULL){
           sscanf(line,"%s",branch);}}

			int shod=0;
			char path_stag[MAX_ARRAY];
			strcpy(path_stag,"/mnt/c/project/.neogit/");
			strcat(path_stag,branch);
			strcat(path_stag,"/staging.txt");
			fp=fopen(path_stag,"r");
			if (fp==NULL){
				perror("eror!!");
				return 1;
			}
			while(fgets(line,MAX_ARRAY,fp)!=NULL){
				int lengh=strlen(line);
				if(line[lengh-1]=='\n' )line[lengh-1]='\0';
				if (strcmp(name,line)==0){
					printf("%s is staged\n",name);
					shod=1;
					
				}
			}
			if(!shod) printf("%s is not staged\n",name);
			return 0;
		} 

///////reset 


int search_for_reset(char name[]){
	DIR * d;
  struct dirent * including;
	char * path;
    d=opendir(".");
	char cwd[MAX_ARRAY];
	getcwd(cwd,MAX_ARRAY);
if (d){
	while((including=readdir(d))!=NULL){
		if (opendir(including->d_name) && strcmp(including->d_name,name)==0){
			DIR * dir;
			struct dirent * entry;
			dir=opendir(including->d_name);
			while((entry=readdir(dir))!=NULL){
				chdir(including->d_name);
				if (!opendir(entry->d_name) && strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
					  path=realpath(entry->d_name,NULL);
                      run_reset(path);
				}
				chdir(cwd);
			}
			return 0;
		}
		else if (strcmp(including->d_name,name)==0){
			     path=realpath(including->d_name,NULL);
                 run_reset(path);
				 return 0;
		}
}printf("the file or directory is not found\n");
}}
int run_reset(char * filepath){
int check=0;
char branch[MAX_ARRAY];
strcpy(branch,branch_where());
char path_staging[MAX_ARRAY];
char tmp_path_staging[MAX_ARRAY];
strcpy(path_staging,"/mnt/c/project/.neogit/");
strcat(path_staging,branch);
strcpy(tmp_path_staging,path_staging);
strcat(path_staging,"/staging.txt");
strcat(tmp_path_staging,"/tmpstaging.txt");
FILE *file_read, *file_write;
file_read=fopen(path_staging,"r");
file_write=fopen(tmp_path_staging,"w");
char line[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,file_read)!=NULL){
	if (line[strlen(line)-1]=='\n')line[strlen(line)-1]='\0';
	if (strcmp(line,filepath)!=0){
		fputs(line,file_write);
		fputs("\n",file_write);
	}
	else check=1;
}
remove(path_staging);
rename(tmp_path_staging,path_staging);
///////
if (check){
char namefile[MAX_ARRAY];
char *token=strtok(filepath,"/");
while(token!=NULL){
	token=strtok(NULL,"/");
	if (token!=NULL)strcpy(namefile,token);
}
char namefile_compl[MAX_ARRAY];
strcpy(namefile_compl,"/mnt/c/project/.neogit/");
strcat(namefile_compl,branch);
strcat(namefile_compl,"/copy_for_staging/");
strcat(namefile_compl,namefile);
remove(namefile_compl);
printf("reset of %s done successfuly\n",namefile);}
else printf("this file alredy is not stage\n");
}
 int run_status(){
	        DIR * dir;
			struct dirent *entry;
			dir=opendir(".");
			char cwd[MAX_ARRAY];
			getcwd(cwd,MAX_ARRAY);
			while((entry=readdir(dir))!=NULL){
				if(!opendir(entry->d_name)){
				printf("%s :",entry->d_name);
				check_in_staging_for_status(realpath(entry->d_name,NULL));
				check_AM_for_status(realpath(entry->d_name,NULL),entry->d_name);
			}}
			check_d_for_status(cwd);
 }
 int check_in_staging_for_status(char path[]){
     FILE *file;
   	file=fopen(cat_branch("staging.txt"),"r");
    char line[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		if(line[strlen(line)-1]=='\n')line[strlen(line)-1]='\0';
		if(strcmp(line,path)==0){
			printf("+");
			return 0;
		}
	}
	printf("-");
 }
int check_AM_for_status(char path[],char namefile[]){
            DIR * dir;
			struct dirent * entry;
			dir=opendir(cat_branch("last_commit_files"));
			char cwd[MAX_ARRAY];
			getcwd(cwd,MAX_ARRAY);
			while((entry=readdir(dir))!=NULL){
				if(strcmp(namefile,entry->d_name)==0){
					chdir(cat_branch("last_commit_files"));
                    FILE *file_1;
					file_1=fopen(realpath(entry->d_name,NULL),"r");
					FILE *file_2;
                    file_2=fopen(path,"r");
					if(compareFiles(file_1,file_2)==0){
						printf("A\n");
					}
					else printf("M\n");
					chdir(cwd);
					return 0;
				}
			}
			printf("is not traked\n");
			return 0;
 }
 int compareFiles(FILE *file1, FILE *file2) {
    char ch1 = getc(file1);
    char ch2 = getc(file2);

    while (ch1 != EOF && ch2 != EOF) {
        if (ch1 != ch2) {
            return 1; // Files are not equal
        }
        ch1 = getc(file1);
        ch2 = getc(file2);
    }

    // Check if both files have ended
    if (ch1 == EOF && ch2 == EOF) {
        return 0; // Files are equal
    } else {
        return 1; // Files are not equal
    }
}
int check_d_for_status(char path_dir[]){
FILE *file_trak;
file_trak=fopen(cat_branch("trak.txt"),"r");
char line[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,file_trak)!=NULL){
	if(line[strlen(line)-1]=='\n')line[strlen(line)-1]='\0';
	if(strstr(line,path_dir)!=NULL){ 
		    int found=0;
            DIR * dir;
			struct dirent * entry;
			dir=opendir(".");
			while((entry=readdir(dir))!=NULL){
				if(!opendir(entry->d_name)){
			if(strcmp(realpath(entry->d_name,NULL),line)==0 )found=1;}}

			if(!found){
				printf("%s :",line);
				check_in_staging_for_status(line);
				printf("D\n");}
			

			
			
}
	}}









int set_massage(char *massage,char * name){
FILE *file;
char message_name[MAX_ARRAY];
strcpy(message_name,"/mnt/c/project/.neogit/");
strcat(message_name,branch_where());
strcat(message_name,"/massage_of_commits.txt");
file=fopen(message_name,"a");
if (file==NULL){
	perror("eror for open the file_massage ");
	return 1;
}
fprintf(file,"%s:%s:\n",massage,name);
printf("the shortcut creat succfuly!!\n");
return 0;
}
int replace_massage(char *new_message,char*target_name){
FILE *file;
char message_name[MAX_ARRAY];
char tmp_message_name[MAX_ARRAY];
strcpy(message_name,"/mnt/c/project/.neogit/");
strcat(message_name,branch_where());
strcpy(tmp_message_name,message_name);
strcat(message_name,"/massage_of_commits.txt");
strcat(tmp_message_name,"/tmp_massage_of_commits.txt");
file=fopen(message_name,"r");
if (file==NULL){
	perror("eror for open massage_file\n");
	return 1;
}


FILE *tmp_file;
tmp_file=fopen(tmp_message_name,"w");
if (file==NULL){
	perror("eror for open massage_file\n");
	return 1;
}
char line[MAX_ARRAY];
char* massage;
char* name;
int check=0;
while(fgets(line,MAX_ARRAY,file)!=NULL){
massage=strtok(line,":");
name=strtok(NULL,":");
if (strcmp(name,target_name)==0){
    fprintf(tmp_file,"%s:%s:\n",new_message,target_name);
	check=1;
}
else fprintf(tmp_file,"%s:%s:\n",massage,name);
}
remove(message_name);
rename(tmp_message_name,message_name);
if (check)printf("the replace shortcut successful!!\n");
else printf("the shortcut is not exist\n");
return 0;
}



int remove_massage(char * name_target){
	FILE  *fp,*tmpfile;
	char message_name[MAX_ARRAY];
     strcpy(message_name,"/mnt/c/project/.neogit/");
     strcat(message_name,branch_where());
     strcat(message_name,"/massage_of_commits.txt");
    fp=fopen(message_name,"r");
	if (fp==NULL){
	perror("eror for open massage_file\n");
	return 1;
}
    char tmp_message_name[MAX_ARRAY];
	strcpy(tmp_message_name,message_name);
	strcat(tmp_message_name,"tmp");
	tmpfile=fopen(tmp_message_name,"w");
	if (tmpfile==NULL){
	perror("eror for open massage_file\n");
	return 1;
}
char line[MAX_ARRAY];
char* massage;
char* name ;
int check=0;
while(fgets(line,MAX_ARRAY,fp)!=NULL){
	massage=strtok(line,":");
	name=strtok(NULL,":");
	if (strcmp(name,name_target)==0){
       check=1;
	}
	else  fprintf(tmpfile,"%s:%s:\n",massage,name);
}
if (check)printf("the shortcut remove successfuly!!\n");
else printf("the shortcut not found!!\n");
remove(message_name);
rename(tmp_message_name,message_name);
return 0;
}

int find_message(char * target_name){
FILE *file;
char message_name[MAX_ARRAY];
strcpy(message_name,"/mnt/c/project/.neogit/");
strcat(message_name,branch_where());
strcat(message_name,"/massage_of_commits.txt");
file=fopen(message_name,"r");
if (fopen==NULL){
	perror(" eror for opening the massage of commits\n");
	return 1;
}
char line[MAX_ARRAY];
char * message;
char * name;
while(fgets(line,MAX_ARRAY,file)!=NULL){
message=strtok(line,":");
name=strtok(NULL,":");
if (strcmp(name,target_name)==0){
    run_commit(message);
	fclose(file);
	return 0;
}
}
printf("the shortcut not found!!\n");
return 1;
}

char *user_name_commit(){
	struct stat st;
	FILE *file;
	file=fopen("/mnt/c/project/.neogit/config.txt","r");
	if (stat("/mnt/c/project/.neogit/config.txt",&st)!=0){
		perror("eror\n");
	}
    if (file==NULL || st.st_size==0 ){
		file=fopen("/mnt/c/project/.neogit/config_global.txt","r");
		if (stat("/mnt/c/project/.neogit/config_global.txt",&st)!=0){
		perror("eror\n");
	}
		if(file==NULL ||  st.st_size==0  ){
			printf("who are you ?? enter the username \n");
			return NULL;
		}
	}
char line[MAX_ARRAY];
char* name=malloc(MAX_ARRAY);
while(fgets(line,MAX_ARRAY,file)!=NULL){
	if (strstr(line,"last_commit_ID")!=NULL){
		sscanf(line,"%s",name);
	}
}
return name;
}

int id_commit(char username[]){
	int id;
	int check=0;
	FILE *file,*tmpfile;
	file=fopen("/mnt/c/project/.neogit/config.txt","r");
	tmpfile=fopen("/mnt/c/project/.neogit/tmpconfig.txt","w");
	if (file==NULL){
	file=fopen("/mnt/c/project/.neogit/config_global.txt","r");
	check=1;
	}
	char line[MAX_ARRAY];
	char name[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		sscanf(line,"%s",name);
		if (strcmp(name,username)==0){
           sscanf(line,"%s last_commit_ID: %d\n",name,&id);
		   fprintf(tmpfile,"%s last_commit_ID: %d\n",name,++id);
		   fgets(line,MAX_ARRAY,file);
		   fprintf(tmpfile,"current_commit_ID: %d\n",id);
		}
		else fputs(line,tmpfile);
	}
	fclose(tmpfile);
	if (check){
        remove("/mnt/c/project/.neogit/config_global.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config_global.txt");
	}
	else{
       remove("/mnt/c/project/.neogit/config.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config.txt");
	}
	return id;
}
int id_commit_without_ezafe(char username[]){
	int id;
	int check=0;
	FILE *file,*tmpfile;
	file=fopen("/mnt/c/project/.neogit/config.txt","r");
	tmpfile=fopen("/mnt/c/project/.neogit/tmpconfig.txt","w");
	if (file==NULL){
	file=fopen("/mnt/c/project/.neogit/config_global.txt","r");
	check=1;
	}
	char line[MAX_ARRAY];
	char name[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		sscanf(line,"%s",name);
		if (strcmp(name,username)==0){
           sscanf(line,"%s last_commit_ID: %d\n",name,&id);
		   fprintf(tmpfile,"%s last_commit_ID: %d\n",name,id);
		}
		else fputs(line,tmpfile);
	}fclose(tmpfile); 
	if (check){
        remove("/mnt/c/project/.neogit/config_global.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config_global.txt");
	}
	else{
       remove("/mnt/c/project/.neogit/config.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config.txt");
	}
	return id;
}
int id_currnent(char username[]){
	int id;
	int check=0;
	FILE *file,*tmpfile;
	file=fopen("/mnt/c/project/.neogit/config.txt","r");
	tmpfile=fopen("/mnt/c/project/.neogit/tmpconfig.txt","w");
	if (file==NULL){
	file=fopen("/mnt/c/project/.neogit/config_global.txt","r");
	check=1;
	}
	char line[MAX_ARRAY];
	char name[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		sscanf(line,"%s",name);
		if (strcmp(name,username)==0){
		   fputs(line,tmpfile);
           fgets(line,MAX_ARRAY,file);
		   sscanf(line,"current_commit_ID :%d\n",&id);
		   fputs(line,tmpfile);
		}
		else fputs(line,tmpfile);
	}fclose(tmpfile); 
	if (check){
        remove("/mnt/c/project/.neogit/config_global.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config_global.txt");
	}
	else{
       remove("/mnt/c/project/.neogit/config.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config.txt");
	}
	return id;
}
int copy_file_in_commit(char name_dir[],int id){
char path_dir_files [MAX_ARRAY];
strcpy(path_dir_files,cat_branch("files"));
int check=0;

    DIR *dir = opendir(path_dir_files);
    struct dirent *entry;
    if (dir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if ( strcmp(entry->d_name, name_dir) == 0) check=1;
    }
if(!check){
int status;
strcat(path_dir_files,"/");
strcat(path_dir_files,name_dir);
status=mkdir(path_dir_files,0755);
if(status!=0){
	perror("eroe in creating directory\n");
	return 1;
}
}
char file_read[MAX_ARRAY];
strcpy(file_read,"/mnt/c/project/.neogit/");
strcat(file_read,branch_where());
strcat(file_read,"/copy_for_staging/");
strcat(file_read,name_dir);

char file_write[MAX_ARRAY];
strcpy(file_write,"/mnt/c/project/.neogit/");
strcat(file_write,branch_where());
strcat(file_write,"/files/");
strcat(file_write,name_dir);
strcat(file_write,"/");
char temp[MAX_ARRAY];
sprintf(temp,"%d",id);
strcat(file_write,temp);
strcat(file_write,name_dir);
copy_file(file_read,file_write);

char path_file_commits[MAX_ARRAY];
strcpy(path_file_commits,cat_branch("all_commits_files/"));
strcat(path_file_commits,temp);
strcat(path_file_commits,"/");
strcat(path_file_commits,name_dir);
copy_file(file_read,path_file_commits);

char path_head[MAX_ARRAY];
strcpy(path_head,cat_branch("last_commit_files/"));
strcat(path_head,name_dir);
    DIR *dp;
	int found=0;
	struct dirent *includ;
	dp=opendir(cat_branch("last_commit_files"));
	while((includ=readdir(dp)) !=NULL){
		if(strcmp(includ->d_name,name_dir)==0){
			copy_file(file_read,path_head);
			found=1;
		}
	}
if(!found)copy_file(file_read,path_head);
remove(file_read);
}
int creat_commit_for_log(char * message,int id,char user[] ){
char file_path_commits[MAX_ARRAY];
char file_all[MAX_ARRAY];
strcpy(file_all,"/mnt/c/project/.neogit/all_commits/");
strcpy(file_path_commits,cat_branch("commits/"));
char tmp[10];
sprintf(tmp,"%d",id);
strcat(file_path_commits,tmp);
strcat(file_path_commits,".txt");
strcat(file_all,tmp);
strcat(file_all,".txt");
FILE *file_read,*file_write;
file_write=fopen(file_path_commits,"w");
file_read=fopen(cat_branch("staging.txt"),"r");
int number=0;
char line[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,file_read)!=NULL){
	fputs(line,file_write);
	number++;
}
fprintf(file_write,"%d files done commit successful\n",number);
fprintf(file_write,"user:%s\n",user);
fprintf(file_write,"message:%s\n",message);
fprintf(file_write,"id:%d\n",id);
fprintf(file_write,"branch:%s\n",branch_where());
time_t t;
time(&t);
fprintf(file_write,"time:%s\n",ctime(&t));
fclose(file_write);
copy_file(file_path_commits,file_all);
return 0;

}
int tark_in_commit(){
	FILE *file_staging,*file_trak;
	file_staging=fopen(cat_branch("staging.txt"),"r");
    file_trak=fopen(cat_branch("trak.txt"),"a+");
    char line_1[MAX_ARRAY];
	char line_2[MAX_ARRAY];
	while(fgets(line_1,MAX_ARRAY,file_staging)!=NULL){
		int found=0;
		while(fgets(line_2,MAX_ARRAY,file_trak)!=NULL){
			if(strcmp(line_1,line_2)==0)found=1;
		}
		if(!found)fputs(line_1,file_trak);
	}
	return 0;
}

int run_commit(char * message){
char username[MAX_ARRAY];
if (user_name_commit()!=NULL)strcpy(username,user_name_commit());
else return 1;
int id=id_commit(username);

FILE * file;
file=fopen(cat_branch("staging.txt"),"r");
struct stat st;
if (stat(cat_branch("staging.txt"), &st) != 0) {
        perror("Error stating file");
        return -1;
    }
if (st.st_size == 0){
	printf("staging is empty\n");
	return 0;
}
creat_commit_for_log(message,id,username);
char path_dir[MAX_ARRAY];
strcpy(path_dir,cat_branch("all_commits_files/"));
char temp[10];
sprintf(temp,"%d",id);
strcat(path_dir,temp);
mkdir(path_dir,0755);
char *token;
char line[MAX_ARRAY];
char namefile[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,file)!=NULL){
	token=strtok(line,"/");
	while(token!=NULL){
		token=strtok(NULL,"/");
		if(token!=NULL)strcpy(namefile,token);
	}
	if (namefile[strlen(namefile)-1]=='\n')namefile[strlen(namefile)-1]='\0';
	copy_file_in_commit(namefile,id);
}

   char path_dir_read[MAX_ARRAY];
   char path_dir_write[MAX_ARRAY];
   strcpy(path_dir_read,cat_branch("all_commits_files"));
   strcpy(path_dir_write,cat_branch("all_commits_files/"));
   strcat(path_dir_write,temp);
    DIR *dp;
	struct dirent *includ;
	dp=opendir(path_dir_read);
	while((includ=readdir(dp)) !=NULL){
		if(strcmp(includ->d_name,path_dir_write)!=0 && strcmp(includ->d_name,".")!=0 && strcmp(includ->d_name,"..")!=0 ){
			char path_dir_read_main[MAX_ARRAY];
			strcpy(path_dir_read_main,path_dir_read);
			strcat(path_dir_read_main,"/");
			strcat(path_dir_read_main,includ->d_name);
			copy_dir(path_dir_read_main,path_dir_write);
		}
	}
   

tark_in_commit();
remove(cat_branch("staging.txt"));
file=fopen(cat_branch("staging.txt"),"w");
time_t t;
time(&t);
printf("commit with message : %s ,on time : %s by : %s with id : %d done successfuly\n",message,ctime(&t),username,id);
}
///  /log and moshtaghtash
/// 
int run_log(){
	char filename[MAX_ARRAY][100];
	int index=0;
	DIR *dir;
	struct dirent *entry;
	dir=opendir("/mnt/c/project/.neogit/all_commits");
	while((entry=readdir(dir)) !=NULL){
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ){
		strcpy(filename[index],"/mnt/c/project/.neogit/all_commits/");
		strcat(filename[index],entry->d_name);
		index++;}}
		for(int i=index-1;i>=0;i--){
		FILE *fp;
		fp=fopen(filename[i],"r");
		char line[MAX_ARRAY];
		while(fgets(line,MAX_ARRAY,fp)!=NULL){
			printf("%s",line);
		}
		fclose(fp);}
	}
int run_log_n(int num){
char filename[MAX_ARRAY][100];
	int index=0;
	DIR *dir;
	struct dirent *entry;
	dir=opendir("/mnt/c/project/.neogit/all_commits");
	while((entry=readdir(dir)) !=NULL){
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ){
		strcpy(filename[index],"/mnt/c/project/.neogit/all_commits/");
		strcat(filename[index],entry->d_name);
		index++;}}
		index--;
		while(num>0){
		FILE *fp;
		fp=fopen(filename[index],"r");
		char line[MAX_ARRAY];
		while(fgets(line,MAX_ARRAY,fp)!=NULL){
			printf("%s",line);
		}
		fclose(fp);
		num--;
		index--;
		}
		return 0;
}
int run_log_branch(char branch_target[]){
	FILE *file;
	int check=0;
	file=fopen("/mnt/c/project/.neogit/branch.txt","r");
    char line[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		char branch[MAX_ARRAY];
		sscanf(line,"%s",branch);
		if (strcmp(branch,branch_target)==0)check=1;
	}
if (!check){
	printf("this branch is not found\n");
	return 0;}
else{
char path_dir[MAX_ARRAY];
strcpy(path_dir,"/mnt/c/project/.neogit/");
strcat(path_dir,branch_target);
strcat(path_dir,"/commits");
DIR *dir;
	struct dirent *entry;
	dir=opendir(path_dir);
	while((entry=readdir(dir)) !=NULL){
	char filepath[MAX_ARRAY];
	strcpy(filepath,path_dir);
	strcat(filepath,"/");
	strcat(filepath,entry->d_name);
	FILE *file;
	file=fopen(filepath,"r");
	char line[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		printf("%s",line);
	}
}
return 0;
}
}

int run_log_name(char name_target[]){
char filename[MAX_ARRAY][100];
	int index=0;
	DIR *dir;
	struct dirent *entry;
	dir=opendir("/mnt/c/project/.neogit/all_commits");
	while((entry=readdir(dir)) !=NULL){
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ){
		strcpy(filename[index],"/mnt/c/project/.neogit/all_commits/");
		strcat(filename[index],entry->d_name);
		index++;}}
		for(int i=index-1;i>=0;i--){
		int check=0;
		FILE *fp;
		fp=fopen(filename[i],"r");
		char line[MAX_ARRAY];
        char name[MAX_ARRAY];
		while(fgets(line,MAX_ARRAY,fp)!=NULL){
			if(strstr(line,"user")!=NULL ){
                sscanf(line,"user:%s\n",name);
                if (strcmp(name,name_target)==0)check=1;
			}
		}
		fclose(fp);
		if (check){
			fp=fopen(filename[i],"r");
			while(fgets(line,MAX_ARRAY,fp)!=NULL){
				printf("%s",line);
			}
		}


}}
int run_log_message(char word[]){
char filename[MAX_ARRAY][100];
	int index=0;
	DIR *dir;
	struct dirent *entry;
	dir=opendir("/mnt/c/project/.neogit/all_commits");
	while((entry=readdir(dir)) !=NULL){
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ){
		strcpy(filename[index],"/mnt/c/project/.neogit/all_commits/");
		strcat(filename[index],entry->d_name);
		index++;}}
		for(int i=index-1;i>=0;i--){
		int check=0;
		FILE *fp;
		fp=fopen(filename[i],"r");
		char line[MAX_ARRAY];
        char name[MAX_ARRAY];
		while(fgets(line,MAX_ARRAY,fp)!=NULL){
			if(strstr(line,"message")!=NULL ){
                if (strstr(line,word)!=NULL)check=1;
			}
		}
		fclose(fp);
		if (check){
			fp=fopen(filename[i],"r");
			while(fgets(line,MAX_ARRAY,fp)!=NULL){
				printf("%s",line);
			}
		}


}}
int run_log_time(char* target_time,int mod){
char filename[MAX_ARRAY][100];
	int index=0;
	DIR *dir;
	struct dirent *entry;
	dir=opendir("/mnt/c/project/.neogit/all_commits");
	while((entry=readdir(dir)) !=NULL){
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ){
		strcpy(filename[index],"/mnt/c/project/.neogit/all_commits/");
		strcat(filename[index],entry->d_name);
		index++;}}
		for(int i=index-1;i>=0;i--){
		int check=0;
		FILE *fp;
		fp=fopen(filename[i],"r");
		char line[MAX_ARRAY];
        char name[MAX_ARRAY];
		while(fgets(line,MAX_ARRAY,fp)!=NULL){
			if(strstr(line,"time")!=NULL ){
                char time[MAX_ARRAY];
				char *token=strtok(line,":");
				token=strtok(NULL,"\n");
				strcpy(time,token);
				struct tm time1 = {0};
                struct tm time2 = {0};
                strptime(time, "%a %b %d %T %Y", &time1);
                strptime(target_time, "%a %b %d %T %Y", &time2);
			    time_t time1Sec = mktime(&time1);
                time_t time2Sec = mktime(&time2);
				if (time1Sec<time2Sec && mod==0)check=1;
				if(time1Sec>time2Sec && mod==1)check=1;
			}
		}
		fclose(fp);
		if (check){
			fp=fopen(filename[i],"r");
			while(fgets(line,MAX_ARRAY,fp)!=NULL){
				printf("%s",line);
			}
		}


}}

int make_branch(char name_branch_target[]){
	int found=0;
	FILE *file,*tmp_file;
	file=fopen("/mnt/c/project/.neogit/branch.txt","r");
	char line[MAX_ARRAY];
	char name_branch[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		sscanf(line,"%s",name_branch);
		if(strcmp(name_branch,name_branch_target)==0){
               found=1;
			   break;
		}
	}
	fclose(file);
	if (found)printf("this branch alredy is exist\n");
	if (!found){
        tmp_file=fopen("/mnt/c/project/.neogit/tmp_branch.txt","w");
		file=fopen("/mnt/c/project/.neogit/branch.txt","r");
		while(fgets(line,MAX_ARRAY,file)!=NULL){
			fputs(line,tmp_file);
		}
		fprintf(tmp_file,"%s\n",name_branch_target);

	remove("/mnt/c/project/.neogit/branch.txt");
	rename("/mnt/c/project/.neogit/tmp_branch.txt","/mnt/c/project/.neogit/branch.txt");
	///////////////////////
	char path_dir[MAX_ARRAY];
	strcpy(path_dir,"/mnt/c/project/.neogit/");
	strcat(path_dir,name_branch_target);
	int status=mkdir(path_dir,0755);
	if (status!=0){
		perror("eror on creating directory\n");
		return 1;
	}
	char path_commits[MAX_ARRAY];
	char path_all_commits[MAX_ARRAY];
	strcpy(path_all_commits,path_dir);
	strcat(path_all_commits,"/all_commits_files");
	mkdir(path_all_commits,0755);
	char path_trak[MAX_ARRAY];
	char path_files[MAX_ARRAY];
	char path_staging[MAX_ARRAY];
	char path_copy_for_stage[MAX_ARRAY];
	char path_last_commits[MAX_ARRAY];
	strcpy(path_trak,path_dir);
	strcat(path_trak,"/trak.txt");
	strcpy(path_last_commits,path_dir);
	strcpy(path_commits,path_dir);
	strcpy(path_files,path_dir);
	strcpy(path_staging,path_dir);
	strcpy(path_copy_for_stage,path_dir);
	strcat(path_commits,"/commits");
	strcat(path_files,"/files");
	strcat(path_copy_for_stage,"/copy_for_staging");
	strcat(path_staging,"/staging.txt");
	strcat(path_last_commits,"/last_commit_files");
	mkdir(path_commits,0755);
	mkdir(path_files,0755);
	mkdir(path_copy_for_stage,0755);
	mkdir(path_last_commits,0755);
	FILE *fp;
	fp=fopen(path_staging,"w");
	FILE *f;
	f=fopen(path_trak,"w");
	printf("branch maked successfuly\n");
	return 0;
}
}
int show_branch(){
	FILE *file;
	file=fopen("/mnt/c/project/.neogit/branch.txt","r");
	char line[MAX_ARRAY];
	char branch[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		printf("%s",line);
	}
	return 0;
}

int checkout_branch(char branch_target[]){
	// FILE *staging_file;
	// staging_file=fopen(cat_branch("staging.txt"),"r");
	char line[MAX_ARRAY];
	// if (fgets(line,MAX_ARRAY,staging_file)!=NULL){
    //     printf("Some added files were not committed\n");
	// 	return 0;
	// }
	FILE *file,*tmp_file;
	char branch[MAX_ARRAY];
    tmp_file=fopen("/mnt/c/project/.neogit/tmp_branch.txt","w");
	file=fopen("/mnt/c/project/.neogit/branch.txt","r");
		while(fgets(line,MAX_ARRAY,file)!=NULL){
			sscanf(line,"%s",branch);
			if(strcmp(branch,branch_target)!=0)fprintf(tmp_file,"%s\n",branch);
		}
		fprintf(tmp_file,"%s :*\n",branch_target);

	remove("/mnt/c/project/.neogit/branch.txt");
	rename("/mnt/c/project/.neogit/tmp_branch.txt","/mnt/c/project/.neogit/branch.txt");
	printf("check out %s done successfuly\n",branch_target);
return 0;
}

int checkout_id(int id){
	int check=0;
	FILE *file,*tmpfile;
	file=fopen("/mnt/c/project/.neogit/config.txt","r");
	tmpfile=fopen("/mnt/c/project/.neogit/tmpconfig.txt","w");
	if (file==NULL){
	file=fopen("/mnt/c/project/.neogit/config_global.txt","r");
	check=1;
	}
	char line[MAX_ARRAY];
	char name[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,file)!=NULL){
		sscanf(line,"%s",name);
		if (strcmp(name,user_name_commit())==0){
           fputs(line,tmpfile);
		   fgets(line,MAX_ARRAY,file);
		   fprintf(tmpfile,"current_commit_ID: %d\n",id);
		}
		else fputs(line,tmpfile);
	}
	fclose(tmpfile);
	if (check){
        remove("/mnt/c/project/.neogit/config_global.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config_global.txt");
	}
	else{
       remove("/mnt/c/project/.neogit/config.txt");
		rename("/mnt/c/project/.neogit/tmpconfig.txt","/mnt/c/project/.neogit/config.txt");
	}
	////foUnd branch commit 
	FILE *all_commits;
	char tmp[10];
	char path_all_commits[MAX_ARRAY];
	sprintf(tmp,"%d.txt",id);
    strcpy(path_all_commits,"/mnt/c/project/.neogit/all_commits/");
	strcat(path_all_commits,tmp);
	all_commits=fopen(path_all_commits,"r");
	if(fopen==NULL){
		perror("eror \n");
		return 0;
	}
	char branch[MAX_ARRAY];
	while(fgets(line,MAX_ARRAY,all_commits)!=NULL){
		if(strstr(line,"branch:")!=NULL){
			sscanf(line,"branch:%s\n",branch);
			break;
		}
	}
	checkout_branch(branch);
	//////copy in header 
	char path_last_status[MAX_ARRAY];
	strcpy(path_last_status,"/mnt/c/project/.neogit/");
	strcat(path_last_status,branch);
	strcat(path_last_status,"/last_commit_files");
	remove_directory(path_last_status);
	mkdir(path_last_status,0755);

	char path_dir_commit[MAX_ARRAY];
	strcpy(path_dir_commit,"/mnt/c/project/.neogit/");
    strcat(path_dir_commit,branch);
	strcat(path_dir_commit,"/all_commits_files/");
	char temp[10];
	sprintf(temp,"%d",id);
	strcat(path_dir_commit,temp);
	copy_dir(path_dir_commit,path_last_status);
	printf("checkout on %d_id done successful\n",id);
return 0;
}

int checkout_head(){
FILE *file;
file=fopen("/mnt/c/project/.neogit/config.txt","r");
if(file==NULL){
	file=fopen("/mnt/c/project/.neogit/config_global.txt","r");
	if(file==NULL){
		printf("please log in\n");
		return 0;
	}
}
char line[MAX_ARRAY];
int id;
char name[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,file)!=NULL){
	if(strstr(line,"last_commit_ID")!=NULL){
      sscanf(line,"%s last_commit_ID: %d",name,&id);
	}
}
checkout_id(id);
return 0;
}
char * message_revert(int id){
  FILE *file;
  char path_file_all_commits[]="/mnt/c/project/.neogit/all_commits/";
  char temp[10];
  sprintf(temp,"%d.txt",id);
  strcat(path_file_all_commits,temp);
  file=fopen(path_file_all_commits,"r");
  char line[MAX_ARRAY];
  char *message=malloc(MAX_ARRAY);
  while(fgets(line,MAX_ARRAY,file)!=NULL){
	if(strstr(line,"message")!=	NULL){
         sscanf(line,"message:%s",message);
		 break;
	}
  }
  return message;

}
int be_revert_past(char branch[],int id,int id_new,int check,char message[]){
int id_file;
int id_read;
int found=0;
char path_dir_commits[MAX_ARRAY]="/mnt/c/project/.neogit/";
strcat(path_dir_commits,branch);
strcat(path_dir_commits,"/all_commits_files");
    DIR *dir;
	struct dirent *entry;
	dir=opendir(path_dir_commits);
	while((entry=readdir(dir)) !=NULL){
		if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
		sscanf(entry->d_name,"%d",&id_file);
		if(id_file<id){
			id_read=id_file;
			found=1;}}
}
if(found){
char path_id[MAX_ARRAY];
strcpy(path_id,path_dir_commits);
char path_last_commit_files[MAX_ARRAY]="/mnt/c/project/.neogit/";
strcat(path_last_commit_files,branch);
strcat(path_last_commit_files,"/last_commit_files");
strcat(path_id,"/");
char temp[10];
sprintf(temp,"%d",id_read);
strcat(path_id,temp);
remove_directory(path_last_commit_files);
mkdir(path_last_commit_files,0755);
copy_dir(path_id,path_last_commit_files);
if(check){
	char path_all_commit_files[MAX_ARRAY]="/mnt/c/project/.neogit/";
	strcat(path_all_commit_files,branch);
	char username[MAX_ARRAY];
    char id_str[10];
	strcat(path_all_commit_files,"/all_commits_files/");
	sprintf(id_str,"%d",id_new);
	strcat(path_all_commit_files,id_str);
	mkdir(path_all_commit_files,0755);
	copy_dir(path_id,path_all_commit_files);
	FILE *fp;
	char path_fp[MAX_ARRAY]="/mnt/c/project/.neogit/";
	strcat(path_fp,branch);
	strcat(path_fp,"/commits/");
	strcat(path_fp,id_str);
	strcat(path_fp,".txt");
	fp=fopen(path_fp,"w");
	// fprintf(fp,"user:%s\n",user_name_commit());
	fprintf(fp,"message:%s\n",message);
	fprintf(fp,"id:%d\n",id_new);
	fprintf(fp,"branch:%s\n",branch);
    time_t t;
    time(&t);
    fprintf(fp,"time:%s\n",ctime(&t));
	fclose(fp);
	printf("commit %s in %s with message:%s done successfull \n",ctime(&t),branch,message);
}
return 0;
}}

int run_revert(char message[],int id,int check){
	 FILE *f_branch;
	 f_branch=fopen("/mnt/c/project/.neogit/branch.txt","r");
	 char line[MAX_ARRAY];
	 char branch[MAX_ARRAY];
    int id_new=id_commit(user_name_commit());
	 while(fgets(line,MAX_ARRAY,f_branch)!=NULL){
		sscanf(line,"%s",branch);
		be_revert_past(branch,id,id_new,check,message);
	 }
	 printf("revert to %d id_commit successful\n",id);
	
}

int run_tag(char name[],char message[],int id,int check){
if(check){
FILE *tag;
tag=fopen("/mnt/c/project/.neogit/tag.txt","a+");
char line[MAX_ARRAY];
while(fgets(line,MAX_ARRAY,tag)!=NULL){
	if(line[strlen(line)-1]=='\n')line[strlen(line)-1]='\0';
	if(strcmp(line,name)==0){
		printf("tag eith ths name alredy exusts\n");
		fclose(tag);
		return 0;
	}
}
fprintf(tag,"%s\n",name);
fclose(tag);}
FILE *fp;
char path_tag_file[MAX_ARRAY]="/mnt/c/project/.neogit/tag/";
strcat(path_tag_file,name);
strcat(path_tag_file,".txt");
fp=fopen(path_tag_file,"w");
fprintf(fp,"name_tag:%s\n",name);
fprintf(fp,"id_commit_head:%d\n",id);
fprintf(fp,"message:%s\n",message);
time_t t;
time(&t);
fprintf(fp,"time:%s",ctime(&t));
fprintf(fp,"user:%s\n",user_name_commit());
fclose(fp);
printf("%s_tag maked successfuly\n",name);

}

int tag_show(char name_tag[]){
FILE *file;
char path_file[MAX_ARRAY]="/mnt/c/project/.neogit/tag/";
strcat(path_file,name_tag);
strcat(path_file,".txt");
file=fopen(path_file,"r");
char line[MAX_ARRAY];
for (int i=0;i<5;i++){
	fgets(line,MAX_ARRAY,file);
	printf("%s",line);
}
fclose(file);
return 0;
}
int tag_sort(){
	FILE *file;
	file=fopen("/mnt/c/project/.neogit/tag.txt","r");
	if(file==NULL){
		printf("you don not have tag\n");
		perror("error in opening the tag.txt file");
		return 1;
	}
	char line[MAX_ARRAY];
	if(fgets(line,MAX_ARRAY,file)==NULL){
		printf("you don not have tag\n");
		return 0;
	}
	fclose(file);
	file=fopen("/mnt/c/project/.neogit/tag.txt","r");
	char names[100][100]; 
    int count = 0;
	while(fgets(names[count],MAX_ARRAY,file)!=NULL){
    names[count][strlen(names[count]) - 1] = '\0'; // Remove trailing newline
    count++;
    }
    fclose(file);

	////do sort
	char temp[MAX_ARRAY];
	for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
	printf("tags:\n");
	for (int i = 0; i < count; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
	
}


 int isOnlyWhitespace(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0; // Found a non-whitespace character
        }
        str++;
    }
    return 1; // No non-whitespace characters found
}
int run_diff_whithout_line(char filename_1[],char filename_2[],char filepath_1[],char filepath_2[]){
	FILE *fp_1,*tmpfp_1;
	fp_1=fopen(filepath_1,"r");
	tmpfp_1=fopen("/mnt/c/project/.neogit/tmpfile_1.txt","w");
	char line_1[MAX_ARRAY];
	while(fgets(line_1,MAX_ARRAY,fp_1)!=NULL){
		if(!isOnlyWhitespace(line_1)){
			fputs(line_1,tmpfp_1);
		}
	}
	FILE *fp_2,*tmpfp_2;
	fp_2=fopen(filepath_2,"r");
	tmpfp_2=fopen("/mnt/c/project/.neogit/tmpfile_2.txt","w");
	char line_2[MAX_ARRAY];
	while(fgets(line_2,MAX_ARRAY,fp_2)!=NULL){
		if(!isOnlyWhitespace(line_2)){
			fputs(line_2,tmpfp_2);
		}
	}
	fclose(fp_1);
	fclose(fp_2);
	fclose(tmpfp_1);
	fclose(tmpfp_2);

	  int lineNumber = 1;
	  tmpfp_1=fopen("/mnt/c/project/.neogit/tmpfile_1.txt","r");
	  tmpfp_2=fopen("/mnt/c/project/.neogit/tmpfile_2.txt","r");
    
    while (fgets(line_1, sizeof(line_1), tmpfp_1) && fgets(line_2, sizeof(line_2), tmpfp_2)) {
        // Remove newline characters
        
        
        if (strcmp(line_1, line_2) != 0) {
            printf("«««««\n");
            printf("%s-%d\n", filename_1,lineNumber);
			printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET "\n", line_1);
            printf("%s-%d\n", filename_2,lineNumber);
			printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n", line_2);
			printf("»»»»»\n");
        }
        
        lineNumber++;
    }
    
    fclose(tmpfp_1);
    fclose(tmpfp_2);
	remove("/mnt/c/project/.neogit/tmpfile_1.txt");
	remove("/mnt/c/project/.neogit/tmpfile_2.txt");
	return 0;
    
}

int run_diff_line(char filename_1[],char filename_2[],int start_1,int end_1,int start_2,int end_2){
	char filepath_1[MAX_ARRAY];
	strcpy(filepath_1,realpath(filename_1,NULL));
	FILE *fp_1,*tmpfp_1;
	fp_1=fopen(filepath_1,"r");
	tmpfp_1=fopen("/mnt/c/project/.neogit/tmpfile_1.txt","w");
	char line_1[MAX_ARRAY];
	int line_start_1=1;
	while (line_start_1 < start_1 && fgets(line_1, sizeof(line_1), fp_1) ){
        while(isOnlyWhitespace(line_1))fgets(line_1,sizeof(line_1),fp_1);
		line_start_1++;
	}
	for(int i=line_start_1;i<=end_1;i++){
             if(fgets(line_1,sizeof(line_1),fp_1)!=NULL){
				while(isOnlyWhitespace(line_1))fgets(line_1,sizeof(line_1),fp_1);
			 }
			 fputs(line_1,tmpfp_1);
	}
	fclose(fp_1);
	fclose(tmpfp_1);
	//file_2
	char filepath_2[MAX_ARRAY];
	strcpy(filepath_2,realpath(filename_2,NULL));
	FILE *fp_2,*tmpfp_2;
	fp_2=fopen(filepath_2,"r");
	tmpfp_2=fopen("/mnt/c/project/.neogit/tmpfile_2.txt","w");
	char line_2[MAX_ARRAY];
	int line_start_2=1;
	while (line_start_2 < start_2 && fgets(line_2, sizeof(line_2), fp_2)){
		while(isOnlyWhitespace(line_2))fgets(line_2,sizeof(line_2),fp_2);
		line_start_2++;
	};
	for(int i=line_start_2;i<=end_2;i++){
             if(fgets(line_2,sizeof(line_2),fp_2)!=NULL){
				while(isOnlyWhitespace(line_2))fgets(line_2,sizeof(line_2),fp_2);
			 }
			 fputs(line_2,tmpfp_2);
	}
    fclose(fp_2);
	fclose(tmpfp_2);
/////////
	int lineNumber_1=start_1;
	int lineNumber_2=start_2;
	tmpfp_1=fopen("/mnt/c/project/.neogit/tmpfile_1.txt","r");
    tmpfp_2=fopen("/mnt/c/project/.neogit/tmpfile_2.txt","r");
    while(lineNumber_1<=end_1 && lineNumber_2<=end_2){
		fgets(line_1,sizeof(line_1),tmpfp_1);
		fgets(line_2,sizeof(line_2),tmpfp_2);
		if(strcmp(line_1,line_2)!=0){
			printf("«««««\n");
            printf("%s-%d\n", filename_1,lineNumber_1);
			printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET "\n", line_1);
            printf("%s-%d\n", filename_2,lineNumber_2);
			printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n", line_2);
			printf("»»»»»\n");
		}
		lineNumber_1++;
		lineNumber_2++;
	}
	remove("/mnt/c/project/.neogit/tmpfile_1.txt");
	remove("/mnt/c/project/.neogit/tmpfile_2.txt");
	return 0;
}

int run_diff_c(char id_1[],char id_2[]){
	////commit 1
	char path_file_1[MAX_ARRAY]="/mnt/c/project/.neogit/all_commits/";
	strcat(path_file_1,id_1);
	strcat(path_file_1,".txt");
	FILE *file_1;
	file_1=fopen(path_file_1,"r");
	char line_1[MAX_ARRAY];
	char branch_1[MAX_ARRAY];
	while(fgets(line_1,MAX_ARRAY,file_1)!=NULL){
		if(strstr(line_1,"branch")!=NULL){
			sscanf(line_1,"branch:%s\n",branch_1);
			break;
		}
	}
	char path_commit_1[MAX_ARRAY]="/mnt/c/project/.neogit/";
	strcat(path_commit_1,branch_1);
	strcat(path_commit_1,"/all_commits_files/");
	strcat(path_commit_1,id_1);
	        char namefile_1[100][100];
	         DIR * dir_1;
			struct dirent * entry_1;
			dir_1=opendir(path_commit_1);
			int index_1=0;
			while((entry_1=readdir(dir_1))!=NULL){
			   if(strcmp(entry_1->d_name,".")!=0 && strcmp(entry_1->d_name,"..")!=0 ){
               strcpy(namefile_1[index_1],entry_1->d_name);
			   index_1++;}
			}


    ////commit 2
	char path_file_2[MAX_ARRAY]="/mnt/c/project/.neogit/all_commits/";
	strcat(path_file_2,id_2);
	strcat(path_file_2,".txt");
	FILE *file_2;
	file_2=fopen(path_file_2,"r");
	char line_2[MAX_ARRAY];
	char branch_2[MAX_ARRAY];
	while(fgets(line_2,MAX_ARRAY,file_2)!=NULL){
		if(strstr(line_2,"branch")!=NULL){
			sscanf(line_2,"branch:%s\n",branch_2);
			break;
		}
	}
	char path_commit_2[MAX_ARRAY]="/mnt/c/project/.neogit/";
	strcat(path_commit_2,branch_2);
	strcat(path_commit_2,"/all_commits_files/");
	strcat(path_commit_2,id_2);
	       char namefile_2[100][100];
	         DIR * dir_2;
			struct dirent * entry_2;
			dir_2=opendir(path_commit_2);
			int index_2=0;
			while((entry_2=readdir(dir_2))!=NULL){
			   if(strcmp(entry_2->d_name,".")!=0 && strcmp(entry_2->d_name,"..")!=0 ){
               strcpy(namefile_2[index_2],entry_2->d_name);
			   index_2++;}
			}
	    
			
	 
	 ////
	 printf("files that is not exist in commit_id:%s:\n",id_2);
     for(int i=0;i<index_1;i++){
		int found=0;
		for(int j=0;j<index_2;j++){
		if(strcmp(namefile_1[i],namefile_2[j])==0)found=1;
		}
		if(!found)printf("%s\n",namefile_1[i]);
	 }


	 printf("files that is not exist in commit_id:%s:\n",id_1);
      for(int i=0;i<index_2;i++){
		int found=0;
		for(int j=0;j<index_2;j++){
		if(strcmp(namefile_2[i],namefile_1[j])==0)found=1;
		}
		if(!found)printf("%s\n",namefile_2[i]);
	 }

	  for(int i=0;i<index_1;i++){
		for(int j=0;j<index_2;j++){
		if(strcmp(namefile_1[i],namefile_2[j])==0){
           char path_each_file1[MAX_ARRAY];
		   strcpy(path_each_file1,path_commit_1);
		   strcat(path_each_file1,"/");
		   strcat(path_each_file1,namefile_1[i]);
		   char path_each_file2[MAX_ARRAY];
		   strcpy(path_each_file2,path_commit_2);
		   strcat(path_each_file2,"/");
		   strcat(path_each_file2,namefile_1[i]);
		   run_diff_whithout_line(namefile_1[i],namefile_2[j],path_each_file1,path_each_file2);

		}
		
	 }

}}

int run_merge(char branch_1[],char branch_2[]){\
/////branch_1
char path_head_1[MAX_ARRAY];
strcpy(path_head_1,"/mnt/c/project/.neogit/");
strcat(path_head_1,branch_1);
strcat(path_head_1,"/last_commit_files");
            char namefile_1[100][100];
	         DIR * dir_head_1;
			struct dirent * entry_1;
			dir_head_1=opendir(path_head_1);
			int index_1=0;
			while((entry_1=readdir(dir_head_1))!=NULL){
			   if(strcmp(entry_1->d_name,".")!=0 && strcmp(entry_1->d_name,"..")!=0 ){
               strcpy(namefile_1[index_1],entry_1->d_name);
			   index_1++;}
			}
///branch 2

char path_head_2[MAX_ARRAY];
strcpy(path_head_2,"/mnt/c/project/.neogit/");
strcat(path_head_2,branch_2);
strcat(path_head_2,"/last_commit_files");
            char namefile_2[100][100];
	         DIR * dir_head_2;
			struct dirent * entry_2;
			dir_head_2=opendir(path_head_2);
			int index_2=0;
			while((entry_2=readdir(dir_head_2))!=NULL){
			   if(strcmp(entry_2->d_name,".")!=0 && strcmp(entry_2->d_name,"..")!=0 ){
               strcpy(namefile_2[index_2],entry_2->d_name);
			   index_2++;}
			}
			//////make branch
			char branch_new[MAX_ARRAY];
			strcpy(branch_new,branch_1);
			strcat(branch_new,branch_2);
			make_branch(branch_new);


			////// branch1
			for(int i=0;i<index_1;i++){
				int equal=0;
				for(int j=0;j<index_2;j++){
					if(strcmp(namefile_1[i],namefile_2[j])==0)equal=1;
				}
				if(!equal){
					char path_read[MAX_ARRAY]="/mnt/c/project/.neogit/";
                     strcat(path_read,branch_1);
					 strcat(path_read,"/last_commit_files/");
					 strcat(path_read,namefile_1[i]);
					char path_write[MAX_ARRAY]="/mnt/c/project/.neogit/";
					strcat(path_write,branch_new);
					strcat(path_write,"/last_commit_files/");
					strcat(path_write,namefile_1[i]);
					copy_file(path_read,path_write);

				}
			}

          ///branch2
			for(int i=0;i<index_2;i++){
				int equal=0;
				for(int j=0;j<index_1;j++){
					if(strcmp(namefile_2[i],namefile_1[j])==0)equal=1;
				}
				if(!equal){
					char path_read[MAX_ARRAY]="/mnt/c/project/.neogit/";
                     strcat(path_read,branch_2);
					 strcat(path_read,"/last_commit_files/");
					 strcat(path_read,namefile_2[i]);
					char path_write[MAX_ARRAY]="/mnt/c/project/.neogit/";
					strcat(path_write,branch_new);
					strcat(path_write,"/last_commit_files/");
					strcat(path_write,namefile_2[i]);
					copy_file(path_read,path_write);

				}
			}

			///// diff
			for (int i=0;i<index_1;i++){
			    for(int j=0;j<index_2;j++){
                   if(strcmp(namefile_1[i],namefile_2[j])==0){
                     char path_1[MAX_ARRAY]="/mnt/c/project/.neogit/";
					 strcat(path_1,branch_1);
					 strcat(path_1,"/last_commit_files/");
					 strcat(path_1,namefile_1[i]);
					 char path_2[MAX_ARRAY]="/mnt/c/project/.neogit/";
					 strcat(path_2,branch_2);
					 strcat(path_2,"/last_commit_files/");
					 strcat(path_2,namefile_2[j]);
					run_diff_whithout_line(namefile_1[i],namefile_2[j],path_1,path_2);
					break;
				   }

				}
			}


}