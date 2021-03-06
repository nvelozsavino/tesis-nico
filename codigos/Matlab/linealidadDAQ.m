clc;
close all;
clear all;
l=load ('../../archivos/tablas/linealidadDAC.txt');
x=l(:,1);
y=l(:,2)*1000;
e=((l(:,3)))*1000;
p=polyfit(x,y,1);
yp=polyval(p,x);
hf=figure;
errorbar(x,y,e); grid on;
xlabel('Voltaje de entrada (V)');
ylabel('Voltaje de salida (mV)');
title('Gr�fica de linealidad V_o_u_t vs V_i_n (Etapa amplificaci�n y filtrado de la se�al AC)','FontWeight','bold');
hold on;
plot(x,yp, 'k');
it=floor(length(x)/2);
xt=-2;%x(it);
yt=-20;%y(it)-20;
txt=text(xt,yt,['V_o_u_t = ',num2str(p(1)),'mV/V\cdotV_i_n - ',num2str(abs(p(2))),'mV'],...
    'BackgroundColor',[0.9 0.9 0.9]);
axis([-10 10 -50 50]);
hgsave('../../archivos/tablas/linealidadDAQ.fig');
saveas(hf,'../../documentos/tesis/imagenes/linealidadDAQ.png');
