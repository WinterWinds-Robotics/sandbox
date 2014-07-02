#!/bin/bash
#tmux_base.sh
 
SESSIONNAME="Base_View"
tmux has-session -t $SESSIONNAME >> /dev/null
 
if [ $? -ne 0 ]
  then
    # new session with name $SESSIONNAME and window 0 named "base"
    tmux new-session -s $SESSIONNAME -n "Main" -d
    tmux split-window -t $SESSIONNAME:1 -v
    tmux select-pane -t 1
    tmux split-window -t $SESSIONNAME:1 -h
    tmux send-keys 'htop' 'C-m'
    # Potentially show adb connections or something
    #tmux split-window -t $SESSIONNAME:1 -v
    #tmux send-keys 'mkdir ./bin' 'C-m'
 
    tmux select-pane -t 3
    tmux resize-pane -U 8
    tmux attach -t $SESSIONNAME
else
  echo "Execute 'tmux attach -t \"$SESSIONNAME\"' if you would like to attach"
fi
 



