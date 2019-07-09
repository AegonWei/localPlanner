//
// Created by ustb on 19-7-9.
//

#include "calKappa.h"


double trajectory_kappa(Node start_node, Node next_node){

    std::array<double, 3> start= {{start_node.x_, start_node.y_, 0.0 * PI / 180.0}};
    std::array<double, 3> end = {{next_node.x_, next_node.y_, 0.0 * PI / 180.0}};
    CubicPolynomial cubic(start, end);
    std::vector<std::vector<double >> set = cubic.computeFrenetCoordinates();
    std::vector<double> s = *(set.cbegin());
    std::vector<double> rho = *(set.cbegin()+1);
    std::vector<double> theta = *(set.cbegin()+2);

    std::vector<double> kappa_set;
    for (size_t i=0; i < (s.size()-1); i=i+5){
        double x0, x1,x2, y0, y1, y2, k1, k2, k3;
        x0 = s[i];
        y0 = rho[i];
        x1=s[i + 1];
        y1=rho[i + 1];
        x2=s[i + 2];
        y2=rho[i + 2];
        k1 = (x1 - x0)*(y2-2*y1+y0);
        k2 = (y1-y0)*(x2-2*x1+x0);
        k3 = pow(pow((x1-x0),2)+pow((y1-y0), 2), 1.5);

        if (k3 == 0.0) kappa_set.push_back(0.0);

        else kappa_set.push_back((k1 - k2) / k3);
    }

    double sum_kappa = 0.0;
    for (auto i:kappa_set){
        sum_kappa = sum_kappa + pow(i,2);
    }
    double mean_kappa = sum_kappa/kappa_set.size();

    return mean_kappa;

}