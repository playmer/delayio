#include <stdio.h>
#include "joshtime.h"

int main(void)
{
  char *strExample = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
                     " Ut et fermentum mi, et mattis libero. Nam egestas nibh "
                     "dolor, id blandit odio imperdiet nec. In sit amet augue "
                     "ut dolor pellentesque mattis at et augue. Quisque eleife"
                     "nd quam lacus, in scelerisque purus imperdiet ut. Mauris"
                     " consectetur accumsan neque eget porttitor. Donec et neq"
                     "ue orci. Fusce vel adipiscing enim, non placerat libero."
                     " Pellentesque aliquet libero magna, vitae ornare felis a"
                     "uctor at. Duis tempus bibendum purus, id eleifend nunc b";

  unsigned int delay = 10000;

  delayPrint(delay, strExample);

  delayPrint(delay, "\nThis is going to test how well %son of this works here I will insert numbers: %i, %i, %i", "the variatic functi", 100, 10000, 20000);

  return 0;
}