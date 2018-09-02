
#include <vector>
#include <cmath>
#include <tuple>
// #include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;
    std::vector<double> x, y, z;

    double x_o(0.26065415386350554), y_o(1.120152281839018), z_o(1.1811620467267077);

    std::vector<double> bl{0.26065415386350554, 1.120152281839018, 1.1811620467267077, 0.3039117303449046, -0.681122181469394, -0.6661158148898227};
    std::vector<double> br{0.26065415386350554, 1.120152281839018, 1.1811620467267077, -0.7961692910257856, -0.07175942488278492, -0.6008036758585832};
    std::vector< std::tuple<double,double,double,double,double,double> > vec;

    for (int i = 0; i < 3 ; i++) {
        vec.push_back(std::make_tuple(x_o, y_o, z_o, 1, 2, 3));
    }

    for (int i = 0; i <10; i++) {
        x.push_back(i);
        y.push_back(i);
        z.push_back(i);
    }

    gp << std::setprecision(3);
    gp << "set xrange [-30:30]\n";
    gp << "set yrange [-30:30]\n";
    gp << "set zrange [0:60]\n";
    gp << "set xlabel \"x\"\n";
    gp << "set ylabel \"y\"\n";
    gp << "set zlabel \"z\"\n";
//    gp << "set format y \"%.1f\"\n";
//    gp << "set term png size 720,480 font \"FreeSerif,12\"\n";
//    gp << "set output \"3d.png\"\n";
//    gp << "set hidden3d\n";
    gp << "set view 60, 60, 1, 1.5\n";
    gp << "splot " << gp.file2d(vec, "record") << "with vectors arrowstyle 3\n";
//    gp.send(std::make_tuple(bl, br));
//    gp.send1d(boost::make_tuple(x,y,z));    
    return 0;
}
