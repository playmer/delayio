/****************************************************************************** 
filename    joshtime.c
author      Joshua T. Fisher 
email       j.fisher@digipen.edu
  
Brief Description: 
  This file contains functions for dealing with printing strings out char by
  char. It's only public function (delayPrint) will take in a string with no 
  newlines, and print it out character by character, with a specified delay in 
  between in microseconds. It will also dynamically insert newlines as they're 
  needed.
    - It will return 0 if operations completed successfully.
    - It will return 1 if malloc failed.
    - It will return 2 if it failed to place newlines "correctly".
  
******************************************************************************/
#include <stdio.h>  
#include <string.h> /* strcpy, strlen */
#include <stdlib.h> /* calloc, free */
#include <unistd.h> /* usleep */
#include <stdarg.h> /* va_list, va_start, va_end*/

#include "delayio.h" /* LINE_LENGTH */

static int insertNewlines(char *string)
{
  /* Used to check the length of the string while iterating. */
  int length = 1; 
  /* Used to make sure we don't iterate behind our string. */
  int backwardslength = 1;

  while(*string)
  {
    if (length != LINE_LENGTH)
    {
      ++length;
      ++backwardslength;
      ++string;
      
    }
    else
    {     
      if (*string != ' ')
      {
        --string;
        --backwardslength;

        if (backwardslength <= 0)
        {
          return 2;
        }
      }
      else
      {
        *string = '\n';
        length = 0;
      }
    }
  }

  return 0;
}

/*
static int vasprintf(char **strPtr, char *format, va_list argv) 
{
  int needed = vsnprintf((*strPtr = NULL), 0, format, argv);

  if((needed < 0) || ((*strPtr = malloc(1 + needed)) == NULL))
  {
    return -1;
  }

  return vsprintf(*strPtr, format, argv);
}
*/

int delayPrint(int delay, char *format, ...)
{
  va_list argv;
  int newlineReturn = 0;
  /* Create a buffer for our newlined string. */
  char *stringBuffer;
  char *start;

  va_start(argv, format);

  /* Create a string with newlines. If malloc failed, return 1. */
  newlineReturn = vasprintf(&stringBuffer, format, argv);
  start = stringBuffer;

  if (newlineReturn < 0)
  {
    return 1;
  }

  newlineReturn = insertNewlines(stringBuffer);

  while (*start)
  {
    /* Put a character to the buffer. */
    putchar(*start);
    
    /* Flush the stdout buffer so the character prints to the screen. */
    fflush(stdout);
    
    /* Sleep for specified delay*/
    usleep(delay);

    /* Iterate through our string. */
    ++start;
  }

  /* Free our buffer. */
  free(stringBuffer);

  va_end(argv);

  return newlineReturn;
}
