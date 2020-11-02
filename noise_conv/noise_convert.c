#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef struct wave_noise_t
{
    double width_usec;
    double noise_val;
} wave_noise_t;

wave_noise_t noise[] = {{20.0 , 3.0},
                        {80.0 , 4.6}
};


double ftau (double tau1)
{
    return ((8.252e-6)*pow((double)tau1,3)) - (0.001536*pow((double)tau1,2)) + (0.1108*(double)tau1) + 1.313;
    
}


/**
 * The following empirically derived function of tau (sub-pulse width) allows us to obtain the equivalent
noise-power value for a waveform from the one measured with another waveform.
○ N2 = f(tau2)/f(tau1) * N1, where N1 and N2 are the noise powers measured with waveforms 1 and
2, respectively, and tau1 and tau2 are the widths of waveforms 1 and 2, respectively.
○ f(tau) = ​ 8.252e-6*tau^3 – 0.001536*tau^2 + 0.1108*tau + 1.313
*/
double noise_convert (double n1, double tau1, double tau2)
{
    double n2=0.0;
    fprintf(stdout," tau1:%g        -         tau2:%g\n",tau1,tau2);
    fprintf(stdout,"ftau1:%g        -        ftau2:%g\n",ftau(tau1),ftau(tau2));
    
    n2 = (ftau(tau2)/ftau(tau1)) * n1;
    return n2;
}


void graph_results()
{
    FILE* cmd;
    
    cmd= popen("graph -Y \"noise-power(linear)\" -X \"tau(usec)\" -C -m 3 -T ps noise.data > plot.ps" ,"r");
    pclose(cmd);
    
    cmd = popen("graph -Y \"noise-power(linear)\" -X \"tau(usec)\" -C -m 3 -T png noise.data > plot.png" ,"r");
    pclose(cmd);
    
}

    

int main(int argc,char**argv)
{

    FILE* outfd;
    outfd = fopen("noise.data", "w");
    double cur_wave=noise[0].width_usec;
    double n1 = noise[0].noise_val;
    double tau_step=10.0;
    
    fprintf(stdout,"tau1\t\tn1\n");
    while(cur_wave <= noise[1].width_usec)
    {
        double tau1= cur_wave;
        cur_wave+=tau_step;
        double tau2= cur_wave;
        double n2 = noise_convert(n1,tau1,tau2);
        fprintf(outfd,"%0.4g\t\t%0.4g\n",tau1,n1);
        n1=n2;
    }
    fclose(outfd);
    graph_results();
    return(0);
}
