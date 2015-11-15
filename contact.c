#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct contact {
	long ph;
	char name[20],add[20],email[30];
} list;

char query[20],name[20];
FILE *fp, *ft;
int i,n,ch,l,found;

//edit login function.....

int login(void) {

	int buf = 0;
	char pass[16];
	char password[16]="coep";

	printf("\n\t **** Welcome to Contact Management System ****");
	printf("\n\t\tEnter Password:");
    	scanf("%[^\n]", pass);

	if(strcmp(pass, password) == 0) 
		buf = 1;
	
    	else 
    		printf("\n\nWrong Password!!\a\a\a");
    	
    	return buf;
    }
    

int main() {
	int buf = login();
	if (buf == 0) 
		exit(0);
	else {

main:
	
	printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t");
	printf("[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t");
	printf("Enter the choice:");
	scanf("%d",&ch);
	switch(ch) {
		case 0:

			break;

        /* *********************Add new contacts************  */
		case 1:

        		
			fp=fopen("contact.dat","a+");
			
            			
				printf("To exit enter blank space in the name input\nName (Use identical):");
				scanf("%s",list.name);
				if(list.name[0] > 122 || list.name[0] < 65)
				break;
				
				printf("Phone:");
				scanf("%ld",&list.ph);
            			
           			printf("address:");
            			scanf("%s",list.add);
			       
			   	printf("email address:");
				scanf("%s",list.email);	
				printf("\n");
				
			fwrite(&list,sizeof(list),1,fp);
			fclose(fp);
			break;

        /* *********************list of contacts*************************  */

    case 2:
		printf("\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n");
		printf("\n=================================================================\n");

		for(i=97; i<=122; i++) {
			fp=fopen("contact.dat","r");
			found=0;

			while(fread(&list,sizeof(list),1,fp)==1) {

				if(list.name[0]==i || list.name[0]==i-32) {
					printf("\nName\t: %s\nPhone\t: %ld\n",list.name,list.ph);
					printf("Address\t: %s\nEmail\t: %s\n",list.add,list.email);
					found++;
				}
			}
			if(found!=0) {
                		printf("=========================================================== [%c]-(%d)\n\n",i-32,found);
            		}
			fclose(fp);
		}
		break;

        /* *******************search contacts**********************  */

    case 3:
    	 do {
		found=0;

		printf("\n\n\t:CONTACT SEARCH\n\t===========================\n\t:Name of contact to search: ");
		scanf("%s",query);
		l=strlen(query);

		fp=fopen("contact.dat","r");
		printf("\n\n:Search result for '%s' \n===================================================\n",query);

		while(fread(&list,sizeof(list),1,fp)==1) {
		for(i=0; i<=l; i++)
			name[i]=list.name[i];
			name[l]='\0';

			if(strcmp(name,query)==0) {
				printf("\nName\t: %s\nPhone\t: %ld\n",list.name,list.ph);
				printf("Address\t: %s\nEmail\t: %s\n",list.add,list.email);
				found++;

				if (found%4==0) {
					printf(":Press any key to continue...");
				}
			}
		}
		if(found==0)
			printf("\n:No match found!");
		else
			printf("\n:%d match(s) found!",found);
			printf("\n===================================================\n");
		fclose(fp);

		printf("\n :Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
		scanf("%d",&ch);
	}while(ch==1);

        break;

        /* *********************edit contacts************************/

    case 4:
		fp=fopen("contact.dat","r");
		ft=fopen("temp.dat","w");
		printf(":Edit contact\n===============================\n\n\t:Enter the name of contact to edit:");
		scanf("%s",name);

		while(fread(&list,sizeof(list),1,fp)==1) {
			if(strcmp(name,list.name)!=0)
				fwrite(&list,sizeof(list),1,ft);
		}
		printf("\n\n:Editing '%s'\n\n",name);

		printf(":Name(Use identical):");

		scanf("%s",list.name);
		printf(":Phone:");

		scanf("%ld",&list.ph);
		printf(":address:");

		scanf("%s",list.add);
		printf(":email address:");

		scanf("%s",list.email);
		printf("\n");

		fwrite(&list,sizeof(list),1,ft);
		fclose(fp);
		fclose(ft);

		remove("contact.dat");

		rename("temp.dat","contact.dat");
		break;

        /* ********************delete contacts**********************/

    case 5:
    	
    		printf("\n\n\t:DELETE A CONTACT\n\t==========================\n\t:Enter the name of contact to delete:");

        scanf("%s",name);

        fp=fopen("contact.dat","r");

        ft=fopen("temp.dat","w");

        while(fread(&list,sizeof(list),1,fp)!=0) {
		if (strcmp(name,list.name)!=0) {
			fwrite(&list,sizeof(list),1,ft);
                }
        }
        fclose(fp);
	fclose(ft);

	remove("contact.dat");

	rename("temp.dat","contact.dat");

	break;

    default:

        printf("Invalid choice");
        break;
}
	printf("\n\n\n:Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n");
	scanf("%d",&ch);
	switch (ch) {
		case 1:
			goto main;

		case 0:
			break;

		default:
			printf("Invalid choice");
			break;
	}
	return 0;

}

}
