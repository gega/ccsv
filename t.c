// gcc -Wall -o t t.c
#include <stdio.h>
#include <stdlib.h>
#include "ccsv.h"

static const char *csv[]=
{
  "aaa;bbb;ccc",
  "aaa,   \"bbb\" , ccc",
  "   aaa   ,   \"b\"\",,,,b\", ccc  ",
  "aaa,b\"bb,ccc",
  NULL
};

static const char *fields[]=
{
  "aaa",
  "bbb",
  "ccc",
  "aaa",
  "bbb",
  "ccc",
  "aaa",
  "b\"\",,,,b",
  "ccc",
  "aaa",
  "b\"bb",
  "ccc",
  NULL
};


int main(void)
{
  struct ccsv c;
  char *f,typ;
  int i,j,r;
  
  for(j=r=0;csv[j]!=NULL;j++)
  {
    char *h=strdup(csv[j]);
    ccsv_init_ex(&c,h,(j==0?';':','));
    for(i=0;NULL!=(f=ccsv_nextfield(&c,&typ));i++)
    {
      printf("csv %d: #%d %s %s '%s'\n",j,i,(typ=='"'?"QUOTED":"NORMAL"),(strcmp(fields[r++],f)==0?"OK":"FAIL"),f);
    }
    free(h);
  }
  
  return(0);
}
