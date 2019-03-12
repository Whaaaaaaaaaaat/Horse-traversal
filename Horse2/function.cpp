#include<function.h>
int HEIGHT = 10, WIDTH = 9;
int stop = HEIGHT * WIDTH;
clock_t t1, t2;
int **visited=new int*[HEIGHT];

vector<int> path;
const int fx[8] = { 2,2,1,1,-1,-1,-2,-2 };
const int fy[8] = { 1,-1,2,-2,2,-2,1,-1 };
const int legx[8] = { 1,1,0,0,0,0,-1,-1 };
const int legy[8] = { 0,0,1,-1,1,-1,0,0, };
vector<int> getPath()
{
    return path;
}
//初始化visited;
void initialize()
{
    path.clear();
    stop=HEIGHT * WIDTH;
    for(int i=0;i<HEIGHT;i++)
    {
        visited[i]=new int[WIDTH];
    }
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            visited[i][j] = 0;
        }
    }
}
//判断该位置是否可以踩
bool isNew(int x, int y)
{
    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && (visited[y][x] == 0||visited[y][x]==-1))
        return true;
    else
        return false;
}
int getNumberOfDoor(int x, int y,int dir[8])
{
    int n=0;
    for (int i = 0; i < 8; i++)
    {
        bool b1=x + legx[i]>=0&&x + legx[i]<WIDTH&&y + legy[i]>=0&&y + legy[i]<HEIGHT;
        if(b1)
        if (visited[y + legy[i]][x + legx[i]] >=0&&isNew(x + fx[i], y + fy[i]))
        {
            dir[n] = i;
            n++;
        }
    }
    return n;
}
int next(int x, int y , int nowN[8],int n)
{
    int nextN[8];
    int min = 9;
    int dir = -1;
    for (int i = 0; i < n; i++)
    {
        if(nowN[i] < 0)
            continue;
        int nn = getNumberOfDoor(x + fx[nowN[i]], y + fy[nowN[i]], nextN);
        if (nn < min)
        {
            min = nn;
            dir = nowN[i];
        }
    }
    return dir;
}
void setN(int n)
{
    stop -= n;
}
void setV(int x, int y, int temp)
{
    visited[y][x] = temp;
}
bool jump(int x, int y,int count)
{
    t2 = clock();
    if ((t2 - t1) / CLOCKS_PER_SEC > 3  )
        return false;
    visited[y][x] = count;
    path.push_back(x);
    path.push_back(y);
    if (count >= stop)
        return true;
    int nowN[8], nextN[8];
    int n = getNumberOfDoor(x, y, nowN);
    for (int i = 0; i < n; i++)
    {
        int dir = next(x, y, nowN, n);
        if (jump(x + fx[dir], y + fy[dir], count + 1))
            return true;
        else
            nowN[dir] = -1;
    }
    visited[y][x] = 0;
    path.pop_back();
    path.pop_back();
    return false;
}
void output()
{

    for (int i = 0; i < stop * 2; i += 2)
    {
        if (i != 0 && i % 10 == 0)
            cout << endl;
        if (i == 0)
            cout << "  (" << path[i] << "," << path[i + 1] << ")";
        else
            cout << "->" << "(" << path[i] << "," << path[i + 1] << ")";
    }
    cout << endl;
}

QString getSPath()
{
    QString spath;
    for (int i = 0; i < stop * 2; i+=2)
    {
        if (i != 0 && i % 10 == 0)
            spath+="\n";
        if (i == 0)
            spath=spath+"  ("+QString::number(path[i])+","+ QString::number(path[i+1])+ ")";
        else
             spath=spath+"->"+"("+QString::number(path[i])+","+ QString::number(path[i+1])+ ")";
    }
    return spath;
}
