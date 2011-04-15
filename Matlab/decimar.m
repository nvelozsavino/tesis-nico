clc;
clear all;
close all;
d=load('solo_aire.txt');
x=(d(:,1));
ydb=d(:,2);
y=10.^(ydb/20);
fs=length(x)/(x(length(x))-x(1));
xmax=500;
ix=(xmax-x(1))*fs;
ya=y(1:ix);
xa=x(1:ix);
r=floor(length(ya)/100);
yn=decimate(ya,r);
fsn=fs/r;
xn=xa(1):1/fsn:xa(length(xa));
plot(xa,ya,'r',(xn),yn,'b');

fmax=xmax;
fs=fmax*2;
T=1/fs;
L=1000;
t=(0:L-1)*T;
forma=zeros(1,L);
for i=1:length(xa)
    fn=xa(i);
    forma=forma+ya(i)*cos(2*pi*fn*t);
end
plot(t,forma);


figure;

NFFT = 2^nextpow2(L); % Next power of 2 from length of y
Y = fft(forma,NFFT)/L;
f = fs/2*linspace(0,1,NFFT/2);

% Plot single-sided amplitude spectrum.
plot(xa,ya,'r',f,2*abs(Y(1:NFFT/2)),'b'); 
title('Single-Sided Amplitude Spectrum of y(t)')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')