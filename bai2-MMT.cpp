#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<fstream>
using namespace std;

ifstream f;
ofstream s;

struct NhanVien //khai bao cau truc nhan vien
{
	int nhanVienId;
	char hoTen[20];
	int tuoi;
	int luong;	
};

class DSNV //lop danh sach nhan vien
{
	public:
		int n;
		vector<NhanVien> dsNV;
		void doc();
		void nhapDSNVTuBanPhim();
		void inDSNV_ManHinh();
		void themNV();
		void timMSNV();
		void xoaMSNV();
		void suaMSNV();
		void menu();
};

void DSNV::doc()
{
	f.open("input2-2.txt");
	if(f.fail())
	{
		cout<<"Khong the mo file";
	}else
	f>>n;
	for(int i=0;i<n;i++)
	{
		f>>dsNV[i].nhanVienId;
		f>>dsNV[i].hoTen;
		f>>dsNV[i].tuoi;
		f>>dsNV[i].luong;
	}
	f.close();
}
void DSNV::nhapDSNVTuBanPhim() //dau vao
{
	cout<<"Nhap so luong nhan vien : "<<endl;
	cin>>n;
	dsNV.resize(n); //dat lai kich thuoc vector
	n=dsNV.size(); //lay kich thuoc vector
	for(int i=0;i<n;i++)
	{
		cout<<"Nhan vien thu "<<i+1<<":"<<endl;
		fflush(stdin);
		cout<<"Nhap ma so nhan vien:"<<endl;
		cin>>dsNV[i].nhanVienId;
		fflush(stdin);
		cout<<"Nhap ho va ten nhan vien:"<<endl; 
		cin.getline(dsNV[i].hoTen, 20);
		cout<<"Nhap tuoi nhan vien:"<<endl;
		cin>>dsNV[i].tuoi;
		cout<<"Nhap luong nhan vien:"<<endl;
		cin>>dsNV[i].luong;
	}
}

void DSNV::inDSNV_ManHinh() //dau ra
{
	for(int i=0;i<n;i++)
	{
		cout<<"Ma so nhan vien:"<<dsNV[i].nhanVienId<<endl;
		cout<<"Ho va ten:"<<dsNV[i].hoTen<<endl;
		cout<<"Tuoi nhan vien:"<<dsNV[i].tuoi<<endl;
		cout<<"Luong nhan vien:"<<dsNV[i].luong<<endl;
		cout<<"*********************************************"<<endl;
	}
}

void DSNV::timMSNV() //tim thong tin nhan vien theo ma nhan vien
{
	int x;
	cout<<"Nhap ma nhan vien can tim:"<<endl;
	cin>>x;
	n=dsNV.size();
	for(int i=0;i<n;i++)
	{
		if(dsNV[i].nhanVienId==x)
		{
			cout<<"================Thong tin nhan vien================"<<endl;
			cout<<"Ma so nhan vien:"<<dsNV[i].nhanVienId<<endl;
			cout<<"Ho va ten:"<<dsNV[i].hoTen<<endl;
			cout<<"Tuoi nhan vien:"<<dsNV[i].tuoi<<endl;
			cout<<"Luong nhan vien:"<<dsNV[i].luong<<endl;
			cout<<"*********************************************"<<endl;
		}	
		else if(dsNV[i].nhanVienId!=x)
			cout<<"Khong tim thay nhan vien co ma tren!"<<endl;
	}

}	
void DSNV::themNV() //them 1 nhan vien moi
{
	int a,l;
	cout<<"Nhap so luong nhan vien can them : ";
	cin>>l;
	n=dsNV.size();
	a=n;
	dsNV.resize(n+l);
	n=dsNV.size();
	for(int i=n-1;i>=a;i--)
	{
		cout<<"Nhap Ma Nhan Vien : "; 
		cin>>dsNV[i].nhanVienId;
		fflush(stdin);
		cout<<"Nhap Ho va Ten : "; 
		cin.getline(dsNV[i].hoTen, 20);
		cout<<"Nhap Tuoi Nhan Vien : ";
		cin>>dsNV[i].tuoi;
		cout<<"Nhap Luong Nhan Vien : ";
		cin>>dsNV[i].luong;
	}	
	cout<<"Da nhap thanh cong !"<<endl;	
}
void DSNV::suaMSNV() //sua thong tin nhan vien theo ma nhan vien
{
	int y;
	cout<<"Nhap ma cua nhan vien can sua doi:"<<endl;
	cin>>y;
	n = dsNV.size(); 
	for(int i=0;i<n;i++)
	{
		if(dsNV[i].nhanVienId==y) 
				{
					int h;
					cout<<"1.Thay doi ten nhan vien"<<endl;
					cout<<"2.Thay doi tuoi nhan vien"<<endl;
					cout<<"3.Thay doi luong nhan vien"<<endl;
					cout<<"Ban muon sua gi?"<<endl;
					cin>>h ;
					if(h==1 || h==2 || h==3)
					{
						if(h==1)
						{
							fflush(stdin);
							cout<<"Nhap lai ten nhan vien : "<<endl;
							cin.getline(dsNV[i].hoTen, 20);
						}else if(h==2)
						{
							cout<<"Nhap lai tuoi nhan vien : "<<endl;
							cin>>dsNV[i].tuoi;
						}else if(h==3)
						{
							cout<<"nhap lai luong nhan vien : "<<endl;
							cin>>dsNV[i].luong;
						}
					}	
				}
	}
}
void DSNV::xoaMSNV()
{
	n = dsNV.size();
	int m;
	cout<<"Nhap ma nhan vien can xoa : "; 
	cin>>m;
	for(int i=0;i<n;i++)
	{
		if(dsNV[i].nhanVienId==m) 
			dsNV.erase(dsNV.begin()+i);
		else if(dsNV[i].nhanVienId!=m)
			cout<<"Khong tim thay ma nhan vien can xoa!";	
	}
}

void DSNV::menu() //danh sach chuc nang
{
	int k; //bien lua chon
	do
	{
		cout<<"\n**********Coder by Ho Chi Khang - 58131320**********";
		cout<<"\n______________PHAN MEM QUAN LY NHAN VIEN______________"<<endl;
		cout<<"1.Doc thong tin nhan vien tu file "<<endl;
		cout<<"2.Nhap thong tin nhan vien"<<endl;
		cout<<"3.Them nhan vien moi"<<endl;
		cout<<"4.Nhap ma nhan vien va cho biet thong tin nhan vien do"<<endl;
		cout<<"5.Sua doi nhan vien theo ma nhan vien"<<endl;
		cout<<"6.Xoa nhan vien theo ma nhan vien"<<endl;
		cout<<"7.In ra man hinh danh sach nhan vien"<<endl;
		cout<<"8.Thoat!"<<endl;
		cout<<"Ban chon chuc nang so:"<<endl;
		cin>> k;
		system("cls"); //xoa man hinh
		switch( k )
		{
			case 1:
				doc();
				break;
			case 2:
				nhapDSNVTuBanPhim();
				break;
			
			case 3:
				themNV();
				break;
			
			case 4:
				timMSNV();
				break;
			
			case 5:
				suaMSNV();
				break;		
				
			case 6:
				xoaMSNV();
				break;
			case 7:
				inDSNV_ManHinh();	
				break;
			case 8: break;	
			default:
				cout<< "\nNhap lai!";
				break;
		}
	}while(k!=0); //neu =0 se ket thuc
}

int main() //ham chinh
{
	int n;
	DSNV a;
	a.menu();
	system("cls");
	system("pause");
}

 



