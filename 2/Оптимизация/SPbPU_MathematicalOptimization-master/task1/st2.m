function [sigma] = probabilityConstr(x)
    covH=x*[0.6; 0.8; 1.0; 1.2]*transpose(x);
    sigma = sqrt(covH);
end

