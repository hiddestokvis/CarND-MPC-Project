#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

const int latency = 2;

struct Solution {
  vector<double> x;
  vector<double> y;
  vector<double> psi;
  vector<double> v;
  vector<double> cte;
  vector<double> epsi;
  vector<double> delta;
  vector<double> a;
};

class MPC {
 public:
  MPC();
  double deg2rad(double deg);

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  Solution Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);

  double delta_prev {0};
  double a_prev {0.1};
};

#endif /* MPC_H */
