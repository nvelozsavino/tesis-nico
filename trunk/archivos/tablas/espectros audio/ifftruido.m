clear all;
close all;
clc;

audiofft=load('todo apagado.txt');

y0p=audiofft(:,2);
x0p=audiofft(:,1);

% y0n=flipud(y0p);
% x0n=flipud(-x0p);
% x0=[x0n;x0p];
% y0=[y0n;y0p];

x0=x0p;
y0=y0p;


Fs = 44100;                    % Sampling frequency
Nf = 2^nextpow2(length(y0)); % Next power of 2 from length of y
f=(Fs/2)*linspace(0,1,Nf);
yi=10.^(interp1(x0,y0,f,'spline','extrap')/20);
fmax=Fs/2;%f(length(f));
data=yi;

% 
% figure
% 
% 
% T = 1/Fs;                     % Sample time
% 
% NFFT = 2^nextpow2(N); % Next power of 2 from length of y
% Y = ifft(yi,NFFT)/N;
% t = T/2*linspace(0,1,NFFT/2);
% 
% % Plot single-sided amplitude spectrum.
% plot(t,real(Y(1:NFFT/2))) 
% xlabel('time (s)')
% ylabel('Y(t)')

% Calculate ifft of half-spectrum data
h = [conj(data) fliplr(data(2:length(data)-1))];
h(1) = 2 * real(h(1));                          % DC tweak
%h(length(data)) = 2 * real(h(length(data)));    % Nyquist tweak
y = ifft(h);

% Plot results
N = length(h);
T=1/Fs;
freq = Fs * (-N/2 : N/2-1) / N;
time = (0 : N-1)*T;
subplot(2,1,1); plot(freq, abs(fftshift(h))); xlabel('Expanded Spectrum [Hz]');
subplot(2,1,2); plot(time, N / 2 * y); xlabel('Time-Domain [s]');

ffmax=20e3;
ffmin=200;
ff=[ffmin ffmax]/(Fs/2);
[b,a]=butter(10,2*ffmax/Fs,'low');
y2=filtfilt(b,a,y);
[b2,a2]=butter(2,2*ffmin/Fs,'high');
yf=filtfilt(b2,a2,y2);
NFFT = 2^nextpow2(N); % Next power of 2 from length of y
Y = fft(yf,NFFT);%/N;
f2 = Fs/2*linspace(0,1,NFFT/2);
figure
% Plot single-sided amplitude spectrum.
semilogx(f,abs(yi)/max(yi),'k');
xlabel ('Frecuencia (Hz)');
ylabel ('Amplitud relativa');
title ('Espectro de la señal obtenida con el microfono');
grid on;
% figure;
% semilogx(f2,2*abs(Y(1:NFFT/2))) 
% title('Single-Sided Amplitude Spectrum of y(t)')
% xlabel('Frequency (Hz)')
% ylabel('|Y(f)|')
% 
% figure
% 
% freqz(b,a,1000);
% figure
% freqz(b2,a2,1000);