clc;
close all;
y=[-255 255];
%js=[5 4 2 5 2 1 2 1 3 2]; % para DC
js=[2 2 4 2 2 5 2 5 2 4 5]; % para AC

for i=1:length(numeradores)
%     for j=1:length(alphas{i})
        j=js(i);
        if (i<10)
            subplot(3,3,i);
        else
            if i==10
                figure
            end
            subplot(3,3,i-9);
        end
%         figure;
        plot(denominadores{i}{j},numeradores{i}{j},'k.'); grid on;
        axis([-510 510 -255 255]);        
        txtTitle=['Sitios de Red para una paso de ', num2str(pasos(i)), 'Hz'];%, ' i=', num2str(i),' j=', num2str(j)];
        title(txtTitle,'FontWeight','bold');
        x=(y-polinomios{i}{j}(2))/polinomios{i}{j}(1);
        hold on;
        plot(x,y);
        if (polinomios{i}{j}(1)>=0)
            yt=80;
            extray=-10;
            extrax=10;
        else 
            yt=-80;
            extray=10;
            extrax=10;
        end
        xt=(yt-polinomios{i}{j}(2))/polinomios{i}{j}(1);
        if (xt>=300 || xt<=-300)
            xt=150;
            yt=polyval(polinomios{i}{j},xt);
        end
        txt=text(xt+extrax,yt+extray,['\alpha = ', num2str(alphas{i}(j)*180/pi),'�']);
%         txt2=text(-500,-150,['\alpha_m = ', num2str(alpha_mean(i)*180/pi),'�']);
%         txt3=text(-500,-200,['\delta\alpha = ', num2str((alpha_mean(i)-alphas{i}(j))*180/pi),'�']);
%    end
end