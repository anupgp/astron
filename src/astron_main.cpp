// Global header files

#include "boost/numeric/odeint.hpp"
#include "include/new_insilico.hpp"
#include "stoch_euler_integrator.hpp"

#include "data_types.hpp"
#include "global_variables.hpp"
// #include "presynaptic_neuron.hpp"
#include "astrocyte.hpp"
#include "atp_synapse.hpp"
#include "glutamate_synapse.hpp"

namespace gvars=astron::globals;

int main(int argc, char **argv) {

  newinsilico::initialize(argc, argv); 
  newinsilico::set_write_this_interval(true);
  newinsilico::set_observe_step_interval(20);
  // newinsilico::set_observe_step_interval(200); // save results after each n steps
  // --------
  newinsilico::observe("ca_cyt");
  newinsilico::observe("ca_er");
  newinsilico::observe("ip3_cyt");
  newinsilico::observe("glu_ext");
  newinsilico::observe("ip3r_lr_openprob");
  newinsilico::observe("pmca_ca_cyt_flux");
  newinsilico::observe("syt45_krrelrate_glu");
  newinsilico::observe("syt45_ffrelrate_glu");
  newinsilico::observe("syt45_totalrelrate_glu");
  // // ---------
  newinsilico::observe("syt45_krreltime_glu");
  newinsilico::observe("syt45_ffreltime_glu");
  newinsilico::observe("syt45_reltime_glu");
  // // ----------
  newinsilico::observe("syt45_vkdoc_glu");
  newinsilico::observe("syt45_vkrel_glu");
  newinsilico::observe("syt45_vkend_glu");
  newinsilico::observe("syt45_vkacd_glu");
  newinsilico::observe("syt45_vfmob_glu");
  newinsilico::observe("syt45_vfrel_glu");
  newinsilico::observe("syt45_vfend_glu");
  newinsilico::observe("syt45_vfacd_glu");
  // -----------
  newinsilico::observe("syt45_relflag_glu");
  newinsilico::observe("syt45_krrelflag_glu");
  newinsilico::observe("syt45_ffrelflag_glu");
  // newinsilico::generate_neuron<presynaptic_neuron>(1);  
  newinsilico::generate_neuron<astrocyte>(1);  
  newinsilico::generate_synapse<atp_synapse>(1);  
  newinsilico::generate_synapse<glutamate_synapse>(1);  

  state_type variables = newinsilico::get_variables();
  state_type noise = newinsilico::get_noise();
  // when using boost integrator
  // for (auto el:variables)
  //   std::cout << el << " ";
  // integrate_const(boost::numeric::odeint::runge_kutta4<state_type>(), 
  // 		  newinsilico::driver(), variables,
  //                 0.0, 200.0, gvars::DELTA_T, newinsilico::observer());
  // integrate_const(boost::numeric::odeint::euler<state_type>(), 
  // 		  newinsilico::driver(), variables,
  //                 0.0, 105.0, gvars::DELTA_T, newinsilico::observer());

  // std::cout << noise.size() << std::endl;
  // std::cout << variables.size() << std::endl;
  // for (auto el: variables){
  //   std::cout << el << " ";
  // }
  // std::cout << std::endl;
  // for (auto el: noise){
  //   std::cout << el << " ";
  // }
  // when using custom stochastic integrator (Euler-Maruyama method)
  double tstart = 0.0;
  double tstop = 300.0;
  // double tstop = 300.0;
  stochastic::integrate_const(stochastic::euler::explicit_euler<state_type>(),
  			    newinsilico::driver(), variables, noise,
  			    tstart,tstop, gvars::DELTA_T, newinsilico::observer());
  newinsilico::finalize();
}
