#ifndef BILINEARINTERP_H
#define BILINEARINTERP_H

#include <QVector>

//Since this interpolation calculation is very simple it doesn't need a thread to speed up the GUI
//See https://en.wikipedia.org/wiki/Bilinear_interpolation

class interp
{
public:
    interp();
    double bilinearInterp(double fieldSize, double energy, QVector<double> x, QVector<double> y, QVector<double> v);
    double trilinearInterp(double fieldSize, double energy, double depth, QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> v);

};

#endif // BILINEARINTERP_H
