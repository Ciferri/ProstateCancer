function diffusion()
  close all;
  
  load('out.dat');
  for i=1:5000
    matrix(:,:,i)=reshape(out(i,:),16,16);
  end
    
  for i=1:5000,   
    figure(1);
    imagesc(matrix(:,:,i));
    colormap('gray');
    img = ['/home/ciferri/Bureau/stage/v2/M2SLv0.1_EP/M2SLv0.1_EP/img/figure' num2str(i,'%04d') '.png']
    saveas(1,img)
  end
  
  
  
endfunction