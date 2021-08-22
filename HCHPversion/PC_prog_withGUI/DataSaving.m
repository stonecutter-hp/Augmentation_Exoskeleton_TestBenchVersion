function DataSaving()
% Saving experimental data for further data analysis
global ExoP;
global TempApp;
% %% Saving program time information
% assignin('base','TimeAll',ExoP.TimeAll);
% assignin('base','TimeTrans',ExoP.TransTime);
% %% Saving data from MCU
% assignin('base','torqueTL',ExoP.torqueTL);
% assignin('base','forceLL',ExoP.forceLL);
% assignin('base','angleAL',ExoP.angleAL);
% assignin('base','torqueTR',ExoP.torqueTR);
% assignin('base','forceLR',ExoP.forceLR);
% assignin('base','angleAR',ExoP.angleAR);
% assignin('base','angleP',ExoP.angleP);
% assignin('base','angleY',ExoP.angleY);
% assignin('base','adotPV',ExoP.adotPV);
% 
% %% Saving data used by control
% assignin('base','AlphaMean',ExoP.AlphaMean);   % from ExoP.angleP
% assignin('base','AlphaDot',ExoP.AlphaDot);     % calculated based on ExoP.AlphaMean and ExoP.TimeAll
% assignin('base','BetaMean',ExoP.BetaMean);     % from ExoP.angleY
% % more ...
% 
% %% Saving data from PC
% assignin('base','DesiredTorque',ExoP.DesiredTorque);
% assignin('base','MotionMode',ExoP.MotionMode);

%% Saving P for experimental configuration parameters
% Delete the initial motion state to keep the correpsonding relationship
% with other datas
ExoP.MotionMode = ExoP.MotionMode(2:end,:);
% assignin('base','ExoP',ExoP);
fileName = datetime('now');
fileName = datestr(fileName,'yyyymmddTHHMMSS');
[file,path] = uiputfile('*.mat','Prototype Data Save',fileName);
if isequal(file,0) || isequal(path,0)
    outPutStatus(TempApp,'Cancel Saving Data');
else
    save([path,file],'ExoP');
    outPutStatus(TempApp,'Data Saved.');
end



end