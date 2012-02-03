close all;
clear all;
clc;
blue=load('../C++/archivos/canon_b.dat');
red=load('../C++/archivos/canon_r.dat');
green=load('../C++/archivos/canon_g.dat');
lmin=100e-9;
lmax=1000e-9;
N=1000;

dl=(lmax-lmin)/N;

k=1.3806488e-23;
h=6.62606957e-34;
c=3e8;

T=3000;



x=(((1:N)-1)*dl)+lmin;

xr=1e-9*red(:,1)/10;
xg=1e-9*green(:,1)/10;
xb=1e-9*blue(:,1)/10;

yr=red(:,2);
yg=green(:,2);
yb=blue(:,2);


yri=interp1(xr,yr,x,'spline',0);
ygi=interp1(xg,yg,x,'spline',0);
ybi=interp1(xb,yb,x,'spline',0);


for i=1:N
    u=h*(c./x(i))/(k*T);
    r(i)=((8*pi*(k*T)^4)/((h*c)^3))*((u^3)/(exp(u)-1));
end
lnm=x*1e9;
plot(lnm,yri,'r-.','LineWidth',2); hold on;
plot(lnm,ygi,'g--','LineWidth',2); hold on;
plot(lnm,ybi,'b-','LineWidth',2); hold on;
plot(lnm,r,'k-','LineWidth',2); hold on;
grid on;

rr=r.*yri;
rg=r.*ygi;
rb=r.*ybi;
figure;
plot(lnm,rr,'r-.','LineWidth',2); hold on;
plot(lnm,rg,'g--','LineWidth',2); hold on;
plot(lnm,rb,'b-','LineWidth',2); hold on;
% plot(lnm,r,'k-','LineWidth',2); hold on;
grid on;

sr=sum(yri);
sg=sum(ygi);
sb=sum(ybi);

srr=sum(rr);
srg=sum(rg);
srb=sum(rb);

rf=srr/sr;
gf=srg/sg;
bf=srb/sb;

rgb=(rf+gf+bf)/3;

rf8=255*rf/rgb
gf8=255*gf/rgb
bf8=255*bf/rgb



