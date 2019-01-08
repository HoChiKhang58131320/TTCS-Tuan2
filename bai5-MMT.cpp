#include<iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <cursor.h>
using namespace std;

int SPEED=210; //cho toc do mac dinh 
#define SNAKE	'*' //hinh dang con ran
#define FOOD	'o' //hinh dang thuc an

//khai bao mau sac
#define BLACK 0
#define GRAY 7
#define DARK_GRAY 8
#define BLUE 9
#define GREEN 10
#define RED 12
#define YELLOW 14
#define WHITE 15

struct Point //khai bao toa do x, y
{
	int x, y;
};

struct Snake 
{
	Point Body[100];
	int len;
};
void welcome ()
{
	cout <<"\n\n     MINI GAME: \n\n";
	cout << "         .*****.   ***       **         ***         **   '*'   *.*.*.*.*.   " << endl;
	cout << "        **'    '*  **'*      **        *' '*        **  '*'     **''''''*   " << endl;
	cout << "        **      '  ** *'     **       *'   '*       ** '*'      **          " << endl;
	cout << "         **        **  '*    **      '*     *'      **'*'       **.....     " << endl;
	cout << "           '**.    **   *.   **     .*'.....'*.     ***'        **.*.*.     " << endl;
	cout << "              '*   **    *'  **     *.*.*.*.*.*     **'*'       **          " << endl;
	cout << "        .      **  **     '* **    *'         '*    ** '*'      **          " << endl;
	cout << "        **.   .**  **      *'**   '*           *'   **  '*'     **......*   " << endl;
	cout << "         '*****'   **       ***  '*'           '*'  **   '*'.  *'*'*'*'*'   " << endl;
	cout << "\n                                                     Coder by Ho Chi Khang"<<endl;
	system ("pause");
}

char map[27][84];
char backm[27][84]=
{
"**********************************************************************************",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"*                                                                                *",
"**********************************************************************************",	
};

void GotoXY(int x, int y) //dua con tro toi vi tri x, y
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void TextColor(WORD color) //ham xay dung mau chu
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
int WriteXY(short x, short y, WORD color, const char *format, ...)
{
	GotoXY(x, y);
	TextColor(color);
	
	va_list arg;
	int done;
	
	va_start(arg, format); // lay danh sach doi so dua theo format
	done = vfprintf(stdout, format, arg); // xuat cac doi so theo format
	va_end(arg);
	
	return done;
}
void kichthuoc(int Width, int Height) //dat kich thuoc man hinh console
{
	COORD coord;
	coord.X = Width;
	coord.Y = Height;

	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);            // dat kich thuoc bo dem
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // dat kich thuoc man hinh window
}
void writec(char c, int n)
{
	for (int i = 0; i < n; i++)
		cout<<c;
}

void DrawBox(int x1, int y1, int x2, int y2, int color) //ve khuon vien
{
	TextColor(color);
	GotoXY(x1, y1);
	writec(219, x2 - x1 + 1);
	for (int i = 1; i < y2 - y1; i++)
	{
		GotoXY(x1, y1 + i);
		writec(219, 1);
		GotoXY(x2, y1 + i);
		writec(219, 1);
	}
	GotoXY(x1, y2);
	writec(219, x2 - x1 + 1);
}
void Init(int CWidth, int CHeight, Snake &snake, int &Diem, int &Level) //khoi tao gia tri cac bien
{
	system("cls");
	for(int i=0; i<27; i++)
		for(int j=0; j<84; j++)
		{
			map[i][j]=backm[i][j];
			if(map[i][j]=='8')
				WriteXY(j,i,WHITE,"%c",219);
		}
	snake.Body[0]={1,1};
	snake.len=1;
	Level=0;
	Diem=0;
	kichthuoc(CWidth+2, CHeight+3);
	DrawBox(0,0,CWidth+1,CHeight+1,GRAY); //ve tuong chan ko cho ran xuyen qua
	TextColor(GREEN);
	GotoXY(1,1);
	printf("%c",SNAKE);
}
void tocdo(int &Speed) //lua chon toc do cho ran san moi
{
	system("cls");
	char title[]="CHON MUC DO CHOI",
		tut[]="Huong dan: Nhan phim mui ten < hoac > de dieu chinh. Nhan ESC de ve Menu.";
	int key;
	WriteXY((80 - strlen(title)) / 2, 1, GREEN, title);
	WriteXY((80 - strlen(tut)) / 2, 10, RED, tut);
	WriteXY(15,5,YELLOW,"Muc: [%40s]: %3d"," ",(210-SPEED)/10);//21
	for(int i=0; i<(210-SPEED)/(200/40); i++)
		WriteXY(21+i,5,YELLOW,"%c",219);//21
	for(int i=(210-SPEED)/(200/40); i<40; i++)
		WriteXY(21+i,5,YELLOW,"%c",32);//21
	do{
		key=getch();
		if(key==224)
			key=getch();	
		switch(key)
		{
			case 77: //sang phai
					SPEED-=10;
					if(SPEED<10)
						SPEED=210;
					WriteXY(64,5,YELLOW,"%3d",(210-SPEED)/10);
					for(int i=0; i<(210-SPEED)/(200/40); i++)
						WriteXY(21+i,5,YELLOW,"%c",219);//21
					for(int i=(210-SPEED)/(200/40); i<40; i++)
						WriteXY(21+i,5,YELLOW,"%c",32);//21
				break;
			case 75://sang trai
					SPEED+=10;
					if(SPEED>210)
						SPEED=10;
					WriteXY(64,5,YELLOW,"%3d",(210-SPEED)/10);
					for(int i=0; i<(210-SPEED)/(200/40); i++)
						WriteXY(21+i,5,YELLOW,"%c",219);//21
					for(int i=(210-SPEED)/(200/40); i<40; i++)
						WriteXY(21+i,5,YELLOW,"%c",32);//21
				break;
		}
	}while(key!=27);
	system("pause");
}


int Menu(char *list[], int n, char *title) //hien thi menu 
{
	int select = 0;
	int	history = 0, 
		dPos = 5;
	

	system("cls"); //xoa man hinh

	// Hien thi tieu de
	WriteXY((80 - strlen(title)) / 2, 1, GREEN, title);
	
	DrawBox(2, 3, 78, n+6, RED);


	for (int i = 0; i < n; i++)
	{
		// In menu
		WriteXY(6, i + dPos, WHITE, "%3d. %s", i + 1, list[i]);
	}

	//To sang lua chon mac dinh
	WriteXY(5, select + dPos, YELLOW, "%c%3d. %s", 175, select + 1, list[select]);
	
	//In text huong dan
	WriteXY(2, n+8, BLUE, "HUONG DAN: Nhan phim mui ten len ^ , xuong v hoac phim so 1 2 3... de chon thao tac, sau do nnhan phim enter de ket thuc thao tac chon.\n");
	WriteXY(2, n+12, GRAY, "HUONG DAN CHOI: Nhan phim mui ten len ^ , xuong v , trai < hoac phai > de di    chuyen con ran va an moi. De tam dung nhan space, de thoat nhan esc.");
	char key = 0;
	do
	{
		key = getch();
		if(key==224)
			key=getch();
			
		if (key == 72) select--;
		if (key == 80) select++;
		
		if(key>'0' && key <='9')
			select=key-'0'-1;
		
		if (select == -1)
			select = n - 1;
		else if (select >= n)
			select = 0;
		
		// Xoa lua chon cu
		WriteXY(5, history + dPos, WHITE, " %3d. %s", history + 1, list[history]);
		
		//To sang lua chon moi
		WriteXY(5, select + dPos, YELLOW, "%c%3d. %s", 175, select + 1, list[select]);
		
		history = select;
	} while (key != 13); // Dung khi nhan phim enter
	
	return select+1;
}


//Bat dau choi game
void datmoi(int CWidth, int CHeight, Point &moi) //dat thuc an 
{
	srand(time (0));
	moi.x=rand()%CWidth+1;
	moi.y=rand()%CHeight+1;
}

void Play(int CWidth, int CHeight, Snake &snake, int &Diem, int &Level) //ham de choi game
{
	const int dx[4]={1,0,-1,0}; 
	const int dy[4]={0,-1,0,1};
	int temp=0, dir=0;
	int key; //cai phim choi game
	
	//dat moi
	Point moi;
	datmoi(CWidth, CHeight, moi);
	while(map[moi.y][moi.x]!=' ')
		datmoi(CWidth, CHeight, moi);
	WriteXY(moi.x, moi.y,RED,"%c",FOOD); //mau cua thuc an
	//to mau thanh taskbar
	WriteXY(65,27,BLUE," Diem: %5d ",Diem);
	WriteXY(50,27,BLUE," Level: %2d ",Level);
	WriteXY(1,27,RED,"Menu chinh: Esc  Tam dung: Space    Speed:%3d/20",(210-SPEED)/10);
	
	key=getch();
	do
	{
		//An dc moi:
		if(snake.Body[0].x==moi.x && snake.Body[0].y==moi.y)
		{
			Diem++;
			snake.len++;
			if(Diem%5==0)
			{
				Level++;
				if(SPEED>30)
					SPEED-=20;
			}
			WriteXY(65,27,GREEN," Diem: %5d ",Diem);
			WriteXY(50,27,GREEN," Level: %5d ",Level);
			WriteXY(1,27,GREEN,"Menu chinh: Esc  Tam dung: Space    Toc do:%3d/20",(210-SPEED)/10);
			//dat moi
			datmoi(CWidth, CHeight, moi);
			while(map[moi.y][moi.x]!=' ')
				datmoi(CWidth, CHeight, moi);
			WriteXY(moi.x, moi.y,GREEN,"%c",FOOD);
		}
	
		//Nhan phim dieu khien
		if(kbhit())
		{
			key=getch();
			if(key==224)
				key=getch();
				
			switch(key)
			{
				case 77: //sang phai
					if(dir!=2)
						dir=0;
					break;
				case 72://len tren
					if(dir!=3)
						dir=1;
					break;
				case 75://sang trai
					if(dir!=0)
						dir=2;
					break;
				case 80://xuong duoi
					if(dir!=1)
						dir=3;
					break;
				case 32:
					system("pause");
					break;
			}
		}
		
		for(int i=snake.len; i>0; i--)
		{
			snake.Body[i]=snake.Body[i-1];	
		}
		
		//xac dinh toa do diem dau moi theo huong di chuyen
		snake.Body[0].x=snake.Body[0].x+dx[dir];
		snake.Body[0].y=snake.Body[0].y+dy[dir];
		
		//xoa diem cuoi dung
		WriteXY(snake.Body[(snake.len)].x,snake.Body[(snake.len)].y,GREEN," ");
		map[snake.Body[(snake.len)].y][snake.Body[(snake.len)].x]=' ';
		
		//ve diem dau
		WriteXY(snake.Body[0].x,snake.Body[0].y,RED,"%c",SNAKE);
		if(map[snake.Body[0].y][snake.Body[0].x]!=' '&&map[snake.Body[0].y][snake.Body[0].x]!='2')
			{
				WriteXY(snake.Body[0].x,snake.Body[0].y,RED,"X");
				WriteXY(25,12,RED,"Ban da thua. Bam Esc de ra menu chinh!");
				while(getch()!=27);
				return;
			}
		map[snake.Body[0].y][snake.Body[0].x]='1';
		//delay
		Sleep(SPEED);
	}while(key!=27);
}

int main()
{
	welcome();
	ShowCur (false);   // an con tro theo con ran
	
	char *title = "TRO CHOI RAN SAN MOI BANG CONSOLE!";
	char *list[3] = 
	{
		"Bat dau choi",				//1			
		"Chon level",		//2
		"Thoat!",	//3
	};
	int CWidth=80, CHeight=25,
		Diem=0, Level;
	Snake snake;
	
	kichthuoc(CWidth+2, CHeight+3);
	kichthuoc(CWidth+2, CHeight+3);
	do{
		int k=Menu(list,3,title); //bien lua chon
		switch (k)
		{
			case 1:
				Init(CWidth, CHeight, snake, Diem, Level);
				Play(CWidth, CHeight, snake, Diem, Level);
				break;
			case 2:
				tocdo(SPEED);
				break;
			case 3:
				exit(0);
				break;
		}
	}while (1);
	return 0;
}
