sudo dd if=build/bootdisk.iso of=/dev/sde bs=1M status=progress
sudo efibootmgr --bootnext 0008
sudo reboot now