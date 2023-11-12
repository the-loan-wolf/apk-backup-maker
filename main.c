#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeCharsFromStart(char *string,int noOfChar);
void removeLastNineChars(char *string);

int main(void)

{
  size_t strLength;
  char firstResult [150];
  char secondResult [150];
  char thirdResult [150];
  char firstBuffer [150];
  char secondBuffer [150];
  char thirdBuffer [150];
  int count;
  FILE *firstPipe;
  FILE *secondPipe;
  FILE *thirdPipe;

  //finding total amount of installed app
  firstPipe = popen("pm list packages -3 | wc -l","r");
  printf("total app which will get backed up: ");
  while (fgets(firstBuffer,100,firstPipe) != NULL) {
    printf("\x1b[31m%s\n\x1b[0m",firstBuffer);
  }

  //we will get installed apps package names
  secondPipe = popen("pm list packages -3 | sed \'s/package://\'","r");
  if (secondPipe == NULL) {
    perror("popen");
  }
  else {
    count = 1;
    while (fgets(secondBuffer,150,secondPipe) != NULL) {
      printf("\x1b[32mApk [\x1b[34m%i\x1b[32m] is coping...\n",count);
      count += 1;
      strcpy(firstResult,"pm path ");
      strcat(firstResult,secondBuffer);
      strLength = strlen(firstResult);
      if (strLength > 0 && firstResult[strLength - 1] == '\n') {
        firstResult[strLength - 1] = '\0';  // Replace '\n' with '\0'
      }
      strcat(firstResult," | sed \'s/package://\'");
      strcat(firstResult," | head -n 1");
      thirdPipe = popen(firstResult,"r");
      while (fgets(thirdBuffer,150,thirdPipe) != NULL) {
        strcpy(secondResult,"cp -r ");
        strcat(secondResult,thirdBuffer);
        removeLastNineChars(secondResult);
        strcat(secondResult," .");
        system(secondResult);

        //rename folder
        removeCharsFromStart(thirdBuffer,37);
        removeLastNineChars(thirdBuffer);
        strcpy(thirdResult,"mv ");
        strcat(thirdResult,thirdBuffer);
        strcat(thirdResult," ");
        strcat(thirdResult,secondBuffer);
        system(thirdResult);
        system("find . -type d -name \'lib\' -exec rm -r {} +");
        system("find . -type d -name \'oat\' -exec rm -r {} +");
        system("find . -name \'base.digests\' -exec rm -r {} +");
        system("find . -name \'base.dm\' -exec rm -r {} +");
      }
    }
    // Close the pipe
    if (pclose(secondPipe) == -1) {
            perror("pclose");
            return -1;
    }
  }
  return 0;
}

void removeCharsFromStart(char *string,int noOfChar)
{
  size_t len;
  
  len = strlen(string);
  if (noOfChar < len) {
    memmove(string,string + noOfChar,(len - noOfChar) + 1);
  }
  else {
    *string = '\0';
  }
}

void removeLastNineChars(char *string)
{
  size_t len;
  
  len = strlen(string);
  if (len < 9) {
    printf("Error: String is too short to remove 8 characters\n");
  }
  else {
    string[len - 9] = '\0';
  }
}
