// Function double_complex - test data.
function svdim()
    b = [ (5.91+5.69*%i),(3.15-4.08*%i),(4.89+4.20*%i),(7.09+2.72*%i);(1.89+3.27*%i),(4.10+6.70*%i),(7.78+4.06*%i),(4.57+2.07*%i);(3.28+3.84*%i),(-0.79+7.21*%i),(3.88+3.30*%i),(3.84+1.19*%i)]
    s = svd(b)
    disp(s)
endfunction
