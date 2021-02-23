# dual monitor
if [ $(xrandr | grep -c 'HDMI1 connected') -eq 1 ]; then
	xrandr --output HDMI1 --mode 1920x1080 --left-of LVDS1
	feh --bg-scale /home/ota/pictures/wallpapers/{blacktip-shark.jpg,oceanic-whitetip-shark.jpg}

	# map wacom tablet to the external monitor
	stylus=$(xsetwacom list devices | grep -o -m 1 '[0-9]\+')
	xsetwacom --set "$stylus" MapToOutput HDMI1
else
	feh --bg-scale /home/ota/pictures/wallpapers/blacktip-shark.jpg
fi

/home/ota/configurations/bar/dwmbar &
picom -c -r 15 -D 0 &
setxkbmap -layout us_intl
xmodmap .Xmodmap
xbindkeys
exec dwm
