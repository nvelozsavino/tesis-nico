function resultado=integrar (x,y)
    resultado=0;
    for i=2:length(x)
        dx=x(i)-x(i-1);
        dy=y(i)-y(i-1);
        resultado=resultado+dx*dy;
    end
end