/*Name: Deirdre Deeney
 *Date: 08/12/2022
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAMELEN 15 //defines the maximum length of a name

/******************************************************
                Set Global Variables
*******************************************************/

struct Person { char lname[20]; char fname[20]; int id; }; //declare struct with data types
struct Person *data;                                       //declare pointer to struct


void countID (struct Person* data,int N); // declare function


int main(  )
{

    /******************************************************
                    Set  Variables
    *******************************************************/
    int  N, numfiles, totalN=0, prevN=0;
    char filename[MAXNAMELEN];

     /*****************************************************
            Open File combined to Write to
    *******************************************************/

    FILE *filecombined = fopen("filecombined.csv","w");
    if (filecombined == NULL)
    {
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }

    /******************************************************
         User inputs number of files to be included
    *******************************************************/
    printf("Please input the number of files to be included\n");
    scanf("%d",&numfiles);

    /******************************************************
        Read In File Name From user Console & Update
        Dyanamic Memory Array
    *******************************************************/

    for(int j=0;j<numfiles;j++){

        memset( filename, '\0', MAXNAMELEN ); /*Fills 'filename' with 0 */

        printf("\nPlease input Student Details CSV File:\n");
        scanf( "%15s", filename );

        FILE *str = fopen( filename, "r") ; //open file for read
        if (str==NULL) {
            perror(filename) ;
            exit(-1) ;
        }

        fscanf( str, "%d\n", &N ) ;      // reads value from file stream (str) and stores it in N.
        calloc(N,sizeof(struct Person)); // create dynamic memory struct

        //printf("Size of N: %d\n", N);  //for testing N value at this point

        totalN+=N;  //Add vaule N to total N, this will allow

        data=(struct Person*)realloc(data,totalN*sizeof(struct Person)); // create new struct with size of totalN
        printf("Reallocating dynamic memory\n");

        //printf("Size of totalN: %d\n", totalN); // for testing the size of totalN
             //for testing

        for (int i=prevN; i<totalN ; i++ ) {
            //printf("Adding content to position %d in data\n", i); //for testing

            fscanf( str, "%[^,],%[^,],B%08d\n", data[prevN].lname, data[prevN].fname, &(data[prevN].id) ); //scan in new values starting at prevN to new array
            fprintf(filecombined,"%s,%s, B%08d\n",data[prevN].lname,data[prevN].fname, data[prevN].id);    //append values to line starting at prevN to new .csv file

            prevN ++; //Increment the prevN value by the amount of times this loop has run.
        }


        fclose(str);     // close file

    }


    /******************************************************
           Read & output specfic value to console screen&
           Call Function to count Student IDs
    *******************************************************/
    /* Access the dynamic array... */
    printf("\n%s, %s, B%08d\n", data[1].lname, data[1].fname,data[1].id) ;
    printf("%s, %s, B%08d\n\n", data[21].lname, data[21].fname,data[21].id) ;

    countID(data,totalN); //Calling countID Function

    /******************************************************
           Clear Dynamic memory & Close
    *******************************************************/

    free(data);                // clear allocated memory

    fclose (filecombined);     // close file

    return 0;
}

/******************************************************
    Function to count the number of Student IDs >1000
*******************************************************/


void countID (struct Person* data,int totalN){

    int count = 0;

    for(int i = 0; i <= totalN; i++){
        if(data[i].id > 1000){
            count++;
        }
    }

    printf("\nNumber of students with ID greater than 1000: %d\n", count);

}
