#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "xis.h"
#include "xreloc.h"
char* getR(unsigned char byte);
char* get8R(char* item);
int main(int argc, char **argv) {
     FILE *file=fopen(argv[1], "rb");//open the file
    if(!file){
        printf("file open failed!");//if open failed ,exit
	printf("a");
        exit(1);
    }
    printf(".globl test\n");//Prologue
    printf("test:\n");
    printf("push %%rbp\n");
    printf("mov %%rsp, %%rbp\n");
    printf(".L0000:\n");
    int sign=1;//while it isn't empty
    int debug=0;//identify if it need to debug
    unsigned int address=0;//caculate the address
    while(sign){
        unsigned char byte1,byte2;
        fread(&byte1,sizeof(unsigned char), 1, file);
        fread(&byte2,sizeof(unsigned char),1,file);
        if(byte1==0x00&&byte2==0x00){
            sign=0;
	    break;
        }
        switch(byte1){
	    case 0xC1:{//jmp instruction
			      address+=4;
                unsigned char imm[2];
                fread(imm,sizeof(unsigned char), 2, file);
                int address2=(imm[0]<<8)|imm[1];
                printf("jmp .L%04x\n",address2);
		printf(".L%04x:\n",address);
		break;
            }
	    case 0x01:{//ret Instruction
                address+=2;
                printf("ret\n");
                printf(".L%04x:\n",address);
                break;
            }
	    case 47:{//out  Instructions
                address+=2;
                unsigned char s=(byte2>>4)&0x0F;
                printf("mov $1,%%rax\n");
                printf("mov $1,%%rdi\n");
                printf("mov %s,%%rsi\n",getR(s));
                printf("mov $1,%%rdx\n");
                printf("syscall\n");
                printf(".L%04x:\n",address);
                break;
            }
	    case 0x90:{//loadb  Instructions
                address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("movb (%s),%s\n",getR(s),get8R(getR(d)));
                printf(".L%04x:\n",address);
                break;
            }
            case 0x91:{//strob  Instructions
                address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("movb %s,(%s)\n",get8R(getR(s)),getR(d));
                printf(".L%04x:\n",address);
                break;
            }
	    case 0x8E:{//load  Instructions
                address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("mov (%s),%s\n",getR(s),getR(d));
                printf(".L%04x:\n",address);
                break;
            }
            case 0x8F:{//stro  Instructions
                address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("mov %s,(%s)\n",getR(s),getR(d));
                printf(".L%04x:\n",address);
                break;
            }
            case 0xC2:{//call  Instructions
                address+=4;
                unsigned char imm[2];
                fread(imm,sizeof(unsigned char), 2, file);
                int address3=(imm[0]<<8)|imm[1];
                printf("call .L%04x\n",address3);
                printf(".L%04x:\n",address);
                break;
            }
	    case 0x61:{//br  Instructions
                address+=2;
                int L=byte2;
                printf("test $1,%%r15\n");
                printf("jne .L%04x\n",address+L-2);
                printf(".L%04x:\n",address);
                break;
            }
            case 0x81:{//add  Instructions
		address+=2;
                unsigned char s=byte2&0x0F;
                unsigned char d=(byte2>>4)&0x0F;
                printf("add %s,%s\n",getR(d),getR(s));
		printf(".L%04x:\n",address);
		break;
            }
	    case 0xE1:{//loadi  Instructions
	//		      printf("e1\n");
		address+=4;
                unsigned char d=(byte2>>4)&0x0F;
                unsigned char imm[2];
                fread(imm,sizeof(unsigned char), 2, file);
                int value=(imm[0]<<8)|imm[1];
                printf("mov $%hu,%s\n",(int16_t) value,getR(d)); 
		printf(".L%04x:\n",address);
		break;
            }
            case 0x8D:{//mov  Instructions
		address+=2;
                unsigned char s=(byte2>>4)&0x0F;
                unsigned char d=byte2&0x0F;
                printf("mov %s,%s\n",getR(s),getR(d));
		printf(".L%04x:\n",address);
		break;
            }
	    case 0x03:{ //std  Instructions      
		debug=1;
		address+=2;
		printf(".L%04x:\n",address);
		break;
            }
	    case 0x02:{//cld  Instructions
                debug=0;
		address+=2;
		printf(".L%04x:\n",address);
		break;
            }
	    case 0x82:{//sub  Instructions
			      address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("sub %s,%s\n",getR(s),getR(d));
		printf(".L%04x:\n",address);
		break;
            }
	    case 0x83:{//imul Instructions
			      address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("imul %s,%s\n",getR(s),getR(d));
		printf(".L%04x:\n",address);
		break;
            }
	   case 0x85:{//and  Instructions
			     address+=2;
            unsigned char d=byte2&0x0F;
            unsigned char s=(byte2>>4)&0x0F;
            printf("and %s,%s\n",getR(s),getR(d));
	    printf(".L%04x:\n",address);
            break;
        }
           case 0x86:{//or  Instructions
			     address+=2;
            unsigned char d=byte2&0x0F;
            unsigned char s=(byte2>>4)&0x0F;
            printf("or %s,%s\n",getR(s),getR(d));
	    printf(".L%04x:\n",address);
            break;
            }
           case 0x87:{//xor  Instructions
			     address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("xor %s,%s\n",getR(s),getR(d));
		printf(".L%04x:\n",address);
                break;
           }
	case 0x41:{//neg  Instructions
			  address+=2;
                unsigned char s=(byte2>>4)&0x0F;
                printf("neg %s\n",getR(s));
		printf(".L%04x:\n",address);
                break;
            }
        case 0x42:{//not  Instructions
			  address+=2;
            unsigned char s=(byte2>>4)&0x0F;
            printf("not %s\n",getR(s));
	    printf(".L%04x:\n",address);
            break;
            }
        case 0x48:{//inc  Instructions
            unsigned char s=(byte2>>4)&0x0F;
            printf("inc %s\n",getR(s));
            break;
            }
        case 0x49:{//dec  Instructions
                unsigned char s=(byte2>>4)&0x0F;
                printf("dec %s\n",getR(s));
                break;
             }
	case 0x8A:{//test  Instructions
			  address+=2;
                unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("test %s,%s\n",getR(s),getR(d));
		printf("setnz %%r15b\n");
		printf(".L%04x:\n",address);
                break;
       	     }
        case 0x8B:{//cmp  Instructions
			address+=2;
                    unsigned char d=byte2&0x0F;
                    unsigned char s=(byte2>>4)&0x0F;
                    printf("cmp %s,%s\n",getR(s),getR(d));
		    printf("setg %%r15b\n");
		    printf(".L%04x:\n",address);
                    break;
       	     }
	case 0x8C:{//equ  Instructions 
		    address+=2;	  
                 unsigned char d=byte2&0x0F;
                unsigned char s=(byte2>>4)&0x0F;
                printf("cmp %s,%s\n",getR(s),getR(d));
		printf("sete %%r15b\n");
		printf(".L%04x:\n",address);
                break;
            }
	case 0x43:{//push  Instructions
			  address+=2;
                unsigned char s=(byte2>>4)&0x0F;
                printf("push %s\n",getR(s));
		printf(".L%04x:\n",address);
                break;
            }
         case 0x44:{//pop  Instructions
			   address+=2;
                unsigned char s=(byte2>>4)&0x0F;
                printf("pop %s\n",getR(s));
		printf(".L%04x:\n",address);
                break;
            }
        }
	if(debug){
            printf("call debug\n");
        }
    }
    printf("pop %%rbp\n");
    printf("ret\n");//Epilogue
    fclose(file);
    return 0;
}
char* getR(unsigned char byte){//search the correct register
    char* item=malloc(sizeof(char *));
    switch(byte){
        case 0:
            item="%rax";
            break;
        case 1:
            item="%rbx";
            break;
        case 2:
            item="%rcx";
            break;
        case 3:
            item="%rdx";
            break;
        case 4:
            item="%rsi";
            break;
	case 5:
	    item="%rdi";
	    break;
        case 6:
            item="%r8";
            break;
        case 7:
            item="%r9";
            break;
        case 8:
            item="%r10";
            break;
        case 9:
            item="%r11";
            break;
        case 10:
            item="%r12";
            break;
        case 11:
            item="%r13";
            break;
        case 12:
            item="%r14";
            break;
        case 'F':
            item="%r15";
            break;
        case 14:
            item="%rbp";
            break;
        case 15:
            item="%rsp";
            break;
    }
    return item;
}
char* get8R(char *item){//search the register in 8 bit
    if(strcmp(item,"%rax")==0)return "%al";
    if(strcmp(item,"%rdx")==0)return "%dl";
    if(strcmp(item,"%rcx")==0)return "%cl";
    return NULL;
}


