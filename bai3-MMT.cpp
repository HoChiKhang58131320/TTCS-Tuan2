#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

using namespace std;
struct bode //khai bao cau truc luu tru cac chuoi cau hoi, tra loi va dap an
{
	string cauhoi, traloi;
	string a, b, c, d;
};
int n;

void doc(ifstream &f, bode DSBD[]) //doc danh sach bo de tu file
{
	f>>n;
	string tam;
	getline(f, tam);
	for (int i=0; i<n; i++)
	{
		getline(f, DSBD[i].cauhoi);
		getline(f, DSBD[i].a);
		getline(f, DSBD[i].b);
		getline(f, DSBD[i].c);
		getline(f, DSBD[i].d);
		getline(f, DSBD[i].traloi);
	}
}

bool kiemTra(bode &p) //ham kiem tra dap an
{
	int diem=0;
	string dapan;
	cout << "Moi ban nhap dap an: ";
	cin>>dapan;
	if(dapan==p.traloi) //xet truong hop dap an nhap vao co dung voi cau tra loi cua bo de khong
		return true;
	else
		return false;
}
void xuat(bode DSBD[]) //in ra man hinh cac cau hoi va hien diem nguoi choi dat duoc
{
	int diem=0;
	for(int i=0;i<n;i++)
	{
		cout<<DSBD[i].cauhoi<<endl;
		cout<<DSBD[i].a<<endl;
		cout<<DSBD[i].b<<endl;
		cout<<DSBD[i].c<<endl;
		cout<<DSBD[i].d<<endl;
		if (kiemTra(DSBD[i])==true)
		{
			cout << "Dung roi"<<endl;
			diem++;
		}
		else 
		{
			cout <<"Sai roi"<<endl;
			cout <<"Dap an dung la "<<DSBD[i].traloi<<endl;
		}
	}
	cout <<"So diem ban dat duoc la:"<<diem<<endl;
	//ghi vao file
	ofstream l;
	l.clear();
	l.open("luu.txt", ios::app);
	l<<"So diem nguoi choi dat duoc la:"<<diem<<endl;
}
void menu(bode DSBD[]) //ham menu chon cac chuc nang
{
	ifstream f;
	int k; //bien lua chon
	do
	{
		system("cls"); //xoa man hinh
		cout<<"------------------Coder by Ho Chi Khang------------------"<<endl;
		cout<<"Phan mem thi trac nghiem mon mang may tinh!"<<endl;
		cout<<"1.Nhap 1 de mo Bo de 1:"<<endl;
		cout<<"2.Nhap 2 de mo Bo de 2:"<<endl;
		cout<<"3.Nhap 3 de mo Bo de 3:"<<endl;
		cout<<"4.Nhap phim 4 de thoat!"<<endl;
		cout<< "Lua chon cua ban: ";
		cin>>k;
		switch (k)
		{
			case 1:
				system("cls");
				f.open("bode1.txt", ios::in);
				doc(f, DSBD);
				xuat(DSBD);
				system("pause"); //dung man hinh de hien thi so dap an dung
				menu(DSBD);
				break;
			case 2:
				system("cls");
				f.open("bode2.txt", ios::in);
				doc(f, DSBD);
				xuat(DSBD);
				system("pause");
				menu(DSBD);
				break;
			case 3: 
				system("cls");
				f.open("bode3.txt", ios::in);
				doc(f, DSBD);
				xuat(DSBD);
				system("pause");
				menu(DSBD);
				break;
			case 4:
				exit(0);
				break;
		}
	}while(k!=0);	
}

int main () //ham chinh
{
	bode DSBD[50];
	menu(DSBD);
}
