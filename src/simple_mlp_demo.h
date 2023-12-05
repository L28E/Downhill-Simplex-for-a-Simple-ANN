#ifndef SIMPLE_MLP_DEMO_H_
#define SIMPLE_MLP_DEMO_H_

double get_output(double w[], double x);
double get_training_error(double w[]);
double get_validation_error(double w[]);
double get_test_error(double w[]);
void print_test_error(double w[]);
double compute_batch_error(int size, double output[], double input[], double output_min, double output_max, double w[]);

double training_size = 200;
double training_input_min = -1.470000E+01;
double training_input_max = 2.570000E+01;
double training_output_min = -1.497354E+00;
double training_output_max = 4.500000E+00;
double validation_size = 200;
double validation_input_min = -1.500000E+01;
double validation_input_max = 2.500000E+01;
double validation_output_min = -1.497357E+00;
double validation_output_max = 4.499999E+00;
double test_size = 200;
double test_input_min = -1.430000E+01;
double test_input_max = 2.530000E+01;
double test_output_min = -1.497358E+00;
double test_output_max = 4.499999E+00;
double training_input[] = { -1.470000E+01, -1.449698E+01, -1.429397E+01,
		-1.409095E+01, -1.388794E+01, -1.368492E+01, -1.348191E+01,
		-1.327889E+01, -1.307588E+01, -1.287286E+01, -1.266985E+01,
		-1.246683E+01, -1.226382E+01, -1.206080E+01, -1.185779E+01,
		-1.165477E+01, -1.145176E+01, -1.124874E+01, -1.104573E+01,
		-1.084271E+01, -1.063970E+01, -1.043668E+01, -1.023367E+01,
		-1.003065E+01, -9.827638E+00, -9.624623E+00, -9.421608E+00,
		-9.218593E+00, -9.015578E+00, -8.812563E+00, -8.609548E+00,
		-8.406533E+00, -8.203518E+00, -8.000503E+00, -7.797487E+00,
		-7.594472E+00, -7.391457E+00, -7.188442E+00, -6.985427E+00,
		-6.782412E+00, -6.579397E+00, -6.376382E+00, -6.173367E+00,
		-5.970352E+00, -5.767337E+00, -5.564322E+00, -5.361307E+00,
		-5.158291E+00, -4.955276E+00, -4.752261E+00, -4.549246E+00,
		-4.346231E+00, -4.143216E+00, -3.940201E+00, -3.737186E+00,
		-3.534171E+00, -3.331156E+00, -3.128141E+00, -2.925126E+00,
		-2.722111E+00, -2.519095E+00, -2.316080E+00, -2.113065E+00,
		-1.910050E+00, -1.707035E+00, -1.504020E+00, -1.301005E+00,
		-1.097990E+00, -8.949749E-01, -6.919598E-01, -4.889447E-01,
		-2.859296E-01, -8.291457E-02, 1.201005E-01, 3.231156E-01, 5.261307E-01,
		7.291457E-01, 9.321608E-01, 1.135176E+00, 1.338191E+00, 1.541206E+00,
		1.744221E+00, 1.947236E+00, 2.150251E+00, 2.353266E+00, 2.556281E+00,
		2.759296E+00, 2.962312E+00, 3.165327E+00, 3.368342E+00, 3.571357E+00,
		3.774372E+00, 3.977387E+00, 4.180402E+00, 4.383417E+00, 4.586432E+00,
		4.789447E+00, 4.992462E+00, 5.195477E+00, 5.398492E+00, 5.601508E+00,
		5.804523E+00, 6.007538E+00, 6.210553E+00, 6.413568E+00, 6.616583E+00,
		6.819598E+00, 7.022613E+00, 7.225628E+00, 7.428643E+00, 7.631658E+00,
		7.834673E+00, 8.037688E+00, 8.240704E+00, 8.443719E+00, 8.646734E+00,
		8.849749E+00, 9.052764E+00, 9.255779E+00, 9.458794E+00, 9.661809E+00,
		9.864824E+00, 1.006784E+01, 1.027085E+01, 1.047387E+01, 1.067688E+01,
		1.087990E+01, 1.108291E+01, 1.128593E+01, 1.148894E+01, 1.169196E+01,
		1.189497E+01, 1.209799E+01, 1.230101E+01, 1.250402E+01, 1.270704E+01,
		1.291005E+01, 1.311307E+01, 1.331608E+01, 1.351910E+01, 1.372211E+01,
		1.392513E+01, 1.412814E+01, 1.433116E+01, 1.453417E+01, 1.473719E+01,
		1.494020E+01, 1.514322E+01, 1.534623E+01, 1.554925E+01, 1.575226E+01,
		1.595528E+01, 1.615829E+01, 1.636131E+01, 1.656432E+01, 1.676734E+01,
		1.697035E+01, 1.717337E+01, 1.737638E+01, 1.757940E+01, 1.778241E+01,
		1.798543E+01, 1.818844E+01, 1.839146E+01, 1.859447E+01, 1.879749E+01,
		1.900050E+01, 1.920352E+01, 1.940653E+01, 1.960955E+01, 1.981256E+01,
		2.001558E+01, 2.021859E+01, 2.042161E+01, 2.062462E+01, 2.082764E+01,
		2.103065E+01, 2.123367E+01, 2.143668E+01, 2.163970E+01, 2.184271E+01,
		2.204573E+01, 2.224874E+01, 2.245176E+01, 2.265477E+01, 2.285779E+01,
		2.306080E+01, 2.326382E+01, 2.346683E+01, 2.366985E+01, 2.387286E+01,
		2.407588E+01, 2.427889E+01, 2.448191E+01, 2.468492E+01, 2.488794E+01,
		2.509095E+01, 2.529397E+01, 2.549698E+01, 2.570000E+01 };
double training_output[] = { 5.000009E-01, 5.000010E-01, 5.000012E-01,
		5.000014E-01, 5.000016E-01, 5.000019E-01, 5.000023E-01, 5.000027E-01,
		5.000031E-01, 5.000037E-01, 5.000044E-01, 5.000051E-01, 5.000060E-01,
		5.000071E-01, 5.000083E-01, 5.000098E-01, 5.000115E-01, 5.000135E-01,
		5.000158E-01, 5.000184E-01, 5.000211E-01, 5.000239E-01, 5.000258E-01,
		5.000251E-01, 5.000178E-01, 4.999946E-01, 4.999343E-01, 4.997891E-01,
		4.994508E-01, 4.986763E-01, 4.969186E-01, 4.929528E-01, 4.840563E-01,
		4.642810E-01, 4.211233E-01, 3.305039E-01, 1.546735E-01, -1.396518E-01,
		-5.287264E-01, -9.091542E-01, -1.185878E+00, -1.346838E+00,
		-1.428517E+00, -1.467060E+00, -1.484571E+00, -1.492327E+00,
		-1.495650E+00, -1.496964E+00, -1.497354E+00, -1.497298E+00,
		-1.497004E+00, -1.496557E+00, -1.495986E+00, -1.495295E+00,
		-1.494473E+00, -1.493503E+00, -1.492360E+00, -1.491015E+00,
		-1.489434E+00, -1.487574E+00, -1.485389E+00, -1.482819E+00,
		-1.479800E+00, -1.476252E+00, -1.472083E+00, -1.467187E+00,
		-1.461438E+00, -1.454689E+00, -1.446770E+00, -1.437481E+00,
		-1.426591E+00, -1.413831E+00, -1.398892E+00, -1.381415E+00,
		-1.360987E+00, -1.337138E+00, -1.309331E+00, -1.276958E+00,
		-1.239334E+00, -1.195698E+00, -1.145210E+00, -1.086951E+00,
		-1.019940E+00, -9.431407E-01, -8.554899E-01, -7.559285E-01,
		-6.434472E-01, -5.171417E-01, -3.762806E-01, -2.203805E-01,
		-4.928614E-02, 1.367525E-01, 3.370149E-01, 5.502664E-01, 7.747464E-01,
		1.008197E+00, 1.247932E+00, 1.490955E+00, 1.734096E+00, 1.974182E+00,
		2.208196E+00, 2.433425E+00, 2.647577E+00, 2.848853E+00, 3.035979E+00,
		3.208197E+00, 3.365225E+00, 3.507190E+00, 3.634553E+00, 3.748032E+00,
		3.848519E+00, 3.937018E+00, 4.014586E+00, 4.082288E+00, 4.141162E+00,
		4.192196E+00, 4.236310E+00, 4.274353E+00, 4.307092E+00, 4.335217E+00,
		4.359340E+00, 4.380005E+00, 4.397686E+00, 4.412801E+00, 4.425711E+00,
		4.436730E+00, 4.446130E+00, 4.454144E+00, 4.460973E+00, 4.466791E+00,
		4.471746E+00, 4.475965E+00, 4.479556E+00, 4.482612E+00, 4.485212E+00,
		4.487424E+00, 4.489306E+00, 4.490907E+00, 4.492268E+00, 4.493426E+00,
		4.494410E+00, 4.495248E+00, 4.495960E+00, 4.496565E+00, 4.497080E+00,
		4.497517E+00, 4.497889E+00, 4.498206E+00, 4.498475E+00, 4.498703E+00,
		4.498898E+00, 4.499063E+00, 4.499203E+00, 4.499323E+00, 4.499424E+00,
		4.499511E+00, 4.499584E+00, 4.499646E+00, 4.499699E+00, 4.499744E+00,
		4.499783E+00, 4.499815E+00, 4.499843E+00, 4.499867E+00, 4.499887E+00,
		4.499904E+00, 4.499918E+00, 4.499930E+00, 4.499941E+00, 4.499950E+00,
		4.499957E+00, 4.499964E+00, 4.499969E+00, 4.499974E+00, 4.499978E+00,
		4.499981E+00, 4.499984E+00, 4.499986E+00, 4.499988E+00, 4.499990E+00,
		4.499992E+00, 4.499993E+00, 4.499994E+00, 4.499995E+00, 4.499996E+00,
		4.499996E+00, 4.499997E+00, 4.499997E+00, 4.499998E+00, 4.499998E+00,
		4.499998E+00, 4.499999E+00, 4.499999E+00, 4.499999E+00, 4.499999E+00,
		4.499999E+00, 4.499999E+00, 4.499999E+00, 4.500000E+00, 4.500000E+00 };
double validation_input[] = { -1.500000E+01, -1.479899E+01, -1.459799E+01,
		-1.439698E+01, -1.419598E+01, -1.399497E+01, -1.379397E+01,
		-1.359296E+01, -1.339196E+01, -1.319095E+01, -1.298995E+01,
		-1.278894E+01, -1.258794E+01, -1.238693E+01, -1.218593E+01,
		-1.198492E+01, -1.178392E+01, -1.158291E+01, -1.138191E+01,
		-1.118090E+01, -1.097990E+01, -1.077889E+01, -1.057789E+01,
		-1.037688E+01, -1.017588E+01, -9.974874E+00, -9.773869E+00,
		-9.572864E+00, -9.371859E+00, -9.170854E+00, -8.969849E+00,
		-8.768844E+00, -8.567839E+00, -8.366834E+00, -8.165829E+00,
		-7.964824E+00, -7.763819E+00, -7.562814E+00, -7.361809E+00,
		-7.160804E+00, -6.959799E+00, -6.758794E+00, -6.557789E+00,
		-6.356784E+00, -6.155779E+00, -5.954774E+00, -5.753769E+00,
		-5.552764E+00, -5.351759E+00, -5.150754E+00, -4.949749E+00,
		-4.748744E+00, -4.547739E+00, -4.346734E+00, -4.145729E+00,
		-3.944724E+00, -3.743719E+00, -3.542714E+00, -3.341709E+00,
		-3.140704E+00, -2.939698E+00, -2.738693E+00, -2.537688E+00,
		-2.336683E+00, -2.135678E+00, -1.934673E+00, -1.733668E+00,
		-1.532663E+00, -1.331658E+00, -1.130653E+00, -9.296482E-01,
		-7.286432E-01, -5.276382E-01, -3.266332E-01, -1.256281E-01,
		7.537688E-02, 2.763819E-01, 4.773869E-01, 6.783920E-01, 8.793970E-01,
		1.080402E+00, 1.281407E+00, 1.482412E+00, 1.683417E+00, 1.884422E+00,
		2.085427E+00, 2.286432E+00, 2.487437E+00, 2.688442E+00, 2.889447E+00,
		3.090452E+00, 3.291457E+00, 3.492462E+00, 3.693467E+00, 3.894472E+00,
		4.095477E+00, 4.296482E+00, 4.497487E+00, 4.698492E+00, 4.899497E+00,
		5.100503E+00, 5.301508E+00, 5.502513E+00, 5.703518E+00, 5.904523E+00,
		6.105528E+00, 6.306533E+00, 6.507538E+00, 6.708543E+00, 6.909548E+00,
		7.110553E+00, 7.311558E+00, 7.512563E+00, 7.713568E+00, 7.914573E+00,
		8.115578E+00, 8.316583E+00, 8.517588E+00, 8.718593E+00, 8.919598E+00,
		9.120603E+00, 9.321608E+00, 9.522613E+00, 9.723618E+00, 9.924623E+00,
		1.012563E+01, 1.032663E+01, 1.052764E+01, 1.072864E+01, 1.092965E+01,
		1.113065E+01, 1.133166E+01, 1.153266E+01, 1.173367E+01, 1.193467E+01,
		1.213568E+01, 1.233668E+01, 1.253769E+01, 1.273869E+01, 1.293970E+01,
		1.314070E+01, 1.334171E+01, 1.354271E+01, 1.374372E+01, 1.394472E+01,
		1.414573E+01, 1.434673E+01, 1.454774E+01, 1.474874E+01, 1.494975E+01,
		1.515075E+01, 1.535176E+01, 1.555276E+01, 1.575377E+01, 1.595477E+01,
		1.615578E+01, 1.635678E+01, 1.655779E+01, 1.675879E+01, 1.695980E+01,
		1.716080E+01, 1.736181E+01, 1.756281E+01, 1.776382E+01, 1.796482E+01,
		1.816583E+01, 1.836683E+01, 1.856784E+01, 1.876884E+01, 1.896985E+01,
		1.917085E+01, 1.937186E+01, 1.957286E+01, 1.977387E+01, 1.997487E+01,
		2.017588E+01, 2.037688E+01, 2.057789E+01, 2.077889E+01, 2.097990E+01,
		2.118090E+01, 2.138191E+01, 2.158291E+01, 2.178392E+01, 2.198492E+01,
		2.218593E+01, 2.238693E+01, 2.258794E+01, 2.278894E+01, 2.298995E+01,
		2.319095E+01, 2.339196E+01, 2.359296E+01, 2.379397E+01, 2.399497E+01,
		2.419598E+01, 2.439698E+01, 2.459799E+01, 2.479899E+01, 2.500000E+01 };
double validation_output[] = { 5.000007E-01, 5.000008E-01, 5.000009E-01,
		5.000011E-01, 5.000013E-01, 5.000015E-01, 5.000018E-01, 5.000021E-01,
		5.000024E-01, 5.000029E-01, 5.000034E-01, 5.000040E-01, 5.000046E-01,
		5.000055E-01, 5.000064E-01, 5.000075E-01, 5.000088E-01, 5.000104E-01,
		5.000122E-01, 5.000142E-01, 5.000166E-01, 5.000192E-01, 5.000220E-01,
		5.000245E-01, 5.000259E-01, 5.000240E-01, 5.000138E-01, 4.999840E-01,
		4.999093E-01, 4.997329E-01, 4.993274E-01, 4.984088E-01, 4.963437E-01,
		4.917267E-01, 4.814660E-01, 4.588928E-01, 4.102401E-01, 3.097767E-01,
		1.194497E-01, -1.886825E-01, -5.798096E-01, -9.476804E-01,
		-1.208049E+00, -1.357509E+00, -1.433150E+00, -1.468953E+00,
		-1.485311E+00, -1.492603E+00, -1.495745E+00, -1.496991E+00,
		-1.497357E+00, -1.497295E+00, -1.497001E+00, -1.496558E+00,
		-1.495994E+00, -1.495312E+00, -1.494502E+00, -1.493547E+00,
		-1.492424E+00, -1.491105E+00, -1.489556E+00, -1.487738E+00,
		-1.485604E+00, -1.483099E+00, -1.480161E+00, -1.476713E+00,
		-1.472669E+00, -1.467927E+00, -1.462366E+00, -1.455849E+00,
		-1.448214E+00, -1.439271E+00, -1.428802E+00, -1.416554E+00,
		-1.402233E+00, -1.385503E+00, -1.365975E+00, -1.343204E+00,
		-1.316686E+00, -1.285848E+00, -1.250044E+00, -1.208556E+00,
		-1.160589E+00, -1.105272E+00, -1.041670E+00, -9.687915E-01,
		-8.856091E-01, -7.910895E-01, -6.842315E-01, -5.641151E-01,
		-4.299629E-01, -2.812091E-01, -1.175747E-01, 6.085721E-02, 2.535735E-01,
		4.595805E-01, 6.773795E-01, 9.049770E-01, 1.139935E+00, 1.379462E+00,
		1.620538E+00, 1.860065E+00, 2.095023E+00, 2.322620E+00, 2.540419E+00,
		2.746427E+00, 2.939143E+00, 3.117575E+00, 3.281209E+00, 3.429963E+00,
		3.564115E+00, 3.684231E+00, 3.791090E+00, 3.885609E+00, 3.968791E+00,
		4.041670E+00, 4.105272E+00, 4.160589E+00, 4.208556E+00, 4.250044E+00,
		4.285848E+00, 4.316686E+00, 4.343204E+00, 4.365975E+00, 4.385503E+00,
		4.402233E+00, 4.416554E+00, 4.428802E+00, 4.439271E+00, 4.448214E+00,
		4.455849E+00, 4.462366E+00, 4.467927E+00, 4.472669E+00, 4.476713E+00,
		4.480161E+00, 4.483099E+00, 4.485604E+00, 4.487738E+00, 4.489556E+00,
		4.491105E+00, 4.492425E+00, 4.493549E+00, 4.494506E+00, 4.495322E+00,
		4.496016E+00, 4.496608E+00, 4.497111E+00, 4.497540E+00, 4.497905E+00,
		4.498216E+00, 4.498481E+00, 4.498707E+00, 4.498899E+00, 4.499062E+00,
		4.499202E+00, 4.499320E+00, 4.499421E+00, 4.499507E+00, 4.499580E+00,
		4.499643E+00, 4.499696E+00, 4.499741E+00, 4.499779E+00, 4.499812E+00,
		4.499840E+00, 4.499864E+00, 4.499884E+00, 4.499901E+00, 4.499916E+00,
		4.499928E+00, 4.499939E+00, 4.499948E+00, 4.499956E+00, 4.499962E+00,
		4.499968E+00, 4.499973E+00, 4.499977E+00, 4.499980E+00, 4.499983E+00,
		4.499986E+00, 4.499988E+00, 4.499990E+00, 4.499991E+00, 4.499992E+00,
		4.499994E+00, 4.499995E+00, 4.499995E+00, 4.499996E+00, 4.499997E+00,
		4.499997E+00, 4.499998E+00, 4.499998E+00, 4.499998E+00, 4.499998E+00,
		4.499999E+00, 4.499999E+00, 4.499999E+00, 4.499999E+00, 4.499999E+00 };
double testing_input[] = { -1.430000E+01, -1.410101E+01, -1.390201E+01,
		-1.370302E+01, -1.350402E+01, -1.330503E+01, -1.310603E+01,
		-1.290704E+01, -1.270804E+01, -1.250905E+01, -1.231005E+01,
		-1.211106E+01, -1.191206E+01, -1.171307E+01, -1.151407E+01,
		-1.131508E+01, -1.111608E+01, -1.091709E+01, -1.071809E+01,
		-1.051910E+01, -1.032010E+01, -1.012111E+01, -9.922111E+00,
		-9.723116E+00, -9.524121E+00, -9.325126E+00, -9.126131E+00,
		-8.927136E+00, -8.728141E+00, -8.529146E+00, -8.330151E+00,
		-8.131156E+00, -7.932161E+00, -7.733166E+00, -7.534171E+00,
		-7.335176E+00, -7.136181E+00, -6.937186E+00, -6.738191E+00,
		-6.539196E+00, -6.340201E+00, -6.141206E+00, -5.942211E+00,
		-5.743216E+00, -5.544221E+00, -5.345226E+00, -5.146231E+00,
		-4.947236E+00, -4.748241E+00, -4.549246E+00, -4.350251E+00,
		-4.151256E+00, -3.952261E+00, -3.753266E+00, -3.554271E+00,
		-3.355276E+00, -3.156281E+00, -2.957286E+00, -2.758291E+00,
		-2.559296E+00, -2.360302E+00, -2.161307E+00, -1.962312E+00,
		-1.763317E+00, -1.564322E+00, -1.365327E+00, -1.166332E+00,
		-9.673367E-01, -7.683417E-01, -5.693467E-01, -3.703518E-01,
		-1.713568E-01, 2.763819E-02, 2.266332E-01, 4.256281E-01, 6.246231E-01,
		8.236181E-01, 1.022613E+00, 1.221608E+00, 1.420603E+00, 1.619598E+00,
		1.818593E+00, 2.017588E+00, 2.216583E+00, 2.415578E+00, 2.614573E+00,
		2.813568E+00, 3.012563E+00, 3.211558E+00, 3.410553E+00, 3.609548E+00,
		3.808543E+00, 4.007538E+00, 4.206533E+00, 4.405528E+00, 4.604523E+00,
		4.803518E+00, 5.002513E+00, 5.201508E+00, 5.400503E+00, 5.599497E+00,
		5.798492E+00, 5.997487E+00, 6.196482E+00, 6.395477E+00, 6.594472E+00,
		6.793467E+00, 6.992462E+00, 7.191457E+00, 7.390452E+00, 7.589447E+00,
		7.788442E+00, 7.987437E+00, 8.186432E+00, 8.385427E+00, 8.584422E+00,
		8.783417E+00, 8.982412E+00, 9.181407E+00, 9.380402E+00, 9.579397E+00,
		9.778392E+00, 9.977387E+00, 1.017638E+01, 1.037538E+01, 1.057437E+01,
		1.077337E+01, 1.097236E+01, 1.117136E+01, 1.137035E+01, 1.156935E+01,
		1.176834E+01, 1.196734E+01, 1.216633E+01, 1.236533E+01, 1.256432E+01,
		1.276332E+01, 1.296231E+01, 1.316131E+01, 1.336030E+01, 1.355930E+01,
		1.375829E+01, 1.395729E+01, 1.415628E+01, 1.435528E+01, 1.455427E+01,
		1.475327E+01, 1.495226E+01, 1.515126E+01, 1.535025E+01, 1.554925E+01,
		1.574824E+01, 1.594724E+01, 1.614623E+01, 1.634523E+01, 1.654422E+01,
		1.674322E+01, 1.694221E+01, 1.714121E+01, 1.734020E+01, 1.753920E+01,
		1.773819E+01, 1.793719E+01, 1.813618E+01, 1.833518E+01, 1.853417E+01,
		1.873317E+01, 1.893216E+01, 1.913116E+01, 1.933015E+01, 1.952915E+01,
		1.972814E+01, 1.992714E+01, 2.012613E+01, 2.032513E+01, 2.052412E+01,
		2.072312E+01, 2.092211E+01, 2.112111E+01, 2.132010E+01, 2.151910E+01,
		2.171809E+01, 2.191709E+01, 2.211608E+01, 2.231508E+01, 2.251407E+01,
		2.271307E+01, 2.291206E+01, 2.311106E+01, 2.331005E+01, 2.350905E+01,
		2.370804E+01, 2.390704E+01, 2.410603E+01, 2.430503E+01, 2.450402E+01,
		2.470302E+01, 2.490201E+01, 2.510101E+01, 2.530000E+01 };
double testing_output[] = { 5.000012E-01, 5.000014E-01, 5.000016E-01,
		5.000019E-01, 5.000022E-01, 5.000026E-01, 5.000031E-01, 5.000036E-01,
		5.000042E-01, 5.000050E-01, 5.000058E-01, 5.000068E-01, 5.000080E-01,
		5.000094E-01, 5.000110E-01, 5.000128E-01, 5.000150E-01, 5.000174E-01,
		5.000201E-01, 5.000228E-01, 5.000251E-01, 5.000259E-01, 5.000225E-01,
		5.000088E-01, 4.999715E-01, 4.998805E-01, 4.996692E-01, 4.991894E-01,
		4.981135E-01, 4.957173E-01, 4.904082E-01, 4.787192E-01, 4.532693E-01,
		3.991014E-01, 2.891007E-01, 8.552200E-02, -2.338145E-01, -6.245441E-01,
		-9.799866E-01, -1.226070E+00, -1.365995E+00, -1.436764E+00,
		-1.470398E+00, -1.485860E+00, -1.492799E+00, -1.495808E+00,
		-1.497006E+00, -1.497358E+00, -1.497294E+00, -1.497004E+00,
		-1.496567E+00, -1.496011E+00, -1.495340E+00, -1.494543E+00,
		-1.493606E+00, -1.492506E+00, -1.491215E+00, -1.489702E+00,
		-1.487928E+00, -1.485850E+00, -1.483415E+00, -1.480562E+00,
		-1.477220E+00, -1.473307E+00, -1.468725E+00, -1.463360E+00,
		-1.457083E+00, -1.449739E+00, -1.441150E+00, -1.431111E+00,
		-1.419383E+00, -1.405690E+00, -1.389714E+00, -1.371092E+00,
		-1.349404E+00, -1.324178E+00, -1.294874E+00, -1.260887E+00,
		-1.221539E+00, -1.176079E+00, -1.123687E+00, -1.063472E+00,
		-9.944883E-01, -9.157479E-01, -8.262465E-01, -7.249964E-01,
		-6.110701E-01, -4.836542E-01, -3.421124E-01, -1.860558E-01,
		-1.541498E-02, 1.694916E-01, 3.679014E-01, 5.785732E-01, 7.997813E-01,
		1.029347E+00, 1.264705E+00, 1.503015E+00, 1.741287E+00, 1.976533E+00,
		2.205918E+00, 2.426885E+00, 2.637266E+00, 2.835348E+00, 3.019902E+00,
		3.190177E+00, 3.345864E+00, 3.487043E+00, 3.614110E+00, 3.727706E+00,
		3.828647E+00, 3.917864E+00, 3.996346E+00, 4.065097E+00, 4.125102E+00,
		4.177309E+00, 4.222604E+00, 4.261808E+00, 4.295669E+00, 4.324863E+00,
		4.349994E+00, 4.371598E+00, 4.390149E+00, 4.406063E+00, 4.419702E+00,
		4.431385E+00, 4.441384E+00, 4.449939E+00, 4.457254E+00, 4.463507E+00,
		4.468849E+00, 4.473414E+00, 4.477312E+00, 4.480640E+00, 4.483481E+00,
		4.485907E+00, 4.487977E+00, 4.489743E+00, 4.491250E+00, 4.492536E+00,
		4.493634E+00, 4.494570E+00, 4.495368E+00, 4.496050E+00, 4.496631E+00,
		4.497126E+00, 4.497549E+00, 4.497910E+00, 4.498217E+00, 4.498479E+00,
		4.498703E+00, 4.498894E+00, 4.499057E+00, 4.499196E+00, 4.499314E+00,
		4.499415E+00, 4.499501E+00, 4.499574E+00, 4.499637E+00, 4.499690E+00,
		4.499736E+00, 4.499775E+00, 4.499808E+00, 4.499836E+00, 4.499860E+00,
		4.499881E+00, 4.499898E+00, 4.499913E+00, 4.499926E+00, 4.499937E+00,
		4.499946E+00, 4.499954E+00, 4.499961E+00, 4.499967E+00, 4.499972E+00,
		4.499976E+00, 4.499979E+00, 4.499982E+00, 4.499985E+00, 4.499987E+00,
		4.499989E+00, 4.499991E+00, 4.499992E+00, 4.499993E+00, 4.499994E+00,
		4.499995E+00, 4.499996E+00, 4.499996E+00, 4.499997E+00, 4.499997E+00,
		4.499998E+00, 4.499998E+00, 4.499998E+00, 4.499999E+00, 4.499999E+00,
		4.499999E+00, 4.499999E+00, 4.499999E+00, 4.499999E+00, 4.499999E+00 };

#endif /* SIMPLE_MLP_DEMO_H_ */