#include "file_functions.h"
///mohamamdrezamonemian
///402106604
int main(int argc, char *argv[])
{ 
	if (argc <2){
		fprintf(stdout, "please enter a valid command\n");
        return 1;
	} 
	  if (strcmp(argv[1], "init") == 0) {
        return init(argc, argv);}
	  if(check_neogit()){
	  if (search_for_alias(argv[1])!=NULL){
		  char * command=argv[1];
          char *token=strtok(search_for_alias(command)," ");
		  int index=0;
		  while(token!=NULL){
			if (*(token+strlen(token)-1)=='\n')  *(token+strlen(token)-1)='\0';
             argv[index]=token;
			 index++;
			 token=strtok(NULL," ");
		  }
		  argc=index+1;

	}
	// //git init
	  if (strcmp(argv[1], "init") == 0) {
        return init(argc, argv);}
	  if (strcmp(argv[1],"config")==0){
	// 	// git config alias
		if (strstr(argv[2],"alias")!=NULL || strstr(argv[3],"alias")!=NULL){
              if (strstr(argv[2],"alias")!=NULL){
               char *token=strtok(argv[2],".");
				token=strtok(NULL,"\0");
				char with_neo[MAX_ARRAY]="neogit ";
				strcat(with_neo,token);
				strcat(with_neo," ");
				strcat(with_neo,argv[3]);
				strcat(with_neo,"\n");
				make_alias(with_neo);
			  }
			  else{
                char *token=strtok(argv[3],".");
				token=strtok(NULL,"\0");
				char with_neo[MAX_ARRAY]="neogit ";
				strcat(with_neo,token);
			    strcat(with_neo," ");
				strcat(with_neo,argv[4]);
				strcat(with_neo,"\n");
				make_alias(with_neo);
			  }}
		
	// 	// git config user
		else{
		if (strcmp(argv[2],"-global")==0){
             if (strcmp(argv[3],"user.name")==0) config_global_user(argv[4]);
			 if (strcmp(argv[3],"user.email")==0) config_global_email(argv[4]);
		}
		else {
             if (strcmp(argv[2],"user.name")==0) config_user(argv[3]);
			 if (strcmp(argv[2],"user.email")==0) config_email(argv[3]);
			 if (strcmp(argv[2],"user.name")!=0 && strcmp(argv[2],"user.email")!=0){
                     printf("enter the vaild command!!\n");
			 }
		}

		}}

		///negit add , .......
		  if (strcmp(argv[1],"add")==0){
			if (argc<3){
				perror("PLEASE ENTER A VALID COMMAND\n");
				return 1;
			}
			else if (strcmp(argv[2],"-f")==0){
                  for(int i=3;i<argc;i++){
					srearch_for_add(argv[i]);
				  }
			}
			else if (strstr(argv[2],"-n")!=NULL){
                  get_file_for_check_staging();
			}
			else{
                for (int i=2;i<argc;i++){
					srearch_for_add(argv[i]);
				}
			}
		}

		///neogit reset
		
		if (strcmp(argv[1],"reset") == 0){
			if (argc<3){
				perror("please enter the valid command!!!");
				return 1;
			}
			search_for_reset(argv[2]);
		}
		
		//neogit status
		if(strcmp(argv[1],"status") == 0){
			if (argc>2){
				perror("please enter the valid command!!!");
				return 1;
			}
			run_status();
		}

		//the massage of commit 
		if (strcmp(argv[1],"set")==0 || strcmp(argv[1],"replace")==0 || strcmp(argv[1],"remove")==0){
               if (strcmp(argv[1],"set")==0){
				if (argc!=6){
					perror("enter the valid command!!");
					return 1;
				}
				set_massage(argv[3],argv[5]);
			   }
			   else if (strcmp(argv[1],"replace")==0 ){
				if (argc!=6){
					perror("enter the valid command!!");
					return 1;
				}
				replace_massage(argv[3],argv[5]);
			   }
			   else {
				if (argc!=4){
					perror("enter the valid command!!");
					return 1;
				}
				remove_massage(argv[3]);
			   }
		}

		//neogit commit 
		if (strcmp(argv[1],"commit")==0){
           if (argc<4){
			printf("please enter the appropriate message\n");
			return 1;
		   }
		   else {
			if (strcmp(argv[2],"-s")==0)find_message(argv[3]);
			else {
				if (strlen(argv[3])>72){
					printf("yuor message is very long\n");
					return 1;
				}
				run_commit(argv[3]);
		   }
		}
		
}
        ////neogit log , moshtaghatt
       if (strcmp(argv[1],"log")==0){
		if (argc==2){
			run_log();
			return 0;
		} 
		  else if (strcmp(argv[2],"-n")==0){
			    int num;
				sscanf(argv[3],"%d",&num);
                run_log_n(num);
				return 0;
		  }
		  else if (strcmp(argv[2],"-branch")==0){
			run_log_branch(argv[3]);
			return 0;
		  }
		  else if (strcmp(argv[2],"-author")==0){
			run_log_name(argv[3]);
			return 0;
		  }
		  else if (strcmp(argv[2],"-search")==0){
               run_log_message(argv[3]);
			   return 0;
		  }
		   else if (strcmp(argv[2],"-befor")==0){
               run_log_time(argv[3],0);
			   return 0;
		  }
		  else if (strcmp(argv[2],"-since")==0){
			     run_log_time(argv[3],1);
			      return 0;
		  }
          else {
			printf("enter the valid command\n");
			return 0;
		  }
		  
	   }
	   ////neogit branch
	   if(strcmp(argv[1],"branch")==0){
		if (argc==2){
            show_branch();
		}
		else if(argc==3){
			make_branch(argv[2]);
			return 0;
		}
		else{
			printf("please enter the valid command\n");
			return 0;
		}
	   }
	   /////neogit checkout
	   if (strcmp(argv[1],"checkout")==0){
		 if(strcmp(argv[2],"-branch")==0){
             checkout_branch(argv[3]);
		 }
		 else if(strcmp(argv[2],"-id")==0){
			int id;
			sscanf(argv[3],"%d",&id);
			checkout_id(id);
		 }
		 else if(strcmp(argv[2],"HEAD")==0){
			checkout_head();
		 }
		 else{
			printf("please enter the valid command\n");
		 }
	   }
       
	   ////revert 
	   if(strcmp(argv[1],"revert")==0){
		if(strcmp(argv[2],"-m")==0){
			int id;
			sscanf(argv[4],"%d",&id);
             run_revert(argv[3],id,1);
		}
		else if(strcmp(argv[2],"-n")==0){
			   int id;
			  sscanf(argv[3],"%d",&id);
               run_revert("no message",id,0);
		}
		else if(strstr(argv[2],"HEAD-")!=NULL){
			 int x;
			sscanf(argv[2],"HEAD-%d",&x);
			 int id=id_commit_without_ezafe(user_name_commit())-x+1;
			 if(argc==5){
                 run_revert(argv[4],id,1);
			 }
			 else run_revert(message_revert(id),id,1);
		}
		else{
			 int id;
			 sscanf(argv[2],"%d",&id);
             run_revert(message_revert(id),id,1);
		}
	   }
	   ///
	   ///tag , moshtaghat
       if(strcmp(argv[1],"tag")==0){
       if(argc==2){
               tag_sort();
	   }
       else if(strcmp(argv[2],"show")==0){
		      tag_show(argv[3]);
	  }
       else{
		 char tag_name[MAX_ARRAY];
		 int id;
		 char message[MAX_ARRAY]=" ";
		 int check=1;
		 strcpy(tag_name,argv[3]);
		 id=id_currnent(user_name_commit());
		 if(argc>4)
		 {
		if(strcmp(argv[4],"-m")==0)strcpy(message,argv[5]);
        if(strcmp(argv[4],"-c")==0)scanf(argv[5],"%d",&id);
		 }
		 if(argc>6){
		 if(strcmp(argv[6],"-c")==0){
			sscanf(argv[7],"%d",&id);
		 }
		 }
		 if(strcmp(argv[argc-1],"-f")==0){
               check=0;
		 }
		 run_tag(tag_name,message,id,check);}
		 
	   }
	 
       /////diffi 
	   if(strcmp(argv[1],"diff")==0){
		if(argc==5){
			if(strcmp(argv[2],"-f")==0){
                 run_diff_whithout_line(argv[3],argv[4],realpath(argv[3],NULL),realpath(argv[4],NULL));
			}
			else if(strcmp(argv[2],"-c")==0){
                  run_diff_c(argv[3],argv[4]);
			}
			else printf("please enter the valid command\n");

		}
		else if(argc==9){
			int start_1,start_2,end_1,end_2;
			sscanf(argv[6],"%d-%d",&start_1,&end_1);
            sscanf(argv[8],"%d-%d",&start_2,&end_2);
			printf("%d",end_2);
			run_diff_line(argv[3],argv[4],start_1,end_1,start_2,end_2);

		}
		else printf("please enter the valid command\n");
	   }
	   
	   ///// merge
	   if(strcmp(argv[1],"merge")==0){
		if(argc==5){
               run_merge(argv[3],argv[4]);
		}
		else printf("please enter the valid command\n");
	   }






}
}
