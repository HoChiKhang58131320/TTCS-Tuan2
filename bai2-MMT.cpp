#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<fstream>
#include<stdio.h>
using namespace std;
ofstream b("output2-2.txt");
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
		void ghi();
		void ghitxt();
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
	dsNV.clear();
	FILE *f;
	f= fopen("input2-2.txt", "rb");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			NhanVien nv;
			fread(&nv, sizeof(NhanVien), 1, f);
			dsNV.push_back(nv);
		}
		fclose(f);
		dsNV.pop_back();
	}
}
void DSNV::ghi()	
{
	n=dsNV.size();
	FILE *s;
	s=fopen("ouput2-2.dat","wb");
	NhanVien nv;
	for(int i=0;i<n;i++)
	{
		nv=dsNV[i];
		fwrite(&nv,sizeof(NhanVien),1,s);
	}
}

void DSNV::ghitxt()
{
	b<<"Ma nhan vien"<<"\t"<<"Ho ten"<<"\t\t\t"<<"Tuoi"<<"\t"<<"Luong nhan vien"<<endl;
	for(int i=0;i<n;i++)
	b<<dsNV[i].nhanVienId<<"\t\t"<<dsNV[i].hoTen<<"\t\t"<<dsNV[i].tuoi<<"\t"<<dsNV[i].luong<<endl;
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
	ghitxt();
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
			b<<"-----------Thong tin nhan vien------------"<<endl;
			b<<"STT"<<"\t"<<"Ma nhan vien"<<"\t"<<"Ho ten"<<"\t\t\t\t"<<"Tuoi"<<"\t"<<"Luong nhan vien"<<endl;
			b<<i+1<<"\t"<<dsNV[i].nhanVienId<<"\t\t"<<dsNV[i].hoTen<<"\t\t\t"<<dsNV[i].tuoi<<"\t\t"<<dsNV[i].luong<<endl;
			b<<endl;
		}	
		else if(dsNV[i].nhanVienId!=x)
			cout<<"Khong tim thay nhan vien co ma tren!"<<endl;
	}

}	
void DSNV::themNV() //them 1 nhan vien moi
{
	int z,a,g=0;
	cout<<"Nhap so luong nhan vien can them:";
	cin>>z;
	n=dsNV.size();
	a=n;
	dsNV.resize(n+z); //dat lai kich thuoc vector
	n=dsNV.size(); //lay kich thuoc moi
	for(int i=n-1;i>=a;i--)
	{
		cout<<"Nhap ma so nhan Vien:"; 
		cin>>dsNV[i].nhanVienId;
		if(dsNV[i].nhanVienId==dsNV[g].nhanVienId) //neu ma nhan vien da ton tai
		{
			cout<<"Nhap lai : ";
			cin>>dsNV[i].nhanVienId;
		}
		fflush(stdin);
		cout<<"Nhap ho va ten nhan vien : "; 
		cin.getline(dsNV[i].hoTen, 20);
		cout<<"Nhap tuoi nhan vien : ";
		cin>>dsNV[i].tuoi;
		cout<<"Nhap luong nhan vien : ";
		cin>>dsNV[i].luong;
	}	
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
	int l,t;
	cout<<"Nhap ma nhan vien can xoa : ";
	cin>>l;
	for(int i=0;i<n;i++)
	if(dsNV[i].nhanVienId==l)
		t=i;
	if(dsNV[t].nhanVienId==l)
	{
		if(t<n)
		{
			dsNV[t]=dsNV[t+1];
			t++;
		}
		n--;
		cout<<"Xoa thanh cong!"<<endl;
		b<<"Xoa thanh cong!"<<endl;
	}
	else
		cout<<"Xoa that bai!"<<endl;
		b<<"Xoa that bai!"<<endl;
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
				ghi();
				break;
			
			case 4:
				timMSNV();
				ghi();
				break;
			
			case 5:
				suaMSNV();
				ghi();
				break;		
				
			case 6:
				xoaMSNV();
				ghi();
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
	system("pause");
}

 



