#ifndef SCULPTOR_H
#define SCULPTOR_H
#include<string>

using namespace std;
//parte 3

/**
* @brief The Voxel struct - Destinado a manipulação das cores do objeto, nível opacidade e se o mesmo está ativo ou não.
        */
struct Voxel {
  float r,g,b;
  float a;
  bool isOn;
};

/**
 * @brief The Sculptor class - Classe que contem todas as manipulações da matriz 3d
 */


class Sculptor{
private:
  int nx, ny, nz;
  float _r,_g,_p,_alpha;
  Voxel ***v;


public:
  /**
   * @brief Sculptor - Construtor da classe
   * @param _nx
   * @param _ny
   * @param _nz
   */
  Sculptor(int _nx=0, int _ny=0, int _nz=0);

  /**
    *@brief   ~Sculptor - Destrutor
    */
  ~Sculptor();

  /**
   * @brief setColor - Define a cor atual de desenho.
   * @param r
   * @param g
   * @param b
   * @param alpha
   */
  void setColor(float r, float g, float b, float alpha);

  /**
   * @brief putVoxel - Ativa o voxel na posição (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor atual de desenho
   * @param x
   * @param y
   * @param z
   */
  void putVoxel(int x, int y, int z);

  /**
   * @brief cutVoxel - Desativa o voxel na posição (x,y,z) (fazendo isOn = false)
   * @param x
   * @param y
   * @param z
   */
  void cutVoxel(int x, int y, int z);
  /**
   * @brief putBox - Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
   * @param x0
   * @param x1
   * @param y0
   * @param y1
   * @param z0
   * @param z1
   */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

  /**
   * @brief cutBox - Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
   * @param x0
   * @param x1
   * @param y0
   * @param y1
   * @param z0
   * @param z1
   */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

  /**
   * @brief putSphere - Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho (r,g,b,a)
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param radius
   */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);

  /**
   * @brief cutSphere - Desativa todos os voxels que satisfazem à equação da esfera
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param radius
   */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

  /**
   * @brief putEllipsoid - Ativa todos os voxels que satisfazem à equação do elipsóide e atribui aos mesmos a cor atual de desenho
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param rx
   * @param ry
   * @param rz
   */

  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

  /**
  * @brief cutEllipsoid - Desativa todos os voxels que satisfazem à equação do elipsóide
  * @param xcenter
  * @param ycenter
  * @param zcenter
  * @param rx
  * @param ry
  * @param rz
  */

  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

  /**
   * @brief writeOFF - grava a escultura no formato OFF no arquivo filename
   * @param filename
   */
  void writeOFF(string filename);
  /**
   * @brief writeVECT - grava a escultura no formato VECT no arquivo filename
   * @param filename
   */
  void writeVECT(string filename);
};
//-----------
#endif // SCULPTOR_H
