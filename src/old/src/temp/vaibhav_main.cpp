#include "insilico/core.hpp"

#include <boost/numeric/odeint.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace insilico;
using namespace std;

class HH_Neuron : public Neuron {
 public:
  void ode_set(state_type &variables, state_type &dxdt,
               const double t, const unsigned index) {

//Variables for 1st block
  double RT = 20000.0,
    K1 = 0.000005,
    K2 = 0.0001,
    kr = 0.000175,
    kp = 0.03,
    ke = 0.006,
    L = 0.001000,
    zeta=0.85;    
//Variables for 3st block
  double er = 0.185,
    d1 = 0.00000013,
    d2=0.00000105,
    d3=0.000000943,
    d5=0.0000000823,
    a2=0.0000002,
    Be = 0.000150,
    Ke=0.000010,
    Ber=0.120000,
    Ker=0.001200,
    Bx=0.000050,
    Kx=0.0000002,
    k3=0.0000004,
    eta1=575.0,
    eta2=5.2,
    eta3=0.000045,
    CaT=0.000067;//ca2+ constants
  double GT =  100000.0,
    k_deg = 1.25,
    ka=0.017,
    kd=0.15,
    PIP2_T=50000.0,
    rr=10,
    delta=0.001234,
    Kc=0.0000004,
    alpha=0.00002781,
    vol=5.0*(pow(10,-16)),
    Na = 6.02232*(pow(10,23)); //G protein constants
//Variables for 2st block
  double rh,rho,RsE,RsT,lambda2,lambda1,m,Ca_er,beta,gamma,t_h,h_ss,wsi;


  int Rsp_index = engine::get_neuron_index(index, "Rsp");//Giving address
  int Rs_index = engine::get_neuron_index(index, "Rs");
  int G_index = engine::get_neuron_index(index, "G");
  int IP3_index = engine::get_neuron_index(index, "IP3");
  int PIP2_index = engine::get_neuron_index(index, "PIP2");
  int h_index = engine::get_neuron_index(index, "h");
  int Ca_index = engine::get_neuron_index(index, "Ca");
  
        double Rsp = variables[Rsp_index];//calling value
        double Rs = variables[Rs_index];
        double G = variables[G_index];
        double IP3 = variables[IP3_index];
        double PIP2 = variables[PIP2_index];
        double h = variables[h_index];
        double Ca = variables[Ca_index];

         //Ligand-Dynamics Parameters
         RsE = kr + ((kp*kr*K2 + kp*kr*L)/(ke*K1 + ke*L));
         RsE = RsE /(kr + (kp*L/(K1+L)) + ((kr*kp*K2 + kr*kp*L)/(ke*K1 +ke*L)));
         RsE = (RsE*zeta*RT) + ((1-zeta)*RT);
         lambda1 = -kp*L/(K1 +L);
         lambda2 = -kr - (ke*L/(K2 + L));
         RsT= (RsE + (((RT-RsE)/(lambda2 - lambda1))*(lambda2*exp(lambda1*t) - lambda1*exp(lambda2*t))))/RT;

         //G-protein Dynamics Parameters
         rh = (alpha)*(G)*(Ca/(Ca + Kc));
         rho = (L*Rs)/((zeta)*(RT)*(K1+L));

         //Ca-Dynamics Parameters
         wsi = (d2)*(IP3+d1)/(IP3+d3);
         t_h = 1/((a2)*(wsi + Ca));
         h_ss = wsi/(wsi + Ca);
         m = (IP3)*(Ca)/((d1 + IP3)*(d5 + Ca));
         beta = pow((1  +  ( (Ke*Be) / (pow((Ke + Ca),2)) )  +  ( (Kx*Bx) / (pow((Kx + Ca),2)) )  ),-1);
         gamma = pow((1  +  ( (Be) / (Ke + Ca) )  +  ( (Bx) / (Kx + Ca) )  ),-1);
         Ca_er = (Ker) * ((CaT)-(Ca/gamma))  /  (Ber*er);

         std::cout<<t/60<<"\t"<<G/100000<<"\t"<<IP3*1000000<<"\t"<<PIP2/50000<<"\t"<<Ca*1000000<<"\t"<<Ca_er*1000000<<"\n";// standard output


    dxdt[Rs_index] = (kr*RT) - ( Rs* (kr + (kp*L/(K1+L)) ) )   -   (kr*Rsp);//Defining diff. eq.
    dxdt[Rsp_index] = L * ( ((kp*Rs)/(K1+L)) - ((ke*Rsp)/(K2+L)) );
    
    dxdt[G_index] = ((ka)*(delta + rho)*(GT - G))  -  (kd*G);
    dxdt[IP3_index] = ((rh)*(1/(Na*vol))*(PIP2))  -  (k_deg*IP3);
    dxdt[PIP2_index] = -((rh+rr)*(PIP2))  -  ((rr)*(Na)*(vol)*(IP3))  +  ((rr)*(PIP2_T));
    dxdt[h_index] = (h_ss - h)/t_h;
    dxdt[Ca_index] = beta*(   ((er)*(Ca_er - Ca)*((eta1*(pow(m,3))*(pow(h,3))) + eta2))  -  ((eta3) * ((pow(Ca,2)) / (pow(k3,2) + pow(Ca,2))))   );
 

    
    engine::neuron_value(index, "Rs", Rs);
    engine::neuron_value(index, "Rsp", Rsp);
    engine::neuron_value(index, "G", G);
    engine::neuron_value(index, "IP3", IP3);
    engine::neuron_value(index, "PIP2", PIP2);
    engine::neuron_value(index, "h", h);
    engine::neuron_value(index, "Ca", Ca);

  }
};

int main(int argc, char **argv) {
  configuration::initialize(argc, argv);
  configuration::observe_header(true);    // optional
  configuration::observe_delimiter('\t'); // optional
  configuration::observe("Rs");
  configuration::observe("Rsp");
  configuration::observe("G");
  configuration::observe("IP3");
  configuration::observe("PIP2");
  configuration::observe("h");
  configuration::observe("Ca");

  engine::generate_neuron<HH_Neuron>();

  state_type variables = engine::get_variables();
  integrate_const(boost::numeric::odeint::runge_kutta4<state_type>(),
                  engine::driver(), variables,
                  0.0, 250.0, 0.05, configuration::observer());//Time limis from 0.0 - 150 unit with delT=0.05 

  configuration::finalize();
}
