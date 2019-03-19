//
//  main.cpp
//  addition
//
//  Created by chengdan on 2018/11/30.
//  Copyright © 2018 chengdan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

FILE *fp;

int **Sub_Sum(int *good, int *value, int num, int weight);

int max_num(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int main(int argc, const char * argv[]) {
    fp = fopen("addition.txt", "r");
    int num;
    int weight;
    fscanf(fp, "%d", &num);
    fscanf(fp, "%d", &weight);
    int good[num];
    int value[num];
    for(int i = 0; i < num; i++)
    {
        fscanf(fp, "%d", &good[i]);
        fscanf(fp, "%d", &value[i]);
    }
    int record[num];
    int counter = 0;
    int i = num;
    int j = weight;

    int **bag = Sub_Sum(good, value, num, weight);
    
    while(1)
    {
        if(i == 0)
            break;
        else if(j == 0)
            break;
        else
        {
            int t = j-good[i-1];
            if(bag[i][j] == (bag[i-1][t] + value[i-1]))
            {
                record[counter] = i;
                counter++;
                j = t;
            }
            i--;
        }
    }
    
    for(int i = counter - 1; i >= 0; i--)
        cout << record[i] << " ";
    cout << endl;
    
    cout << bag[num][weight] << endl;
    return 0;
}

int **Sub_Sum(int *good, int *value, int num, int weight){
    int **M = new int*[num+1];
    for(int i = 0; i <= num; i++)
        M[i] = new int[weight+1];
    for(int i = 0; i <= weight; i++)
        M[0][i] = 0;
    for(int i = 1; i <= num; i++)
    {
        for(int j = 0; j <= weight; j++)
        {
            if(j < good[i-1])
                M[i][j] = M[i-1][j];
            else
                M[i][j] = max_num(M[i-1][j], (value[i-1] + M[i-1][j-good[i-1]]));
        }
    }
    return M;
}
