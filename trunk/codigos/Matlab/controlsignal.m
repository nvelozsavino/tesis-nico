clear all;
close all;
clc;
Fs=10000;
tf=100e-3;
t=0:1/Fs:tf;
% x{1}=a(1)*exp((t-m(1))^2/(2*s(1)^2));
inti=tf/4;
intf=tf/4;
mult=[];
for i=1:length(t)
    if (t(i)<0)
        mult(i)=0;
    elseif (t(i)<=inti)
        mult(i)= 1-cos(t(i)*pi/inti);
    elseif (t(i)<(tf-intf))
        mult(i)=2;
    elseif (t(i)<=tf)
        mult(i)=1+cos((t(i)-(tf-intf))*pi/intf);
    else
        mult(i)=0;
    end
end
mult=mult/2;
p=[ 0   11  0;
    258 29  30;
    238 7   65];
CLmin=-546.1;
CLmax=546.1;
DLmax=10;
DLmin=-10;
c=zeros(size(t));
for j=1:length(p)
    A=p(j,1);
    X=t;
    M=p(j,3)/1000;
    S=p(j,2)/1000;
    
    y=A*exp(-(((X-M).^2)/(2*(S^2))));
%     y=a(j)*exp(-((t-t0(j)).^2/(2*(s(j)^2))));
     
    figure;
    plot (t,y); grid on;
    c=c+(y.*mult);
end
x=DLmin+((c-CLmin)*((DLmax-DLmin)/(CLmax-CLmin)));
plot(t,x); grid on;


