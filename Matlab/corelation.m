function [ coreScore ] = corelation( trainImg,testImg )
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here
    c = corr2(testImg,trainImg);           
    coreScore=double(1-c);
    
    %1-c because corelation will provide a number with either 0-1 with 1
    %for max matching

end

