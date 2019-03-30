
%Main Directory of images
A= dir('..\Assets\SortedImages');
sizeA=size(A);

%Stucture to store Names and their Scores
names=cell(sizeA);
scores1=cell(sizeA);
scores2=cell(sizeA);
scores3=cell(sizeA);

%Set for storing times
names2=cell(sizeA);
times=cell(sizeA);


%Creating a Directory to store Scores:
[status, msg, msgID] = mkdir ('..\ScoreBoard');



%Looping through each image
for i=3:size(A)
    
    %To calculate Ecectution time:
    tic;
   
    
    %Reading each directory 
    message=strcat('Present Working Subject :',A(i).name);
    disp(message);
    imgDir=dir(strcat('..\Assets\SortedImages\',A(i).name));
    
    %Makaing folder of a particular name 
    %[status, msg, msgID] = mkdir(['..\ScoreBoard\',A(i).name]);
    
    
    %Getting Train image
    if i>=3
        trainImg = imread(strcat('..\Assets\SortedImages\',A(i).name,'\',imgDir(3).name));
        %imshow(trainImg);
    
        
    %Getting Test images
        for j=3:size(A)
            if j~=i       
                
                %Getting test image directory
                imgDir=dir(strcat('..\Assets\SortedImages\',A(j).name));
                
                %Now here we Calculate Scores:
                
                %Sift Score
                scoreSift=0.00;
                for k=3:size(imgDir)
                    
                    %Getting set of images from a particular directory.
                    testImg=imread(strcat('..\Assets\SortedImages\',A(j).name,'\',imgDir(k).name));
                    temp=SIFT(trainImg,testImg);
                    
                    if temp>0
                        scoreSift=temp;
                        break;
                    end
                
                end
                a=sprintf('%.6f',scoreSift);
                disp(strcat('Sift Score with subject: ',A(j).name,' is :',a));
                
                
                %Corelation Score
                corScore=corelation(trainImg,testImg);
                b=sprintf('%.6f',corScore);
                disp(strcat('Corelation Score with subject: ',A(j).name,' is :',b));
                
                
                %EMD Score
                train=histImage(trainImg);
                test=histImage(testImg);
                dist=patDistMAp(train,test);
                [m,n]=size(dist);
                emdScore=double(sum(dist)/(m*n));
                c=sprintf('%.6f',emdScore);
                disp(strcat('EMD Score with subject: ',A(j).name,' is :',c));
                
                
                %Storage;
                names{j}=A(j).name;
                scores1{j}=a;
                scores2{j}=b;
                scores3{j}=c;
                
            end
        end
        %Creating CSV FILE TO STORE;
        storeScores(A(i).name,names,scores1,scores2,scores3);
        
    end
    
    %Storing the time with names.
    timeElapsed=toc;
    disp(timeElapsed);
    
    names2{i}=A(i).name;
    times{i}=timeElapsed;
    
    %Storing it in a csv file
    timeStore(names2,times);
    
end



