#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

/* global variable declaration */
int ch;
char choice='y';
int offsetposition;
char has_record = 'n';
char temp_request;
int flag;

#define password 1234

/* Structure declaration */
/* struct for students */
struct student
{
    char fname[10];
    char mname[10];
    char lname[10];
    char address[10];
    long int contact;
    char email[20];
    float gpa;
    char registration[20];
    char faculty[15];
    char semester[10];
};
struct student s;
struct student ts;

// file pointer declaration 
FILE *fp, *temp;

//function ti return to main menu
void return_to_menu()
{
	getchar();
	printf("\n Press ENTER to return on main menu ");
	ch = getchar();
	return;
}

/* COMMON MENU FUNCTION 
    FOR ADDING THE INFORMATION 
    FOR MODIFYING THE INFORMATION 
    FOR SEARCHING THE INFORMATION 
    FOR DELETING THE INFORMATION
*/

void c_menu()
{
    printf("****************************    [ 1 ]   >>  [  ADD INFORMATION      ]   ***************************\n");
    printf("****************************    [ 2 ]   >>  [  SEARCH INFORMATION   ]   ***************************\n");
    printf("****************************    [ 3 ]   >>  [  DISPLAY INFORMATION  ]   ***************************\n");
    printf("****************************    [ 4 ]   >>  [  DELETE INFORMATION   ]   ***************************\n");
    printf("****************************    [ 5 ]   >>  [  RETURN TO MAIN MWNU  ]   ***************************\n");
    printf("***************************************************************************************************\n");
    printf("***************************************************************************************************\n");
}

/* function for clearing the screen */
void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

/* function to exit from the program */
void exit_program()
{
    printf("\n Do you want to exit ? \n Press 1 to exit from the program. ( Press any number key to cancel.) \t");
    scanf("%d",&ch);
    if(ch==1)
    {
        clear_screen();
        printf("\n Thank you for Using the program");
    }
    else
    main_menu();

}



/* code for showing the top logo  menu */
void top_menu()
{
    // using graphics function to display on the top of the page 
    clear_screen();
    printf("***************************************************************************************************\n");
    printf("****************************   WELCOME TO SARASWATI MULTIPLE CAMPPUS   ****************************\n");
    printf("***************************************************************************************************\n");
    printf("****************************            CREATED BY SUNIL MAHATO         ***************************\n");
    printf("****************************         WEBSITE :  mahatosunil.com.np      ***************************\n");
    printf("****************************         EMAIL   :  sunilmaht642@gmail.com  ***************************\n");
    printf("***************************************************************************************************\n");
    printf("***************************************************************************************************\n");
}

/* function for the student management system 
    - adding the details 
    - modifying the details
    - deleting the details
    - searching the details 
*/
// function for adding the student records
void std_add()
{
    top_menu();
    fp = fopen("D:/FacultyMgmtSystem/student_database.bin","ab");

    printf("\n Enter the details of the students : ");
    // while(choice != 'n')
    // {
        /* taking the information of the students using the struct */
        printf("\n Enter first Name : \t"); 
        scanf("%s",s.fname);
        printf("Enter Middle Name :\t");
        scanf("%s",s.mname);
        printf("Enter Last Name : \t ");
        scanf("%s",s.lname);
        printf("Enter Address: \t ");
        scanf("%s",s.address);
        printf("Enter Contact Number : \t");
        scanf("%ld",&s.contact);
        printf("Enter Email Address : \t");
        scanf("%s",s.email);
        printf("Enter the GPA of +2  \t");
        scanf("%f",&s.gpa);

        // inserting the details of the studnets into file 
        fwrite(&s, sizeof(struct student),1,fp);
       
        // printf("\n Do you want to continue adding details : [y/n] \t");
        // getc(choice);
   // } 
    return_to_menu();
    fclose(fp);
}

// function to search the student information 
void std_search()
{
    errno = 0;
    fp = fopen("D:/FacultyMgmtSystem/student_database.bin","rb");
    if(fp == NULL)
        {
            fprintf(stderr,"\n Error : %s", strerror(errno));
            printf("\n Please create file before procedding !");
        }
    rewind(fp);                     // moving the pointer to the initial line
    fseek(fp,0,SEEK_END);           //seeking to the last of the files
    offsetposition = ftell(fp);
    if(offsetposition > 0)
    {
        printf("\n Enter the Name to search : \t ");
        scanf("%s",temp_request);
        printf("\n Searching for possible results..........");
        rewind(fp);
        while(fread(&s, sizeof(s),1,fp))
        {
            if(strcmp(temp_request,s.fname) == 0)
            {
                printf("\n \t %s \t %s \t %s\t %s\t %ld\t  %s\t %.2f\t %d \t", s.fname,s.mname, s.lname, s.address, s.contact, s.email, s.gpa, s.registration);
                has_record = 'y';
            }
        }
        if (has_record = 'n')
            printf("\n Sorry the record you are trying to search is not found in the list. ");
    }   
    else
    {
        printf("\n Sorry The file is empty. \n Please Add some details before procedding !!");
    } 
}

// function to delete the record of the students
void std_delete()
{
    top_menu();
    errno = 0;
	
    fp = fopen("D:/FacultyMgmtSystem/student_database.bin","rb");	
    temp = fopen("D:/FacultyMgmtSystem/temp_student_database.bin","wb");

	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}

	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);

	if (offsetposition > 0)
	{
		printf("\n Please Enter the Registration Number to delete :\t");
		scanf("%s", temp_request);
		rewind(fp);

		while (fread(&s, sizeof(s), 1, fp))
		{
			if (strcmp(temp_request, s.registration) == 0)          // looking for the match 
			{
				has_record = 'y';
                
                // asking for the user confirmation 
				printf("\n Do you want to delete the following record :\n 1 : Yes , 0 :No?");
                printf("\n --------------------------------------------------------------------");
                printf("\n | Name    : %s %s %s", s.fname, s.mname, s.lname);
                printf("\n | Address : %s",s.address);
                printf("\n | Contact : %ld", s.contact);
                printf("\n | Reg. No : %s",s.registration);
                printf("\n ---------------------------------------------------------------------\n");

				scanf("%d", &ch);
				if (ch == 1)
				{
					flag = 1;
				}
				else
					return;
			}
		}

		if (has_record == 'n')
			    printf("\n Sorry the Number you are trying to delete is not found in the list");
		
        // deleting the data 
        if (flag == 1)
		{
			rewind(fp);
			while (fread(&s, sizeof(s), 1, fp))
			{
				if (strcmp(temp_request, s.registration) != 0)
				{
					fwrite(&s, sizeof(s), 1, temp);
				}
			}
			printf("\n One record deleted ! ");
		}
	}

     // code if the file is empty 
	else
    printf("\n The file is empty. Please create some record before procedding !");
	fclose(fp);
	fclose(temp);
	remove("student_database.bin");
	rename("temp_student_database.bin", "student_database.bin");
	return_to_menu();
}

// function to display the students info
void std_display()
{
    top_menu();
    errno = 0;

    fp = fopen("D:/FacultyMgmtSystem/student_database.bin","rb");	

    // checking for the error
    if(fp == NULL)
    {
        fprintf(stderr, "\n %s", strerror(errno));
        return_to_menu();
    }

    //displaying the titles 
    printf("\n Name  \t Address  \t Registration \t Contact Number /t Email Address /t Faculty /t Semester /t GPA of +2 /n");

    while(fread(&s, sizeof(struct student), 1, fp))
    {
        // displaying the details of all the students 
        printf("\n %s %s %s \t %-15s \t %-18s \t %-15ld \t %-15s \t %-15s \t %-15s \t %.2f",s.fname, s.mname, s.lname, s.address, s.registration, s.contact, s.email, s.faculty, s.semester , s.gpa);

    }
}

// main std mgmt funciton declaration 
void std_mgmt()
{
    top_menu();
    c_menu();
    printf("\n Please Enter your choice : \t");
    scanf("%d",&ch);
    switch (ch)
    {
        case 1 : std_add(); break;
        case 2 : std_search(); break;
        case 3 : std_display(); break;
        case 5 : return_to_menu(); break;
        default : printf("\n Invalid Choice");
    }

}
/* code for the main menu that is to be displayed in the front page */
void main_menu()
{
    do
    {
    top_menu();
    printf("****************************    [ 1 ]   >>  [  STUDENT MANAGEMENT   ]   ***************************\n");
    printf("****************************    [ 2 ]   >>  [  TEACHER MANAGEMENT   ]   ***************************\n");
    printf("****************************    [ 3 ]   >>  [  CLASS ROOM MANAGEMENT]   ***************************\n");
    printf("****************************    [ 4 ]   >>  [  SALARY MANAGEMENT    ]   ***************************\n");
    printf("****************************    [ 5 ]   >>  [  QUIT                 ]   ***************************\n");
    printf("***************************************************************************************************\n");
    printf("***************************************************************************************************\n");
    printf("\n Please Enter your choice : \t");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: std_mgmt(); break;
        case 5 : exit_program(); break; 
        default : printf("\n Please enter the number from 1 to 5 only ");
        
    }
    }
    while(ch != 5);
}

/* code for the user authorization */
void login()
{
    
    // declaring the default username and the pasword
   int pw;
    // asking the used for their credintials
    printf("\n Enter your password : \t");
    scanf("%d",&pw);

    // checking for the user validation 
    if(password != pw)
    {
        printf("\n Password is invalid");
        return login();
    }
    else
    {
        main_menu();
    }
}

/* Main Functions */
int main()
{
    top_menu();
    login();
    return 0;
}