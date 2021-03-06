/*
 * Copyrigtht 2020 Georgios Karagiannis
 *
 * This file is part of 'Variance Reduced Replica Exchange Stochastic Gradient
 * Langevin Dynamics' (VRRESGLD).
 *
 * VRRESGLD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3 of the License.
 *
 * VRRESGLD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VRRESGLD.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Georgios Karagiannis
 * Assistant Professor in Statistics
 * Department of Mathematical Sciences, University of Durham
 * Stockton Road, Durham DH1 3LE, UK
 *
 * Telephone: +44 (0) 1913342718
 *
 * Email: georgios.karagiannis@durham.ac.uk
 *
 * Contact email: georgios.stats@gmail.com
 *
 * URL: http://www.maths.dur.ac.uk/~mffk55
 *
 * URL: https://github.com/georgios-stats
*/


/*
 * SGLD PARAMETERS
 */

typedef struct {
	double eta_1 ;
	double tau_1 ;
	double eta_2 ;
	double tau_2 ;
	int sig2hat_rep ;
	int gain_sig2hat_t0 ;
	double gain_sig2hat_c0 ;
	int subsample_type ;
	double Fscl ;
	int sig2hat_update_rate ;
} struct_are_sgld_parameters ;

void alloc_are_sgld_parameters(struct_are_sgld_parameters **) ;

void set_are_sgld_parameters(struct_are_sgld_parameters *) ;

void print_are_sgld_parameters(struct_are_sgld_parameters *) ;

void destroy_are_sgld_parameters(struct_are_sgld_parameters *) ;

/*
 * SUB-DATA
 */

typedef struct {
	struct_data *data ;
	int en_ysub ;
	int *I_ysub ;
} struct_are_sgld_subdata ;

void alloc_are_sgld_subdata(struct_are_sgld_subdata **, struct_data *, int) ;

void sample_are_sgld_subdata(struct_are_sgld_subdata *,
							struct_data *data,
							struct_are_sgld_parameters *) ;

void set_external_are_sgld_parameters(struct_are_sgld_parameters *, int , char *[]) ;

void print_are_sgld_subdata(struct_are_sgld_subdata *) ;

void destroy_are_sgld_subdata(struct_are_sgld_subdata *) ;

/*
 * GRADIENT ESTIMATOR
 */

void comp_are_sgld_grad_log_lik_estimate(double *  ,
										struct_are_sgld_subdata * ,
										struct_random_parameters*  ,
										struct_fixed_parameters*  ) ;

void comp_are_sgld_udpate_random_parameters(struct_are_sgld_subdata * ,
                                            struct_random_parameters*  ,
                                            struct_random_parameters* ,
                                            struct_fixed_parameters*  ,
                                            struct_are_sgld_parameters *,
                                            double *,double *,double *,double *) ;

/*
 * Compute log likelihood estimate
 */

double  comp_are_sgld_log_lik_estimate(struct_are_sgld_subdata *,
									struct_random_parameters* ,
									struct_fixed_parameters* ) ;

/*
 * Compute the stochastisity correction term
 */

double comp_are_sgld_gain_sig2hat(int , struct_are_sgld_parameters *) ;

double comp_are_sgld_sig2tilde(struct_are_sgld_subdata *,
								struct_random_parameters* ,
								struct_random_parameters* ,
								struct_fixed_parameters* ,
								struct_are_sgld_parameters *,
								struct_are_sgld_subdata *)  ;

void comp_are_sgld_sig2hat(double *,
									double ,
									double ) ;


/*
 * Compute the Metropolis Hastings
 */

void comp_are_sgld_acceptance_ratio(double *, double *,
										struct_are_sgld_subdata *,
										struct_random_parameters* ,
										struct_random_parameters* ,
										struct_fixed_parameters* ,
										struct_are_sgld_parameters *,
										double ) ;



