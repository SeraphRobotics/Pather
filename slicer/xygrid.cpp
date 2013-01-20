#include "xygrid.h"


/*
 *  The file uses a grid of the structure
 *   *-----y----->  row = Y
 *   | 0123
 *   | 4567
 *   x
 *   |
 *  \|/
 *   column = x
 *
 *  its stored as a Vector of length #x*#y where the value i,j is at #n*i+j
 *  it can be any type in the XYGrid but it is designed to be access by lengths as well as indecies
*/



template <class T>
XYGrid<T>::XYGrid():stepsize_(1.0),nx_(0),ny_(0)
{
}

// Constructs a null grid
template <class T>
XYGrid<T>::XYGrid(const XYGrid<T>& otherxygrid){
    stepsize_ = otherxygrid.stepsize_;
    data_ = otherxygrid.data_;
    nx_=otherxygrid.nx_;
    ny_=otherxygrid.ny_;
}
//Copy constructor
template <class T>
XYGrid<T>::XYGrid(int x, int y){
    nx_=x;
    ny_=y;
    data_ = QVector<T>(x*y);
    stepsize_=1.0;
}
//Creates a grid of size x,y of zeros
template <class T>
XYGrid<T>::XYGrid(int x, int y, float stepsize){
    nx_=x;
    ny_=y;
    data_ = QVector<T>(x*y);
    stepsize_=stepsize;
}
//Creates a grid of size x,y of zeros and sets stepsize
template <class T>
XYGrid<T>::XYGrid(float Lx, float Ly, float stepsize){
    nx_=(int) Lx/stepsize+1;
    ny_=(int) Ly/stepsize+1;
    data_ = QVector<T>(nx_*ny_);
    stepsize_=stepsize;
}
//Creats a grid with the ceiling of Lx/stepsize, Ly/stepsize and sets stepsize
template <class T>
XYGrid<T>::XYGrid(FAHVector3 min, FAHVector3 max,float stepsize) {
    FAHVector3 delta(min.sub(max));
    float x,y;
    x = abs(delta.x);
    y = abs(delta.y);
    nx_=(int) x/stepsize+1;
    ny_=(int) y/stepsize+1;
    data_ = QVector<T>(x*y);
    stepsize_=stepsize;
}
//Creates a grid of delta of the points in the X and Y dimensions
template <class T>
XYGrid<T>::XYGrid(FAHVector3 Delta, float stepsize) {
    float x,y;
    x = abs(Delta.x);
    y = abs(Delta.y);
    nx_=(int) x/stepsize+1;
    ny_=(int) y/stepsize+1;
    data_ = QVector<T>(x*y);
    stepsize_=stepsize;
}
//Creates a grid of delta of the points in the X and Y dimensions
template <class T>
XYGrid<T>::XYGrid(QVector<T> v, int rowSize){
    if(rowSize==0){XYGrid<T>();}
    else{
        ny_ = rowSize;
        nx_ = v.size()/rowSize;
        data_ = v;
        stepsize_=1.0;
    }
}
//Creates a grid from a Qvector and sets the rowSize
template <class T>
XYGrid<T>::XYGrid(QVector<T> v, int rowSize, float stepsize){
    data_=v;
    ny_=rowSize;
    nx_ = v.size()/ny_;
    stepsize_=stepsize;

}
//Overloaded constructor
template <class T>
XYGrid<T>::XYGrid(QByteArray barray,int rowSize,float stepsize) {}
//Loads form QByteArray
template <class T>
XYGrid<T>::XYGrid(QString csvfileLocation) {}
//Loads from CSV file


/// Save Data
template <class T>
QString XYGrid<T>::toCSV(){return "";}
template <class T>
QByteArray XYGrid<T>::toQByteArray() {return QByteArray();}


/// Data Set and return
template <class T>
void XYGrid<T>::setDim(int x, int y){
    QVector<T> newdata(x*y);
    int tempx=0,tempy=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if((i>nx_) or (j>ny_)){
                newdata[(y*i*j)]=T();
            }
            else{
                newdata[(y*i+j)]=at(i,j);
            }
        }
    }
    ny_=y;
    nx_=x;
    data_=newdata;
}
//Resets the dimensions of the array

template <class T>
void XYGrid<T>::setStepSize(float a){
    stepsize_=a;
}
//Sets the stepzie

template <class T>
float XYGrid<T>::stepSize() {return stepsize_;}
//Returns stepsize

template <class T>
bool XYGrid<T>::isNull() {return data_.isEmpty();}
//Returns true if Data is empty

template <class T>
FAHVector3 XYGrid<T>::getDimensions(){
    return FAHVector3(xDimension(),yDimension(),0);
}
//Returns a point of the dx, dy, 0

template <class T>
float XYGrid<T>::xDimension() {return nx_*stepsize_;}
//Returns x length

template <class T>
float XYGrid<T>::yDimension() {return ny_*stepsize_;}
//Returns y length



/// Data Access
template <class T>
QVector<T> XYGrid<T>::asVector(){
    return QVector<T>(&data_);
}
//Returns a copy of the data vector
template <class T>
const T XYGrid<T>::at(int I, int j){
    return T(data_[(ny*I+j)]);
}
//Returns an integer of the value at I,j

template <class T>
T XYGrid<T>::operator()(int I,int j){
    return data_[(ny*I+j)];
}
//Returns the interger at I,j


template <class T>
QList<T> XYGrid<T>::getValueRange(){
    QList<T> values;
    for(int i=0;i<data_.size();i++){
        if(!values.contains(data_.at(i))){values.append(data_[i]);}
    }
    return values;
}
//Returns a list of the values in the slice

template <class T>
XYGrid<T> XYGrid<T>::getValueGrid( T i){}
//Retruns a grid with only the points at the value. Null grid if value not in grid
