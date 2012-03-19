clear all;
close all;
clc;
data=load('sim7.mat');
x=data.sim7(:,1);
y=data.sim7(:,2);%*3/255;
xs=300;
xf=2101;
ymax=0.45;
ymin=0;
ts=x(xs);
tf=x(xf);
ci=mean(y(1:xs));
cf=mean(y(xf:length(y)));
stdi=std(y(1:xs));
stdf=std(y(xf:length(y)));

t=x;
plot(t,y,'k'); grid on;
axis([0 80 -0.08 0.5]);
% axis([0 522 0 50]);
xlabel ('Tiempo (s)');
ylabel ('Contraste');

ymin1=0.22;
ymax1=0.33;
ts1=x(1);
tf1=x(xs-1);

ymin2=0.31;
ymax2=0.42;
ts2=x(xf+1);
tf2=x(length(x));



title('Simulación de la evolución del contraste en el tiempo','FontWeight', 'bold','FontSize',14);
line([ts1 ts1 tf1 tf1 ts1],[ymin1 ymax1 ymax1 ymin1 ymin1],'Color','r','LineWidth',2);
line([ts ts tf tf ts],[ymin ymax ymax ymin ymin],'Color','b','LineWidth',2);
line([ts2 ts2 tf2 tf2 ts2],[ymin2 ymax2 ymax2 ymin2 ymin2],'Color','g','LineWidth',2);
txt1=text(10,-0.025,['Contraste Inicial: ', num2str(ci,'%.4f'), ' \pm ',num2str(stdi,'%.4f')], 'BackgroundColor',[1 1 1]);
txt2=text(10,-0.06,['Contraste Final:   ', num2str(cf,'%.4f'), ' \pm ',num2str(stdf,'%.4f')], 'BackgroundColor',[1 1 1]);
txt3=text((tf-ts)/2+ts,ymin,'Proceso de ajuste','HorizontalAlignment','center', 'BackgroundColor','b','FontWeight','bold','color','w');
txt4=text((tf1-ts1)/2+ts1,ymin1,'Sin Control','HorizontalAlignment','center', 'BackgroundColor','r','FontWeight','bold','color','w');
txt5=text((tf2-ts2)/2+ts2,ymin2,'Adaptado','HorizontalAlignment','center', 'BackgroundColor','g','FontWeight','bold','color','w');


