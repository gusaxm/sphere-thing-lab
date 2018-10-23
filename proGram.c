//this was made for a programming course
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define WORDLENGTH 30
#define MAX 10000
struct sphere
{
    double radius,xPos,yPos,zPos;
    char color[WORDLENGTH];
};
typedef struct sphere Sphere;
Sphere createSphere(double radius, double x, double y, double z, char color[WORDLENGTH])
{
    Sphere s;
    s.radius=radius;
    s.xPos=x;
    s.yPos=y;
    s.zPos=z;
    strcpy(s.color,color);
    return s;
}
void addSpheres(Sphere reg[], int *pNrOfSpheres)//DONE?
{
    char again[WORDLENGTH]="yes", tmp[WORDLENGTH], color[WORDLENGTH];
    double radius,xPos,yPos,zPos;
    while(strcmp(again,"yes")==0 || strcmp(again,"y")==0)
    {
        printf("Set radius:");
        gets(tmp);
        radius=atof(tmp);
        printf("Set value of X:");
        gets(tmp);
        xPos=atof(tmp);
        printf("Set value of Y:");
        gets(tmp);
        yPos=atof(tmp);
        printf("Set value of Z:");
        gets(tmp);
        zPos=atof(tmp);

        srand(time(NULL));
        int colorNr=rand()%6+1;
        switch(colorNr)
        {
            case 1:strcpy(color,"black");printf("%s\n",color);
            break;
            case 2:strcpy(color,"white");printf("%s\n",color);
            break;
            case 3:strcpy(color,"green");printf("%s\n",color);
            break;
            case 4:strcpy(color,"blue");printf("%s\n",color);
            break;
            case 5:strcpy(color,"red");printf("%s\n",color);
            break;
            case 6:strcpy(color,"yellow");printf("%s\n",color);
            break;
        }

        reg[(*pNrOfSpheres)]=createSphere(radius,xPos,yPos,zPos,color);
        (*pNrOfSpheres)++;
        printf("Do you want to keep adding spheres? (yes/no): ");
        gets(again);
    }
}
void printSpheres(Sphere reg[],int *pNrOfSpheres)//DONE?
{
    if((*pNrOfSpheres)==0)
        printf("There are no spheres stored...\n");
    else
    {
        printf("-------------------------------------------------------------------------------\n");
       int i;
        for(i=0;i<(*pNrOfSpheres);i++)
        {
            printf("\n\tSphere(%d): radius:%.2f position:(%.2f,%.2f,%.2f) %s\n",i+1,reg[i].radius,reg[i].xPos,reg[i].yPos,reg[i].zPos,reg[i].color);
        }
        printf("-------------------------------------------------------------------------------\n");
    }
}
void writeToFile(Sphere reg[], int *pNrOfSpheres, char *pFile)  // SKRIVA OM ALLA SFÄRER ISTÄLLET FÖR ATT LÄGGA TILL NYA?
{

    FILE *fp;
    sprintf(pFile,"%s",pFile);
    fp=fopen(pFile,"w");
    fprintf(fp,"%d\n",(*pNrOfSpheres));       //ANTAL SFÄRER HÖGST UPP I FILEN
    int i;
    for(i=0;i<(*pNrOfSpheres);i++)
    {
        fprintf(fp,"%.2f %.2f %.2f %.2f %s\n",reg[i].radius,reg[i].xPos,reg[i].yPos,reg[i].zPos,reg[i].color);
    }
    fclose(fp);
}
void readFromFile(Sphere reg[], int *pNrOfSpheres, char *pFile)
{
    FILE *fp;
    fp=fopen(pFile,"r");
    if(fp!=NULL)
    {
        char color[WORDLENGTH];
        char tmp[WORDLENGTH];
        double radius,xPos,yPos,zPos;
        int exisitingSpheres=0;
        fscanf(fp,"%d",&exisitingSpheres);
        printf("%d\n",exisitingSpheres);
        int i=0;
        while((*pNrOfSpheres)<exisitingSpheres)
        {
            fscanf(fp,"%s",tmp);
            radius=atof(tmp);
            fscanf(fp,"%s",tmp);
            xPos=atof(tmp);
            fscanf(fp,"%s",tmp);
            yPos=atof(tmp);
            fscanf(fp,"%s",tmp);
            zPos=atof(tmp);
            fscanf(fp,"%s",color);
            reg[(*pNrOfSpheres)]=createSphere(radius,xPos,yPos,zPos,color);   //Funkar ej?
            (*pNrOfSpheres)++;
        }
        fclose(fp);
    }
}
void initializeSphereSearch(Sphere reg[], int *pNrOfSpheres, int searchResults[],int *pSphereNr)//WHAT TO SEARCH FOR
{
    char choice[WORDLENGTH];
    char tmp[WORDLENGTH];
    printf("Search for: radius, x, y or z: ");
    gets(choice);
    printf("Choose %s min and max value:(enter in between...) ",choice);
    gets(tmp);
    double min=atof(tmp);
    gets(tmp);
    double max=atof(tmp);
    printf("\tSphere(s) with %.2f <= %s <= %.2f\n",min,choice,max);
    printf("------------------------------------------------------------\n");    //60 "-"
    int i=0;
    while(i<(*pNrOfSpheres))
    {
        if(strcmp(choice,"radius")==0)
        {
            for(i=0;i<(*pNrOfSpheres);i++)
            {
                if(reg[i].radius>=min && reg[i].radius<=max)
                {
                    printf("\n\tradius:%.2f position:(%.2f,%.2f,%.2f)\n",reg[i].radius,reg[i].xPos,reg[i].yPos,reg[i].zPos);
                    searchResults[i]=i;
                    (*pSphereNr)++;
                }
            }
        }
        else if(strcmp(choice,"x")==0)
        {
            for(i=0;i<(*pNrOfSpheres);i++)
            {
                if(reg[i].xPos>=min && reg[i].xPos<=max)
                {
                    printf("\n\tradius:%.2f position:(%.2f,%.2f,%.2f)\n",reg[i].radius,reg[i].xPos,reg[i].yPos,reg[i].zPos);
                    searchResults[i]=i;
                    (*pSphereNr)++;
                }
            }
        }
        else if(strcmp(choice,"y")==0)
        {
            for(i=0;i<(*pNrOfSpheres);i++)
            {
                if(reg[i].yPos>=min && reg[i].yPos<=max)
                {
                    printf("\n\tradius:%.2f position:(%.2f,%.2f,%.2f)\n",reg[i].radius,reg[i].xPos,reg[i].yPos,reg[i].zPos);
                    searchResults[i]=i;
                    (*pSphereNr)++;
                }
            }
        }
        else if(strcmp(choice,"z")==0)
        {
            for(i=0;i<(*pNrOfSpheres);i++)
            {
                if(reg[i].zPos>=min && reg[i].zPos<=max)
                {
                    printf("\n\tradius:%.2f position:(%.2f,%.2f,%.2f)\n",reg[i].radius,reg[i].xPos,reg[i].yPos,reg[i].zPos);
                    searchResults[i]=i;
                    (*pSphereNr)++;
                }
            }
        }
        else{printf("\tIncorrect menu choice!\n");}
    }
    printf("\n------------------------------------------------------------\n");//60 "-"
}
void removeSpheres(Sphere reg[],int *pNrOfSpheres, int pSearchResults[],int *pSphereNr)//NOT FINISHED THANK YOU
{
    initializeSphereSearch(reg,&pNrOfSpheres,&pSearchResults,&pSphereNr);
    int i;
    for(i=0;i<(*pNrOfSpheres);i++)
    {
        printf("%d",pSearchResults[i]);
    }
}
void sortSpheres(Sphere reg[],int *pNrOfSpheres)
{
    char choice[WORDLENGTH];
    char tmp[WORDLENGTH];
    printf("Sort after radius, x or volume:");
    gets(choice);

    if(strcmp(choice,"radius")==0)
    {
        //SORT
        int i,j,k;
        double tmp;
        for(i=0;i<(*pNrOfSpheres);i++)
        {
            for(j=i;j<=(*pNrOfSpheres)-1;j++)
            {
                if(reg[j].radius<=reg[i].radius)
                {
                    tmp=reg[i].radius;
                    reg[i].radius=reg[j].radius;
                    reg[j].radius=tmp;
                }
            }
        }
    }
    else if(strcmp(choice,"x")==0)
    {
        //SORT
        int i,j,k;
        double tmp;
        for(i=0;i<(*pNrOfSpheres);i++)
        {
            for(j=i;j<=(*pNrOfSpheres)-1;j++)
            {
                if(reg[j].xPos<=reg[i].xPos)
                {
                    tmp=reg[i].xPos;
                    reg[i].xPos=reg[j].xPos;
                    reg[j].xPos=tmp;
                }
            }
        }
    }
    else if(strcmp(choice,"volume")==0)
    {
        //SORT
        int i,j,k;
        double tmp;
        for(i=0;i<(*pNrOfSpheres);i++)
        {
            for(j=i;j<=(*pNrOfSpheres)-1;j++)
            {
                if(reg[j].radius<=reg[i].radius)
                {
                    tmp=reg[i].radius;
                    reg[i].radius=reg[j].radius;
                    reg[j].radius=tmp;
                }
            }
        }
    }

}
void changeRadius(Sphere reg[],int *pNrOfSpheres,int searchResults[],int *pSphereNr,double *pNewRadius)
{
    int i,removeThis;
    for(i=0;i<(*pSphereNr);i++)
    {
        printf("%d",searchResults[i]);
    }
    for(i=0;i<(*pSphereNr);i++)
    {
        searchResults[i]=removeThis;
        reg[i].radius=(*pNewRadius);
    }
}
int main()
{
    int menuNr=0;
    int nrOfSpheres=0;
    int searchResults[MAX];
    Sphere sphereRegister[MAX];     //för alla sfärer
    int sphereNr=0;         //for search and change
    char file[WORDLENGTH];
    printf("Please choose a file name: ");
    gets(file);
    strcat(file,".txt");            //add .txt
    readFromFile(sphereRegister,&nrOfSpheres,file);

    printf("Sphere program v3.0\n");
    while(menuNr!=7)
    {
        printf("\nAdd sphere (1)\nPrint sphere (2)\nSort sphere (3)\nSphere search (4)\nChange sphere radius (5)\nRemove sphere (6)\nExit (7)\n");
        char tmp[WORDLENGTH];
        gets(tmp);
        menuNr=atoi(tmp);

        if(menuNr==1)//ADD
        {
        menuNr=0;
        addSpheres(sphereRegister,&nrOfSpheres);
        printf("\tNumber of spheres:%d\n",nrOfSpheres);
        }
        else if(menuNr==2)//PRINT
        {
            printf("Number of spheres:%d\n",nrOfSpheres);
            printSpheres(sphereRegister,&nrOfSpheres);
        }
        else if(menuNr==3)//SORT
        {
            sortSpheres(sphereRegister,&nrOfSpheres);
        }
        else if(menuNr==4)//SEARCH
        {
            initializeSphereSearch(sphereRegister,&nrOfSpheres,searchResults,&sphereNr);
        }
        else if(menuNr==5)//CHANGE RADIUS
        {
            printf("Choose new radius: ");
            char tmp[WORDLENGTH];
            double newRadius;
            gets(tmp);
            newRadius=atof(tmp);
            initializeSphereSearch(sphereRegister,&nrOfSpheres,searchResults,&sphereNr);
            changeRadius(sphereRegister,&nrOfSpheres,searchResults,&sphereNr,&newRadius);
        }
        else if(menuNr==6)//REMOVE
        {
            removeSpheres(sphereRegister,&nrOfSpheres,searchResults,&sphereNr);
        }
        else if(menuNr==7)//EXIT
        {
            writeToFile(sphereRegister,&nrOfSpheres,file);
            return 0;
        }
        else
            printf("Wrong menu number.\n");
    }
}
