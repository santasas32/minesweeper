#include <stdbool.h>
#include "workWithUser.h"
#include <stdio.h>

int checkErrors(int errorCode)
{   if (errorCode == 1 || errorCode == 2)
        while(getchar() != '\n');
    showErrors(errorCode);

    return 0;
}