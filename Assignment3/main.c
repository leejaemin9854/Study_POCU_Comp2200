#include <assert.h>
#include <string.h>
#include "document_analyzer.h"




int main(void)
{
    load_document("test.txt");
    Test_Show_Memory();
    
    printf("Done");

    return 0;
}


