#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <conio.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


  sqlite3 *db;
   char *zErrMsg = 0;
   sqlite3_stmt* stmt;
   int rc;
 



int main_menu(){
   printf("\n \n \nWelcome to the Student Record Management System \n \n \n");
   printf("1. Enter Record \n2. Delete Record \n3. Update Record \n4. Select Record \n \n");
}

int enter_record(){
   char name[256], id[256], address[256], contact_number[256], level[256], program[256], email[256], gender[256], birthdate[256];
   int age;


   printf("Enter Name : ");
   scanf("%s", name);

   printf("Enter ID : ");
   scanf("%s", id);

   printf("Enter Address : ");
   scanf("%s", address);

   printf("Enter Contact Number : ");
   scanf("%s", contact_number);

   printf("Enter Grade Level : ");
   scanf("%s", level);

   printf("Enter Program : ");
   scanf("%s", program);

   printf("Enter Email : ");
   scanf("%s", email);

   printf("Enter Sex (F/M) : ");
   scanf("%s", gender);

   printf("Enter Age : ");
   scanf("%d", &age);

   printf("Enter Birthdate : ");
   scanf("%s", birthdate);



   char sql[1028] = "INSERT INTO STUDENTRECORDS (name, id, address, contact_number, grade_level, program, email, gender, age, birthdate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

   sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

   sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 2, id, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 3, address, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 4, contact_number, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 5, level, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 6, program, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 7, email, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 8, gender, -1, SQLITE_STATIC);
   sqlite3_bind_int64(stmt, 9, age);
   sqlite3_bind_text(stmt, 10, birthdate, -1, SQLITE_STATIC);

   sqlite3_step(stmt);
   sqlite3_finalize(stmt);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else if (rc == SQLITE_OK) {
      fprintf(stdout, "\n \n \nRecord Created \n");
   }
}

// (name, id, address, contact_number, grade_level, program, email, gender, age, birthdate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)


int update_record(){
   char name[256], id[256], address[256], contact_number[256], level[256], program[256], email[256], gender[256], birthdate[256];
   int age; 
   char sql[256] = "UPDATE StudentRecords set name = ?, address = ?, contact_number = ?, grade_level = ?, program = ?, email = ?, gender = ?, age = ?, birthdate = ? WHERE id = ?";
 

   char sql1[256] = "SELECT * from StudentRecords WHERE id = ?";
   sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
   char input_id[256];
   printf("Enter ID to Filter : ");
   scanf("%s", input_id);
   sqlite3_bind_text(stmt, 1, input_id, -1, SQLITE_STATIC);
   int result = sqlite3_step(stmt);

    if (result == SQLITE_ROW){
         printf("\nName : %s  \t \t ", sqlite3_column_text(stmt, 0));
         printf("\nID : %s ", sqlite3_column_text(stmt, 1));
         printf("\nAddress : %s ", sqlite3_column_text(stmt, 2));
         printf("\nContact Number : %s ", sqlite3_column_text(stmt, 3));
         printf("\nSection : %s ", sqlite3_column_text(stmt, 4));
         printf("\nProgram : %s ", sqlite3_column_text(stmt, 5));
         printf("\nEmail : %s ", sqlite3_column_text(stmt, 6));
         printf("\nGender : %s ", sqlite3_column_text(stmt, 7));
         printf("\nAge : %s ", sqlite3_column_text(stmt, 8));
         printf("\nBirthdate : %s ", sqlite3_column_text(stmt, 9));
         sqlite3_finalize(stmt);
      }
      else{
         printf("\n \nQuery not found");
      }



   printf(" \n \nUPDATE MODE ENTER THE FOLLOWING INFORMATION : \n");

   printf("Enter Name : ");
   scanf("%s", name);

   printf("Enter Address : ");
   scanf("%s", address);

   printf("Enter Contact Number : ");
   scanf("%s", contact_number);

   printf("Enter Grade Level : ");
   scanf("%s", level);

   printf("Enter Program : ");
   scanf("%s", program);

   printf("Enter Email : ");
   scanf("%s", email);

   printf("Enter Sex (F/M) : ");
   scanf("%s", gender);

   printf("Enter Age : ");
   scanf("%d", &age);

   printf("Enter Birthdate : ");
   scanf("%s", birthdate);

   sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

   sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 2, address, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 3, contact_number, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 4, level, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 5, program, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 6, email, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 7, gender, -1, SQLITE_STATIC);
   sqlite3_bind_int64(stmt, 8, age);
   sqlite3_bind_text(stmt, 9, birthdate, -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 10, input_id, -1, SQLITE_STATIC);


   sqlite3_step(stmt);
   sqlite3_finalize(stmt);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else if (rc == SQLITE_OK) {
      fprintf(stdout, "\n \n \nRecord Updated \n");
   }



}

int delete_record(){
 char id[256];
 char sql[256] = "DELETE FROM StudentRecords WHERE id = ?";

 printf("Enter the ID of the Record to be deleted : ");
 scanf("%s", id);

 sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
 sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);

 int result = sqlite3_step(stmt);

 if (rc != SQLITE_OK){
      

      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      printf("\n \nInvalid ID \n \n \n");

   }
   else{

      printf("Successfully Deleted \n \n \n");
      return 0;
      
   }
}



int select_record(){
   printf("\n Filter Records \n \n1. ID\n2. Name\n3. Gender\n4. Program");
   int choice, result;
   printf("\n \nEnter number menu : ");
   scanf("%d", &choice);

   

   switch(choice){
      case 1:
      char sql1[256] = "SELECT * from StudentRecords WHERE id = ?";
      sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
      char input_id[256];
      printf("Enter ID to Filter : ");
      scanf("%s", input_id);
      sqlite3_bind_text(stmt, 1, input_id, -1, SQLITE_STATIC);
      result = sqlite3_step(stmt);

       if (result == SQLITE_ROW){
         printf("\nName : %s ", sqlite3_column_text(stmt, 0));
         printf("\nID : %s ", sqlite3_column_text(stmt, 1));
         printf("\nAddress : %s ", sqlite3_column_text(stmt, 2));
         printf("\nContact Number : %s ", sqlite3_column_text(stmt, 3));
         printf("\nSection : %s ", sqlite3_column_text(stmt, 4));
         printf("\nProgram : %s ", sqlite3_column_text(stmt, 5));
         printf("\nEmail : %s ", sqlite3_column_text(stmt, 6));
         printf("\nGender : %s ", sqlite3_column_text(stmt, 7));
         printf("\nAge : %s ", sqlite3_column_text(stmt, 8));
         printf("\nBirthdate : %s ", sqlite3_column_text(stmt, 9));
         sqlite3_finalize(stmt);
      }
      else{
         printf("\n \nQuery not found");
      }

      break;

      case 2:
      char sql2[256] = "SELECT * from StudentRecords WHERE name = ?";
      sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
      char input_name[256];
      printf("Enter Name to Filter : ");
      scanf("%s", input_name);
      sqlite3_bind_text(stmt, 1, input_name, -1, SQLITE_STATIC);
      result = sqlite3_step(stmt);
      
       if (result == SQLITE_ROW){
         printf("\nName : %s ", sqlite3_column_text(stmt, 0));
         printf("\nID : %s ", sqlite3_column_text(stmt, 1));
         printf("\nAddress : %s ", sqlite3_column_text(stmt, 2));
         printf("\nContact Number : %s ", sqlite3_column_text(stmt, 3));
         printf("\nSection : %s ", sqlite3_column_text(stmt, 4));
         printf("\nProgram : %s ", sqlite3_column_text(stmt, 5));
         printf("\nEmail : %s ", sqlite3_column_text(stmt, 6));
         printf("\nGender : %s ", sqlite3_column_text(stmt, 7));
         printf("\nAge : %s ", sqlite3_column_text(stmt, 8));
         printf("\nBirthdate : %s ", sqlite3_column_text(stmt, 9));
         sqlite3_finalize(stmt);
      }
      else{
         printf("\n \nQuery not found");
      }
      break;

      case 3:
      char sql3[256] = "SELECT * from StudentRecords WHERE gender = ?";
      sqlite3_prepare_v2(db, sql3, strlen(sql3) + 1, &stmt, NULL);
      char input_gender [256];
      printf("Enter Gender to Filter : ");
      scanf("%s", input_gender);
      sqlite3_bind_text(stmt, 1, input_gender, -1, SQLITE_STATIC);
      result = sqlite3_step(stmt);

       if (result == SQLITE_ROW){
         printf("\nName : %s ", sqlite3_column_text(stmt, 0));
         printf("\nID : %s ", sqlite3_column_text(stmt, 1));
         printf("\nAddress : %s ", sqlite3_column_text(stmt, 2));
         printf("\nContact Number : %s ", sqlite3_column_text(stmt, 3));
         printf("\nSection : %s ", sqlite3_column_text(stmt, 4));
         printf("\nProgram : %s ", sqlite3_column_text(stmt, 5));
         printf("\nEmail : %s ", sqlite3_column_text(stmt, 6));
         printf("\nGender : %s ", sqlite3_column_text(stmt, 7));
         printf("\nAge : %s ", sqlite3_column_text(stmt, 8));
         printf("\nBirthdate : %s ", sqlite3_column_text(stmt, 9));
         sqlite3_finalize(stmt);
      }
      else{
         printf("\n \nQuery not found");
      }
      
      break;

      case 4:
      char sql4[256] = "SELECT * from StudentRecords WHERE program = ?";
      sqlite3_prepare_v2(db, sql4, strlen(sql4) + 1, &stmt, NULL);
      char input_program[256];
      printf("Enter Program to Filter : ");
      scanf("%s", input_program);
      sqlite3_bind_text(stmt, 1, input_program, -1, SQLITE_STATIC);
      result = sqlite3_step(stmt);


      if (result == SQLITE_ROW){
         printf("\nName : %s ", sqlite3_column_text(stmt, 0));
         printf("\nID : %s ", sqlite3_column_text(stmt, 1));
         printf("\nAddress : %s ", sqlite3_column_text(stmt, 2));
         printf("\nContact Number : %s ", sqlite3_column_text(stmt, 3));
         printf("\nSection : %s ", sqlite3_column_text(stmt, 4));
         printf("\nProgram : %s ", sqlite3_column_text(stmt, 5));
         printf("\nEmail : %s ", sqlite3_column_text(stmt, 6));
         printf("\nGender : %s ", sqlite3_column_text(stmt, 7));
         printf("\nAge : %s ", sqlite3_column_text(stmt, 8));
         printf("\nBirthdate : %s ", sqlite3_column_text(stmt, 9));
         sqlite3_finalize(stmt);
      }
      else{
         printf("\n \nQuery not found");
      }
      break;

      default:
      break;
   }
}
int main(void){
    
   /* Open database */
   rc = sqlite3_open("RecordManagement.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } 


   



   int choice;

   while(1){

   main_menu();
   printf("\n \n Enter menu choice : ");
   scanf("%d", &choice);


   switch (choice)
   {
   case 1:
      enter_record();

      break;


   case 2:
      delete_record();
      break;

   case 3:
      update_record();
      break;
   case 4:
      select_record();
      break;
   
   default:
      main();
      getche();
      break;
   }
   }
   




   sqlite3_close(db);
   return 0;


    return 0;
}