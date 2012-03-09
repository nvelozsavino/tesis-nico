clc
clear all
close all
l=546.1e-9;
xi=-4*l;
xf=4*l;
dx=1e-9;
x=xi:dx:xf;
fps=10;
ti=1/fps;

t=0:ti/1000:ti;
c=3e8;

y=cos(4*pi*x/l);
f=60;
n=(2*l/6)*sin(2*pi*f*t);
yf=zeros(size(x));
yf2=zeros(size(x));
Nx=length(x);
j0=round(1+((0-xi)*(Nx-1)/(xf-xi)));

for i=1:length(n)
    
    dn=n(i);
    if (dn<xi)
        jn=1;
    elseif (dn>xf)
        jn=length(x);
    else
        jn=round(1+((dn-xi)*(Nx-1)/(xf-xi)));        
    end
    y1=zeros(size(x));
    dj=jn-j0;
    if (dj<0)
        y1(1-dj:Nx)=y(1:Nx+dj);
    else
        y1(1:Nx-dj)=y(1+dj:Nx);
    end
    yf2=yf2+y1;
    
    for j=1:Nx
        yf(j)=yf(j)+cos(4*pi*(x(j)+n(i))/l);
    end
end
yf=yf/length(t);
yf2=yf2/length(t);

plot(x,y,x,yf);
% figure;
% plot(t,dx);