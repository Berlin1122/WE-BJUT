#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
 //����ؼ���
#define ID 1
#define INT8 2
#define INT10 3
#define INT16 4
#define IDN 5
#define PLUS 6
#define MINUS 7
#define MULTI 8
#define RDIV 9
#define GT 10
#define LT 11
#define EQ 12
#define LR_BRAC 13
#define RR_BRAC 14
#define SEMIC 15
#define IF 16
#define THEN 17
#define ELSE 18
#define WHILE 19
#define DO 20
char *Key[10]={"if","then","else","while","do"};
char Word[20],ch;                   // �洢ʶ����ĵ�����

int IsAlpha(char c) {                //�ж��Ƿ�Ϊ��ĸ
	if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A'))) return 1;
	else return 0;
}
 
int IsNum(char c){                //�ж��Ƿ�Ϊ����
	if(c>='0'&&c<='9') return 1;
	else return 0;
}

int Is81(char c){                //�ж��Ƿ�Ϊ����
	if(c>='1'&&c<='7') return 1;
	else return 0;
}

int Is82(char c){                //�ж��Ƿ�Ϊ����
	if(c>='0'&&c<='7') return 1;
	else return 0;
}

int Is16(char c){                //�ж��Ƿ�Ϊ����
	if((c>='0'&&c<='9')||(c>='a'&&c<='f')) return 1;
	else return 0;
}
int IsKey(char *Word){
	int i,m;
	for(i=0;i<5;i++){
		if((m=strcmp(Word,Key[i]))==0) break;
	}
	switch(i){
	case 0: return 1;
	case 1: return 2;
	case 2: return 3;
	case 3: return 4;
	case 4: return 5;
	default: return 0;
	}          //ʶ��ؼ��ֺ���
 
}
void scanner(FILE *fp){        //ɨ�躯��
	char Word[20]={'\0'};
	//char ch;
	int i,c;
	ch=fgetc(fp);        //��ȡ�ַ���ָ��fp���Զ�ָ����һ���ַ�
	if(IsAlpha(ch)){            //�жϸ��ַ��Ƿ�����ĸ
		Word[0]=ch;
		ch=fgetc(fp);
		i=1;
		while(IsNum(ch)||IsAlpha(ch)){   //�жϸ��ַ��Ƿ�����ĸ������
			Word[i]=ch;
			i++;
			ch=fgetc(fp);
		   }
		Word[i]='\0';       //'\0' �����ַ�����(�ո�)
		fseek(fp,-1,1);                              //����һ���ַ�
		c=IsKey(Word);                              //�ж��Ƿ��ǹؼ���
			switch(c){
				case 0: printf("%d\t%s\n\n",IDN,Word); break;
				case 1: printf("%d\n\n",IF); break;
				case 2: printf("%d\n\n",THEN); break;
				case 3: printf("%d\n\n",ELSE); break;
				case 4: printf("%d\n\n",WHILE); break;
				case 5: printf("%d\n\n",DO); break;
			}
	  }

      else                          //��ʼ�жϵ��ַ�������ĸ
		    if(IsNum(ch)){   //�ж��Ƿ�������	           
			   Word[0]=ch;
			   ch=fgetc(fp);
			   i=1;
			   if(Word[0]=='0'){
			   	if(Is81(ch)){
			   		Word[i]=ch;
					 i++;
					 ch=fgetc(fp);
			   	 while(Is82(ch)){
					 Word[i]=ch;
					 i++;
					 ch=fgetc(fp);
				}
				 Word[i]='\0';
				 fseek(fp,-1,1);                    //����
				 printf("%d\t%s\n\n",INT8,Word);
				
				 }
				 else if(ch=='x'){
				 	Word[i]=ch;
					 i++;
					 ch=fgetc(fp);
				 	 while(Is16(ch)){
					 Word[i]=ch;
					 i++;
					 ch=fgetc(fp);
				}
				 Word[i]='\0';
				 fseek(fp,-1,1);                    //����
				 printf("%d\t%s\n\n",INT16,Word);
				 }
				 else{
				 	
				 Word[i]='\0';
				 fseek(fp,-1,1);                    //����
				 printf("%d\t%s\n\n",INT10,Word);
				 	
				 	
				 	
				 }
			   	
			   	
			   }
			   else{
			   
			   while(IsNum(ch)){
					 Word[i]=ch;
					 i++;
					 ch=fgetc(fp);
				 }
			
				 Word[i]='\0';
				 fseek(fp,-1,1);                    //����
				 printf("%d\t%s\n\n",INT10,Word);
			}
		   }
		   else         //��ʼ�жϵ��ַ�������ĸҲ��������
		   {
			   Word[0]=ch;
			   switch(ch){
			   	case '+': printf("%d\n\n",PLUS); break;
			   	case '-': printf("%d\n\n",MINUS); break;
			   	case '*': printf("%d\n\n",MULTI); break;
			   	case '/': printf("%d\n\n",RDIV); break;
			   	case '>': printf("%d\n\n",GT); break;
			   	case '<': printf("%d\n\n",LT); break;
			   	case '=': printf("%d\n\n",EQ); break;
			   	case '(': printf("%d\n\n",LR_BRAC); break;
			   	case ')': printf("%d\n\n",RR_BRAC); break;
			   	case ';': printf("%d\n\n",SEMIC); break;
			   	
			  
			   default:printf("�޷�ʶ���ַ�!\n\n"); break;
			   }
		   }
}
main()
{
	char in_fn[30];                          //�ļ�·��
    FILE *fp;
    printf("\n������Դ�ļ�·������׺��(Դ�ļ�����'$'��β):"); 
    while(1){
	gets(in_fn);
	//scanf("%s",in_fn);
    if((fp=fopen(in_fn,"r"))!=NULL)  break;  //��ȡ�ļ����ݣ��������ļ�ָ�룬��ָ��ָ���ļ��ĵ�һ���ַ�
    else printf("�ļ�·������!����������:");
	}
 printf("\n�ʷ������������:\n");
 do{
	 ch=fgetc(fp);
	 if(ch=='$')   break;         //�ļ���#��β����Ϊɨ���������
	 else if(ch==' '||ch=='\t'||ch=='\n'){} //���Կո񣬿հף��ͻ���
	 else{
		 fseek(fp,-1,1);           //����һ���ֽڿ�ʼʶ�𵥴���
		 scanner(fp);
	 }
 }while(ch!='$');
 system("pause");
 return(0);
}

