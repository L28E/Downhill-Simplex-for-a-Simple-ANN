fileID = fopen('out.txt','w');
x_training = linspace(-14.7,25.7,200);
x_validation = linspace(-15,25,200);
x_testing = linspace(-14.3,25.3,200);

f = @(x) 0.5 - 2./(1+e.^(-(4*x+28))) + 6./(1+e.^(-(0.8*x-4)))
y_training=f(x_training);
y_validation=f(x_validation);
y_testing=f(x_testing);

figure();
plot(x_training,y_training);
hold on;
plot(x_validation,y_validation);
plot(x_testing,y_testing);

# Lets print them out like a C array so we can paste them into the program
function [] = print_c_arr(fileID,name,vector)
  fprintf(fileID,'double %s[] = { \n',name);
  for n = 1:length(vector)
    if n == length(vector)
      fprintf(fileID,'%E',vector(n));
    else
      fprintf(fileID,'%E,\n',vector(n));
    end 
  end
  fprintf(fileID,'\n};\n');
end

fprintf(fileID,'double training_size = %d\ndouble training_input_min=%E\ndouble training_input_max=%E\n',length(x_training),min(x_training),max(x_training));
fprintf(fileID,'double training_output_min=%E\ndouble training_output_max=%E\n',min(y_training),max(y_training));

fprintf(fileID,'double validation_size = %d\ndouble validation_input_min=%E\ndouble validation_input_max=%E\n',length(x_validation),min(x_validation),max(x_validation));
fprintf(fileID,'double validation_output_min=%E\ndouble validation_output_max=%E\n',min(y_validation),max(y_validation));

fprintf(fileID,'double test_size = %d\ndouble test_input_min=%E\ndouble test_input_max=%E\n',length(x_testing),min(x_testing),max(x_testing));
fprintf(fileID,'double test_output_min=%E\ndouble test_output_max=%E\n',min(y_testing),max(y_testing));

print_c_arr(fileID,"training_input",x_training);
print_c_arr(fileID,"training_output",y_training);
print_c_arr(fileID,"validation_input",x_validation);
print_c_arr(fileID,"validation_output",y_validation);
print_c_arr(fileID,"testing_input",x_testing);
print_c_arr(fileID,"testing_output",y_testing);


fclose(fileID);