# COMP3004 Team 47 - Final Project
## Team Members 
* Ellie Ng - wisdomlesstooths
    * Use Cases, Class Diagram, use case diagram
    * state machine diagram: device
    * Sequence Diagram: device low battery
    * Requirements Traceability Matrix
    * Set up slots + signals
    * Button Implemenation/Logic
    * Battery Functionality (set battery level, set low/no battery, deplete during session run)
    * Battery UI
    * New session designs
    * Write test cases
    * Design & Prototyping
    * Update date and time functionality
    * new session - only allow play when headset has been connected
    * uploading completed documentation to github
    * video recording
    * troubleshooting
* Ryushen Tan - ryushen-tan
    * UI Design/Implemenation
    * New Session UI
    * Use cases
    * Stylesheets for UI
    * UI - add PC view of sessions
    * New Session Implementation
    * Look into and implement new session flow
    * make timer and progress bar in UI
    * Finish battery UI
    * UI display of logs for pc and session logs view
    * Video recording
    * Textual explanation of design decisions
    * Button Implemenation/Logic
    * Design & Prototyping
    * troubleshooting
* William Yin - water-fleas
    * Use Cases, Class Diagram
    * Session Info Class Implementation
    * Button Implemenation/Logic
    * Design & Prototyping
    * troubleshooting
    * Requirements traceability matrix
    * Sequence diagram: PC view
    * Database write + storing session info
    * Textual explanation of design decisions
* Stephen Mamosian - TheSlenk
    * New Session Process Implementation/Logic
    * New Session Process/Controller
    * Button Implemenation/Logic
    * Design & Prototyping
    * troubleshooting
    * Device RGB light and beep functionality for session process and no contact
    * complete implementation of new session
    * play/pause new session
    * stop new session
    * make timer and progress bar in ui work with new session process
* Mike Lin - Maiku3
    * Use Cases, Class Diagram
    * Signal Generation Implementation/Logic
    * EEG Site and Processing Implementation
    * Button Implemenation/Logic
    * Design & Prototyping
    * Requirements Traceability Matrix
    * Sequence Diagram: Connection Loss
    * Sequence Diagram: Normal Operation of Treatment
    * Setting up QCharts and UI for plotting EEG Signal
    * Plotting EEG Signal
    * Implement Signal generation (SignalGenerator, EEGSite)
    * Apply treatment and update rounds
    * Disconnect headset functionality (call pause treatment, stop EEG plot)
    * Signal analysis and processing
    * State machine diagram: device
    * Implement calculate dominante frequency function
    * Applying offset for treatment
    * Disconnect headset implementation
    * connect + test signal generation
    * implement math for sinewave generation
    * Class diagram
    * Textual explanation of design decisions
    * troubleshooting
* TA: Anjali

## How to run the simulation!
Export github as zip
Install QChart (using command: 'sudo apt install libqt5charts5-dev')
Run Final_3004.pro in Qt

## Video demo
Watch here: [https://www.youtube.com/watch?v=fMr4ltGo5rQ](https://www.youtube.com/watch?v=fMr4ltGo5rQ)

## File Organization

. Final_3004.pro\
L Headers\
&nbsp;&nbsp;. Device.h\
&nbsp;&nbsp;. EEGSite.h\
&nbsp;&nbsp;. mainwindow.h\
&nbsp;&nbsp;. SessionInfo.h\
&nbsp;&nbsp;. SignalGenerator.h\
L Sources\
&nbsp;&nbsp;. Device.cpp\
&nbsp;&nbsp;. EEGSite.cpp\
&nbsp;&nbsp;. main.cpp\
&nbsp;&nbsp;. mainwindow.cpp\
&nbsp;&nbsp;. SessionInfo.cpp\
&nbsp;&nbsp;. SignalGenerator.cpp\
L Forms\
&nbsp;&nbsp;. mainwindow.ui\
L Design Documentation
&nbsp;&nbsp;. Class Diagram\
&nbsp;&nbsp;. Use Cases\
&nbsp;&nbsp;. Use Case diagram\
&nbsp;&nbsp;. Requirements Traceability Matrix\
&nbsp;&nbsp;. State diagram\
&nbsp;&nbsp;. Team47ProjectReport (Textual Explanation of Design Decisions)\
&nbsp;&nbsp;L Sequence Diagrams\
&nbsp;&nbsp;&nbsp;&nbsp;. 1 normal operation of treatment\
&nbsp;&nbsp;&nbsp;&nbsp;. 2 therapy history viewing with PC\
&nbsp;&nbsp;&nbsp;&nbsp;. 3 device battery low response\
&nbsp;&nbsp;&nbsp;&nbsp;. 4 connection loss between electrodes and the device\
