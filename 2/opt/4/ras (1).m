lambda=[];
lambda0=7;
N=45;
M=27;
t=[];
P=[];
for i=1:1:M
    P(i,1,1)=1;
end
m=[];
for q=1:1:M;
    m(q)=1;
end
m(2)=N;
mu=[];
mu=[7, 0.5, 10];
% для каналов
for i=4:1:11
    mu=[mu 0.5];
end
% для аск
for i=12:1:19
    mu=[mu 5];
end
%для то
for i=20:1:27
    mu = [mu 0.25];
end

omega=[1, 1, 1, 0.16,0.16,0.16,0.16,0.16,0.16,0.16,0.16,...
    0.125,  0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125,...
    0.03,0.03,0.03,0.03,0.03,0.03,0.03,0.03];

t=zeros(M,N+1);


for r=2:1:N+1
    %поиск t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    for i=1:1:M
        for n=2:1:r
            if (n < m(i))
                muu=n*mu(i);
            else
                muu=m(i)*mu(i);
            end
            t(i,r-1)=t(i,r-1) + (n-1)*P(i,n-1,r-1)/muu;
        end
    end
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    %поиск лямбды%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    znam=0;
    for j=1:1:M
        znam=znam+omega(j)*t(j,r-1)/omega(1);
    end
    lambda(r-1)=(r-1)/znam;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    %поиск P%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     for i=1:1:M
         sumP=0;
        for n=2:1:r
            if (n < m(i))
                muu=n*mu(i);
            else
                muu=m(i)*mu(i);
            end
            P(i,n,r)=omega(i)*lambda(r-1)*P(i,n-1,r-1)/(omega(1)*muu);
            sumP=sumP+P(i,n,r);
        end
        P(i,1,r)=1-sumP;
     end
end
%вероятность отказа 
veroyatnost_otkaza = P(1,1,N+1)

%коэффициент загрузки
koeff_zagruzki = 1-veroyatnost_otkaza

%среднее число заявок в сети
n_sred=zeros(M);
n_sred_syst=0;
for j=1:1:M
    for n=1:1:N
        n_sred(j)=n_sred(j) + n*P(j,n+1,N+1);
    end
    n_sred_syst = n_sred_syst + n_sred(j);
end 
%среднее число заявок в сети
n_sred_v_systeme = n_sred_syst

%среднее число заявок в источнике
n0 = n_sred(1)

%интенсивность на выходе источника
intesyvnost = lambda(N)
intensyvnost_po_formule = koeff_zagruzki*lambda0

%среднее время пребывания пакета в буферной памяти
%t(2,N)
sr_vremya_prebyvania_v_pamyati = (N-n_sred(1))/intesyvnost

