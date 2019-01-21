//
//  cfuncs.c
//  myMathLib
//
//  Created by Samuel Wu on 1/13/19.
//  Copyright © 2019 Samuel Wu. All rights reserved.
//

#include "cfuncs.h"
#include "nngreqrep.h"

int reqNode(char* name, char * value);

float cmul(float a, float b)
{
//    reqNode("node0","SA");
    return 10*a*b;
}

char * getDate()
{
    return node1("tcp://10.10.10.23:8899");
//    return "1/2/2019";
}


