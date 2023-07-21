#include<stdio.h>
#include<string.h>

typedef struct {  //unique = enroll
	char name[20], uname[20], upass[20];
	int age, sem, enroll;
}Student;


typedef struct {  //unique = isbn
	char bname[20], author[20], isbn[20];
	int qty;
	float costpu;
}Book;

typedef struct{
	int dd, mm, yy;
}Date;

typedef struct {  //unique = empid
	char name[20], uname[20], upass[20];
	Date dob;
	int empid;
}Employee;

typedef struct {
	char isbn[20];
	int enroll;
	Date doi, dor;
}Book_Student_Map;

typedef struct {
	char isbn[20];
	int enroll;
	int status;
}Book_req;

void studashboard(Student stu);
void empdashboard(Employee emp);
void bookRelease();
void editStuDetails(Student stu);
void showIssuedBooks(int enroll);
void requestbook(int enroll);
void viewrequestedbooks();

void registerstu(){
	Student s, sr;
	char choice;
	FILE *fp, *fpr;
	int flag=0;
	fp = fopen("stu_rec.dat", "a");
	
	do{
		printf("Enter student name : ");
		gets(s.name);
		fflush(stdin);
		
		//search student username
		fpr = fopen("stu_rec.dat", "r");
	 do{	
		printf("Enter student user name : ");
		gets(s.uname);
		while(fread(&sr,sizeof(Student),1,fpr)>0)
		{
			if(strcmp(sr.uname,s.uname)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("Username exists.Please try again");
			rewind(fpr);
		}
	 } while(flag==1);
		fclose(fpr);
	
		
		
		printf("Enter student password : ");
		gets(s.upass); fflush(stdin);
		printf("Enter student age : ");
		scanf("%d", &s.age);
		printf("Enter student semester : ");
		scanf("%d", &s.sem);
		printf("Enter student enroll no : ");
		scanf("%d", &s.enroll);
		fflush(stdin);
		
		fwrite(&s, sizeof(Student), 1, fp);
		
		
		printf("Student registered successfully...\n");
		
		printf("Do you want to register more ? [y/N] ");
		scanf("%c", &choice);
		fflush(stdin);
	}while(choice == 'y' || choice=='Y');
	
	fclose(fp);
}

void showallstu(){
	FILE *fp;
	fp = fopen("stu_rec.dat", "r");
	
	Student s;
	
	printf("\nName\t\tAge\tSem\tEnroll\tUsername\tpassword\n---------------------------------------------------------------\n");
	while(fread(&s, sizeof(Student), 1, fp) > 0){
		printf("%s\t%d\t%d \t %d\t",s.name, s.age, s.sem, s.enroll);
		printf("%s\t%s\n", s.uname, s.upass);
	}
	
	fclose(fp);
}


void stulogin(){
	FILE *fp;
	fp = fopen("stu_rec.dat", "r");
	
	Student s;
	int flag = 0;
	char un[20], pass[20];
	printf("Enter username: ");
	gets(un);
	printf("Enter password: ");
	gets(pass);
	
	while(fread(&s, sizeof(Student), 1, fp) > 0){
		if(strcmp(s.uname, un) == 0 && strcmp(s.upass, pass) == 0){
			flag = 1;
			break;
		}
	}
	
	fclose(fp);
	
	if(flag == 0){
		printf("User not registerd ..\n");
	} else{
	
		printf("Login successfull\n");
		studashboard(s);
	}
}

void studashboard(Student stu){
	int choice, c = 1;
	Student s;
	Book b;

	FILE *fp;
	
	printf("Welcome .. %s %c%c", stu.name, 1,1);
	
	do{
	printf("\n\nList of actions: \n");
	printf("\t1. Issued books\n\t2. Edit basic detail\n\t3.Request for book issue\n4.Logout");
	printf("\nSelect any options: ");
	scanf("%d", &choice);  fflush(stdin);
	
	 switch(choice){
		case 1:
			showIssuedBooks(stu.enroll);
		break;
		case 2:
			editStuDetails(stu);
		break;
		case 3:
			requestbook(stu.enroll);
			
		case 4:
			c = 0;
	 }
	}while(c);
}



void showIssuedBooks(int enroll){
	Book_Student_Map bsm;
	Book bo;
	FILE *fpr;
	FILE *fp = fopen("book_stu_map_rec.dat", "r");
	
	int flag = 0;
	printf("ISBN \t Enroll # \t DOI \t\t DOR \n------------------------------------------------------\n");
	while(fread(&bsm, sizeof(Book_Student_Map), 1, fp) > 0){
		if(bsm.enroll == enroll){
			
			fpr=fopen("book_rec.dat","r+");
			while(fread(&bo,sizeof(Book),1,fpr)>0)
			{
				if(strcmp(bsm.isbn,bo.isbn)==0)
				{
				
			
			printf("%s \t %d \t %02d-%02d-%4d \t %02d-%02d-%4d\n", bsm.isbn, bsm.enroll, bsm.doi.dd, bsm.doi.mm, bsm.doi.yy, bsm.dor.dd, bsm.dor.mm, bsm.dor.yy);
			flag = 1;
		}
		}
		fclose(fpr);
	}
	
	if(flag == 0){
		printf("No record found\n");
	}
	
	fclose(fp);
}
}

  void requestbook(int enroll)
  {
  	Book_req br;
  	Book bo;
  	Student stu;
  	char name[20], author[20];
  	int status=0;
  	int flag=0;
  	FILE *fp,*fpr;
  	fp=fopen("book_request.dat","a+");
  	fpr=fopen("book_rec.dat","r+");
  	do
  	{
	  
		printf("Enter book title");
  	gets(name);
  	printf("Enter book author");
  	gets(author);
  	while(fread(&bo,sizeof(Book),1,fpr)>0)
{
	if((strcmp(bo.bname,name)==0) && (strcmp(bo.author,author)==0))
	{
		if(bo.qty>0){
			br.enroll=enroll;
		   strcpy(br.isbn,bo.isbn);
			br.status=0;
			fwrite(&br,sizeof(Book_req),1,fp);
			flag=1;
			break;
		}
		
	}
}
	if(flag==0)
	{
		
	
	printf("Book unavailable.Please search with another book\n");
	rewind(fpr);
}
}
while(flag==0);
	  	
  	fclose(fpr);
  	fclose(fp);
  	
  }

void editStuDetails(Student stu){
	FILE *fp = fopen("stu_rec.dat", "r+");	
	Student s;
	
	printf("\nEdit student record \n-----------------------------------------\n");
	while(fread(&s, sizeof(Student), 1, fp) > 0){
		if(s.enroll == stu.enroll) {
		
		printf("Enter student name : ");
		gets(s.name);
		fflush(stdin);
		printf("Enter student password : ");
		gets(s.upass); fflush(stdin);
		printf("Enter student age : ");
		scanf("%d", &s.age);
		printf("Enter student semester : ");
		scanf("%d", &s.sem);
		printf("Enter student enroll no : ");
		scanf("%d", &s.enroll);
		fflush(stdin);
		
		fseek(fp, -sizeof(Student), SEEK_CUR);
		fwrite(&s, sizeof(Student), 1, fp);
		
		printf("Student updated successfully...\n");
		break;
		}
	}
	
	fclose(fp);
}

void bookEntry(){
	Book b,bo;
	char choice;
	FILE *fp,*fpr;
	int flag=0;
	
	fp = fopen("book_rec.dat", "a");
	
	do{
		printf("Enter book name : ");
		gets(b.bname); fflush(stdin);
		printf("Enter author : ");
		gets(b.author);
		
				fpr = fopen("book_rec.dat", "r");
	 do{	
		printf("Enter book isbn: ");
		gets(b.isbn);
		fflush(stdin);
		while(fread(&bo,sizeof(Student),1,fpr)>0)
		{
			if(strcmp(bo.isbn,b.isbn)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("Book exists.Please try again");
			rewind(fpr);
		}
	 } while(flag==1);
		fclose(fpr);
	
		
		printf("Enter quatity : ");
		scanf("%d", &b.qty);	fflush(stdin);
		printf("Enter cost per unit : ");
		scanf("%f", &b.costpu);
		fflush(stdin);
		
		fwrite(&b, sizeof(Book), 1, fp);
		
		printf("Book details saved successfully...\n");
		
		printf("Do you want to save more ? [y/N] ");
		scanf("%c", &choice);
		fflush(stdin);
	}while(choice == 'y' || choice=='Y');
	
	fclose(fp);
}

void showallbooks(){
	FILE *fp;
	fp = fopen("book_rec.dat", "r");
	
	Book b;
	
	printf("Name \t\t author \t ISBN \t Quantity \t Unit price\n-------------------------------------------------------\n");
	while(fread(&b, sizeof(Book), 1, fp) > 0){
		printf("%s \t %s \t %s \t %d \t %.2f\n",b.bname, b.author, b.isbn, b.qty, b.costpu);
	}
	
	fclose(fp);
}

 void bookedit(Book bo)
 {
 	Book b;
 	FILE *fp;
 	fp=fopen("book_rec.dat","r+");
 	while(fread(&b,sizeof(Book),1,fp)>0)
 	{
 		if(strcmp(bo.isbn,b.isbn)==0)
 		{
 			printf("Enter book title");
 			gets(b.bname);
 			printf("Enter book author");
 			gets(b.author);
 			fflush(stdin);
 			printf("Enter quantity");
 			scanf("%d",b.qty);
 			printf("enter price");
 			scanf("%f",b.costpu);
 			fseek(fp,-sizeof(Book),SEEK_CUR);
 			fwrite(&b,-sizeof(Book),1,fp);
 			
 			
 			printf("book details updated succesfully");
 			break;
		 }
	 }
	 fclose(fp);
 }
void registeremp(){
	Employee e,em;
	char choice;
	FILE *fp,*fpr;
	int flag=0;
	
	fp = fopen("emp_rec.dat", "a");
	
	do{
		printf("Enter employee name : ");
		gets(e.name); fflush(stdin);
				fpr = fopen("emp_rec.dat", "r");
	 do{	
		printf("Enter employee user name : ");
		gets(e.uname);
		while(fread(&em,sizeof(Employee),1,fpr)>0)
		{
			if(strcmp(em.uname,e.uname)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("Username exists.Please try again");
			rewind(fpr);
		}
	 } while(flag==1);
		fclose(fpr);
	
		
		printf("Enter employee password : ");
		gets(e.upass); fflush(stdin);
		printf("Enter employee id : ");
		scanf("%d", &e.empid);  fflush(stdin);
		printf("Enter dob : ");
		scanf("%2d-%2d-%4d", &e.dob.dd, &e.dob.mm, &e.dob.yy);  fflush(stdin);

		fwrite(&e, sizeof(Employee), 1, fp);
		
		printf("Employee registered successfully...\n");
		
		printf("Do you want to register more ? [y/N] ");
		scanf("%c", &choice);
		fflush(stdin);
	}while(choice == 'y' || choice=='Y');
	
	fclose(fp);
}

void showallemp(){
	FILE *fp;
	fp = fopen("emp_rec.dat", "r");
	
	Employee e;
	
	printf("\nName\t\tEmpId\tDOB\t\tUsername\tpassword\n---------------------------------------------------------------\n");
	while(fread(&e, sizeof(Employee), 1, fp) > 0){
		printf("%s \t %d \t %d-%d-%d\t", e.name, e.empid, e.dob.dd, e.dob.mm, e.dob.yy);
		printf("%s \t  %s \n", e.uname, e.upass);
	}
	
	fclose(fp);
}

void emplogin(){
	FILE *fp;
	fp = fopen("emp_rec.dat", "r");
	
	Employee b;
	int flag = 0;
	char uname[20], upass[20];
	printf("Enter username: ");
	gets(uname);
	printf("Enter password: ");
	gets(upass);
	
	while(fread(&b, sizeof(Employee), 1, fp) > 0){
		if(strcmp(b.uname, uname) == 0 && strcmp(b.upass, upass) == 0){
			flag = 1;
			break;
		}
	}
	
	fclose(fp);

	if(flag == 0){
		printf("User not registerd ..\n");
	} else {
		printf("Login successfull\n");
		empdashboard(b);
	}
}

void empdashboard(Employee emp){
	int choice, c = 1;
	Book bo;
	
	printf("Welcome .. %s %c", emp.name, 1);
	
	do{
	printf("\n\nList of actions: \n");
	printf("\t1. Book entry\n\t2. Book issue\n\t3.requested books\n 4. edit employee details\n 5.book edit\n6.Logout\n");
	printf("\nSelect any options: ");
	scanf("%d", &choice);  fflush(stdin);
	
	switch(choice){
		case 1:
			bookEntry();
		break;
		case 2:
			bookRelease();
		break;
		case 3:
		viewrequestedbooks();
		break;
			
			case 4:
				editempDetails(emp);
				break;
				case 5:
					bookedit(bo);
					break;
				case 6:
			c = 0;
			
	}
	}while(c);
}

void editempDetails(Employee emp)
{
	Employee e;
	FILE *fp;
	fp=fopen("emp_rec.dat","r+");
	while(fread(&e,sizeof(Employee),1,fp)>0)
	{
		if(e.empid==emp.empid)
		{
			printf("Enter name");
			gets(e.name);
			fflush(stdin);
			printf("Enter password");
			gets(e.upass);
			fseek(fp,-sizeof(Employee),SEEK_CUR);
			fwrite(&e,sizeof(Employee),1,fp);
			printf("Employee details updated succesfully");
			break;
		}
	}
	fclose(fp);
	
}
void bookRelease(){
	FILE *fp;
	Book b;
	Student s;
	int flag = 0;
	int enroll;
	char isbn[20];
	Book_Student_Map bsm;
	
	
	fp = fopen("stu_rec.dat", "r");
	do{
		printf("Enter student enrollment no: ");
		scanf("%d", &enroll);   
		  fflush(stdin);
		
		while(fread(&s, sizeof(Student), 1, fp) > 0){
			if(enroll == s.enroll){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			printf("Incorrect enrollment no. Please try again ..\n");
			rewind(fp);
		}
	} while(flag == 0);
	 
	 fclose(fp);
	 
	flag = 0;
	fp = fopen("book_rec.dat", "r");
	do{
		printf("Enter book ISBN: ");
		gets(isbn);   fflush(stdin);
		
		while(fread(&b, sizeof(Book), 1, fp) > 0){
			if(strcmp(b.isbn, isbn) == 0 ){
				if(b.qty > 0){
					flag = 2;
				} else {
					flag = 1;
				}
				break;
			}
		}
		if(flag == 0){
			printf("Incorrect ISBN. Please try again ..\n");
			rewind(fp);
		} else if(flag == 1){
			printf("Required quantity not available. Please try again ..\n");
			rewind(fp);
		}
	} while(flag != 2);
	 
	 fclose(fp);
	 
	 
	 printf("Enter date of issue [dd-mm-yyyy] : ");
	 scanf("%2d-%2d-%4d", &bsm.doi.dd,  &bsm.doi.mm,  &bsm.doi.yy);
	 fflush(stdin);
	 
	 printf("Enter date of return [dd-mm-yyyy] : ");
	 scanf("%2d-%2d-%4d", &bsm.dor.dd,  &bsm.dor.mm,  &bsm.dor.yy);
	 fflush(stdin);
	 
	 bsm.enroll = enroll;
	 strcpy(bsm.isbn, isbn);
	 
	 fp = fopen("book_stu_map_rec.dat", "a");
	 
	 fwrite(&bsm, sizeof(bsm), 1, fp);
	 
	 fclose(fp);
	 printf("Book issued successfully");
	 
	 fp = fopen("book_rec.dat", "r+");
	 	while(fread(&b, sizeof(Book), 1, fp) > 0){
			if(strcmp(b.isbn, isbn) == 0){				
				fseek(fp, -sizeof(Book), SEEK_CUR);
				b.qty--;
				fwrite(&b, sizeof(Book), 1, fp);
				break;
			}
		}
	fclose(fp);
	showallbooks();
}
 void viewrequestedbooks()
 {
 	FILE *fp, *fpr, *fpb;
		Student s;
		Book_Student_Map bsm;
		Book b;
	char ch;
	char isbn[20];
	int flag=0,enroll;
	Book_req br;
	
	fp = fopen("book_request.dat", "r+");
		fpr = fopen("book_stu_map_rec.dat", "a");

		while(fread(&br, sizeof(Book_req), 1, fp) > 0){
		
			
			if(br.status == 0){
				
				printf("Student with enroll %d has requested for book with ISBN = %s", br.enroll, br.isbn);	
				
				printf("\n\nDo you approve? y/n\n");
				scanf("%c",&ch);
				fflush(stdin);
	
				if(ch=='y' || ch=='Y')
				{
					
				bsm.enroll = br.enroll;
				strcpy(bsm.isbn, br.isbn);
		
				printf("Enter date of issue [dd-mm-yyyy] : ");
	 			scanf("%2d-%2d-%4d", &bsm.doi.dd,  &bsm.doi.mm,  &bsm.doi.yy);
	 			fflush(stdin);
	 
	 			printf("Enter date of return [dd-mm-yyyy] : ");
	 			scanf("%2d-%2d-%4d", &bsm.dor.dd,  &bsm.dor.mm,  &bsm.dor.yy);
	 			fflush(stdin);
	 			 		
	 
	 			fwrite(&bsm, sizeof(bsm), 1, fpr);
	 			
	 			fpb = fopen("book_rec.dat", "r+");
	 			while(fread(&b, sizeof(Book), 1, fpb) > 0){
					if(strcmp(b.isbn, br.isbn) == 0){				
						fseek(fpb, -sizeof(Book), SEEK_CUR);
						b.qty--;
						fwrite(&b, sizeof(Book), 1, fpb);
						break;
					}
				}
				fclose(fpb);
	 			
	 			printf("Book issued successfully\n");
	 			
	 			} else {
	 				printf("Book issue request rejected\n");
				 }
	 				
				
			}
		}
	 fclose(fpr);
	 fclose(fp);
	 
	 fp=fopen("book_request.dat","r+");
	 	while(fread(&br, sizeof(Book_req), 1, fp) > 0){
			if(br.status == 0){				
				fseek(fp, -sizeof(Book_req), SEEK_CUR);
				br.status=1;
				fwrite(&br, sizeof(Book_req), 1, fp);
			}
			
		}
	fclose(fp);
	 			
 	
 }

void main(){
	Student stu;
	Book bo;
//	registerstu();
//showallstu();
//stulogin();
//studashboard(stu);
//emplogin();
//registeremp();
//bookEntry();
//showallbooks();
//bookedit(bo);
//emplogin();
//stulogin();


	
}

