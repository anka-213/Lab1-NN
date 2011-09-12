load('uppg1_new','-ascii')
x = uppg1_new(:,2)./uppg1_new(:,1);
y = uppg1_new(:,3);
XY = sortrows([x y]);
X=XY(:,1);
Y=XY(:,2);
X1 = X; Y1 = Y;


for i=1:200
    X1 = (X1(1:(end-1)) + X1(2:end))/2; 
    Y1 = (Y1(1:(end-1)) + Y1(2:end))/2;
end


hold on

figure(1)
clf
Ytheoretic = 1/2 * (erfc(sqrt(1./(2*X))));
plot(X,Y,X,Ytheoretic)
figure(2)
clf
Y1theoretic = 1/2 * (erfc(sqrt(1./(2*X1))));
plot(X1,Y1,X1,Y1theoretic)


