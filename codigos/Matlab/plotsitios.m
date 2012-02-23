close all
clc;
min=1;
max=length(pasos);
fig=figure;
errorbar(pasos(min:max),alpha_mean(min:max)*180/pi,alpha_std(min:max)*180/pi,'kx'); hold on;
polinomio_alpha_vs_in=polyfit(pasos(min:max),alpha_mean(min:max)*180/pi,1);
alpha_vs_in=polyval(polinomio_alpha_vs_in,pasos(min:max));
% plot(pasos(min:max),alpha_vs_in); hold off;
grid on;

title('Fase vs. Entrada Señal AC');
xlabel('Entrada \alpha (grados)');
ylabel('Fase \alpha (grados)');


save('../../archivos/tablas/alpha/señalAC1.mat','veces','numImagenes', 'pasos','alphas','alpha_mean','alpha_std','numeradores','denominadores','cosine_alphas','polinomios','polinomio_alpha_vs_in','alpha_vs_in');
hgsave('../../archivos/tablas/alpha/señalAC1.fig')
