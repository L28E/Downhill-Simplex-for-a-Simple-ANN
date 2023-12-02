#ifndef DEMO_MLP_H_
#define DEMO_MLP_H_

double get_output(double weights[], double vds, double vgs);
double get_batch_error(double current[], double voltage[], double weights[]);

/*
 * I'm using a uniform grid distribution where V_{DS} and V_{GS} are the same vectors
 * the sweep of V_{GS} is nested in the sweep of V_{DS} 
 */

int training_size = 16;
int validation_size = 14;

double training_voltage[] = { -1.000E-01, -1.500E-02, 7.000E-02, 1.550E-01,
		2.400E-01, 3.250E-01, 4.100E-01, 4.950E-01, 5.800E-01, 6.650E-01,
		7.500E-01, 8.350E-01, 9.200E-01, 1.005E-03, 1.090E-03, 1.175E-03 };

double training_current[] = { 2.346E-12, 1.583E-11, 1.850E-10, 2.014E-09,
		1.765E-08, 1.060E-07, 4.531E-07, 1.545E-06, 3.982E-06, 7.484E-06,
		1.126E-05, 1.485E-05, 1.809E-05, 2.096E-05, 2.346E-05, 2.563E-05,
		3.516E-13, 3.519E-13, 3.713E-12, 4.508E-11, 5.141E-10, 4.814E-09,
		3.040E-08, 1.239E-07, 3.661E-07, 8.158E-07, 1.409E-06, 2.029E-06,
		2.604E-06, 3.114E-06, 3.555E-06, 3.933E-06, 1.814E-13, 5.856E-13,
		5.693E-12, 6.868E-11, 7.992E-10, 7.865E-09, 5.454E-08, 2.552E-07,
		9.158E-07, 2.491E-06, 4.916E-06, 7.641E-06, 1.027E-05, 1.264E-05,
		1.474E-05, 1.656E-05, 3.721E-13, 9.163E-13, 7.815E-12, 9.279E-11,
		1.073E-09, 1.041E-08, 7.062E-08, 3.277E-07, 1.206E-06, 3.546E-06,
		7.792E-06, 1.313E-05, 1.855E-05, 2.358E-05, 2.809E-05, 3.209E-05,
		5.670E-13, 1.243E-12, 9.841E-12, 1.156E-10, 1.331E-09, 1.275E-08,
		8.489E-08, 3.885E-07, 1.417E-06, 4.138E-06, 9.139E-06, 1.585E-05,
		2.324E-05, 3.052E-05, 3.725E-05, 4.333E-05, 7.670E-13, 1.570E-12,
		1.182E-11, 1.378E-10, 1.580E-09, 1.499E-08, 9.832E-08, 4.450E-07,
		1.610E-06, 4.652E-06, 1.019E-05, 1.764E-05, 2.604E-05, 3.469E-05,
		4.310E-05, 5.099E-05, 9.685E-13, 1.897E-12, 1.378E-11, 1.598E-10,
		1.812E-09, 1.708E-08, 1.108E-07, 4.968E-07, 1.784E-06, 5.109E-06,
		1.110E-05, 1.912E-05, 2.820E-05, 3.764E-05, 4.703E-05, 5.610E-05,
		1.170E-12, 2.223E-12, 1.574E-11, 1.778E-10, 2.027E-09, 1.899E-08,
		1.221E-07, 5.440E-07, 1.941E-06, 5.514E-06, 1.189E-05, 2.039E-05,
		3.001E-05, 4.003E-05, 5.007E-05, 5.989E-05, 1.372E-12, 2.550E-12,
		1.769E-11, 1.954E-10, 2.222E-09, 2.074E-08, 1.325E-07, 5.869E-07,
		2.082E-06, 5.875E-06, 1.259E-05, 2.150E-05, 3.156E-05, 4.205E-05,
		5.259E-05, 6.296E-05, 1.648E-12, 2.853E-12, 1.858E-11, 2.119E-10,
		2.401E-09, 2.233E-08, 1.420E-07, 6.260E-07, 2.210E-06, 6.198E-06,
		1.321E-05, 2.248E-05, 3.291E-05, 4.380E-05, 5.474E-05, 6.553E-05,
		1.882E-12, 3.172E-12, 2.011E-11, 2.261E-10, 2.565E-09, 2.380E-08,
		1.507E-07, 6.620E-07, 2.327E-06, 6.491E-06, 1.377E-05, 2.335E-05,
		3.411E-05, 4.533E-05, 5.661E-05, 6.775E-05, 2.116E-12, 3.491E-12,
		2.164E-11, 2.398E-10, 2.716E-09, 2.515E-08, 1.588E-07, 6.952E-07,
		2.435E-06, 6.759E-06, 1.428E-05, 2.413E-05, 3.518E-05, 4.669E-05,
		5.826E-05, 6.970E-05, 2.478E-12, 3.860E-12, 2.255E-11, 2.525E-10,
		2.857E-09, 2.641E-08, 1.663E-07, 7.262E-07, 2.534E-06, 7.005E-06,
		1.474E-05, 2.485E-05, 3.615E-05, 4.792E-05, 5.974E-05, 7.143E-05,
		2.784E-12, 4.213E-12, 2.380E-11, 2.650E-10, 2.989E-09, 2.760E-08,
		1.734E-07, 7.553E-07, 2.627E-06, 7.235E-06, 1.517E-05, 2.551E-05,
		3.704E-05, 4.903E-05, 6.108E-05, 7.299E-05, 3.091E-12, 4.566E-12,
		2.505E-11, 2.758E-10, 3.115E-09, 2.873E-08, 1.802E-07, 7.829E-07,
		2.715E-06, 7.449E-06, 1.557E-05, 2.612E-05, 3.786E-05, 5.006E-05,
		6.231E-05, 7.441E-05, 3.398E-12, 4.919E-12, 2.631E-11, 2.868E-10,
		3.235E-09, 2.981E-08, 1.866E-07, 8.091E-07, 2.798E-06, 7.651E-06,
		1.595E-05, 2.668E-05, 3.863E-05, 5.101E-05, 6.344E-05, 7.572E-05 };

double validation_voltage[] = { -5.000E-03, 8.000E-02, 1.650E-01, 2.500E-01,
		3.350E-01, 4.200E-01, 5.050E-01, 5.900E-01, 6.750E-01, 7.600E-01,
		8.450E-01, 9.300E-01, 1.015E+00, 1.100E+00 };

double validation_current[] = { 1.173E-13, 1.316E-12, 1.603E-11, 1.837E-10,
		1.732E-09, 1.098E-08, 4.434E-08, 1.284E-07, 2.816E-07, 4.823E-07,
		6.910E-07, 8.843E-07, 1.055E-06, 1.203E-06, 7.876E-13, 7.982E-12,
		9.637E-11, 1.107E-09, 1.054E-08, 6.939E-08, 3.135E-07, 1.109E-06,
		2.970E-06, 5.763E-06, 8.846E-06, 1.180E-05, 1.446E-05, 1.681E-05,
		1.168E-12, 1.072E-11, 1.279E-10, 1.460E-09, 1.368E-08, 8.813E-08,
		3.944E-07, 1.417E-06, 4.037E-06, 8.604E-06, 1.424E-05, 1.991E-05,
		2.517E-05, 2.990E-05, 1.545E-12, 1.338E-11, 1.584E-10, 1.798E-09,
		1.663E-08, 1.052E-07, 4.649E-07, 1.656E-06, 4.680E-06, 1.000E-05,
		1.695E-05, 2.453E-05, 3.197E-05, 3.887E-05, 1.922E-12, 1.597E-11,
		1.879E-10, 2.124E-09, 1.944E-08, 1.212E-07, 5.301E-07, 1.872E-06,
		5.238E-06, 1.111E-05, 1.879E-05, 2.735E-05, 3.610E-05, 4.462E-05,
		2.297E-12, 1.854E-11, 2.153E-10, 2.426E-09, 2.205E-08, 1.360E-07,
		5.899E-07, 2.068E-06, 5.732E-06, 1.206E-05, 2.032E-05, 2.954E-05,
		3.907E-05, 4.852E-05, 2.672E-12, 2.111E-11, 2.407E-10, 2.705E-09,
		2.444E-08, 1.495E-07, 6.442E-07, 2.244E-06, 6.171E-06, 1.289E-05,
		2.163E-05, 3.138E-05, 4.148E-05, 5.157E-05, 3.048E-12, 2.368E-11,
		2.639E-10, 2.960E-09, 2.662E-08, 1.618E-07, 6.936E-07, 2.402E-06,
		6.561E-06, 1.363E-05, 2.277E-05, 3.295E-05, 4.352E-05, 5.410E-05,
		3.364E-12, 2.473E-11, 2.858E-10, 3.192E-09, 2.861E-08, 1.730E-07,
		7.386E-07, 2.546E-06, 6.911E-06, 1.428E-05, 2.377E-05, 3.433E-05,
		4.528E-05, 5.626E-05, 3.719E-12, 2.671E-11, 3.045E-10, 3.405E-09,
		3.044E-08, 1.834E-07, 7.799E-07, 2.676E-06, 7.228E-06, 1.487E-05,
		2.467E-05, 3.555E-05, 4.683E-05, 5.814E-05, 4.074E-12, 2.870E-11,
		3.225E-10, 3.602E-09, 3.214E-08, 1.930E-07, 8.182E-07, 2.796E-06,
		7.517E-06, 1.540E-05, 2.548E-05, 3.664E-05, 4.821E-05, 5.980E-05,
		4.459E-12, 2.977E-11, 3.394E-10, 3.787E-09, 3.372E-08, 2.020E-07,
		8.539E-07, 2.908E-06, 7.784E-06, 1.589E-05, 2.622E-05, 3.764E-05,
		4.945E-05, 6.129E-05, 4.837E-12, 3.136E-11, 3.560E-10, 3.959E-09,
		3.521E-08, 2.105E-07, 8.874E-07, 3.012E-06, 8.032E-06, 1.634E-05,
		2.690E-05, 3.854E-05, 5.058E-05, 6.264E-05, 5.215E-12, 3.296E-11,
		3.702E-10, 4.124E-09, 3.663E-08, 2.185E-07, 9.192E-07, 3.110E-06,
		8.264E-06, 1.676E-05, 2.753E-05, 3.938E-05, 5.162E-05, 6.388E-05 };

#endif /* DEMO_MLP_H_ */
