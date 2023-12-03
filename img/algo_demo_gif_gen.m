# Create a gif of the optimization process
# See https://www.mathworks.com/help/matlab/ref/imwrite.html

filename = 'algo_demo.gif';
DelayTime = 1; # Time in seconds for each plot in the GIF
f = figure;

minW = -10;
maxW = 10;
step_size=0.1;
[W1,W2] = meshgrid(minW:step_size:maxW, minW:step_size:maxW);
E = W1.^2-2.*W1+1+2*(W2.^2-4.*W2+4);

num_simplexes = 13; # The number of iterations +1 for the initial simplex
size = 2; # The size of each vertex i.e. tje number of variables

X = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  
Y = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  

# Pasted output from algo_demo.out
X(1,:)=[ 0.027471 -6.085879 6.307488 0.027471 ];
Y(1,:)=[ 2.004216 1.585021 -9.201490 2.004216 ];
X(2,:)=[ 0.027471 -6.085879 1.639142 0.027471 ];
Y(2,:)=[ 2.004216 1.585021 -3.703436 2.004216 ];
X(3,:)=[ 0.027471 -0.695031 -6.085879 0.027471 ];
Y(3,:)=[ 2.004216 -0.954409 1.585021 2.004216 ];
X(4,:)=[ 0.027471 2.542270 -0.695031 0.027471 ];
Y(4,:)=[ 2.004216 -0.005155 -0.954409 2.004216 ];
X(5,:)=[ 0.027471 3.264772 2.542270 0.027471 ];
Y(5,:)=[ 2.004216 2.953470 -0.005155 2.004216 ];
X(6,:)=[ 0.027471 2.094196 3.264772 0.027471 ];
Y(6,:)=[ 2.004216 1.236844 2.953470 2.004216 ];
X(7,:)=[ 0.027471 2.162803 2.094196 0.027471 ];
Y(7,:)=[ 2.004216 2.287000 1.236844 2.004216 ];
X(8,:)=[ 1.594667 0.027471 2.162803 1.594667 ];
Y(8,:)=[ 1.691226 2.004216 2.287000 1.691226 ];
X(9,:)=[ 1.486936 1.594667 0.027471 1.486936 ];
Y(9,:)=[ 2.067361 1.691226 2.004216 2.067361 ];
X(10,:)=[ 0.784136 1.486936 1.594667 0.784136 ];
Y(10,:)=[ 1.941755 2.067361 1.691226 1.941755 ];
X(11,:)=[ 0.784136 0.905971 1.486936 0.784136 ];
Y(11,:)=[ 1.941755 2.161224 2.067361 1.941755 ];
X(12,:)=[ 1.165995 0.784136 0.905971 1.165995 ];
Y(12,:)=[ 2.059425 1.941755 2.161224 2.059425 ];
X(13,:)=[ 1.165995 1.044160 0.784136 1.165995 ];
Y(13,:)=[ 2.059425 1.839956 1.941755 2.059425 ];
X(14,:)=[ 0.944607 1.165995 1.044160 0.944607 ];
Y(14,:)=[ 1.945723 2.059425 1.839956 1.945723 ];
X(15,:)=[ 0.944607 1.049731 1.165995 0.944607 ];
Y(15,:)=[ 1.945723 1.921265 2.059425 1.945723 ];
X(16,:)=[ 1.081582 0.944607 1.049731 1.081582 ];
Y(16,:)=[ 1.996460 1.945723 1.921265 1.996460 ];
X(17,:)=[ 0.976458 1.081582 0.944607 0.976458 ];
Y(17,:)=[ 2.020917 1.996460 1.945723 2.020917 ];

for i = 1:num_simplexes    
      
      contour(W1, W2, E, 'linewidth',1.5);
      xlabel("w_1");
      ylabel("w_2");
      set(gca, "fontsize", 12)
      hold on;
      plot(X(i,:),Y(i,:), 'r','linewidth',1.5)
      hold off;
      drawnow
                  
      frame = getframe(f);      
      im = frame2im(frame);     
      [imind,cm] = rgb2ind(im); 
      if i == 1;          
          imwrite(imind,cm,filename,'gif','DelayTime', DelayTime , 'Compression' , 'lzw');
      else
          imwrite(imind,cm,filename,'gif','WriteMode','append','DelayTime', DelayTime , 'Compression' , 'lzw');
      end
end