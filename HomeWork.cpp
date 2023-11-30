//Eyüphan Kaygusuz
//B2210.033030

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MIN_LOWER 1
#define MIN_UPPER 1
#define MIN_NUMBER 1
#define MIN_SPECIAL 1

#define TEMP_MAX 32
#define PASS_MIN 10
#define PASS_MAX 30
#define USER_MIN 5
#define USER_MAX 20
#define MAIL_MIN 5
#define MAIL_MAX 40

using namespace std;


void Welcome();
void PrintChooseMenu();
void WelcomScreen();
bool GetInput(int min,int max);
void MainMenuRouter(int route);
void Login();
void GetString(char *tempText);
void CheckMail(char* tempText);
bool isTempName(char* tempText);
void CheckLength(char* tempText, int max, int min, bool isName,bool isPass);
void Register();
void CheckUsername(char* tempText);
void GetUsers();
void ListUsers();
void PrintBack();
bool CheckExit(char* input);
void CheckCredentials(char* nameMail, char* password, bool isName);
bool CheckPass(char* tempText);
void EncrypPass(char* newPass);
void isUsernameTaken(char* name);
void isMailTaken(char* mail);
void SaveUsers();

int input = 0;
bool correctInput;
char username[USER_MAX];
char mail[MAIL_MAX];
char password[PASS_MAX];
char auth[2];
int attempts;
bool logged;
int lower = 0,upper = 0,number = 0,special = 0;



typedef struct node{
	char name[USER_MAX];
	char mail[MAIL_MAX];
	char pass[PASS_MAX];
	char auth[2];
	int attempts;
	struct node *next;
} node;


node *userHead = NULL;

void AddNewUser(char *name, char *mail, char *pass, char* auth, int attempts){
	node *temp =  (node*)malloc(sizeof(node));
	strcpy(temp->name,name);
	strcpy(temp->mail,mail);
	strcpy(temp->pass,pass);
	strcpy(temp->auth,auth);
	temp->attempts = attempts;
	temp->next = userHead;
	userHead = temp;
}

int main() {
	while(true){
		if(!logged){
			printf("Loading Users...");
        	GetUsers();
            system("cls");
            WelcomScreen();
            correctInput = false;
		}
		else{
			correctInput = false;
			printf("Account Type: ");
			if(!strcmp(auth,"a"))
                printf("ADMIN\n");
            else if (!strcmp(auth,"u"))
                printf("USER\n");
            else
                printf("GUEST\n");
            
			printf("Welcome to your account, %s! What would you like to do?\n",username);
            printf("\n1-)Log out");
            while(!correctInput){
            	correctInput = GetInput(1,1);
			}
			strcpy(username,"");
			strcpy(mail,"");
			strcpy(password,"");
			strcpy(auth,"");
            attempts = 0; 
            logged = false;
            correctInput = false;
		}
		
	}
	return 0;
    
}
void WelcomScreen(){
	
    while(!correctInput){
        PrintChooseMenu();
        while(!correctInput){
            correctInput = GetInput(1,3);
        }
        correctInput = false;
        MainMenuRouter(input);


       
    }
    correctInput = false;
}
void PrintChooseMenu(){    
printf("Welcome to the system! What would you like to do?\n");
    printf("1-) Login\n");
    printf("2-) Register\n");
    printf("3-) Exit application");
}

void Login(){
	bool isName = true;
	// USERNAME - EMAIL
    char tempText[TEMP_MAX];
	while(!correctInput){
    	system("cls");
    	PrintBack();
    	printf("Please Enter Your Username Or E-mail\n");
        printf("Username/E-mail: ");
		GetString(tempText); //Get the username/mail
		if(CheckExit(tempText))
			return;
		isName = isTempName(tempText);// check if it is name or mail		
			
		if(isName)
		{
	        CheckLength(tempText,USER_MAX,USER_MIN,true,false); // returns correctInput true or false
	        if(correctInput) //dont bother to check if it is false
	            CheckUsername(tempText);
		}
	    else
	    {
	    	CheckLength(tempText, MAIL_MAX,MAIL_MIN,false,false); // returns correctInput true or false
	    	if(correctInput) //dont bother to check if it is false
				CheckMail(tempText);
		}
	    strcpy(username,tempText);
    }
    correctInput = false;
    //-------------------------
    //PASSWORD
    while(!correctInput){
    	system("cls");
    	char tempText[TEMP_MAX];
    	PrintBack();
    	printf("Please Enter Your Password For Your %s Account\n",username);
        printf("Password: ");
        GetString(tempText);
        if(CheckExit(tempText))
            return;
        CheckLength(tempText,PASS_MAX,PASS_MIN,false,true);
        strcpy(password,tempText);
	}
        CheckCredentials(username,password,isName);
        SaveUsers();
        printf("Logged in Successfully!");
	    getch();
        system("cls");

        
}
//Check x for Exit
void PrintBack(){
	printf("(Press X to go to the main menu.)\n");
}
bool CheckExit(char* input){
	if(!strcmp(input,"x") || !strcmp(input,"X")){
		system("cls");
		return true;
	}
	return false;
}
//Get String From User as 32 chars for tempText variable
void GetString(char *tempText){
	scanf("%32s",tempText);
}
//Check if it is mail or name in login page
bool isTempName(char* tempText){
	int length = strlen(tempText);
	char* str = (char*)malloc(length + 1);
	strcpy(str,tempText);
	
	for(int i = 0; i < length; i++,str++){
		if(*str == '@'){
			return false;
		}
	}
	return true;
}

void CheckMail(char* tempText){
	
	int txtlngth = strlen(tempText);
	char* str = (char*)malloc(txtlngth + 1);
	strcpy(str,tempText);
	
	correctInput = true;
	bool mailch = false; // to check '@' character to check dot.
	bool dot = false; // to check if there is a ' . ' (dot) after ' @ '
	int quotes = 0;
	
    if((!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a' && str[0] <= 'z') && !(str[0] >= '0' && str[0] <= '9')))
	{
		printf("Your E-mail adress can't start with special characters!\n");
		correctInput = false;
		getch();
		return;
	}	
	for(int i = 0; i < txtlngth; i++,str++){
	    	
	    if((!(*str >= 'A' && *str <= 'Z') && !(*str >= 'a' && *str <= 'z') && !(*str >= '0' && *str <= '9')) && *str != '@' && *str != '.' && *str != '_' && *str != '-'){
		    correctInput = false;
	    	printf("You can only use following characters in your E-mail = [A-Z], [a,z], [0-9], [- _ . @]\n");
	    	getch();
			return;	
	    }		
		if(*str == '@'){
			if(mailch){	    
				correctInput = false;
	    		printf("You can't use '@' charanter more than one!\n");
	    		getch();
				return;
			}
			mailch = true;
		}
        if(mailch && *str == '.'){
            dot = true;
            if(txtlngth - i - 1 <= 0){	
	            printf("Please enter a valid E-Mail adress! For example: examplemail@hotmail.com\n");
				correctInput = false;
				getch();
			}
		}
	}
	if(!mailch){
	    correctInput = false;
	    printf("Please enter a valid E-Mail adress! For example: examplemail@hotmail.com\n");
	   	getch();
	   	return;
		
	}
	if(mailch && !dot){
	   	correctInput = false;
	    printf("Please enter a valid E-Mail adress! For example: examplemail@hotmail.com\n");
	   	getch();
	   	return;
	}	   	
	return;
	
}

void CheckCredentials(char* nameMail, char* password, bool isName){
	node* temp = userHead;
    logged = false;
	correctInput = false;
	while(temp != NULL){
		if(isName){
			if(!strcmp(temp->name,nameMail)){
				if(temp->attempts == 3){
					printf("This Account has been locked!");
					return;
				}
				EncrypPass(password);			    
				if(!strcmp(temp->pass,password)){
					temp->attempts = 0;
					strcpy(auth,temp->auth);
					logged = true;
					printf("LOGGED IN WITH USERNAME!\n");
					correctInput = true;
    				return; // User matched!
				}
				else{
					temp->attempts += 1;
					SaveUsers();
					printf("WRONG CREDENTIALS!\n");
					return; //WRONG PASSWORD
				}
			}
			else{
				temp = temp->next;
				continue;
			}		
			    
		}
		else{
			if(!strcmp(temp->mail,nameMail)){
				if(temp->attempts == 3){
					printf("This Account has been locked!");
					return;
				}
				EncrypPass(password);
				
				if(!strcmp(temp->pass,password)){
					temp->attempts = 0;
				    strcpy(auth,temp->auth);
					logged = true;
					printf("LOGGED IN WITH E-MAIL!\n");
					correctInput = true;
					return; // User matched!
				}
				else{
					temp->attempts += 1;
					SaveUsers();
					printf("WRONG CREDENTIALS!\n");
					return; //WRONG PASSWORD
				}
			}
			else{
				temp = temp->next;
				continue;
			}
		}
		temp = temp->next;
		system("cls");
	}
	if(!correctInput){
        printf("WRONG CREDENTIALS!\n");
        printf("You're redirecting to the main menu!");
		getch();
	}
	system("cls");
	
}

char key[] = "qwerty";

void EncrypPass(char* newPass){
	int lngth = strlen(newPass);
	for(int i = 0; i < lngth;i++, newPass++){
		*newPass ^= key[i % strlen(key)]; 
		if(*newPass == 11 || *newPass == '\n' || *newPass == '\0')
	        *newPass += 65;
	}
	newPass -= lngth;
}


//Check if password is valid in registration page
bool CheckPass(char* tempText){
	int length = strlen(tempText);
    char* str = (char*)malloc(length + 1);
    strcpy(str,tempText);
    correctInput = true;
    upper = 0; lower = 0;
    special = 0; number = 0;
    for(int i = 0; i < length; i++,str++){
    	if(*str >= 'A' && *str < 'Z')
    		upper++;
		else if(*str >= 'a' && *str < 'z')
		    lower++;
		else if (*str >= '0' && *str < '9')
	        number++;
	    else
	        special++;
	}
	if(special < MIN_SPECIAL || upper < MIN_UPPER || lower < MIN_LOWER || number < MIN_NUMBER){
	    printf("Your password must contain minimum 1 Upper, 1 Lower, 1 Number and 1 Special characters at the same time!");
		correctInput = false;	
		getch();
	}
}

void Register(){
	char tempText[TEMP_MAX];
	while(!correctInput){
	
	    while(!correctInput){
		    system("cls");
		    PrintBack();
		    printf("Welcome to Registration Page!\n");
		    printf("Please Enter a username: ");
	        GetString(tempText);
		    if(CheckExit(tempText))
				    return;
		    CheckLength(tempText,USER_MAX,USER_MIN,true,false);
		    strcpy(username,tempText);
	    }
	    CheckUsername(tempText);
	    if(!correctInput) continue;
	    isUsernameTaken(tempText);
	}
	correctInput = false;
	while(!correctInput){
		while(!correctInput){
			system("cls");
		    PrintBack();
		    printf("Please enter a E-Mail for your %s account!\n",username);
		    printf("E-Mail: ");
	        GetString(tempText);
		    if(CheckExit(tempText))
				    return;
		    CheckLength(tempText,MAIL_MAX,MAIL_MIN,true,false);
		    strcpy(mail,tempText);
	    }	
	    CheckMail(tempText);
	    if(!correctInput) continue;
		isMailTaken(tempText);
	}	
	correctInput = false;
	while(!correctInput){
		while(!correctInput){
			system("cls");
		    PrintBack();
		    printf("Please enter a strong password for your %s account!\n",username);
		    printf("Password: ");
	        GetString(tempText);
		    if(CheckExit(tempText))
				    return;
		    CheckLength(tempText,PASS_MAX,PASS_MIN,false,true);
		    strcpy(password,tempText);
	    }	
	    CheckPass(tempText);
	}
	correctInput = false;
	EncrypPass(password);
	char tempAuth[] = "u";
	AddNewUser(username,mail,password,tempAuth,0);
	printf("Registered Successfully!");
	getch();
	SaveUsers();
	
}

void CheckUsername(char* tempText){
	int length = strlen(tempText);
	char* str = (char*)malloc(length + 1);
	strcpy(str,tempText);
	lower = upper = number = 0;
	correctInput = true;
	for(int i = 0; i < length; i++,str++){
		if(*str >= 'a' && *str <= 'z'){
			lower++;
		}
		else if(*str >= 'A' && *str <= 'Z'){
			upper++;
		}
		else if(*str >= '0' && *str <= '9'){
		    number++;	
		}
		else
		{
			printf("You can only use [A-Z],[a-z] and [0-9] characters in your username!");
		    correctInput = false;	
		    getch();
		    return;
		}
	}
	if(lower < MIN_LOWER || upper < MIN_UPPER || number < MIN_NUMBER){
			printf("Your username must contain minimum 1 lower, 1 upper and 1 number character!\n");
		    correctInput = false;	
		    getch();
		    return;
	}
}

void isUsernameTaken(char* name){
	
	node* temp = userHead;
	correctInput = true;
	while(temp != NULL){
		if(!strcmp(temp->name,name)){
			printf("This username is already taken!\n");
			correctInput = false;
			getch();
    		return; // User matched!
		}
		else{
			temp = temp->next;
			continue;
		}		   
	}
		system("cls");
}
void isMailTaken(char* mail){
	
	node* temp = userHead;
	correctInput = true;
	while(temp != NULL){
		if(!strcmp(temp->mail,mail)){
			printf("This mail is already taken!\n");
			correctInput = false;
			getch();
    		return; // User matched!
		}
		else{
			temp = temp->next;
			continue;
		}		   
	}
		system("cls");
}


//Get input from user for changing menus
bool GetInput(int min, int max) {
    char x = getch();
   
    if (((x >= ('0' + min)) && (x <= ('0' + max))) && min != max) {
        input = x - '0';
        system("cls");
        return true;
    }
    else if(min == max){
    	if(x == '1'){
    	    input = x - '0';
            system("cls");
            printf("DENEME");
            return true;
		}
		return false;
	}
    system("cls");
    PrintChooseMenu();
    printf("\nPlease enter a valid number: ");
    return false;
}
//Switch Menus from MainMenu
void MainMenuRouter(int route){
    switch(route){
        case 1:
            Login();
            break;
        case 2:
            Register();
            break;
        case 3:
        	exit(0);
		    break;
    }
}
//Get Users
void GetUsers(){
	FILE *file;	
	file = fopen("useraccounts.txt","r");
	if(file == NULL){
		printf("No such a file found!\n");
		return;
	}
	char name[USER_MAX], mail[MAIL_MAX], pass[PASS_MAX], auth[2];
	int attempts = 0;

	while(fscanf(file,"%s %s %s %s %d\n",name,mail,pass,auth,&attempts) != EOF){
			printf("User adding2...");
		AddNewUser(name,mail,pass,auth,attempts);
	}
	printf("Users Loaded");
	fclose(file);
}
void SaveUsers(){
	FILE *file;
	file = fopen("useraccounts.txt","w");
	node *temp = userHead;
	
	while(temp != NULL){
		fprintf(file,"%s %s %s %s %d\n",temp->name,temp->mail,temp->pass,temp->auth,temp->attempts);
		temp = temp->next;
	}
	fclose(file);
}

//List All Users In Text
void ListUsers(){
	node *temp = userHead;
	
	while(temp != NULL){
		printf("Username: %s\t E-Mail: %s\t Password: %s\n",temp->name,temp->mail,temp->pass);
		temp = temp->next;
	}
}
//Check the length of text.
void CheckLength(char* tempText, int max, int min, bool isName,bool isPass){
	
	int txtlngth = strlen(tempText);
	
	if(txtlngth > max){
		if(isName)
       	    printf("Username cannot be longer than %d characters! Please press any key to continue...1\n", max);
       	else if(!isName && !isPass)
       	    printf("E-mail cannot be longer than %d characters! Please press any key to continue...1\n",max);
		else if (!isName && isPass)
		    printf("Password cannot be longer than %d characters! Please press any key to continue...1\n",max);
		getch();	
		correctInput = false;
		return;
	}
	if(txtlngth < min){
		if(isName)
       	    printf("Username cannot be less than %d characters! Please press any key to continue...2\n", min);
       	else if(!isName && !isPass)
       	    printf("E-mail cannot be less than %d characters! Please press any key to continue...2\n",min);
		else
		    printf("Password cannot be less than %d characters! Please press any key to continue...2\n",min);
		_getch();	
		correctInput = false;
		return;
	}
	//tempText -= txtlngth;
	correctInput = true;
}	
