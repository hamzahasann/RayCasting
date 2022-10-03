class Map{
	vector<vector<int>>grid;
	friend class Player;
public:
	Map(){
		grid.resize(MAPHEIGHT,vector<int>(MAPHEIGHT));
		ifstream in("map.txt");
		string line;
		int i=0;
		while(getline(in,line)){
			int j=0;
			for(auto c:line){
				if(c=='1' || c=='0'){
					grid[i][j]=c-'0';
					j++;
				}
			}i++;
		}
	}void draw(sf::RenderWindow &window){
		for(int i=0;i<MAPHEIGHT;i++){
			for(int j=0;j<MAPHEIGHT;j++){
				if(grid[i][j]==1){
					sf::RectangleShape rect({TILESIZE,TILESIZE});
					rect.setPosition(j*TILESIZE,i*TILESIZE);
					rect.setFillColor({255,255,255});
					window.draw(rect);
				}
			}
		}
	}
};