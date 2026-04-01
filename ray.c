#include<stdio.h>
#include<stdlib.h>
//practicing parsing in C!

//literally super unreliable but idrc tbf
typedef struct{
    char* text[254];
}string;

typedef struct{
    string name;
    string last_name;
} Person;

typedef struct{
    string brand;
    int year;
    Person owner;
}Car;

int main(){
    FILE *pfile;
    Person p1;
    Car c1;
    p1.name.text[0] = (char*)"Mehdi";
    p1.last_name.text[0] = (char*)"Ben_Rebah";
    c1.owner = p1;
    c1.brand.text[0] = (char*)"Volvo";
    c1.year = 1996;
    pfile = fopen("prog.txt", "a");
    fprintf(pfile, "%s %s %s %d\n", (char *)*p1.name.text, (char *)*p1.last_name.text, (char *)*c1.brand.text, c1.year);
}