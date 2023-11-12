# apk-backup-maker
this little program copy all "APK" or "split APKs" of currently installed application without ROOT permission.

i made this program because i wanted something which can copy all the APKs of currently installed application before i factory reset my device so i have backup which i can install quickly after the reset.

using this tool is very simple and straight, this tool don't take any parameters so just copy this program compiled binary in a dir/folder which has read, write and execute permission
```sh
adb push apk-backup-maker /data/local/tmp

adb shell

cd /data/local/tmp

chmod +x apk-backup-maker #if binary is not executable

./apk-backup-maker
```

# Building the program
because this program is going to be run on the device it has to be the same architecture as the device. most android devices are ARMv8(AARCH64) so you need a C compiler which targets ARMv8.
the simplest way to build this program of the same architecture as your device is to build it on your device itself with Termux Application which you can get from fdroid https://f-droid.org/en/packages/com.termux/

After installing Termux open it and run this commands
```
apt update && apt upgrade
pkg install clang git
git clone https://github.com/the-loan-wolf/apk-backup-maker.git && cd apk-backup-maker
clang main.c -o apk-backup-maker
```
now you have native binary! just run it there to make backup of your installed application
```
./apk-backup-maker
```
