function convertir(fileInput,fileOutput)
    data=load(fileInput);
    ydb=data(:,2);
    x=data(:,1);
    y=10.^(ydb/20);
    yn=y/max(y);
    toFile=[x' ; yn']
    fid = fopen(fileOutput, 'wt');
    fprintf(fid, '%6.2f\t%12.8f\n', toFile);
    fclose(fid);
end