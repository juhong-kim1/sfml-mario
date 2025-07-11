#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1280, 720, "Super Mario Bros");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}