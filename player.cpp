#include<bits/stdc++.h>
using namespace std;

class Player{
public:
	int x,y,theta,linVel,angVel;
	Map* map;
	Player(int _x,int _y,int _theta,int _linVel,int _angVel,Map* _map){
		x=_x;
		y=_y;
		theta=_theta;
		linVel=_linVel;
		angVel=_angVel;
		map=_map;
	}void moveF(){
		int tx=x,ty=y;
		x=x+round(linVel*cos(theta*PI/180));
		y=y-round(linVel*sin(theta*PI/180));
		if(checkCollision(x,y)){
			// x=tx;
			if(!checkCollision(tx,y)){
				x=tx;
			}else if(!checkCollision(x,ty)){
				y=ty;
			}else{
				x=tx;y=ty;
			}
		}
	}void moveB(){
		int tx=x,ty=y;
		x=x-round(linVel*cos(theta*PI/180));
		y=y+round(linVel*sin(theta*PI/180));
		if(checkCollision(x,y)){
			// x=tx;
			if(!checkCollision(tx,y)){
				x=tx;
			}else if(!checkCollision(x,ty)){
				y=ty;
			}else{
				x=tx;y=ty;
			}
		}
	}
	void turnCW(){
		theta=(theta-angVel%360+360)%360;
	}void turnACW(){
		theta=(theta+angVel)%360;
	}void draw(sf::RenderWindow &window){
		sf::CircleShape body(PLAYERSIZE);
		sf::RectangleShape dir({PLAYERSIZE,3});
		body.setPosition(x,y);
		body.setFillColor(sf::Color(255,255,255));
		window.draw(body);
		dir.setFillColor(sf::Color(255,0,0));
		dir.setPosition(x+PLAYERSIZE,y+PLAYERSIZE);
		dir.setRotation(-theta);
		window.draw(dir);
	}bool checkCollision(int x,int y){
		for(int i=0;i<MAPHEIGHT;i++){
			for(int j=0;j<MAPWIDTH;j++){
				if(map->grid[i][j]==0)continue;
				if(collide(x,y,2*PLAYERSIZE,2*PLAYERSIZE,j*TILESIZE,i*TILESIZE,TILESIZE,TILESIZE)){
					return true;
				}
			}
		}return false;
	}void castRays(sf::RenderWindow &window,sf::RenderWindow &window2){
		double thetaStep=8*2*PLAYERFOV*1.0/WIDTH;
		
		// createRay(theta,window);
		
		for(int i=0;i<100;i++){
			pair<double,int>aa=createRay(theta+PLAYERFOV-thetaStep*i,window);
			if(aa.second==0)continue;
			double dt=aa.first;
			double ang=abs(-PLAYERFOV+thetaStep*i);
			dt=dt*cos(ang*PI/180);
			sf::RectangleShape rect({8,round(50000/(dt))});
			rect.setPosition(8*i,(800-50000/(dt))/2);
			double fact=100000/dt/dt;
			cout<<fact<<endl;
			rect.setFillColor(sf::Color(min(200.0,round(255*fact/25)),min(200.0,round(255*fact/25)),min(200.0,round(255*fact/25))));
			window2.draw(rect);
		}
	}pair<double,int> createRay(double theta,sf::RenderWindow &window){
		while(theta<0)theta+=360;
		while(theta>=360)theta-=360;
		double m=tan(theta*PI/180);
		double dirX=0;
		if(theta<=90 || theta>=270)dirX=1;
		else dirX=-1;
		double tx=x+PLAYERSIZE,ty=y+PLAYERSIZE;
	
		ty=ty+m*(tx/TILESIZE-int(tx/TILESIZE))*TILESIZE;
		tx=tx-(tx/TILESIZE-int(tx/TILESIZE))*TILESIZE;
		if(dirX==-1){
			tx+=TILESIZE;
			ty-=m*TILESIZE;
		}
		// if(dirX==-1){
		// 	tx+=1;
		// 	ty-=m;
		// }
		double d1=1e9,d2=1e9,x1,y1,x2,y2;
		for(tx=tx+dirX*TILESIZE,ty=ty-dirX*m*TILESIZE;;tx=tx+dirX*TILESIZE,ty=ty-dirX*(m*TILESIZE)){
			// cout<<tx<<" "<<ty<<" "<<y+PLAYERSIZE<<endl;
			if(!inside((tx+dirX)/TILESIZE,ty/TILESIZE))break;
			if(map->grid[ty/TILESIZE][(tx+dirX)/TILESIZE]==1){
				// sf::Vertex line[]={sf::Vertex({x+PLAYERSIZE,y+PLAYERSIZE}),sf::Vertex({tx,ty})};
				// window.draw(line,2,sf::Lines);
				cout<<tx<<" "<<ty<<endl;
				x1=tx;y1=ty;
				d1=dist(x+PLAYERSIZE,y+PLAYERSIZE,x1,y1);
				break;
			}
		}

		m=1/m;
		tx=x+PLAYERSIZE;ty=y+PLAYERSIZE;
		int dirY=0;
		if(theta>=0 && theta<=180)dirY=-1;
		else dirY=1;
		tx=tx+m*(ty/TILESIZE-int(ty/TILESIZE))*TILESIZE;
		ty=ty-(ty/TILESIZE-int(ty/TILESIZE))*TILESIZE;
		if(dirY==-1){
			ty+=TILESIZE;
			tx-=m*TILESIZE;
		}
		for(tx=tx-dirY*m*TILESIZE,ty=ty+dirY*TILESIZE;;tx=tx-dirY*m*TILESIZE,ty=ty+dirY*TILESIZE){
			if(!inside(tx/TILESIZE,(ty+dirY)/TILESIZE))break;
			if(map->grid[(ty+dirY)/TILESIZE][tx/TILESIZE]==1){
				// sf::Vertex line[]={sf::Vertex({x+PLAYERSIZE,y+PLAYERSIZE}),sf::Vertex({tx,ty})};
				// window.draw(line,2,sf::Lines);
				x2=tx;y2=ty;
				// if(dirY==-1){
				// 	x2-=TILESIZE*m;
				// 	y2+=TILESIZE;
				// }
				d2=dist(x+PLAYERSIZE,y+PLAYERSIZE,x2,y2);
				break;
			}	
		}if(d1<d2){
			tx=x1;ty=y1;
		}else{
			tx=x2;ty=y2;
		}
		double d3=MAXDEPTH;
		if(min({d1,d2,d3})==d3){
			m=1/m;
			double k=d3/(sqrt(1+m*m));
			tx=x+PLAYERSIZE+dirX*k;
			ty=y+PLAYERSIZE-dirX*k*m;
		}
		sf::Vertex line[]={sf::Vertex({{x+PLAYERSIZE,y+PLAYERSIZE},sf::Color(255,0,0)}),sf::Vertex({tx,ty})};
		window.draw(line,2,sf::Lines);
		// cout<<min(d1,d2)<<endl;
		return {min({d1,d2,d3}),(d1<d3 || d2<d3)};
	}
};