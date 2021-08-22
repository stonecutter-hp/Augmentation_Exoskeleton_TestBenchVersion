function P = RTGInit(RTGMode)
% Initialization the specific parameters of RTG strategy according to the
% selection from GUI

if RTGMode == 1
    P = RTGImpedanceStra_Init();
elseif RTGMode == 2
    P = RTGCompensationStra_Init();
elseif RTGMode == 3
    P = [];
%     P = RTGVel_basedCompStra_Init();
else
    P = [];
end

end