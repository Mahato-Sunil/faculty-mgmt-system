/*
    This is a Faculty (college) Management system
    it is written in c language and is developed by
    SUnil Mahato
    website : mahatosunil.com.np
    Budhanilkantha, Kathmandu
    Saraswati Multiple Campus
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* global variable declaration */
int ch;
int i; // for the for loop  and other loop
char choice = 'y';
int offsetposition;
char has_record = 'n';
char temp_request[30];
int flag;

#define password 1234

/* Structure declaration */
/* struct for students */
struct student
{
    char fname[25];
    char mname[25];
    char lname[25];
    char address[30];
    char contact[15];
    char email[30];
    float gpa;
    char registration[30];
    char semester[15];
};
struct student s;

// struct for the teachers
struct teacher
{
    char fname[25];
    char mname[25];
    char lname[25];
    char address[30];
    char contact[15];
    char email[30];
    int work_experience;
    int ssf;
    char sub[50];
};
struct teacher tech;

// structure for the routine
struct routine
{
    char subject[20];
    char time[15];
    char teacher[20];
};

// variable initialization for the routine
// storing the routine in array of structures
// future updates are to be made in the array without changing other paramenters
// change the following array for altering the routines of the different faculty

// array of routine for semester 1
struct routine sem_1[] =
    {
        {"ENGLISH I", "10:00-11:00", "MR. SHOVAKANT REGMI"},
        {"MATHS", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", "MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", "MR. DEEPAK POUDEL"}};

// array of routine for semester 2
struct routine sem_2[] =
    {
        {"ENGLISH II", "10:00-11:00", " MR. DEVRAJ MAHATO"},
        {"MATHS II ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"C PROGRAM", "12:00-01:00", " MR. DEEPAK POUDEL"},
        {"MP arch.", "01:30- 02:30", "Mr. SUJAN SHRESTHA"},
        {"FINANCE", "02:30-03:30", " MR. DR BHANDARI"}};

// array of routine for semester 3
struct routine sem_3[] =
    {
        {"ENGLISH I", "10:00-11:00", " MR. SHOVAKANT REGMI"},
        {"MATHS ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", " MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", " MR. DEEPAK POUDEL"}};

// array of routine for semester 4
struct routine sem_4[] =
    {
        {"ENGLISH I", "10:00-11:00", " MR. SHOVAKANT REGMI"},
        {"MATHS ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", " MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", " MR. DEEPAK POUDEL"}};

// array of routine for semester 5
struct routine sem_5[] =
    {
        {"ENGLISH I", "10:00-11:00", " MR. SHOVAKANT REGMI"},
        {"MATHS ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", " MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", " MR. DEEPAK POUDEL"}};

// array of routine for semester 6
struct routine sem_6[] =
    {
        {"ENGLISH I", "10:00-11:00", " MR. SHOVAKANT REGMI"},
        {"MATHS ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", " MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", " MR. DEEPAK POUDEL"}};

// array of routine for semester 7
struct routine sem_7[] =
    {
        {"ENGLISH I", "10:00-11:00", " MR. SHOVAKANT REGMI"},
        {"MATHS ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", " MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", " MR. DEEPAK POUDEL"}};
// array of routine for semester 8
struct routine sem_8[] =
    {
        {"ENGLISH I", "10:00-11:00", " MR. SHOVAKANT REGMI"},
        {"MATHS ", "11:00-12:00", "Mr.PRAHLAD SANGRAULA"},
        {"DIGITAL LOGIC", "12:00-01:00", " MR. SUJAN  SHRESTHA"},
        {"SOCIOLOGY ", "01:30- 02:30", "Mr.PRAHLAD SANGRAULA"},
        {"COMPUTER", "02:30-03:30", " MR. DEEPAK POUDEL"}};

// file pointer declaration
FILE *fp, *temp;    // file pointer for students
FILE *fpt, *t_temp; // file pointer for teachers

// function to return to main menu
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
    clear_screen();
    printf("\n Do you want to exit ? \n Press 0 to exit from the program. ( Press any number key to cancel.) \t");
    scanf("%d", &ch);
    if (ch == 0)
    {
        clear_screen();
        printf("\n Thank you for Using the program");
    }
    else
        return;
}

/* code for showing the top logo  menu */
void top_menu()
{
    // using graphics function to display on the top of the page
    clear_screen();
    printf("***************************************************************************************************\n");
    printf("****************************   WELCOME TO SARASWATI MULTIPLE CAMPPUS   ****************************\n");
    printf("****************************            CREATED BY SUNIL MAHATO         ***************************\n");
    printf("****************************         WEBSITE :  mahatosunil.com.np      ***************************\n");
    printf("****************************         EMAIL   :  sunilmaht642@gmail.com  ***************************\n");
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
    fp = fopen("D:/FacultyMgmtSystem/student_database.bin", "ab");

    printf("\n Enter the details of the students : ");

    /* taking the information of the students using the struct */
    printf("\n Enter first Name : \t");
    scanf("%s", s.fname);

    printf("Enter Middle Name :\t");
    scanf("%s", s.mname);

    printf("Enter Last Name : \t ");
    scanf("%s", s.lname);

    printf("Enter Address: \t ");
    scanf("%s", s.address);

    printf("Enter Contact Number : \t");
    scanf("%s", &s.contact);

    printf("Enter Email Address : \t\t");
    scanf("%s", s.email);

    printf("Enter the GPA  \t");
    scanf("%f", &s.gpa);

    printf("Enter the Registration Number :\t");
    scanf("%s", s.registration);

    printf("Enter Semester :\t");
    scanf("%s", s.semester);

    // inserting the details of the studnets into file
    fwrite(&s, sizeof(struct student), 1, fp);

    return_to_menu();
    fclose(fp);
}

// function to only show the details of the studetns
void infoStudent()
{
    printf("\n --------------------------------------------------------------------");
    printf("\n | Name    : %s %s %s", s.fname, s.mname, s.lname);
    printf("\n | Address : %s", s.address);
    printf("\n | Contact : %s", s.contact);
    printf("\n | Reg. No : %s", s.registration);
    printf("\n | Email Id: %s", s.email);
    printf("\n | Semester: %s", s.semester);
    printf("\n ---------------------------------------------------------------------\n");
}

// function to search the student information
void std_search()
{
    top_menu();
    errno = 0;
    fp = fopen("D:/FacultyMgmtSystem/student_database.bin", "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "\n Error : %s", strerror(errno));
        printf("\n Please create file before procedding !");
        return_to_menu();
    }

    rewind(fp);             // moving the pointer to the initial line
    fseek(fp, 0, SEEK_END); // seeking to the last of the files
    offsetposition = ftell(fp);

    if (offsetposition > 0)
    {
        printf("\n Enter the Name to search : \t ");
        scanf("%s", temp_request);
        printf("\n Searching for possible results..........");
        rewind(fp);

        while (fread(&s, sizeof(s), 1, fp)) // searching the name in the file
        {
            if (strcmp(temp_request, s.fname) == 0)
            {
                infoStudent();
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

    fp = fopen("D:/FacultyMgmtSystem/student_database.bin", "rb");        // opening the file to read  the data
    temp = fopen("D:/FacultyMgmtSystem/temp_student_database.bin", "wb"); // opening the file to add the data after deleting

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
            if (strcmp(temp_request, s.registration) == 0) // looking for the match
            {
                has_record = 'y';

                // asking for the user confirmation
                printf("\n Do you want to delete the following record :\n 1 : Yes , 0 :No?");
                infoStudent();
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
                    fwrite(&s, sizeof(s), 1, temp); // searching for match and copying the content of the file until the match is found to the new temp file
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

    fp = fopen("D:/FacultyMgmtSystem/student_database.bin", "rb");

    // checking for the error
    if (fp == NULL)
    {
        fprintf(stderr, "\n %s", strerror(errno));
        return_to_menu();
    }

    rewind(fp); // rewinding the pointer to the initial line

    fseek(fp, 0, SEEK_END); // going to the last of the file
    offsetposition = ftell(fp);

    if (offsetposition > 0)
    {
        printf("\n Preparing to read the data .........");
        rewind(fp);

        while (fread(&s, sizeof(struct student), 1, fp))
        {
            // displaying the details of all the students
            infoStudent();
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
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        std_add();
        break;
    case 2:
        std_search();
        break;
    case 3:
        std_display();
        break;
    case 4:
        std_delete();
        break;
    case 5:
        return_to_menu();
        break;
    default:
        printf("\n Invalid Choice");
    }
    return_to_menu();
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
    top_menu();
    errno = 0;

    // opening the file teacher.bin for adding the details of the teachers
    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin", "ab");

    // getting the details of the teachers
    printf("\n Enter FIrst Name : \t ");
    scanf("%s", tech.fname);

    printf("Enter Middle Name : \t");
    scanf("%s", tech.mname);

    printf("Enter Last Name : \t");
    scanf("%s", tech.lname);

    printf("Enter Address : \t ");
    scanf("%s", tech.address);

    printf("Enter COntact Number : \t  ");
    scanf("%s", tech.contact);

    printf("Enter Email Id :  \t");
    scanf("%s", tech.email);

    printf("Enter SSF number :\t");
    scanf("%d", &tech.ssf);

    printf("Enter Work Experience :\t");
    scanf("%d", &tech.work_experience);

    printf("Enter the subject taught [ use comma for multiple subject] \t");
    scanf("%s", tech.sub);

    fclose(fpt);
    return_to_menu();
}

// function to display the teachers info only
void infoTeacher()
{

    printf("\n --------------------------------------------------------------------");
    printf("\n | Name       : %s %s %s", tech.fname, tech.mname, tech.lname);
    printf("\n | Address    : %s", tech.address);
    printf("\n | Contact    : %s", tech.contact);
    printf("\n | SSF No     : %s", tech.ssf);
    printf("\n | Experience : %d years", tech.work_experience);
    printf("\n | Subjects   : %s", tech.sub);
    printf("\n ---------------------------------------------------------------------\n");
}

// function to display the list of teachers
void teach_display()
{

    top_menu();
    errno = 0;
    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin", "rb"); // opening the file for reading purpose

    // checking for the error
    if (fpt == NULL)
    {
        fprintf(stderr, "\n %s", strerror(errno));
        return_to_menu();
    }
    rewind(fpt); // rewinding the pointer to the initial line

    fseek(fpt, 0, SEEK_END); // going to the last of the file
    offsetposition = ftell(fpt);

    if (offsetposition > 0)
    {
        printf("\n Preparing to read the data .........");
        rewind(fpt);

        while (fread(&tech, sizeof(struct teacher), 1, fpt))
        {
            // displaying the details of all the students
            infoTeacher();
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

    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin", "rb");         // opening file for reading
    t_temp = fopen("D:/FacultyMgmtSystem/temp_teacher_database.bin", "wb"); // opening file for temporary storing the  data

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
        while (fread(&tech, sizeof(tech), 1, fpt))
        {
            // checking if the data match or not
            if (temp_ssf == tech.ssf)
            {
                has_record = 'y';
                // asking for the user validation
                printf("\n Do you want to delete the following record :\n 1 : Yes , 0 :No?");
                infoTeacher();
                scanf("%d", &ch); // asking the users for confirmaion
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
                if (temp_ssf != tech.ssf)
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

    fpt = fopen("D:/FacultyMgmtSystem/teacher_database.bin", "rb"); // opening file for reading
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
                infoTeacher();
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

// main function for the teacher management
void teach_mgmt()
{

    top_menu();
    c_menu();
    printf("\n Please Enter your choice :\t");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        teach_add();
        break;
    case 2:
        teach_search();
        break;
    case 3:
        teach_display();
        break;
    case 4:
        teach_delete();
        break;
    case 5:
        return_to_menu();
        break;
    default:
        printf("\n Invalid Choice");
    }
    return_to_menu();
}

/*
    functions for the classroom management
    - display the routine
    - display the faculty wise information
*/

// code for showing the common format in the routine function
void format()
{

    printf("\n-------------------------------------------------------------------------------");
    printf("\n NOTE :  ROUTINE APPLICABLE FROM SUNDAY TO FRIDAY !");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n BREAK TIME : \t [ 01:00 -- 01:30 ]");
    printf("\n-------------------------------------------------------------------------------");
}

// function to display the routine of semester 1
void sem_first()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER FIRST ");
    format(); // caling the format function to show the format of the routine
    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_1[i].subject, sem_1[i].time, sem_1[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

// function to display the routine of semester 2
void sem_second()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER SECOND ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine

    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_2[i].subject, sem_2[i].time, sem_2[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

// function to display the routine of semester 3
void sem_third()
{
    // displaying the routine

    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER THIRD ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine

    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_3[i].subject, sem_3[i].time, sem_3[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

// function to display the routine of semester 4
void sem_fourth()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER FOURTH ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine

    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_4[i].subject, sem_4[i].time, sem_4[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

// function to display the routine of semester 5
void sem_fifth()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER FIFTH ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine
    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_5[i].subject, sem_5[i].time, sem_5[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");

    return_to_menu();
}

// function to display the routine of semester 6
void sem_sixth()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER SIXTH ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine
    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_6[i].subject, sem_6[i].time, sem_6[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

// function to display the routine of semester 7
void sem_seventh()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER SEVENTH ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine
    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_7[i].subject, sem_7[i].time, sem_7[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

// function to display the routine of semester 8
void sem_eighth()
{

    // displaying the routine
    printf("\n Preparing to display the routine............");
    printf("\n \n");
    printf("\n \t \t \t \t SEMESTER EIGHT ");
    printf("\n-------------------------------------------------------------------------------");
    format(); // caling the format function to show the format of the routine
    // looping the contents of the array
    for (i = 0; i < 5; i++)
    {
        printf("\n| \t %s \t | \t %s \t| \t %-5s \t", sem_8[i].subject, sem_8[i].time, sem_8[i].teacher);
    }
    printf("\n-------------------------------------------------------------------------------");
    return_to_menu();
}

void routine_mgmt()
{

    top_menu();
    // displaying the functions
    printf("***********          [ 1 ] >> [ FIRST SEMESTER ]         [ 5 ] >> [ FIFTH SEMESTER  ]         ******************\n");
    printf("***********          [ 2 ] >> [ SECOND SEMESTER]         [ 6 ] >> [ SIXTH SEMESTER  ]         ******************\n");
    printf("***********          [ 3 ] >> [ THIRD SEMESTER ]         [ 7 ] >> [ SEVENTH SEMESTER]         ******************\n");
    printf("***********          [ 4 ] >> [ FOURTH SEMESTER]         [ 8 ] >> [ EIGHTH SEMESTER ]         ******************\n");
    printf("***********                                              [ 9 ] >> [ QUIT            ]         ******************\n");
    printf("****************************************************************************************************************\n");
    printf("\n Enter your choice : \t");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        sem_first();
        break;
    case 2:
        sem_second();
        break;
    case 3:
        sem_third();
        break;
    case 4:
        sem_fourth();
        break;
    case 5:
        sem_fifth();
        break;
    case 6:
        sem_sixth();
        break;
    case 7:
        sem_seventh();
        break;
    case 8:
        sem_eighth();
        break;
    case 9:
        exit_program();
    default:
        printf("\n Invalid input ! ");
    }
    return_to_menu();
}

/* code for the main menu that is to be displayed in the front page */
void menu()
{

    top_menu();
    do
    {
        printf("****************************    [ 1 ]   >>  [  STUDENT MANAGEMENT   ]   ***************************\n");
        printf("****************************    [ 2 ]   >>  [  TEACHER MANAGEMENT   ]   ***************************\n");
        printf("****************************    [ 3 ]   >>  [  ROUTINE              ]   ***************************\n");
        printf("****************************    [ 0 ]   >>  [  QUIT                 ]   ***************************\n");
        printf("***************************************************************************************************\n");
        printf("***************************************************************************************************\n");
        printf("\n Please Enter your choice : \t");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            std_mgmt();
            break;
        case 2:
            teach_mgmt();
            break;
        case 3:
            routine_mgmt();
            break;
        case 0:
            exit_program();
            break;
        default:
            printf("\n Please enter the number from 1 to 5 only ");
        }
    } while (ch != 0);
}

/* code for the user authorization */
void login()
{

    // declaring the default username and the pasword
    int pw;
    // asking the used for their credintials
    printf("\n Enter your password : \t");
    scanf("%d", &pw);

    // checking for the user validation
    if (password != pw)
    {
        printf("\n Password is invalid \n");
        return login();
    }
    else
    {
        menu();
    }
}

/* Main Functions */
int main()
{

    top_menu();
    login();
    return 0;
}