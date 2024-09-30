### uninstall snap




```bash

# Must install gnome-software before uninstall snap
sudo apt update

sudo apt install gnome-software


sudo snap remove --purge $(snap list | awk '!/Disabled|Name/ {print $1}')

sudo apt purge snapd

sudo rm -rf ~/snap
sudo rm -rf /var/snap
sudo rm -rf /var/lib/snapd
sudo rm -rf /var/cache/snapd

sudo apt autoremove

```

### install flatpak

```bash


sudo apt install flatpak

flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

sudo apt install gnome-software-plugin-flatpak

sudo apt update

reboot
```


### software
- kepubify epub to kepub `kepubify --no-hyphenate example.epub`
- Foliate epub viewer
- Typora markdown writer

