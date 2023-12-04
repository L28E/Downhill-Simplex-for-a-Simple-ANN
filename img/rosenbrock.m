# Create a gif of the optimization process
# See https://www.mathworks.com/help/matlab/ref/imwrite.html

filename = 'rosenbrock.gif';
DelayTime = 1; # Time in seconds for each plot in the GIF
f = figure;

minW = -3;
maxW = 3;
step_size=0.1;
[W1,W2] = meshgrid(minW:step_size:maxW, minW:step_size:maxW);
E = (1-W1).^2+100*(W2-W1.^2).^2;
contour_levels = [10^5 10^4 10^3 10^2 10^1 10^0 10^-1 10^-2 10^-3 10^-4];

num_simplexes = 43; # The number of iterations +1 for the initial simplex
size = 2; # The size of each vertex i.e. the number of variables

X = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  
Y = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  

# Pasted output from algo_demo.out
X(1,:)=[ -2.369136 -2.941394 2.596464 -2.369136 ];
Y(1,:)=[ 1.623523 2.831420 -0.371964 1.623523 ];
X(2,:)=[ -0.029401 -2.369136 -2.941394 -0.029401 ];
Y(2,:)=[ 0.927754 1.623523 2.831420 0.927754 ];
X(3,:)=[ 0.542857 -0.029401 -2.369136 0.542857 ];
Y(3,:)=[ -0.280142 0.927754 1.623523 -0.280142 ];
X(4,:)=[ -1.056204 0.542857 -0.029401 -1.056204 ];
Y(4,:)=[ 0.973665 -0.280142 0.927754 0.973665 ];
X(5,:)=[ -1.056204 -0.483947 0.542857 -1.056204 ];
Y(5,:)=[ 0.973665 -0.234231 -0.280142 0.973665 ];
X(6,:)=[ -0.113609 -1.056204 -0.483947 -0.113609 ];
Y(6,:)=[ 0.044787 0.973665 -0.234231 0.044787 ];
X(7,:)=[ -0.113609 -0.534427 -1.056204 -0.113609 ];
Y(7,:)=[ 0.044787 0.137497 0.973665 0.044787 ];
X(8,:)=[ -0.113609 -0.690111 -0.534427 -0.113609 ];
Y(8,:)=[ 0.044787 0.532404 0.137497 0.044787 ];
X(9,:)=[ -0.113609 -0.468144 -0.690111 -0.113609 ];
Y(9,:)=[ 0.044787 0.213046 0.532404 0.044787 ];
X(10,:)=[ -0.113609 -0.468144 -0.490494 -0.113609 ];
Y(10,:)=[ 0.044787 0.213046 0.330660 0.044787 ];
X(11,:)=[ -0.113609 -0.091259 -0.468144 -0.113609 ];
Y(11,:)=[ 0.044787 -0.072827 0.213046 0.044787 ];
X(12,:)=[ -0.113609 -0.285289 -0.091259 -0.113609 ];
Y(12,:)=[ 0.044787 0.099513 -0.072827 0.044787 ];
X(13,:)=[ -0.113609 -0.145354 -0.285289 -0.113609 ];
Y(13,:)=[ 0.044787 -0.000338 0.099513 0.044787 ];
X(14,:)=[ 0.026325 -0.113609 -0.145354 0.026325 ];
Y(14,:)=[ -0.055064 0.044787 -0.000338 -0.055064 ];
X(15,:)=[ 0.159782 0.026325 -0.113609 0.159782 ];
Y(15,:)=[ -0.014739 -0.055064 0.044787 -0.014739 ];
X(16,:)=[ 0.159782 -0.010278 0.026325 0.159782 ];
Y(16,:)=[ -0.014739 0.004943 -0.055064 -0.014739 ];
X(17,:)=[ 0.123179 0.159782 -0.010278 0.123179 ];
Y(17,:)=[ 0.045268 -0.014739 0.004943 0.045268 ];
X(18,:)=[ 0.123179 0.293239 0.159782 0.123179 ];
Y(18,:)=[ 0.045268 0.025586 -0.014739 0.045268 ];
X(19,:)=[ 0.256636 0.123179 0.293239 0.256636 ];
Y(19,:)=[ 0.085593 0.045268 0.025586 0.085593 ];
X(20,:)=[ 0.256636 0.241573 0.123179 0.256636 ];
Y(20,:)=[ 0.085593 0.045508 0.045268 0.085593 ];
X(21,:)=[ 0.312067 0.256636 0.241573 0.312067 ];
Y(21,:)=[ 0.075692 0.085593 0.045508 0.075692 ];
X(22,:)=[ 0.369908 0.312067 0.256636 0.369908 ];
Y(22,:)=[ 0.150911 0.075692 0.085593 0.150911 ];
X(23,:)=[ 0.369908 0.425340 0.312067 0.369908 ];
Y(23,:)=[ 0.150911 0.141010 0.075692 0.150911 ];
X(24,:)=[ 0.483181 0.369908 0.425340 0.483181 ];
Y(24,:)=[ 0.216229 0.150911 0.141010 0.216229 ];
X(25,:)=[ 0.483181 0.425942 0.369908 0.483181 ];
Y(25,:)=[ 0.216229 0.162290 0.150911 0.216229 ];
X(26,:)=[ 0.483181 0.412235 0.425942 0.483181 ];
Y(26,:)=[ 0.216229 0.170085 0.162290 0.216229 ];
X(27,:)=[ 0.491239 0.483181 0.412235 0.491239 ];
Y(27,:)=[ 0.254891 0.216229 0.170085 0.254891 ];
X(28,:)=[ 0.562185 0.491239 0.483181 0.562185 ];
Y(28,:)=[ 0.301035 0.254891 0.216229 0.301035 ];
X(29,:)=[ 0.570243 0.562185 0.491239 0.570243 ];
Y(29,:)=[ 0.339697 0.301035 0.254891 0.339697 ];
X(30,:)=[ 0.641189 0.570243 0.562185 0.641189 ];
Y(30,:)=[ 0.385841 0.339697 0.301035 0.385841 ];
X(31,:)=[ 0.692779 0.641189 0.570243 0.692779 ];
Y(31,:)=[ 0.486238 0.385841 0.339697 0.486238 ];
X(32,:)=[ 0.692779 0.618614 0.641189 0.692779 ];
Y(32,:)=[ 0.486238 0.387868 0.385841 0.486238 ];
X(33,:)=[ 0.692779 0.648443 0.618614 0.692779 ];
Y(33,:)=[ 0.486238 0.411447 0.387868 0.486238 ];
X(34,:)=[ 0.722608 0.692779 0.648443 0.722608 ];
Y(34,:)=[ 0.509816 0.486238 0.411447 0.509816 ];
X(35,:)=[ 0.826195 0.722608 0.692779 0.826195 ];
Y(35,:)=[ 0.671187 0.509816 0.486238 0.671187 ];
X(36,:)=[ 0.826195 0.733590 0.722608 0.826195 ];
Y(36,:)=[ 0.671187 0.538370 0.509816 0.671187 ];
X(37,:)=[ 0.894462 0.826195 0.733590 0.894462 ];
Y(37,:)=[ 0.794702 0.671187 0.538370 0.794702 ];
X(38,:)=[ 0.894462 0.796959 0.826195 0.894462 ];
Y(38,:)=[ 0.794702 0.635657 0.671187 0.794702 ];
X(39,:)=[ 0.894462 0.865226 0.796959 0.894462 ];
Y(39,:)=[ 0.794702 0.759172 0.635657 0.794702 ];
X(40,:)=[ 0.962728 0.894462 0.865226 0.962728 ];
Y(40,:)=[ 0.918217 0.794702 0.759172 0.918217 ];
X(41,:)=[ 0.962728 0.896911 0.894462 0.962728 ];
Y(41,:)=[ 0.918217 0.807816 0.794702 0.918217 ];
X(42,:)=[ 1.000535 0.962728 0.896911 1.000535 ];
Y(42,:)=[ 0.999646 0.918217 0.807816 0.999646 ];
X(43,:)=[ 1.000535 0.939271 0.962728 1.000535 ];
Y(43,:)=[ 0.999646 0.883374 0.918217 0.999646 ];

for i = 1:num_simplexes    
      
      contour(W1, W2, E, contour_levels, 'ShowText','on','linewidth',1.5);
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
