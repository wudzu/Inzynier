function [] = generujwykres(modyfikowana,testy_zestawow)

plik = fopen('dane.txt','rt');
plaintext=fscanf(plik,'Plaintext testu to %d%d\n');

seed=fscanf(plik,'Seed liczb losowych to %d\n');

zestawy=fscanf(plik,'Liczba zestawow to %d\n');

sredniatrafien(zestawy)=0;
prawdopodobienstwo(zestawy)=0;
sredniapudel(zestawy)=0;
powtorzenia(zestawy)=0;

n(zestawy)=0;
t(zestawy)=0;
m(zestawy)=0;
r(zestawy)=0;

for i=1:zestawy
    n(i)=fscanf(plik,'Zestaw %d');
    t(i)=fscanf(plik,',%d,');
    m(i)=fscanf(plik,'%d');
    r(i)=fscanf(plik,',%d\n');

    dane=fscanf(plik,'%d');

    for j=2:2:(2*testy_zestawow)
        sredniatrafien(i)=sredniatrafien(i)+dane(j-1);
        sredniapudel(i)=sredniapudel(i)+dane(j);
    end
    sredniatrafien(i)=sredniatrafien(i)/testy_zestawow;
    sredniapudel(i)=sredniapudel(i)/testy_zestawow;
    powtorzenia(i)=r(i)*t(i)*m(i)-sredniatrafien(i);
    prawdopodobienstwo(i)=sredniatrafien(i)/(2^16);
end

if modyfikowana=='n'
   figure('name','Srednia trafien','numbertitle','off')
   plot(n,sredniatrafien,'-r');
   
    figure('name','Srednia pudel','numbertitle','off')
   plot(n,sredniapudel,'-b');
   
   figure('name','Srednia powtorzen','numbertitle','off')
   plot(n,powtorzenia,'-g');  
   
   figure('name','Prawdopodobienstwo trafienia','numbertitle','off')
   plot(n,prawdopodobienstwo,'-c');  
elseif modyfikowana=='t'
   figure('name','Srednia trafien','numbertitle','off')
   plot(t,sredniatrafien,'-r');
   
    figure('name','Srednia pudel','numbertitle','off')
   plot(t,sredniapudel,'-b');  
   
   figure('name','Srednia powtorzen','numbertitle','off')
   plot(t,powtorzenia,'-g'); 
   
   figure('name','Prawdopodobienstwo trafienia','numbertitle','off')
   plot(t,prawdopodobienstwo,'-c'); 
elseif modyfikowana=='m'
   figure('name','Srednia trafien','numbertitle','off')
   plot(m,sredniatrafien,'-r');
   
    figure('name','Srednia pudel','numbertitle','off')
   plot(m,sredniapudel,'-b');  
   
   figure('name','Srednia powtorzen','numbertitle','off')
   plot(m,powtorzenia,'-g');  
   
   figure('name','Prawdopodobienstwo trafienia','numbertitle','off')
   plot(m,prawdopodobienstwo,'-c'); 
elseif modyfikowana=='r'
   figure('name','Srednia trafien','numbertitle','off')
   plot(r,sredniatrafien,'-r');
   
    figure('name','Srednia pudel','numbertitle','off')
   plot(r,sredniapudel,'-b');
   
   figure('name','Srednia powtorzen','numbertitle','off')
   plot(r,powtorzenia,'-g');  
   
   figure('name','Prawdopodobienstwo trafienia','numbertitle','off')
   plot(r,prawdopodobienstwo,'-c'); 
else
    
end

fclose(plik);

end
