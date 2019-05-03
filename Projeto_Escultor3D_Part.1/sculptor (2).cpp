#include "sculptor.h"
#include <iostream>
#include <cstdlib>
#include<string>
#include <fstream>

//Construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx; ny = _ny; nz = _nz;
    if(nx <= 0 || ny <= 0 || nz <= 0){
        nx =0;
        ny = 0;
        nz = 0;
    }
    v = new Voxel**[nx];
    if(v == nullptr){
        exit(0);
    }
    v[0] = new Voxel*[nx*ny];
    if(v[0] == nullptr){
        exit(0);
    }
    v[0][0] = new Voxel[nx*ny*nz];
    if(v[0][0] == nullptr){
        exit(0);
    }

    for(int i=0; i< nx; i++)
    {
        if (i<(nx-1))
        {
            v[i+1] = v[i]+nx;
        }
        for(int j=0; j< ny; j++)
        {
            v[i][j+1] = v[i][j]+ny;
            if(j==ny-1 && i!=(nx-1))
            {
                v[i+1][0] = v[i][j]+nz;
            }}}

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                v[i][j][k].isOn = false;
            }}}}

//Destrutor da classe
Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

//Define a cor atual de desenho.
void Sculptor::setColor(float r, float g, float b, float alpha){

    //verificacao de codigo invalido e atrbuindo valor valido referente a variavel
    if(r >1){
        _r = 1;
    }
    if(r <0){
        _r = 0;
    }else{
        _r = r;
    }
    if(g >1){
        _g = 1;
    }
    if(g <0){
        _g = 0;
    }else{
        _g = g;
    }
    if(b >1){
        _p = 1;
    }
    if(b <0){
        _p = 0;
    }else{
        _p = b;
    }
    if(alpha >1){
        _alpha = 1;
    }
    if(alpha <0){
        _alpha = 0;
    }else{
        _alpha = alpha;
    }}

//Ativa o voxel na posicao (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor atual de desenho
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = _r;
    v[x][y][z].g = _g;
    v[x][y][z].b = _p;
    v[x][y][z].a = _alpha;
}

//Desativa o voxel na posicao (x,y,z) (fazendo isOn = false)
void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

//Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int i = x0; i<x1+1; i++){
        for (int j = y0; j<y1+1; j++){
            for (int k = z0; i<z1+1; k++){

                v[i][j][k].r = _r;
                v[i][j][k].g = _g;
                v[i][j][k].b = _p;
                v[i][j][k].a = _alpha;
                v[i][j][k].isOn = true;

            }}}}

//Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int i = x0; i<x1+1; i++){
        for (int j = y0; j<y1+1; j++){
            for (int k = z0; i<z1+1; k++){
                v[i][j][k].r = _r;
                v[i][j][k].g = _g;
                v[i][j][k].b = _p;
                v[i][j][k].a = _alpha;
                v[i][j][k].isOn = false;

            }}}}

//Ativa todos os voxels que satisfazem a equacao da esfera e atribui aos mesmos a cor atual de desenho
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i< xcenter; i++)
    {
        for(int j=0; j< ycenter; j++)
        {
            for(int k=0; k< zcenter; k++)
            {

                //equacao da esfera
                if (((i-xcenter)*(i-xcenter)) + ((j-ycenter)*(j-ycenter)) + ((k-zcenter)*(k-zcenter)) <= ((radius)*(radius)))
                {
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = _r;
                    v[i][j][k].g = _g;
                    v[i][j][k].b = _p;
                    v[i][j][k].a = _alpha;
                }}}}}

//Desativa todos os voxels que satisfazem a equacao da esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i< xcenter; i++)
    {
        for(int j=0; j< ycenter; j++)
        {
            for(int k=0; k< zcenter; k++)
            {
                //Equacao da esfera
                if (((i-xcenter)*(i-xcenter)) + ((j-ycenter)*(j-ycenter)) + ((k-zcenter)*(j-ycenter)) <= ((radius)*(radius)))
                {
                    v[i][j][k].r = _r;
                    v[i][j][k].g = _g;
                    v[i][j][k].b = _p;
                    v[i][j][k].a = _alpha;
                    v[i][j][k].isOn = false;

                }}}}}

//Ativa todos os voxels que satisfazem à equacao do elipsoide e atribui aos mesmos a cor atual de desenho
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i< rx; i++)
    {
        for(int j=0; j< ry; j++)
        {
            for(int k=0; k< rz; k++)
            {
                //Equacao da elipse
                if ((((i-xcenter)*(i-xcenter))/((float)((xcenter)*(xcenter)))) + (((j-ycenter)*(j-ycenter))/((float)((ycenter)*(ycenter))))
                        + (((k-zcenter)*(k-zcenter))/((float)((zcenter)*(zcenter)))) <=1.0)
                {
                    v[i][j][k].r = _r;
                    v[i][j][k].g = _g;
                    v[i][j][k].b = _p;
                    v[i][j][k].a = _alpha;
                    v[i][j][k].isOn = true;

                }}}}}

//Desativa todos os voxels que satisfazem a equacao do elipsoide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i< rx; i++)
    {
        for(int j=0; j< ry; j++)
        {
            for(int k=0; k< rz; k++)
            {
                //equacao da elipse
                if ((((i-xcenter)*(i-xcenter))/((float)((xcenter)*(xcenter)))) +
                        ((((j-ycenter)*(j-ycenter)))/((float)((ycenter)*(ycenter)))) +
                        ((((k-zcenter)*(k-zcenter)))/((float)((zcenter)*(zcenter)))) <=1.0)
                {
                    v[i][j][k].r = _r;
                    v[i][j][k].g = _g;
                    v[i][j][k].b = _p;
                    v[i][j][k].a = _alpha;
                    v[i][j][k].isOn = false;

                }}}}}


//grava a escultura no formato OFF no arquivo filename
void Sculptor::writeOFF(string filename){
    //numero de voxel
    int n_voxel = 0;

    //matriz auxiliar para verificacao do voxel e seu arredor
    int aux[nx][ny][nz];
    bool test_x, test_y, test_z;


    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                aux[i][j][k] = 0;
            }}}


    ofstream outfile (filename);
    outfile<<"OFF"<<endl;
    for(int i = 0; i < nx-2; i++){
        for(int j = 0; j < ny-2; j++){
            for(int k = 0; k < nz-2; k++){
                test_x = false, test_y = false, test_z=false;

                //Verificacao ao redor do voxel
                if(v[i][j][k].isOn && v[i+2][j][k].isOn){
                    test_x = true;
                }
                if(v[i][j][k].isOn && v[i][j+2][k].isOn){
                    test_y = true;
                }
                if(v[i][j][k].isOn && v[i][j][k+2].isOn){
                    test_z = true;
                }
                if(test_x || test_y || test_z){
                    aux[i+1][j+1][k+1] = 1;
                }}}}

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && aux[i][j][k] == 0){
                    n_voxel++;
                }}}}


    outfile << 8*n_voxel << " " << 6*n_voxel << " " << 0 << std::endl;
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && aux[i][j][k] == 0){
                    outfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    outfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    outfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    outfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    outfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    outfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    outfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    outfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }}}}
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && aux[i][j][k] ==0){
                    outfile << 4 << " " << 0 + 8*i << " " << 3 + 8*i << " " << 2 + 8*i << " " << 1 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    outfile << 4 << " " << 4 + 8*i << " " << 5 + 8*i << " " << 6 + 8*i << " " << 7 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    outfile << 4 << " " << 0 + 8*i << " " << 1 + 8*i << " " << 5 + 8*i << " " << 4 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    outfile << 4 << " " << 0 + 8*i << " " << 4 + 8*i << " " << 7 + 8*i << " " << 3 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    outfile << 4 << " " << 3 + 8*i << " " << 7 + 8*i << " " << 6 + 8*i << " " << 2 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    outfile << 4 << " " << 1 + 8*i << " " << 2 + 8*i << " " << 6 + 8*i << " " << 5 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                }}}}

    outfile.close();
}

//grava a escultura no formato VECT no arquivo filename
void Sculptor::writeVECT(string filename){
    int n_voxel = 0;
    bool test_x = false, test_y = false, test_z=false;
    int s[nx][ny][nz];
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                s[i][j][k] = 0;
     }}}


    ofstream outfile (filename);
    outfile << "VECT" << endl;
    for(int i = 0; i < nx-2; i++){
        for(int j = 0; j < ny-2; j++){
            for(int k = 0; k < nz-2; k++){
                test_x = false, test_x = false, test_z=false;


                //logica referente a verificacao da locacao do voxel, valida ou invalida
                if(v[i][j][k].isOn && v[i+2][j][k].isOn){
                    test_x = true;
                }
                if(v[i][j][k].isOn && v[i][j+2][k].isOn){
                    test_x = true;
                }
                if(v[i][j][k].isOn && v[i][j][k+2].isOn){
                    test_z = true;
                }
                if(test_x || test_x || test_z){
                    s[i+1][j+1][k+1] = 1;
        }}}}


    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && s[i][j][k] == 0){
                    n_voxel++;
    }}}}

    outfile << n_voxel << " " << n_voxel << " " << n_voxel << endl;
    for (int i =0;i<n_voxel; i++) {
        outfile << "1" <<" ";
    }
    outfile << endl;
    for (int i =0;i<n_voxel; i++) {
        outfile << "1" <<" ";
    }
    outfile << endl;
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && s[i][j][k] == 0){
                    outfile << i <<" "<< j <<" "<< k << endl;
     }}}}

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(test_x || test_x || test_z){ v[i][j][k].isOn = false;}
                if (v[i][j][k].isOn && s[i][j][k] == 0){
                    outfile << v[i][j][k].r <<" "<< v[i][j][k].g <<" "<< v[i][j][k].b <<" "<< v[i][j][k].a << endl;
                }}}}

    outfile.close();
}
