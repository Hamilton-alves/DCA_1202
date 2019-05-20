#include <string>
#include <iostream>
#include <fstream>
#include <sculptor.h>
#include <cstdlib>

using namespace std;

Sculptor::Sculptor(int x, int y, int z){
    nx=x; ny=y; nz=z;
    v= new Voxel**[nx];
    if(v == nullptr){
        cout<<"v não armazenado"<<endl;
        exit(0);
    }
    v[0]= new Voxel*[nx*ny] ;
    if(v[0] == nullptr){
        cout<<"v[0] não armazenado"<<endl;
        exit(0);
    }
    v[0][0]= new Voxel[nx*ny*nz];
    if(v[0][0]==nullptr){
        cout<<"v[0][0] não armazenado"<<endl;
        exit(0);
    }

    for (int i=0;i<nx;i++){
        if(i<(nx-1)){
            v[i+1]=v[i]+ny;
        }
        for (int j=0;j<ny;j++){
            if(j==ny-1&&i!=(nx-1)){
                v[i+1][0]=v[i][j]+nz;
            }
            else{
                v[i][j+1]=v[i][j]+nz;
            }

            for(int k=0;k<nz;k++){
                v[i][j][k].r=0.0;
                v[i][j][k].g=0.0;
                v[i][j][k].b=0.0;
                v[i][j][k].a=0.0;
                v[i][j][k].isOn=false;
            }

        }
    }


}

Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;

}

void Sculptor::setColor(float _r, float _g, float _b, float alpha)
{
    if(_r<0||_g<0||_b<0||alpha<0){
        cout<<"Parametros de 'setColor' invalidos"<<endl;
        exit(1);
    }
    r=_r;
    g=_g;
    b=_b;
    a=alpha;
}

void Sculptor::putVoxel( int x, int y, int z)
{
    if(x<nx && x >= 0 && y < ny && y >= 0 && z < nz && z>= 0){

        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel( int x, int y, int z)
{
    if(x<nx && x >= 0 && y < ny && y >= 0 && z < nz && z>= 0){
        v[x][y][z].isOn = false;
    }
}

void Sculptor::writeOFF(const string filename)
{

    int Nf,Nv, vox=0 ,nfc=0, face;
    char ***M;
    M=new char**[nx];
    if(M == nullptr){
        cout<<"não armazenado"<<endl;
        exit(0);
    }
    M[0]= new char*[nx*ny] ;
    if(M[0] == nullptr){
        cout<<"M[0] não armazenado"<<endl;
        exit(0);
    }
    M[0][0]= new char[nx*ny*nz];
    if(M[0][0]==nullptr){
        cout<<"M[0][0] não armazenado"<<endl;
        exit(0);
    }

    for (int i=0;i<nx;i++){
        if(i<(nx-1)){
            M[i+1]=M[i]+ny;
        }
        for (int j=0;j<ny;j++){
            if(j==ny-1&&i!=(nx-1)){
                M[i+1][0]=M[i][j]+nz;
            }
            else{
                M[i][j+1]=M[i][j]+nz;
            }
            for(int k=0;k<nz;k++){
                M[i][j][k]='0';
            }
        }
    }

    for(int i=1;i<(nx-1);i++){
        for (int j=1;j<(ny-1);j++) {
            for(int k=1; k<(nz-1);k++){
                if(v[i-1][j][k].isOn && v[i+1][j][k].isOn && v[i][j-1][k].isOn &&
                   v[i][j+1][k].isOn && v[i][j][k-1].isOn && v[i][j][k+1].isOn){
                    M[i][j][k]='1';
                }
            }
        }
    }
    for(int i=1;i<(nx-1);i++){
        for (int j=1;j<(ny-1);j++) {
            for(int k=1; k<(nz-1);k++){
                if(M[i][j][k]=='1'){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
    delete [] M[0][0];
    delete [] M[0];
    delete [] M;
    ofstream file;
    file.open(filename);
    if(file.is_open()){
        cout<<"Arquivo aberto (off)"<<endl;
    }
    else{
        cout << "arquivo não aberto (off)"<<endl;
        exit(1);
    }
    file<<"OFF \n";

    for (int i=0;i<nx;i++) {
        for (int j=0;j<ny;j++) {
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn){
                    vox++;
                }
            }
        }
    }

    Nf=6*vox;
    Nv=8*vox;

    file<<Nv<<" "<<Nf<<" 0 \n";

    double bX,aX,bY,aY,bZ,aZ;

    for(int k=0;k<nz; k++){
        bZ=-0.5+k;
        aZ=0.5+k;
        for(int j=0;j<ny;j++){
            bY=-0.5+j;
            aY=0.5+j;
            for (int i=0;i<nx;i++) {
                bX=-0.5+i;
                aX=0.5+i;
                if(v[i][j][k].isOn){
                    file<<bX<<" "<<aY<<" "<<bZ<<endl
                        <<bX<<" "<<bY<<" "<<bZ<<endl
                        <<aX<<" "<<bY<<" "<<bZ<<endl
                        <<aX<<" "<<aY<<" "<<bZ<<endl
                        <<bX<<" "<<aY<<" "<<aZ<<endl
                        <<bX<<" "<<bY<<" "<<aZ<<endl
                        <<aX<<" "<<bY<<" "<<aZ<<endl
                        <<aX<<" "<<aY<<" "<<aZ<<endl;
                }
            }
        }

    }

    for(int k=0;k<nz; k++){
        for(int j=0;j<ny;j++){
            for (int i=0;i<nx;i++) {
                if(v[i][j][k].isOn){
                    face=nfc*8;
                    file<<"4 "<<0+face<<" "<<3+face<<" "<<2+face<<" "<<1+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<4+face<<" "<<5+face<<" "<<6+face<<" "<<7+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<0+face<<" "<<1+face<<" "<<5+face<<" "<<4+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<0+face<<" "<<4+face<<" "<<7+face<<" "<<3+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<3+face<<" "<<7+face<<" "<<6+face<<" "<<2+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<1+face<<" "<<2+face<<" "<<6+face<<" "<<5+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    nfc++;
                }


            }
        }

    }

    file.close();
}

void Sculptor::writeVECT(const string filename)
{
    ofstream file;
    file.open(filename);
    if(file.is_open()){
        cout<<"Arquivo aberto(vect)"<<endl;
    }
    else{
        cout << "arquivo não aberto(vect)"<<endl;
        exit(1);
    }
    file<<"VECT \n";
    int  vox=0;
    for (int i=0;i<nx;i++) {
        for (int j=0;j<ny;j++) {
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn){
                    vox++;
                }
            }
        }
    }


    file<<vox<<" "<<vox<<" "<<vox<<endl;
    for(int j=0;j<2;j++){
        for (int i = 0; i< vox; i++){
            file<<"1 ";
        }
        file<<"\n";
    }
    for(int i = 0; i<nx; i++){
        for(int j =0 ; j < ny ; j++){
            for (int k=0; k< nz; k++){
                if(v[i][j][k].isOn){
                file<<i<<" "<<j<<" "<<k<<endl;
                }
            }
        }
    }
    for(int i = 0; i<nx; i++){
        for(int j =0 ; j < ny ; j++){
            for (int k=0; k< nz; k++){
                if(v[i][j][k].isOn){
                    file<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                }

            }
        }
    }

    file.close();

}
