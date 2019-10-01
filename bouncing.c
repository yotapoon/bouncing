
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double a = 0.01;
double e = 1.0;
double g = 1.0;//ãKäiâªÇ≥ÇÍÇΩèdóÕâ¡ë¨ìx
double A = 1.0;
double T = 100.0;//ÉVÉ~ÉÖÉåÅ[ÉVÉáÉìèIóπéûçè
int step_gif = 100;//gifÉAÉjÉÅÅ[ÉVÉáÉìÇÃÉXÉeÉbÉvêî

double Uniform(void){//0Ç©ÇÁ1ÇÃàÍólóêêîÇê∂ê¨
    return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}

int main(void){
    double omega = 1.0;
    FILE *fp_position,*fp_setting,*fp_bouncing;//ÉtÉ@ÉCÉãÇÃê∂ê¨
    char name_position[256],name_bouncing[256];
    sprintf(name_position,"position(omega=%lf).txt",omega);//à∂Ç∑ÇÈÉtÉ@ÉCÉã
    sprintf(name_bouncing,"bouncing(omega=%lf).txt",omega);
    if((fp_position = fopen(name_position,"w"))==NULL){
        printf("file_check open error\n");
    }
    if((fp_setting = fopen("setting.txt","w"))==NULL){//gifê∂ê¨éûÇ…ïKóvÇ»ÉpÉâÉÅÅ[É^Çäiî[Ç∑ÇÈ
        printf("file open error\n");
    }
    if((fp_bouncing = fopen(name_bouncing,"w"))==NULL){
        printf("file_bouncing open error\n");
    }
    double x,y,u,v;
    double t=0.0,dt=0.0001,trec=0.0,dtrec = (double)T/(double)step_gif;//dtrecÇÕgifê∂ê¨ÇÃéûä‘ä‘äu
    fprintf(fp_setting,"A = %lf\n",A);
    fprintf(fp_setting,"n1 = %d\ndt = %lf\n",step_gif,dtrec);
    fprintf(fp_setting,"file_position = \"position(omega=%lf)\"\n",omega);
    fprintf(fp_setting,"file_bouncing = \"bouncing(omega=%lf)\"\n",omega);
    
    srand((unsigned) time(NULL));
    y = 0.0;
    x = Uniform();
    v = Uniform();
    
    printf("set up ok\n");

    while(t <= T){
        t += dt;
        x += v*dt-0.5*g*dt*dt;
        v += -g*dt;
        y = A*sin(omega*t);
        u = A*omega*cos(omega*t);
        
        if( x-y < a){//collision
            v += e*(u-v);
            fprintf(fp_bouncing,"%lf %lf\n",t,x);
        }
        //ó±éqÇÃà íuÇÃèoóÕ
        if((t > trec)&&(t < T)){
            printf("t = %lf x = %lf y = %lf\n",t,x,y);
            trec += dtrec;
            fprintf(fp_position,"0.0 %lf %lf\n",x,y);
            fprintf(fp_position,"\n\n");
        }
    }
    
    fclose(fp_position);
    fclose(fp_bouncing);
    fclose(fp_setting);
    return 0;
}
