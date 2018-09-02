// Demo of sending data via temporary files.  The default is to send data to gnuplot directly
// through stdin.
//
// Compile it with:
//   g++ $(pkg-config --cflags eigen3) -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <map>
#include <vector>
#include <cmath>
#include <tuple>

#include <eigen3/Eigen/Dense>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;

    double x_o(0.26065415386350554), y_o(1.120152281839018), z_o(1.1811620467267077);
    double qx_o(0.2027327210011219), qy_o(0.8379558468003546), qz_o(-0.4854024102825173), qw_o(-0.1453063754296597);


    std::vector< std::tuple< double, double, double > > cv = {
        std::make_tuple( 0.3039117303449046, -0.681122181469394, -0.666115814889822),
        std::make_tuple(-0.7961692910257856, -0.071759424882784, -0.600803675858583),
        std::make_tuple( 0.1709394113037584, -0.981919007720502, -0.081331215750972),
        std::make_tuple(-0.9293228491429482, -0.368618314008413, -0.021899838791887)
    };

	std::vector< std::tuple< double, double, double, double, double, double> > xy_vec_B;
    std::vector<Eigen::Vector3d> frust_vec;
	for(double alpha=0; alpha<4; alpha++) {
		xy_vec_B.push_back(std::make_tuple(x_o, y_o, z_o, 3*std::get<0>(cv[alpha]), 3*std::get<1>(cv[alpha]), 3*std::get<2>(cv[alpha])));

        frust_vec.push_back({std::get<0>(cv[alpha]), std::get<1>(cv[alpha]), std::get<2>(cv[alpha])});
	}


    double theta = std::acos( frust_vec[0].dot(frust_vec[2]) / ( frust_vec[0].norm()*frust_vec[2].norm() ) );
    std::cout << "Theta: " << theta << "(" << (theta * 180) / 3.14 << ")" << std::endl;

    std::random_device rd;                                                                                    
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(std::cos(theta), 1.0);                                          
    double rand_z = distribution(generator);
    std::cout << "Random Z: " << rand_z << std::endl;

    std::uniform_real_distribution<double> distribution1(0, 2 * 3.14);
    double rand_phi = distribution1(generator);
    std::cout << "Random phi: " << rand_phi << std::endl;

    std::tuple<double, double, double> random_vec(std::sqrt(1-(rand_z*rand_z)) * std::cos(rand_phi),std::sqrt(1-(rand_z*rand_z)) * std::sin(rand_phi),rand_z);
    std::cout << "(" << std::get<0>(random_vec) << ", "
                     << std::get<1>(random_vec) << ", "
                     << std::get<2>(random_vec) << ")" << std::endl;
    xy_vec_B.push_back(std::make_tuple(x_o, y_o, z_o, std::get<0>(random_vec), std::get<1>(random_vec), std::get<2>(random_vec)));

	gp << "set xrange [-3:4]\nset yrange [-3:4]\n set zrange [-1:6]\n";
    gp << "set hidden3d\n"; 
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "splot"  << gp.file1d(xy_vec_B, "frust_camera.dat") << "with vectors title 'vec'" << std::endl;
    //<< gp.file1d(xy_pts_A) << "with lines title 'cubic'," << std::endl;
		//<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;

}
