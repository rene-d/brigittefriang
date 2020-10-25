


access.log:
179.97.58.61 - - [Nov 05 2020 16:22:20] "POST /login HTTP/1.1" 200 476 "-" "Evil Browser"

Adresse IP: 179.97.58.61

unzip evil_country_landscape.jpg

raids possibles (cf. https://docs.oracle.com/cd/E19871-01/820-1847-20/appendixf.html):
* RAID 0
* RAID 1
* RAID 1 Enhanced Arrays
* RAID 5 Arrays


sudo losetup /dev/loop2 part2.img
sudo losetup /dev/loop3 part3.img

sudo mount /dev/md6 /mnt
unzip /mnt/dump.zip
sudo umount /mnt
sudo mdadm --stop /dev/md6
sudo losetup -D



 volatility -f dump.vmem imageinfo
 volatility -f dump.vmem --profile Win7SP1x64 envars
 # => notepad, dropbox,

volatility -f dump.vmem --profile Win7SP1x64 pstree
    cmd.exe                       1744
    notepad.exe                     1880
    drpbx.exe                        2304

volatility -f dump.vmem --profile Win7SP1x64 memdump -p 1880 -D .

"J'ai payé, je veux retrouver mes fichiers svp"
"Envoyez 500000 EvilCoins ici:"
"Que les choses soient bien claires, nous ne tolérons aucune entrave à notre plan
Votre action de résistance est vaine et dénuée de sens
Nous vous détruirons sans_
"

volatility -f dump.vmem --profile Win7SP1x64 filescan | grep Documents

0x000000003ddb1890      7      0 R--r-d \Device\HarddiskVolume1\Users\user\Documents\Firefox_installer.exe
0x000000001715ed50     16      0 R--r-- \Device\HarddiskVolume1\Users\user\Documents\informations_attaque.txt.evil


volatility -f dump.vmem --profile Win7SP1x64 dumpfiles -D toto -Q 0x000000003ddb1890  -n
volatility -f dump.vmem --profile Win7SP1x64 dumpfiles -D toto -Q 0x000000001715ed50  -n


!!! JigSaw
"Copyright 1999-2012 Firefox and Mozzilla developers. All rights reserved"
dans file.None.0xfffffa800e7892a0.Firefox_installer.exe.dat
