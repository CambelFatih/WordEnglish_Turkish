#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
typedef struct Word
{
    char Eng[50];
    char Tur[50];
    struct Word* next;
} word;
word* head=NULL;
void read_file();
void arrangement();
void main_operation();
int size_box();
int main()
{
	read_file();
	printf("kelime sayisi : %d\n",size_box());
    arrangement();
	main_operation();
}
void main_operation()
{
    system("color 71");
    int random,i,j,boyut,box,dogru_say=0,yanlis_say=0,control;
    char A[50];
    srand(time(NULL));
    while(1)
    {
        while(1)
        {
        	printf("English Dictionary...\n");
        printf("1-Sadece Turkcesini Sor\n2-Karisik Sor\nCevap:");
        control=getch();
        if(control!='1'&&control!='2')
        {
        	system("cls");
        	printf("Secenekler Yanlizca '1' veya '2'..");
        	continue;
		}
		    system("cls");
        	printf("Kac adet Soru : ");
            scanf("%d",&boyut);
            if(boyut>0)
            {
            	break;
			}
			else
			{
				printf("Lutfen 0'dan buyuk bir sayi giriniz....\n");
			}
		}
    box=size_box();
    word*q=head;
    for(i=0;i<boyut;i++)
    {
        random=1+rand()%(box-1);
        for(j=1;j<random;j++)
        {
            q=q->next;
        }
        random=rand()%2;
        if(random==1 || control=='1')
        {
            printf("%s bu kelimenin turkcesi nedir?\n",q->Eng);
            fflush(stdin);
            gets(A);
            if(strcmp(q->Tur,A)==0)
            {
                system("cls");
                printf("dogru bildiniz..\n");
                dogru_say++;
            }
            else
            {
              printf("dogru cevap : %s\n",q->Tur);
              yanlis_say++;
            }
        }
        else if(random==0&&control=='2')
        {
            printf("%s bu kelimenin ingilizcesi nedir?\n",q->Tur);
             fflush(stdin);
             gets(A);
            if(strcmp(q->Eng,A)==0)
            {
                system("cls");
                printf("dogru bildiniz..\n");
                dogru_say++;
            }
            else
            {
              printf("dogru cevap : %s\n",q->Eng);
              yanlis_say++;
            }
        }
        q=head;
    }
    printf("\nDogru sayisi : %d\nYanlis sayisi : %d ",dogru_say,yanlis_say);
    printf("\nYeni test...\n");dogru_say=0;yanlis_say=0;
    }
}
void read_file()
{
    word *add,*q;
    FILE *p=fopen("english_word.txt","r");
    if(p==NULL)
    {
        printf("Dosya olusturuldu ama ici bos\n");
        p = fopen("english_word.txt","w");
        fclose(p);
    }
    else
    {
        while(!feof(p))
        {
            add = (word*)malloc(sizeof(word));
            fscanf(p,"%s %s",add->Eng,add->Tur);
            add->next=NULL;
            if(head==NULL)
            {
                head=add;
            }
            else
            {
                q=head;
                while(q->next!=NULL)
                {
                    q = q -> next;
                }
                q->next=add;
            }
        }
    }
    fclose(p);
}
void arrangement()
{
    int a,size=size_box();
    word *i,*j;
    char temp[50];
    for(i=head; i->next!=NULL; i=i->next)
    {
        for(j=i->next; j->next!=NULL; j=j->next)
        {
            if(strcmp(j->Eng,i->Eng)==-1)
            {
                strcpy(temp,j->Eng);
                strcpy(j->Eng,i->Eng);
                strcpy(i->Eng,temp);
                strcpy(temp,j->Tur);
                strcpy(j->Tur,i->Tur);
                strcpy(i->Tur,temp);
            }
        }
    }
    FILE *f=fopen("Arrangement.txt","w");
    i=head;
    if(f==NULL)
    {
        printf("Dosya Hatasi\n");
    }
    else
    {
        for(a=0; a<size; a++)
        {
            fprintf(f,"%s %s\n",i->Eng,i->Tur);
            i=i->next;
        }
    }
    fclose(f);
}
int size_box()
{
    int counter=0;
    word*q;
    for(q=head;q!=NULL;q=q->next)
    {
        counter++;
    }
    return counter;
}

