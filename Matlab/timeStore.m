function [  ] = timeStore( names,time )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Creating CSV FILE TO STORE;
        [status, msg, msgID]=mkdir('..\CPUTimes');
        setdir=strcat('..\CPUTimes\','matlabTimes','.csv');
        fid = fopen( setdir, 'w' );
        fprintf( fid, '%s,%s\n','Names','Time(in s)');
        
        for jj = 1 : length( names )
            if jj~=i
                fprintf( fid, '%s,%s\n', names{jj}, time{jj});
            end
        end
        fclose( fid );    

end

