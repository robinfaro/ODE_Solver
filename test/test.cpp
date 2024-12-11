#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <gtest/gtest.h>


#include "../src/ForwardEuler.h"
#include "../src/OdeSolver.h"
#include "../src/RungeKutta.h"
#include "../src/Function.h"
#include "../src/AdamBashforth.h"
#include "../src/AdamMoulton.h"
#include "../src/BDF.h"
#include "../src/MultiStep.h"
#include "../src/NewtonMethod.h"
#include "../src/AdamBashforthOneStep.h"
#include "../src/AdamBashforthTwoSteps.h"
#include "../src/AdamBashforthThreeSteps.h"
#include "../src/AdamBashforthFourSteps.h"
#include "../src/BackwardEuler.h"


// **************************** Vector function tests *******************************

// Set up function for vector function test
class VectorODETest : public ::testing::Test {
    protected:
        void SetUp() override {
            std::vector<std::vector<std::string>> function_combination = {{"+1_6_1", "0", "+1_6_1"}, {"+1_1_1", "-1_6_1", "0"}};
            std::vector<std::vector<std::string>> derivative_combination = {{"0", "+1_7_1"}, {"-1_7_1", "0"}};
            function.SetFunctionCombination(function_combination);
            function.SetDerivativeCombination(derivative_combination);
        }
        double initial_time = 0;
        double final_time = 1.0;
        double step_size = 0.1;
        Function function;
};


// Vector function test 

TEST_F(VectorODETest, ForwardEuler) {
    Eigen::VectorXd initial_condition(2);
    initial_condition(0) = 1;
    initial_condition(1) = 0;
    ForwardEuler method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();

    Eigen::MatrixXd expected(2, 11);
    expected << 
        1.000000, 1.000000, 1.000000, 1.001000, 1.003983, 1.009914, 1.019698, 1.034178, 1.054107, 1.080137, 1.112799, // y1 values
        0.000000, -0.100000, -0.190017, -0.270150, -0.340698, -0.402154, -0.455203, -0.500708, -0.539704, -0.573380, -0.603061; // y2 values

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(VectorODETest, RK4) {
    Eigen::VectorXd initial_condition(2);
    initial_condition(0) = 1;
    initial_condition(1) = 0;
    Eigen::VectorXd b(4);
    b << 1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0;
    Eigen::VectorXd c(4);
    c << 0, 0.5, 0.5, 1;
    Eigen::MatrixXd a(4, 4);
    a << 0, 0, 0, 0,
         0.5, 0, 0, 0,
         0, 0.5, 0, 0,
         0, 0, 1, 0;
    RungeKutta method(step_size, initial_time, final_time, initial_condition, function, a, b, c);

    Eigen::MatrixXd approximations = method.Solve();

    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0001665972309022, 1.0013282001538013, 1.0044599127395124, 1.0104973370103312, 1.0203175639544333, 1.0347210435984937, 1.0544146089718227, 1.0799959132880477, 1.111939520775678, 1.150584869443273, // y1 values
             0.0, -0.0950083300352802, -0.1801330842168526, -0.2556720178652363, -0.3221164262191257, -0.38014376857174277, -0.43060748124373477, -0.4745241115682504, -0.5130579510566569, -0.5475033670759601, -0.5792650736367019; // y2 values

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));

}

TEST_F(VectorODETest, AdamBashforth1) {
    Eigen::VectorXd initial_condition(2);
    initial_condition(0) = 1;
    initial_condition(1) = 0;
    AdamBashforthOneStep method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0, 1.0, 1.0009983341664683, 1.0039833616408873, 1.0099136078402549, 1.0196982038463, 1.0341779191599847, 1.0541070771691567, 1.080136632859106, 1.112798678683588, // y1 values
             0.0, -0.1, -0.190016658335172, -0.27014972525581105, -0.3406975380063239, -0.40215403993954757, -0.45520284686315277, -0.5007084199082792, -0.5397044431005086, -0.573379541727472, -0.6030605140506342; // y2 values
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));   
}

TEST_F(VectorODETest, AdamBashforth2){
    Eigen::MatrixXd initial_condition(2, 2);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;
    initial_condition(0, 1) = 1;
    initial_condition(1, 1) = -0.1;

    AdamBashforthTwoSteps method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0, 1.0, 1.0022462518745536, 1.0074650624422936, 1.0165520805724275, 1.0303306115047404, 1.0495276809317398, 1.07475854858046, 1.1065124470877892, 1.1451402198574336, // y1 values
             0.0, -0.1, -0.1850249875029758, -0.260216258716058, -0.32615863203779316, -0.3835293377971789, -0.43319598308573043, -0.47619287670377497, -0.513704968852397, -0.5470498378198352, -0.577657455548342; // y2 values
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(VectorODETest, AdamBashforth3){
    Eigen::MatrixXd initial_condition(2, 3);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;
    initial_condition(0, 1) = 1;
    initial_condition(1, 1) = -0.1;
    initial_condition(0, 2) = 1;
    initial_condition(1, 2) = -0.19;

    AdamBashforthThreeSteps method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0, 1.0, 1.0019134738190643, 1.0072428756012093, 1.0161921063266308, 1.0297702408450544, 1.048707469587677, 1.073598485670409, 1.104925785344492, 1.1430334458169862, // y1 values 
                0.0, -0.1, -0.190016658335172, -0.26524949215250754, -0.3313043867701284, -0.388923764580378, -0.438860471753074, -0.4821837737051939, -0.5200592199840398, -0.553787364978879, -0.5847819044530954; // y2 values

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));

}

TEST_F(VectorODETest, AdamBashforth4){
    Eigen::MatrixXd initial_condition(2, 4);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;
    initial_condition(0, 1) = 1;
    initial_condition(1, 1) = -0.1;
    initial_condition(0, 2) = 1;
    initial_condition(1, 2) = -0.19;
    initial_condition(0, 3) = 1;
    initial_condition(1, 3) = -0.27;

    AdamBashforthFourSteps method(step_size, initial_time, final_time, initial_condition, function);

    Eigen::MatrixXd approximations = method.Solve();

    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0, 1.0, 1.0009983341664683, 1.0053847839694439, 1.0142285947154728, 1.0271282222691414, 1.0455802269067191, 1.0700340853885817, 1.1009112879157057, 1.1386234462925102, // y1 values
                0.0, -0.1, -0.190016658335172, -0.27014972525581105, -0.3361036882298029, -0.39361485605874136, -0.4434601174044845, -0.48648008020204325, -0.5241146451995188, -0.5575131662818774, -0.5881264219438975; // y2 values
            
    ASSERT_TRUE(approximations.isApprox(expected, 1e-2));
}

TEST_F(VectorODETest, BackwardEuler){
    Eigen::MatrixXd initial_condition(2, 1);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;

    BackwardEuler method(step_size, initial_time, final_time, initial_condition, function);

    Eigen::MatrixXd approximations = method.Solve();

    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0009884496697705, 1.0039243491559324, 1.0097182680284233, 1.0192142280435652, 1.0331727162819297, 1.0522550784695492, 1.0770095223064808, 1.107858937656511, 1.145090714991844, 1.188848715004749, // y1 values
                0.0, -0.09011550330229423, -0.17064100513838135, -0.24206081127508972, -0.30504039984858117, -0.36041511761635386, -0.4091763781238025, -0.45245556163068423, -0.4915058463082971, -0.5276822268446671, -0.5624199998643524; // y2 values

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));

}

TEST_F(VectorODETest, AdamMoulton3){
    Eigen::MatrixXd initial_condition(2, 3);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;
    initial_condition(0, 1) = 1;
    initial_condition(1, 1) = -0.1;
    initial_condition(0, 2) = 1;
    initial_condition(1, 2) = -0.19;

    Eigen::VectorXd beta(4);
    beta << 5.0/12.0, 2.0/3.0, -1.0/12.0, 0.0;
    AdamMoulton adam_moulton(step_size, initial_time, final_time, initial_condition, function, beta);

    Eigen::MatrixXd approximations = adam_moulton.Solve();

    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0, 1.0, 1.002108119536361, 1.0071852402328516, 1.0160767875800603, 1.029592557942348, 1.0484483797582755, 1.073250419276222, 1.1044811872314901, 1.1424874200599402, // y1 values
                0.0, -0.1, -0.190016658335172, -0.26537847779082924, -0.33154687048596454, -0.3892035664476135, -0.439205179086107, -0.48257270316948675, -0.5204757623153272, -0.5542148900029359, -0.5852017405755656; // y2 values
            
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));

}

TEST_F(VectorODETest, BDF1){
    Eigen::MatrixXd initial_condition(2, 1);
    initial_condition(0, 0) = 1;
    initial_condition(1, 0) = 0;

    Eigen::VectorXd alpha(2);
    alpha << 1.0, 1.0;

    BDF bdf(step_size, initial_time, final_time, initial_condition, function, alpha);

    Eigen::MatrixXd approximations = bdf.Solve();

    Eigen::MatrixXd expected(2, 11);
    expected << 1.0, 1.0009884496697705, 1.0039243491559324, 1.0097182680284233, 1.0192142280435652, 1.0331727162819297, 1.0522550784695492, 1.0770095223064808, 1.107858937656511, 1.145090714991844, 1.188848715004749, // y1 values
                0.0, -0.09011550330229423, -0.17064100513838135, -0.24206081127508972, -0.30504039984858117, -0.36041511761635386, -0.4091763781238025, -0.45245556163068423, -0.4915058463082971, -0.5276822268446671, -0.5624199998643524; // y2 values

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

// **************************** Scalar function tests *******************************

// Set up function for scalar function test
class ScalarODETest : public ::testing::Test {
protected:
    void SetUp() override {
        std::vector<std::vector<std::string>> function_combination = {{"+1_3_-1", "1_2_1"}};
        std::vector<std::vector<std::string>> derivative_combination = {{"-1_1_1"}};
        function.SetFunctionCombination(function_combination);
        function.SetDerivativeCombination(derivative_combination);
    }
    double initial_time = 0;
    double final_time = 2.0;
    double step_size = 0.1;
    Function function;

};

TEST_F(ScalarODETest, ForwardEuler) {
    Eigen::MatrixXd initial_condition(1, 1);
    initial_condition(0) = 0.0; 
    ForwardEuler method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.388490399958772014, 0.5629116687298343, 0.7215639791503203, 
                0.863673338375136, 0.9892913303920218, 1.0991007128969277, 1.194198821947805, 
                1.2759077188570365, 1.3456280116467356, 1.4047429989224027, 1.4545592334549142, 
                1.4962762068809048, 1.5309745029450776, 1.5596153293316928, 1.583046421796517, 
                1.6020110947340638, 1.617158477228651, 1.6290538117135698, 1.638188219952978;
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, RK4) {
    Eigen::MatrixXd initial_condition(1, 1);
    initial_condition(0) = 0.0; 
    Eigen::VectorXd b(4);
    b << 1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0;
    Eigen::VectorXd c(4);
    c << 0, 0.5, 0.5, 1;
    Eigen::MatrixXd a(4, 4);
    a << 0, 0, 0, 0,
         0.5, 0, 0, 0,
         0, 0.5, 0, 0,
         0, 0, 1, 0;
    RungeKutta method(step_size, initial_time, final_time, initial_condition, function, a, b, c);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.19452361355176226, 0.3764184202146631, 0.5437708163551102, 
                0.6955221892676562, 0.8314092300472722, 0.9518080266149732, 
                1.0575457718904404, 1.1497249399321867, 1.229581976886883, 
                1.2983854600589206, 1.3573693143277177, 1.4076932380013931, 
                1.450422427082619, 1.4865200545578507, 1.516847644862736, 
                1.5421699809651503, 1.5631623389942326, 1.5804186707982457, 
                1.5944599125095782, 1.6057419588721633;

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, AdamBashforth1) {
    Eigen::MatrixXd initial_condition(1, 1);
    initial_condition(0) = 0.0; 
    AdamBashforthOneStep method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.388490399958772014, 0.5629116687298343, 0.7215639791503203, 
                0.863673338375136, 0.9892913303920218, 1.0991007128969277, 1.194198821947805, 
                1.2759077188570365, 1.3456280116467356, 1.4047429989224027, 1.4545592334549142, 
                1.4962762068809048, 1.5309745029450776, 1.5596153293316928, 1.583046421796517, 
                1.6020110947340638, 1.617158477228651, 1.6290538117135698, 1.638188219952978;
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, AdamBashforth2){
    Eigen::MatrixXd initial_condition(1, 2);
    initial_condition(0, 0) = 0.0;
    initial_condition(0, 1) = 0.2;
    AdamBashforthTwoSteps method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.3827355993815802, 0.5504469833801316, 0.7020944758779889, 
                0.8375107133667632, 0.9571969073259609, 1.0620985004163788, 
                1.1534110694568764, 1.2324348658535036, 1.3004765738675146, 
                1.3587888505574583, 1.4085369893187796, 1.450783665958509, 
                1.4864850269936922, 1.516493460423271, 1.5415639911375258, 
                1.56236237759501, 1.5794737490592388, 1.593411116624183, 
                1.6046234014293617;
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, AdamBashforth3){
    Eigen::MatrixXd initial_condition(1, 3);
    initial_condition(0, 0) = 0.0;
    initial_condition(0, 1) = 0.2;
    initial_condition(0, 2) = 0.3884;
    AdamBashforthThreeSteps method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.3884, 0.5548106326598123, 0.7056934730148678, 0.8406272649219949, 0.960139631078364, 1.0650728493016435, 1.1565374218536233,
                1.2357624824905629, 1.3040058793700633, 1.3624904104404907, 1.4123661773042349, 1.4546906424554022, 1.4904209469249723, 1.5204139266758374, 1.5454306713336203, 
                1.5661434764930962, 1.5831438199015535, 1.5969505269844781, 1.6080176491675773;
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, AdamBashforth4){
    Eigen::MatrixXd initial_condition(1, 4);
    initial_condition(0, 0) = 0.0;
    initial_condition(0, 1) = 0.2;
    initial_condition(0, 2) = 0.3884;
    initial_condition(0, 3) = 0.5629;
    AdamBashforthFourSteps method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.388490399958772014, 0.5629116687298343, 0.7132936261668191, 0.8484022546698009, 0.9674120424199768, 1.0720006777341435, 1.1629617729331596,
              1.2416979173861296, 1.3094176387853176, 1.367400418789901, 1.4167921719394583, 1.4586682467400607, 1.493984983601297, 1.5236027340581628, 1.5482803266375746, 
              1.5686886762617578, 1.5854162752041387, 1.5989793076227423, 1.6098289117261018;

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, BackwardEuler){
    Eigen::MatrixXd initial_condition(1, 1);
    initial_condition(0) = 0.0;
    BackwardEuler method(step_size, initial_time, final_time, initial_condition, function);
    Eigen::MatrixXd approximations = method.Solve();

    Eigen::MatrixXd expected(1, 21);
    expected << 0, 0.1887, 0.3640, 0.5247, 0.6701, 0.8004, 0.9161, 1.0183, 1.1079, 1.1861, 1.2540, 1.3128, 1.3635, 1.4071, 1.4443, 1.4761, 
    1.5031, 1.5258, 1.5449, 1.5609, 1.5741;

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}


TEST_F(ScalarODETest, AdamMoulton3){
    Eigen::MatrixXd initial_condition(1, 3);
    initial_condition(0, 0) = 0.0;
    initial_condition(0, 1) = 0.2;
    initial_condition(0, 2) = 0.3884;
    Eigen::VectorXd beta(4);
    beta << 5.0/12.0, 2.0/3.0, -1.0/12.0, 0.0;
    AdamMoulton adam_moulton(step_size, initial_time, final_time, initial_condition, function, beta);
    Eigen::MatrixXd approximations = adam_moulton.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.388490399958772014, 0.5553362714222025, 
                0.7064615781460778, 0.841638172534208, 0.9612847695655495, 
                1.0662629226539693, 1.1577002180456144, 1.2368497324242431, 
                1.3049898111766953, 1.36335907263503, 1.4131184197845157, 
                1.4553320129743563, 1.4909606581857284, 1.5208628061633502, 
                1.5457998684944942, 1.5664437076669442, 1.583384970558056, 
                1.597141479363603, 1.6081662447693483;

    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}

TEST_F(ScalarODETest, BDF1){
    Eigen::MatrixXd initial_condition(1, 1);
    initial_condition(0) = 0.0;
    Eigen::VectorXd alpha(2);
    alpha << 1.0, 1.0;
    BDF bdf(step_size, initial_time, final_time, initial_condition, function, alpha);
    Eigen::MatrixXd approximations = bdf.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.1887084750059145, 0.3640285579051505, 0.5246598194213946, 
                0.6700696643634951, 0.8003670649487918, 0.9161371226125106, 
                1.0182788325796095, 1.107868681449309, 1.186057366682921, 
                1.253997901366658, 1.3127994350999854, 1.3635003122529195, 
                1.4070545939079822, 1.4443274879832952, 1.4760963530906126, 
                1.5030549616309807, 1.525819482238543, 1.5449351958956796, 
                1.5608833402383078, 1.5740877289415809;

    ASSERT_TRUE(approximations.isApprox(expected, 1e-1));
}

TEST_F(ScalarODETest, BDF3){
    Eigen::MatrixXd initial_condition(1, 3);
    initial_condition(0, 0) = 0.0;
    initial_condition(0, 1) = 0.2;
    initial_condition(0, 2) = 0.3884;
    Eigen::VectorXd alpha(4);
    alpha << 11.0/6.0, 3.0, -3.0/2.0, 1.0/3.0;
    BDF bdf(step_size, initial_time, final_time, initial_condition, function, alpha);
    Eigen::MatrixXd approximations = bdf.Solve();
    Eigen::MatrixXd expected(1, 21);
    expected << 0.0, 0.2, 0.388490399958772014, 0.5587340241332085, 0.7107029943312788, 0.8457149706425615, 0.9649954476059777, 1.0696455947336936, 1.1608045515832637, 
                1.2396958737495392, 1.3075831161625928, 1.365705338703422, 1.415229145413565, 1.4572235580035846, 1.4926517829524633, 1.5223726638627837, 1.5471468451004382, 
                1.56764448888212478, 1.5844559572828016, 1.5980963727660995, 1.6090177087207407;
    ASSERT_TRUE(approximations.isApprox(expected, 1e-4));
}