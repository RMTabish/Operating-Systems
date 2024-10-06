#!/bin/bash

MakeUser(){
read -p "enter the user name: " name
read -sp "enter password: " password
sudo useradd -m $name


echo "$user:$password"| sudo chpasswd

sudo usermod -aG sudo $user

echo "user named $user havve succesfully been created and have been assigned the admin privileges."


}

instaledAPPS(){
#dpkg-query -l
pacman -Q
}

install(){

read -p "Enter the name of application " name
#sudo apt-get install $name
sudo pacman -S $name
echo "$name succesfully installed "
}

cfg_ip(){
sudo ip addr add 10.0.0.1/255.255.255.0 dev eth0
sudo ip route add default via 10.0.0.254
echo "name server $dns "| sudo tee /etc/resolv.conf > /dev/null
echo " IP address, mask, gateway, and DNS of that this configured succesfully"


}

help(){

echo "Options:"
echo "  -uc     to create a new user and assign administrator privileges"
echo "  -ld     list all installed applications"
echo "  -ins    install an application"
echo "  -ipcon  configure IP address, netmask, gateway, and DNS"
echo "  -h      display this help message"

}


main(){
echo "21i-2541 Rai Tabish"
case "$1" in
-ld)
instaledAPPS
;;

-ins)
install
;;

-uc)
MakeUser
;;

-ipcon)
cfg_ip
;;
-h)
help
;;

esac



}

main "$@"
