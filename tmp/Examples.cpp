//  Created by Victor Axelsson on 2017-04-03.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#include <stdio.h>
#include <string>

using namespace std;

static int fabric_examples[][2] = {
    {10, 20},
    {22, 20},
    {100, 100},
    {120, 100},
    {50, 20},
    {44, 101},
    {5, 5},
    {100, 68},
    {22, 20},
    {100, 100},
    {20, 20},
    {22, 66},
    {10, 20}
};


static int fabric_examples_widths[] = {33,46,25,46,76,55,93,35,23,12,101,89,16,103,23,15,31,78,107,51,59,89,25,70,11,34};
static int fabric_examples_heights[] = {46,25,46,76,55,93,35,23,12,101,89,16,103,23,15,31,78,107,51,59,89,25,70,11,34,33};
static string colors[] = {"red", "green", "silver", "blue", "yellow", "brown", "gray", "white"};