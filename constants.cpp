const int WIDTH=800;
const int HEIGHT=800;
const int INPUTLAG=250;
const int FRAMERATE=30;
const int PLAYERSIZE=20;
const int MAPWIDTH=20;
const int MAPHEIGHT=20;
const int TILESIZE=40;
const int PLAYERFOV=20;
const int MAXDEPTH=1000;
const double PI=3.14159265;

pair<int,int>convert(pair<int,int>p){
    return {WIDTH/2+p.first,HEIGHT/2-p.second};
}
bool collide(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){
    if(x1<x2+w2 && x1+w1>x2 && y1<y2+h2 && y1+h1>y2){
        return true;
    }return false;
}
bool inside(int x,int y){
    if(y<0 || y>=MAPHEIGHT || x<0 || x>=MAPWIDTH){
        return 0;
    }return 1;
}
double dist(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}