clear all;
close all;
clc;

load('control2.mat');
x=data(:,1);
y=data(:,2)*3/255;
xs=166;
xf=5140;


yimin=min(y(1:xs-1));
yimax=max(y(1:xs-1));
ypmin=min(y(xs:xf));
ypmax=max(y(xs:xf));
yamin=min(y(xf+1:length(y)));
yamax=max(y(xf+1:length(y)));

ymin=ypmin-0.02;
ymax=ypmax+0.05;
ts=x(xs)/10;
tf=x(xf)/10;

ymin1=yimin-0.05;
ymax1=yimax+0.02;
ts1=x(1)/10;
tf1=x(xs-1)/10;

ymin2=yamin-0.05;
ymax2=yamax+0.02;
ts2=x(xf+1)/10;
tf2=x(length(x))/10;


ci=mean(y(1:xs));
cf=mean(y(xf:length(y)));
stdi=std(y(1:xs))/sqrt(length(y(1:xs)));
stdf=std(y(xf:length(y)))/sqrt(length(y(xf:length(y))));


t=x/10;

ymina=min([0 ymin-0.1 ymin1 ymin2]);
ymaxa=0.5;%max([ymax ymax1 ymax2])+0.5;

xmina=x(1)/10;
xmaxa=x(length(x))/10;

plot(t,y,'k'); grid on;
axis([xmina xmaxa ymina ymaxa]);
% axis([0 522 0 50]);
xlabel ('Tiempo (s)');
ylabel ('Contraste');





title('Contrast Evolution ','FontWeight', 'bold','FontSize',14);
line([ts1 ts1 tf1 tf1 ts1],[ymin1 ymax1 ymax1 ymin1 ymin1],'Color','r','LineWidth',2);
line([ts ts tf tf ts],[ymin ymax ymax ymin ymin],'Color','b','LineWidth',2);
line([ts2 ts2 tf2 tf2 ts2],[ymin2 ymax2 ymax2 ymin2 ymin2],'Color','g','LineWidth',2);
txt1=text(100,ymina+2*((ymin-ymina)/4),['Initial Contrast: ', num2str(ci,'%.3f'), ' \pm ',num2str(stdi,'%.3f')], 'BackgroundColor',[1 1 1]);
txt2=text(100,ymina+1*((ymin-ymina)/4),['Final Contrast:   ', num2str(cf,'%.3f'), ' \pm ',num2str(stdf,'%.3f')], 'BackgroundColor',[1 1 1]);
txt3=text((tf-ts)/2+ts,ymin,'Adjust Process','HorizontalAlignment','center', 'BackgroundColor','b','FontWeight','bold','color','w');
% txt4=text((tf1-ts1)/2+ts1,ymin1,'Sin Control','HorizontalAlignment','center', 'BackgroundColor','r','FontWeight','bold','color','w');
% txt5=text((tf2-ts2)/2+ts2,ymin2,'Adaptado','HorizontalAlignment','center', 'BackgroundColor','g','FontWeight','bold','color','w');


mejora=((cf/ci)-1)*100