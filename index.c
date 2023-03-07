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
    char fname[20];
    char mname[20];
    char lname[20];
    char address[20];
    long int contact;
    char email[20];
    float gpa;
    char registration[20];
    char faculty[15];
    char semester[10];
};
struct student s;

// struct for the teachers 
struct teacher
{
    char fname[20];
    char mname[20];
    char lname[20];
    char address[20];
    long int contact;
    char email[20];
    int work_experience;
    int ssf;
};
struct teacher tech;


// file pointer declaration 
FILE *fp, *temp;
FILE *fpt, *t_temp;

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
            return_to_menu();
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

    fclose(fp);
    return_to_menu();

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
        return_to_menu();
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

    rewind(fp);    // rewinding the pointer to the initial line 

    fseek(fp, 0, SEEK_END); // going to the last of the file 
    offsetposition = ftell(fp);
    
    if(offsetposition > 0)
    {
        printf("\n Preparing to read the data .........");
        rewind(fp);

        //displaying the titles 
        printf("\n Name  \t Address  \t Registration \t Contact Number /t Email Address /t Faculty /t Semester /t GPA of +2 /n");

        while(fread(&s, sizeof(struct student), 1, fp))
        {
            // displaying the details of all the students 
            printf("\n %s %s %s \t %-15s \t %-18s \t %-15ld \t %-15s \t %-15s \t %-15s \t %.2f",s.fname, s.mname, s.lname, s.address, s.registration, s.contact, s.email, s.faculty, s.semester , s.gpa);

        }
    }
    else
    printf("\n The File is empty. !");

    fclose(fp);
    return_to_menu;
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
        case 4 : std_delete(); break;
        case 5 : return_to_menu(); break;
        default : printf("\n Invalid Choice");
    }

}

/* 
    Function for the teacher management system 
    it includes all the function for 
        - adding the teacher details
        - deleting the teacher details
        - displaying the teachers details
*/

// function for adding the teachers details 
void teach_add()
{
    errno = 0;

    // opening the file teacher.bin for adding the details of the teachers
    fpt =fopen ("D:/FacultyMgmtSystem/teacher_database.bin","ab");	
    
    // getting the details of the teachers

    printf("\n Enter FIrst Name : \t ");
    scanf("%s",tech.fname)

    printf("\n Enter Middle Name : \t");
    scanf("%s", tech.mname);

    printf("\n Enter Last Name : \t");
    scanf("%s", tech.lname);

    printf("\n Enter Address : \t ");
    scanf("%s", tech.address);

    printf("\n Enter COntact Number : \t  ");
    scanf("%ld", &tech.contact);

    printf("\n Enter Email Id :  \t");
    scanf("%s",tech.email);

    printf("\n Enter SSF number :\t");
    scanf("%d",&tech.ssf);

    printf("\n Enter Work Experience :\t");
    scnaf("%d", &tech.work_experience);

    fclose(fpt);
}

// function to display the list of teachers 
void teach_display()
{
    errno = 0;
    top_menu();

    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin","rb");	        // opening the file for reading purpose
   
    // checking for the error
    if(fp == NULL)
    {
        fprintf(stderr, "\n %s", strerror(errno));
        return_to_menu();
    }

    rewind(fpt);    // rewinding the pointer to the initial line 

    fseek(fpt, 0, SEEK_END); // going to the last of the file 
    offsetposition = ftell(fpt);
    if(offsetposition > 0)
    {
        printf("\n Preparing to read the data .........");
        rewind(fpt);
        
        //displaying the titles 
        printf("\n Name  \t Address  \t Contact Number /t Email Address /t SSF Number /t Work Experience  /n");

        while(fread(&tech, sizeof(struct teacher), 1, fpt))
        {
            // displaying the details of all the students 
            printf("\n %s %s %s \t %-15s \t %-18ld \t %-15s \t %-15d \t %-15d", tech.fname, tech.mname, tech.lname, tech.address, tech.contact, tech.email, tech.ssf, tech.work_experience);


        }
    }
    else
    printf("\n Sorry the file is empty !");

    fclose(fpt);
    return_to_menu();
}


// function to delete the teachers details 
void teach_delete()
{
    top_menu();

	errno = 0;
	int temp_ssf;
    // opening the file for reading and deleting the information 
    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin","rb"); // opening file for reading 
	t_temp = fopen("D:/FacultyMgmtSystem/temp_teacher_database.bin","wb");   // opening file for temporary storing the  data 
	
    if (fpt == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
        return_to_menu();
	}

	rewind(fpt);

	fseek(fpt, 0, SEEK_END);

	offsetposition = ftell(fpt);

	if (offsetposition > 0)
	{
		printf("\n Enter the SSF number of the teacher you want to remove  :\t");
		scanf("%d", temp_ssf);

		rewind(fpt);

        // reading the data 
		while (fread(&user, sizeof(user), 1, fpt))
		{
            // checking if the data match or not 
			if (temp_ssf == tech.ssf)
			{
				has_record = 'y';

                // asking for the user validation 
				printf("\n Do you want to delete the following record :\n 1 : Yes , 0 :No?");
                printf("\n --------------------------------------------------------------------");
                printf("\n | Name    : %s %s %s", tech.fname, tech.mname, tech.lname);
                printf("\n | Address : %s",tech.address);
                printf("\n | Contact : %ld", tech.contact);
                printf("\n | SSF No  : %s",tech.ssf);
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
        // showing user if the record is not found 
		if (has_record == 'n')
			printf("\n Sorry the Number you are trying to delete is not found in the list");
		
        // deleting the record of the teacher 
        if (flag == 1)
		{
			rewind(fpt);
			while (fread(&tech, sizeof(tech), 1, fpt))
			{
				if ( temp_ssf != tech.ssf)
				{
					fwrite(&tech, sizeof(tech), 1, t_temp);
				}
			}
			printf("\n One record deleted ! ");
		}
	}

	else
		printf("\n The file is empty.");

	fclose(fpt);
	fclose(t_temp);

	remove("teacher_database.bin");
	rename("temp_teacher_database", "teacher_database.bin ");
	return_to_menu();
}

// function to search the details of the teachers 
void teach_search()
{
    top_menu();
	errno = 0;
	
    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin","rb"); // opening file for reading 
    if (fpt == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
        return_to_menu();
	}

	rewind(fpt);
	fseek(fpt, 0, SEEK_END);

	offsetposition = ftell(fpt);

	if (offsetposition > 0)
	{
		printf("\n Enter the name of the teacher to search :\t");
		scanf("%s", temp_request);

		printf("\n Searching for possible result.... \n ");
		
        rewind(fpt);

		while (fread(&tech, sizeof(tech), 1, fpt))
		{
			if (strcmp(temp_request, tech.fname) == 0)
			{
                printf("\n --------------------------------------------------------------------");
                printf("\n | Name    : %s %s %s", tech.fname, tech.mname, tech.lname);
                printf("\n | Address : %s",tech.address);
                printf("\n | Email   : %s", tech.email);
                printf("\n | Contact : %ld", tech.contact);
                printf("\n | SSF No  : %s",tech.ssf);
                printf("\n ---------------------------------------------------------------------\n");
				has_record = 'y';
			}
		}

		if (has_record == 'n')
			printf("\n Sorry the Number you are trying to search is not found in the list");
	}
    else 
    printf("\n Sorry the file is empty. ");

	fclose(fpt);
	return_to_menu();
}

}

// main function for the teacher management 
void teach_mgmt()
{
    top_menu();
    c_menu();
    printf("\n Please Enter your choice :\t");
    scanf("d",&ch);
    switch(ch)
    {
        case 1 : teach_add(); break;
        case 2 : teach_search(); break;
        case 3 : teach_display(); break;
        case 4 : teach_delete(); break;
        case 5 :return_to_menu(); break;
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
        case 2 : teach_mgmt(); break;
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
