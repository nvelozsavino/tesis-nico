close all
clc;
min=1;
max=length(pasos);
minp=10;
maxp=length(pasos)-3;
fig=figure;

errorbar(pasos(min:max),alpha_mean(min:max)*180/pi,alpha_std(min:max)*180/pi,'kx'); hold on;
polinomio_alpha_vs_in=polyfit(pasos(minp:maxp),alpha_mean(minp:maxp)*180/pi,1);
alpha_vs_in=polyval(polinomio_alpha_vs_in,[pasos(min:max) 5.5]);
plot([pasos(min:max) 5.5],alpha_vs_in); hold off;
grid on;

title('Fase vs. Entrada Señal DC');
% xlabel('Entrada f_s_o_u_n_d_ (Hz)');
xlabel('Entrada V_D_A_C (V)');
ylabel('Fase \alpha (grados)');
% axis([0 350 0 160]);
it=floor(length(pasos)/2);
xt=pasos(it);
yt=alpha_vs_in(it)-20;
txt=text(xt,yt,['y = ',num2str(polinomio_alpha_vs_in(1)),'\cdotx + ',num2str(polinomio_alpha_vs_in(2))],...
    'BackgroundColor',[0.9 0.9 0.9]);
% save('../../archivos/tablas/alpha/señalDC1.mat','veces','numImagenes', 'pasos','alphas','alpha_mean','alpha_std','numeradores','denominadores','polinomios','polinomio_alpha_vs_in','alpha_vs_in');
hgsave('../../archivos/tablas/alpha/señalAC2.fig');