#ifndef FUNCTION_H
#define FUNCTION_H
#include<vector>
#include<QString>
#include<iostream>
#include<ctime>
using namespace std;
extern  int HEIGHT, WIDTH;
extern vector<int> path;
extern clock_t t1, t2;
extern int **visited;
extern int stop;
void initialize();
bool isNew(int x, int y);
int getNumberOfDoor(int x, int y,int dir[8]);
int next(int x, int y , int nowN[8],int n);
void setN(int n);
void setV(int x, int y, int temp);
bool jump(int x, int y,int count);
void output();
vector<int> getPath();
QString getSPath();
#endif // FUNCTION_H
