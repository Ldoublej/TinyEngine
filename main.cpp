#include <iostream>
#include "TestTexture2DArray.h"

int main()
{
    TestTexture2DArray * app = new TestTexture2DArray(800,600,"Hello");
    app->Run();
    return 0;
}