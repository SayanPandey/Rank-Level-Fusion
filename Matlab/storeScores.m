function [ ] = storeScores( subject,names,scores1,scores2 ,scores3)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
 %Creating CSV FILE TO STORE;
        setdir=strcat('..\ScoreBoard\',subject,'.csv');
        fid = fopen( setdir, 'w' );
        fprintf( fid, '%s,%s,%s,%s\n','Names','SIFT Scores','Coreleation Scores','EMD Scores');
        
        for jj = 1 : length( names )
            if jj~=i
                fprintf( fid, '%s,%s,%s,%s\n', names{jj}, scores1{jj},scores2{jj},scores3{jj});
            end
        end
        fclose( fid );    

end

