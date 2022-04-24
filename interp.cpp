#include "interp.h"
#include <QVector>
#include <QDebug>
#include <QGenericMatrix>
#include <QtMath>

interp::interp(){

}

double interp::bilinearInterp(double fieldSize, double energy, QVector<double> x, QVector<double> y, QVector<double> v)
{
   // x is usually the field size, y the energy and z the value of the magnitude(scatter factor,TPS etc)
    QVector<double> xsub=x;
    QVector<double> ysub=y;


    for (int i=0; i<x.size();++i){
        xsub[i]=abs(x[i]-fieldSize); //subtracted 0.1 so nearest to 19.5 is 20 and not 19. why the FUCK did I do this!!
    }

    auto minx = std::min_element(xsub.begin(),xsub.end());
    auto distx = std::distance(xsub.begin(),minx);
    qDebug() << "x.at(distx)" << x.at(distx);



    //finding the x limits for the interpolation
    double x1=0;
    double x2=0;
    int ix1=0;
    int ix2=0;
    if (fieldSize-x.at(distx)>0  ){
        x1=x.at(distx);
        x2=x.at(distx+1);
        ix1=distx;
        ix2=distx+1;
    }
    else if (fieldSize-x.at(distx)<0){
        x1=x.at(distx-1);
        x2=x.at(distx);
        ix1=distx-1;
        ix2=distx;
    }
    else{
        if (x.at(distx)==x.back()) {
            x1=x.at(distx-1);
            x2=x.at(distx);
            ix1=distx-1;
            ix2=distx;
        }
        else{
            x1=x.at(distx);
            x2=x.at(distx+1);
            ix1=distx;
            ix2=distx+1;
        }
    }



    //finding the y limits for the interpolation
    for (int i=0; i<y.size();++i){
        ysub[i]=abs(y[i]-energy); //subtracted 0.1 so nearest to 19.5 is 20 and not 19
    }
    auto miny = std::min_element(ysub.begin(),ysub.end());
    auto disty = std::distance(ysub.begin(),miny);

    double y1=0;
    double y2=0;
    int iy1=0;
    int iy2=0;
    if (energy-y.at(disty)>0  ){
        y1=y.at(disty);
        y2=y.at(disty+1);
        iy1=disty;
        iy2=disty+1;
    }
    else if (energy-y.at(disty)<0){
        y1=y.at(disty-1);
        y2=y.at(disty);
        iy1=disty-1;
        iy2=disty;
    }
    else{
        if (y.at(disty)==y.back()) {
            y1=y.at(disty-1);
            y2=y.at(disty);
            iy1=disty-1;
            iy2=disty;
        }
        else{
            y1=y.at(disty);
            y2=y.at(disty+1);
            iy1=disty;
            iy2=disty+1;
        }

    }


//    Q11=(x1,y1);
//    Q12=(x1,y2);
//    Q21=(x2,y1);
//    Q22=(x2,y2);

    qDebug() << x1 << x2;
    qDebug() << y1 << y2;
    qDebug() << "value - interp=" << 1/((x2-x1)*(y2-y1)+0.000001)*(v.at(ix1+iy1*x.size())*(x2-fieldSize)*(y2-energy) +  v.at(ix2+iy1*x.size())*(fieldSize-x1)*(y2-energy)   +   v.at(ix1+iy2*x.size())*(x2-fieldSize)*(energy-y1)  +    v.at(ix2+iy2*x.size())*(fieldSize-x1)*(energy-y1));
//success!!!

//    value = a0 + a1*x + a2*y + a3*x*y (definition)
    double f11=v.at(ix1+iy1*x.size());
    double f21=v.at(ix2+iy1*x.size());
    double f12=v.at(ix1+iy2*x.size());
    double f22=v.at(ix2+iy2*x.size());

    double a0 = f11*x2*y2/((x1-x2)*(y1-y2)) + f12*x2*y1/((x1-x2)*(y2-y1)) +  f21*x1*y2/((x1-x2)*(y2-y1)) + f22*x1*y1/((x1-x2)*(y1-y2)) ;
    double a1 = f11*y2/((x1-x2)*(y2-y1)) + f12*y1/((x1-x2)*(y1-y2)) +  f21*y2/((x1-x2)*(y1-y2)) + f22*y1/((x1-x2)*(y2-y1)) ;
    double a2 = f11*x2/((x1-x2)*(y2-y1)) + f12*x2/((x1-x2)*(y1-y2)) +  f21*x1/((x1-x2)*(y1-y2)) + f22*x1/((x1-x2)*(y2-y1)) ;
    double a3 = f11/((x1-x2)*(y1-y2)) + f12/((x1-x2)*(y2-y1)) +  f21/((x1-x2)*(y2-y1)) + f22/((x1-x2)*(y1-y2)) ;
//        value = a0 + a1*fieldSize + a2*energy + a3*fieldSize*energy;
    double value = a0 + a1*fieldSize + a2*energy + a3*fieldSize*energy;



//    double value=1/((x2-x1)*(y2-y1)+0.000001)*(v.at(ix1+iy1*x.size())*(x2-fieldSize)*(y2-energy) +  v.at(ix2+iy1*x.size())*(fieldSize-x1)*(y2-energy)   +   v.at(ix1+iy2*x.size())*(x2-fieldSize)*(energy-y1)  +    v.at(ix2+iy2*x.size())*(fieldSize-x1)*(energy-y1) );
    qDebug() << "bilinear value" << value;
//    now we just need to display this value. send a signal or something go over older code
    return value;


}


double interp::trilinearInterp(double fieldSize, double energy, double depth, QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> v)
{
   // x is usually the field size, y the energy and z the value of the magnitude(scatter factor,TPS etc)
    QVector<double> xsub=x;
    QVector<double> ysub=y;
    QVector<double> zsub=z;


    for (int i=0; i<x.size();++i){
        xsub[i]=abs(x[i]-fieldSize); //subtracted 0.1 so nearest to 19.5 is 20 and not 19
    }

    qDebug() << xsub;
    qDebug() << x;
    auto minx = std::min_element(xsub.begin(),xsub.end());
    auto distx = std::distance(xsub.begin(),minx);
    qDebug() << x.at(distx);

    //finding the x limits for the interpolation
    double x1=0;
    double x2=0;
    int ix1=0;
    int ix2=0;
    if (fieldSize-x.at(distx)>0  ){
        x1=x.at(distx);
        x2=x.at(distx+1);
        ix1=distx;
        ix2=distx+1;
    }
    else if (fieldSize-x.at(distx)<0){
        x1=x.at(distx-1);
        x2=x.at(distx);
        ix1=distx-1;
        ix2=distx;
    }
    else{
        if (x.at(distx)==x.back()) {
            x1=x.at(distx-1);
            x2=x.at(distx);
            ix1=distx-1;
            ix2=distx;
        }
        else{
            x1=x.at(distx);
            x2=x.at(distx+1);
            ix1=distx;
            ix2=distx+1;
        }
    }



    //finding the y limits for the interpolation
    for (int i=0; i<y.size();++i){
        ysub[i]=abs(y[i]-energy); //subtracted 0.1 so nearest to 19.5 is 20 and not 19
    }
    auto miny = std::min_element(ysub.begin(),ysub.end());
    auto disty = std::distance(ysub.begin(),miny);
    qDebug() << y.at(disty);

    double y1=0;
    double y2=0;
    int iy1=0;
    int iy2=0;
    if (energy-y.at(disty)>0  ){
        y1=y.at(disty);
        y2=y.at(disty+1);
        iy1=disty;
        iy2=disty+1;
    }
    else if (energy-y.at(disty)<0){
        y1=y.at(disty-1);
        y2=y.at(disty);
        iy1=disty-1;
        iy2=disty;
    }
    else{
        if (y.at(disty)==y.back()) {
            y1=y.at(disty-1);
            y2=y.at(disty);
            iy1=disty-1;
            iy2=disty;
        }
        else{
            y1=y.at(disty);
            y2=y.at(disty+1);
            iy1=disty;
            iy2=disty+1;
        }

    }



    //finding the z limits for the interpolation
    for (int i=0; i<z.size();++i){
        zsub[i]=abs(z[i]-energy); //subtracted 0.1 so nearest to 19.5 is 20 and not 19
    }
    auto minz = std::min_element(zsub.begin(),zsub.end());
    auto distz = std::distance(zsub.begin(),minz);
    qDebug() << z.at(distz);

    double z1=0;
    double z2=0;
    int iz1=0;
    int iz2=0;
    if (depth-z.at(distz)>0  ){
        z1=z.at(distz);
        z2=z.at(distz+1);
        iz1=distz;
        iz2=distz+1;
    }
    else if (depth-z.at(distz)<0){
        z1=z.at(distz-1);
        z2=z.at(distz);
        iz1=distz-1;
        iz2=distz;
    }
    else{
        if (z.at(distz)==z.back()) {
            z1=z.at(distz-1);
            z2=z.at(distz);
            iz1=distz-1;
            iz2=distz;
        }
        else{
            z1=z.at(distz);
            z2=z.at(distz+1);
            iz1=distz;
            iz2=distz+1;
        }

    }


    //    Q11=(x1,y1);
    //    Q12=(x1,y2);
    //    Q21=(x2,y1);
    //    Q22=(x2,y2);

        qDebug() << x1 << x2;
        qDebug() << y1 << y2;
        qDebug() << z1 << z2;
    //success!!!

}
