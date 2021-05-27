function SerialStop(SerialPort,~)
global ExoP;
global TempApp;
fclose(SerialPort);
delete(SerialPort);
% disp('Serial port shut down!')

% check if timer is started
if(~isempty(ExoP.config{2,1}) && isvalid(ExoP.config{2,1}))
    ExoP.stopFlag = 4;
    stop(ExoP.config{2,1});
else
    %% Saving data
    ExoP.stopFlag = 3;
    DataSaving();
    outPutStatus(TempApp,'Data Saved.');
    stopStateDis();
end
end