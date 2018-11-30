#include <iostream>
#include "TestCEGUI.h"

int main()
{
    auto * app = new TestCEGUI(800,600,"Test Texture2DArray");
    app->Run();
    return 0;
}