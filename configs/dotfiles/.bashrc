# .bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'

# verify for background jobs
bg()
{
	if [[ $(jobs | wc -l) -ne 0 ]]; then
		printf "\001\e[33m\002B"
	fi
}

# VIM shell variable detector
vv()
{
	if [[ ! -z $VIM ]]; then
		printf "\001\e[32m\002V"
	fi
}

# detect actual branch and if work tree is dirty
branch()
{
	CLEAN="nothing to commit, working tree clean"
	if [[ $(git status 2> /dev/null | tail -n1) != $CLEAN ]]; then 
		printf " \001\e[31m\002$(git branch 2> /dev/null | grep '^*' | colrm 1 2)"
	else
		printf " \001\e[32m\002$(git branch 2> /dev/null | grep '^*' | colrm 1 2)"
	fi
}

# untrack files counter
untrack()
{
	GITS=$(git status 2> /dev/null | sed -n '/Untracked/,/^$/p' | wc -l)
	if [[ $GITS -ne 0 ]]; then
		UNTRACK=$(echo "$GITS - 3" | bc)
		printf " \001\e[33m\002+$UNTRACK"
	fi
}

# deleted files counter
deleted()
{
	DEL=$(git status 2> /dev/null | grep deleted | wc -l)
	if [[ $DEL -ne 0 ]]; then
		printf " \001\e[31m\002-$DEL"
	fi
}

# modified files counter
modified()
{
	MOD=$(git status 2> /dev/null | grep modified | wc -l)
	if [[ $MOD -ne 0 ]]; then
		printf " \001\e[37m\002~$MOD"
	fi
}

# added files counter
add()
{
	ADD=$(git status 2> /dev/null | awk '/Changes to be committed/,/^$/{print;f=1} f&&/^$/{exit}' | wc -l)
	if [[ $ADD -ne 0 ]]; then
		TRACK=$(echo "$ADD - 3" | bc)
		printf " \001\e[32m\002^$TRACK"
	fi
}

# display prompt
export PS1='\[\e[36m\][$(bg)$(vv) \[\e[35m\]\W$(branch)$(untrack)$(deleted)$(modified)$(add)\[\e[36m\]]\$\[\e[0m\] '
