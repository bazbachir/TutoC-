/*!
 * \file BAZEMLAL.cpp
 * \brief Création de point, cercle et ensemble
 * \author Bachir_BAZEMLAL
 * \version 0.1
 */

#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

    /*! \class Point
   * \brief classe permettant de créer et de manipuler des point
   *
   *  Cette classe permet de créer des point, d'additioner des points, de calculer la distance entre les points et leur affichage
   */
class Point
{
private:
    float x; /*!L'abscisse du point*/
    float y;/*!L'ordonnée du point*/
public:
    /*!
     *  \brief Constructeur vide
     *
     *  Constructeur vide de la classe Point
     *
     */
    Point();
    /*!
     *  \brief Constructeur avec deux paramètres
     *
     *  Constructeur à deux paramètres de la classe Point
     *
     *  \param a : L'abscisse du point
     *  \param b : L'ordonnée du point
     */
    Point(float a, float b);
    /*!
     *  \brief destructeur
     *
     *  destructeur de la classe Point
     *
     */
    ~Point();
    /*!
     *  \brief calcule de distance 
     *
     *  Fonction amie qui permet de calculer la distance entre deux points
     *
     *  \param a : le premier point
     *  \param b : le deuxième point
     *  \return la distance entre les deux points 
     */
    friend float distance(Point const& a, Point const& b);
    /*!
     *  \brief surcharge de l'opérateur <<
     *
     *  surcharge de l'oprateur d'affichage (flot de sortie)
     *
     *  \param s : le flot de sortie
     *  \param b : le  point à afficher
     *  \return le flot de sortie (pour permettre l'enchainement)
     */
    friend ostream& operator<<(ostream& s, const Point& a);
    /*!
     *  \brief surcharge de l'opérateur +
     *
     *  surcharge de l'oprateur d'addition (+)
     *
     *  \param a : le premier point
     *  \param b : le deuxième point
     *  \return le point résultant
     */
    friend Point operator+(const Point& a, const Point& b);
    /*!
     *  \brief surcharge de l'opérateur +
     *
     *  surcharge de l'opérateur de division d'un point sur un réel
     *
     *  \param a : le point
     *  \param b : le réel
     *  \return le point résultant
     */
    friend Point operator/(const Point& a, float b);
     /*!
     *  \brief définition de la classe ensemble comme amie de la classe point 
     *
     *  définition de la classe ensmble comme amie de la classe point pour lui permettre l'acces au coordonnées x et y
     */
    friend class Ensemble;
};

    /*! \class Cercle
   * \brief classe permettant de créer et de manipuler des cercles
   *
   *  Cette classe permet de créer des cercles et de les affichager
   */


class Cercle
{
private:
    Point m_centre; /*!Le centre du cercle*/
    float m_rayon;  /*!Le rayon du cercle*/
    
public:
    /*!
     *  \brief Constructeur vide de Cercle
     *
     *  Constructeur vide de la classe Cercle
     *
     */
    Cercle();
    Cercle(Point const&, float);
    ~Cercle();
    friend ostream& operator<<(ostream& s, const Cercle& a);
};

  /*! \class Ensemble
   * \brief classe permettant de créer un ensemble de points
   *
   *  Cette classe permet de créer des ensembles, de calculer leur barycentre, le cercle qui les enveloppe, et l'ensemnle des points à gauche du barycentre
   */

class Ensemble
{
private:
    int m_nbrDePoint; /*!Le nombre de points dans l'ensemble*/
    Point *m_T; /*!le tableau contennant l'ensemble des points*/
public:
    /*!
     *  \brief Constructeur vide
     *
     *  Constructeur vide de la classe Ensemble
     *
     */
    Ensemble(); 
    ~Ensemble();
    void Ajoute(Point const&);
    void Supprime(int);
    Point Barycentre() const;
    Cercle Enveloppe() const;
    Ensemble Gauche()const;
    friend ostream& operator<<(ostream& s, const Ensemble& a);
};



/*!Le code source des différents classes et fonctions*/


Point::Point()
{
    x=0;
    y=0;
}

Point::~Point()
{
}
Point::Point(float a, float b)
{
    x=a;
    y=b;
}
float distance(Point const& a, Point const& b)
{
    float d;
    d=sqrt(pow((a.x-b.x),2)+pow((a.x-b.x),2));
    return d;
}
ostream& operator<<(ostream& s, const Point& a)
{
    s<<"("<<a.x<<","<<a.y<<")";
    return s;
}
Point operator+(const Point& a, const Point& b)
{   
    Point c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    return c;
}
Point operator/(const Point& a, float r)
{   
    Point c;
    c.x=a.x/r;
    c.y=a.y/r;
    return c;
}



Cercle::Cercle()
{
    m_centre=Point(0,0);
    m_rayon=0;
}
Cercle::Cercle(Point const& c, float r)
{
    m_centre=c;
    m_rayon=r;
}
Cercle::~Cercle()
{
}
ostream& operator<<(ostream& s, const Cercle& a)
{
    s<<"(c="<<a.m_centre<<", r="<<a.m_rayon<<")";
    return s;
}


Ensemble::Ensemble()
{
    m_nbrDePoint=0;
    m_T=nullptr;
}

Ensemble::~Ensemble()
{
    delete [] m_T;
}
void Ensemble::Ajoute(Point const& a)
{
    m_nbrDePoint++;
    Point *m_T2;
    m_T2=new Point[m_nbrDePoint];
    for(int i=0; i<m_nbrDePoint-1; i++)
    {
        m_T2[i]=m_T[i];
    }
    m_T2[m_nbrDePoint-1]=a;
    delete [] m_T;
    m_T=m_T2;

}

void Ensemble::Supprime(int i)
{
    if (i>0)
    {
        if (i<m_nbrDePoint)
        {
            Point *m_T2;
            m_T2=new Point[m_nbrDePoint-1];
            for (int j = 0; j < i-1; j++)
            {
                m_T2[j]=m_T[j];
            }
            for (int j = i; j < m_nbrDePoint; j++)
            {
                m_T2[j-1]=m_T[j];
            }
            delete m_T;
            m_nbrDePoint--;
            m_T=m_T2;
        }
    }
}

Point Ensemble::Barycentre()const
{
    Point a(0,0);
    for(int i=0;i<m_nbrDePoint; i++)
    {
        a=a+m_T[i];
    }
    a=a/m_nbrDePoint;
    return a;
}

Cercle Ensemble::Enveloppe() const
{
    float plusGrandeDist(0);
    for(int i=0; i<m_nbrDePoint; i++)
    {
        if(distance(m_T[i],Barycentre())>plusGrandeDist)
        {
            plusGrandeDist=distance(m_T[i],Barycentre());
        }
    }
    return(Cercle(Barycentre(), plusGrandeDist));

}

Ensemble Ensemble::Gauche()const
{
    Ensemble a;
    for(int i=0;i<m_nbrDePoint; i++)
    {
        if(m_T[i].y<Barycentre().y)
        {
            a.Ajoute(m_T[i]);
        }
    }
    return a;
}
ostream& operator<<(ostream& s, const Ensemble& a)
{
    for(int i=0; i<a.m_nbrDePoint;i++)
    {
        s<<a.m_T[i]<<" ";
    }
    return s;
}

int main()
{

    Ensemble e; 
    e.Ajoute(Point(2,3)); 
    e.Ajoute(Point(-2,2)); 
    e.Ajoute(Point(6,1)); 
    e.Ajoute(Point(1,-5));
    cout<<e<<endl;
    Cercle c;
    c=e.Enveloppe();
    cout<<c<<endl;
    return 0;
}