#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main() {
    //books categorized based on 3 categories
    //[0] = title of media [1] = time period, [2] = emotion, [3] = plot

    //array of books to display to the user for input feedback
    char bookarr[9][4][25] = {{"Nineteen Eighty Four","futuristic", "sad", "action"},
                              {"Good Omens","futuristic", "happy", "comedy"},
                              {"Life Of Pi","modern", "sad", "action"},
                              {"Call Of The Wild","modern", "happy", "action"},
                              {"Beloved","old", "sad", "comedy"},
                              {"Hunger Games", "futuristic", "fear", "action"},
                              {"Little Women","old", "happy", "romance"},
                              {"Cats Cradle","futuristic", "happy", "action"},
                              {"The Little Prince","old", "happy", "action"}};

        //counters to tally and store favourited properties of media
    int categorycount [3][3] = {{0,0,0},{0,0,0},{0,0,0}}; //where order is old, modern, futuristic|happy,sad,fear|action,romance,comedy

    for(int i = 0; i<9;i++){ //mimicking UI functionality prior to full integration
        int yesOrNo; //variable to stroe user preference
        printf("Do you like this book? %s", bookarr[i][0]); //prompt user with each book title in the array and ask them to 'like' or 'dislike' it
        scanf("%d",&yesOrNo); //get feedback from user- 1= yes, 0= no
        //switch case for user feedback to tally favourited properties
        if(yesOrNo){
        //if user 'likes' the book, add tally onto those properties ex. action, happy, futuristic all get an increased tally
            for(int p = 1; p<4;p++){ //parse through each property of the book that is being shown
                if(strcmp(bookarr[i][p],"old")==0){ //add a tally to the property that the book has and store it
                    categorycount[0][0]++;
                }
                if(strcmp(bookarr[i][p],"modern")==0){  //same. adding a tally to the property that the book has and store it
                    categorycount[0][1]++;
                }
                if(strcmp(bookarr[i][p],"futuristic")==0){
                    categorycount[0][2]++;
                }
                if(strcmp(bookarr[i][p],"happy")==0){
                    categorycount[1][0]++;
                }
                if(strcmp(bookarr[i][p],"sad")==0){
                    categorycount[1][1]++;
                }
                if(strcmp(bookarr[i][p],"fear")==0){
                    categorycount[1][2]++;
                }
                if(strcmp(bookarr[i][p],"action")==0){
                    categorycount[2][0]++;
                }
                if(strcmp(bookarr[i][p],"romance")==0){
                    categorycount[2][1]++;
                }
                if(strcmp(bookarr[i][p],"comedy")==0){
                    categorycount[2][2]++;
                }
            }
        }
    }

    char preferenceArray [3][25]; //create array to store the preferred properties (those with the most tallys)


    //filter through 2D array 'category count'  array to compare the property tallies
    for(int i = 0; i<3; i++){
        int temp = 0;
        for(int b = 1; b<3;b++){
            if(categorycount[i][b]>categorycount[i][temp]){
                temp = b;
            }
        }
        //switch case statement to compare tallies and add the property with the highest tally to the 'preference array'
        if(i==0){
            switch(temp) {
                case 0:
                    strcpy(preferenceArray[0],"old");
                    break;
                case 1:
                    strcpy(preferenceArray[0],"modern");
                    break;
                case 2:
                    strcpy(preferenceArray[0],"futuristic");
                    break;
                default:
                    break;
            }
        }
        if(i==1){
            switch(temp) {
                case 0:
                    strcpy(preferenceArray[1],"happy");
                    break;
                case 1:
                    strcpy(preferenceArray[1],"sad");
                    break;
                case 2:
                    strcpy(preferenceArray[1],"fear");
                    break;
                default:
                    break;
            }
        }
        if(i==2){
            switch(temp) {
                case 0:
                    strcpy(preferenceArray[2],"action");
                    break;
                case 1:
                    strcpy(preferenceArray[2],"romance");
                    break;
                case 2:
                    strcpy(preferenceArray[2],"comedy");
                    break;
                default:
                    break;
            }
        }
    }

    //open media database file
    FILE *fp;
    fp = fopen("media.txt", "r");
    //check that file was opened properly
    if(fp == NULL){
        printf("File was not opened properly");
    }

    //number of media elements
    int elements = 107;
    //number of properties for each element
    int properties = 5;
    //size of each property
    int size = 25;

    //create triple pointer array to store 2D array of strings from media file
    //dynamically allocate memory so that the database size can change

    char ***media = (char**)malloc(elements *sizeof(char**)); //memory for each media element
    for(int i = 0; i<elements; i++){
        media[i] = malloc(properties*sizeof(char*)); //memory the properties of the media
        for(int j = 0; j<properties; j++){
            media[i][j] = malloc(size*sizeof(char)); //memory for each string
            fscanf(fp, "%s", media[i][j]); //scan in media data from database file
        }
    }

    //print check of media strings to ensure it comes in properly
//    for(int i = 0; i< elements; i++){
//        for(int j = 0; j<properties; j++){
//            printf("%s", media[i][j]);
//        }
//    }


    // print check for the preferred properties
    //printf("%s %s %s\n", preferenceArray[0],preferenceArray[1],preferenceArray[2]);



    //print out media recommendations
    printf("Your media recommendations are: \n\n");

    //parse through media database 3D array and compare the properties of each media element with the preferenced properties
    //if these properties are a match, print the media recommendation in this format (media type : media name)
    for(int i = 0; i< elements; i++){
            if(strcmp(media[i][2],preferenceArray[0]) == 0 && strcmp(media[i][3],preferenceArray[1]) == 0 && strcmp(media[i][4],preferenceArray[2])==0){
                printf("%s: %s\n", media[i][1],  media[i][0]);
            }

    }


    return 0;
}