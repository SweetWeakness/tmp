#include <iostream>
#include <vector>
#include <cmath>


class Object{
protected:
    std::vector<double> params;
    virtual double getSquare() = 0;
    explicit Object(std::vector<double>& args): params(args) {}
};

class Triangle: Object{
public:
    explicit Triangle(std::vector<double>& points): Object(points) {}
    double getSquare() override{
        return fabs((params[0] - params[4]) * (params[3] - params[5]) -
        (params[2] - params[4]) * (params[1] - params[5])) / 2;
    }
};

class Rectangle: Object{
public:
    explicit Rectangle(std::vector<double>& points): Object(points) {}
    double getSquare() override{
        return fabs((params[0] - params[2]) * (params[1] - params[3]));
    }
};

class Circle: Object{
public:
    explicit Circle(std::vector<double>& points): Object(points) {}
    double getSquare() override{
        return M_PI * params[2] * params[2];
    }
};

int main(int argc, char *argv[]) {
    std::string type = argv[1];
    std::vector<double> params;
    for (int i = 2; i < argc; ++i){
        params.push_back(std::stod(argv[i]));
    }

    double out = 0;
    if (type == "Triangle"){
        out = Triangle(params).getSquare();
    }
    if (type == "Rectangle"){
        out = Rectangle(params).getSquare();
    }
    if (type == "Circle"){
        out = Circle(params).getSquare();
    }

    printf("The square is %f", out);
    return 0;
}