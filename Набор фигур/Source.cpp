#include<cmath>
#include<iostream>
#include<memory>
#include<vector>
#include<sstream>
#include<iomanip>
using namespace std;

class Figure {
public:
	virtual string Name()const = 0;

	virtual double Perimeter()const = 0;

	virtual double Area()const = 0;
};

class Triangle : public Figure {
public:
	Triangle(const double& a_, const double&b_, const double& c_)
		: a(a_),b(b_),c(c_){}

	string Name() const override {
		return "TRIANGLE";
	}

	double Perimeter() const override {
		return a + b + c;
	}

	double Area() const override {
		double p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
private:
	double a;
	double b;
	double c;
};

class Rect : public Figure {
public:
	Rect(const double& width_, const double& height_)
		:width(width_), height(height_) {}
	string Name() const override {
		return "RECT";
	}

	double Perimeter() const override {
		return 2 * (width + height);
	}

	double Area() const override {
		return width * height;
	}
private:
	double width;
	double height;
};

class Circle : public Figure {
public:
	Circle(const double& r_)
		:r(r_) {}
	string Name() const override {
		return"CIRCLE";
	}

	double Perimeter() const override {
		return 2 * 3.14 * r;
	}

	double Area() const override {
		return 3.14 * r * r;
	}
private:
	double r;
};

shared_ptr<Figure> CreateFigure(istringstream& is){
	string FigureType;
	is >> FigureType;
	if (FigureType == "RECT")
	{
		double width, height;
		is >> width >> height;
		return make_shared<Rect>(width, height);
	}
	else if (FigureType == "CIRCLE")
	{
		double r;
		is >> r;
		return make_shared<Circle>(r);
	}
	else 
	{
		double a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}
}

int main()
{
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	//system("pause");
	return 0;
}