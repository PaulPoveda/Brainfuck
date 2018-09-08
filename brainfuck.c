#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void brainfuck_interpreter(char *instructions);
void clean(const char *buffer, FILE *fp);

char chaine[30000]={0};
char *ptr=chaine;

int main(){
	
    char chaine[30000]={0};
    printf("Write your brainfuck program then press ENTER :\n");
    fgets(chaine, sizeof(chaine), stdin);
    clean(chaine, stdin);
    brainfuck_interpreter(chaine);	

return 0;
}

void brainfuck_interpreter(char * instruction){
	
  for (;*instruction != '\0'; ++instruction)
  {
    switch (*instruction)
    {
      case '>': ++ptr; break;
      case '<': --ptr; break;
      case '+': ++*ptr; break;
      case '-': --*ptr; break;
      case '.': putchar(*ptr); break;
      case ',': *ptr = getchar(); break;
      case '[':
        if (!*ptr)
        {
          int loop_cnt = 1;
          while (loop_cnt)
          {
            ++instruction;				//jump to next instruction
            if (*instruction == ']')			//decrement loop, if loop=1 close the loop
              --loop_cnt;
            else if (*instruction == '[')		//add a loop in our loop
              ++loop_cnt;
          }
        }
        break;
      case ']':
        if (*ptr)
        {
          int loop_cnt = 1;
          while (loop_cnt)
          {
            --instruction;
            if (*instruction == '[')
              --loop_cnt;
            else if (*instruction == ']')
              ++loop_cnt;
          }
        }
        break;
      default:
        printf("Invalid character '%c'\n", *instruction);
    }
  }
}


void clean(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
    {
        *p = 0;
    }
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}

