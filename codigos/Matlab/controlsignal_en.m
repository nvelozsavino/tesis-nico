clear all;
close all;
clc;
Fs=10e3;
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
mult=mult/1;
p=[ 0   11  0;
    258 29  30;
    109 7   65];
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
     
%     figure;
%     plot (t,y); grid on;
    c=c+(y.*mult);
end
x=DLmin+((c-CLmin)*((DLmax-DLmin)/(CLmax-CLmin)));
a=(31.6837*x+1.1014);
mediaa=mean(a)
b=180-abs(-a+180);
plot(t,a,'b','LineWidth',2);
hold on;
plot(t,b,'r--','LineWidth',2);
hold on;
plot([0 tf],[180 180],'k-.','LineWidth',2);
grid on;
legend('Original phase', 'Equivalent phase','180�');
%axis([0 0.1 0 360]);
ylabel('Phase \alpha (degrees)');
xlabel('Time (s)');
title('Control Signal','FontWeight','bold');
y=[];
for k=1:100
    if k==100
        y=[y b];
    else 
        y=[y zeros(1,length(b))+b(1)];
    end
end
figure
plot(y)

fmin=1
fmax=100;
W1=2*fmin/Fs;
W2=2*fmax/Fs;
Wn=[W1 W2];
[b,a]=butter(1,W1,'high');
y2=filtfilt(b,a,y);

figure
plot(y2)

%y=b-mean(b);
% y=b
L=length(y);
NFFT = L;%2^nextpow2(L); % Next power of 2 from length of y
Y = fft(y,NFFT)/L;
f = Fs/2*linspace(0,1,NFFT/2);
figure
% Plot single-sided amplitude spectrum.
semilogx(f,2*abs(Y(1:NFFT/2)),'LineWidth',2);grid on; 
% axis([1 1000 0 0.5])
title('Equivalent control signal spectrum','FontWeight','bold');
xlabel('Frequency(Hz)')
ylabel('|Y(f)|')

